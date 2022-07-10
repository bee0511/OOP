#include "DateCalculator.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

DateCalculator::DateCalculator():year(2000),month(1),day(1), changeDays(0){}

void DateCalculator::readFile(const char *fileName) {
	//TODO:
	//Read the data from the txt file.
	//The file is in the Lab4_template/Lab4.
	// 
	//Hint: You can use get() to get a character in ifstream.
	//      You can use getline() to get one line in the txt file.
	//      You can use atoi() or stoi() to change variable type from string to int
	ifstream input;
	char slash;

	input.open(fileName);

	if (!input.is_open()) {
		cout << "Could not open the file - " << fileName << " -" << endl;
		input.close();
		system("pause");
	}
	else {
		cout << fileName << " is opened successfully." << endl;
		cout << "output of " << fileName << endl;
		while (input >> operand >> year >> slash >> month >> slash >> day >> changeDays) {
			switch (operand) {
			case '+':
				add();
				break;
			case '-':
				minus();
				break;
			default:
				break;
			}
			showDay();
		}
		input.close();
		cout << fileName << " closed." << endl;
	}
}

void DateCalculator::add() {
	//TODO:
	//Calculate the date add the changeDays.
	while (day + changeDays > 0) {
		switch (month) {
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			month++;
			changeDays -= 31;
			break;
		case 2:
			month++;
			if (isLeapYear(year)) changeDays -= 29;
			else changeDays -= 28;
			break;
		case 4: case 6: case 9: case 11:
			month++;
			changeDays -= 30;
			break;
		default:
			year++;
			month -= 12;
			break;
		}
	}
	day += changeDays;
	if (day <= 0) {
		month--;
		if (month == 0) {
			year--;
			month = 12;
		}
		else {
			switch (month) {
			case 1: case 3: case 5: case 7: case 8: case 10: case 12:
				day += 31;
				break;
			case 4: case 6: case 9: case 11:
				day += 30;
				break;
			case 2:
				if (isLeapYear(year)) day += 29;
				else day += 28;
				break;
			default:
				break;
			}
		}
	}
}

void DateCalculator::minus() {
	//TODO:
	//Calculate the date minus the changeDays.
	int sum = day, temp = month - 1;
	while (temp) {
		switch (temp) {
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			temp--;
			sum += 31;
			break;
		case 4: case 6: case 9: case 11:
			temp--;
			sum += 30;
			break;
		case 2:
			temp--;
			if (isLeapYear(year)) sum += 29;
			else sum += 28;
			break;
		default:
			break;
		}
	}
	sum -= changeDays;
	while (sum <= 0) {
		year--;
		sum += (365 + (isLeapYear(year) ? 1 : 0));
	}
	month = 1;
	bool flag = true;
	while (flag) {
		switch (month) {
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			sum -= 31;
			if (sum <= 0) {
				day = sum + 31;
				flag = false;
			}
			else month++;
			break;
		case 4: case 6: case 9: case 11:
			sum -= 30;
			if (sum <= 0) {
				day = sum + 30;
				flag = false;
			}
			else month++;
			break;
		case 2:
			if (isLeapYear(year)) {
				sum -= 29;
				if (sum <= 0) {
					day = sum + 29;
					flag = false;
				}
				else month++;
			}
			else {
				sum -= 28;
				if (sum <= 0) {
					day = sum + 28;
					flag = false;
				}
				else month++;
			}
			break;
		default:
			break;
		}
	}
	/*while (changeDays - day > 0) {
		switch (month) {
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			month--;
			changeDays -= 31;
			break;
		case 4: case 6: case 9: case 11:
			month--;
			changeDays -= 30;
			break;
		case 2:
			month--;
			if (isLeapYear(year)) changeDays -= 29;
			else changeDays -= 28;
			break;
		default:
			year--;
			month += 12;
			break;
		}
		//cout << endl << "month: " << month << "\tchangeDays: " << changeDays << endl;
	}
	//cout << endl << "day: " << day << "\tchangeDays: " << changeDays << endl;
	if (day == changeDays || changeDays < 0) day -= changeDays;
	else day -= (changeDays + 1);
	if (day <= 0 || month == 0) {
		month--;
		if (month <= 0) {
			year--;
			month = 12;
		}
		switch (month) {
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			day += 31;
			break;
		case 4: case 6: case 9: case 11:
			day += 30;
			break;
		case 2:
			if (isLeapYear(year)) day += 29;
			else day += 28;
			break;
		default:
			break;
		}
	}*/
}

bool DateCalculator::isLeapYear(int year_) {
	//TODO: 
	//Determine whether year_ is a leap year.
	if (year_ % 400 == 0) return true;
	else if (year_ % 100 == 0) return false;
	else if (year_ % 4 == 0) return true;
	else return false;
}

void DateCalculator::showDay() {
	//TODO: 
	//The function output the date on the screen.
	//Hint: You can use setw() to set the length of the number.
	//      You can use setfill('c') to fill 'c' to the empty space.
	//      Two functions of above is in iomanip header file. 
	cout << year 
		<< "/" << setfill('0') << setw(2) << month
		<< "/" << setfill('0') << setw(2) << day
		<< endl;
}