#include<iostream>
#include<thread>
#include<chrono>
using namespace std;

int main() {
    //时间点减去另一个时间点得到一个时间间隔
    //创建时间点
    chrono::time_point<chrono::steady_clock> tp;

    //时间间隔换算
    //每当间隔换算使编译器报错时，不妨使用duration_cast进行换算
    chrono::steady_clock::time_point before = chrono::steady_clock::now();
    this_thread::sleep_for(chrono::seconds(1));//休眠1s
    chrono::steady_clock::time_point after = chrono::steady_clock::now();
    //因为after和before是来自于steady_clock的时间点，所以它们的时间间隔自然也就来自steady_clock的<long long,nanoseconds>
    //chrono::duration<long long,milli>dur非法，因为这属于精度丢失的转换，小数点后面的数会被砍掉，精度变低
    chrono::duration<double, milli> dur = after - before;//合法，double使得小数点后的数字依旧保留了下来，精度不变
    cout << dur.count() << endl;
    //必须使用显式转换，告诉编译器确定要截断精度
    chrono::duration<long long, milli>dur2 = chrono::duration_cast<chrono::duration<long long, milli>>(after - before);
    //chrono::milliseconds dur2 = chrono::duration_cast<chrono::milliseconds>(after - before);与上面等价
    cout << dur2.count() << endl;
    //对于隐式转化，只有低精度转化为高精度可用，比如秒->毫秒
    chrono::seconds s(1);
    chrono::milliseconds ms = s;
}