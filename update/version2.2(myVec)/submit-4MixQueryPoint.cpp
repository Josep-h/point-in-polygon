#include "submit-4MixQueryPoint.h"

void SetEnvironmentFromMixQueryPoint() {
;
}

std::vector<int> QueryPointFromMixQueryPoint(double x, double y) {
    vector<int> ans;
    QuaryPoint1(x,y,ans);
    return ans;
}

void AddPolygonFromMixQueryPoint(int id, int n, std::vector<std::pair<double, double> > &polygon) {
    polyTreeInsert1(polygon,n,id);
}

void DeletePolygonFromMixQueryPoint(int id) {
    polyTreeRemove1(id);
}
