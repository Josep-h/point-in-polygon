#include"basci_.cpp"
#include"math_added.cpp"
#include<map>
#define NoofCellsx 10 
#define NoofCellsy 10
using namespace std;
#define delta 0.005
class rectangle{
    public:
    tup min;
    tup max;
    tup cells[NoofCellsx][NoofCellsy];
    float sizex;
    float sizey;
    int WIDTH,HIGHT;
    vector<edge> polygon;
    map<edge,vector<tup> > edge_cells;//the cells crossed by an edge
    map<tup,vector<edges> > cell_edges;//the egdes cross the cell
    rectangle(){}
    rectangle(tup min,tup max);
    vector<tup> Cells(edge e);//return the cells crossed by edge
    MarkQuasiPoint FindCloestPointofPtoEdges(tup p,vector<tup> &cells);
    MarkQuasiPoint FindAquasiClosePoint(tup p,vector<tup> &initcells);
    int InclusionQuery(tup p,MarkQuasiPoint q);
};


//find the quasi closed point of p and return it's edge dis
MarkQuasiPoint rectangle::FindAquasiClosePoint(tup p,vector<tup> &initcells)
{
    MarkQuasiPoint q;
    vector<tup> curcells=initcells;
    while(1)
    {
        //set flag for each of the curcells
        q=FindCloestPointofPtoEdges(p,curcells);
        vector<tup> cells_crossed=Cells(edge(p,q.quasi_point));
        //if each cells been used
        int sz=cells_crossed.size();bool flag=0;
        for(int i=0;i!=sz;i++)
        {
            if(cells_crossed[i].flag==0)
            {flag=1;break;}
        }
        if(!flag)
        {
            break;
        }
        else curcells=cells_crossed;
    }
    return q;
}

int rectangle::InclusionQuery(tup p,MarkQuasiPoint q)
{
    if(Distance_P_P(p,q.quasi_point)<=delta) return 2;//1 mines on the edge
    if()
    {
        if(IsOnTheLeftSide(p,q.e))
            return 1;
    }
    else if()
    {
        if(IsOnTheLeftSide(p,q.e)&&IsOnTheLeftSide(p,q.another))
            return 1;
        if(IsOnTheRightSide(p,q.e)&&IsOnTheRightSide(p,q.another))
            return 0;
        if(IsOnTheRightSide(q.another,q.e))
            return 1;
    }
    return 0;
}

rectangle::rectangle(tup in_min,tup in_max)
{
    min=in_min;max=in_max;
    WIDTH=max.x-min.x;
    HIGHT=max.y-min.y;
    sizex=WIDTH/NoofCellsx;
    sizey=WIDTH/NoofCellsy;
    int sz=polygon.size();
    for(int i=0;i!=NoofCellsx;i++)//get the cells
    {
        for(int j=0;j!=NoofCellsy;j++)
        {
            cells[j][i].x=min.x+i*sizex;
            cells[j][i].y=min.y+j*sizey;
        }
    }
    /*for(int i=0;i!=sz;i++)
    {
        Cells(polygon[i]);//store the map from the beginning
    }*/
}
//---------------------------------------------
vector<tup> rectangle::Cells(edge e)//return the cells crossed by an edge
{
    vector<tup> ans;
    for(int i=0;i!=NoofCellsx;i++)
    {
        float test_x=min.x+i*sizex;
        float test_y=edge_x(e,test_x);
        float test_y_next=edge_x(e,test_x+sizex);
        int change;
        if(!(test_y<min.y||test_y>max.y))
        {
            change=(test_y-min.y)/sizey;
            float new_y=min.y+change*sizey;
            ans.push_back(tup(test_x,new_y));
        }
        if(!(test_y_next<min.y||test_y_next>max.y))
        {
            int change_new=(test_y_next-min.y)/sizey;
            if(change_new>change)
            {
                while(change_new>change)
                {
                    if(!(test_y_next<min.y||test_y_next>max.y))
                    ans.push_back(tup(test_x,min.y+change_new*sizey));
                    change_new--;
                    test_y_next-=sizey;
                }
            }
            if(change_new<change)
            {
                while(change_new<change)
                {
                    if(!(test_y_next<min.y||test_y_next>max.y))
                    ans.push_back(tup(test_x,min.y+change_new*sizey));
                    change_new++;
                    test_y_next+=sizey;
                }
            }
        }
        /*edge_cells.insert(pair<edge,vector<tup> >(e,ans));*/
    }
    return ans;
}

MarkQuasiPoint rectangle::FindCloestPointofPtoEdges(tup p,vector<tup> &cells)
{
    int sz;
    float min=0;bool flag=0;
    MarkQuasiPoint q;//ans
    edge e;//mark theedge cross the cells
    for(int i=0;i!=sz;i++)
    {
        if(!flag)
        {
            q=Distance_P_E(p,e);
            flag=1;
        }
        else
        {
            MarkQuasiPoint tp=Distance_P_E(p,e);
            if(tp.dis<q.dis) q=tp;
        }
    }
    sz=cells.size();
    for(int i=0;i!=sz;i++)
    {
        cells[i].flag=1;
    }
    return q;
}


