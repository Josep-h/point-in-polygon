#pragma once
#include"RTree.h"
#include<vector>
#include<unordered_map>
using namespace std;
typedef vector<pair<double,double>> Polygon;
typedef int polygon_id;
typedef int point_id;
typedef RTree<polygon_id,double,2,double> polygon_tree;
typedef RTree<point_id,double,2,double> point_tree;

class tup{//def of the tuple
    public:
    double x;
    double y;
    tup(){}
    tup(double x,double y):x(x),y(y){}
};

class MinMax{
    public:
    double min[2];
    double max[2];
    MinMax(){}
    MinMax(double xmin,double ymin,double xmax,double ymax){
        min[0]=xmin;min[1]=ymin;
        max[0]=xmax;max[1]=ymax;
    }
};

extern unordered_map<polygon_id,Polygon> poly_map;
extern polygon_tree py_tree;
extern double maxd[2],mind[2];
extern unordered_map<point_id,tup> point_map;
extern point_tree pt_tree;
extern int Sz;
extern vector<int> poly_ans;
extern Polygon *polygon_test_now;

extern vector<int> point_ans;
extern tup tup_test_now;
extern int Id;
extern unordered_map<int,MinMax> min_max;
extern MinMax bound;
extern unordered_map<polygon_id,Polygon>::iterator iter1;
extern unordered_map<point_id,tup>::iterator iter2;

void polyTreeInsert(Polygon &py,int sz);
void polyTreeRemove();
void pointTreeInsert(double x,double y);
void pointTreeRemove();
bool CallForPolygon(polygon_id id);
bool CallForPoint(point_id id);
bool point_in_polygon_new(Polygon &poly,tup &p);
void QuaryPolygon(int sz,Polygon &polygon);
void QuaryPoint(double x,double y);
//Polygon parachange(vector<pair<double,double> > &polygon_in,int id);
