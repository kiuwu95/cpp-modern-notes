#include "SimpleLogger.h"
#include <thread>

void workThread(int threadId) {
    for (int i = 0; i < 30; ++i) {
        Logger::getInstance().log(LogLevel::INFO, "thread={}, count={}", threadId, i);
        Logger::getInstance().log(LogLevel::DEBUG, "thread={} debug info", threadId);
    }
}

int main() {
    auto& logger = Logger::getInstance();

    logger.setLevel(LogLevel::DEBUG);         // 可以改成INFO，观察debug日志被过滤
    logger.setLogFile("E:\\桌面\\编程\\c++新特性\\多线程同步日志库\\log.txt");           // 传入 "" 就关闭文件输出，只打印控制台

    // 启动3个线程并发打印日志
    std::thread t1(workThread, 1);
    std::thread t2(workThread, 2);
    std::thread t3(workThread, 3);

    t1.join();
    t2.join();
    t3.join();

    return 0;
    // main退出，单例Logger析构，触发flush
}
