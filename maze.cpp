#include "maze.h"

using namespace std;

Maze::Maze() : mapWidth(0), mapHeight(0), colorChannels(0) {}

bool Maze::importFromBMP(const char* filename) {
    ifstream bmpFile(filename, ios::binary);
    if (!bmpFile.is_open()) {
        cout << "Не удалось открыть файл" << endl;
        return false;
    }

    BMPFileHeader bmpHeader;
    BMPInfoHeader infoHeader;

    bmpFile.read(reinterpret_cast<char*>(&bmpHeader), sizeof(bmpHeader));
    bmpFile.read(reinterpret_cast<char*>((&infoHeader), sizeof(infoHeader));

    if (bmpHeader.file_type != 0x4D42) {
        return false;
    }

    mapWidth = infoHeader.width;
    mapHeight = abs(infoHeader.height);
    colorChannels = infoHeader.bit_count / 8;

    int bytesPerRow = (mapWidth * colorChannels + 3) & ~3;
    pixelData.resize(mapHeight, vector<uint8_t>(bytesPerRow));
    navigationGrid.resize(mapHeight, vector<int>(mapWidth, 0));

    bmpFile.seekg(bmpHeader.offset_data, ios::beg);
    for (int row = 0; row < mapHeight; row++) {
        bmpFile.read(reinterpret_cast<char*>(pixelData[row].data()), bytesPerRow);
    }
    bmpFile.close();

    bool startDetected = false;
    bool finishDetected = false;

    for (int row = 0; row < mapHeight; row++) {
        int flippedY = mapHeight - 1 - row;
        for (int col = 0; col < mapWidth; col++) {
            int pixelIndex = col * colorChannels;
            uint8_t blue = pixelData[row][pixelIndex];
            uint8_t green = pixelData[row][pixelIndex + 1];
            uint8_t red = pixelData[row][pixelIndex + 2];

            if (red > 140 && green < 80 && blue < 80) {
                targetPoint = Point(col, flippedY);
                finishDetected = true;
                navigationGrid[flippedY][col] = 0;
            }
            else if (green > 140 && red < 80 && blue < 80) {
                sourcePoint = Point(col, flippedY);
                startDetected = true;
                navigationGrid[flippedY][col] = 0;
            }
            else if (red < 100 && green < 100 && blue < 100) {
                navigationGrid[flippedY][col] = -1;
            }
            else {
                navigationGrid[flippedY][col] = 0;
            }
        }
    }

    if (!startDetected || !finishDetected) {
        cout << "Внимание Цветовые маркеры не обнаружены!" << endl;
        if (!startDetected) sourcePoint = Point(mapWidth / 10, mapHeight / 2);
        if (!finishDetected) targetPoint = Point(mapWidth - (mapWidth / 10), mapHeight / 2);
    }

    return true;
}

void Maze::findOptimalPath() {
    if (navigationGrid[sourcePoint.y][sourcePoint.x] == -1 || 
        navigationGrid[targetPoint.y][targetPoint.x] == -1) {
        cout << "Ошибка Старт или финиш заблокирован" << endl;
        return;
    }

    queue<Point> searchQueue;
    searchQueue.push(sourcePoint);
    navigationGrid[sourcePoint.y][sourcePoint.x] = 1;

    int deltaX[4] = {1, -1, 0, 0};
    int deltaY[4] = {0, 0, 1, -1};
    bool pathFound = false;

    while (!searchQueue.empty()) {
        Point currentPos = searchQueue.front();
        searchQueue.pop();

        if (currentPos.x == targetPoint.x && currentPos.y == targetPoint.y) {
            pathFound = true;
            break;
        }

        for (int dir = 0; dir < 4; dir++) {
            int nextX = currentPos.x + deltaX[dir];
            int nextY = currentPos.y + deltaY[dir];

            if (nextX >= 0 && nextY >= 0 && nextX < mapWidth && 
                nextY < mapHeight && navigationGrid[nextY][nextX] == 0) {
                navigationGrid[nextY][nextX] = navigationGrid[currentPos.y][currentPos.x] + 1;
                searchQueue.push(Point(nextX, nextY));
            }
        }
    }

    if (!pathFound) {
        cout << "Ошибка, Путь не найден" << endl;
        return;
    }

    Point currentPos = targetPoint;
    int currentValue = navigationGrid[targetPoint.y][targetPoint.x];

    while (currentValue > 1) {
        int invertedY = mapHeight - 1 - currentPos.y;

        for (int offsetY = -2; offsetY <= 2; offsetY++) {
            for (int offsetX = -2; offsetX <= 2; offsetX++) {
                int pixelY = invertedY + offsetY;
                int pixelX = currentPos.x + offsetX;
                if (pixelY >= 0 && pixelY < mapHeight && pixelX >= 0 && pixelX < mapWidth) {
                    int pixelIndex = pixelX * colorChannels;
                    pixelData[pixelY][pixelIndex] = 0;
                    pixelData[pixelY][pixelIndex + 1] = 0;
                    pixelData[pixelY][pixelIndex + 2] = 255;
                }
            }
        }

        for (int dir = 0; dir < 4; dir++) {
            int prevX = currentPos.x + deltaX[dir];
            int prevY = currentPos.y + deltaY[dir];

            if (prevX >= 0 && prevY >= 0 && prevX < mapWidth && 
                prevY < mapHeight && navigationGrid[prevY][prevX] == currentValue - 1) {
                currentPos = Point(prevX, prevY);
                currentValue--;
                break;
            }
        }
    }

    int invertedStartY = mapHeight - 1 - sourcePoint.y;
    for (int offsetY = -3; offsetY <= 3; offsetY++) {
        for (int offsetX = -3; offsetX <= 3; offsetX++) {
            int pixelY = invertedStartY + offsetY;
            int pixelX = sourcePoint.x + offsetX;
            if (pixelY >= 0 && pixelY < mapHeight && pixelX >= 0 && pixelX < mapWidth) {
                int pixelIndex = pixelX * colorChannels;
                pixelData[pixelY][pixelIndex] = 0;
                pixelData[pixelY][pixelIndex + 1] = 0;
                pixelData[pixelY][pixelIndex + 2] = 255;
            }
        }
    }
    
    cout << "Путь успешно построен" << endl;
}

void Maze::exportToBMP(const char* filename) {
    ofstream bmpFile(filename, ios::binary);
    if (!bmpFile.is_open()) {
        return;
    }

    BMPFileHeader bmpHeader;
    BMPInfoHeader infoHeader;

    int bytesPerRow = (mapWidth * colorChannels + 3) & ~3;
    int totalImageSize = bytesPerRow * mapHeight;

    bmpHeader.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
    bmpHeader.file_size = bmpHeader.offset_data + totalImageSize;

    infoHeader.size = sizeof(BMPInfoHeader);
    infoHeader.width = mapWidth;
    infoHeader.height = mapHeight;
    infoHeader.bit_count = colorChannels * 8;
    infoHeader.size_image = totalImageSize;

    bmpFile.write(reinterpret_cast<char*>(&bmpHeader), sizeof(bmpHeader));
    bmpFile.write(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    for (int row = 0; row < mapHeight; row++) {
        bmpFile.write(reinterpret_cast<char*>(pixelData[row].data()), bytesPerRow);
    }
    bmpFile.close();
}