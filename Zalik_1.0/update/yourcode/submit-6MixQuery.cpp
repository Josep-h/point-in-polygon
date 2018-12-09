#include "submit-6MixQuery.h"

void SetEnvironmentFromMixQuery() {

}

void AddPointFromMixQuery(int id, double x, double y) {
    Stup one;
    one.p.x=x;
    one.p.y=y;
    one.id=id;
    pointTreeInsert(pt_tree,one);
}

void DeletePointFromMixQuery(int id) {
    map<point_id,Stup>::iterator iter=point_map.find(id);
    if(iter==point_map.end())
    return;
    Stup temp=iter->second;
    pointTreeRemove(pt_tree,temp);
}

std::vector<int> QueryPointFromMixQuery(double x, double y) {
    tup test=tup(x,y);
    Stup test2=Stup(test);
    vector<int> ans;
    poly_ans=ans;
    py_tree.Search(test2.min,test2.max,CallForPolygon);
    return poly_ans;
}

void AddPolygonFromMixQuery(int id, int n, std::vector<std::pair<double, double>> &polygon) {
    Polygon add=parachange(polygon,id);
    polyTreeInsert(py_tree,add);
}

void DeletePolygonFromMixQuery(int id) {
    map<polygon_id,Polygon>::iterator iter=poly_map.find(id);
    if(iter==poly_map.end())
    return;
    Polygon tp=iter->second;
    polyTreeRemove(py_tree,tp);
}

std::vector<int> QueryPolygonFromMixQuery(int n, std::vector<std::pair<double, double>> &polygon) {
    vector<int> ans;
    point_ans=ans;
    Polygon test=parachange(polygon,1);
    pt_tree.Search(test.min,test.max,CallForPoint);
    return point_ans;
}

