//
//  Eliminate.hpp
//  Threes
//
//  Created by CT on 11/6/15.
//
//

#ifndef Eliminate_hpp
#define Eliminate_hpp

#include <stdio.h>
#include "Singleton.hpp"
#include <iostream>
#include <vector>
#include <Map>
#include <list>
#include <time.h>
#include <cstdio>
#include "Vec2.h"
#include "Const.h"
USING_NS_CC_MATH;

struct Range{
    int a,b;
    Range(int _a, int _b):a(_a),b(_b)
    {}
    void toString()
    {
        CCLOG("Range is %d-%d\n",a,b);
    }
    inline bool rangeIn(int num)
    {
        return num>=a && num<=b;
    }
    void setRangeDisable()
    {
        a = -1;
        b = -1;
    }
    inline bool isEnable() { return a!=-1&&b!=-1; }
};

enum class Priority{
    THREE = 0x3,
    FOUR = 1<<3,
    FIVE = 1<<4,
    CROSS = 1<<5
};

struct Threes {
    Priority prrority;
    int xLine, xstart, xend, yLine, ystart, yend;
    Threes():xLine(-1), xstart(0), xend(0), yLine(-1), ystart(0), yend(0) {}
    ~Threes(){}
    void toString() {
        switch(prrority)
        {
            case Priority::FIVE: CCLOG("FIVE"); break;
            case Priority::CROSS: CCLOG("FIVE"); break;
            case Priority::THREE: CCLOG("THREE"); break;
            case Priority::FOUR: CCLOG("FOUR"); break;
            default:
                CCLOG("FKFK %d", (int)prrority);
        }
        CCLOG("x:%d(%d-%d), y:%d(%d-%d)", xLine, xstart, xend, yLine, ystart, yend);
    }
};

using ThreesVec = std::vector<std::shared_ptr<Threes>>;
using Nodes = std::list<Range *>;
using XYMap = std::map<int, Nodes *>;
using ThreesVec_ptr = std::shared_ptr<ThreesVec>;

class Eliminate {
private:
    int hMap[xCount][yCount];
//    XYMap xVec, yVec;
    XYMap xx[2];
    std::vector<Vec2 *> clashs;
    int _map[xCount][yCount];
    ThreesVec_ptr _eliminate;
    
private:
    void init();
    void threes();
    void processClashs();
    inline void processClash(int x, int y);
    void processLast();
    Priority getPriority(Range *range);
protected:
    Eliminate() {};
    ~Eliminate() {};
    
    friend class Singleton<Eliminate>;
public:
    ThreesVec_ptr doEliminate();
};

#endif /* Eliminate_hpp */
