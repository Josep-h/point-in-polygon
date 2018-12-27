#include "submit-2AddPointBeforeQueryPolygon.h"
#include<iostream>
void SetEnvironmentFromAddPointBeforeQueryPolygon() {
}

void AddPointFromAddPointBeforeQueryPolygon(int id, double x, double y) {
    iter2=point_map.find(id);
    //cout<<pt.id<<endl;//DEBUG
    //Stup one=Stup(tup(x,y));
    if(iter2!=point_map.end()) return ;
    TYPE mind[2],maxd[2];
    mind[0]=maxd[0]=x;
    mind[1]=maxd[1]=y;
    point_map[id]=tup(x,y);
    pt_tree.Insert(mind,maxd,id);
    return ;
}

std::vector<int> QueryPolygonFromAddPointBeforeQueryPolygon(int sz, std::vector<std::pair<double, double> > py) {
    QuaryPolygon(sz,py);
    return point_ans;
}
