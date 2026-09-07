#include<iostream>
#include<thread>
#include<atomic>
#include<mutex>
#include<chrono>

std::mutex mut;
std::atomic<int>val = 0;
void func() {
    for (int i = 0;i < 100000;i++) {
        //不需要使用mutex互斥锁
        val++;
    }
}

int main() {
    std::thread t1(func);
    std::thread t2(func);

    t1.join();
    t2.join();

    std::cout << val << std::endl;

    int get = val.load();//原子写入
    //但感觉直接写val也可以
    std::cout << get << std::endl;
    val.store(114514);//原子读取
    //但感觉直接写val=114514也可以
    std::cout << val << std::endl;
    val++;//自增
}