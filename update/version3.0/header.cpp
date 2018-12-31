//#pragma once
#include"header.h"
#include<iostream>
using namespace std;
 unordered_map<polygon_id,TriPolygon> TriPolygon_map;
 unordered_map<polygon_id,Polygon> poly_map;
 unordered_map<point_id,tup> point_map;
 polygon_tree py_tree;
 point_tree pt_tree;
 vector<int> poly_ans;
 vector<int> point_ans;
 int Sz;
 Polygon *polygon_test_now;
 tup tup_test_now;
 TriPolygon *polygon_test_now2;

 unordered_map<polygon_id,Polygon>::iterator iter1;
 unordered_map<point_id,tup>::iterator iter2;
 interTree::interval_vector ans;

void polyTreeInsert(Polygon &py,int sz,int id)
{
    iter1=poly_map.find(id);
    MinMax bound;
    bound.max[0]=bound.min[0]=py[0].first;
    bound.max[1]=bound.min[1]=py[0].second;
    TYPE xtp,ytp;
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
    poly_map.insert(pair<polygon_id,Polygon>(id,py));
    py_tree.Insert(bound.min,bound.max,id);
    return ;
}

void polyTreeRemove(int id)
{
    Polygon one;
    poly_map[id]=one;
}

void pointTreeInsert(TYPE x,TYPE y,int id)
{
    TYPE mind[2],maxd[2];
    mind[0]=maxd[0]=x;
    mind[1]=maxd[1]=y;
    point_map[id]=tup(x,y);
    pt_tree.Insert(mind,maxd,id);
    return ;
}

void pointTreeRemove(int id)
{
    tup one;
    point_map[id]=one;
}

bool CallForPolygon(int id)//Myversion
{
    int ct=0,i=0,j,sz;
    TYPE  k,b,y;
    double xtp1,ytp1,xtp2;
    Polygon *polygon_in=&poly_map[id];//这里使用指针快了有1/4
    sz=(*polygon_in).size();
    tup *p=&tup_test_now;
    //int sz=polygon_in.size();
    for(;i<sz-1;i++)
    {
        j=i+1;
        //int s=(i+2)%sz;
        xtp1=(*polygon_in)[i].first;
        xtp2=(*polygon_in)[j].first;
        if((xtp1<(*p).x&&xtp2>(*p).x)\
        ||(xtp1>(*p).x&&xtp2<(*p).x))
        {
            
            //if(polygon_in[i].first==polygon_in[j].first)
            //continue;
            ytp1=(*polygon_in)[i].second;
            k=((*polygon_in)[j].second-ytp1)/(xtp2-xtp1);
            b=ytp1-xtp1*k;
            y=k*(*p).x+b;
            if(y>(*p).y)
            ct++;
        }
    }
    j=0;
        xtp1=(*polygon_in)[i].first;
        xtp2=(*polygon_in)[0].first;
        if((xtp1<(*p).x&&xtp2>(*p).x)\
        ||(xtp1>(*p).x&&xtp2<(*p).x))
        {
            ytp1=(*polygon_in)[i].second;
            k=((*polygon_in)[j].second-ytp1)/((*polygon_in)[j].first-xtp1);
            b=ytp1-xtp1*k;
            y=k*(*p).x+b;
            if(y>(*p).y)
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
        pair<TYPE,TYPE> k_b;
        xtp1=in[i].first;
        xtp2=in[j].first;
        ytp1=in[i].second;
        k_b.first=(in[j].second-ytp1)/(xtp2-xtp1);
        k_b.second=ytp1-xtp1*k_b.first;
        in_changed.push_back(interTree::interval(in[i].first,in[j].first,k_b));
    }
        double xtp1,xtp2,ytp1;
        pair<TYPE,TYPE> k_b;
        xtp1=in[sz-1].first;
        xtp2=in[0].first;
        ytp1=in[sz-1].second;
        k_b.first=(in[0].second-ytp1)/(xtp2-xtp1);
        k_b.second=ytp1-xtp1*k_b.first;
        in_changed.push_back(interTree::interval(in[sz-1].first,in[0].first,k_b));
    tree=interTree(move(in_changed),16,1);
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
    point_ans.clear();
    TriPolygon now=TriPolygon(py);
    polygon_test_now2=&now;
    TYPE xtp,ytp;
    TYPE mind[2],maxd[2];
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
    pt_tree.Search(mind,maxd,CallForPoint);
    return ;
}

