#include "submit-1AddPolygonBeforeQueryPoint.h"

void SetEnvironmentFromAddPolygonBeforeQueryPoint() {;
}

std::vector<int> QueryPointFromAddPolygonBeforeQueryPoint(double x, double y) {
    TYPE mind[2],maxd[2];
    mind[0]=maxd[0]=(tup_test_now).x=x;
    mind[1]=maxd[1]=(tup_test_now).y=y;
    //Stup test2=Stup(tup_test_now);
    vector<int> ans;
    poly_ans=ans;
    py_tree.Search(mind,maxd,CallForPolygon);
    return poly_ans;
}

void AddPolygonFromAddPolygonBeforeQueryPoint(int id, int n, std::vector<std::pair<double, double> > &py) {
    MinMax bound;
    bound.max[0]=bound.min[0]=py[0].first;
    bound.max[1]=bound.min[1]=py[0].second;
    TYPE2 xtp,ytp;
    for(int i=1;i<n;i++)
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
    
    poly_map.insert(pair<polygon_id,Polygon>(id,py));
    py_tree.Insert(bound.min,bound.max,id);
    return ;
}
