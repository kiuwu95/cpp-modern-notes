#include<iostream>
#include<memory>
using namespace std;

int main() {
    //weak_ptr的初始化
    shared_ptr<int>ptr1 = make_shared<int>(10);
    weak_ptr<int>ptr2(ptr1);
    weak_ptr<int>ptr3 = ptr2;//ptr3->ptr2->ptr1->[内存]

    //lock：weak_ptr所监管的指针所指向的对象
    shared_ptr<int>ptr4 = ptr2.lock();
    //use_count：weak_ptr所监管的指针数量
    cout << ptr2.use_count() << endl;
    //清空对象，使其不检测任何资源
    ptr2.reset();
    //expired：ture代表资源已被清空，flase则代表没有被清空
    cout << ptr2.expired() << endl;
}