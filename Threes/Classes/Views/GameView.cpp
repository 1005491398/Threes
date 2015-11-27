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

GameView::~GameView()
{
    
}

inline const Vec2 getFruitPosition(int x, int y)
{
    return Vec2(y*Width+Width/2 , x*Height+Height/2);
}

bool GameView::init()
{
    auto bg = Sprite::create("assets/323.jpg");
    this->addChild(bg);
    auto size = Director::getInstance()->getWinSize();
    bg->setPosition(size.width/2, size.height/2);
    
    GetCommponent<GameModel*>("GameModel")->registerEvent(GameModel::EVENT_EXCHANGE, [=](const Msg &msg){
        for (int i=0; i<xCount; i++) {
            for (int j=0; j<yCount; j++) {
                auto fruit = GetCommponent<GameModel*>("GameModel")->getFuit(i, j);
                if (fruit) {
                    auto sp = fruit->getSprite();
                    sp->setPosition(getFruitPosition(i,j));
                }
            }
        }
    });
    for (int i=0; i<xCount; i++) {
        for (int j=0; j<yCount; j++) {
            auto fruit = GetCommponent<GameModel*>("GameModel")->getFuit(i, j);
            if (fruit) {
                auto sp = fruit->getSprite();
                this->addChild(sp);
                sp->setPosition(getFruitPosition(i,j));
            }
        }
    }
    return true;
}