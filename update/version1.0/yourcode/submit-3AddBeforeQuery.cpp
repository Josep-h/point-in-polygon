#include "submit-3AddBeforeQuery.h"

void SetEnvironmentFromAddBeforeQuery() {
;
}

void AddPointFromAddBeforeQuery(int id, double x, double y) {
    Stup one=Stup(tup(x,y));
    one.id=id;
    pointTreeInsert(pt_tree,one);
}

void AddPolygonFromAddBeforeQuery(int id, int n, std::vector<std::pair<double, double> > &polygon) {
    Polygon add=parachange(polygon,id);
    polyTreeInsert(add);
}

std::vector<int> QueryPointFromAddBeforeQuery(double x, double y) {
    tup_test_now=tup(x,y);
    Stup test2=Stup(tup_test_now);
    vector<int> ans;
    poly_ans=ans;
    py_tree.Search(test2.min,test2.max,CallForPolygon);
    return poly_ans;
}

std::vector<int> QueryPolygonFromAddBeforeQuery(int n, std::vector<std::pair<double, double> > &polygon) {
    vector<int> ans;
    point_ans=ans;
    polygon_test_now=parachange(polygon,1);
    pt_tree.Search2(polygon_test_now.min,polygon_test_now.max,CallForPoint);
    return point_ans;
}
