栈，其实也是线性表的一种，在我的理解中，栈只是加了**限制**的顺序表，所以同样也可以通过数组和链表来表示（就和顺序表一样）。通过增加限制，可以起到安全的效果，让程序不容易出错。
# 栈是什么
数据集合只涉及在**一端**插入和删除数据，并且满足**后进先出、先进后出**的特性，我们将存储具有这些特性的数据的数据类型叫做栈。它的核心操作有：
- Push（入栈）：将元素插入栈顶，栈顶指针上移，时间复杂度显然是O(1)
- Pop（出栈）：删除栈顶元素，栈顶指针下移（注意判空，避免崩溃），时间复杂度为O(1)
- GetTop（取栈顶）：获取栈顶元素，不删除，时间复杂度为O(1)
- IsEmpty（判空）：判断栈是否为空，时间复杂度为O(1)
- IsFull（判满）：仅顺序栈需要，链栈无满栈限制（除内存溢出），时间复杂度为O(1)
## 用数组实现栈
栈是加了限制的顺序表，将实现顺序表时结构体中的last等价为top（都是最后的**一端**）即可，我们的操作也都是在top端进行的。  
在顺序表中，数据的个数为last+1，同理在栈中数据的个数为top+1（用于判断数组是否越界）
```cpp
#include <iostream>
// 规范命名：最大容量
#define Maxsize 100
using namespace std;

// 顺序栈结构体（顺序表实现栈）
struct SeqStack {
    int data[Maxsize];  // 顺序表存储栈元素
    int top;            // 栈顶指针，-1表示空栈
};

// 重命名指针类型，语义更清晰
typedef SeqStack* Stack;

// 创建空栈
Stack CreateStack() {
    Stack p = new SeqStack;
    p->top = -1;
    return p;
}

// 销毁栈：释放内存，修复内存泄漏
void DelStack(Stack p) {
    if (p != NULL) {
        delete p;
        p = NULL;
    }
}

// 判断栈空：简化逻辑
bool IsEmpty(Stack p) {
    return (p->top == -1);
}

// 判断栈满：独立封装，模块化更强
bool IsFull(Stack p) {
    return (p->top + 1 == Maxsize);
}

// 入栈
void Push(Stack p, int val) {
    if (IsFull(p)) {
        cout << "栈满，无法入栈！" << endl;
        return;
    }
    p->data[++p->top] = val;
}

// 出栈
int Pop(Stack p) {
    if (IsEmpty(p)) {
        cout << "栈空，无法出栈！" << endl;
        return -1;
    }
    return p->data[p->top--];
}

// 获取栈顶元素
int GetTop(Stack p) {
    if (IsEmpty(p)) {
        cout << "栈空，无栈顶元素！" << endl;
        return -1;
    }
    return p->data[p->top];
}

```
关键注意：入栈先移指针（++top），出栈先取元素（top--），避免数组越界。
## 用链表实现栈
用链表实现栈，就不需要注意栈满了。同时栈这种后进元素的排在最前面的特性，和链表的头插法十分相似！（个人感觉）
```cpp
#include <iostream>
#define Maxsize 100
using namespace std;

struct SeqStack {
    int data;
    SeqStack* next;            
};

// 重命名指针类型，语义更清晰
typedef SeqStack* Stack;

// 创建空栈
Stack CreateStack() {
    Stack p=new SeqStack;
    p->next=NULL;
    return p;
}

// 销毁栈：释放内存，修复内存泄漏
void DelStack(Stack p) {
    while(p){
        Stack cur=p;
        p=p->next;
        delete cur;
    }
}

// 判断栈空：简化逻辑
bool IsEmpty(Stack p) {
    return (p->next==NULL);
}

// 入栈
void Push(Stack p, int val) {
    Stack h=new SeqStack;
    h->data=val;
    h->next=p->next;
    p->next=h;
}

// 出栈
int Pop(Stack p) {
    if (IsEmpty(p)) {
        cout << "栈空，无法出栈！" << endl;
        return -1;
    }
    Stack del=p->next;
    int val=del->data;
    p->next=del->next;
    delete del;
    return val;
}

// 获取栈顶元素
int GetTop(Stack p) {
    if (IsEmpty(p)) {
        cout << "栈空，无栈顶元素！" << endl;
        return -1;
    }
    return p->next->data;
}

int main() {
    Stack stk = CreateStack();

    // 测试入栈
    Push(stk, 1);
    Push(stk, 3);

    // 测试取栈顶
    cout << "栈顶元素：" << GetTop(stk) << endl;

    // 测试出栈
    int popVal = Pop(stk);
    cout << "出栈元素：" << popVal << endl;

    // 再次取栈顶
    cout << "栈顶元素：" << GetTop(stk) << endl;

    // 销毁栈，释放内存
    DelStack(stk);
    return 0;
}
```
这里用到了哨兵节点，链栈无需判满，重点是“**头结点不动，仅操作其下一个节点**”，避免内存泄漏。此外我发现相比直接头插法还有个好处，可以避免引用带来的二级指针的不美观，更加简洁。
# 数组实现双栈共享
核心：用一个数组存储两个栈，栈1从左向右生长（top1 = -1），栈2从右向左生长（top2 = Maxsize），共享数组空间。
```cpp
#include <iostream>
#define Maxsize 100
using namespace std;

struct DualStack {
    int data[Maxsize];
    int top1, top2;
    // 初始化：两个栈分别在数组两端
};

// 创建空栈
Stack CreateStack() {
    Stack p = new SeqStack;
    p->top1 = -1;
    p->top2=Maxsize;
    return p;
}

// 判满（两个栈顶相遇即为满）
bool IsFull(DualStack& s) {
    return top1 + 1 == top2;
}

// 入栈：flag=1表示栈1，flag=2表示栈2
void Push(DualStack& s, int x, int flag) {
    if (IsFull(s)) return;
    flag == 1 ? s.data[++s.top1] = x : s.data[--s.top2] = x;
}

// 出栈
int Pop(DualStack& s, int flag) {
    if (flag == 1 && s.top1 == -1) return -1;  // 栈1空
    if (flag == 2 && s.top2 == Maxsize) return -1;  // 栈2空
    return flag == 1 ? s.data[s.top1--] : s.data[s.top2++];
}
```
在原来的基础上改改就行了
# 总结
- 1. 顺序栈与链栈对比
        
  - 顺序栈：优点是操作快（数组随机访问），缺点是固定容量，可能溢出
  - 链栈：优点是容量灵活（无满栈），缺点是操作需遍历指针，效率略低
- 2. 出栈必须先判空，入栈（顺序栈）必须先判满，否则会出现空指针崩溃、数组越界。
- 3. 链栈带头结点 vs 不带头结点：带头结点更简洁，无需处理头指针为空的情况，推荐使用。
- 4. 双栈共享的判满条件：top1 + 1 == top2（唯一判满方式）。
# 栈的应用
## 函数调用栈
操作系统给每个线程分配了一块独立的内存空间，这块内存被组织成“**栈**”这种结构, 用来存储函数调用时的临时变量。每进入一个函数，就会将临时变量作为一个栈帧入栈，当被调用函数执行完成，返回之后，将这个函数对应的栈帧出栈。
## 表达式求值
核心逻辑：用两个栈（数字栈 + 符号栈），结合运算符优先级，处理加减乘除+括号，将中缀表达式与后缀表达式联系起来。  
关键步骤：
1. 遍历表达式，数字压入数字栈，运算符按优先级处理（优先级高直接压栈，低则先计算再压栈）。
2. 遇到左括号 ( 直接压栈，遇到右括号 ) 计算到左括号为止。可以理解为未入栈的（优先级是最高的，但是一入栈后优先级就变成最低的了。
3. 表达式遍历完，计算栈中剩余的运算符，最终数字栈顶即为结果。
```cpp
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
```
## 其他应用
- 括号匹配（判断括号是否成对，如 (()) 合法，(()) 合法）
- 逆序输出（如将数组逆序，入栈后依次出栈）
- 浏览器网页的前进、后退功能