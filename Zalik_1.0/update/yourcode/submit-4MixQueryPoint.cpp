#include "submit-4MixQueryPoint.h"

void SetEnvironmentFromMixQueryPoint() {
;
}

std::vector<int> QueryPointFromMixQueryPoint(double x, double y) {
    tup test=tup(x,y);
    Stup test2=Stup(test);
    vector<int> ans;
    poly_ans=ans;
    py_tree.Search(test2.min,test2.max,CallForPolygon);
    return poly_ans;
}

void AddPolygonFromMixQueryPoint(int id, int n, std::vector<std::pair<double, double> > &polygon) {
    Polygon add=parachange(polygon,id);
    polyTreeInsert(py_tree,add);
}

void DeletePolygonFromMixQueryPoint(int id) {
    map<polygon_id,Polygon>::iterator iter=poly_map.find(id);
    if(iter==poly_map.end())
    return;
    Polygon tp=iter->second;
    polyTreeRemove(py_tree,tp);
}
