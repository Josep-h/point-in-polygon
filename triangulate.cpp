#include<vector>
#include<algorithm>
#include<stack>
using namespace std;

class tup{//def of the tuple
    public:
    float x;
    float y;
    bool flag;//to mark the convexicity of the point
    tup(){}
    tup(float x,float y):x(x),y(y){}
    bool operator < (const tup &now) const{
        return y<now.y;//for sort function
    }
    bool operator == (const tup &now) const{
        return y==now.y&&x==now.x;
    }
};
bool cmp_complex(vector<tup> &ring,int &left,int &right,int sz,stack<tup> &path)//input the two tuple and return next one considered
{
    if(ring[left].y>ring[right].y)
    {
        path.push(ring[left]);
        left=(left+1)%sz;
        return 1;
    }
    else{
        path.push(ring[right]);
        right=(right+sz-1)%sz;
        return 0;
    }
}
bool cmp(vector<tup> &ring,int &left,int &right)
{
    return ring[left].y>ring[right].y;
}
class tri{//def of triangle
    public:
    int id;
    tup a,b,c;
    float x_low;
    float y_low;
    float x_high;
    float y_high;
    tri(){}
    tri(int id,tup x,tup y,tup z):id(id),a(x),b(y),c(z){
        //get x,w,y,h while initialize
        x_low=a.x,y_low=a.y,x_high=a.x,y_high=a.y;
        if(b.x<x_low)
            x_low=b.x;
        else if(b.x>x_high)
                x_high=b.x;
        if(b.y<y_low)
            y_low=b.y;
        else if(b.y>y_high)
                y_high=b.y;
        
        if(c.x<x_low)
            x_low=c.x;
        else if(c.x>x_high)
                x_high=c.x;
        if(c.y<y_low)
            y_low=c.y;
        else if(c.y>y_high)
                y_high=c.y;//get the bound of the triangle
    }
    bool test(tup tt);//fun test if a point is in a triangule
};

class poly{//that's the polygon marked by the point formation
    public:
    int id;
    int nums;
    tup up_right;//denote the rectangle surrounds polygon
    tup down_left;
    vector<tup> tuples;//tuples the polygon holds which is counterclockwise
    poly(){}
    poly_tri triangulate();
};

class poly_tri{//def of the polygon triangulated with the algorithm
    public:
    int id;//the same as the id the ori polygon has
    tup up_right;//denote the rectangle surrounds polygon
    tup down_left;
    vector<tri> cells;//denote the triangles the alogorithms get
    poly_tri(){}
    poly_tri(int id):id(id){}
    bool test(tup tt);//fun to finish the point-in-polygon test
};

//funs in triangle
bool tri::test(tup tt)//divide the vector into two edge vector, and the sum of the division must <= than 1
{//tests passed in this method the edge counts in the triangle
    float v,u;
    float xba=b.x-a.x, xca=c.x-a.x, xpa=tt.x-a.x;
    float yba=b.y-a.y, yca=c.y-a.y, ypa=tt.y-a.y;
    float xba_yca_xca_yba=xba*yca-xca*yba;
    //compute v
    v=(ypa*xba-yba*xpa)/xba_yca_xca_yba;
    if(v<0) return 0;
    //compute u
    u=(ypa*xca-yca*xpa)/(-xba_yca_xca_yba);
    if(u<0) return 0;
    return u+v<=1;//test the sum
}

bool next_point(vector<tup> &ring,int &left,int &right,int &next,int sz)
{
    if(cmp(ring,left,right)) 
    {
        next=left;
        left=(left+1)%sz;
        return 1;
    }
    else 
    {
        next=right;
        right=(right-1+sz)%sz;
        return 0;
    }
}

//funs trans poly to poly_tri
poly_tri poly::triangulate()
{
    vector<tup> ring;//the now ring that i construct
    poly_tri after;
    after.id=id;
    after.up_right=up_right;
    after.down_left=down_left;
    int sz=tuples.size();

    int now=0;//the node becomes a circle list
    
    int FLAG_THE_FIRST_POINT=0;
    int uphill,downhill;//record the mark
    float max,min;//record the top and the hill
    for(int i=0;i!=sz;i++)//cut the strange angle and mark the flag
    {
        bool convex,strange;
        int a,b,c;
        if(i==0) {a=sz-1;b=0;c=1;}
        else if(i==sz-1) {a=sz-2;b=sz-1;c=0;}
        else {a=i-1;b=i;c=i+1;}
        //get the convex judge
        convex=((tuples[b].x-tuples[a].x)*(tuples[c].y-tuples[b].y)-\
        (tuples[c].x-tuples[b].x)*(tuples[b].y-tuples[a].y))>0;
        
        //get the strange judge.
        strange=(tuples[a].y<=tuples[b].y)&&(tuples[c].y<=tuples[b].y);

        if(convex&&strange)//exclude the special point
            after.cells.push_back(tri(id,tuples[a],tuples[b],tuples[c]));
        else//get the top and below tuples of the polygon 
        {
            tuples[i].flag=convex;//this place i gave the flag marking the convex
            ring.push_back(tuples[i]);
            if(FLAG_THE_FIRST_POINT==0)
            {
                max=tuples[i].y, min=tuples[i].y;  
                uphill=downhill=now;
                FLAG_THE_FIRST_POINT=1;
            }
            else
            {
                if(tuples[i].y<min)
                {min=tuples[i].y;downhill=now;}
                if(tuples[i].y>max)
                {max=tuples[i].y;uphill=now;}
            }
            now++;
        }  
    }

    //-----------------------------------------------------------------
    //now get the rest triangle splited
    int now_left,now_right;
    //begin to split
    stack<tup> path;
    int sz_new=ring.size();
    path.push(tuples[uphill]);now_left=(uphill+1)%sz_new;now_right=(uphill-1+sz_new)%sz_new;
    //because of counterclockwise, so the left size plus while the other minus
    bool side=cmp_complex(ring,now_left,now_right,sz_new,path);//side ==1 mines that the convexside now on the left
    bool this_side;int top;
    
    this_side=next_point(ring,now_left,now_right,top,sz_new);
    while(now_left!=now_right);//untill the meeting the the two sides
    {
        if(this_side!=side)//on the opposite side
        {
            tup temp=path.top();
            path.pop();
            after.cells.push_back(tri(id,ring[now],temp,path.top()));
            //get a new triangle and remove the lsit top
            if(path.empty())//if the non convext list empty
            this_side=next_point(ring,now_left,now_right,top,sz_new);
        }
        else//the same side
        {
            if(ring[top].flag)//if the convex
            {
                
                //get the triangle
                if(path.empty())//if the non convext list empty
                this_side=next_point(ring,now_left,now_right,top,sz_new);
            }
            else //if nonconvex added to the path
            {
                path.push(ring[top]);
                this_side=next_point(ring,now_left,now_right,top,sz_new);
            } 
        }
    }
    //devide the graph into two pieces and start to devide the rest graph
    return after;
}

