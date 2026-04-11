#include <iostream>
#define Maxxroom 100
using namespace std;

struct List {
    int data[Maxxroom];
    int last;
};

// 创建空顺序表
List* create() {
    List* Pl = new List;
    Pl->last = -1;
    return Pl;
}

// 尾部添加元素
void add(int n, List* Pl) {
    if (Pl->last + 1 == Maxxroom) {
        cout << "已满！" << endl;
        return;
    } else {
        Pl->data[++Pl->last] = n;
    }
}

// 删除第 pos 个位置的元素（pos从1开始）
void delpost(int pos, List* Pl) {
    if (Pl->last + 1 < pos) {
        cout << "位置不合法！" << endl;
        return;
    } else {
        for (int i = pos; i < Pl->last + 1; i++) {
            Pl->data[i - 1] = Pl->data[i];
        }
        Pl->last--;
    }
}

// 查找值为 num 的元素，返回下标，找不到返回-1
int findnum(int num, List* Pl) {
    for (int i = 0; i < Pl->last + 1; i++) {
        if (Pl->data[i] == num) {
            return i;
        }
    }
    return -1;
}

// 删除第一个值为 num 的元素
void delnum(int num, List* Pl) {
    int i = findnum(num, Pl);
    if (i == -1) {
        cout << "没有该元素！" << endl;
        return;
    }
    for (int j = i + 1; j < Pl->last + 1; j++) {
        Pl->data[j - 1] = Pl->data[j];
    }
    Pl->last--;
}

// 在第 pos 个位置插入元素 num（pos从1开始）
void insert(int pos, int num, List* Pl) {
    if (Pl->last + 2 < pos) {
        cout << "插入位置不合法！" << endl;
        return;
    } else if (Pl->last + 1 == Maxxroom) {
        cout << "表已满！" << endl;
        return;
    }
    for (int i = Pl->last; i >= pos - 1; i--) {
        Pl->data[i + 1] = Pl->data[i];
    }
    Pl->data[pos - 1] = num;
    Pl->last++;
}

// 新增：打印顺序表（方便查看结果）
void print(List* Pl) {
    if (Pl->last == -1) {
        cout << "空表" << endl;
        return;
    }
    for (int i = 0; i <= Pl->last; i++) {
        cout << Pl->data[i] << " ";
    }
    cout << endl;
}

// 主函数测试
int main() {
    // 创建顺序表
    List* L = create();

    // 尾插元素
    add(10, L);
    add(20, L);
    add(30, L);
    add(40, L);
    cout << "尾插后：";
    print(L);

    // 第2个位置插入 15
    insert(2, 15, L);
    cout << "插入15后：";
    print(L);

    // 删除第3个元素
    delpost(3, L);
    cout << "删除第3位后：";
    print(L);

    // 删除值为 20 的元素
    delnum(20, L);
    cout << "删除值20后：";
    print(L);

    // 查找元素
    int pos = findnum(30, L);
    if (pos != -1)
        cout << "元素30的下标：" << pos << endl;
    else
        cout << "未找到30" << endl;

    return 0;
}