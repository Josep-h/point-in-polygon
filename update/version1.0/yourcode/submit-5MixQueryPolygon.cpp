//
// Created by zhang on 18-12-4.
//

#include "submit-5MixQueryPolygon.h"

void SetEnvironmentFromMixQueryPolygon() {
;
}

void AddPointFromMixQueryPolygon(int id, double x, double y) {
    Stup one=Stup(tup(x,y));
    one.id=id;
    pointTreeInsert(pt_tree,one);
}

void DeletePointFromMixQueryPolygon(int id) {
    map<point_id,Stup>::iterator iter=point_map.find(id);
    if(iter==point_map.end())
    return;
    Stup temp=iter->second;
    pointTreeRemove(pt_tree,temp);
}

std::vector<int> QueryPolygonFromMixQueryPolygon(int n, std::vector<std::pair<double, double> > &polygon) {
    vector<int> ans;
    point_ans=ans;
    polygon_test_now=parachange(polygon,1);
    pt_tree.Search(polygon_test_now.min,polygon_test_now.max,CallForPoint);
    return point_ans;
}
