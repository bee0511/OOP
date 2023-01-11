#include <iostream>
#include <stack>
#include <bits/stdc++.h>
using namespace std;
/* Add whatever you want. */
void bottomtotop(stack<long long> s){
    if(s.empty()){
        return;
    }
    long long x=s.top();
    s.pop();
    bottomtotop(s);
    cout<<x<<" ";
    s.push(x);
}
int main() {
    
    int _numOfline;
    int action;
    long long num=0;
    stack<long long> _actnum;
    cin>>_numOfline;
    if(_numOfline!=0){
        while(_numOfline>0){
          cin>>action;
            if(action==0){
                cin>>num;
                //cout << num << endl;
                _actnum.push(num);
            }
            else if(action==1){
                if(!_actnum.empty()){
                    _actnum.pop();        
                }
                else{ cout<<"Not legal"<<endl;}
                
            }
            else if(action==2){
                if(!_actnum.empty()){
                        //cout<<_actnum.size()<<endl;
                        cout<<_actnum.top()<<endl;
                        //bottomtotop(_actnum);
                }
                else{
                    cout<<"Not legal"<<endl;
                    }
                
            }
            else if(action==3){
                if(!_actnum.empty()){
                    cout<<_actnum.size()<<endl;
                    //cout<<_actnum.top()<<endl;
                    //bottomtotop(_actnum);
                }
                else{
                    cout<<"No data"<<endl;   
                }
            }
        --_numOfline;
      }
        if(!_actnum.empty()){
            bottomtotop(_actnum);  
        }
        else{cout<<"No data"<<endl; }  
        
        }
  
    
    return 0;
}