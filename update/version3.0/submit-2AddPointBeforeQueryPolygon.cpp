#include "submit-2AddPointBeforeQueryPolygon.h"
#include<iostream>
void SetEnvironmentFromAddPointBeforeQueryPolygon() {
}

void AddPointFromAddPointBeforeQueryPolygon(int id, double x, double y) {
    pointTreeInsert(x,y,id);
    return ;
}

std::vector<int> QueryPolygonFromAddPointBeforeQueryPolygon(int sz, std::vector<std::pair<double, double> > py) {
    QuaryPolygon(sz,py);
    return point_ans;
}
