#include <iostream>
#include <thread>
#include <string>
#include <mutex> // call_once

using namespace std;

void SystemInit()
{
    cout << "call SystemInit" << endl;
}

void SystemInitOne()
{
    static std::once_flag flag;
    std::call_once(flag, SystemInit);
}

int main(int argc, char *argv[])
{
    SystemInitOne();
    SystemInitOne();

    for (int i = 0; i < 3; i++)
    {
        thread th(SystemInitOne);
        th.detach();
    }
    getchar();
    return 0;
}