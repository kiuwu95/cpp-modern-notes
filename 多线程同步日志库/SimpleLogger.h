#ifndef SIMPLE_LOGGER_H
#define SIMPLE_LOGGER_H

#include <iostream>
#include <fstream>
#include <mutex>
#include <string>
#include <memory>
#include <ctime>
#include <chrono>
#include <string>

// 日志等级
enum class LogLevel
{
    DEBUG,
    INFO,
    WARN,
    ERROR
};

class Logger
{
public:
    // 获取全局单例实例
    static Logger& getInstance();

    // 设置日志文件路径；传入空字符串关闭文件输出
    void setLogFile(const std::string& filePath);

    // 格式化日志主接口，可变参数模板，必须用std::forward完美转发
    template<typename... Args>
    void log(LogLevel level, const char* fmt, Args&&... args) {
        // --------------------------
        // 【你在这里完成实现】
        // 1.等级过滤判断
        if (level < m_filterLevel) {
            return;
        }
        // 2.加锁保护整条日志
        std::unique_lock<std::mutex> lock(m_mtx);
        // 3.snprintf格式化消息

        // 4.获取时间字符串、等级字符串
        std::string tmstring = getTimeString();
        const char* lvstring = levelToString(level);
        // 5.拼接完整日志行
        // 6.输出到控制台
        // 7.如果文件流有效，则写入文件
        // --------------------------
    }

    // 析构：RAII，必须flush缓冲区，关闭文件流
    ~Logger();

    // 删除拷贝构造、拷贝赋值，禁止复制日志对象
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

private:
    // 私有构造函数，单例
    Logger();

    // 将LogLevel转为字符串，例如 LogLevel::INFO → "INFO"
    const char* levelToString(LogLevel lv);

    // 获取本地时间字符串，格式 "YYYY‑MM‑DD HH:MM:SS"
    std::string getTimeString();

private:
    std::mutex m_mtx;                     // 互斥锁，保护全部IO操作
    LogLevel m_filterLevel;               // 过滤等级
    std::shared_ptr<std::ofstream> m_outFile; // 文件输出流智能指针
};

#endif //SIMPLE_LOGGER_H
