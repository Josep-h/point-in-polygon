//
// Created by zhang on 18-12-4.
//

#include "submit-5MixQueryPolygon.h"

void SetEnvironmentFromMixQueryPolygon() {

}

void AddPointFromMixQueryPolygon(int id, double x, double y) {
    Stup one;
    one.p.x=x;
    one.p.y=y;
    one.id=id;
    pointTreeRemove(pt_tree,one);
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
    Polygon test=parachange(polygon,1);
    pt_tree.Search(test.min,test.max,CallForPoint);
    return point_ans;
}
