//
//  GameModel.hpp
//  Threes
//
//  Created by CT on 11/12/15.
//
//

#ifndef GameModel_hpp
#define GameModel_hpp

#include <stdio.h>
#include "Fruit.hpp"
#include "Const.h"
#include "Commponent.hpp"
#include "GameLogic.hpp"

struct MoveDown: public Msg {
    Fruit_Ptr fruit;
};

// 关卡模型 保存 所有水果的状态
class GameModel:public Commponent {
public:
    const static std::string EVENT_EXCHANGE;
    const static std::string EVENT_ADD_FRUIT;
    const static std::string EVENT_MOVEDOWN;
private:
    Fruit_Ptr fruits[xCount][yCount];
    shared_ptr<GameLogic> _logic;
    
private:
    void initRandomFruits();
    
public:
    GameModel(const std::string &key);
    ~GameModel() {}
    
    void init();
    
    inline Fruit_Ptr getFuit(int x, int y) { return fruits[x][y]; }
    void exchange(int sx,int sy,int dx,int dy);
    void moveDown(int sx,int sy,int dx,int dy);
    void eliminateFruit(int x, int y);
    void addNewFruit(int x, int y, Fruit_Ptr fruit);
};

#endif /* GameModel_hpp */
