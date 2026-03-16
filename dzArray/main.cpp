#include "headers/Array.h"
#include <iostream>

using namespace std;



int main(){
 setlocale(LC_ALL, "Russian");
	Array arr(4);
	for (int i = 0; i < 4; i++)
		arr.insert(i + 1);
	cout << arr << endl;
	for (int i = 0; i < 8; i += 2)
		arr.insert(10 + i, i);
	cout << arr << endl;
	for (int i = 1; i < 8; i += 2)
		arr[i] = 20 + i;
	cout << arr << endl;
	for (int i = 6; i >= 0; i -= 3)
		arr.remove(i);
	cout << arr << endl;
}