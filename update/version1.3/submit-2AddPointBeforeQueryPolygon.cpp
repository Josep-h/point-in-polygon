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
    point_ans.clear();
    /*for(int i=0;i!=sz;i++)
    {
        std::cout<<py[i].first<<" "<<py[i].second<<std::endl;
    }*/
    polygon_test_now=&py;
    MinMax bound;
    bound.max[0]=bound.min[0]=py[0].first;
    bound.max[1]=bound.min[1]=py[0].second;
    static double xtp,ytp;
    for(int i=1;i<sz;i++)//这里做一个小小的尝试,看一下准确率会下降多少,下降到了0.917
    //这里的实验告诉我隔一个取一个似乎是不行的
    {
        xtp=py[i].first,ytp=py[i].second;
        if(xtp>bound.max[0])
            bound.max[0]=xtp;
        else if(xtp<bound.min[0])
            bound.min[0]=xtp;
        if(ytp>bound.max[1])
            bound.max[1]=ytp;
        else if(ytp<bound.min[1])
            bound.min[1]=ytp;
    }
    Sz=sz;
    pt_tree.Search(bound.min,bound.max,CallForPoint);
    return point_ans;
}
