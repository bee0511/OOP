#include "Integer.h"


Integer::Integer() {
	isNegative = false;
	PrintZero = false;
}
Integer::~Integer() {
	//cout << "D";
}

Integer::Integer(string number) 
{
	//TODO: read the string and construct the huge integer
	isNegative = false;
	PrintZero = false;
	char temp;
	for (int i = 0; i < number.size(); i++) {//the original order
		temp = number[i];
		if (number[i] >= 'a') {
			temp -= 'a';
			temp += 10;
		}
		else {
			temp -= '0';
		}
		num.push_back(temp);
	}
}

Integer Integer::operator +(const Integer& b) {
	//TODO: perform + opearion overloading
	Integer temp;
	vector<int> btemp = b.num;
	add(num, btemp, temp);
	return temp;
}

bool Integer::operator >(const Integer& b) {
	if (num.size() > b.num.size()) return true;
	else if (num.size() < b.num.size()) return false;
	else {
		int i = 0;
		while (num[i] == b.num[i] && i < num.size() -1 ) {
			i++;
		}
		if (num[i] > b.num[i]) return true;
		else if (num[i] < b.num[i])return false;
		else return true;// num1 = num2
	}
}

Integer Integer::operator -(const Integer& b) {
	//TODO: perform - opearion overloading
	Integer temp;
	vector<int> btemp;
	for (int i = 0; i < b.num.size(); i++) {//15'complement
		btemp.push_back(15 - b.num[i]);
	}
	invert(btemp); //Line 60 ~ Line 65: add 15's complement if the smaller number is not the same length of bigger number.

	while (num.size() > btemp.size()) {
		btemp.push_back(15);
	}
	invert(btemp);

	btemp[btemp.size() - 1] += 1;//15's complement
	add(num, btemp, temp);

	invert(temp.num); //Line 70 ~ Line 73: delete the leftmost carry of 15's complement.
	if (temp.num.size() > b.num.size() || temp.num.size() > num.size())	
		temp.num.pop_back();
	invert(temp.num);
	return temp;
}

Integer Integer::operator =(const Integer& b) {
	num.clear();
	num = b.num;
	isNegative = b.isNegative;
	return *this;
}

Integer Integer::operator -() {
	Integer temp;
	temp.num = num;
	temp.isNegative = true;
	return temp;
}

ostream& operator << (ostream& out, const Integer& i) {
	//TODO: perform output overloading
	char table[] = { 'a','b', 'c', 'd', 'e', 'f' };
	bool isZero = true;
	if (i.isNegative == true)out << "-";

	for (int index = 0; index < i.num.size(); index++) {
		if (i.num[index] != 0 || index == i.num.size() - 1 || i.PrintZero == true)//the second condition is for the zero number.
			isZero = false;
		if (i.num[index] >= 10)
			out << table[i.num[index] - 10];
		else if (isZero == false)
			out << i.num[index];
	}
	return out;
}


void Integer:: invert(vector<int>&num) {//numtemp is the vector needed to invert, num is the result.
	vector<int> numtemp = num;
	num.clear();
	for (int i = 1; i <= numtemp.size(); i++) {//invert the number
		num.push_back(numtemp[numtemp.size() - i]);
	}
}


void Integer::add(vector<int>num1, vector<int> num2, Integer& result) {//after the calcultion, still in inverted order.
	int i = 0;
	bool isCarry = false;
	invert(num1);
	invert(num2);

	while (i < num1.size() && i < num2.size()) {
		int numtemp = num1[i] + num2[i] + (int)isCarry;
		if (isCarry == true) isCarry = false;
		if (numtemp >= 16) {
			isCarry = true;
			numtemp -= 16;
		}
		result.num.push_back(numtemp);
		i++;
	}
	cout << endl;

	if (num1.size() == num2.size() && isCarry == true) result.num.push_back(1);
	else if (num1.size() >= num2.size()) {
		while (i < num1.size()) {
			result.num.push_back(num1[i]);
			i++;
		}
	}
	else if (num1.size() < num2.size()) {
		while (i < num2.size()) {
			result.num.push_back(num2[i]);
			i++;
		}
	}
	invert(result.num);
}

void Integer::needToPrintZero() {
	PrintZero = true;
}
void Integer::setNegative() {
	isNegative = true;
}
bool Integer::getNegative() {
	return isNegative;
}
void Integer::print(vector<int> num) {
	for (int i = 0; i < num.size(); i++) {
		cout << num[i] << " ";
	}
	cout << endl;

}