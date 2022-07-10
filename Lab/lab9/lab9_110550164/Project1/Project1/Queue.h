#pragma once
#include <iostream>
#include "LinkedList.h"
using namespace std;

class Queue :public LinkedList {
public:
	Queue();
	bool empty();
	int size();
	void enqueue(int);
	void dequeue();
	int back();
	int front();
	void print();
};