#include "submit-4MixQueryPoint.h"

void SetEnvironmentFromMixQueryPoint() {
;
}

std::vector<int> QueryPointFromMixQueryPoint(double x, double y) {
    tup_test_now=tup(x,y);
    Stup test2=Stup(tup_test_now);
    vector<int> ans;
    poly_ans=ans;
    py_tree.Search(test2.min,test2.max,CallForPolygon);
    return poly_ans;
}

void AddPolygonFromMixQueryPoint(int id, int n, std::vector<std::pair<double, double> > &polygon) {
    polyTreeInsert(polygon,id);
}

void DeletePolygonFromMixQueryPoint(int id) {
    map<polygon_id,Polygon>::iterator iter=poly_map.find(id);
    if(iter==poly_map.end())
    return;
    polyTreeRemove(py_tree,id);
}
