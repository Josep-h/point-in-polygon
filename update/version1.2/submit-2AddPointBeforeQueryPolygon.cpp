#include "submit-2AddPointBeforeQueryPolygon.h"

void SetEnvironmentFromAddPointBeforeQueryPolygon() {

}

void AddPointFromAddPointBeforeQueryPolygon(int id, double x, double y) {
    Id=id;
    pointTreeInsert(x,y);
}

std::vector<int> QueryPolygonFromAddPointBeforeQueryPolygon(int n, std::vector<std::pair<double, double> > polygon) {
    QuaryPolygon(n,polygon);
    return point_ans;
}
