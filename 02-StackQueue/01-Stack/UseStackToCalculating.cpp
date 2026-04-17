#include <iostream>
#include <stack>
#include <string>
using namespace std;

//排符号优先级，但是我觉得也可以把()的优先级都定义为0，这样也可以少掉一些判别步骤
int pri(char c) { return c == '+'||c == '-' ? 1 : 2; }

//计算规则
int calc(int a, int b, char op) {
    if(op == '+') return a+b;
    if(op == '-') return a-b;
    if(op == '*') return a*b;
    return a/b;
}

int main() {
    stack<int> num;
    stack<char> op;
    //s是计算式
    string s; cin >> s;
    int n = s.size(), i = 0;
    while(i < n) {
        //将运算数取出来
        if(isdigit(s[i])) {
            int x = 0;
            while(i < n && isdigit(s[i])) x = x*10 + s[i++]-'0';
            num.push(x);
        }
        //如果是（，则直接入栈
        else if(s[i] == '(') {
            op.push(s[i++]);
        }
        //碰到），一直计算到（ ，如果前面把（）的优先级定义为0则可以不需要这个else if分支
        else if(s[i] == ')') {
            while(op.top() != '(') {
                int b = num.top(); num.pop();
                int a = num.top(); num.pop();
                num.push(calc(a,b,op.top())); op.pop();
            }
            op.pop(); i++;
        }
        //计算过程（如果前面把（）的优先级定义为0则可以在while循环中少一个判断，但是需要注意这样会多产生一个0入栈，所以我们会需要flag）
        else {
            while(!op.empty() && op.top()!='(' && pri(op.top())>=pri(s[i])) {
                int b = num.top(); num.pop();
                int a = num.top(); num.pop();
                num.push(calc(a,b,op.top())); op.pop();
            }
            op.push(s[i++]);
        }
    }
    //将栈中剩余的取出来
    while(!op.empty()) {
        int b = num.top(); num.pop();
        int a = num.top(); num.pop();
        num.push(calc(a,b,op.top())); op.pop();
    }
    cout << num.top();
    return 0;
}