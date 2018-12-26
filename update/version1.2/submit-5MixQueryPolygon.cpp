//
// Created by zhang on 18-12-4.
//

#include "submit-5MixQueryPolygon.h"

void SetEnvironmentFromMixQueryPolygon() {
;
}

void AddPointFromMixQueryPolygon(int id, double x, double y) {
    Id=id;
    pointTreeInsert(x,y);
}

void DeletePointFromMixQueryPolygon(int id) {
    Id=id;
    pointTreeRemove();
}

std::vector<int> QueryPolygonFromMixQueryPolygon(int n, std::vector<std::pair<double, double> > &polygon) {
    QuaryPolygon(n,polygon);
    return point_ans;
}
