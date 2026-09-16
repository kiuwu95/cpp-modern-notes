#include "SimpleLogger.h"

// 单例获取，实现
Logger& Logger::getInstance() {
    // 【你来实现】静态局部变量单例
}

Logger::Logger() {
    // 【你来实现】构造初始化，默认等级，默认文件流为空
}

Logger::~Logger() {
    // 【你来实现】析构：加锁、flush缓冲区，m_outFile自动析构关闭文件
}

void Logger::setLogFile(const std::string& filePath) {
    // 【你来实现】
    // 如果filePath为空，m_outFile重置，关闭文件输出
    // 不为空则打开文件；打开失败不要崩溃，m_outFile置空，降级仅控制台输出
}

void Logger::setLevel(LogLevel lv) {
    // 【你来实现】设置过滤等级，注意多线程，要不要锁？思考一下
}

const char* Logger::levelToString(LogLevel lv) {
    // 【你来实现】enum转字符串
    switch (lv) {
    case LogLevel::DEBUG:
        return "Debug";
        break;
    case LogLevel::ERROR:
        return "Error";
        break;
    case LogLevel::INFO:
        return "Info";
        break;
    case LogLevel::WARN:
        return "Warn";
        break;
    }
}

std::string Logger::getTimeString() {
    // 【你来实现】获取格式化时间字符串 YYYY‑MM‑DD HH:MM:SS
    std::chrono::
}
