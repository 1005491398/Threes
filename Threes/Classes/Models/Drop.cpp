//
//  Drop.cpp
//  Threes
//
//  Created by CT on 11/27/15.
//
//

#include "Drop.hpp"
#include "GameModel.hpp"
#include "CommponentManager.hpp"

using namespace std;
void printMap(int Map[xCount][yCount])
{
    for (int i = 0; i < xCount; ++i)
    {
        for (int j = 0; j < yCount; ++j)
        {
            cout<<Map[i][j]<<"\t";
        }
        cout<<endl;
    }
}

const int UnReachable = -1;

Drop::Drop()
{
//    memset(_map, 0, sizeof(int)*xCount*yCount);
}

void Drop::initExitList()
{
    for (int i=0; i<xCount; i++) {
        _exitPoints.push_back(new drop_point(0, i));
    }
}

int Drop::getUpValue(int x, int y)
{
    if (x>0) {
        auto value = _map[x-1][y];
        if (value!=0&&value!=-1) {
            return value+1;
        }
    }
    return 1;
}

int Drop::getLeftValue(int x, int y)
{
    if (x>0&&y>0) {
        auto value = _map[x-1][y-1];
        if (value!=0&&value!=-1) {
            return value+3;
        }
    }
    return 1;
}

int Drop::getRightValue(int x, int y)
{
    if (x>0&&y<yCount-1) {
        auto value = _map[x-1][y+1];
        if (value!=0&&value!=-1) {
            return value+2;
        }
    }
    return 1;
}

void Drop::initPathValue()
{
    for (auto point: _exitPoints) {
        _map[(int)point->x][(int)point->y] = 1;
    }
    for (int i=0; i<xCount; i++) {
        for (int j=0; j<yCount; j++) {
            if (Map[i][j] == 0) {
                _map[i][j] = UnReachable;
            }
            else if (_map[i][j] == 0)
            {
                auto value = getUpValue(i, j);
                if (value == 1)
                {
                    value = getLeftValue(i, j);
                    if (value == 1)
                    {
                        value = getRightValue(i, j);
                    }
                }
                _map[i][j] = value;
            }
        }
    }
}

int Drop::find(int x, int y)
{
    if (x<0 || x>xCount-1 || y<0 || y>yCount-1)
        return UnReachable;
    
    return _map[x][y];
}

int Drop::findUp(int x, int y)
{
    return find(x-1,y);
}

int Drop::findLeft(int x, int y)
{
    return find(x-1,y-1);
}

int Drop::findRight(int x, int y)
{
    return find(x-1,y+1);
}

void Drop::insertEliminatePoint(int x, int y, points_list::iterator *it)
{
    _eliminatePoints.insert(++(*it), new drop_point(x, y));
}

points_ptr Drop::findOneWay(int x, int y, points_list::iterator *it)
{
    points_ptr points = make_shared<Points>();
    auto xx = x, yy = y;
    
    for (int i=0; i<2*xCount; i++) {
        auto value = findUp(xx, yy);
        if (value == UnReachable) {
            value = findLeft(xx, yy);
            if (value == UnReachable) {
                value = findRight(xx, yy);
                if (value == UnReachable) {
                    // 无法移动
                    CCLOG("Can't move!!");
                    points->push_back(new drop_point(xx, yy));
                    return points;
                }
                else {
                    points->push_back(new drop_point(xx, yy));
                    points->push_back(new drop_point(xx-1, yy+1));
                    xx -= 1;
                    yy += 1;
                }
            }
            else {
                points->push_back(new drop_point(xx, yy));
                points->push_back(new drop_point(xx-1, yy-1));
                xx -= 1;
                yy -= 1;
            }
        }
        else {
            points->push_back(new drop_point(xx, yy));
            points->push_back(new drop_point(xx-1, yy));
            xx -= 1;
        }
        if (Map[xx][yy] == 2)
        {
            Map[x][y] = Map[xx][yy];
            Map[xx][yy] = 1;
            CCLOG("fruit %d-%d", xx, yy);
//            _eliminatePoints.push_back(new drop_point(xx, yy));
            insertEliminatePoint(xx, yy, it);
            break;
        }
        if (value == 1)
            break;
    }
    return points;
}

void Drop::init()
{
    _exitPoints.clear();
    _eliminatePoints.clear();
    memset(_map, 0, sizeof(_map));
    for (int i=xCount-1; i>=0; i--) {
        for (int j=0; j<yCount; j++) {
            auto fruit = GetCommponent<GameModel*>("GameModel")->getFuit(i, j);
            if (fruit==nullptr) {
                _eliminatePoints.push_back(new drop_point(i,j));
                Map[i][j] = 1;
            }
            else {
                Map[i][j] = 2;
            }
        }
    }
    initExitList();
    initPathValue();
}

void printPoints(points_ptr points)
{
    int i=0;
    for (auto point:*points) {
        printf("num:%d %d-%d\n", ++i, point->x, point->y);
    }
    printf("\n");
}

vec_points_ptr Drop::doDrop()
{
    init();
    printMap(Map);
    
    auto dropPosints = make_shared<vector<points_ptr>>();
    auto c = 0;
    for (auto it = _eliminatePoints.begin(); it != _eliminatePoints.end(); it++) {
        auto p = *it;
        CCLOG("eliminateCount %d p:%d-%d",++c,p->x,p->y);
        auto points = findOneWay(p->x, p->y, &it);
        if (points->size() != 0) {
            printPoints(points);
            dropPosints->push_back(points);
        }
    }
    return dropPosints;
}