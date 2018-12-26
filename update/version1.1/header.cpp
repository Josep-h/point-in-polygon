#pragma once
#include"header.h"
#include<iostream>
#define delta 0.00001
using namespace std;
unordered_map<polygon_id,Polygon> poly_map;
polygon_tree py_tree;

unordered_map<point_id,Stup> point_map;
point_tree pt_tree;

vector<int> poly_ans;
Polygon polygon_test_now;

vector<int> point_ans;
tup tup_test_now;

unordered_map<int,MinMax> min_max;

void polyTreeInsert(Polygon py,int id)
{
    unordered_map<polygon_id,Polygon>::iterator iter=poly_map.find(id);
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

void polyTreeRemove(int id)
{
    unordered_map<polygon_id,Polygon>::iterator iter=poly_map.find(id);
    if(iter==poly_map.end())
    return;
    poly_map.erase(iter);
    py_tree.Remove(min_max[id].min,min_max[id].max,id);
}

void pointTreeInsert(int id,double x,double y)
{
    unordered_map<point_id,Stup>::iterator iter=point_map.find(id);
    //cout<<pt.id<<endl;//DEBUG
    Stup one=Stup(tup(x,y));
    one.id=id;
    if(iter!=point_map.end()) return ;
    point_map.insert(pair<point_id,Stup>(one.id,one));
    pt_tree.Insert(one.min,one.max,one.id);
    return ;
}

void pointTreeRemove(int id)
{
    unordered_map<point_id,Stup>::iterator iter=point_map.find(id);
    if(iter==point_map.end())
    return;
    Stup pt=iter->second;
    point_map.erase(iter);
    pt_tree.Remove(pt.min,pt.max,pt.id);
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
    unordered_map<point_id,Stup>::iterator iter=point_map.find(id);
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

void QuaryPoint(double x,double y)
{
    tup_test_now=tup(x,y);
    Stup test2=Stup(tup_test_now);
    vector<int> ans;
    poly_ans=ans;
    py_tree.Search(test2.min,test2.max,CallForPolygon);
    return;
}
