#pragma once
#include"RTree.h"
#include<vector>
#include<unordered_map>
using namespace std;
typedef double TYPE;
typedef double TYPE2;
typedef vector<pair<double,double>> Polygon;
typedef int polygon_id;
typedef int point_id;
typedef RTree<polygon_id,TYPE,2,TYPE> polygon_tree;
typedef RTree<point_id,TYPE,2,TYPE> point_tree;
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

extern unordered_map<polygon_id,Polygon> poly_map;
extern polygon_tree py_tree;
extern TYPE maxd[2],mind[2];
extern unordered_map<point_id,tup> point_map;
extern point_tree pt_tree;
extern int Sz;
extern vector<int> poly_ans;
extern Polygon *polygon_test_now;

extern vector<int> point_ans;
extern tup tup_test_now;
extern unordered_map<int,MinMax> min_max;
//extern MinMax bound;
extern unordered_map<polygon_id,Polygon>::iterator iter1;
extern unordered_map<point_id,tup>::iterator iter2;
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
