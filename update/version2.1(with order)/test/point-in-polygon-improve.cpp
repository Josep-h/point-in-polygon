#include<vector>
#include<iostream>
using namespace std;
#define delta 0.000001
class tup{//def of the tuple
    public:
    double x;
    double y;
    tup(){}
    tup(double x,double y):x(x),y(y){}
    bool operator < (const tup &now) const{
        return y<now.y;
    }
    bool operator == (const tup &now) const{
        return y==now.y&&x==now.x;
    }
};

class Stup{//special tup with id and rectangle
    public:
    tup p;
    int id;
    double min[2];
    double max[2];
    Stup(){}
    Stup(tup);
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


class Polygon{
    public:
    vector<edge> edges;
    int id;
    double min[2];
    double max[2];
    Polygon(){}
};
Stup::Stup(tup pt)
{
    p=pt;
    min[0]=pt.x-delta;
    min[1]=pt.y-delta;
    max[0]=pt.x+delta;
    max[1]=pt.y+delta;
}

edge::edge(tup one,tup two)
{
    bgn=one,nd=two;
    if(one.x==two.x)
    k=100;//if the same
    k=(one.y-two.y)/(one.x-two.x);
    b=one.y-k*one.x;
}
bool point_in_polygon(Polygon &poly,tup p)//不需要这一次转换?
{
    int ct=0;
    int sz=poly.edges.size();
    for(int i=0;i!=sz;i++)
    {
        if((poly.edges[i].bgn.x<=p.x&&poly.edges[i].nd.x>=p.x)\
        ||(poly.edges[i].bgn.x>=p.x&&poly.edges[i].nd.x<=p.x))
        {
            float y=poly.edges[i].k*p.x+poly.edges[i].b;
            if(y>=p.y)
            ct++;
            
                if((poly.edges[i].nd.x==p.x)\
                &&((poly.edges[(i+1)%sz].nd.x<p.x)!=(poly.edges[i].bgn.x<p.x)))
                ct--;    
        }
    }
    return ct%2;
}

Polygon parachange(vector<pair<double,double> > &polygon_in,int id)
{
    Polygon out;
    int sz=polygon_in.size();
    double ymax=polygon_in[0].second,xmax=polygon_in[0].first;
    double ymin=polygon_in[0].second,xmin=polygon_in[0].first;
    for(int i=0;i!=sz-1;i++)
    {
        tup one;
        tup two;
        one.x=polygon_in[i].first;
        one.y=polygon_in[i].second;
        two.x=polygon_in[i+1].first;
        two.y=polygon_in[i+1].second;
        out.edges.push_back(edge(one,two));
    }
    for(int i=0;i!=sz;i++)
    {
        if(polygon_in[i].first>xmax)
            xmax=polygon_in[i].first;
        else if(polygon_in[i].first<xmin)
            xmin=polygon_in[i].first;
        if(polygon_in[i].second>ymax)
            ymax=polygon_in[i].second;
        else if(polygon_in[i].second<ymin)
            ymin=polygon_in[i].second;
    }
    tup one;
    one.x=polygon_in[sz-1].first;
    one.y=polygon_in[sz-1].second;
    tup two;
    two.x=polygon_in[0].first;
    two.y=polygon_in[0].second;
    out.edges.push_back(edge(one,two));
    out.id=id;
    out.max[0]=xmax;out.max[1]=ymax;//这里赋给矩形范围
    out.min[0]=xmin;out.min[1]=ymin;
    return out;
}

bool point_in_polygon_new(vector<pair<double,double> > &polygon_in,tup p)
{
    int ct=0;
    int sz=polygon_in.size();
    for(int i=0;i!=sz;i++)
    {
        int j=(i+1)%sz;
        int s=(i+2)%sz;
        if((polygon_in[i].first<=p.x&&polygon_in[j].first>=p.x)\
        ||(polygon_in[i].first>=p.x&&polygon_in[j].first<=p.x))
        {
            if(polygon_in[i].first==polygon_in[j].first)
            continue;
            double k=(polygon_in[j].second-polygon_in[i].second)/(polygon_in[j].first-polygon_in[i].first);
            double b=polygon_in[i].second-polygon_in[i].first*k;
            double y=k*p.x+b;
            if(y>=p.y)
            ct++;
            
                if((polygon_in[j].first==p.x)\
                &&((polygon_in[s].first<p.x)!=(polygon_in[i].first<p.x)))
                ct--;    
        }
    }
    return ct%2;
}