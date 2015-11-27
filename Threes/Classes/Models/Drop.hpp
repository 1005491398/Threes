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
USING_NS_CC;

using Points = std::vector<Vec2>;
class Drop {
private:
    Points _exitPoints;
    int _map[xCount][yCount];
    int Map[xCount][yCount];
    
private:
    void initExitList();
    void initPathValue();
    int getUpValue(int x, int y);
    int getLeftValue(int x, int y);
    int getRightValue(int x, int y);
    int find(int x, int y);
    int findUp(int x, int y);
    int findLeft(int x, int y);
    int findRight(int x, int y);
    Points findOneWay(int x, int y);
public:
    Drop();
    ~Drop() {}
    
    void doDrop();
};

#endif /* Drop_hpp */
