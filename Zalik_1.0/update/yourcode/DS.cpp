#include"DS.h"
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


bool point_in_polygon(Polygon &poly,tup p)
{
    int ct=0;
    int sz=poly.edges.size();
    for(int i=0;i!=sz;i++)
    {
        if((poly.edges[i].bgn.x<=p.x&&poly.edges[i].nd.x>=p.x)||(poly.edges[i].bgn.x>=p.x&&poly.edges[i].nd.x<=p.x))
        {
            float y=poly.edges[i].k*p.x+poly.edges[i].b;
            if(y>p.y)
            ct++;
        }
    }
    return ct%2;
}

Polygon parachange(vector<pair<double,double> > &polygon_in,int id)
{
    Polygon out;
    int sz=polygon_in.size();
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
    tup one;
    one.x=polygon_in[sz-1].first;
    one.y=polygon_in[sz-1].second;
    tup two;
    two.x=polygon_in[0].first;
    two.y=polygon_in[0].second;
    out.edges.push_back(edge(one,two));
    out.id=id;
    return out;
}


