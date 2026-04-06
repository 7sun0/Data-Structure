#include <iostream>
using namespace std;

//创建节点
struct node{
    char element;
    node* next;
};

//创建链表
node* creat(){
    char n;
    node* head=NULL;
    node* tail=NULL;
    //换行停止链表的创建
    while(cin.get(n)&&n!='\n'){
        node* p=new node;
        p->element=n;
        p->next=NULL;
        if(head==NULL){
            head=p;
        }
        else tail->next=p;
        tail=p;
    }
    return head;
}

//反转，我们这里是将1->2->3......->n->NULL变为NULL<-1<-2<-3......<-n(->NULL)，我们从1开始向后改变箭头的方向
node* reverse(node* head){
    if(head==NULL)return head;
    node* cur=head;
    node* next=cur->next;
    node* prev=NULL;
    while(cur!=NULL){
        next=cur->next;
        cur->next=prev;
        prev=cur;
        cur=next;
    }
    //cur此时为NULL，需要返回prev为头部。
    return prev;
}

int main() {
    node* head=creat();
    node* newhead=reverse(head);
    node* cur=newhead;
    //输出反转后的结果
    while(cur!=NULL){
        cout<<cur->element;
        cur=cur->next;
    }
}