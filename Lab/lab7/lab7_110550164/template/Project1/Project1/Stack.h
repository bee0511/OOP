#pragma once
#include <iostream>
#include "LinkedList.h"
using namespace std;

class Stack :public LinkedList {
public:
	Stack();
	bool empty();
	int size();
	void push(int );
	void pop();
	int top();
	void print();
};