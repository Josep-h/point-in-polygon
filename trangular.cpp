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
    tup a,b,c;
    tri(){}
    tri(tup x,tup y,tup z):a(x),b(y),c(z){}
    bool test(tup tt);//fun test if a point is in a triangule
};

class poly{
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

