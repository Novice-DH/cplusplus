#include <iostream>
#include <thread>
// Linux -lpthread

using namespace std;

bool is_exit = false;

// 线程入口函数
void ThreadMain()
{
    cout << "begin sub thread id " << this_thread::get_id() << endl;
    for (int i = 0; i < 10; i++)
    {
        if (is_exit)
        {
            break;
        }
        cout << "in thread " << i << endl;
        this_thread::sleep_for(1000ms);
    }
    cout << "end sub thread id " << this_thread::get_id() << endl;
}

// 主线程入口
int main(int argc, char *argv[])
{
    {
        //thread th(ThreadMain);
    } // err，线程对象被销毁，但子线程还在运行

    {
        //thread th(ThreadMain);
        //th.detach(); // 子线程与主线程分离，潜在问题，主线程退出后子线程未退出！
        // 理解成 创造了一个守护线程（后台运行），与主线程无关
        // 在主线程中，无需再去维护 th 对象
        // detach 是让目标线程成为守护线程（daemon threads）
    }

    {
        thread th(ThreadMain);
        this_thread::sleep_for(1000ms); // 模拟 主线程业务处理
        is_exit = true; // 通知子线程退出

        cout << "主线程阻塞，等待子线程退出" << endl;
        th.join(); // 主线程阻塞，等待子线程退出
        cout << "子线程已退出！" << endl;
    }

    getchar(); // 让主线程保持运行
    return 0;
}
