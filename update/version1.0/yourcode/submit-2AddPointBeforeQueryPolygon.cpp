#include "submit-2AddPointBeforeQueryPolygon.h"

void SetEnvironmentFromAddPointBeforeQueryPolygon() {

}

void AddPointFromAddPointBeforeQueryPolygon(int id, double x, double y) {
    Stup one=Stup(tup(x,y));
    one.id=id;
    pointTreeInsert(pt_tree,one);
}

std::vector<int> QueryPolygonFromAddPointBeforeQueryPolygon(int n, std::vector<std::pair<double, double> > polygo) {
    vector<int> ans;
    point_ans=ans;
    polygon_test_now=parachange(polygo,1);
    pt_tree.Search(polygon_test_now.min,polygon_test_now.max,CallForPoint);
    return point_ans;
}
