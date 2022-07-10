#include "LinkedList.h"
#include "vector"

LinkedList::LinkedList() {
	// Constructor
	Head = NULL;
}

void LinkedList::Push_back(int x) {
	// TODO : Insert a node to the end of the linked list, the node’s value is x.
	if (!Head) {
		Head = new ListNode(x);
		return;
	}
	ListNode* current = Head;
	while (current->next != 0) {//find last node
		current = current->next;
	}
	ListNode* new_node = new ListNode(x);
	current->next = new_node;

	//cout << "push_back " << x << endl;
	//Print();
	//cout << endl;
}

void LinkedList::Push_front(int x) {
	if (!Head) {
		Head = new ListNode(x);
		return;
	}
	ListNode* temp = new ListNode(x);

	temp->next = Head;
	Head = temp;
	//cout << "push_front " << x << endl;
	//Print();
	//cout << endl;

}

void LinkedList::Insert(int index, int x) {
	// TODO : Insert a node to the linked list at position “index”, the node's
	// value is x. The index of the first node in the linked list is 0.
	if (!Head) {
		Head = new ListNode(x);
		return;
	}
	if (index == 0) {
		Push_front(x);
		return;
	}
	ListNode* previous = Head;
	for (int i = 0; i < index - 1; i++) { // at "index" means we need to find the previous one to insert.
		previous = previous->next;
		if (previous == 0) {
			cout << "Error: Out of the linked list." << endl;
			return;
		}
	}
	ListNode* new_node = new ListNode(x);
	new_node->next = previous->next;//previous->next means current
	previous->next = new_node;
	//cout << "insert " << x << " at index " << index << endl;
	//Print();
	//cout << endl;

}

void LinkedList::Delete(int index) {
	// TODO : Remove the node with index “index” in the linked list.
	if (!Head) {
		cout << "Error: No node to delete.";
		return;
	}
	if (index == 0) {
		ListNode* new_head = Head->next;
		delete Head;
		Head = new_head;
		//cout << "delete index " << index << endl;
		//Print();
		//cout << endl;
		return;
	}
	ListNode* previous = 0, *current = Head;
	for (int i = 0; i < index; i++) {
		previous = current;
		current = current->next;
	}
	if (current == 0) {
		cout << "Error: Out of the linked list.";
		return;
	}
	previous->next = current->next;//index = 0 已經被上面處理掉了
	delete current;
	//cout << "delete index " << index << endl;
	//Print();
	//cout << endl;

}

void LinkedList::Reverse() {
	// TODO : Reverse the linked list.
	// Example :
	//
	// Original List : 1 -> 2 -> 3 -> 4 -> NULL
	// Updated List  : 4 -> 3 -> 2 -> 1 -> NULL
	ListNode* previous = 0, * current = Head, * temp;
	while (current) {
		temp = current->next;		//存current的下一個(因為等等要往前接他會不見)
		current->next = previous;	//往前接
		previous = current;			//更新previous
		current = temp;				//更新current
	}
	Head = previous;
	//cout << "reverse" << endl;
	//Print();
	//cout << endl;

}

void LinkedList::Swap(int index_1, int index_2) {
	if (index_1 == index_2) return;

	// TODO : Swap two nodes in the linked list
	// Example : 
	// index_1 : 1   ,  index_2 : 3
	// 
	// Original List : 1 -> 2 -> 3 -> 4 -> NULL
	// Updated List  : 1 -> 4 -> 3 -> 2 -> NULL

	ListNode* Xcurrent = Head, * Ycurrent = Head;
	ListNode* Xprevious = 0, * Yprevious = 0;
	for (int i = 0; i < index_1; i++) {
		Xprevious = Xcurrent;
		Xcurrent = Xcurrent->next;
	}
	for (int i = 0; i < index_2; i++) {
		Yprevious = Ycurrent;
		Ycurrent = Ycurrent->next;
	}
	if (Xcurrent == 0 || Ycurrent == 0) {
		cout << "Error: Out of the linked list." << endl;
		return;
	}
	if (Xprevious != 0)
		Xprevious->next = Ycurrent;
	else
		Head = Ycurrent;

	if(Yprevious != 0)
		Yprevious->next = Xcurrent;
	else
		Head = Xcurrent;

	ListNode* temp = Xcurrent->next;
	Xcurrent->next = Ycurrent->next;
	Ycurrent->next = temp;
	//cout << "swap " << index_1 << " and " << index_2 << endl;
	//Print();
	//cout << endl;

}

void LinkedList::Print() {
	if (!Head) {
		cout << "Error: No element in the linked list." << endl;
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
	current = Head;
	while (current) {
		cout << "next address " << &current->next << endl;
		current = current->next;
	}
	cout << endl;
}

LinkedList::~LinkedList()
{
	ListNode* current = Head, * next;
		
	while (current != 0) {
		next = current->next;
		delete current;
		current = next;
	}

	Head = 0;
}
