#pragma once
#ifndef LABIRINT_H
#define LABIRINT_H

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cstdint>

#pragma pack(push, 1)
struct BMPFileHeader {
    uint16_t file_type{0x4D42};
    uint32_t file_size{0};
    uint16_t reserved1{0};
    uint16_t reserved2{0};
    uint32_t offset_data{0};
};

struct BMPInfoHeader {
    uint32_t size{0};
    int32_t width{0};
    int32_t height{0};
    uint16_t planes{1};
    uint16_t bit_count{0};
    uint32_t compression{0};
    uint32_t size_image{0};
    int32_t x_pixels_per_meter{0};
    int32_t y_pixels_per_meter{0};
    uint32_t colors_used{0};
    uint32_t colors_important{0};
};
#pragma pack(pop)

struct Point {
    int x, y;
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
};

class Maze {
private:
    int width;
    int height;
    std::vector<std::vector<int>> grid;
    std::vector<std::vector<uint8_t>> pixels;
    int channels;
    Point start;
    Point finish;

public:
    lairint();
    bool loadFromBMP(const char* file_name);
    void waveAlgorithm();
    void saveToBMP(const char* file_name);
    Point getStart() const { return start; }
    Point getFinish() const { return finish; }
};

#endif
