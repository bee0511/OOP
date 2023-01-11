#include <iostream>
#include <string>
#include <sstream>
using namespace std;
int main(){
	stringstream ss;
	ss << 2.7263;
	string s = ss.str();
	cout << s << endl;
	getline (cin , s);
	cout << s << endl;
  string s1("good");
  s1.append(" Programming");
  cout << s1 <<endl;
  string s2("Good123456789");
  s2.replace(8,10,"here");
  s2.insert(2,5,'a');
  cout << s2 << endl;
  cout << s2.find('a') << endl;
  return 0;
}