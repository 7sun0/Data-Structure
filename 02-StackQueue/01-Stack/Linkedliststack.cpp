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