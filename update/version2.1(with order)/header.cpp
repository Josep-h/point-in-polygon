#pragma once
#include"header.h"
#include<iostream>
using namespace std;
 unordered_map<polygon_id,TriPolygon> TriPolygon_map;
 //unordered_map<polygon_id,Polygon> poly_map;
 unordered_map<point_id,tup> point_map;
 unordered_map<polygon_id,kbPolygon> kbPolygon_map;
 point_tree pt_tree;
 polygon_tree py_tree;
 unordered_map<int,MinMax> min_max;

 int Sz;
 vector<int> poly_ans;
 vector<int> point_ans;

 kbPolygon *polygon_test_now;
 tup tup_test_now;
 TriPolygon *polygon_test_now2;

 unordered_map<polygon_id,Polygon>::iterator iter1;
 unordered_map<point_id,tup>::iterator iter2;
 interTree::interval_vector ans;

void polyTreeInsert1(Polygon &py,int sz,int id)
{
    //if(iter!=poly_map.end()) return;
    //TYPE max[2],min[2];
    kbPolygon one=kbPolygon(py);
    kbPolygon_map[id]=one;
    //min_max[id]=bound;
    py_tree.Insert(one.bound.min,one.bound.max,id);
    return ;
}

void polyTreeRemove1(int id)
{
    kbPolygon one;
    kbPolygon_map[id]=one;
    //TYPE mind[2],maxd[2];
    //mind[0]=bound.min[0];mind[1]=bound.min[1];
    //maxd[0]=bound.max[0];maxd[1]=bound.max[1];
    //py_tree.Remove(mind,maxd,id);
}

void pointTreeInsert(TYPE x,TYPE y,int id)
{
    iter2=point_map.find(id);
    //Stup one=Stup(tup(x,y));
    if(iter2!=point_map.end()) return ;
    TYPE mind[2],maxd[2];
    mind[0]=maxd[0]=x;
    mind[1]=maxd[1]=y;
    point_map[id]=tup(x,y);
    pt_tree.Insert(mind,maxd,id);
    return ;
}

void pointTreeRemove(int id)
{
    tup one=tup(0,0);
    point_map[id]=one;
   
    //mind[0]=maxd[0]=iter2->second.x;
    //mind[1]=maxd[1]=iter2->second.y;
    //pt_tree.Remove(mind,maxd,id);
}

bool CallForPolygon1(int id)//Myversion
{
    int ct=0,sz;
    static TYPE2 k,b,y,xtp1,ytp1,xtp2;
    kbPolygon *polygon_in=&kbPolygon_map[id];//这里使用指针快了有1/4
    sz=(*polygon_in).sz;
    tup p=tup_test_now;
    //int sz=polygon_in.size();
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
    //cout<<"Checking: "<<id<<endl;//DEBUG
    return 1;
}
/*
bool CallForPolygon(int id)//The other version
{
    if(point_in_polygon_new(poly_map[id],tup_test_now))
    poly_ans.push_back(id);
    //cout<<"Checking: "<<id<<endl;//DEBUG
    return 1;
}*/
bool CallForPoint1(int id)
{
    //cout<<"Checking: "<<id<<endl;      //DEBUG
    int ct=0,j,sz=Sz;
    static TYPE k,b,y;
    tup p=point_map[id];
    //cout<<p.x<<" "<<p.y<<endl;
    //int sz=polygon_in.size();
    for(int i=0;i!=sz;i++)
    {
        k=(*polygon_test_now).k_b_vec[i].first,b=(*polygon_test_now).k_b_vec[i].second;
        y=k*p.x+b;
        if(y>p.y)
        ct++;
    }

    if(ct%2)
    point_ans.push_back(id);
    return 1;
}

void QuaryPolygon1(int sz,Polygon &py)
{
    Polygon one;
    for(int i=0;i!=sz;i++)
    {
        one.push_back(py[i]);
    }
    //vector<int> ans;
    point_ans.clear();
    //polygon_test_now=&one;
    TYPE xmax,xmin,ymin,ymax,xtp,ytp;
    TYPE mind[2],maxd[2];
    xmax=xmin=py[0].first;
    ymin=ymax=py[0].second;
    for(int i=1;i<sz;i++)
    {
        xtp=py[i].first,ytp=py[i].second;
        if(xtp>xmax)
            xmax=xtp;
        else if(xtp<xmin)
            xmin=xtp;
        if(ytp>ymax)
            ymax=ytp;
        else if(ytp<ymin)
            ymin=ytp;
    }
    mind[0]=xmin;mind[1]=ymin;
    maxd[0]=xmax;maxd[1]=ymax;
    Sz=sz;
    pt_tree.Search(mind,maxd,CallForPoint1);
    return ;
}

void QuaryPoint1(TYPE x,TYPE y)
{
    TYPE mind[2],maxd[2];
    mind[0]=maxd[0]=(tup_test_now).x=x;
    mind[1]=maxd[1]=(tup_test_now).y=y;
    //Stup test2=Stup(tup_test_now);
    //vector<int> ans;
    poly_ans.clear();
    py_tree.Search(mind,maxd,CallForPolygon1);
    return;
}


TriPolygon::TriPolygon(Polygon &in)
{
    interTree::interval_vector in_changed;
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

void polyTreeInsert2(Polygon &py,int sz,int id)
{

    MinMax bound;
    bound.max[0]=bound.min[0]=py[0].first;
    bound.max[1]=bound.min[1]=py[0].second;
    static TYPE2 xtp,ytp;
    for(int i=1;i<sz;i++)
    {
        xtp=py[i].first,ytp=py[i].second;
        if(xtp>bound.max[0])
            bound.max[0]=xtp;
        else if(xtp<bound.min[0])
            bound.min[0]=xtp;
        if(ytp>bound.max[1])
            bound.max[1]=ytp;
        else if(ytp<bound.min[1])
            bound.min[1]=ytp;
    }
   
    TriPolygon one=TriPolygon(py);
    TriPolygon_map[id]=one;
    //min_max[id]=bound;
    py_tree.Insert(bound.min,bound.max,id);
    return ;
}

void polyTreeRemove2(int id)
{
    //iter1=poly_map.find(id);
    /*if(iter1==poly_map.end())
    return;*/
    //poly_map.erase(iter1);
    //TYPE mind[2],maxd[2];
    //mind[0]=bound.min[0];mind[1]=bound.min[1];
    //maxd[0]=bound.max[0];maxd[1]=bound.max[1];
    //py_tree.Remove(mind,maxd,id);
}

bool CallForPolygon2(int id)//Myversion
{
    int ct=0,sz;
    static TYPE2 k,b,y;
    TriPolygon *now=&TriPolygon_map[id];
    tup *p=&tup_test_now;
    ans.clear();
    //vector<Interval<double,edge>> ans= (*now).tree.findOverlapping(tup_test_now.x,tup_test_now.x);
    (*now).tree.findOverlapping(tup_test_now.x,tup_test_now.x,ans);
    sz=ans.size();
    for(int i=0;i!=sz;i++)
    {
        k=ans[i].value.first,b=ans[i].value.second;
        y=k*(*p).x+b;
        if(y>(*p).y)
        ct++;
    }
    if(ct%2)
    poly_ans.push_back(id);
    //cout<<"Checking: "<<id<<endl;//DEBUG
    return 1;
}

bool CallForPoint2(int id)
{
    //cout<<"Checking: "<<id<<endl;      //DEBUG
    int ct=0;
    static TYPE k,b,y;
    tup p=point_map[id];
    //cout<<p.x<<" "<<p.y<<endl;
    ans.clear();
    (*polygon_test_now2).tree.findOverlapping(p.x,p.x,ans);
    int sz=ans.size();
    //int sz=polygon_in.size();
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

void QuaryPolygon2(int sz,Polygon &py)
{
    //vector<int> ans;
    point_ans.clear();
    TriPolygon now=TriPolygon(py);
    polygon_test_now2=&now;
    TYPE xmax,xmin,ymin,ymax,xtp,ytp;
    TYPE mind[2],maxd[2];
    xmax=xmin=py[0].first;
    ymin=ymax=py[0].second;
    for(int i=1;i<sz;i++)
    {
        xtp=py[i].first,ytp=py[i].second;
        if(xtp>xmax)
            xmax=xtp;
        else if(xtp<xmin)
            xmin=xtp;
        if(ytp>ymax)
            ymax=ytp;
        else if(ytp<ymin)
            ymin=ytp;
    }
    mind[0]=xmin;mind[1]=ymin;
    maxd[0]=xmax;maxd[1]=ymax;
    Sz=sz;
    pt_tree.Search(mind,maxd,CallForPoint2);
    return ;
}

void QuaryPoint2(TYPE x,TYPE y)
{
    TYPE mind[2],maxd[2];
    mind[0]=maxd[0]=(tup_test_now).x=x;
    mind[1]=maxd[1]=(tup_test_now).y=y;
    //Stup test2=Stup(tup_test_now);
    //vector<int> ans;
    poly_ans.clear();
    py_tree.Search(mind,maxd,CallForPolygon2);
    return;
}

