#include <iostream>
#include <thread>
#include <string>
// Linux -lpthread

using namespace std;

class MyThread
{
public:
    // 线程入口函数
    void Main()
    {
        std::cout << "MyThread::Main " << name << " : " << age << std::endl;
    }
    std::string name;
    int age = 100;
};

// 线程基类
class XThread
{
public:
    virtual void Start()
    {
        is_exit_ = false;
        th_ = std::thread(&XThread::Main, this);
    }
    virtual void Stop()
    {
        is_exit_ = true;
        Wait();
    }
    virtual void Wait()
    {
        if (th_.joinable())
        {
            th_.join();
        }
    }
    bool is_exit() { return is_exit_; }

private:
    // 1 不需要基类实现
    // 2 约定 派生类 必须 重写
    virtual void Main() = 0; // 纯虚函数
    std::thread th_;

    bool is_exit_ = false;
};

class TestXThread : public XThread
{
public:
    // override 确保 在 编译阶段 之前 就发现（检测） err
    void Main() override
    {
        cout << "TestXThread::Main begin" << endl;
        while (!is_exit())
        {
            this_thread::sleep_for(100ms);
            // flush 确保 . 从标准缓冲区 输出到屏幕
            cout << "." << flush;
        }
        cout << endl;
        cout << "TestXThread::Main end" << endl;
    }
    string name;
};

int main(int argc, char *argv[])
{
    TestXThread testth;
    testth.name = "TestXThread name";
    testth.Start();
    this_thread::sleep_for(3s);
    testth.Stop();

    testth.Wait();
    getchar();


    MyThread myth;
    myth.name = "test name 001";
    myth.age = 20;
    // &MyThread::Main 成员函数指针（不能直接访问）
    // &myth 通过当前对象地址 this 指针
    thread th(&MyThread::Main, &myth);
    th.join();

    return 0;
}
