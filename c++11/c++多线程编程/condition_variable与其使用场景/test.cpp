#include<iostream>
#include<thread>
#include<condition_variable>
#include<queue>
#include<chrono>
//消费者与生产者模型
std::condition_variable cv;
static std::mutex mut;
std::queue<int> q;

void producer() {
    for (int i = 0;i < 10;i++) {
        {
            std::unique_lock<std::mutex> lock(mut);
            q.push(i);
            cv.notify_one();
            std::cout << "producer " << i << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

void consumer() {
    while (1) {
        std::unique_lock<std::mutex> lock(mut);
        cv.wait(lock, []() {return !q.empty();});

        std::cout << "consumer " << q.front() << std::endl;
        q.pop();
    }
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();
}