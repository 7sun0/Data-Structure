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

// 出栈：新增返回出栈元素，功能更完整
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