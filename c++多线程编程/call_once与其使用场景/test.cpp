#include<iostream>
#include<thread>
#include<string>
//once_flag是一个状态标记对象，记录关联函数是否已经执行完毕；必须所有线程共享同一个实例，所以 static。
static std::once_flag once;
class Log* l = nullptr;
//日志类（单例模式）
class Log {
public:
    Log() = default;
    Log(const Log& log) = delete;
    Log& operator=(const Log& log) = delete;

    static Log& get_instance() {
        std::call_once(once, init);//依据 once 标记，保证init()整个程序生命周期只运行一次，多线程并发调用也不会重复执行
        return *l;
    }
    static void init() {
        if (!l)l = new Log;
    }
    void print(const std::string& s) {
        std::cout << s << std::endl;
    }
};

void print_error() {
    Log::get_instance().print("Error!");
}

int main() {
    // 1. 多个线程（t1、t2）同时进入`get_instance()`，同时调用`call_once(once, init)`
    // 2. 只有其中某一个线程能够真正执行 `init()` ；`init()`里面`new Log`创建单例对象。
    // 3. 剩下其他线程：卡在`call_once`内部阻塞等待， 不会执行 init ；等到第一个线程把 init 跑完、once 标记置为 “已完成” 之后，其他线程直接放行，跳过 init。
    //👉 效果：init 函数保证全局只执行一次，多线程环境下安全创建单例，不会 new 出多个 Log 对象。
    std::thread t1(print_error);
    std::thread t2(print_error);
    t1.join();
    t2.join();
}