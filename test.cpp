#include<vector>
#include<string>
#include<iostream>
using namespace std;
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

int main()
{
    int sedge;
    cin>>sedge;
    vector<pair<double,double>> poly;
    for(int i=0;i!=sedge;i++)
    {
        double x,y;
        cin>>x>>y;
        poly.push_back(pair<double,double>(x,y));
    }
    Polygon out=parachange(poly,1);
    while(1)
    {
        int x,y;
        cin>>x>>y;
        tup test=tup(x,y);
        if(point_in_polygon(out,test))
        cout<<"in"<<endl;
        else cout<<"out"<<endl;
    }
    return 0;
}