#include<iostream>
#include<thread>
#include<functional>
#include<memory>

void func(int& a) {
    a++;
    return;
}
void func1(int* a) {
    std::cout << *a << std::endl;
}
class test {
public:
    void print() {
        std::cout << "Hello,world!" << std::endl;
        return;
    }
};

int main() {
    int a = 1;
    std::thread t1(func, std::ref(a));//不加ref会被模板参数推导会变成值拷贝，而不是引用
    t1.join();
    std::cout << a << std::endl;
    //类与线程
    test test1;
    std::thread t2(&test::print, &test1);
    t2.join();
    //+智能指针
    std::shared_ptr<test>ptr(new test);
    std::thread t3(&test::print, ptr);
    t3.join();
    ptr.reset();
    //普通指针
    int* ptr1 = new int(1);
    std::thread t4(func1, ptr1);
    //不能在这行写delete ptr1;，否则会出现未定义行为
    t4.join();
    delete ptr1;
}