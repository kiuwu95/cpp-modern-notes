#include<iostream>
#include<chrono>
#include<ctime>
using namespace std;

int main() {
    chrono::system_clock s;
    auto currenttime = chrono::system_clock::now();
    time_t currenttime_t = chrono::system_clock::to_time_t(currenttime);
    cout << "当前时间：" << ctime(&currenttime_t);
    chrono::steady_clock std;
    chrono::high_resolution_clock hrc;

    chrono::system_clock::duration s_d;
    chrono::steady_clock::duration std_d;
    chrono::high_resolution_clock::duration hrc_d;

    chrono::system_clock::time_point s_p;
    chrono::steady_clock::time_point std_p;
    chrono::high_resolution_clock hrc_p;

}