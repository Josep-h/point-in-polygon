#pragma once
#include"header.h"
#include<iostream>
using namespace std;
unordered_map<polygon_id,Polygon> poly_map;
polygon_tree py_tree;

unordered_map<point_id,tup> point_map;
point_tree pt_tree;

unordered_map<polygon_id,Polygon>::iterator iter1;
unordered_map<point_id,tup>::iterator iter2;

vector<int> poly_ans(10000);
Polygon *polygon_test_now;

vector<int> point_ans(10000);
tup tup_test_now;
int Sz;
unordered_map<int,MinMax> min_max;
TYPE maxd[2],mind[2];
//MinMax bound;

void polyTreeInsert(Polygon &py,int sz,int id)
{
    iter1=poly_map.find(id);
    //cout<<id<<endl;//DEBUG
    //if(iter!=poly_map.end()) return;
    MinMax bound;
    //TYPE max[2],min[2];
    bound.max[0]=bound.min[0]=py[0].first;
    bound.max[1]=bound.min[1]=py[0].second;
    static TYPE2 xtp,ytp;
    for(int i=1;i<sz;i++)//这里做一个小小的尝试,看一下准确率会下降多少,下降到了0.917
    //这里的实验告诉我隔一个取一个似乎是不行的
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
    /*
    for(int i=1;i<sz;i++)//这里做一个小小的尝试,看一下准确率会下降多少,下降到了0.917
    //这里的实验告诉我隔一个取一个似乎是不行的
    {
        if(py[i].first>bound.max[0])
            bound.max[0]=py[i].first;
        else if(py[i].first<bound.min[0])
            bound.min[0]=py[i].first;
        if(py[i].second>bound.max[1])
            bound.max[1]=py[i].second;
        else if(py[i].second<bound.min[1])
            bound.min[1]=py[i].second;
    }*/
    //使用一个全局变量总是一个不错的选择,似乎他不需要将时间交给空间与删除,这里节约了有4~5秒钟
        //但似乎又不总是这样,因为有一些值进入内存反而速度降低
    /*
   TYPE2 xtp1,ytp1,xtp2,ytp2;
   MinMax bound1,bound2,Bound;
   bound1.max[0]=bound1.min[0]=py[0].first;
    bound1.max[1]=bound1.min[1]=py[0].second;
    bound2.max[0]=bound2.min[0]=py[1].first;
    bound2.max[1]=bound2.min[1]=py[1].second;
   for(int i=2;i<n-1;i+=2)//这里做一个小小的尝试,看一下准确率会下降多少,下降到了0.917
    //这里的实验告诉我隔一个取一个似乎是不行的
    {
        int j=i+1;
        xtp1=py[i].first,ytp1=py[i].second;
        xtp2=py[j].first,ytp2=py[j].second;
        if(xtp1>bound1.max[0])
            bound1.max[0]=xtp1;
        else if(xtp1<bound1.min[0])
            bound1.min[0]=xtp1;
        if(ytp1>bound1.max[1])
            bound1.max[1]=ytp1;
        else if(ytp1<bound1.min[1])
            bound1.min[1]=ytp1;
        
        if(xtp2>bound2.max[0])
            bound2.max[0]=xtp2;
        else if(xtp2<bound2.min[0])
            bound2.min[0]=xtp2;
        if(ytp2>bound2.max[1])
            bound2.max[1]=ytp2;
        else if(ytp2<bound2.min[1])
            bound2.min[1]=ytp2;
    }
    if(bound2.min[0]<bound1.min[0]) bound1.min[0]=bound2.min[0];
    if(bound2.min[1]<bound1.min[1]) bound1.min[1]=bound2.min[1];
    if(bound2.max[0]>bound1.max[0]) bound1.max[0]=bound2.max[0];
    if(bound2.max[1]>bound1.max[1]) bound1.max[1]=bound2.max[1];
    */
   //这个方法似乎也没有太多的作用,其原因在于本来使用的数字就没有冲突,所以不会进行优化.麻烦的在于这个里有太多的if语句
    poly_map.insert(pair<polygon_id,Polygon>(id,py));
    min_max[id]=bound;
    py_tree.Insert(bound.min,bound.max,id);
    return ;
}

void polyTreeRemove(int id)
{
    iter1=poly_map.find(id);
    /*if(iter1==poly_map.end())
    return;*/
    poly_map.erase(iter1);
    TYPE mind[2],maxd[2];
    //mind[0]=bound.min[0];mind[1]=bound.min[1];
    //maxd[0]=bound.max[0];maxd[1]=bound.max[1];
    py_tree.Remove(mind,maxd,id);
}

void pointTreeInsert(TYPE x,TYPE y,int id)
{
    iter2=point_map.find(id);
    //cout<<pt.id<<endl;//DEBUG
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
    iter2=point_map.find(id);
    if(iter2==point_map.end())
    return;
    
    mind[0]=maxd[0]=iter2->second.x;
    mind[1]=maxd[1]=iter2->second.y;

    point_map.erase(iter2);
    pt_tree.Remove(mind,maxd,id);
}

bool CallForPolygon(int id)//Myversion
{
    int ct=0,i=0,j,sz;
    static TYPE2 k,b,y,xtp1,ytp1,xtp2;
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
bool CallForPoint(int id)
{
    //cout<<"Checking: "<<id<<endl;      //DEBUG
    int ct=0,i=0,j,sz=Sz;
    static TYPE k,b,y,xtp1,ytp1,xtp2;
    tup p=point_map[id];
    //cout<<p.x<<" "<<p.y<<endl;
    Polygon polygon_in=*polygon_test_now;
    //int sz=polygon_in.size();
    for(;i<sz-1;i++)
    {
        j=i+1;
        //int s=(i+2)%sz;
        xtp1=polygon_in[i].first,ytp1=polygon_in[i].second;
        xtp2=polygon_in[j].first;
        if((xtp1<p.x&&xtp2>p.x)\
        ||(xtp1>p.x&&xtp2<p.x))
        {
            //if(polygon_in[i].first==polygon_in[j].first)
            //continue;
            k=(polygon_in[j].second-ytp1)/(xtp2-xtp1);
            b=ytp1-xtp1*k;
            y=k*p.x+b;
            if(y>p.y)
            ct++;
        }
    }
    j=0;
        xtp1=polygon_in[i].first,ytp1=polygon_in[i].second;
        xtp2=polygon_in[0].first;
        if((xtp1<p.x&&xtp2>p.x)\
        ||(xtp1>p.x&&xtp2<p.x))
        {
            k=(polygon_in[j].second-ytp1)/(polygon_in[j].first-xtp1);
            b=ytp1-xtp1*k;
            y=k*p.x+b;
            if(y>p.y)
            ct++;
        }
    if(ct%2)
    point_ans.push_back(id);
    return 1;
}

bool point_in_polygon_new(Polygon &polygon_in,tup &p)//My version
{
    int ct=0,i=0,j,sz=polygon_in.size();
    static TYPE k,b,y,xtp1,ytp1,xtp2;
    //cout<<p.x<<" "<<p.y<<endl;
    //int sz=polygon_in.size();
    for(;i<sz-1;i++)
    {
        j=i+1;
        xtp1=polygon_in[i].first;
        xtp2=polygon_in[j].first;
        if((xtp1<p.x&&xtp2>p.x)\
        ||(xtp1>p.x&&xtp2<p.x))
        {
            ytp1=polygon_in[i].second;
            //if(polygon_in[i].first==polygon_in[j].first)
            //continue;
            k=(polygon_in[j].second-ytp1)/(xtp2-xtp1);
            b=ytp1-xtp1*k;
            y=k*p.x+b;
            if(y>p.y)
            ct++;
        }
    }
    j=0;
        xtp1=polygon_in[i].first,ytp1=polygon_in[i].second;
        xtp2=polygon_in[0].first;
        if((xtp1<p.x&&xtp2>p.x)\
        ||(xtp1>p.x&&xtp2<p.x))
        {
            k=(polygon_in[j].second-ytp1)/(polygon_in[j].first-xtp1);
            b=ytp1-xtp1*k;
            y=k*p.x+b;
            if(y>p.y)
            ct++;
        }

    return ct%2;
}

/*
bool point_in_polygon_new(vector<pair<TYPE, TYPE>> &polygon,tup &p)
{
    bool flag = false;
    TYPE px=p.x;
    TYPE py=p.y;
    for(int i = 0, l = polygon.size(), j = l - 1; i < l; j = i, i++)
    {
        TYPE sx = polygon[i].first, sy = polygon[i].second, tx = polygon[j].first, ty = polygon[j].second;

        // 点与多边形顶点重合
        //if((sx == px && sy == py) || (tx == px && ty == py)) return false;

        // 判断线段两端点是否在射线两侧
        if((sy < py && ty >= py) || (sy >= py && ty < py))
        {
            // 线段上与射线 Y 坐标相同的点的 X 坐标
            TYPE x = sx + (py - sy) * (tx - sx) / (ty - sy);
            // 点在多边形的边上
            if(x == px) return false;
            // 射线穿过多边形的边界
            if(x > px) flag = !flag;
        }
    }

    // 射线穿过多边形边界的次数为奇数时点在多边形内
    return flag;
}*/

void QuaryPolygon(int sz,Polygon &py)
{
    Polygon one;
    for(int i=0;i!=sz;i++)
    {
        one.push_back(py[i]);
    }
    //vector<int> ans;
    point_ans.clear();
    polygon_test_now=&one;
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
    pt_tree.Search(mind,maxd,CallForPoint);
    return ;
}

void QuaryPoint(TYPE x,TYPE y)
{
    TYPE mind[2],maxd[2];
    mind[0]=maxd[0]=(tup_test_now).x=x;
    mind[1]=maxd[1]=(tup_test_now).y=y;
    //Stup test2=Stup(tup_test_now);
    //vector<int> ans;
    poly_ans.clear();
    py_tree.Search(mind,maxd,CallForPolygon);
    return;
}
