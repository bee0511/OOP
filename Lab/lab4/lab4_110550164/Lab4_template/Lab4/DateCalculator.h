#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

class DateCalculator {
private:
	int year;
	int month;
	int day;
	int changeDays;
	char operand;
	//You can add any variable if you need.
public:
	DateCalculator();
	void readFile(const char *filename);
	void add();
	void minus();
	bool isLeapYear(int year_);
	void showDay();
	//You can add any function if you need.
};