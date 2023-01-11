#include <iostream>
using namespace std;

class A_q1 { 
public: 
 A_q1(): a(1) { b = 2;} 
int a, b; 
}; 

void test1_1(){
    A_q1 c, d; 
    d.a = c.a + c.b; // L1 
    cout << "c.a: " << c.a << endl;
    cout << "c.b: " << c.b << endl;
    cout << "d.a: " << d.a << endl;
    cout << "d.b: " << d.b << endl;
}

int &g_q1( ) { 
    static int b = 0; 
    //cout << "b: " << b << endl;
    return b; // L1 
} 
void k_q1( ) { 
    int &p = g_q1(); // L2 
    p = 3; // L3 
} 
void test1_2(){
    k_q1();
}

class B_q2 { 
public: B_q2( ) { b = 0; } 
 B_q2(int a) { b = a/2; } 
 int b; B_q2 *prev; 
}; 

void test2(){
    cout << "====L1 start====" << endl;
     B_q2 x, y(5), z(3); // L1 x.b=0 z.b=1
     cout << "x.b: " << x.b << endl;
     cout << "z.b: " << z.b << endl;
    x.prev = &z; y.prev = &x; z.prev = &y; //z <- x, x <- y, y <- z
    cout << "====L2 start====" << endl;
    x.prev->b = 2; // L2 z.b=2
     cout << "x.b: " << x.b << endl;
     cout << "z.b: " << z.b << endl;
    cout << "====L3 start====" << endl;
    y.prev->prev->b = y.b; // L3 z.b=y.b=2
     cout << "x.b: " << x.b << endl;
     cout << "z.b: " << z.b << endl;
    B_q2 *p = &x; 
    cout << "====L4 start====" << endl;
    for (int i = 0; i < 1000; ++i) { p = p->prev; p->b = i; } // L4 i=999 z.b=999 x.b=998 y.b=997
     cout << "x.b: " << x.b << endl;
     cout << "z.b: " << z.b << endl;
}


void test3(){
    cout << "====L1 start====" << endl;
    int x = 12, y[] = {1, 2, 3, 8}; // L1 x=12 y:1,2,3,8
    cout << "x: " << x << endl;
    cout << "y[0]: " << y[0] << endl;
    cout << "y[1]: " << y[1] << endl;
    cout << "y[2]: " << y[2] << endl;
    cout << "y[3]: " << y[3] << endl;
    int *q = y; 
    int *qx = &x; 
    cout << "====L2 start====" << endl;
    y[3] = (*q+1) + y[0]; // L2 x=12 y3=(1+1)+1=3=> y=1,2,3,3
    cout << "x: " << x << endl;
    cout << "y[0]: " << y[0] << endl;
    cout << "y[1]: " << y[1] << endl;
    cout << "y[2]: " << y[2] << endl;
    cout << "y[3]: " << y[3] << endl;
    y[0] = *qx + *y; //y0=12+1=13 => y=13,2,3,3
    cout << "====L3 start====" << endl;
    *qx = q[0] + q[2]; // L3 x=13+3=16
       cout << "x: " << x << endl;
    cout << "y[0]: " << y[0] << endl;
    cout << "y[1]: " << y[1] << endl;
    cout << "y[2]: " << y[2] << endl;
    cout << "y[3]: " << y[3] << endl;
    qx = q; //qx->y0
    cout << "====L4 start====" << endl;
    qx[2] = (++q[0]) + (q[2]--); // L4 y2=(1+13)+(3)=17 
       cout << "x: " << x << endl;
    cout << "y[0]: " << y[0] << endl;
    cout << "y[1]: " << y[1] << endl;
    cout << "y[2]: " << y[2] << endl;
    cout << "y[3]: " << y[3] << endl;
}

template<typename T> class X_q4 {//Template -> template, type->typename
public:
    T a;
    X_q4() : a(0) { }
    X_q4 operator+(const X_q4& y) { //T -> X
        X_q4 x;
        x.a =  (*this).a + y.a;
        return x;//&x -> x
    }
};//加了;


void test4(){
    X_q4<int> A,B,X=A+B;
    cout << "X.a: " << X.a << endl;
}


class U_q7 {
public: U_q7() { name = 'U'; cout << name << endl; }
      U_q7(char name) { this->name = name; cout << name << endl; }
      virtual void printf() const { cout << "U:" << name << endl; }
      char name;
};
class W_q7 : public U_q7 {
public: W_q7() { name = 'W'; cout << name << endl; }
      W_q7(char name) { this->name = name; cout << name << endl; }
      virtual void printf() const { cout << "W:" << name << endl; }
};
class Z_q7 : public W_q7 {
public: Z_q7() { name = 'Z'; cout << name << endl; }
      Z_q7(char name) { this->name = name; cout << name << endl; }
      virtual void printf() const { cout << "Z:" << name << endl; }
      char name;
};

void test7() {
    cout << "====L1 start====" << endl;
    U_q7 a('a'); // L1 a
    cout << "====L2 start====" << endl;
    W_q7 b('b'); // L2 U b
    cout << "====L3 start====" << endl;
    Z_q7 c('c'); // L3 U W c
    U_q7* pa = &a; 
    W_q7* pc = &c;
    cout << "====L4 start====" << endl;
    pc->printf(); // L4 Z:c
    cout << "====L5 start====" << endl;
    pa = pc;
    pc = dynamic_cast<Z_q7*>(pa); // L5 
    cout << "====L6 start====" << endl;
    pc->printf(); // L6 fail because we can't cast a base class to its derived class / after modified: Z:c
}

int a = 5; 
int g(int &x, int y) { 
    static int z = 0; 
    ++z; 
    a = 10; x = 5; 
    y = 4; 
    return a + x + z; 
} 

void test9(){
    int c = 2, d = 1; 
    cout << g(c, d) << endl; // L1 g(2,1)=> z=1 x=5 10+5+1=16
    cout << a << endl; // L2 10
    cout << c << endl; // L3 5
    cout << d << endl; // L4 1
    cout << g(c, d) << endl; // L5 z=2 x=5 a=10 10+2+5=17
}

int main() { 
    //test1_1();
    //test1_2();
    //test2();
    //test3();
    //test4();
    //test7();
    //test9();
    return 0;
} 