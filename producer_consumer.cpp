#include<iostream>
#include<queue>
#include<mutex>
#include<condition_variable>
#include<thread>
using namespace std;
#define maxsize 5;
queue<int> myq;
condition_variable pro, con;
mutex reslock;
void producer()
{
    int index=0;
    while (1)
    {
        unique_lock<mutex> lk(reslock);
        pro.wait(lk, [](){return myq.size()<maxsize ;});
        myq.push(index);
       cout<<"producing "<<index<<endl;
        lk.unlock();
        con.notify_one();
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout<<"produced index = "<<index<<endl;
        index++;
    }
     
    
}


void consumer()
{
    while(1)
    {
        unique_lock <mutex> lk2(reslock);
        cout<<"consumer waiting"<<endl;
        con.wait(lk2, [](){return !myq.empty();});
        int x=myq.front();
        myq.pop();
        lk2.unlock();
        pro.notify_one();
        cout<<"consumed index = "<<x<<endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

int main()
{
    thread t1(consumer);
    thread t2(producer);
    t1.join();
    t2.join();
}