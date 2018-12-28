//这个版本使用四分树,但是没有使用R树快,差距也并不大,
//但是使用的是非平衡的插入方法所以会慢一些,但是这个板子的平衡方法似乎有问题.
//如果使用平衡的方法可能速度就上去了
#include "yourcode/submit-1AddPolygonBeforeQueryPoint.h"
#include "yourcode/submit-2AddPointBeforeQueryPolygon.h"
#include "yourcode/submit-3AddBeforeQuery.h"
#include "yourcode/submit-4MixQueryPoint.h"
#include "yourcode/submit-5MixQueryPolygon.h"
#include "yourcode/submit-6MixQuery.h"

#include "yourcode/submit-1AddPolygonBeforeQueryPoint.cpp"
#include "yourcode/submit-2AddPointBeforeQueryPolygon.cpp"
#include "yourcode/submit-3AddBeforeQuery.cpp"
#include "yourcode/submit-4MixQueryPoint.cpp"
#include "yourcode/submit-5MixQueryPolygon.cpp"
#include "yourcode/submit-6MixQuery.cpp"

#include "yourcode/RTree.h"
#include "yourcode/header.h"
#include "yourcode/header.cpp"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <time.h>
#include <string>
//这个版本采用的区间树,但不知道什么原因,使用的时间非常之多
int environment_variable(0);

void PrintAnswerOut(std::fstream &fout, std::vector<int> &answer_vector)
{
    for (auto answer : answer_vector) {
        fout << answer << " ";
    }
    fout << std::endl;
}

void AddPoint(std::fstream &fin) {
    int id;
    double x;
    double y;
    fin >> id;
    fin >> x >> y;
    //cout<<"AddPoint..."<<endl;
    switch (environment_variable) {
        case 2: {
            AddPointFromAddPointBeforeQueryPolygon(id, x, y);
            break;
        }
        case 3: {
            AddPointFromAddBeforeQuery(id, x, y);
            break;
        }
        case 5: {
            AddPointFromMixQueryPolygon(id, x, y);
            break;
        }
        case 6: {
            AddPointFromMixQuery(id, x, y);
            break;
        }
        default:
            std::cout << "Good morning, and in case I don't see ya, good afternoon, good evening, and good night!" << std::endl;
    }
}

void DeletePoint(std::fstream &fin) {
    int id;
    fin >> id;
    //cout<<"DeletePoint..."<<endl;
    switch (environment_variable) {
        case 5: {
            DeletePointFromMixQueryPolygon(id);
            break;
        }
        case 6: {
            DeletePointFromMixQuery(id);
            break;
        }
        default: {
            std::cout << "Don't cry because it's over, smile because it happened." << std::endl;
        }
    }
}

void QueryPoint(std::fstream &fin, std::fstream &fout) {
    double x;
    double y;
    fin >> x >> y;
    std::vector<int> query_answer;
    //cout<<"QuaryPoint..."<<endl;
    switch (environment_variable) {
        case 1: {
            query_answer = QueryPointFromAddPolygonBeforeQueryPoint(x, y);
            break;
        }
        case 3: {
            query_answer = QueryPointFromAddBeforeQuery(x, y);
            break;
        }
        case 4: {
            query_answer = QueryPointFromMixQueryPoint(x, y);
            break;
        }
        case 6: {
            query_answer = QueryPointFromMixQuery(x, y);
            break;
        }
        default: {
            std::cout << "You can't connect the dots looking forward; you can only connect them looking backwards." << std::endl;
        }
    }
    //cout<<query_answer.size()<<endl;//DEBUG
    PrintAnswerOut(fout, query_answer);
}

void AddPolygon(std::fstream &fin) {
    int id;
    int n;
    std::vector< std::pair<double, double> > polygon;
    fin >> id;
    fin >> n;
    double x;
    double y;
    //cout<<"AddPolygon..."<<endl;
    for (int i = 0; i < n; ++i) {
        fin >> x >> y;
        polygon.emplace_back(std::make_pair(x, y));
    }

    switch (environment_variable) {
        case 1: {
            AddPolygonFromAddPolygonBeforeQueryPoint(id, n, polygon);
            break;
        }
        case 3: {
            AddPolygonFromAddBeforeQuery(id, n, polygon);
            break;
        }
        case 4: {
            AddPolygonFromMixQueryPoint(id, n, polygon);
            break;
        }
        case 6: {
            AddPolygonFromMixQuery(id, n, polygon);
            break;
        }
        default: {
            std::cout << "We slept on floors. We waded across rivers." << std::endl;
        }
    }
}

void DeletePolygon(std::fstream &fin) {
    int id;
    fin >> id;
    //cout<<"DeletePolygon..."<<endl;
    switch (environment_variable) {
        case 4: {
            DeletePolygonFromMixQueryPoint(id);
            break;
        }
        case 6: {
            DeletePolygonFromMixQuery(id);
            break;
        }
        default: {
            std::cout << "We accept the love we think we deserve." << std::endl;
        }
    }
}

void QueryPolygon(std::fstream &fin, std::fstream &fout) {
    int n;
    std::vector< std::pair<double, double> > polygon;
    fin >> n;
    double x;
    double y;
    //cout<<"QuaryPolygon..."<<endl;
    for (int i = 0; i < n; ++i) {
        fin >> x >> y;
        polygon.emplace_back(std::make_pair(x, y));
    }
    std::vector<int> query_answer;
    switch (environment_variable) {
        case 2: {
            query_answer = QueryPolygonFromAddPointBeforeQueryPolygon(n, polygon);
            break;
        }
        case 3: {
            query_answer = QueryPolygonFromAddBeforeQuery(n, polygon);
            break;
        }
        case 5: {
            query_answer = QueryPolygonFromMixQueryPolygon(n, polygon);
            break;
        }
        case 6: {
            query_answer = QueryPolygonFromMixQuery(n, polygon);
            break;
        }
        default: {
            std::cout << "I'm not a hero, but I have served in a company full of them." << std::endl;
        }
    }
    //cout<<query_answer.size()<<endl;
    PrintAnswerOut(fout, query_answer);
}

int main() {
    time_t t; t = time(NULL);
    std::cout << "Hello, World!" << std::endl;
    std::fstream fin("test.in", std::fstream::in);
    std::fstream fout("test.out", std::fstream::out);

    fin >> environment_variable;

    switch (environment_variable) {
        case 1: {
            SetEnvironmentFromAddPolygonBeforeQueryPoint();
            break;
        }
        case 2: {
            SetEnvironmentFromAddPointBeforeQueryPolygon();
            break;
        }
        case 3: {
            SetEnvironmentFromAddBeforeQuery();
            break;
        }
        case 4: {
            SetEnvironmentFromMixQueryPoint();
            break;
        }
        case 5: {
            SetEnvironmentFromMixQueryPolygon();
            break;
        }
        case 6: {
            SetEnvironmentFromMixQuery();
            break;
        }
        default:
            std::cout << "Who am I, where am I from, to where am I going" << std::endl;
    }

    int user_operation(0);
    while (fin >> user_operation) {
        switch (user_operation) {
            case 1: {
                // Add Point
                AddPoint(fin);
                break;
            }
            case 2: {
                // Delete Point
                DeletePoint(fin);
                break;
            }
            case 3: {
                // Query Point
                QueryPoint(fin, fout);
                break;
            }
            case 4: {
                // Add Polygon
                AddPolygon(fin);
                break;
            }
            case 5: {
                // Delete Polygon
                DeletePolygon(fin);
                break;
            }
            case 6: {
                // QueryPolygon
                QueryPolygon(fin, fout);
                break;
            }
            default: {
                // reach file ending
                std::cout << "! Hope is a good thing, maybe the best of things, and no good thing ever dies." << std::endl;
            }
        }
    }

    fin.close();
    fout.close();

    std::cout << "Well Done!" << std::endl;
    time_t t2; t2 = time(NULL);
    cout<<t2-t<<endl;
    for(;;);
    return 0;
}