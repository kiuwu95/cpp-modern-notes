/*
关系梳理：
promise(写) ↔ future(读)  最底层，手动set_value，不绑定函数
    ↑
packaged_task：包装函数，内部自带promise；函数跑完自动set_value
    ↑
std::async：高层接口，封装packaged_task，自动管理线程，直接返回future

关键点：
1. promise、packaged_task、future不能拷贝，只可移动
2. get_future()仅可调用一次；future.get()也仅可调用一次
3. 如果promise/packaged_task销毁但没有设置值，future.get()抛出异常
*/

#include<iostream>
#include<thread>
#include<chrono>
#include<future>
#include<functional>

int calcu1(int x) {
    return x * 2;
}
//函数参数中必须要有promise
void calcu2(std::promise<int>& p, int x) {
    p.set_value(x * 2);
}

int main() {
    std::promise<int>p;
    std::future<int>fu1 = p.get_future();//promise只能调用一次get_future
    std::thread t1(calcu2, std::ref(p), 4);
    std::cout << fu1.get() << std::endl;//阻塞等待，等calcu2函数结束，fu1获得值后，代码才继续往下运行
    //get只能调用一次，调用完以后future就会失效
    std::packaged_task<int(int)>task(calcu1);
    std::future<int>fu2 = task.get_future();
    std::thread t2(std::move(task), 5);
    // task(5);也可以，等价于创建线程
    std::cout << fu2.get() << std::endl;//阻塞等待，等calcu1函数结束，fu2获得值后，代码才继续往下运行

    std::future<int> fu3 = std::async(std::launch::async, calcu1, 2);
    std::cout << fu3.get() << std::endl;//阻塞等待，等calcu1函数结束，fu3获得值后，代码才继续往下运行

    t1.join();
    t2.join();
}