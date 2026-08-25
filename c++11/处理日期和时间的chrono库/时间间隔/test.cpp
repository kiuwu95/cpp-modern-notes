#include<iostream>
#include<chrono>
#include<thread>
using namespace std;

int main() {
    chrono::steady_clock::period;//period表示该时钟类型的精度为nanoseconds
    chrono::steady_clock::rep();//rep表示该时钟类型的时间储存类型为long long
    //创造一个自定义的时间间隔
    //60ms
    using fps_60 = chrono::duration<long long, ratio<3, 500>>;
    fps_60 f(1);

    auto before = chrono::steady_clock::now();
    this_thread::sleep_for(fps_60(1));
    auto after = chrono::steady_clock::now();
    chrono::duration<double, milli> dur = after - before;
    cout << dur.count() << endl;

    //data()每隔60ms运行
    // while (1) {
    //     auto tn = chrono::steady_clock::now();
    //     auto end = tn + fps_60(1);
    //     //data();
    //     this_thread::sleep_until(end);
    // }
}