#include<iostream>
using namespace std;

template<class K,class V>
class HashNode
{
    public:
    K k;
    V v;
    HashNode* next;
    
    HashNode(K k1, V v1):k(k1),v(v1)
    {next=nullptr;}
};
template<class T>
long hashfunc(T t)
{
    return static_cast<long>(t)%20;
}


template<class K, class V>
class MyHash
{
    private :
        HashNode<K,V> **table;
    public:
        MyHash()
        {
            table=new HashNode<K,V>*[20];

        }
        void put(K k,V v)
        {
            long hash=hashfunc<K>(k);
            if(table[hash]==NULL)
            {
                table[hash]=new HashNode<K,V>(k,v);
            }
            else{
                HashNode<K,V> *temp=table[hash];
                while(temp->next)
                {
                    temp=temp->next;
                }
                temp->next=new HashNode<K,V>(k,v);
            }
        }
        V get(K k)
        {
            long hash=hashfunc<K>(k);
            if(table[hash]!=NULL)
            
            {
                HashNode<K,V>*  temp=table[hash];
                while(temp)
                {
                    if(temp->k==k)return temp->v;
                    temp=temp->next;
                }
            }
            cout<<"Value N F";
            return reinterpret_cast<V>(0);
        }

        void erase(K k)
        {

            long hash=hashfunc<K>(k);
            if(table[hash]!=NULL)
            
            {
                HashNode<K,V>*  temp=table[hash];
                if(temp->k==k)
                {
                  //  t=temp;
                    table[hash]=temp->next;
                    delete temp;
                    return;
                }
                while(temp->next)
                {
                    if(temp->next->k==k){
                        HashNode<K,V> n=temp->next;
                        temp->next=n->next;
                        delete n;
                        return;
                    }
                    temp=temp->next;
                }
            }
            cout<<"Value N F";
        }

};


int main()
{
    MyHash<int,int>  myh;
    myh.put(1,3);
    cout<<myh.get(1)<<endl;
}