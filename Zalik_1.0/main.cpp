#include"RTree.h"
#include"point_in_polygon.cpp"
#include<map>
typedef int polygon_id;
typedef int point_id;
using namespace std;

typedef RTree<polygon_id,double,2,double> polygon_tree;
typedef RTree<point_id,double,2,double> point_tree;


void polyTreeInsert(polygon_tree& pytree,Polygon py)
{
    map<polygon_id,Polygon>::iterator iter=poly_map.find(py.id);
    if(iter!=poly_map.end()) return;
    poly_map.insert(pair<polygon_id,Polygon>(py.id,py));
    pytree.Insert(py.min,py.max,py.id);
}

void polyTreeRemove(polygon_tree& pytree,Polygon py)
{
    map<polygon_id,Polygon>::iterator iter=poly_map.find(py.id);
    if(iter!=poly_map.end())
    {
        poly_map.erase(iter);
        pytree.Remove(py.min,py.max,py.id);
    }
}

void pointTreeInsert(point_tree& pttree,Stup pt)
{
    map<point_id,Stup>::iterator iter=point_map.find(pt.id);
    if(iter!=point_map.end()) return ;
    point_map.insert(pair<point_id,Stup>(pt.id,pt));
    pttree.Insert(pt.min,pt.max,pt.id);
}

void pointTreeRemove(point_tree& pttree,Stup pt)
{
    map<point_id,Stup>::iterator iter=point_map.find(pt.id);
    if(iter!=point_map.end())
    {
        point_map.erase(iter);
        pttree.Remove(pt.min,pt.max,pt.id);
    }
}

bool CallForPolygon(polygon_id id)
{
    map<polygon_id,Polygon>::iterator iter=poly_map.find(id);
    if(point_in_polygon(iter->second,tup_test_now))
    poly_ans.push_back(id);
    return 1;
}

bool CallForPoint(point_id id)
{
    map<point_id,Stup>::iterator iter=point_map.find(id);
    if(point_in_polygon(polygon_test_now,iter->second.p))
    point_ans.push_back(id);
    return 1;
}

