#pragma once
#include <iostream>
#include <vector>
class Node {
public:
	Node(int val) {
		value = val;
		lchild = NULL;
		rchild = NULL;
		parent = NULL;
	}
	int getValue();
	Node* getLchild();
	Node* getRchild();
	Node* getparent();

	void setValue(int value);
	void setLchild(Node* node);
	void setRchild(Node* node);
	void setparent(Node* node);
private:
	int value;
	Node* lchild;
	Node* rchild;
	Node* parent;
};
