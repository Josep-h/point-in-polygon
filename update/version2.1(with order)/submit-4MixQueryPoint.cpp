#include "submit-4MixQueryPoint.h"

void SetEnvironmentFromMixQueryPoint() {
;
}

std::vector<int> QueryPointFromMixQueryPoint(double x, double y) {
    QuaryPoint1(x,y);
    return poly_ans;
}

void AddPolygonFromMixQueryPoint(int id, int n, std::vector<std::pair<double, double> > &polygon) {
    polyTreeInsert1(polygon,n,id);
}

void DeletePolygonFromMixQueryPoint(int id) {
    polyTreeRemove1(id);
}
