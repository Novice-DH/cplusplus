#include <iostream>
#include <thread>
#include <string>

using namespace std;

class TestLambda
{
public:
    void Start()
    {
        // lambda 作为线程入口函数 访问成员变量
        thread th([this]() {cout << "name = " << name << endl; });
        th.join();
    }
    string name = "test lambda";
};


int main(int argc, char *argv[])
{
    thread th(
        // 相当于 形成一个函数指针 返回
        [](int i) {cout << "test lambda " << i << endl; },
        123
    );
    th.join();

    TestLambda test;
    test.Start();

    return 0;
}
