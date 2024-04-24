#include<iostream>
#include<map>
using namespace std;
template <class K, class V>
class LL{
    public:
    K k;
    V v;
     LL<K,V>* next;
    LL(K kt,V vt):k(kt),v(vt)
    {
        next=NULL;
    }
};
//#define LL struct  LL;



template <class K, class V>
class LRUCache
{
    private:
        int cachesize;
        map<K,V> storage;
        LL <int,int>* head;
        void listInsert(LL<int,int>* node)
        {
            if(!head){head=node;return;}
            LL<int,int>* temp=head;
            while(temp->next)
            temp=temp->next;
            temp->next=node;
        }
         void evictkey()
        {
            LL<int,int>* temp=head;
            head=head->next;
            storage.erase(temp->k);
            delete temp;
        }
        void removekeyLL(K k)
        {
            if(head->k==k)
            {
                evictkey();return;
            }
             LL<int,int>* temp=head;
            while(temp->next)
            {
                if(temp->next->k==k)
                {
                    LL<int,int>* d=temp->next;
                    temp->next=d->next;
                    delete d;
                    break;
                }
            }
            
        }
    public:
    LRUCache(int s=100):cachesize(s)
    {
        head=NULL;
    }
   
    void put(K k, V v)
    {

        if(storage.count(k))
        {
            //V v1=storage(k);
            storage[k]=v;
            removekeyLL(k);
            listInsert(new LL(k,v));
            return ;
        }
        if(storage.size()==cachesize)
        {
            cout<<"size exceeded removing element"<<endl;
            evictkey();
           
        }
        storage.insert({k,v});
            LL<int,int>* node=new LL(k,v);
            listInsert(node);

    }
    V getKey(K k)
    {
        if(storage.count(k))
        {
            V v1=storage[k];
            removekeyLL(k);
            listInsert(new LL(k,v1));
            return v1;
        }
        else
        {
            cout<<"key not found";
            return reinterpret_cast<V> (0);
        }
    }

    
};

int main()
{
    LRUCache<int,int> cache;
    cache.put(1,2);
  cout<<cache.getKey(1)<<endl;
   cache.put(1,56);
    cout<<cache.getKey(1)<<endl;

}