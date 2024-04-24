#include<iostream>
using namespace std;

template<class T>
class SharedPointer{
    private:
        T* ptr;
        //int* counter;
    public :
        int* counter;
        SharedPointer(T* ptr=nullptr)   // c1
        {
            cout<<"parameterized constructor"<<endl;
            this->ptr=ptr;
            counter=new int(1);
        }
      
        SharedPointer( SharedPointer& sp)//c3
        {
          //  sp.incrementcounter();
           cout<<"copy constructor"<<endl;
            this->ptr=sp.ptr;
            this->counter=sp.counter;
            incrementcounter();
        }
        T operator*()
        {
            if(ptr==nullptr) return static_cast<T>(0);
            return *ptr;
        }
        T* operator->()
        {
            return ptr;
        }
        void decreasecount()
        {
            if(counter)
            (*counter)--;
            else return;
            if(*counter==0)
            {
                delete ptr;
                delete counter;
                ptr=nullptr;
                counter=nullptr;
            }
        }
        void incrementcounter()
        {
            if(counter)
            (*counter)++;
        }
        void operator=(SharedPointer p) //c5
        {
             cout<<"assignment operator"<<endl;
            this->decreasecount();
            this->ptr=p.ptr;
            this->counter=p.counter;
            incrementcounter();
        }

        SharedPointer(SharedPointer&& mv)  //c4
        {
             cout<<"move symantics constructor"<<endl;
            counter=mv.counter;
            ptr=mv.ptr;
            mv.ptr=nullptr;
            mv.counter=new int(0);
        }
        void operator=(SharedPointer&& mv)  //c7
        {
             cout<<"move symantics constructor"<<endl;
            counter=mv.counter;
            ptr=mv.ptr;
            mv.ptr=nullptr;
            mv.counter=new int(0);
        }
        int use_count()
        {
            return *counter;
        }
        void reset()
        {
             decreasecount();
             ptr=nullptr;
             counter=new int(0);
        }
        ~SharedPointer()
        {
            decreasecount();
        }



};
int main()
{
    cout<<"****Programme for inplementation of shared POinter****\n"<<endl;

    SharedPointer<int> p1(new int(54));//c1
   SharedPointer<int> p2=p1;
    //SharedPointer p2 =p1; //c5
   // SharedPointer p3;
   SharedPointer<int> p3(p2); //c3
   SharedPointer<int> p4(std::move(p2));
  //SharedPointer p4(std::move(SharedPointer<int> (new int(23))));  //c4
   cout<<"p1 ::"<<p1.use_count()<<" " <<(*p1)<<endl;
   cout<<"p2 ::"<<p2.use_count()<<" " <<(*p2)<<endl;
   cout<<"p3 ::"<<p3.use_count()<<" " <<(*p3)<<endl;
   cout<<"p4 ::"<<p4.use_count()<<" " <<(*p4)<<endl;

   p2.reset();
    cout<<"p1 ::"<<p1.use_count()<<" " <<(*p1)<<endl;
  // cout<<"p2 ::"<<p2.use_count()<<" " <<(*p2)<<endl;
   cout<<"p3 ::"<<p3.use_count()<<" " <<(*p3)<<endl;
   cout<<"p4 ::"<<p4.use_count()<<" " <<(*p4)<<endl;
p3.reset();
p3=p4;
cout<<"p1 ::"<<p1.use_count()<<" " <<(*p1)<<endl;
  // cout<<"p2 ::"<<p2.use_count()<<" " <<(*p2)<<endl;
   //cout<<"p3 ::"<<p3.use_count()<<" " <<(*p3)<<endl;
   cout<<"p4 ::"<<p4.use_count()<<" " <<(*p4)<<endl;
    SharedPointer<int> p5=move(p1);
     cout<<"p1 ::"<<p1.use_count()<<" " <<(*p1)<<endl;
   cout<<"p2 ::"<<p2.use_count()<<" " <<(*p2)<<endl;
   cout<<"p3 ::"<<p3.use_count()<<" " <<(*p3)<<endl;
   cout<<"p4 ::"<<p4.use_count()<<" " <<(*p4)<<endl;
   cout<<"p5::"<<p5.use_count()<<" " <<(*p5)<<endl;

    //p2=p1;//
}