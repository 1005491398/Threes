//
//  Drop.hpp
//  Threes
//
//  Created by CT on 11/27/15.
//
//

#ifndef Drop_hpp
#define Drop_hpp

#include <stdio.h>
#include <iostream>
#include "cocos2d.h"
#include "Const.h"
#include "Singleton.hpp"
#include <vector>
#include <list>
USING_NS_CC;

using Points = std::vector<drop_point*>;
using points_list = std::list<drop_point*>;
using points_ptr = std::shared_ptr<Points>;
using vec_points_ptr = std::shared_ptr<std::vector<points_ptr>>;

class Drop {
protected:
    friend class Singleton<Drop>;
    
private:
    Points _exitPoints;         //出口
    points_list _eliminatePoints;
    int _map[xCount][yCount];
    int Map[xCount][yCount];
    
private:
    void init();
    
    void initExitList();
    void initPathValue();
    int getUpValue(int x, int y);
    int getLeftValue(int x, int y);
    int getRightValue(int x, int y);
    inline int find(int x, int y);
    int findUp(int x, int y);
    int findLeft(int x, int y);
    int findRight(int x, int y);
    void insertEliminatePoint(int x, int y, points_list::iterator *it);
    points_ptr findOneWay(int x, int y, points_list::iterator *it = nullptr);
public:
    Drop();
    ~Drop() {}
    
    vec_points_ptr doDrop();
};

#endif /* Drop_hpp */
