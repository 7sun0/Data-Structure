 #include <iostream>
 #include <string>
 using namespace std;

 //节点定义
 struct node{
     node* next;
     string name;
 };

 //创造循环链表
 node* create(int n){
     node* head=NULL;
     node* tail=NULL;
     for(int i=1;i<=n;i++){
        //创造一个新的节点，输入节点处一个人的名字
         node* p=new node;
         cin>>p->name;
         p->next=NULL;
         if(head==NULL)head=p;
         else tail->next=p;
         tail=p;
     }
     //最后，将尾节点与头节点连接，形成循环链表
     tail->next=head;
     return head;
 }

 //约瑟夫环消除操作
node* del(int m,node* head){
    node* pre=head;
    //找到头节点的上一个节点：尾节点，之后它将跟随cur节点成为cur节点的前节点
    while(pre->next!=head){
        pre=pre->next;
    }
    node* cur=head;
    //开始计数到第m人
    for(int i=1;i<m;i++){
        pre=pre->next;
        cur=cur->next;
    }
    //第m个节点删除操作，需要用到我们的pre
    pre->next=cur->next;
    free(cur);
    return pre->next;
}

void change(int n,int m,node* head){
    node* newhead=head;
    //约瑟夫环会清除到只剩最后一个人，所以会有n-1次清除操作，当然也可以用while(newhead->next!=newhead)来循环
    for(int i=0;i<n-1;i++){
        newhead=del(m,newhead);
    }
    cout<<newhead->name;
}

 int main(){
    //n是人数 计数到m则会淘汰
     int n,m;
     cin>>n>>m;
     //创建长度为n的循环链表
     node*head=create(n);
     //约瑟夫问题操作链表
     change(n,m,head);
 }