#include<vector>

using namespace std;

class tup{//def of the tuple
    public:
    float x;
    float y;
    tup(){}
    tup(float x,float y):x(x),y(y){}
};

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
    vector<tup> cons;
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
bool tri::test(tup tt)
{

}

//funs trans polyy to poly_tri
poly_tri poly::triangulate()
{
    poly_tri after;
    after.id=id;
    after.up_right=up_right;
    after.down_left=down_left;
    //cut the strange angle first

    //sort the tuple again by y

    //devide the graph into two pieces and start to devide the rest graph
    return after;
}

