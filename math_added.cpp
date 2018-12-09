#include<math.h>
#include"basci_.cpp"

using namespace std;
float dou(float x)
{
    return pow(x,2);
}

float edge_x(edge e,float x)//compute f(x)
{
    float y=x*e.k+e.b;
    return y;
}

float area2(tup v0,tup v1,tup v2)//conpute the area of a triangle
{
    return (v1.x-v0.x)*(v2.y-v1.y)-(v1.y-v0.y)*(v2.x-v1.x);
}

//show the distance of two tuples
float Distance_P_P(tup one,tup two)
{
    return sqrt(dou(one.x-two.x)+dou(one.y-two.y));
}
//show the distance from an edge to a point
MarkQuasiPoint Distance_P_E(tup point,edge e)
{
    float dis1=Distance_P_P(point,e.bgn);
    float dis2=Distance_P_P(point,e.nd);
    float dis3=area2(point,e.bgn,e.nd)/Distance_P_P(e.bgn,e.nd);
    MarkQuasiPoint ans;
    if(dis1<dis2&&dis1<dis3)
    {
        return ans=MarkQuasiPoint(dis1,e,e.bgn);
    }
    if(dis2<dis1&&dis2<dis3)
    {
        return ans=MarkQuasiPoint(dis2,e,e.nd);
    }
    tup near;
    float lamda_up=(e.nd.x-e.bgn.x)*(point.x-e.bgn.x)+(e.nd.y-e.bgn.y)*(point.y-e.bgn.y);
    float lamda_dowm=(e.nd.x-e.bgn.x)*(e.nd.x-e.bgn.x)+(e.nd.y-e.bgn.y)*(e.nd.y-e.bgn.y);
    float lamda=lamda_up/lamda_dowm;
    near.x=lamda*(e.nd.x-e.bgn.x)+e.bgn.x;
    near.y=lamda*(e.nd.y-e.bgn.y)+e.bgn.y;
    return ans=MarkQuasiPoint(dis3,e,near);
}

//judge if a point on the left side of a edge
bool IsOnTheLeftSide(tup p,edge e)
{
    return (area2(e.bgn,e.nd,p)>0);
}
bool IsOnTheRightSide(tup p,edge e)
{
    return !IsOnTheLeftSide(p,e);
}
