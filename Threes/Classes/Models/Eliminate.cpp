//
//  Eliminate.cpp
//  Threes
//
//  Created by CT on 11/6/15.
//
//

#include "Eliminate.hpp"
#include "CommponentManager.hpp"
#include "GameModel.hpp"

//void printMap(int Map[xCount][yCount])
//{
//    for (int i = 0; i < xCount; ++i)
//    {
//        for (int j = 0; j < yCount; ++j)
//        {
//            cout<<Map[i][j]<<"\t";
//        }
//        cout<<endl;
//    }
//}

template <typename T>
void printT(T t)
{
    for (auto point:t)
    {
        point.toString();
    }
}

void Eliminate::threes()
{
    memset(hMap, 0, sizeof(hMap));
    for (int i = 0; i < xCount; ++i)
    {
        int startPos[] = {0,0};
        int len[] = {1,1};
        static auto cpv = [&](int value, int startPosValue, int index, int j){
            if(j<yCount && startPosValue != 0 && value == startPosValue)
            {
                ++len[index];
            }
            else
            {
                if(len[index]>=3)
                {
                    CCLOG("%dThrees!!!%d\n",i,index);
                    auto tmpMap = xx[index].find(i);
                    if (tmpMap != xx[index].end()) {
                        tmpMap->second->push_back(new Range(startPos[index],j-1));
                    }
                    else
                    {
                        auto nodes = new Nodes();
                        nodes->push_back(new Range(startPos[index],j-1));
                        xx[index][i] = nodes;
                    }
                    // 在冲突 数组里面检测是否有冲突点
                    if(len[index]<7)
                    {
                        for (int k=startPos[index]; k<=j-1; k++) {
                            if (index == 0) {
                                hMap[i][k] += 1;
                                if (hMap[i][k]>1) {
                                    clashs.push_back(new Vec2(i, k));
                                }
                            }
                            else {
                                hMap[k][i] += 1;
                                if (hMap[k][i]>1) {
                                    clashs.push_back(new Vec2(k, i));
                                }
                            }
                        }
                    }
                }
                len[index] = 1;
                startPos[index] = j;
            }
        };
        for (int j = 1; j < yCount+1; ++j)  //  此处多访问了 一个数组纬度
        {
            cpv(_map[i][j], _map[i][startPos[0]], 0, j);
            cpv(_map[j][i], _map[startPos[1]][i], 1, j);
        }
    }
    printMap(hMap);
}

Range* findIndex(const XYMap &array, int index, int value)
{
    auto nodes = array.find(index);
    if (nodes != array.end()) {
        for (auto range:*nodes->second) {
            if (range->rangeIn(value)) {
                return range;
            }
        }
    }
    return nullptr;
}

// ***@*** 七连中间未处理
bool checkSelfIsTrible( int i, Range *range )
{
    if (i - range->a >= 3) {
        range->b = i-1;
        return false;
    }
    else if (range->b - i >= 3) {
        range->a = i+1;
        return false;
    }
    return false;
}

Priority Eliminate::getPriority(Range *range)
{
    auto len = std::abs(range->b-range->a);
    if (len>=4) {
        return Priority::FIVE;
    }
    else if (len>=3) {
        return Priority::FOUR;
    }
    else if (len>=2) {
        return Priority::THREE;
    }
    return static_cast<Priority>(0);
}

Priority addPriority(Priority a, Priority b)
{
    return static_cast<Priority>(static_cast<int>(a) + static_cast<int>(b));
}

inline void setNormal(Threes &threes, int line, int start, int end, bool isy = false)
{
    if (isy) {
        threes.yLine = line;
        threes.ystart = start;
        threes.yend = end;
    }
    else {
        threes.xLine = line;
        threes.xstart = start;
        threes.xend = end;
    }
}

inline void setCross(Threes &threes, int xLine, int xstart, int xend, int yLine, int ystart, int yend)
{
    setNormal(threes, xLine, xstart, xend);
    setNormal(threes, yLine, ystart, yend, true);
}

void Eliminate::sortClashs()
{
    
}

void Eliminate::processClash(int x, int y) {
    Range* xArray = findIndex(xx[0], x, y);
    Range* yArray = findIndex(xx[1], y, x);
    if (xArray && yArray) {
        int x1 = xArray->a, y1 = xArray->b;
        int x2 = yArray->a, y2 = yArray->b;
        // 存储十字形状
        auto threes = std::make_shared<Threes>();
        threes->prrority = addPriority(Priority::CROSS, std::max(getPriority(xArray), getPriority(yArray)));
        setCross(*threes, x, x1, y1, y, x2, y2);
        _eliminate->push_back(threes);
        
        xArray->setRangeDisable();
        yArray->setRangeDisable();
        for (int i=x1; i<y1; i++) {
            if (hMap[x][i] != 0) {
                processClash(x, i);
            }
        }
        for (int i=x2; i<y2; i++) {
            if (hMap[i][y] != 0) {
                processClash(i, y);
            }
        }
    }
    else if (xArray) {
        if (checkSelfIsTrible(x, xArray)) {
            xArray->setRangeDisable();
        }
    }
    else if (yArray) {
        if (checkSelfIsTrible(y, yArray)) {
            yArray->setRangeDisable();
        }
    }
}

void Eliminate::processClashs()
{
    for (auto clashP:clashs) {
        processClash(clashP->x, clashP->y);
    }
}

void Eliminate::processLast()
{
    for (int i=0; i<2; i++) {
        for (auto nodes:xx[i]) {
            for (auto range:*nodes.second) {
                if (range->isEnable()) {
                    auto threes = std::make_shared<Threes>();
                    threes->prrority = getPriority(range);
                    setNormal(*threes, nodes.first, range->a, range->b, i==1);
                    _eliminate->push_back(threes);
                }
            }
        }
    }
}

void Eliminate::init()
{
//    _map
    for (int i=0; i<xCount; i++) {
        for (int j=0; j<yCount; j++) {
            auto fruit = GetCommponent<GameModel*>("GameModel")->getFuit(i, j);
            _map[i][j] = fruit!=nullptr?fruit->ftype():0;
        }
    }
    printMap(_map);
//    xVec.clear();
//    yVec.clear();
    // clear 可能不会是放 容器的空间
    clashs.clear();
    xx[0].clear();
    xx[1].clear();
    _eliminate = std::make_shared<ThreesVec>();
}

ThreesVec_ptr Eliminate::doEliminate()
{
    init();
    threes();
    processClashs();
    processLast();
    for (auto threes:*_eliminate) {
        threes->toString();
    }
    return _eliminate;
}