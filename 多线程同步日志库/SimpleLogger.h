#ifndef SIMPLE_LOGGER_H
#define SIMPLE_LOGGER_H

#include <iostream>
#include <fstream>
#include <mutex>
#include <string>
#include <memory>
#include <ctime>
#include <chrono>
#include <functional>
#include <sstream>
#include <vector>

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

    // 设计过滤等级
    void setLevel(LogLevel lv);

    // 格式化日志主接口，可变参数模板，必须用std::forward完美转发
    template<typename... Args>
    void log(LogLevel level, const std::string& fmt, Args&&... args) {
        // --------------------------
        // 【你在这里完成实现】
        // 1.等级过滤判断
        if (level <= m_filterLevel) {
            return;
        }
        // 2.加锁保护整条日志
        std::unique_lock<std::mutex> lock(m_mtx);
        // 3.格式化消息
        std::string msg = Formatter(fmt, args...);
        // 4.获取时间字符串、等级字符串
        std::string tmstring = getTimeString();
        std::string lvstring = levelToString(level);
        // 5.拼接完整日志行
        std::ostringstream oos;
        oos << tmstring << " " << lvstring << " " << msg;
        // 6.输出到控制台
        std::cout << oos.str() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        // 7.如果文件流有效，则写入文件
        if (m_outFile && m_outFile->is_open()) {
            *m_outFile << oos.str() << std::endl;
        }
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
    const std::string levelToString(LogLevel lv);

    // 获取本地时间字符串，格式 "YYYY‑MM‑DD HH:MM:SS"
    std::string getTimeString();

    //变量转字符串
    template<class T>
    std::string arg_to_string(T&& arg) {
        std::ostringstream oos;
        oos << std::forward<T>(arg);
        return oos.str();
    }

    //格式化函数
    template<class... Args>
    std::string Formatter(const std::string& fmt, Args&&... args) {
        std::vector<std::string> args_vec{
            arg_to_string(std::forward<Args>(args))...
        };
        size_t pos = 0, vec_index = 0;
        std::ostringstream oos;

        size_t cutPos = fmt.find("{}");
        while (cutPos != std::string::npos) {
            oos << fmt.substr(pos, cutPos - pos);

            if (vec_index < args_vec.size()) {
                oos << args_vec[vec_index++];
            }
            else {
                oos << "{}";
            }
            cutPos += 2;
            pos = cutPos;

            cutPos = fmt.find("{}", cutPos);
        }
        oos << fmt.substr(pos);

        return oos.str();
    }

private:
    std::mutex m_mtx;                     // 互斥锁，保护全部IO操作
    LogLevel m_filterLevel;               // 过滤等级
    std::shared_ptr<std::ofstream> m_outFile; // 文件输出流智能指针
};

#endif //SIMPLE_LOGGER_H
