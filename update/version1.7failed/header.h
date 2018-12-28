#pragma once
#include"RTree.h"
#include"IntervalTree.h"
#include"QuadTree.h"
#include<vector>
#include<unordered_map>
using namespace std;
typedef double TYPE;
typedef double TYPE2;
typedef int polygon_id;
typedef int point_id;
typedef vector<pair<double,double>> Polygon;

typedef RTree<polygon_id,TYPE,2,TYPE> polygon_tree;
typedef IntervalTree<double,pair<double,double>> interTree;//mark as k,b
typedef QuadTree<int> point_tree;

class tup{//def of the tuple
    public:
    TYPE x;
    TYPE y;
    tup(){}
    tup(TYPE x,TYPE y):x(x),y(y){}
};
typedef pair<pair<double,double>,pair<double,double>> edge;

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

extern unordered_map<polygon_id,TriPolygon> TriPolygon_map;
extern unordered_map<point_id,tup> point_map;
extern unordered_map<int,MinMax> min_max;

extern unordered_map<polygon_id,Polygon>::iterator iter1;
extern unordered_map<point_id,tup>::iterator iter2;

//extern point_tree pt_tree;
extern polygon_tree py_tree;
extern point_tree *pt_tree;

extern TYPE maxd[2],mind[2];

extern vector<int> poly_ans;
extern vector<int> point_ans;

extern TriPolygon *polygon_test_now;
extern tup tup_test_now;



//extern MinMax bound;


void polyTreeInsert(Polygon &py,int sz,int id);
void polyTreeRemove(int id);
void pointTreeInsert(TYPE x,TYPE y,int id);
void pointTreeRemove(int id);
bool CallForPolygon(polygon_id id);
bool CallForPoint(point_id id);
bool point_in_polygon_new(Polygon &poly,tup &p);
void QuaryPolygon(int sz,Polygon &polygon);
void QuaryPoint(TYPE x,TYPE y);
//Polygon parachange(vector<pair<TYPE,TYPE> > &polygon_in,int id);
