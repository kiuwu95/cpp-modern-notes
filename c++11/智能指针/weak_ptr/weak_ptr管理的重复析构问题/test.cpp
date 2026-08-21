#include<iostream>
#include<memory>
using namespace std;

class test :public enable_shared_from_this<test> {
public:
    shared_ptr<test> get_ptr() {
        //return shared_ptr<test>(this)错误,也会导致重复析构,必须继承enable_shared_from_this<test>然后使用shared_from_this()。
        //原理：在构造对于test类的共享指针的同时，由于继承了enable_shared_from_this<test>，test在构造中会产生一个weak_ptr去监测新产生的shared_ptr,
        //weak_ptr会通过weak_ptr.lock()返回检测的对象从而避免重复析构
        return shared_ptr<test>(shared_from_this());
    }
};

class B;
class A {
public:
    shared_ptr<B>next;
    ~A() {
        cout << "A析构函数的调用" << endl;
    }
};
class B {
public:
    //shared_ptr<A>next错误，会导致主程序结束后A和B的指针数量始终为1从而导致内存泄漏，必须使用weak_ptr，因为weak_ptr不会使对象的指针数量+1。
    weak_ptr<A>next;
    ~B() {
        cout << "B析构函数的调用" << endl;
    }
};

int main() {
    //关于在同一原始地址初始化多个智能指针对象的问题
    int* p = new int;
    shared_ptr<int>ptr1(p);
    //shared_ptr<int>ptr2(p)错误，会导致重复析构，两个指针指针的use_count()的值都为1
    shared_ptr<int>ptr2(ptr1);

    //关于返回管理this的智能指针对象问题
    shared_ptr<test>ptr3(new test);
    shared_ptr<test>ptr4 = ptr3->get_ptr();

    //循环引用问题
    shared_ptr<A>Aptr(new A);
    shared_ptr<B>Bptr(new B);
    cout << "Aptr：" << Aptr.use_count() << endl;
    cout << "Bptr：" << Bptr.use_count() << endl;
    Aptr->next = Bptr;
    Bptr->next = Aptr;
    cout << "Aptr：" << Aptr.use_count() << endl;
    cout << "Bptr：" << Bptr.use_count() << endl;
}