#include "submit-4MixQueryPoint.h"

void SetEnvironmentFromMixQueryPoint() {
;
}

std::vector<int> QueryPointFromMixQueryPoint(double x, double y) {
    QuaryPoint(x,y);
    return poly_ans;
}

void AddPolygonFromMixQueryPoint(int id, int n, std::vector<std::pair<double, double> > &polygon) {
    polyTreeInsert(polygon,id);
}

void DeletePolygonFromMixQueryPoint(int id) {
    polyTreeRemove(id);
}
