#include<iostream>
#include<future>
#include<functional>
#include<thread>
#include <unistd.h>
#include <chrono>
using namespace std;
//future can be created by three ways , directly  as in future.cpp, using promise, using packaged_task


//here the child thread will expect something from the parent .. so parent has to promise something ans this will have a future 

int func1(int x, future<int> f)
{
    cout<<"f1 executed"<<endl;

    int k=f.get();
    cout<<"got promise"<<endl;
    this_thread::sleep_for(std::chrono::seconds(4));
    cout<<"sleep complete returning"<<endl;
    return 89+k+x;
}

/*

int func1(int x, future<int> f)
{
    cout<<"f1 executed"<<endl;

    int k=f.get();
    cout<<"got promise"<<endl;
    this_thread::sleep_for(std::chrono::seconds(4));
    cout<<"sleep complete returning"<<endl;
    return 89+k+x;
}
*/
//async coukb be execute in different thread or same thread
//execution 
int main()
{
    promise<int> p;
    future<int> fu=async(launch::async,  func1,12,p.get_future());//getting fututre from child class to parent clas
    cout<<"created future"<<endl;
    this_thread::sleep_for(std::chrono::seconds(4));

    p.set_value(89);
    int a=fu.get();
   // int b=fu.get();//this will crash
    cout<<"value of a="<<a;   
}