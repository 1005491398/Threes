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

GameModel::GameModel(const std::string &key):Commponent(key)
{
    init();
}

void GameModel::initRandomFruits()
{
    for (int i=0; i<xCount; i++) {
        for (int j=0; j<yCount; j++) {
            auto type = (int)(CCRANDOM_0_1()*10);
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
        fruits[sx][sy]->setXY(sx, sy);
        fruits[dx][dy]->setXY(dx, dy);
        dispatchEvent(EVENT_EXCHANGE);
    }
}

void GameModel::eliminateFruit(int x, int y)
{
    if (fruits[x][y]) {
        fruits[x][y]->remove();
        fruits[x][y] = nullptr;
    }
}