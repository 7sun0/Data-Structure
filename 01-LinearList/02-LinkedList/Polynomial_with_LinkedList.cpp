#include <iostream>
using namespace std;
struct Xnode{
    int coef;
    int expon;
    Xnode* next;
};
//attach
void attach(int c,int e,Xnode** rear){
    Xnode* p=new Xnode;
    p->coef=c;
    p->expon=e;
    p->next=NULL;
    (*rear)->next=p;
    (*rear)=p;
}

Xnode* create(){
    int n;
    cin>>n;
    //哨兵
    Xnode* rear=new Xnode;
    Xnode* sentinel=rear;
    while(n--){
        int c,e;
        cin>>c>>e;
        attach(c,e,&rear);
    }
    Xnode*head=sentinel->next;
    delete sentinel;
    return head;
}

void printx(Xnode* head){
    if(head==NULL){
        cout<<"error!"<<endl;
        return;
    }
    else{
        Xnode* cur=head;
        while(cur){
            cout<<cur->coef<<" "<<cur->expon<<endl;
            cur=cur->next;
        }
    }
}

Xnode* add(Xnode* h1,Xnode* h2){
    Xnode* rear=new Xnode;
    Xnode* sentinel=rear;
    Xnode* cur1=h1;
    Xnode* cur2=h2;
    while(cur1&&cur2){
        if(cur1->expon>cur2->expon){
            attach(cur1->coef,cur1->expon,&rear);
            cur1=cur1->next;
        }
        else if(cur1->expon<cur2->expon){
            attach(cur2->coef,cur2->expon,&rear);
            cur2=cur2->next;
        }
        else{
            int sum=cur1->coef+cur2->coef;
            if(sum){
                attach(sum,cur1->expon,&rear);
            }
            cur1=cur1->next;
            cur2=cur2->next;
        }
    }
    while(cur1){
        attach(cur1->coef,cur1->expon,&rear);
        cur1=cur1->next;
    }
    while(cur2){
        attach(cur2->coef,cur2->expon,&rear);
        cur2=cur2->next;
    }
    Xnode* head=sentinel->next;
    delete sentinel;
    return head;
}

int main(){
    Xnode* head1=create();
    Xnode* head2=create();
    Xnode* head3=add(head1,head2);
    printx(head3);
}