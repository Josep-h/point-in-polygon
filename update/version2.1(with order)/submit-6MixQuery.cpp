#include "submit-6MixQuery.h"

void SetEnvironmentFromMixQuery() {
;
}

void AddPointFromMixQuery(int id, double x, double y) {
    pointTreeInsert(x,y,id);
}

void DeletePointFromMixQuery(int id) {
    pointTreeRemove(id);
}

std::vector<int> QueryPointFromMixQuery(double x, double y) {
    QuaryPoint1(x,y);
    return poly_ans;
}

void AddPolygonFromMixQuery(int id, int n, std::vector<std::pair<double, double>> &polygon) {
    polyTreeInsert1(polygon,n,id);
}

void DeletePolygonFromMixQuery(int id) {
    polyTreeRemove1(id);
}

std::vector<int> QueryPolygonFromMixQuery(int n, std::vector<std::pair<double, double>> &polygon) {
    QuaryPolygon2(n,polygon);
    return point_ans;
}

