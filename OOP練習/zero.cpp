
#include<stdio.h>
#include<iostream>
#include<cmath>

using namespace std;

class Quadratic{
	Quadratic(){
		this->r1 = 0;
		this->r2 = 0;
	}
	double a, b, c, r1, r2;
	double getDis();

	public:
	Quadratic(double a, double b, double c){
		this->a = a;
		this->b = b;
		this->c = c;
	};

	void findRoot();
};

double Quadratic:: getDis(){
	//Calculate discriminant.
	return b*b - 4*a*c;
}

void Quadratic:: findRoot(){
	double d2 = getDis();
	cout << "d2=" << d2 << endl;
	r1 = ((-b + sqrt(d2)) / (2*a) );
	r2 = ((-b - sqrt(d2)) / (2*a) );
	if(d2 > 0){
		cout << "roots:\t" << (double)r1 << ",\t" << r2 << endl;
	}
	else if(d2 = 0){
		cout << "root:\t" << (double)r1 << ",\t" << r2 << endl;
	}
	else{
		cout << "The equation has no real roots" << endl;
	}
}

int main(){
   Quadratic q1;
    while(cin>>q1){
        q1.findRoot();
    }
    return 0;
}