//here im implementing a basic threadPool 
#include<iostream>
#include<thread>
#include<unistd.h>
#include<future>
#include<chrono>
#include<functional>
#include<vector>
#include<queue>
using namespace std;
/*
std::function is a wrapper class. So what does it wrap?

It wraps any callable.
syntax  
function<returnType(argumentTyp1, argType2,...)> f(funxtionName);

// AS AN ALTERNative to functionpointer 
using funx=function<int(int)> ;

void f1(func f)

*/
using funx=function<int(int)> ;
void execfun();
mutex m;
condition_variable cv;
class ThreadPool
{
    private:
    int threadcount;
    
    vector<thread> threadvec;
    queue<function<void()> > taskqueue;
    public:
    bool stoppool;
    ThreadPool(int threadno):threadcount(threadno),stoppool(0){
        for(int i=0;i<threadcount;i++)
        {
            threadvec.emplace_back([this,i]()
            {
                while(1)
                {
                    unique_lock<mutex> lock(m);
                    cv.wait(lock, [this](){
                    return !taskqueue.empty() || stoppool;
                    });
                    if(stoppool)break;
                    cout<<"thread num "<<i<<"wake up from waiting "<<endl;
                    function<void()> task=move(taskqueue.front());
                    cout<<"got task , popping element "<<endl;
                    taskqueue.pop();
                    m.unlock();
                    task();
                }
                //cv.wait(lock);
            });
        }
    }
    void insertTask(function<void()> task)
    {
        unique_lock<mutex> lock(m);
        taskqueue.emplace(task);
        m.unlock();
        cv.notify_one();
    }
    

    template<typename F, typename... Args>
    auto executeTask(F && f, Args&&... arg)->future<decltype(f(arg...))>
    {
        using returnType=decltype(f(arg...));
        auto task = make_shared<packaged_task<returnType()>>(bind(forward<F>(f), forward<Args>(arg)...)) ;
        future<returnType> res=task->get_future();
        this->insertTask([task]()->void{
            (*task)();
        });
        return res;
    }



    ~ThreadPool()
    {
        cv.notify_all();
        for(int i=0;i<threadcount;i++)
        threadvec[i].join();
    }
};



int execfun(int x)
{
    cout<<"inside task ==== "<<endl;
   // this_thread::sleep_for(chrono::seconds(2));
    cout<<"task executed"<<endl;
    return x*x;
}


int main()
{
    ThreadPool pool(5);
    //int i=90;
    for(int i=0;i<5;i++ )
    {
    future<int> f1 = pool.executeTask([i]() {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            return i * i;
        });
        //function<int(int)> fu=execfun;
        //future<int> f2 = pool.executeTask((execfunc), 12);
        int x=f1.get();
    cout << "answer is = " << x << endl;
    }
    pool.stoppool = true;
    cv.notify_all();
    
    return 0;
}

