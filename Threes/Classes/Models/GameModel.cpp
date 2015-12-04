//
//  GameModel.cpp
//  Threes
//
//  Created by CT on 11/12/15.
//
//

#include "GameModel.hpp"
#include "FruitFactory.hpp"
const std::string GameModel::EVENT_EXCHANGE = "EVENT_EXCHANGE";

int testMap[9][9] = {
    {1,2,3,4,3,2,1,2,3},
    {4,1,5,5,6,5,6,3,3},
    {3,2,5,2,5,2,5,2,1},
    {3,2,4,5,4,5,1,2,2},
    {2,3,4,5,3,4,1,4,5},
    {3,6,4,1,4,5,6,3,6},
    {6,6,3,5,3,4,1,6,3},
    {6,3,3,2,1,6,4,3,6},
    {1,1,2,6,4,4,5,1,0},
};

GameModel::GameModel(const std::string &key):Commponent(key)
{
    init();
}

void GameModel::initRandomFruits()
{
    for (int i=0; i<xCount; i++) {
        for (int j=0; j<yCount; j++) {
            auto type = testMap[i][j];// || (int)(CCRANDOM_0_1()*10);
            auto fruit = FruitFactory::getInstance()->getFruitByType(FruitType(type%6 + 1));
            fruit->setXY(i, j);
            fruits[i][j] = fruit;
        }
    }
}

void GameModel::init()
{
    _logic = make_shared<GameLogic>();
    initRandomFruits();
}

void GameModel::exchange(int sx,int sy,int dx,int dy)
{
    if (sx!=sy || dx!=dy) {
        auto tmp = fruits[sx][sy];
        fruits[sx][sy] = fruits[dx][dy];
        fruits[dx][dy] = tmp;
        if (fruits[sx][sy]) {
            fruits[sx][sy]->setXY(sx, sy);
        }
        if (fruits[dx][dy]) {
            fruits[dx][dy]->setXY(dx, dy);
        }
        dispatchEvent(EVENT_EXCHANGE);
    }
}

void GameModel::moveDown(int sx,int sy,int dx,int dy)
{
    if (sx!=sy || dx!=dy) {
        fruits[dx][dy] = fruits[sx][sy];
        fruits[sx][sy] = nullptr;
        if (fruits[dx][dy]) {
            fruits[dx][dy]->setXY(dx, dy);
        }
//        dispatchEvent(EVENT_EXCHANGE);
    }
}

void GameModel::eliminateFruit(int x, int y)
{
    if (fruits[x][y]) {
        fruits[x][y]->remove();
        fruits[x][y] = nullptr;
    }
}