#include "submit-6MixQuery.h"

void SetEnvironmentFromMixQuery() {
;
}

void AddPointFromMixQuery(int id, double x, double y) {
    Id=id;
    pointTreeInsert(x,y);
}

void DeletePointFromMixQuery(int id) {
    Id=id;
    pointTreeRemove();
}

std::vector<int> QueryPointFromMixQuery(double x, double y) {
    QuaryPoint(x,y);
    return poly_ans;
}

void AddPolygonFromMixQuery(int id, int n, std::vector<std::pair<double, double>> &polygon) {
    Id=id;
    polyTreeInsert(polygon,n);
}

void DeletePolygonFromMixQuery(int id) {
    Id=id;
    polyTreeRemove();
}

std::vector<int> QueryPolygonFromMixQuery(int n, std::vector<std::pair<double, double>> &polygon) {
    QuaryPolygon(n,polygon);
    return point_ans;
}

