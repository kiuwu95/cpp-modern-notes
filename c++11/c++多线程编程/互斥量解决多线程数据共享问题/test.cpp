#include<iostream>
#include<thread>
#include<mutex>

int a = 0;
static std::mutex m;
void plus() {
    for (int i = 0;i < 1000000;i++) {
        //加入互斥锁，解决多线程数据共享问题
        m.lock();//加锁
        a++;
        m.unlock();//解锁
    }
}

int main() {
    std::thread t1(plus);//t1开始运行
    std::thread t2(plus);//t2开始运行
    t1.join();//主线程等待t1运行结束，此时t1与t2同时运行
    t2.join();//主线程等待t2运行结束，此时t1已经结束，而t2仍在运行
    std::cout << a << std::endl;
}