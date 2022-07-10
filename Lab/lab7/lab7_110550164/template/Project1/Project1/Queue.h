#pragma once
#include <iostream>
#include "LinkedList.h"
using namespace std;

class Queue :public LinkedList {
public:
	Queue();
	bool empty();
	int size();
	void push(int);
	void pop();
	int back();
	int front();
	void print();
};