#pragma once
#include"header.h"
#include<iostream>
using namespace std;
 unordered_map<polygon_id,TriPolygon> TriPolygon_map;
 unordered_map<point_id,tup> point_map;
 unordered_map<polygon_id,kbPolygon> kbPolygon_map;
 kdtree pt_tree;
 polygon_tree py_tree;

 vector<int> poly_ans;
 vector<int> point_ans;

 kbPolygon *polygon_test_now;
 tup tup_test_now;
 TriPolygon *polygon_test_now2;

 unordered_map<polygon_id,Polygon>::iterator iter1;
 unordered_map<point_id,tup>::iterator iter2;
 interTree::interval_vector ans;
vector<int> pans(10000);
void polyTreeInsert(Polygon &py,int sz,int id)
{
    kbPolygon one=kbPolygon(py);
    kbPolygon_map[id]=one;
    py_tree.Insert(one.bound.min,one.bound.max,id);
    return ;
}

void polyTreeRemove(int id)
{
    kbPolygon one;
    kbPolygon_map[id]=one;
}

void pointTreeInsert(TYPE x,TYPE y,int id)
{
    double pos[]={x,y};
    point_map[id]=tup(x,y);
    pt_tree.insert(pos,id,pt_tree.head);
    return ;
}

void pointTreeRemove(int id)
{
    tup one=tup(0,0);
    point_map[id]=one;
}

bool CallForPolygon(int id)//Myversion
{
    int ct=0,sz;
    static TYPE2 k,b,y;
    kbPolygon *polygon_in=&kbPolygon_map[id];
    sz=(*polygon_in).sz;
    tup p=tup_test_now;
    for(int i=0;i!=sz;i++)
    {
        if(p.x<(*polygon_in).left_right[i].first||p.x>(*polygon_in).left_right[i].second) continue;
        k=(*polygon_in).k_b_vec[i].first,b=(*polygon_in).k_b_vec[i].second;
        y=k*p.x+b;
        if(y>p.y)
        ct++;
    }
    if(ct%2)
    poly_ans.push_back(id);
    return 1;
}

void QuaryPoint(TYPE x,TYPE y)
{
    TYPE mind[2],maxd[2];
    mind[0]=maxd[0]=(tup_test_now).x=x;
    mind[1]=maxd[1]=(tup_test_now).y=y;
    poly_ans.clear();
    py_tree.Search(mind,maxd,CallForPolygon);
    return;
}


TriPolygon::TriPolygon(Polygon &in)
{
    static interTree::interval_vector in_changed;
    in_changed.clear();
    int sz=in.size();
    for(int i=0;i<sz-1;i++)
    {
        int j=i+1;
        double xtp1,xtp2,ytp1;
        pair<double,double> k_b;
        xtp1=in[i].first;
        xtp2=in[j].first;
        ytp1=in[i].second;
        k_b.first=(in[j].second-ytp1)/(xtp2-xtp1);
        k_b.second=ytp1-xtp1*k_b.first;
        in_changed.push_back(interTree::interval(in[i].first,in[j].first,k_b));
    }
        double xtp1,xtp2,ytp1;
        pair<double,double> k_b;
        xtp1=in[sz-1].first;
        xtp2=in[0].first;
        ytp1=in[sz-1].second;
        k_b.first=(in[0].second-ytp1)/(xtp2-xtp1);
        k_b.second=ytp1-xtp1*k_b.first;
        in_changed.push_back(interTree::interval(in[sz-1].first,in[0].first,k_b));
    tree=interTree(move(in_changed),16,1);
}
kbPolygon::kbPolygon(Polygon &in)
{
    sz=in.size();
    k_b_vec=new pair<double,double>[sz];
    left_right=new pair<double,double>[sz];
    double xtp,ytp;
    bound.max[0]=bound.min[0]=in[sz-1].first;
    bound.max[1]=bound.min[1]=in[sz-1].second;
    for(int i=0;i<sz-1;i++)
    {
        xtp=in[i].first,ytp=in[i].second;
        if(xtp>bound.max[0])
            bound.max[0]=xtp;
        else if(xtp<bound.min[0])
            bound.min[0]=xtp;
        if(ytp>bound.max[1])
            bound.max[1]=ytp;
        else if(ytp<bound.min[1])
            bound.min[1]=ytp;
        int j=i+1;
        double xtp1,xtp2,ytp1;
        pair<double,double> k_b;
        xtp1=in[i].first;
        xtp2=in[j].first;
        ytp1=in[i].second;
        k_b.first=(in[j].second-ytp1)/(xtp2-xtp1);
        k_b.second=ytp1-xtp1*k_b.first;
        k_b_vec[i]=k_b;
        if(xtp1>xtp2) {left_right[i].first=xtp2;left_right[i].second=xtp1;}
        else {left_right[i].first=xtp1;left_right[i].second=xtp2;}
    }
        double xtp1,xtp2,ytp1;
        pair<double,double> k_b;
        xtp1=in[sz-1].first;
        xtp2=in[0].first;
        ytp1=in[sz-1].second;
        k_b.first=(in[0].second-ytp1)/(xtp2-xtp1);
        k_b.second=ytp1-xtp1*k_b.first;
        k_b_vec[sz-1]=k_b;
        if(xtp1>xtp2) {left_right[sz-1].first=xtp2;left_right[sz-1].second=xtp1;}
        else {left_right[sz-1].first=xtp1;left_right[sz-1].second=xtp2;}
}

bool CallForPoint(int id)
{
    int ct=0;
    static TYPE k,b,y;
    tup p=point_map[id];
    ans.clear();
    (*polygon_test_now2).tree.findOverlapping(p.x,p.x,ans);
    int sz=ans.size();
    for(int i=0;i!=sz;i++)
    {
        k=ans[i].value.first,b=ans[i].value.second;
        y=k*p.x+b;
        if(y>p.y)
        ct++;
    }
    if(ct%2)
    point_ans.push_back(id);
    return 1;
}

void QuaryPolygon(int sz,Polygon &py)
{
    TriPolygon now=TriPolygon(py);
    polygon_test_now2=&now;
    point_ans.clear();
    TYPE mind[2],maxd[2];
    TYPE xtp,ytp;
    mind[0]=maxd[0]=py[0].first;
    mind[1]=maxd[1]=py[0].second;
    for(int i=1;i<sz;i++)
    {
        xtp=py[i].first,ytp=py[i].second;
        if(xtp>maxd[0])
            maxd[0]=xtp;
        else if(xtp<mind[0])
            mind[0]=xtp;
        if(ytp>maxd[1])
            maxd[1]=ytp;
        else if(ytp<mind[1])
            mind[1]=ytp;
    }
    pt_tree.search(mind,maxd,pt_tree.head);
    return ;
}
