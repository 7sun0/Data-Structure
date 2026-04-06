#include <iostream>
using namespace std;
int main(){
    // 初始，创建一个大小为3的数组
    int* arr=new int[3];
    //记录容量
    int room=3;
    //记录输入数据的个数
    int count=0;
    int num;
    while(cin>>num){
        arr[count++]=num;
        //如果输入数据个数与容量相等，需要扩容！
        if(count==room){
            //新容量为原来的两倍（一般情况下）
            room*=2;
            int* new_arr=new int[room];
            //将原来的数据复制到新数组上
            for(int i=0;i<count;i++){
                new_arr[i]=arr[i];
            }
            //释放空间
            delete[]arr;
            //重新命名，利于进入下一次循环
            arr=new_arr;
        }
    }
    //检测结果
    for(int i=0;i<count;i++){
        cout<<arr[i]<<" ";
    }
    //释放内存
    delete[] arr;
    return 0;
}