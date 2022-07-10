#include <iostream>
#include <fstream>
#include "Integer.h"

using namespace std;

//read the data from the file
void readFile(const char* fileName);


int main()
{
	readFile("input1.txt");
	readFile("input2.txt");
	readFile("input3.txt");
	//readFile("test.txt");
	return 0;
}

void readFile(const char* fileName) {
	
	ifstream inputFile;
	inputFile.open(fileName);
	if (!inputFile.is_open()) {
		cout << "Could not open the file - " << fileName << " -" << endl;
		system("pause");
	}
	//TODO: Read the input file here.
	//int lines = ...
	cout << "======= Open " << fileName << "========" << endl;
	int lines;
	inputFile >> lines;
	//cout << lines << endl;
	for (size_t i = 0; i < lines; i++) {
		string temp, num;
		char operand;
		inputFile >> temp;
		//cout << temp << endl;
		int index = 0;
		if (temp[0] == '-') {
			index++;
		}
		while (temp[index] != '+'
			&& temp[index] != '-') {
			num.push_back(temp[index]);
			index++;
		}
		operand = temp[index];
		Integer a(num);
		if (temp[0] == '-')
			a.setNegative();
		temp.assign(temp, index + 1, temp.size() - index - 1);
		Integer b(temp);
		//TODO: Implement your add or minus
		Integer answer;
		if (operand == '+') {//a and b is in inverted order.
			if (a.getNegative()) {
				if (b > a) answer = b - a; //-a+b=b-a
				else  answer = -(a - b);
			}
			else  answer = a + b;  
		}
		else if(operand == '-'){//operand == '-'
			if (a.getNegative()) 
				answer = -(b + a); //-a-b=-(b+a)
			else {
				if (a > b) answer = a - b;//a-b
				else answer = -(b - a);
				//cout << "===" << (a > b) << endl;
			}
		}
		//cout << answer.getNegative() << endl;
		a.needToPrintZero();
		b.needToPrintZero();
		cout << i + 1 << endl;
		cout << "num1: " << a << endl;
		cout << "num2: " << b << endl;
		cout << "result: " << answer << endl << endl;
	}
	inputFile.close();
	cout << "======= Close " << fileName << "========" << endl;
}