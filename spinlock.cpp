#include<atomic>
#include<iostream>
#include<thread>
using   namespace std;
class spinlock
{
    atomic_flag flag=ATOMIC_FLAG_INIT;
    int retry;
    void backoff()
    {
        
        if(retry<=8)
        {
            this_thread::yield();
        }
        else
        {
            this_thread::sleep_for(chrono::milliseconds(1<<(retry-8)));
        }
    }
    public:
    spinlock()
    {
        retry=0;
    }
    void lock()
    {
        while(flag.test_and_set(memory_order_acquire))
        {
            retry++;
            backoff();
        }
    }
    void unlock()
    {
        flag.clear(memory_order_release);
    }

};
spinlock lk;
void testLock(int &counter)
{
    for(int i=0;i<7;i++)
    {
        lk.lock();
        counter++;
        cout<<this_thread::get_id()<<"changed counter to "<<counter<<endl;
        lk.unlock(); 
    }
}
int main()
{
    int counter=0;
    thread threads[5];
    for(int i=0;i<5;i++)
    {
        threads[i]=std::thread(testLock, std::ref(counter));
    }
    for(int i=0;i<5;i++)
    threads[i].join();
}