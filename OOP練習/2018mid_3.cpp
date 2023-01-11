#include <iostream>
#include <vector>
using namespace std;

int main() {
    int numberofcase;
    vector<int> a;
    vector<bool> light;
    cin >> numberofcase;
    for(int i = 0 ; i < numberofcase ; i++){
        int n, m, c, con = 0, con_max = -1; // con stands for power consumption
        bool blown_flag = false;
        cin >> n >> m >> c;
        a.clear();
        light.clear();
        light.resize(n, 0);
        for(int j = 0 ; j < n ; j++){
            int temp;
            cin >> temp;
            a.push_back(temp);
        }
        for(int j = 0 ; j < m ; j++){
            int temp;
            cin >> temp;
            if(light[temp - 1] == 0){// if the bulb is not lightened
                con += a[temp - 1];
                light[temp - 1] = true;
                if(con_max < con){
                    con_max = con;
                }
                if(con_max >= c){
                    cout << "Fuse was blown." << endl;
                    blown_flag = true;
                    break;
                }
            }
            else{
                con -= a[temp - 1];
                light[temp - 1] = false;
            }
        }
        if(blown_flag == false){
            cout << "Fuse was not blown." << endl;
            cout << "Maximal power consumption was " << con_max << " amperes." << endl;
        }
    }
    return 0;
}