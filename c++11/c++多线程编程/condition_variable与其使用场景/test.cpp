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
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}

void consumer() {
    while (1) {
        std::unique_lock<std::mutex> lock(mut);
        // 1. 消费者：先上锁
        // 2. 调用 wait：
        // - 条件不满足：释放锁 → 睡觉
        // - 条件满足：不释放锁，直接返回往下跑
        // 3. 被唤醒后：抢锁 → 再判条件。
        cv.wait(lock, []() {return !q.empty();});
        //1. 线程没有休眠（刚进 wait）：只要 lambda 为 true，直接返回，不需要 notify。
        //2. 线程已经休眠在 wait 里面：先要被唤醒（notify_one / 虚假唤醒），唤醒之后还要求 lambda 为 true，wait 才返回。

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