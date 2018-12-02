#include"triangulate.cpp"
#include<vector>
#include<iostream>
using namespace std;
int main()
{
    tup a_1=tup(1,1),a_2=tup(1,5),a_3=tup(3,4);
    tri trian=tri(1,a_1,a_2,a_3);
    while(1)
    {
        float x,y;
        cin>>x>>y;
        tup tt=tup(x,y);
        cout<<trian.test(tt)<<endl;
    }
    return 0;
}