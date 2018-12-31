#include "submit-1AddPolygonBeforeQueryPoint.h"

void SetEnvironmentFromAddPolygonBeforeQueryPoint() {;
}

std::vector<int> QueryPointFromAddPolygonBeforeQueryPoint(double x, double y) {
    vector<int> ans;
    QuaryPoint1(x,y,ans);
    //cout<<ans.size();
    return ans;
}

void AddPolygonFromAddPolygonBeforeQueryPoint(int id, int n, std::vector<std::pair<double, double> > &py) {
    polyTreeInsert1(py,n,id);
    return ;
}
