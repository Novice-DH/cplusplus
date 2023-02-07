#include <iostream>
#include <thread>
#include <string>

using namespace std;

class Para
{
public:
    Para() { cout << "Creat Para" << endl; }
    Para(const Para &p) { cout << "Copy Para" << endl; }
    ~Para() { cout << "Drop Para" << endl; }
    string name;
};

// 传递 Para 对象，多次创建
void ThreadMain(int p1, float p2, string str, Para p4)
{
    this_thread::sleep_for(100ms);
    cout << "ThreadMain " << p1 << " " << p2 << " " << str << " " << p4.name << endl;
}

// 传递 Para 指针，没有拷贝，在对象创建后，直接访问对象内容
// 子线程没有指针参数所有权（不负责销毁），由主线程维护
void ThreadMainPtr(Para *p)
{
    this_thread::sleep_for(100ms);
    cout << "ThreadMainPtr name = " << p->name << endl;
}

// 传递 Para 引用，没有拷贝
void ThreadMainRef(Para &p)
{
    this_thread::sleep_for(100ms);
    cout << "ThreadMainPtr name = " << p.name << endl;
}

int main(int argc, char *argv[])
{
    {
        Para p;
        p.name = "test ref";
        //thread th(ThreadMainRef, p); // err，模板函数参数没法确定 p 是一个引用
        thread th(ThreadMainRef, ref(p)); // 模板函数参数 都要显式 ref
        th.join();
    }
    getchar();

    {
        Para p;
        p.name = "test ThreadMainPtr name";
        thread th(ThreadMainPtr, &p); // err，线程访问的 p 空间被提前释放
        th.detach();
    } // Para 释放，但子线程仍在访问，此时访问不到对象内容
    getchar();

    {
        Para p;
        p.name = "test ThreadMainPtr name";
        thread th(ThreadMainPtr, &p);
        th.join();
        getchar();
    }


    thread th;
    {
        float f1 = 12.1f;
        Para p;
        p.name = "test Para Class";
        // 启动线程时，所有的参数传递后，都做了复制
        th = thread(ThreadMain, 101, f1, "test string para", p);
    } // 此时 f1 被销毁，但因为参数有拷贝，不影响 子线程的运行
    th.join();

    return 0;
}