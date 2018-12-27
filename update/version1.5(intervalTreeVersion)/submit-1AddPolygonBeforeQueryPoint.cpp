#include "submit-1AddPolygonBeforeQueryPoint.h"

void SetEnvironmentFromAddPolygonBeforeQueryPoint() {;
}

std::vector<int> QueryPointFromAddPolygonBeforeQueryPoint(double x, double y) {
    QuaryPoint(x,y);
    return poly_ans;
}

void AddPolygonFromAddPolygonBeforeQueryPoint(int id, int n, std::vector<std::pair<double, double> > &py) {
    polyTreeInsert(py,n,id);
    return ;
}
