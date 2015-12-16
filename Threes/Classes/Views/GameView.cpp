//
//  GameView.c
//  Threes
//
//  Created by CT on 11/6/15.
//
//

#include "GameView.h"
#include "Const.h"
#include "FruitFactory.hpp"
#include "CommponentManager.hpp"

#pragma omp parallel for
const float MoveDownTime = 0.777f;

GameView::~GameView()
{
    
}

inline const Vec2 getFruitPosition(int x, int y)
{
    return Vec2(y*Width+Width/2 , (xCount-x-1)*Height+Height/2);
}

void GameView::addFruit(int x, int y)
{
    auto fruit = GetCommponent<GameModel*>("GameModel")->getFuit(x, y);
    if (fruit) {
        auto sp = fruit->getSprite();
        this->addChild(sp);
        sp->setPosition(getFruitPosition(x,y));
    }
}

void GameView::doMoveDownAnimation(const Msg &msg)
{
    auto args = (MoveDown&)msg;
    auto fruit = args.fruit;
    if (fruit) {
        auto sp = fruit->getSprite();
        sp->stopAllActions();
        sp->runAction(MoveTo::create(MoveDownTime, getFruitPosition(fruit->px(), fruit->py())));
    }
}

bool GameView::init()
{
    auto bg = Sprite::create("assets/323.jpg");
    this->addChild(bg);
    auto size = Director::getInstance()->getWinSize();
    bg->setPosition(size.width/2, size.height/2);
    
    auto update = [=](const Msg &msg){
        for (int i=0; i<xCount; i++) {
            for (int j=0; j<yCount; j++) {
                auto fruit = GetCommponent<GameModel*>("GameModel")->getFuit(i, j);
                if (fruit) {
                    auto sp = fruit->getSprite();
                    sp->setPosition(getFruitPosition(i,j));
                }
            }
        }
    };
    
    auto addNew = [this](const Msg &msg){
        auto args = (MoveDown&)msg;
        auto fruit = args.fruit;
        if (fruit) {
            auto sp = fruit->getSprite();
            this->addChild(sp);
            sp->stopAllActions();
            sp->setPosition(getFruitPosition(fruit->px()-1, fruit->py()));
            sp->runAction(MoveTo::create(MoveDownTime, getFruitPosition(fruit->px(), fruit->py())));
        }
    };
    
    GetCommponent<GameModel*>("GameModel")->registerEvent(GameModel::EVENT_EXCHANGE, update);
    GetCommponent<GameModel*>("GameModel")->registerEvent(GameModel::EVENT_ADD_FRUIT, addNew);
    GetCommponent<GameModel*>("GameModel")->registerEvent(GameModel::EVENT_MOVEDOWN, CC_CALLBACK_1(GameView::doMoveDownAnimation, this));
    
//    GetCommponent<GameLogic*>("GameLogic")->registerEvent(GameLogic::EVENT_DROP, update);
    
    for (int i=0; i<xCount; i++) {
        for (int j=0; j<yCount; j++) {
            addFruit(i, j);
        }
    }
    return true;
}