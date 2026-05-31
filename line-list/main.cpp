#include <iostream>
#include <locale>
#include <ctime>
#include <fstream>
#include "LineList.h"

using namespace std;

int josephus(int N, int k) {
    LineList<int> list;

    for (int i = N; i >= 1; --i) {
        list.insertFirst(i);
    }

    LineListElem<int>* prev = list.getTail();
    
    int remaining = N;

    while (remaining > 1) {
        for (int i = 1; i < k; ++i) {
            prev = prev->getNext();
        }

        if (prev->getNext() == list.getStart()) {
            list.deleteFirst();
        } else {
            list.deleteAfter(prev);
        }
        
        remaining--;
    }

    return list.getStart() ? list.getStart()->getData() : -1;
}

int main() {
    setlocale(LC_ALL, "Russian");
    
    int N_values[] = {1000, 5000, 10000, 50000, 100000, 500000, 1000000};
    int k = 2;
    int numTests = sizeof(N_values) / sizeof(N_values[0]);
    
    ofstream outFile("results.csv");
    if (!outFile) {
        cerr << "Ошибка открытия файла results.csv для записи!" << endl;
        return 1;
    }
    
    outFile << "N;Ответ;Время расчета (сек)" << endl;
    
    cout << "Задача Иосифа-Флавия (k=" << k << ")" << endl;
    
    for (int i = 0; i < numTests; ++i) {
        int N = N_values[i];
        
        clock_t start = clock();
        int result = josephus(N, k);
        clock_t end = clock();
        
        double timeSec = (double)(end - start) / CLOCKS_PER_SEC;
        
        cout << "N=" << N << " -> Ответ: " << result << " Время: " << timeSec << " сек" << endl;
        
        outFile << N << ";" << result << ";" << timeSec << endl;
    }
    
    outFile.close();
    
    cout << "Результаты сохранены" << endl;
    
    cout << "\nСамопроверка:" << endl;
    cout << "N=100, k=2 -> Ожидаем: 73, Получили: " << josephus(100, 2) << endl;
    cout << "N=1000, k=2 -> Ожидаем: 977, Получили: " << josephus(1000, 2) << endl;
    
    return 0;
}