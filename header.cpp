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

map<int,MinMax> min_max;

void polyTreeInsert(Polygon py,int id)
{
    map<polygon_id,Polygon>::iterator iter=poly_map.find(id);
    //cout<<id<<endl;//DEBUG
    if(iter!=poly_map.end()) return;
    double xmax,xmin,ymin,ymax;
    MinMax bound;
    int sz=py.size();
    xmin=xmax=py[0].first;
    ymin=ymax=py[0].second;
    for(int i=1;i<sz;i++)
    {
        if(py[i].first>xmax)
            xmax=py[i].first;
        else if(py[i].first<xmin)
            xmin=py[i].first;
        if(py[i].second>ymax)
            ymax=py[i].second;
        else if(py[i].second<ymin)
            ymin=py[i].second;
    }
    bound=MinMax(xmin,ymin,xmax,ymax);
    poly_map.insert(pair<polygon_id,Polygon>(id,py));
    min_max[id]=bound;
    py_tree.Insert(bound.min,bound.max,id);
    return ;
}

void polyTreeRemove(polygon_tree& pytree,int id)
{
    map<polygon_id,Polygon>::iterator iter=poly_map.find(id);
    if(iter!=poly_map.end())
    {
        poly_map.erase(iter);
        pytree.Remove(min_max[id].min,min_max[id].max,id);
    }
}

void pointTreeInsert(point_tree& pttree,Stup pt)
{
    map<point_id,Stup>::iterator iter=point_map.find(pt.id);
    //cout<<pt.id<<endl;//DEBUG
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
    if(point_in_polygon_new(poly_map[id],tup_test_now))
    poly_ans.push_back(id);
    //cout<<"Checking: "<<id<<endl;//DEBUG
    return 1;
}

bool CallForPoint(point_id id)
{
    map<point_id,Stup>::iterator iter=point_map.find(id);
    //cout<<"Checking: "<<id<<endl;      //DEBUG
    if(point_in_polygon_new(polygon_test_now,iter->second.p))
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
/*
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
*/
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

void QuaryPolygon(int sz,Polygon polygon)
{
    vector<int> ans;
    point_ans=ans;
    polygon_test_now=polygon;
    double xmax,xmin,ymin,ymax;
    MinMax bound;
    xmax=xmin=polygon[0].first;
    ymin=ymax=polygon[0].second;
    for(int i=1;i<sz;i++)
    {
        if(polygon[i].first>xmax)
            xmax=polygon[i].first;
        else if(polygon[i].first<xmin)
            xmin=polygon[i].first;
        if(polygon[i].second>ymax)
            ymax=polygon[i].second;
        else if(polygon[i].second<ymin)
            ymin=polygon[i].second;
    }
    bound.min[0]=xmin;bound.min[1]=ymin;
    bound.max[0]=xmax;bound.max[1]=ymax;
    pt_tree.Search(bound.min,bound.max,CallForPoint);
    return;
}

