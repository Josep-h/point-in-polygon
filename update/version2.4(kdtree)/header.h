#pragma once
#include"RTree.h"
#include"IntervalTree.h"
#include"kdtree.h"
#include<vector>
#include<unordered_map>
using namespace std;
typedef double TYPE;
typedef double TYPE2;
typedef vector<pair<double,double>> Polygon;
typedef pair<pair<double,double>,pair<double,double>> edge;
typedef IntervalTree<double,pair<double,double>> interTree;//mark as k,b
typedef int polygon_id;
typedef int point_id;
typedef RTree<polygon_id,TYPE,2,TYPE> polygon_tree;
//typedef RTree<point_id,TYPE,2,TYPE> point_tree;

class tup{//def of the tuple
    public:
    TYPE x;
    TYPE y;
    tup(){}
    tup(TYPE x,TYPE y):x(x),y(y){}
};

class MinMax{
    public:
    TYPE min[2];
    TYPE max[2];
    MinMax(){}
    MinMax(TYPE xmin,TYPE ymin,TYPE xmax,TYPE ymax){
        min[0]=xmin;min[1]=ymin;
        max[0]=xmax;max[1]=ymax;
    }
};

class TriPolygon{
    public:
    interTree tree;
    TriPolygon(Polygon &in);
    TriPolygon(){}
};

class kbPolygon{
    public:
    pair<double,double> *k_b_vec;
    pair<double,double> *left_right;
    int sz;
    MinMax bound;
    kbPolygon(){}
    kbPolygon(int n){k_b_vec=new pair<double,double>[n];}
    kbPolygon(Polygon &in);
};

extern unordered_map<polygon_id,TriPolygon> TriPolygon_map;
extern unordered_map<polygon_id,kbPolygon> kbPolygon_map;
//extern unordered_map<polygon_id,Polygon> poly_map;
extern unordered_map<point_id,tup> point_map;
//extern point_tree pt_tree;
extern kdtree pt_tree;
extern polygon_tree py_tree;
extern TYPE maxd[2],mind[2];

extern int Sz;
extern vector<int> poly_ans;
extern vector<int> point_ans;

extern kbPolygon *polygon_test_now;
extern tup tup_test_now;
extern TriPolygon *polygon_test_now2;

extern unordered_map<polygon_id,Polygon>::iterator iter1;
extern unordered_map<point_id,tup>::iterator iter2;

void pointTreeInsert(TYPE x,TYPE y,int id);
void pointTreeRemove(int id);

void polyTreeInsert(Polygon &py,int sz,int id);
void polyTreeRemove(int id);

bool CallForPolygon(polygon_id id);
bool CallForPoint(point_id id);

void QuaryPoint(TYPE x,TYPE y);
void QuaryPolygon(int sz,Polygon &polygon);


