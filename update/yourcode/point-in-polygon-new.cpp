#include<vector>
using namespace std;

class tup{//def of the tuple
    public:
    double x;
    double y;
    tup(){}
    tup(double x,double y):x(x),y(y){}
    bool operator < (const tup &now) const{
        return y<now.y;
    }
    bool operator == (const tup &now) const{
        return y==now.y&&x==now.x;
    }
};

bool online(pair<double,double> bg,pair<double,double> nd,pair<double,double> p)
{
    double dx,dy,dx1,dy1;
    dx=nd.first-bg.first;
    dy=nd.second-bg.second;
    dx1=p.first-bg.first;
    dy1=p.second-bg.second;
    return (dx*dy1-dy*dx1)&&(dx1*(dx1-dx)<0||dy1*(dy1-dy)<0);
}

bool same1(pair<pair<double,double>,pair<double,double>> l,pair<double,double> p1,pair<double,double> p2)
{
    double dx,dy,dx1,dy1,dx2,dy2;
    dx=l.second.first-l.first.first;
    dy=l.second.second-l.first.second;
    dx1=p1.first-l.second.first;
    dy1=p1.second-l.second.second;
    dx2=p2.first-l.second.first;
    dy2=p2.second-l.second.second;
    return (dx*dy1-dy*dx1)*(dx*dy2-dy*dx2)>=0;
}

bool intersect(pair<pair<double,double>,pair<double,double>> l1,pair<pair<double,double>,pair<double,double>> l2)
{

}

bool inside(vector<pair<double,double>> &poly,pair<double,double> p)
{
    int c=0,i;
    pair<pair<double,double>,pair<double,double>> l1,l2;
    l1.first=p;
    l1.second=p;
    l1.second.first=1000000;
    for(int i=0;i!=poly.size();i++)
    {
        l2.first=poly[i];
        l2.second=poly[i+1];
        if(intersect(l1,l2)||online(l1.first,l1.second,poly[i+2])&&(!online(l1.first,l1.second,poly[i+2])&&!same1(l1,poly[i],poly[i+2])||online(l1.first,l1.second,poly[i+2])&&!same1(l1,poly[i],poly[i+3])))
        {
            c++;
        }
        return c%2;
    }
}