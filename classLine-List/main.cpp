#include "LineList.h"

#include <ctime>
#include <fstream>
#include <iostream>
#include <locale>
#include <vector>

using namespace std;

static int josephus_list(int n, int k) {
    LineList<int> list;
    for (int i = n; i >= 1; --i) list.insertFirst(i);

    LineListElements<int>* prev = list.getTail();
    int remaining = n;

    while (remaining > 1) {
        for (int step = 1; step < k; ++step) {
            prev = prev->getNext();
        }

        if (prev->getNext() == list.getStart()) {
            list.deleteFirst();
        } else {
            list.deleteAfter(prev);
        }

        --remaining;
    }

    return list.getStart() ? list.getStart()->getData() : -1;
}

static int josephus_vector(int n, int k) {
    vector<int> v;
    v.reserve(n);
    for (int i = 1; i <= n; ++i) v.push_back(i);

    size_t index = 0;
    while (v.size() > 1) {
        index = (index + (size_t)k - 1) % v.size();
        v.erase(v.begin() + (ptrdiff_t)index);
    }
    return v.empty() ? -1 : v[0];
}

int main() {
    setlocale(LC_ALL, "Russian");

    const int k = 2;
    int n_values[] = {1000, 5000, 10000, 50000, 100000, 500000, 1000000};
    int count = (int)(sizeof(n_values) / sizeof(n_values[0]));

    ofstream csv("results.csv");
    csv << "N,k,answer,time_list,time_vector\n";

    cout << "--- Тестирование Иосифа Флавия ---\n";
    cout << "k=" << k << "\n";

    for (int i = 0; i < count; ++i) {
        int n = n_values[i];

        clock_t start_list = clock();
        int ans_list = josephus_list(n, k);
        clock_t end_list = clock();
        double t_list = double(end_list - start_list) / CLOCKS_PER_SEC;

        clock_t start_vec = clock();
        int ans_vec = josephus_vector(n, k);
        clock_t end_vec = clock();
        double t_vec = double(end_vec - start_vec) / CLOCKS_PER_SEC;

        cout << "N=" << n << " -> answer=" << ans_list
             << " time_list=" << t_list << "s"
             << " time_vector=" << t_vec << "s" << '\n';

        csv << n << ',' << k << ',' << ans_list << ',' << t_list << ',' << t_vec << '\n';

        if (ans_list != ans_vec) {
            cerr << "ERROR: answers differ for N=" << n
                 << " list=" << ans_list << " vector=" << ans_vec << '\n';
            return 1;
        }
    }

    cout << "\nСамопроверка (k=2):\n";
    cout << "N=100  -> ожидаем 73, получили " << josephus_list(100, 2) << '\n';
    cout << "N=1000 -> ожидаем 977, получили " << josephus_list(1000, 2) << '\n';

    cout << "\nГотово! results.csv сохранен.\n";
    return 0;
}
