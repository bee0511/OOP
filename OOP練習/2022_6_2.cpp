#include <iostream>
#include <cmath>
#include <vector>
#include <ctime>
using namespace std;

void test1_a(){
    cout << "input n: ";
    int n;
    double ans = 0;
    cin >> n;
    for(double i = 1 ; i <= n ; i++){
        ans+= 1/(i*(i+3));
    }
    cout << "ans: " << ans << endl;
}

void test1_b(){
    cout << "input n: ";
    int n;
    double ans = 0;
    cin >> n;
    for(double i = 1 ; i <= n ; i++){
        ans+= 1/sqrt(i);
    }
    cout << "ans: " << ans << endl;
}

void test1_c(){
    cout << "input n: " ;
    int n;
    double ans = 0, factorial = 1;
    cin >> n;
    for(int i = 1 ; i <= n ; i++){
        for(int j = 1; j <= i ;j++){
            factorial *= j;
        }
        ans += 1/sqrt(factorial);
        factorial = 1;
    }
    cout << "ans: " << ans << endl;
}

void test2(){
    srand((unsigned)time(NULL));
    int n, x;
    cout << "n:"; cin >> n;
    cout << "x:"; cin >> x;
    if(n > x){
        cout << "Error." << endl;
        return ;
    }
    int arr_a[n];
    //vector<int> arr;
    cout << "random array:";
    for(int i = 0 ; i < n ; i++){//get random array
        arr_a[i] = ((rand() % (x-1)) + 1);
        cout << arr_a[i] << " ";
    }
    cout << endl;
    for(int i = 0 ; i < n ;i++){//bubble sort
        for(int j = i+1 ; j < n ; j++){
            if(arr_a[i] > arr_a[j]){
                int temp  = arr_a[i];
                arr_a[i] =arr_a[j];
                arr_a[j] = temp;
            }
        }
    }
    cout << "sorted array:";
    for(int i = 0 ; i < n ; i++){//sorted
        cout << arr_a[i] << " ";
    }
    cout << endl;
    cout << "odd number:";
    for(int i = 0 ; i< n ;i++){//odd number
        if(arr_a[i] % 2 == 1) cout << arr_a[i] << " ";
    }
    cout << endl;
    //vector<int> is_prime;
    int is_prime_a[x+1];
    for(int i = 0 ; i <= x ;i++){
        is_prime_a[i] = 1;
    }
    is_prime_a[0] = 0;
    is_prime_a[1] = 0;
    for(int i = 2 ; i <= x ; i++){//prime table
        if(is_prime_a[i] == 1){
            for(int j = i * 2 ; j <= x ; j+=i){
                is_prime_a[j] = 0;
                //cout << j << "is 0" << endl;
            }
        }
    }
    //for(int i =0 ;i<=x ;i++){
    //    cout << is_prime_a[i] << " ";
    //}
    cout <<"prime number:";
    for(int i = 0 ; i < n ; i++){
        if(is_prime_a[arr_a[i]] == 1) cout << arr_a[i] << " ";
    }
    cout << endl;
}

int main(){
    //test1_a();
    //test1_b();
    //test1_c();
    test2();
}