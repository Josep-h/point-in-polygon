#include "submit-3AddBeforeQuery.h"

void SetEnvironmentFromAddBeforeQuery() {
;
}

void AddPointFromAddBeforeQuery(int id, double x, double y) {
    Stup one=Stup(tup(x,y));
    one.id=id;
    pointTreeInsert(pt_tree,one);
}

void AddPolygonFromAddBeforeQuery(int id, int n, std::vector<std::pair<double, double> > &polygon) {
    polyTreeInsert(polygon,id);
}

std::vector<int> QueryPointFromAddBeforeQuery(double x, double y) {
    tup_test_now=tup(x,y);
    Stup test2=Stup(tup_test_now);
    vector<int> ans;
    poly_ans=ans;
    py_tree.Search(test2.min,test2.max,CallForPolygon);
    return poly_ans;
}

std::vector<int> QueryPolygonFromAddBeforeQuery(int n, std::vector<std::pair<double, double> > &polygon) {
    vector<int> ans;
    point_ans=ans;
    polygon_test_now=polygon;
    double xmax,xmin,ymin,ymax;
    MinMax bound;
    int sz=polygon.size();
    for(int i=0;i!=sz;i++)
    {
        if(polygon[i].first>xmax)
            xmax=polygon[i].first;
        else if(polygon[i].first<xmin)
            xmin=polygon[i].first;
        if(polygon[i].second>ymax)
            ymax=polygon[i].second;
        else if(polygon[i].second<ymin)
            ymin=polygon[i].second;
    }
    bound.min[0]=xmin;bound.min[1]=ymin;
    bound.max[0]=xmax;bound.max[2]=ymax;
    pt_tree.Search(bound.min,bound.max,CallForPoint);
    return point_ans;
}
