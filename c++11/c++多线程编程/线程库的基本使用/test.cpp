#include<iostream>
#include<thread>
#include<string>
void print(std::string str) {
    std::cout << str << std::endl;
    return;//加return表进程结束
}
int main() {
    //std::thread 进程名字(函数名，函数变量1，函数变量2，...)
    std::thread t1(print, "Hello,world!");
    if (t1.joinable()) {//joinable是一个bool值类型，表示该进程是否可以join
        t1.join();//join表示主进程等待t1进程（子进程）运行结束完时再继续运行
    }
    t1.detach();//detach表示t1进程（子进程）与主进程分离，各运行各的，如果主进程结束而子进程还没有结束则子进程也要被迫结束
}