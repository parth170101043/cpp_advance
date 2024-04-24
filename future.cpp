#include<iostream>
#include<future>
#include<functional>
#include<thread>
#include <unistd.h>
#include <chrono>
using namespace std;
//future can be created by three ways , directly  as in this file, using promise, using packaged_task

int func1(int x)
{
    cout<<"f1 executed"<<endl;
    this_thread::sleep_for(std::chrono::seconds(4));
    cout<<"sleep complete returning"<<endl;
    return 89;
}

//async coukb be execute in different thread or same thread
//execution 
int main()
{
    future<int> fu=async(launch::async,  func1,12);//getting fututre from child class to parent class
    cout<<"created future"<<endl;
    int a=fu.get();
   // int b=fu.get();//this will crash
    cout<<"value of a="<<a;   
}