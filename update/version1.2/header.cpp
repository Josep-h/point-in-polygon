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

vector<int> poly_ans(1000);
Polygon *polygon_test_now;

vector<int> point_ans(10000);
tup tup_test_now;
int Sz;
unordered_map<int,MinMax> min_max;
double maxd[2],mind[2];
MinMax bound;
int Id;
void polyTreeInsert(Polygon &py,int sz)
{
    iter1=poly_map.find(Id);
    //cout<<id<<endl;//DEBUG
    //if(iter!=poly_map.end()) return;
    //double max[2],min[2];
    bound.max[0]=bound.min[0]=py[0].first;
    bound.max[1]=bound.min[1]=py[0].second;
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
    }
    /*max[0]=min[0]=py[0].first;
    max[1]=min[1]=py[0].second;
    for(int i=1;i<sz;i++)//这里做一个小小的尝试,看一下准确率会下降多少,下降到了0.917
    //这里的实验告诉我隔一个取一个似乎是不行的
    {
        if(py[i].first>max[0])
            max[0]=py[i].first;
        else if(py[i].first<min[0])
            min[0]=py[i].first;
        if(py[i].second>max[1])
            max[1]=py[i].second;
        else if(py[i].second<min[1])
            min[1]=py[i].second;
    }*/
    //使用一个全局变量总是一个不错的选择,似乎他不需要将时间交给空间与删除,这里节约了有4~5秒钟

    poly_map.insert(pair<polygon_id,Polygon>(Id,py));
    min_max[Id]=bound;
    py_tree.Insert(bound.min,bound.max,Id);
    return ;
}

void polyTreeRemove()
{
    iter1=poly_map.find(Id);
    if(iter1==poly_map.end())
    return;
    poly_map.erase(iter1);
    py_tree.Remove(min_max[Id].min,min_max[Id].max,Id);
}

void pointTreeInsert(double x,double y)
{
    iter2=point_map.find(Id);
    //cout<<pt.id<<endl;//DEBUG
    //Stup one=Stup(tup(x,y));
    if(iter2!=point_map.end()) return ;
    mind[0]=maxd[0]=x;
    mind[1]=maxd[1]=y;
    point_map.insert(pair<point_id,tup>(Id,tup(x,y)));
    pt_tree.Insert(mind,maxd,Id);
    return ;
}

void pointTreeRemove()
{
    iter2=point_map.find(Id);
    if(iter2==point_map.end())
    return;
    
    mind[0]=maxd[0]=iter2->second.x;
    mind[1]=maxd[1]=iter2->second.y;

    point_map.erase(iter2);
    pt_tree.Remove(mind,maxd,Id);
}

bool CallForPolygon(int id)
{
    Sz=poly_map[id].size();
    if(point_in_polygon_new(poly_map[id],tup_test_now))
    poly_ans.push_back(id);
    //cout<<"Checking: "<<id<<endl;//DEBUG
    return 1;
}

bool CallForPoint(int id)
{
    //cout<<"Checking: "<<id<<endl;      //DEBUG
    
    if(point_in_polygon_new(*polygon_test_now,point_map[id]))
    point_ans.push_back(id);
    return 1;
}

bool point_in_polygon_new(Polygon &polygon_in,tup &p)
{
    int ct=0;
    //int sz=polygon_in.size();
    for(int i=0;i!=Sz;i++)
    {
        int j=(i+1)%Sz;
        //int s=(i+2)%sz;
        if((polygon_in[i].first<=p.x&&polygon_in[j].first>=p.x)\
        ||(polygon_in[i].first>=p.x&&polygon_in[j].first<=p.x))
        {
            if(polygon_in[i].first==polygon_in[j].first)
            continue;
            double k=(polygon_in[j].second-polygon_in[i].second)/(polygon_in[j].first-polygon_in[i].first);
            double b=polygon_in[i].second-polygon_in[i].first*k;
            double y=k*p.x+b;
            if(y>p.y)
            ct++;
            
                /* if((polygon_in[j].first==p.x)\
                // &&((polygon_in[s].first<p.x)!=(polygon_in[i].first<p.x)))
                 ct--;*/
               
        }
    }
    return ct%2;
}
/*

bool point_in_polygon_new(vector<pair<double, double>> &polygon,tup p)
{
    bool flag = false;
    double px=p.x;
    double py=p.y;
    for(int i = 0, l = polygon.size(), j = l - 1; i < l; j = i, i++)
    {
        double sx = polygon[i].first, sy = polygon[i].second, tx = polygon[j].first, ty = polygon[j].second;

        // 点与多边形顶点重合
        if((sx == px && sy == py) || (tx == px && ty == py)) return false;

        // 判断线段两端点是否在射线两侧
        if((sy < py && ty >= py) || (sy >= py && ty < py))
        {
            // 线段上与射线 Y 坐标相同的点的 X 坐标
            double x = sx + (py - sy) * (tx - sx) / (ty - sy);
            // 点在多边形的边上
            if(x == px) return false;
            // 射线穿过多边形的边界
            if(x > px) flag = !flag;
        }
    }

    // 射线穿过多边形边界的次数为奇数时点在多边形内
    return flag;
}*/

void QuaryPolygon(int sz,Polygon &polygon)
{
    //vector<int> ans;
    point_ans.clear();
    polygon_test_now=&polygon;
    double xmax,xmin,ymin,ymax;
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
    mind[0]=xmin;mind[1]=ymin;
    maxd[0]=xmax;maxd[1]=ymax;
    Sz=sz;
    pt_tree.Search(mind,maxd,CallForPoint);
    return;
}

void QuaryPoint(double x,double y)
{
    mind[0]=maxd[0]=(tup_test_now).x=x;
    mind[1]=maxd[1]=(tup_test_now).y=y;
    //Stup test2=Stup(tup_test_now);
    //vector<int> ans;
    poly_ans.clear();
    py_tree.Search(mind,maxd,CallForPolygon);
    return;
}
