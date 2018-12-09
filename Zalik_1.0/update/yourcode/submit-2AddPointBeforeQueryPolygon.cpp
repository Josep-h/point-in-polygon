#include "submit-2AddPointBeforeQueryPolygon.h"

void SetEnvironmentFromAddPointBeforeQueryPolygon() {

}

void AddPointFromAddPointBeforeQueryPolygon(int id, double x, double y) {
    Stup one;
    one.p.x=x;
    one.p.y=y;
    one.id=id;
    pointTreeRemove(pt_tree,one);
}

std::vector<int> QueryPolygonFromAddPointBeforeQueryPolygon(int n, std::vector<std::pair<double, double> > polygo) {
    vector<int> ans;
    point_ans=ans;
    Polygon test=parachange(polygo,1);
    pt_tree.Search(test.min,test.max,CallForPoint);
    return point_ans;
}
