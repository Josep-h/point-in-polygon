#include "submit-3AddBeforeQuery.h"

void SetEnvironmentFromAddBeforeQuery() {

}

void AddPointFromAddBeforeQuery(int id, double x, double y) {
    Stup one;
    one.p.x=x;
    one.p.y=y;
    one.id=id;
    pointTreeInsert(pt_tree,one);
}

void AddPolygonFromAddBeforeQuery(int id, int n, std::vector<std::pair<double, double> > &polygo) {
    Polygon add=parachange(polygo,id);
    polyTreeInsert(py_tree,add);
}

std::vector<int> QueryPointFromAddBeforeQuery(double x, double y) {
    tup test=tup(x,y);
    Stup test2=Stup(test);
    vector<int> ans;
    poly_ans=ans;
    py_tree.Search(test2.min,test2.max,CallForPolygon);
    return poly_ans;
}

std::vector<int> QueryPolygonFromAddBeforeQuery(int n, std::vector<std::pair<double, double> > &polygo) {
    vector<int> ans;
    point_ans=ans;
    Polygon test=parachange(polygo,1);
    pt_tree.Search(test.min,test.max,CallForPoint);
    return point_ans;
}
