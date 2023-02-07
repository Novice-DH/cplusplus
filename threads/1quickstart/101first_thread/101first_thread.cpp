#include <iostream>
#include <thread>
// Linux -lpthread

using namespace std;

// 线程入口函数
void ThreadMain()
{
    cout << "begin sub thread id " << this_thread::get_id() << endl;
    for (int i = 0; i < 10; i++) // 10s 之后线程退出
    {
        cout << "in thread " << i << endl;
        // sleep_for：CPU 睡眠，即当前线程释放 CPU 资源时间
        //this_thread::sleep_for(chrono::seconds(1)); // 1000ms
        this_thread::sleep_for(1000ms);
    }
    cout << "end sub thread id " << this_thread::get_id() << endl;
}

// 主线程入口
int main(int argc, char *argv[])
{
    cout << "main thread id : " << this_thread::get_id() << endl;
    // 线程创建启动
    thread th(ThreadMain);

    cout << "begin wait sub thread " << endl;
    // 主线程阻塞，等待子线程退出
    th.join();
    cout << "end wait sub thread " << endl;

    return 0;
}
