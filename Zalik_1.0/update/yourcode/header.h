#pragma once
#include"RTree.h"
#include<vector>
#include<map>
using namespace std;

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

void polyTreeInsert(polygon_tree& pytree,Polygon py);
void polyTreeRemove(polygon_tree& pytree,Polygon py);
void pointTreeInsert(point_tree& pttree,Stup pt);
void pointTreeRemove(point_tree& pttree,Stup pt);
bool CallForPolygon(polygon_id id);
bool CallForPoint(point_id id);
bool point_in_polygon(Polygon &poly,tup p);
Polygon parachange(vector<pair<double,double> > &polygon_in,int id);

extern map<polygon_id,Polygon> poly_map;
extern polygon_tree py_tree;

extern map<point_id,Stup> point_map;
extern point_tree pt_tree;

extern vector<int> poly_ans;
extern Polygon polygon_test_now;

extern vector<int> point_ans;
extern tup tup_test_now;