#include<iostream>
using namespace std;
typedef pair<int,int> Point;
typedef struct Node{
    int val,posX,posY;
    Node(int x,int y):posX(x),posY(y){}
}Node;

class quad{
    Point topleft, bottomright;
    quad *top_left,*top_right,*bottom_left, *bottom_right;
    Node* lnode;
    public: 
    quad(){
        lnode=NULL;
        topleft=make_pair(0,0);
        bottomright=make_pair(0,0);
    }
    quad(Point top, Point bottom): topleft(top),bottomright(bottom){
        lnode=NULL;
    }
    bool isValid(Node* candidate)
    {
        if(candidate->val==0)return false;
        if(candidate->posX<topleft.first || candidate->posX>bottomright.second || candidate->posY<topleft.second || candidate->posY>bottomright.second)return false;
        return true;
    }
    void insert(Node* node)
    {
        if(!isValid(node))return;
        if(!lnode)lnode=node;
        else
        {
            if(abs(topleft.first-bottomright.first)<=1 || abs(topleft.second-bottomright.second)<=1){
                cout<<"No space left to devide further"<<endl;
            }
            if(node->posX<=(bottomright.first+topleft.first)/2 && node->posY<=(topleft.second+bottomright.second)/2)
            {
                if(top_left==NULL)
                {
                    Point bottom=make_pair((bottomright.first+topleft.first)/2 , (topleft.second+bottomright.second)/2);
                    top_left=new quad(topleft, bottom);
                }
                top_left->insert(node);
            }
            else if(node->posX>=(bottomright.first+topleft.first)/2 && node->posY<=(topleft.second+bottomright.second)/2)
            {
                if(top_right==NULL)
                {
                    Point bottom=make_pair(bottomright.first, (topleft.second+bottomright.second)/2);
                    Point top= make_pair((bottomright.first+topleft.first)/2 , topleft.second);
                    top_left=new quad(top, bottom);
                }
                top_left->insert(node);
            }
            else if()
            {

            }
            else if()
            {

            }
        }

    }
};
