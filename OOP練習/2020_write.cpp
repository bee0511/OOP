#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class A_q1_1 { 
 public: A_q1_1( ) { x = 1; y = 2; } 
A_q1_1(int a): x(a), y(a+1) { } 
 int x, y; 
}; 
class B_q1_1 : public A_q1_1 { 
 public: B_q1_1( ): A_q1_1( 2 ) { x = y+1; } 
 B_q1_1( int a ) { x = ++a; } 
};

void test1_1(){
    A_q1_1 a; //a.x=1 a.y=2
    B_q1_1 x(1), y; //x.x=1+1=2, x.y=2, y.x=3+1=4, y.y=3
    y.x = --(x.x) + ++(a.y); // L1 y.x=(2-1)+(2+1)=4, x.x=2-1=1, a.y=2+1=3
    cout <<  a.y << " " <<  x.x << " " << y.x << " "<<  y.y << endl;//3,1,4,3
}

class A_q1_2 { 
 public: A_q1_2( ) { x = 1; } 
 A_q1_2 &operator=(A_q1_2 a) {
        x = x + 2*a.x;
        return *this; //bug line 
    } 
    int x; 
}; 

void test1_2(){
    A_q1_2 a; (a = (a = *(new A_q1_2))); //(a = a = (1)) -> (a = 1 + 2*1=3)->(3 + 2*3) = 9
    cout << a.x << endl; //L1 9
}

class A_q2 { 
public: int a; 
    A_q2( ) { a =11 ; } 
    A_q2( int a) { (*this).a = a; } 
    void printf() const { 
        cout << "A:" << "\t" 
        << a << endl; 
    } 
};

class B_q2: public A_q2 { 
public: int b; 
    B_q2( ) { b = 12; } 
    B_q2 (int b) { this->b = b + a; 
    cout << "B:" << b++ 
    << endl; } 
    virtual void printf() const { 
    cout << "B:" << "\t" 
    << b << endl;} 
};

class C_q2: public A_q2 { 
    public: int a; 
    C_q2( ): A_q2(13) { a = 10; 
    cout << "a:" << A_q2::a << endl; } 
    C_q2(int c): A_q2( ) { this->a = c; 
    cout << "C:" << a << endl; } 
    virtual void printf() const { 
    cout << "C:" << "\t" 
    << C_q2::a << "\t" << A_q2::a << endl; } 
};

void test2(){
    cout << "=======L1 start=======" << endl;
    B_q2 a; a.printf( ); // L1 B:\t12 endl a.a=11 a.b=12
    cout << "=======L2 start=======" << endl;
    B_q2 b(1); // L2 B:1 endl, this->b=1+11=12 b.a=11 b.b=12
    cout << "=======L3 start=======" << endl;
    C_q2 c(2); A_q2 *pa = &b; // L3 (a=2) C:2 endl //c.a=2, pa->b
    cout << "=======L4 start=======" << endl;
    pa->printf( ); C_q2 *pc; // L4 A:\t11 endl 
    cout << "=======L5 start=======" << endl;
    if ( pc = dynamic_cast<C_q2*>(&b) ) pc->printf( ); // L5 no output(pc->b? no)
}

void test3(){
    unsigned short a[2]; unsigned char b[2]; int c; 
    fstream input; 
    input.open("oop_2020.txt", ios::in|ios::binary ); input.seekg(7, ios::beg); 
    cout << "======L1 start======" << endl;
    cout << input.tellg() << endl; // L1 
    input.read(reinterpret_cast<char*>(&a[0]), sizeof(unsigned short));
    cout << "======L2 start======" << endl; 
    cout << input.tellg() << endl; input.seekg(-8, ios::cur); // L2 
    input.read(reinterpret_cast<char*>(&b[0]), sizeof(unsigned char)); 
    cout << "======L3 start======" << endl;
    cout << input.tellg() << endl; input.seekg(-7, ios::end); // L3 
    input.read(reinterpret_cast<char*>(&c), sizeof(int)); 
    cout << "======L4 start======" << endl;
    cout << input.tellg() << endl; input.seekg(-3, ios::cur); // L4 
    input.read(reinterpret_cast<char*>(&a[1]), sizeof(a[0])); // no error 
    cout << "======L5 start======" << endl;
    cout << input.tellg() << endl; input.seekg(-6, ios::end); // L5 
    input.read(reinterpret_cast<char*>(&b[1]), sizeof(unsigned char)); 
    cout << "a[0]: " << hex << (int)a[0] << endl;
    cout << "a[1]: " << hex << (int)a[1] << endl;
    cout << "b[1]: " << hex << (int)b[1] << endl;
    cout << "c: " << hex << (int)c << endl;
    cout << "b[0]: " << dec << (int)b[0] << endl;
}

template<typename T>
class Node {
public:
    Node(T element) {
        this->element = element;
        next = 0;//少這行
    }
    Node() {
        element = 0;//不知道這行要不要
        next = 0;
    }
    T element;
    Node<T>* next;
};

template<typename T> //原本是TypeName
class LinkedList { //少了:public Node?
public://少了public:
    Node<T>* tail;//少了宣告tail//應該不能用
    Node<T>* head; //少了宣告head//應該不能用
    LinkedList() {
        tail = 0;
        head = 0;
    }
    void addLast(T element) { //少了 {
        if (tail == 0) { //本來是=
            head = new Node<T>(element);
            tail = head;//少這行
        }//原本有;
        else {//少了{
            tail->next = new Node<T>(element);//少了<T> 
            tail = tail->next;//原本=0 
        }//少了}
    } // end addLast 
    void printList() {
        Node<T>* current = head;
        while (current) {
            cout << current->element << " ";
            current = current->next;
        }
        cout << endl;
    }
};


void test4() {
    LinkedList<int> a;
    LinkedList<double> b;
    a.addLast(1);
    a.addLast(2);
    a.printList();
    b.addLast(1.5);
    b.addLast(2.5);
    b.printList();
}

class A_q7 { 
    public: 
    static int c; 
    int x; 
    A_q7( ) { ++c; x =c; } 
    A_q7 &operator=(const A_q7 &a) { ++c; x = a.x; cout << "A=:" <<x << endl; 
        return *this; 
    } 
    A_q7 &operator+(const A_q7 &a) { ++c; x = x + a.x; cout << "A+:" << x << endl; 
        return *this; 
    } 
 }; 
 class B_q7: public A_q7 { public: B_q7( ) { ++c; x =c; } 
    B_q7 &operator=(const B_q7 &b) { ++c; x = b.x; cout << "B=:" << x << endl; 
        return *this; 
    } 
    B_q7 operator+(const B_q7 &a) { ++c; B_q7 b; b.x = x + a.x; cout << "B+:" << b.x << endl; 
        return b; // b is a new object. 
    } 
 }; 
 int A_q7::c = 0; 

void test7(){
    A_q7 a, d; B_q7 b, c; A_q7 e; //a.x=1, d.x=2, b.x=4, c.x=6, e.x=7 
      cout << "======L1 start======" << endl;
    cout << "A::c:" << A_q7::c << endl; // L1  //7
      cout << "======L2 start======" << endl;
    (a+d) = e; // L2 //A+:3 endl A=:7(c=9, a.x=7)
      cout << "======L3 start======" << endl;
    b = c + c; // L3 //B+:12 endl B=:12(c=13, b.x=12)
      cout << "======L4 start======" << endl;
    cout << "A::c:" << A_q7::c << endl; // L4 13
      cout << "======L5 start======" << endl; 
    a = a + b; //L5 //A+:19 endl A=:19 (c=15)
}

class Node_q8{
    Node_q8* lchild = 0;
    Node_q8* rchild = 0;
    int element;
    Node_q8(){
        element = 0;
        lchild = 0;
        rchild = 0;
    }
    Node_q8(int x){
        element = x;
        lchild = 0;
        rchild = 0;
    }
};

class Binarytree{
    public:
    Binarytree(){
        root = 0;
    }
    Node_q8* root;
};

void test8(){  
}

class X_q9 { 
 public: 
    int a; 
    X_q9( ) { a = 0; }
    X_q9( int b) { a = b; cout << "cX" << endl;} 
    X_q9( const X_q9 &x ) { a = x.a; cout << "copyX:" << a << endl; } 
}; 
class Y_q9: public X_q9 { 
public: 
    Y_q9( int b ): X_q9(b+1) { cout << "cY:" << a << endl;} 
    Y_q9( const X_q9 &x ) { a = x.a; cout << "copyY:" << a << endl; } 
}; 
class Z_q9 : public X_q9 { 
 public: 
    Z_q9( int b ): X_q9( b+2 ) { cout << "cZ" << endl;} 
    ~Z_q9( ) { cout << "dZ:" << a << endl;} 
}; 

void test9(){
    cout << "====start L1====" << endl;
    Z_q9 z(3); // L1 //(z.a=5 z.b=3) cX endl cZ
    cout << "====start L2====" << endl;
    Y_q9 y = *( new Z_q9(5) ); // L2 //cX endl cZ endl copyY:7 endl dZ:7 endl //problem //false
    cout << "====start L3====" << endl; 
    X_q9 x = z; // L3 cX endl //false // deep copy, copyX:5
    cout << "====start L4====" << endl;
    x = z; // L4 copyX:5 endl //false //shallow copy, no output
    cout << "====start L5====" << endl;
    new Z_q9(1); // L5 cX endl cZ endl dZ:3 endl//false
    cout << "====end L5====" << endl;//dZ:5 endl
}

template<typename T>
void Swap(T &a, T &b){
    T temp = a;
    a = b;
    b = temp;
}
    
void test10(){
    int a = 1, b=2;
    Swap(a,b);
    cout << a << " " << b << endl;
}

int main(){
    //test1_1();
    //test1_2();
    //test2();
    //test3();
    //test4();
    //test7();
    //test8();
    //test9();
    test10();
    return 0;
}