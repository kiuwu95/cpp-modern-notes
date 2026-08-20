#include<iostream>
#include<memory>
#include<string>
#include<utility>
using namespace std;

template <typename T>
shared_ptr<T> make_share_array(size_t size) {
    // 返回匿名对象
    return shared_ptr<T>(new T[size], default_delete<T[]>());
}

int main() {
    //shared_ptr初始化
    shared_ptr<string>ptr1 = make_shared<string>("114514");
    shared_ptr<string>ptr2(new string("Hearts of Iron IV"));
    cout << *ptr1 << endl << *ptr2 << endl;
    //拷贝构造
    shared_ptr<string>ptr3 = ptr1;
    shared_ptr<string>ptr4(ptr2);
    cout << *ptr3 << endl << *ptr4 << endl;
    //reset构造
    ptr1.reset(new string("???"));
    ptr2.reset();
    cout << *ptr1 << endl;

    //指定共享指针的删除器
    shared_ptr<int>ptr5(new int(1), [](int* p) {delete p;});//也可指定普通函数
    //在C++11中使用shared_ptr管理动态数组时，需要指定删除器，因为std::shared_ptr的默认删除器不支持数组对象
    shared_ptr<int>ptr6(new int[5], [](int* p) {delete[]p;});
    //在删除数组内存时，除了自己编写删除器，也可以使用C++提供的std::default_delete<T>()函数作为删除器，这个函数内部的删除功能也是通过调用delete来实现的
    shared_ptr<int>ptr7(new int[5], default_delete<int[]>());
    //另外，我们还可以自己封装一个make_shared_array方法来让shared_ptr支持数组
    shared_ptr<int> ptr8 = make_share_array<int>(10);
    cout << ptr8.use_count() << endl;
}