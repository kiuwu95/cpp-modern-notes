#include<iostream>
#include<thread>
#include<queue>
#include<functional>
#include<chrono>
#include<mutex>
#include<condition_variable>
#include<vector>

class ThreadPool {
public:
    ThreadPool(int thread_num) {
        // for循环用于批量创建指定数量的工作线程
        // 循环结束后构造函数返回，但每个线程已经在自己的while(1)中独立运行
        // 线程的生命周期与创建它的for循环无关
        for (int i = 0;i < thread_num;i++) {
            // emplace_back直接在vector内部构造std::thread对象
            // lambda是std::thread构造函数的参数（可调用对象）
            // 不是把lambda添加到vector，而是用lambda构造thread对象
            threads.emplace_back([this] {
                while (1) {
                    std::unique_lock<std::mutex>lock(mut);
                    // cv.wait在等待时会释放锁，被唤醒后重新获取锁
                    // 谓词返回true时继续执行，否则继续等待
                    cv.wait(lock, [this] {return end || !tasks.empty();});

                    // 如果线程池要关闭且任务队列为空，线程退出
                    if (end && tasks.empty())return;

                    // 从队列取出任务
                    std::function<void()>task = std::move(tasks.front());
                    tasks.pop();
                    lock.unlock();  // 执行任务前释放锁，避免长时间占用
                    task();         // 执行任务
                }
                });
        }
    }
    ~ThreadPool() {
        {
            // 加锁保护共享变量end，防止数据竞争
            // 工作线程在cv.wait谓词中读end，主线程这里写end
            // 不加锁会导致未定义行为，加锁保证内存可见性
            std::unique_lock<std::mutex>lock(mut);
            end = true;  // 通知所有线程准备退出
        }

        // 唤醒所有等待的线程，让它们检查end标志并退出
        cv.notify_all();
        // 必须join所有线程：
        // 1. std::thread析构时如果线程还在运行会terminate崩溃
        // 2. join等待线程安全退出，回收系统资源
        // 3. 确保线程不再访问this（线程池对象），对象才能安全销毁
        // 不能用detach，因为分离的线程可能访问已销毁的对象导致悬空指针
        for (auto& it : threads) {
            it.join();
        }
    }

    template<typename F, class... Args>
    void AddTask(F&& func, Args&& ...args) {
        // 支持添加各种可调用对象：
        // 普通函数、lambda、成员函数（需传对象指针）、函数对象
        // 带返回值的函数也可以，但返回值会被忽略
        // 注意：引用参数必须用std::ref包装，否则std::bind默认拷贝参数会编译错误
        // 注意：指针参数要确保在任务执行期间有效，避免悬空指针
        std::function<void()>task = std::bind(std::forward<F>(func), std::forward<Args>(args)...);
        {
            std::unique_lock<std::mutex>lock(mut);
            tasks.emplace(std::move(task));
            cv.notify_one();  // 在锁内通知更安全，避免丢失唤醒
        }
    }

private:
    std::vector<std::thread>threads;          // 工作线程容器
    std::queue<std::function<void()>>tasks;   // 任务队列
    std::mutex mut;                           // 互斥锁，保护共享数据
    std::condition_variable cv;               // 条件变量，线程间通信
    bool end = false;                         // 线程池关闭标志
};

int main() {
    ThreadPool tp(2);//双线程
    for (int i = 0;i < 10;i++) {
        tp.AddTask([i] {
            std::cout << "Task " << i << " is running." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
            std::cout << "Task " << i << " is ending." << std::endl;
            });
    }
}