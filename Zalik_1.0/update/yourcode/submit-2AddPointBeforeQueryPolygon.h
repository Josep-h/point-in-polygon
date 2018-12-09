#ifndef DATASTRUCTUREPROJECT_SUBMIT_2ADDPOINTBEFOREQUERYPOLY_H
#define DATASTRUCTUREPROJECT_SUBMIT_2ADDPOINTBEFOREQUERYPOLY_H

#include<vector>
#include<string>
#define delta 0.001
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

class Stup{//special tup with id and rectangle
    public:
    tup p;
    int id;
    double min[2];
    double max[2];
    Stup(){}
    Stup(tup);
};

Stup::Stup(tup pt)
{
    p=pt;
    min[0]=pt.x-delta;
    min[1]=pt.y-delta;
    max[0]=pt.x+delta;
    max[1]=pt.y+delta;
}

class edge{
    public:
    tup bgn;
    tup nd;
    float k;
    float b;
    edge(){}
    edge(tup one,tup two);
};

edge::edge(tup one,tup two)
{
    bgn=one,nd=two;
    if(one.x==two.x)
    k=100;//if the same
    k=(one.y-two.y)/(one.x-two.x);
    b=one.y-k*one.x;
}


class Polygon{
    public:
    vector<edge> edges;
    int id;
    double min[2];
    double max[2];
    Polygon(){}
};

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


//全局变量们
map<polygon_id,Polygon> poly_map;
polygon_tree py_tree;

map<point_id,Stup> point_map;
point_tree pt_tree;


vector<int> poly_ans;
Polygon polygon_test_now;

vector<int> point_ans;
tup tup_test_now;

#include"RTree.h"
#include<map>
typedef int polygon_id;
typedef int point_id;
using namespace std;

typedef RTree<polygon_id,double,2,double> polygon_tree;
typedef RTree<point_id,double,2,double> point_tree;


void polyTreeInsert(polygon_tree& pytree,Polygon py)
{
    map<polygon_id,Polygon>::iterator iter=poly_map.find(py.id);
    if(iter!=poly_map.end()) return;
    poly_map.insert(pair<polygon_id,Polygon>(py.id,py));
    pytree.Insert(py.min,py.max,py.id);
}

void polyTreeRemove(polygon_tree& pytree,Polygon py)
{
    map<polygon_id,Polygon>::iterator iter=poly_map.find(py.id);
    if(iter!=poly_map.end())
    {
        poly_map.erase(iter);
        pytree.Remove(py.min,py.max,py.id);
    }
}

void pointTreeInsert(point_tree& pttree,Stup pt)
{
    map<point_id,Stup>::iterator iter=point_map.find(pt.id);
    if(iter!=point_map.end()) return ;
    point_map.insert(pair<point_id,Stup>(pt.id,pt));
    pttree.Insert(pt.min,pt.max,pt.id);
}

void pointTreeRemove(point_tree& pttree,Stup pt)
{
    map<point_id,Stup>::iterator iter=point_map.find(pt.id);
    if(iter!=point_map.end())
    {
        point_map.erase(iter);
        pttree.Remove(pt.min,pt.max,pt.id);
    }
}

bool CallForPolygon(polygon_id id)
{
    map<polygon_id,Polygon>::iterator iter=poly_map.find(id);
    if(point_in_polygon(iter->second,tup_test_now))
    poly_ans.push_back(id);
    return 1;
}

bool CallForPoint(point_id id)
{
    map<point_id,Stup>::iterator iter=point_map.find(id);
    if(point_in_polygon(polygon_test_now,iter->second.p))
    point_ans.push_back(id);
    return 1;
}


void SetEnvironmentFromAddPointBeforeQueryPolygon();

void AddPointFromAddPointBeforeQueryPolygon(int id, double x, double y);

std::vector<int> QueryPolygonFromAddPointBeforeQueryPolygon(int n, std::vector<std::pair<double, double> > polygon);

#endif //DATASTRUCTUREPROJECT_SUBMIT_2ADDPOINTBEFOREQUERYPOLY_H
