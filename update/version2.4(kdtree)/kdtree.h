#include<iostream>
#include<stack>
using namespace std;
bool CallForPoint(int id);
class node{
    public:
    int id;
    int dir;//0 for x ,1 for y
    double pos[2];
    node *left;
    node *right;
    node(){}
    node(int id,double *posin):id(id){
        pos[0]=posin[0];
        pos[1]=posin[1];
        left=right=NULL;
    };
};

class kdtree{
    public:
    node head;
    void build();
    void insert(double *pos,int id,node &head);
    void search(double *min,double *max,node &head);
};

void kdtree::build()
{
    double pos[2]={2500,2500};
    head=node(1,pos);
    head.dir=0;
}

void kdtree::insert(double *pos,int id,node &head)
{
    switch(head.dir) //x大者在右边
    {
        case 0:
        if(pos[0]>head.pos[0])//to right
        {
            if(head.right!=NULL)
            insert(pos,id,*(head.right));
            else 
            {
                node *right=new node;
                (*right)=node(id,pos);
                (*right).dir=1;
                head.right=right;
            }
        }
        else 
        {
            if(head.left!=NULL)
            insert(pos,id,*(head.left));
            else 
            {
                node *left=new node;
                (*left)=node(id,pos);
                (*left).dir=3;
                head.left=left;
            }
        }
            break;
        case 1://y大者在左边
        if(pos[1]<head.pos[1])
        {
            if(head.right!=NULL)
                insert(pos,id,*(head.right));
            else 
            {
                node *right=new node;
                (*right)=node(id,pos);
                (*right).dir=2;
                head.right=right;
            }
        }
        else
        {
            if(head.left!=NULL)
                insert(pos,id,*(head.left));
            else 
            {
                node *left=new node;
                (*left)=node(id,pos);
                (*left).dir=0;
                head.left=left;
            }
        }
            break;
        case 2://x大者在左
        if(pos[0]<head.pos[0])
        {
            if(head.right!=NULL)
                insert(pos,id,*(head.right));
            else 
            {
                node *right=new node;
                (*right)=node(id,pos);
                (*right).dir=3;
                head.right=right;
            }
        }
        else 
        {
            if(head.left!=NULL)
                insert(pos,id,*(head.left));
            else 
            {
                node *left=new node;
                (*left)=node(id,pos);
                (*left).dir=1;
                head.left=left;
            }
        }
            break;
        default:
        if(pos[1]>head.pos[1])
        {
            if(head.right!=NULL)
                insert(pos,id,*(head.right));
            else 
            {
                node *right=new node;
                (*right)=node(id,pos);
                (*right).dir=0;
                head.right=right;
            }
        }
        else 
        {
            if(head.left!=NULL)
                insert(pos,id,*(head.left));
            else 
            {
                node *left=new node;
                (*left)=node(id,pos);
                (*left).dir=2;
                head.left=left;
            }
        }
    }
}

void kdtree::search(double *min,double *max,node &head)
{
        switch(head.dir)
        {
            case 0:
                if(max[0]>head.pos[0]&&head.right!=NULL)
                search(min,max,*(head.right));
                if(min[0]<head.pos[0]&&head.left!=NULL)
                search(min,max,*(head.left));
                break;
            case 1:
                if(max[1]>head.pos[1]&&(head).left!=NULL)
                search(min,max,*(head.left));
                if(min[1]<head.pos[1]&&(head).right!=NULL)
                search(min,max,*(head.right));
                break;
            case 2:
                if(max[0]>(head).pos[0]&&(head).left!=NULL)
                search(min,max,*(head.left));
                if(min[0]<(head).pos[0]&&(head).right!=NULL)
                search(min,max,*(head.right));
                break;
            default:
                if(max[1]>(head).pos[1]&&(head).right!=NULL)
                search(min,max,*(head.right));
                if(min[1]<(head).pos[1]&&(head).left!=NULL)
                search(min,max,*(head.left));
        }
    if((head.pos[0]>=min[0])&&\
    ((head).pos[0]<=max[0])&&\
    ((head).pos[1]>=min[1])&&\
    ((head).pos[1]<=max[1]))
         CallForPoint(head.id);
}
