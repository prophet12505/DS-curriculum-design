#include "Heap.h"
#include <iostream>

int main()
{
	int num;
	unsigned long minCost = 0;
	cin >> num;
	Heap heap(num);
	getchar();
	int size = num;
	// insert input items in the min-heap
	while (size > 0) {
		int item;
		cin >> item;
		heap.insert(item);
		size--;
	}
	// extract smallest two of them and insert their num into the heap
	while (heap.length() > 2) {
		int new_item;
		int a = heap.extract();
		int b = heap.extract();
		new_item = a + b;
		heap.insert(new_item);
		minCost += new_item;
	}
	// deal with the remain items
	if (num <= 0) {
		cout << "请输入正整数!";
	}
	else if (num == 1) {
		int remain_1 = heap.extract();
		minCost += remain_1;
		cout << minCost;
	}
	else if (num >= 2) {
		int remain_2 = heap.extract();
		int remain_1 = heap.extract();
		minCost += remain_1;
		minCost += remain_2;
		cout << minCost;
	}
}
