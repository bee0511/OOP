#include<iostream>
#include<fstream>
#include<string>
#include"LinkedList.h"
#include"Stack.h"
#include"Queue.h"
using namespace std;

#define file "test.txt"
int main() {
	/*Queue queue;
	for (int i = 0; i < 5; i++) {
		queue.push(i);
	}
	queue.print();
	queue.pop();
	queue.print();
	cout << " front = " << queue.front() << endl;
	cout << " back = " << queue.back() << endl;
	queue.pop();
	queue.pop();
	queue.pop();
	queue.pop();
	queue.pop();
	queue.print();
	*/
	/*Stack stack;
	for (int i = 0; i < 5; i++) {
		stack.push(i);
	}
	stack.pop();
	stack.Print();
	stack.pop();
	stack.Print();
	stack.pop();
	stack.Print();
	for (int i = 0; i < 5; i++) {
		stack.push(i);
	}
	stack.Print();
	stack.pop();
	cout << stack.top() << endl;
	stack.pop();
	cout << stack.top() << endl;	
	stack.pop();
	cout << stack.top() << endl;
	stack.Print();*/

	ifstream File;
	File.open("input2.txt");
	if (!File.is_open()) {
		cout << "Can't open txt file" << endl;
		return 0;
	}

	int TestCase = 0;
	File >> TestCase;

	while (TestCase) {

		LinkedList List;
		int num_op = 0;
		File >> num_op;
		for (int i = 0; i < num_op; i++) {
			char op;
			int val;
			int index;
			int index2;

			File >> op;

			switch (op)
			{
			case 'b':
				File >> val;
				List.Push_back(val);
				break;
			case 'f':
				File >> val;
				List.Push_front(val);
				break;
			case 'i':
				File >> index;
				File >> val;
				List.Insert(index, val);
				break;
			case 'd':
				File >> index;
				List.Delete(index);
				break;
			case 'r':
				List.Reverse();
				break;
			case 's':
				File >> index;
				File >> index2;
				List.Swap(index, index2);
				break;
			default:
				break;
			}
		}
		List.Print();

		cout << endl;
		TestCase--;
	}
	
	system("pause");
	return 0;
}