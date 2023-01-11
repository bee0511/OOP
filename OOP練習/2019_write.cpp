#include <iostream>
#include <fstream>

using namespace std;

class Z_q1 { 
 public: Z_q1(): x(-1), y(1) { } 
 int x, y; 
}; 

void test1_1(){
    Z_q1 c, d; //c.x=-1 c.y=1 c.x=-1 c.y=1
    d.x = ++(c.y) + (c.x)--;//c.y=2 d.x=2+(-1)=1 c.x=-2
    cout << "c.x: " << c.x << endl;
    cout << "c.y: " << c.y << endl;
    cout << "d.x: " << d.x << endl;
    cout << "d.y: " << d.y << endl;
}

int *k_q1( ) { 
 return new int[4]; // L1 
} 

void test1_2(){
    int *p = k_q1(); *p = 8; 
    *(&(p[2])+1) = 5; 
    *(p+2) = 2; 
    *(&p[1]) = 3; // L2 
    cout << "p[0]: " << p[0] << endl;
    cout << "p[1]: " << p[1] << endl;
    cout << "p[2]: " << p[2] << endl;
    cout << "p[3]: " << p[3] << endl;
}

class Z_q2 { 
public: 
    Z_q2( ) { c = ' '; } // c is initialized to be a single white space character, i.e., 0x20. 
    Z_q2(char c) : c(c) { } 
    char c; Z_q2 *next, *prev;
}; 

void test2(){
    Z_q2 d('a'), e('b'), f; // L1 
    cout << "====After L1====" << endl;
    cout << "d.c: " << d.c << " e.c: " << e.c << endl;
    d.next = &e; e.next = &f; f.next = &d; // d->e e->f f->d
    d.prev = &f; e.prev = &d; f.prev = &e; // f<-d d<-e e<-f
    f.prev->c = 'x'; //e=x
    d.next->prev->c = 'p'; //L2 //d=p 
    cout << "====After L2====" << endl;
    cout << "d.c: " << d.c << " e.c: " << e.c << endl;
    f.next->next->next->prev->c = 'q'; //e=q 
    (*(d.prev->next->next->next)).c = 'y'; // L3 //f=y
    cout << "====After L3====" << endl;
    cout << "e.c: " << e.c << " f.c: " << f.c << endl;
    Z_q2 *k = &f; 
    for (int i = 0; i < 123; ++i ) { 
        k->c = '0'+i%10; //'0'+2 = '2' ->d=2 e=1 f=0
        k = k->prev; //122/3=2 d<-e<-f
    }//L4
    cout << "====After L4====" << endl;
    cout << "d.c: " << d.c << " f.c: " << f.c << endl;
}

void test3(){
    //df 34 56 78 91 a5 b7 f8 15 e0 3d 10 
    //0  1  2  3  4  5  6  7  8  9  10 11
    unsigned char x[3]; unsigned short y; int z; 
    fstream input; 
    input.open("oop_2019.txt", ios::in|ios::binary ); input.seekg(8, ios::beg);//15 ptr= 8
cout << "L1: " << input.tellg() << endl; // L1 ptr=8
input.read(reinterpret_cast<char*>(&x[0]), sizeof(unsigned char)); //x[0]=15 ptr=9
cout << "L2: " << input.tellg() << endl; input.seekg(-3, ios::cur); // L2 ptr=9, ptr=6 b7
input.read(reinterpret_cast<char*>(&x[1]), sizeof(unsigned char)); //x[1]=b7 ptr=7
cout << "L3: " <<  input.tellg() << endl; input.seekg(-6, ios::end); // L3 ptr=7, ptr=6 by
input.read(reinterpret_cast<char*>(&y), sizeof(unsigned short)); //y=f8b7, ptr=8 15
cout << "L4: " <<  input.tellg() << endl; input.seekg(2, ios::cur); // L4 ptr=8, ptr=10 3d
input.read(reinterpret_cast<char*>(&x[2]), sizeof(unsigned char)); //x[2]=3d ptr=11
cout << "L5: " <<  input.tellg() << endl; input.seekg(-5, ios::end); // L5 ptr=11,ptr=7
input.read(reinterpret_cast<char*>(&z), sizeof(z)); //ptr=11 z=3de015f8
cout << "x[0]: " << hex << (int)x[0] << endl;
cout << "x[1]: " << hex << (int)x[1] << endl;
cout << "x[2]: " << hex << (int)x[2] << endl;
cout << "y: " << hex << y << endl;
cout << "z: " << hex << z << endl;
}

template<typename TD = int > class X_q4 {//datatype ->typename, == -> =
public://private->public
    X_q4(): a(0) { } // initialize a to 0. //X_q4( ):: 0(a)->X_q4(): a(0)
    X_q4(TD a): a(a) { } // initialize this->a to a // ( int a) a(a) -> (TD a): a(a)
    X_q4 operator*(X_q4 const &b) {//X_q4*->X_q4, & const b->const &b
        X_q4 c;//多了&
        c.a = a * b.a; //c->a, (*this).a, b->a
        //cout << "val: " << c.a << endl;
        return (c);
    }
    TD a; //多了<>
};

void test4(){
    X_q4<int> a(1),b(2);
    X_q4<int> c= a*b;
    cout << "c.a: " << c.a << endl;
    X_q4<double> x(1.5),y(2.5);
    X_q4<double> z=x*y;
    cout << "z.a: " <<  z.a << endl;
}

class P_q7 { 
public: P_q7( ) { c = 'P'; cout << c << endl;} 
 P_q7(char c) { (*this).c = c; } 
 void printf() const { cout << "\t" << c << endl;} 
 char c; 
}; 
class Q_q7: public P_q7 { 
public: Q_q7( ) { c = 'q'; } 
 Q_q7 (char c) { this->c = c; cout << c << endl;} 
 virtual void printf() const { cout << "Q:" << "\t" << c << endl;} 
 char c; 
}; 
class R_q7: public Q_q7 { 
public: R_q7( ):Q_q7('q') { cout << "c:" << P_q7::c << endl; } 
 R_q7(char name): Q_q7( ) { this->c = c; cout << c << endl;} 
 virtual void printf() const { cout << "R:" << "\t" << P_q7::c << endl;} 
}; 

void test7(){
    cout << "====L1 start====" << endl;
    R_q7 x; // L1 //P q c:P
    cout << "====L2 start====" << endl;
    Q_q7 y('b'); // L2 //P b
    cout << "====L3 start====" << endl;
    P_q7 z('c'); // L3 //NA
    Q_q7 *a = &x; 
    cout << "====L4 start====" << endl;
    a->printf( ); // L4 //R:\tP 
    a = &y; 
    cout << "====L5 start====" << endl;
    a->printf( ); // L5 //Q:\tb
}

class A_q9 { 
    public:
static int cc; 
 public: 
 A_q9( ) { cc++; cout << "cA" << endl;} ~A_q9( ) { cc--; cout << "dA" << endl;} 
}; 
class B_q9: public A_q9 { 
 public: 
 B_q9( ) { cc += 2; cout << "cB" << endl;} ~B_q9( ) { cc -= 2; cout << "dB" << endl;} 
}; 
class C_q9 : public B_q9 { 
 public: 
 C_q9( ) { cc += 3; cout << "cC" << endl;} ~C_q9( ) { cc -=3; cout << "dC" << endl;} 
}; 
int A_q9::cc = 0;

void test9(){
    cout << "====L1 start====" << endl;
    A_q9 *a; // L1 //NA 
    cout << "====L2 start====" << endl;
    B_q9 b; // L2 //cA cB c=3
    cout << "====L3 start====" << endl;
    C_q9 *c; // L3 //NA
    cout << "====L4 start====" << endl;
    a = new B_q9; // L4 //cA cB c=3+3=6 
    cout << "====L5 start====" << endl;
    c = new C_q9; // L5 //cA cB cC c=6+6=12
    cout << "====L6 start====" << endl;
    delete c; // L6 //dC dB dA c=12-6 = 6
    cout << "====L6 end====" << endl;
    cout << "A::cc: " << A_q9::cc << endl;
}

template<typename T>
T min(T &a, T &b, T &c){
    if (a > b){swap(b,a);}
    if (a > c){swap(c,a);}
    return a;
}

void test10(){
    int a = 3, b=2,c=4;
    int minimal = min(a,b,c);
    cout << "minimal: " << minimal << endl;
}

int main(){
    //test1_1();
    //test1_2();
    //test2();
    //test3();
    //test4();
    //test7();
    //test9();
    //test10();
    return 0;
}