#pragma once
#include"header.h"
#include<iostream>
using namespace std;
 //unordered_map<polygon_id,TriPolygon> TriPolygon_map;
 unordered_map<polygon_id,Polygon> poly_map;
 unordered_map<point_id,tup> point_map;
 point_tree pt_tree;
 polygon_tree py_tree;
 //unordered_map<int,MinMax> min_max;

 int Sz;
 vector<int> poly_ans(10000);
 vector<int> point_ans(10000);
 myVec mpoly_ans(10000);
 myVec mpoint_ans(10000);

 Polygon *polygon_test_now;
 tup tup_test_now;
 TriPolygon *polygon_test_now2;

 unordered_map<polygon_id,Polygon>::iterator iter1;
 unordered_map<point_id,tup>::iterator iter2;
 interTree::interval_vector ans;
 interTree::interval_vector in_changed;
void polyTreeInsert1(Polygon &py,int sz,int id)
{
    MinMax bound;
    bound.max[0]=bound.min[0]=py[0].first;
    bound.max[1]=bound.min[1]=py[0].second;
    TYPE2 xtp,ytp;
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
    poly_map[id]=py;
    py_tree.Insert(bound.min,bound.max,id);
    return ;
}

void pointTreeInsert(TYPE x,TYPE y,int id)
{
    TYPE mind[2],maxd[2];
    point_map[id].x=mind[0]=maxd[0]=x;
    point_map[id].y=mind[1]=maxd[1]=y;
    pt_tree.Insert(mind,maxd,id);
    return ;
}

bool CallForPolygon1(int id)
{
    int ct=0,i=0,j,sz;
    TYPE2 k,b,y,xtp1,ytp1,xtp2;
    Polygon *polygon_in=&poly_map[id];
    sz=(*polygon_in).size();
    tup *p=&tup_test_now;
    for(;i<sz-1;i++)
    {
        j=i+1;
        xtp1=(*polygon_in)[i].first;
        xtp2=(*polygon_in)[j].first;
        if((xtp1<(*p).x&&xtp2>(*p).x)\
        ||(xtp1>(*p).x&&xtp2<(*p).x))
        {
            ytp1=(*polygon_in)[i].second;
            k=((*polygon_in)[j].second-ytp1)/(xtp2-xtp1);
            b=ytp1-xtp1*k;
            y=k*(*p).x+b;
            if(y>(*p).y)
            ct++;
        }
    }
        xtp1=(*polygon_in)[i].first;
        xtp2=(*polygon_in)[0].first;
        if((xtp1<(*p).x&&xtp2>(*p).x)\
        ||(xtp1>(*p).x&&xtp2<(*p).x))
        {
            ytp1=(*polygon_in)[i].second;
            k=((*polygon_in)[0].second-ytp1)/((*polygon_in)[0].first-xtp1);
            b=ytp1-xtp1*k;
            y=k*(*p).x+b;
            if(y>(*p).y)
            ct++;
        }
    if(ct%2)
    {
        mpoly_ans.ids[mpoly_ans.ct]=id;
        mpoly_ans.ct++;
    };
    return 1;
}

void QuaryPoint1(TYPE x,TYPE y)
{
    TYPE mind[2],maxd[2];
    mind[0]=maxd[0]=(tup_test_now).x=x;
    mind[1]=maxd[1]=(tup_test_now).y=y;
    mpoly_ans.ct=0;
    py_tree.Search(mind,maxd,CallForPolygon1);
    poly_ans.clear();
    for(int i=0;i!=mpoly_ans.ct;i++)
    poly_ans.push_back(mpoly_ans.ids[i]);
    return;
}


TriPolygon::TriPolygon(Polygon &in)
{
    int sz=in.size();
    in_changed.clear();
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
    tree=interTree(move(in_changed),8,1);
}

bool CallForPoint2(int id)
{
    //cout<<"Checking: "<<id<<endl;      //DEBUG
    int ct=0;
    TYPE k,b,y;
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


void pointTreeRemove(int id)
{
    tup one;
    point_map[id]=one;
}

void polyTreeRemove1(int id)
{
    Polygon one;
    poly_map[id]=one;
}
