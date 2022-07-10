#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "DateCalculator.h"
using namespace std;


int main() {
	DateCalculator calculator;
	calculator.readFile("input1.txt");
	cout << endl;
	calculator.readFile("input2.txt");
	cout << endl;
	calculator.readFile("input_HIDDEN.txt");
	cout << endl;
	return 0;
}