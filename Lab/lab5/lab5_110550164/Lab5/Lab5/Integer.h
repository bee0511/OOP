#ifndef INTEGER_H
#define INTEGER_H 

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Integer
{
private:
	vector<int> num;  //store the number
	bool PrintZero;
	bool isNegative;
public:
	//constructor
	~Integer();
	Integer();
	Integer(string number);	//default constructor
	void invert(vector<int> &num);
	void add(vector<int> num1, vector<int> num2, Integer& result);
	void needToPrintZero();
	void setNegative();
	bool getNegative();
	void print(vector<int> num);
	//operation overload 
	Integer operator +(const Integer& b);
	Integer operator -(const Integer& b);
	Integer operator -();
	Integer operator =(const Integer& b);
	bool operator >(const Integer& b);

	//output overload
	friend ostream& operator << (ostream& out, const Integer& i);
};
#endif