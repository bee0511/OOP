#include "LinkedList.h"
#include "vector"
#include "Queue.h"

Queue::Queue() {
	Head = 0;
}

bool Queue::empty() {
	if (!Head) return true;
	else return false;
}
int Queue::size() {
	int size = 0;
	ListNode* current = Head;
	while (current != 0) {
		current = current->next;
		size++;
	}
	return size;
}
void Queue::push(int x) {
	Push_back(x);
}
void Queue::pop() {
	if (!Head) {
		cout << "Error: Nothing to pop." << endl;
		return;
	}
	Delete(0);
}
int Queue::back() {
	if (!Head) {
		cout << "Error: No element in the list." << endl;
		return -1;
	}
	ListNode* current = Head;
	for (int i = 0; i < size() - 1; i++) {
		current = current->next;
	}
	return current->val;
}
int Queue::front() {
	if (!Head) {
		cout << "Error: No element in the list." << endl;
		return -1;
	}
	return Head->val;
}

void Queue::print() {
	if (!Head) {
		cout << "Error: No element in the queue." << endl;
		return;
	}
	cout << "List: ";
	// TODO : Print all the elements in the linked list in order.
	ListNode* current = Head;
	while (current) {
		cout << current->val << " ";
		current = current->next;
	}
	cout << endl;
}