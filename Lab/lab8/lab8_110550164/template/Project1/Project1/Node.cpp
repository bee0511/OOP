#include "Node.h"
int Node::getValue() {
	// TODO: return the value of node
	return value;
}

Node* Node::getparent() {
	return this->parent;
}

Node* Node::getLchild() {
	// TODO: return the left child of this node
	return this->lchild;
}
Node* Node::getRchild() {
	// TODO: return the right child of this node
	return this->rchild;
}

void Node::setLchild(Node* node) {
	// TODO: set the left child of this node
	this->lchild = node;	
}
void Node::setRchild(Node* node) {
	// TODO: set the right child of this node
	this->rchild = node;
}

void Node::setparent(Node* node) {
	this->parent = node;
}

void Node::setValue(int value) {
	this->value = value;
}