#include "submit-3AddBeforeQuery.h"

void SetEnvironmentFromAddBeforeQuery() {
;
}

void AddPointFromAddBeforeQuery(int id, double x, double y) {
    pointTreeInsert(x,y,id);
}

void AddPolygonFromAddBeforeQuery(int id, int n, std::vector<std::pair<double, double> > &polygon) {
    polyTreeInsert1(polygon,n,id);
}

std::vector<int> QueryPointFromAddBeforeQuery(double x, double y) {
    QuaryPoint1(x,y);
    return poly_ans;
}

std::vector<int> QueryPolygonFromAddBeforeQuery(int n, std::vector<std::pair<double, double> > &polygon) {
    QuaryPolygon2(n,polygon);
    return point_ans;
}
