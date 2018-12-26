#include "submit-3AddBeforeQuery.h"

void SetEnvironmentFromAddBeforeQuery() {
;
}

void AddPointFromAddBeforeQuery(int id, double x, double y) {
    Id=id;
    pointTreeInsert(x,y);
}

void AddPolygonFromAddBeforeQuery(int id, int n, std::vector<std::pair<double, double> > &polygon) {
    Id=id;
    polyTreeInsert(polygon,n);
}

std::vector<int> QueryPointFromAddBeforeQuery(double x, double y) {
    QuaryPoint(x,y);
    return poly_ans;
}

std::vector<int> QueryPolygonFromAddBeforeQuery(int n, std::vector<std::pair<double, double> > &polygon) {
    QuaryPolygon(n,polygon);
    return point_ans;
}
