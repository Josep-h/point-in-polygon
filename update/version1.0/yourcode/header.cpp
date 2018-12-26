#pragma once
#include"header.h"
#include<iostream>
#define delta 0.00001
using namespace std;
map<polygon_id,Polygon> poly_map;
polygon_tree py_tree;

map<point_id,Stup> point_map;
point_tree pt_tree;


vector<int> poly_ans;
Polygon polygon_test_now;

vector<int> point_ans;
tup tup_test_now;

void polyTreeInsert(Polygon py)
{
    map<polygon_id,Polygon>::iterator iter=poly_map.find(py.id);
    cout<<py.id<<endl;//DEBUG
    if(iter!=poly_map.end()) return;
    poly_map.insert(pair<polygon_id,Polygon>(py.id,py));
    py_tree.Insert(py.min,py.max,py.id);
    return ;
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
    cout<<pt.id<<endl;//DEBUG
    if(iter!=point_map.end()) return ;
    point_map.insert(pair<point_id,Stup>(pt.id,pt));
    pttree.Insert(pt.min,pt.max,pt.id);
    return ;
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
    if(point_in_polygon(poly_map[id],tup_test_now))
    poly_ans.push_back(id);
    cout<<"Checking: "<<id<<endl;//DEBUG
    return 1;
}

bool CallForPoint(point_id id)
{
    map<point_id,Stup>::iterator iter=point_map.find(id);
    cout<<"Checking: "<<id<<endl;      //DEBUG
    if(point_in_polygon(polygon_test_now,iter->second.p))
    point_ans.push_back(id);
    return 1;
}

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


