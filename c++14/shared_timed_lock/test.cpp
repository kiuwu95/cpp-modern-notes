//读写锁适用于多读且写数据并存的情况中
#include<iostream>
#include<shared_mutex>
#include<thread>
#include<string>
#include<sstream>
#include<chrono>
#include<vector>
using namespace std::chrono_literals;
//当一个读数据的线程拿到锁时，所有读数据的线程都可以访问该数据，所有写数据的线程都不能修改该数据
//当一个写数据的线程拿到锁时，只有该线程线程可以修改该数据，其他线程一律不可以访问或修改该数据
class SharedData {
private:
    mutable std::shared_timed_mutex stm;//读写锁
    std::string m_data;//共享可读数据
public:
    //读操作
    void read() const {
        std::shared_lock<std::shared_timed_mutex> lock(stm);
        std::stringstream ss;

        ss << "reader正在读取..." << std::endl;
        std::this_thread::sleep_for(500ms);
        ss << "reader读取 " << m_data << " 成功" << std::endl;

        std::cout << ss.str();
    }
    //写操作
    void write(const std::string& s) {
        std::unique_lock<std::shared_timed_mutex> lock(stm);
        std::stringstream ss;

        ss << "writer正在修改..." << std::endl;
        std::this_thread::sleep_for(1s);
        m_data = s;
        ss << "writer修改成功" << std::endl;

        std::cout << ss.str() << std::endl;
    }
    //尝试读操作
    void try_read_for(const int& time) {
        std::shared_lock<std::shared_timed_mutex> lock(stm, std::defer_lock);
        std::stringstream ss;

        ss << "trying reading..." << std::endl;
        if (lock.try_lock_for(std::chrono::milliseconds(time))) {
            ss << "try reading " << m_data << " successfully" << std::endl;
        }
        else {
            ss << "failed to try reading" << std::endl;
        }

        std::cout << ss.str() << std::endl;
    }

    SharedData(const std::string& s) :m_data(s) {};
};

int main() {
    SharedData sd("Version 0.1");
    //创建3个读数据的线程，每个线程均会读5次数据
    std::vector<std::thread>readers;
    for (int i = 0;i < 3;i++) {
        readers.emplace_back([&sd] {
            for (int i = 0;i < 5;i++) {
                sd.read();
                std::this_thread::sleep_for(100ms + std::chrono::milliseconds(rand() % 1000));
            }
            });
    }
    //创建1个写数据的线程，该线程也会写5次数据
    std::thread writer([&sd] {
        for (int i = 2;i < 7;i++) {
            sd.write("Version 0." + std::to_string(i));
            std::this_thread::sleep_for(100ms + std::chrono::milliseconds(rand() % 1000));
        }
        });
    //创建1个尝试读取数据的线程，该线程会尝试在300ms的时间内读取数据3次
    std::thread trying_reader([&sd] {
        for (int i = 0;i < 3;i++) {
            sd.try_read_for(300);
        }
        });
    //等待线程全部结束
    for (auto& it : readers) {
        it.join();
    }
    writer.join();
    trying_reader.join();
}