#include "LinkedList.h"
#include "vector"
#include "Stack.h"

Stack::Stack(){
	Head = 0;
}

bool Stack::empty() {
	if (!Head) return true;
	else return false;
}
int Stack::size() {
	int size = 0;
	ListNode* current = Head;
	while (current) {
		current = current->next;
		size++;
	}
	return size;
}
void Stack::push(int x) {
	Push_back(x);
}
void Stack::pop() {
	/*ListNode* previous = Head;
	for (int i = 0; i < size() - 2; i++) {
		previous = previous->next;
	}
	delete previous->next;
	previous->next = 0;*/
	if (!Head) {
		//cout << "Error: No element in the stack.";
		return;
	}
	Delete(size() - 1);
}
int Stack::top() {
	if (!Head) {
		//cout << "Error: No element in the stack.";
		return -1;
	}
	ListNode* current = Head;
	/*for (int i = 0; i < size() - 1; i++) {
		current = current->next;
	}*/
	while (current->next) {
		current = current->next;
	}
	return current->val;
}
void Stack::print() {
	cout << "The values in the stack : ";
	if (!Head) {
		//cout << "Error: No element in the stack." << endl;
		cout << endl;
		return;
	}
	// TODO : Print all the elements in the linked list in order.
	ListNode* current = Head;
	while (current) {
		cout << current->val << " ";
		current = current->next;
	}
	cout << endl;
}