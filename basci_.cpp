#include<vector>
#include<algorithm>
#include<stack>
#include<math.h>
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
class edge{
    public:
    tup bgn;
    tup nd;
    float k;
    float b;
    edge(){}
    edge(tup one,tup two);
};
class MarkQuasiPoint{
    public:
    float dis;//mark the distance between the quasi point to the quary point
    edge e; //mark the edge that the quasi point from
    edge another;
    tup quasi_point;//mark the quasi point
    MarkQuasiPoint(){}
    MarkQuasiPoint(float dis,edge e,tup q):dis(dis),e(e),quasi_point(q){}
};
edge::edge(tup one,tup two)
{
    bgn=one,nd=two;
    if(one.x==two.x)
    k=100;//if the same
    k=(one.y-two.y)/(one.x-two.x);
    b=one.y-k*one.x;
}


