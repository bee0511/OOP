#include <iostream>
#include <string>
using namespace std;


void foo( ) throw( )  {
     int a = 10.0;
     return;
}

void h() {
    //throw(28);
}
void k() {
    h(); 
    cout << "here" << endl;
    throw(string("call k()"));
};


void g() {
    try {
        k( );
    }
    catch(int num) {
        cout << "Num:" << num << endl;
    }
    catch( string &e ) {
        cout << "Error:" << e << endl;
    }
}

void g_1(){
    throw(string("abc"));
}
int main( )
{
   /* try {
        g( );
    }
    catch( int e ) {
        cout << "Error:" << e << endl;
    }
    g();*/
    

try {
        g_1( );
    }
    catch(string e ) {
        cout << "Error:" << e << endl;
    }
    return 0;
}
