#include<iostream>
#include<chrono>
#include<thread>
using namespace std;
//duration->时间间隔,time_point->时间点
int main() {
    //system_clock（系统时间）用法
    auto currenttime = chrono::system_clock::now();//currenttime类型为一个system_clock的时间点类型
    time_t currenttime_t = chrono::system_clock::to_time_t(currenttime);
    cout << "当前时间：" << ctime(&currenttime_t);//c语言api

    cout << "在system_clock上距离1970-01-01的时间间隔： ";
    cout << currenttime.time_since_epoch().count() << endl;//距离1970-01-01的时间间隔

    tm* lt = localtime(&currenttime_t);//一个当前时间的结构体指针
    cout << "当前时间：";
    cout << lt->tm_year + 1900 << "-" << lt->tm_mon + 1 << "-" << lt->tm_mday << " " << lt->tm_hour << ":" << lt->tm_min << ":" << lt->tm_sec << endl;

    //steady_clock用法（来自CPU时钟）
    cout << "在steady_clock上距离1970-01-01的时间间隔： ";
    cout << chrono::steady_clock::now().time_since_epoch().count() << endl;//距离1970-01-01的时间间隔

    auto before = chrono::steady_clock::now();
    this_thread::sleep_for(chrono::seconds(1));//睡眠1s
    auto after = chrono::steady_clock::now();
    chrono::steady_clock::duration dur = after - before;//dur代表after和before创建的时间间隔
    cout << dur.count() << endl;

    chrono::duration<double, milli> dur1 = after - before;//milli千分之一单位制
    cout << dur1.count() << endl;

    //high_resolution_clock的用法（代表了当前系统时间所支持的最高精度，它可能就是steady_clock或system_clock）
    cout << "在high_resolution_clock上距离1970-01-01的时间间隔： ";
    cout << chrono::high_resolution_clock::now().time_since_epoch().count() << endl;//距离1970-01-01的时间间隔

    auto before1 = chrono::high_resolution_clock::now();
    this_thread::sleep_for(chrono::seconds(1));//睡眠1s
    auto after1 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> dur2 = after1 - before1;//dur2代表after1和before1创建的时间间隔（千分之一单位制）
    cout << dur2.count() << endl;
}