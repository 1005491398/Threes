//
//  GameControl.cpp
//  Threes
//
//  Created by CT on 11/12/15.
//
//

#include "GameControl.hpp"
#include "HelloWorldScene.h"
USING_NS_CC;

GameController::GameController()
:_gameModel(nullptr)
,_gameView(nullptr)
{
    
}

GameController::~GameController()
{
    
}

void GameController::gameStart()
{
    _gameModel = make_shared<GameModel>("GameModel");
    _gameView = GameView::create();
    
    auto scene = Scene::create();
    // add layer as a child to scene
    scene->addChild(_gameView);
    
    Director::getInstance()->runWithScene(scene);
}

