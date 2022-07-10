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
	File.open("input1.txt");
	if (!File.is_open()) {
		cout << "Can't open txt file" << endl;
		return 0;
	}

	int TestCase = 0;
	File >> TestCase;

	while (TestCase) {
		char datatype;
		File >> datatype;
		//if (datatype == 'S')
			Stack s;
		//else if (datatype == 'Q')
			Queue q;
		int num_case = 0;
		File >> num_case;
		for (int i = 0; i < num_case; i++) {
			string op;
			int num_op;
			int val;

			File >> op;
			if (op == "push") {
				File >> val;
				s.push(val);
			}
			else if (op == "pop") {
				s.pop();
			}
			else if (op == "print") {
				if (datatype == 'S')
					s.print();
				else
					q.print();
			}
			else if (op == "en") {
				File >> val;
				q.enqueue(val);
			}
			else if (op == "de") {
				q.dequeue();
			}
		}
		cout << endl;
		TestCase--;
	}
	
	system("pause");
	return 0;
}