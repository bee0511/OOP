#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <stack>
using namespace std;

typedef long long LL;
const int SIZE = 1010;
char str[SIZE];
stack<char> OPERATOR;  // 操作符
stack<LL> OPERAND;     // 操作數

inline int get_priority(char ch) {
    switch (ch) {
    case '(':
        return 0;
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case ')':
        return 3;
    }
}

inline LL calc() {
    LL b = OPERAND.top(); OPERAND.pop();
    LL a = OPERAND.top(); OPERAND.pop();
    char ch = OPERATOR.top(); OPERATOR.pop();

    switch (ch) {
    case '+':
        return a+b;
    case '-':
        return a-b;
    case '*':
        return a*b;
    case '/':
        return a/b;
    }
}

int main() {
    cin >> str;
    int priority_top, priority_cur;
    LL number;
    int i = 0, len = strlen(str)-1;
    while (i < len) {
        if (isdigit(str[i])) {
        	// 如果是數字
            number = 0;
            while (i < len && isdigit(str[i])) {
            	// 讀全數字
                number = number * 10 + (str[i] - '0');
                i++;
            }
            OPERAND.push(number);
        } else {
            if (OPERATOR.empty()) {
                OPERATOR.push(str[i]);
                i++;
                continue;
            }
            priority_top = get_priority(OPERATOR.top());
            priority_cur = get_priority(str[i]);
            if (priority_cur == 0) {
            	// 如果是左括號 (
                OPERATOR.push(str[i]);
                i++;
            } else if (priority_cur == 3) {
            	// 如果是右括號 )，計算到第一個左括號 ( 內的表達式的值
                while (OPERATOR.top() != '(') {
                    number=calc();
                    OPERAND.push(number);
                }
                // 彈出右括號 )
                OPERATOR.pop();
                i++;
            } else {
                while (!OPERATOR.empty() && priority_cur <= priority_top) {
                	// 如果還有操作符，並且當前符號的優先級較低
					// 那麼可以先計算棧裏的數
                    number=calc();
                    OPERAND.push(number);
                    // 如果還有操作符，獲取其優先級
                    if (!OPERATOR.empty()) priority_top = get_priority(OPERATOR.top());
                }
                OPERATOR.push(str[i]);
                i++;
            }
        }
    }

    while (!OPERATOR.empty()) {
        number = calc();
        OPERAND.push(number);
    }

    cout << OPERAND.top() << endl;

    return 0;
}