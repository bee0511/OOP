#include <iostream>
#include <fstream>
#include <string>


using namespace std;

class OOP{
    private: int a;
    protected: int b;
    public: int c;
    OOP(){
        a = b = c = 1;
    }
};

class CPP: protected OOP{
    public: int c; static int d;
    CPP(){c = 5;}
    void f(){
        c = 10;// L1
    }
};

int CPP::d = -1;//L2
OOP x;      //L3 create a object of OOP
OOP y();    //L4 create a object of OOP with no argument
OOP *z;     //L5 create a pointer of OOP
CPP e;

void test1(){
    //OOP *w = new CPP(); // L6 No. base class pointer can not point to protected or private derived class
    //x.a = 1;            // L7 No. because a is a private member of x
    //e.b = 2;            // L8 No. because b is a protected member of e
    e.c = 3;             // L9 Yes.
    CPP s; s.CPP::c = 7; // L10 Yes
}

class X_q2{
    public: X_q2(){a=-1;b=1;}
    X_q2(int a,int b = 3){this->a=a;(*this).b=b;}
    int a,b;
};

class Y_q2:public X_q2{
    public: Y_q2(): X_q2(5){}
    Y_q2(int a, int b){this->b = b; b++;}
};

void test2_1(){
    X_q2 x,y(7); //x.a=-1, x.b=1, y.a=7, y.b=3
    Y_q2 z,w(2,1);//z.a=5, z.b=3, w.a=2, w.b=1
    cout << "x.a: " << x.a << endl;//-1
    cout << "y.b: " << y.b << endl;//3
    cout << "z.a: " << z.a << endl;//5
    cout << "w.b: " << w.b << endl;//1
}

class W_q2{
public:
    const W_q2 *n;
    int v;
    W_q2(){v=0;n=0;}
    W_q2(const W_q2 & w){v = w.v; v++; n = &w;}
};

void test2_2(){
    W_q2 a, b(a), c(b);//a.v=0, a.n=0, b.v=1, b.n=a, c.v=2, c.n=b
    W_q2* d = new W_q2(c);//d->v=3, d->n=b
    W_q2 e(*d);//L2 //e.v=4, e.n=b
    cout << "b.v: " << b.v << endl;
    cout << "d->v: " << d->v << endl;
    cout << "e.v: " << e.v << endl;
    cout << "c.n: " << c.n << endl;//c.n points to b
    cout << "b's address: " << &b << endl;
}
int s = 0;
int f(int a,int n){
    if(a<2*n){
        cout << s << endl;
        return s;
    }
    s = f(a+2,n);
    return s;
}
int h(int a, int n , int &s){
    if(a>2*n){
        cout << s << endl;
        return s;
    }
    s += 2* n - a;
    cout << "s: " << s << endl;
    h(a+1,n,s);
    return s;
}
int k(int a ,int b,int n, int s){
    if(s == 1){
        cout << a%n <<endl;
        return a%n;
    }
    cout << a << " " << b << " " << n << " " << s << endl;
    return k(a*b,b,n,s-1);
}
void test4(){
    //f(-1,1);
    //h(0,1,s);
    k(3,3,7,12);
}

class X_q5{
public: 
    int x;
    string n;
    X_q5(){ n = "z" ; x = 0;}
    X_q5(string n, int x){
        this->n = n ; this->x = x;
    }
    X_q5(const X_q5 &a){
        this->n = "copy of\t" + (&a)->n;
        this->x=a.x;
    }
    ~X_q5(){cout << n << endl;}
    X_q5 &operator=(const X_q5 &a){
        this->n = "assign\t" + a.n + "\tto\t" + this->n;
        return *this;
    }
    void p() const{
        cout << "X:" << "\t" << n << "\t" << x << endl;
    }
};

void q03_1(X_q5 x){
    x.p();
}

void q03_2(const X_q5 &x){
    x.p();
}

void q03(){
    cout << "=======L1======" << endl;
    X_q5 x1; x1.p();//L1 (x1.n=z, x1.x=0) X:\tz\t0 endl
    cout << "=======L2======" << endl;
    X_q5 x2 = x1 ; x2.p();//L2 (x2.n=copy of \tz, x2.x=0) X:\tcopy of \tz\t0 endl
    cout << "=======L3======" << endl;
    X_q5 x3("x3", 2); x3.p();//L3 (x3.n=x3, x3.x=2) X:x3\t2 endl
    cout << "=======L4======" << endl;
    (x3 = x1).p();//L4 (x3.n= assign\tz\tto\tx3, x3.x=2) X:assign\tz\tto\tx3\t2 endl
    cout << "=======L5======" << endl;
    q03_1(x2);//L5 X:\tcopy of copy of \tz\t0 endl copy of copy of\tz endl
    cout << "=======L6======" << endl;
    q03_1(X_q5("good", 5));//L6 X:\tgood\t5 endl good endl
    cout << "=======L7======" << endl;
    q03_2(*(new X_q5("hello", 6)));//L7 X:\thello\t6 endl
    //assign\tz\tto\tx3 endl
    //copy of \tz endl
    //z
}

void test5(){
    q03();
}

void reportData(char &a, short &b, int &c){
    cout << "a: " << dec << (short) a << endl;
    cout << "b: " << dec << (short) b << endl;
    cout << "c: " << dec << (short) c << endl;
}

void test6(){
    char a; short b; int c;
    fstream input;
    input.open("dat.txt", ios::in|ios::binary);
    cout << input.tellg() << endl;
    input.read(reinterpret_cast<char*>(&a),sizeof(a));
    cout << input.tellg() << endl; input.seekg(3,ios::cur);
    input.read(reinterpret_cast<char*>(&b),sizeof(b));
    cout << input.tellg() << endl; input.seekg(-2,ios::cur);
    input.read(reinterpret_cast<char*>(&c),sizeof(c));
    reportData(a,b,c);

}

template <typename T> void h(int m){
    int index = -1;
    const int n = 10; T a[n];
    for (int i = 0 ; i < n ; ++i) {
        a[i] = (i+1) % m + 0.5;
        //cout << "a[" << i << "]: " << a[i] << " ";
    }
    int j =0 ; int c = 0;
    while(j < n -1){
        if (a[j] < a[j+1]){
            index = j;
            ++c;
        }
        ++j;
    } 
    cout << index << "\t" << c << endl;
}

void u(int m){
    int index = -1;
    const int n = 100; int a[n];
    for (int i = 0 ; i < n ; ++i) a[i]=(i+1) % m;
    int j = 0 ; static int c = 0;
    while(j < n-1){
        if (a[j] > a[j+1]) ++c;
        ++j;
    }
    cout << j << "\t" << c << endl;
}

void test7(){
    cout << "=====h<double>(2)=====" << endl;
    h<double>(2);//1.5 0.5 1.5 0.5 1.5 0.5 1.5 0.5 1.5 0.5 index=7 c=4
    cout << "=====h<int>(5)=====" << endl;
    h<int>(5);
    cout << "=====u(1)=====" << endl;
    u(1);
    cout << "=====u(2)=====" << endl;
    u(2);
}

class X_q9{
    public:
    X_q9(){ a = 1 ; pp("CX", a);}
    X_q9(int b){a = b ; pp("CXb", a);}
    virtual void h() = 0;
    void k() {pp("p:", a);}
    void p(){pp("p:",a);}
    int a;
    void pp(const string &s, int v){
    cout << s << "\t" << v << endl;
}
};

class Y_q9: public X_q9{
    public:
    Y_q9(){pp("CY", a);}
    Y_q9(int b){a=b+1;pp("CYb",a);}
    void h(){a=a+1;}
    void k(){a=a+3;}
    void pp(const string &s, int v){
    cout << s << "\t" << v << endl;
}
};

class W_q9: public Y_q9{
    public:
    W_q9(){pp("CW",a);}
    W_q9(int b){a = b + b; pp("CWb",a);}
    virtual void h(){a = a+5;}
    virtual void k(){a = a+7;}
    void pp(const string &s, int v){
    cout << s << "\t" << v << endl;
}
};

void pp(const string &s, int v){
    cout << s << "\t" << v << endl;
}

void test9(){
    cout << "=======L1 start=======" << endl;
    Y_q9 y;//L1 CX\t1 endl CY\t1
    cout << "=======L1 end=======" << endl;
    W_q9 a;
    cout << "=======L2 start=======" << endl;
    W_q9 b(2); //L2 CX\t1 endl CY\t1 endl CWb\t4 endl
    cout << "=======L2 end=======" << endl;
    cout << "=======L3 start=======" << endl;
    a.p(); //L3 p:\t1
    cout << "=======L3 end=======" << endl;
    X_q9 *q = &y;
    y.h();//y.a=2
    cout << "=======L4 start=======" << endl;
    q->p(); //L4 //p:\t2
    cout << "=======L4 end=======" << endl;
    q = &b;
    cout << "=======L5 start=======" << endl;
    q->p(); //L5 p:\t4
    cout << "=======L5 end=======" << endl;
}

void test10(){
    unsigned short a[] = {0x4321, 0x5678, 0xcdef, 0x89ab};
    unsigned char *r = (unsigned char*) a;
    unsigned short *p = a; unsigned int *q = (unsigned int*) a;
    unsigned long long *l = (unsigned long long *) a;
    //cout << sizeof(unsigned char) <<  " " << sizeof(unsigned short) << endl;
    //cout << sizeof(long long) << endl;
    cout << "a[3]: " << hex << a[3] << endl;//89ab
    cout << "(r+2)[2]: " <<  hex << (short)(r+2)[2] << endl;//ef
    cout << "(p+1)[2]: " <<  hex << (p+1)[2] << endl;//89ab
    cout << "q[1]: " <<  hex << (int)q[1] << endl;//89abcdef
    cout << "l[0]: " << (long long )l[0] << endl;
    r[1]= 0x56;
    cout << "r[1]: " << hex << (short) r[1] << endl; 
}

int main(){
    //test10();
    //test9();
    //test7();
    //test6();
    //test5();
    //test4();
    //test2_2();
    //test2_1();
    //test1();
    return 0;
}