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
    bool operator < (const tup &now) const{
        return y<now.y;
    }
    bool operator == (const tup &now) const{
        return y==now.y&&x==now.x;
    }
};

class Stup{//special tup with id and rectangle
    public:
    tup p;
    int id;
    double min[2];
    double max[2];
    Stup(){}
    Stup(tup);
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
    MinMax(double omin[2],double omax[2])
    {
        min[0]=omin[0];min[1]=omin[1];
        max[0]=omax[0];max[1]=omax[1];
    }
};
/*
class edge{
    public:
    tup bgn;
    tup nd;
    float k;
    float b;
    edge(){}
    edge(tup one,tup two);
};

class Polygon{
    public:
    vector<edge> edges;
    int id;
    double min[2];
    double max[2];
    Polygon(){}
};
*/
extern unordered_map<polygon_id,Polygon> poly_map;
extern polygon_tree py_tree;

extern unordered_map<point_id,Stup> point_map;
extern point_tree pt_tree;

extern vector<int> poly_ans;
extern Polygon polygon_test_now;

extern vector<int> point_ans;
extern tup tup_test_now;

extern unordered_map<int,MinMax> min_max;

void polyTreeInsert(Polygon py,int id);
void polyTreeRemove(int id);
void pointTreeInsert(int id,double x,double y);
void pointTreeRemove(int id);
bool CallForPolygon(polygon_id id);
bool CallForPoint(point_id id);
bool point_in_polygon(Polygon &poly,tup p);
bool point_in_polygon_new(Polygon &poly,tup p);
void QuaryPolygon(int sz,Polygon polygon);
void QuaryPoint(double x,double y);
//Polygon parachange(vector<pair<double,double> > &polygon_in,int id);
