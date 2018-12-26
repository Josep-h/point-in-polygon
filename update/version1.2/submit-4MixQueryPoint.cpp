#include "submit-4MixQueryPoint.h"

void SetEnvironmentFromMixQueryPoint() {
;
}

std::vector<int> QueryPointFromMixQueryPoint(double x, double y) {
    QuaryPoint(x,y);
    return poly_ans;
}

void AddPolygonFromMixQueryPoint(int id, int n, std::vector<std::pair<double, double> > &polygon) {
    Id=id;
    polyTreeInsert(polygon,n);
}

void DeletePolygonFromMixQueryPoint(int id) {
    Id=id;
    polyTreeRemove();
}
