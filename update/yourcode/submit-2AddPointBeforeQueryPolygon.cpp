#include "submit-2AddPointBeforeQueryPolygon.h"

void SetEnvironmentFromAddPointBeforeQueryPolygon() {

}

void AddPointFromAddPointBeforeQueryPolygon(int id, double x, double y) {
    Stup one=Stup(tup(x,y));
    one.id=id;
    pointTreeInsert(pt_tree,one);
}

std::vector<int> QueryPolygonFromAddPointBeforeQueryPolygon(int n, std::vector<std::pair<double, double> > polygon) {
    QuaryPolygon(n,polygon);
    return point_ans;
}
