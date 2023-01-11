#include <iostream>
#include <queue>
using namespace std;

int main(){
    priority_queue <int> pq;   //由大排到小
    priority_queue<int, vector<int>, greater<int> > pq_max; //由小排到大
    /*pq.push(5131);
    pq.push(31);
    pq.push(255);
    pq.push(51);*/
    pq_max.push(5131);
    pq_max.push(31);
    pq_max.push(255);
    pq_max.push(51);
    cout << "pq.size()" << pq_max.size() << " ";
    cout << endl;
    vector <int> v;
    for(int i = 0 ; i < 4; i++){
       v.push_back(pq_max.top()); pq_max.pop();
    }
    for(int i = 0 ; i < 4 ; i++){
        cout << v[i] << " ";
    }
    return 0;
}