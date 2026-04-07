# 链表
## 什么是链表
前面我们提到了数组是通过一组连续的存储空间来存储一组相同类型的数据，那么链表呢？在我的理解中，链表是和数组**相反**的数据结构，链表和铁链十分相似，每一个节点都相当于铁链中的一个铁环，链表的各个节点所在空间之间并无联系，而是通过如node*next等指针结构来串联两个节点，这也就使得链表之间的各个节点是易于拆散的，正是这种 **“临时链接”** 的结构，让链表在插入、删除时非常灵活。
## 五花八门的链表结构
链表结构不像数组那般严格，我们可以通过不同的连接方式产生出各种各样的链表，我们先来看看最简单的单链表。
### 单链表
单链表一般会包含两部分，即：
- 数据域：存储当前节点信息
- 指针域：指向后继节点
``` cpp
struct node{
    //存储该节点基本信息
    int data;
    //连接下一个节点
    node* next;
};
```
在最后一个节点尾指针tail处，我们一般令**tail->next=NULL**，如此来标志单链表的结束。  
而单链表拼装一般的结构，天然的具备**插入、删除**的优势，这也就是数组不具有的特点。我们都知道，数组在进行插入、删除的操作时，为了保证内存数据的连续性，会进行大量的数据迁移，时间复杂度为**O(n)**，而在链表中，我们结合生活实际如何在铁链中插入一个铁环或是拆掉一个铁环，我们只需要将两个节点之间的链接断开，再把新的节点连在拆开的两头上即可实现插入操作，时间复杂度为**O(1)**，链表的删除操作也是同理，将要删除节点的两头链接断开，再将删除节点左右两边的节点连接起来即可实现删除操作。  
但是，有利就有弊，单链表如果想要访问第k个元素，就远远没有数组高效了，单链表需要从头节点开始通过next的连接层层寻找，一直走到第k层才停下，时间复杂度显然是O(n)，明显弱于数组访问arr[k]（O(1)）的效率呀！
#### 单链表一道有趣的题目：如何实现单向链表的反转
题目很简洁：如何实现单向链表的反转？  
做法具体有多种，个人认为比较容易想到的是头插法反转，因为我们会发现，用头插法创建链表时，是新插入的节点成为新的头节点，而不是我们本能的以为最开始插入的是头节点。根据这个平常做题时的发现，我们运用头插法把原来链表从头到尾的节点依次作为新的头节点，就可以实现反转的功能。
```cpp
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

//反转，我们这里是将1->2->3......->n->NULL变为NULL<-1<-2<-3......<-n，1作为最开始的头节点，n为最后的头节点
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
```

### 循环链表
前面我们提到，单链表的尾指针tail->next==NULL，但是如果让tail->next=head呢？首尾相连，形成一个圆环状的链表结构。  
循环链表的特点在于，
- 可以从任意节点出发，遍历整个链表
- 非常适合处理环状问题，比如经典的**约瑟夫环**问题
*循环链表解决约瑟夫问题*
```cpp
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
```

### 双向链表
单链表是从头到尾，通过后继指针next实现的单向操作，那双向链表呢？顾名思义，有next指向后面的节点地址，也有prev指向前面的节点地址。  
双向链表和单向链表如此相似，特殊之处在哪？个人认为，它践行了空间换时间的思想。在双向链表中，由于每个节点新加入了一个数据node* prev，导致增大了对空间的消耗，那么时间上呢？在单链表的删除操作中，我们需要定位到节点的两头，节点的后端我们知道是next，那前面呢？因此，我们还需要得到节点的前一个节点。而在双向链表中，则直接一步到位，同时知道了prev和next，省去了一部分时间。在插入操作中，也是同理。  
双向链表的优势不只体现在插入删除上，还体现在查询上，如果链表是有序链表，我们需要查找data值为p的节点，我们可以通过p的大小来判断应该从头开始向后遍历还是从尾开始向前遍历。  
双向链表的创建思路如下：
```cpp
struct Node {
    int val;
    Node* prev;
    Node* next;
};
Node* create(int arr[], int n) {
    Node *head = nullptr, *tail = nullptr;
    for (int i = 0; i < n; i++) {
        Node* p = new Node{arr[i], nullptr, nullptr};
        if (!head) head = tail = p;
        else {
            tail->next = p;
            p->prev = tail;
            tail = p;
        }
    }
    return head;
}
```

### 静态链表（静态 = 用数组模拟链表）
它到底是什么？静态链表是用数组 + 下标，模拟出链表的结构。
- 普通链表：Node* next 存内存地址
- 静态链表：int next 存数组下标
因为数组是提前开好的，大小固定，所以叫静态链表，我们可以把这里的数组理解成链表的一堆节点的集合
它的关键点是：
- next = -1 表示没有下一个节点（相当于 NULL）
- head 存第一个节点的下标
- 所有 “指针” 都是int 下标
为了方便复习，贴一个文件，具体的静态链表操作：
```cpp
#include <iostream>
using namespace std;

const int MAXN = 100;

struct Node {
    int data;
    int next;
} SLL[MAXN];

int head = -1;//头节点
int tot = 0;//可用节点（相当于cur）

// 尾插建立链表
void add(int val) {
    SLL[tot].data = val;
    SLL[tot].next = -1;
    if (head == -1) head = tot;
    else {
        int p = head;
        while (SLL[p].next != -1) p = SLL[p].next;
        SLL[p].next = tot;
    }
    tot++;
}

// 遍历
void print() {
    for (int p = head; p != -1; p = SLL[p].next)
        cout << SLL[p].data << " ";
    cout << endl;
}
// 在第 pos 个节点后面插入 val（pos从0开始）
void insert(int pos, int val) {
    // 1. 申请新节点
    SLL[tot].data = val;

    // 2. 找到要插入的位置
    int p = head;
    for (int i = 0; i < pos; ++i) {
        p = SLL[p].next;
    }

    // 3. 核心插入逻辑
    SLL[tot].next = SLL[p].next;
    SLL[p].next = tot;

    tot++;
}
// 删除第 pos 个节点（pos从0开始）
void del(int pos) {
    int p = head;

    // 如果删第一个节点
    if (pos == 0) {
        head = SLL[head].next;
        return;
    }

    // 找到 pos 的前一个节点
    for (int i = 0; i < pos - 1; ++i) {
        p = SLL[p].next;
    }

    // 核心删除逻辑
    int toDel = SLL[p].next;
    SLL[p].next = SLL[toDel].next;
}
int main() {
    add(10);
    add(20);
    add(30);
    print();           // 10 20 30

    insert(1, 25);
    print();           // 10 20 25 30

    del(2);
    print();           // 10 20 30
}
```
