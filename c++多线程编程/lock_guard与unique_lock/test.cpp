#include<iostream>
#include<thread>
#include<chrono>
#include<mutex>

int data1 = 0;
std::timed_mutex mut1;//timed_mutex时间互斥锁
void func1() {
    for (int i = 0;i < 2;i++) {
        //std::unique_lock <std::timed_mutex> ul(mut1)是默认构造时加锁的状态
        //std::unique_lock <std::timed_mutex> ul(mut1,std::defer_lock)是默认构造时不加锁的状态,defer为"延迟"的意思
        //std::unique_lock <std::timed_mutex> ul(mut1, std::adopt_lock)是强调加锁的状态
        //std::unique_lock <std::timed_mutex> ul(mut1,std::try_to_lock)是指尝试加锁。如果可以加锁那就成功，否则就不成功
        std::unique_lock <std::timed_mutex> ul(mut1, std::defer_lock);
        //ul.try_lock_for(std::chrono::seconds(2))为尝试等待2s去拿到data1的使用权，如果拿到了就锁，拿不到就不锁
        if (ul.try_lock_for(std::chrono::seconds(2))) {
            std::this_thread::sleep_for(std::chrono::seconds(3));
            data1++;
        }
    }
    return;
}

int data2 = 0;
std::mutex mut2;//timed_mutex时间互斥锁
void func2() {
    for (int i = 0;i < 1000000;i++) {
        // std::lock_guard<std::timed_mutex>lg(mut,std::adopt_lock)是默认构造时不加锁的状态
        std::lock_guard<std::mutex>lg(mut2);//默认构造时加锁状态
        data2++;
    }
    return;
}
//unique_lock和lock_guard在析构时都会自动解锁
int main() {
    std::thread t1(func1);
    std::thread t2(func1);
    t1.join();
    t2.join();

    std::cout << data1 << std::endl;

    std::thread t3(func2);
    std::thread t4(func2);
    t3.join();
    t4.join();

    std::cout << data2 << std::endl;
}