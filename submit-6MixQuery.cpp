#include "submit-6MixQuery.h"

void SetEnvironmentFromMixQuery() {
;
}

void AddPointFromMixQuery(int id, double x, double y) {
    Stup one=Stup(tup(x,y));
    one.id=id;
    pointTreeInsert(pt_tree,one);
}

void DeletePointFromMixQuery(int id) {
    map<point_id,Stup>::iterator iter=point_map.find(id);
    if(iter==point_map.end())
    return;
    Stup temp=iter->second;
    pointTreeRemove(pt_tree,temp);
}

std::vector<int> QueryPointFromMixQuery(double x, double y) {
    tup_test_now=tup(x,y);
    Stup test2=Stup(tup_test_now);
    vector<int> ans;
    poly_ans=ans;
    py_tree.Search(test2.min,test2.max,CallForPolygon);
    return poly_ans;
}

void AddPolygonFromMixQuery(int id, int n, std::vector<std::pair<double, double>> &polygon) {
    polyTreeInsert(polygon,id);
}

void DeletePolygonFromMixQuery(int id) {
    map<polygon_id,Polygon>::iterator iter=poly_map.find(id);
    if(iter==poly_map.end())
    return;
    polyTreeRemove(py_tree,id);
}

std::vector<int> QueryPolygonFromMixQuery(int n, std::vector<std::pair<double, double>> &polygon) {
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

