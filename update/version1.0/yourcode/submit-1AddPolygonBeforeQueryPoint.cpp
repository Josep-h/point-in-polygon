#include "submit-1AddPolygonBeforeQueryPoint.h"

void SetEnvironmentFromAddPolygonBeforeQueryPoint() {;
}

std::vector<int> QueryPointFromAddPolygonBeforeQueryPoint(double x, double y) {
    tup_test_now=tup(x,y);
    Stup test2=Stup(tup_test_now);
    vector<int> ans;
    poly_ans=ans;
    py_tree.Search(test2.min,test2.max,CallForPolygon);
    return poly_ans;
}

void AddPolygonFromAddPolygonBeforeQueryPoint(int id, int n, std::vector<std::pair<double, double> > &polygo) {
    Polygon add=parachange(polygo,id);
    polyTreeInsert(add);
}
