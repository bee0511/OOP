#include <iostream>

using namespace std;

class Y_q1 { 
 public: 
    Y_q1() { a = b = 1;} 
    int a, b; 
}; 

void test1_1(){
    Y_q1 x, y; 
    y.a = x.a + y.b; // L1 y.a=1+1=2
    cout << "x.a: " << x.a << endl;
    cout << "x.b: " << x.b << endl;
    cout << "y.a: " << y.a << endl;
    cout << "y.b: " << y.b << endl;
}

int *foo_q1( ) { 
    return new int; // L1 no error. allocate a memory space for an integer
} 
void g_q1( ) { 
    int *p = foo_q1(); // L2 no error. assign its address to p
}

void test1_2(){
    g_q1();
}

class X_q2 { 
public: 
    X_q2( ) { x = 0; } 
    X_q2(int a) : x(a) { } 
    int x; X_q2 *next; 
};


void test2(){
    cout << "====L1 start====" << endl;
    X_q2 a, b(10); // L1 a.x=0, b.x=10
    cout << "a.x: " << a.x << endl;
    cout << "b.x: " << b.x << endl;
    a.next = &b; 
    b.next = &a; //a->b b->a
    cout << "====L2 start====" << endl;
    a.next->x = 10; //L2 b.x=10
    cout << "a.x: " << a.x << endl;//0
    cout << "b.x: " << b.x << endl;//10
    cout << "====L3 start====" << endl;
    a.next->next->next->x = 15; // L3 b.x=15
    cout << "a.x: " << a.x << endl;//0
    cout << "b.x: " << b.x << endl;//15
    X_q2 *p = &a; 
    cout << "====L4 start====" << endl;
    for (int i = 0; i < 5; ++i ) { //i=4
        p->x = i; 
        p = p->next; 
    } // L4
    cout << "a.x: " << a.x << endl; //4
    cout << "b.x: " << b.x << endl; //3
}

void test3(){
    cout << "====L1 start====" << endl;
    int a[] = {1, 2, 3}, b = 4; // L1 a=1,2,3
    cout << "a[0]: " << a[0] << endl;
    cout << "a[1]: " << a[1] << endl;
    cout << "a[2]: " << a[2] << endl;
    cout << "====L2 start====" << endl;
    int *p = a; // L2 
    cout << "====L3 start====" << endl;
    *p = *(p + 2); // L3 //a[0]=a[2]=3 a=3,2,3
    cout << "a[0]: " << a[0] << endl;
    cout << "a[1]: " << a[1] << endl;
    cout << "a[2]: " << a[2] << endl;
    cout << "====L4 start====" << endl;
    p = &b; // L4 
    cout << "====L5 start====" << endl;
    a[1] = (*p) + 3; // L5 a[1]=4+3=7 a=3,7,3
    cout << "a[0]: " << a[0] << endl;
    cout << "a[1]: " << a[1] << endl;
    cout << "a[2]: " << a[2] << endl;
}

template<typename T> class A_q4 { //type->typename
public: 
    T x; 
    A_q4(): x(0){}//,->:
    A_q4 &operator=(const A_q4 &a) {//& A a -> A &a 
        x = a.x; //a.x = x; 
        return (*this); //this->*this
    } 
}; 

void test4(){
    A_q4<int> b;
    cout << b.x;
}

class A_q6 { 
    public: A_q6() { name = 'A'; cout << name << endl;} 
    A_q6(char name) { this->name = name; } 
    virtual void printf() const { cout << "\t" << name << endl;} 
    char name; 
}; 
class B_q6: public A_q6 { 
    public: B_q6() { } 
    B_q6(char name) { this->name = name; cout << name << endl;} 
    void printf() const { cout << "B:" << "\t" << name << endl;} 
}; 
class C_q6: public A_q6 { 
    public: C_q6() { } 
    C_q6(char name) { this->name = name; cout << name << endl;} 
    void printf() const { cout << "C:" << "\t" << name << endl;} 
    char name; 
    void assign(){A_q6::name = 'p';}
};

void test7(){
    cout << "====L1 start====" << endl;
    A_q6 a('x'); // L1 no output
    cout << "====L2 start====" << endl;
    B_q6 b('y'); // L2 Ay
    cout << "====L3 start====" << endl;
    C_q6 c('z'); // L3 Az
    A_q6 *p = &b; //upcast to B
    cout << "====L4 start====" << endl;
    p->printf( ); // L4 B:\ty
    p = &c; //upcast to C
    cout << "====L5 start====" << endl;
    p->printf( ); // L5 C:\tz
    c.assign();//7.f)
}

class X_q9 { 
public: 
 X_q9() { cout << "CX" << endl;} 
~X_q9() { cout << "DX" << endl;} 
}; 
class Y_q9: public X_q9 { 
public: 
 Y_q9() { cout << "CY" << endl;} 
~Y_q9() { cout << "DY" << endl;} 
}; 
class Z_q9 : public Y_q9 { 
public: 
 Z_q9() { cout << "CZ" << endl;} 
~Z_q9() { cout << "DZ" << endl;} 
};
void test9(){
    cout << "====L1 start====" << endl;
    X_q9 a; // L1 CX
    cout << "====L2 start====" << endl;
    Y_q9 b; // L2 CX endl CY
    cout << "====L3 start====" << endl;
    Z_q9 *c; // L3 no output
    cout << "====L4 start====" << endl;
    c = new Z_q9; // L4 CX endl CY endl CZ endl
    cout << "====L5 start====" << endl;
    delete c; // L5 DZ endl DY endl DX endl
    cout << "====L5 end====" << endl;
}
int main(){
    //test1_1();
    //test1_2();
    //test2();
    //test3();
    //test4();
    //test7();
    //test9();
}