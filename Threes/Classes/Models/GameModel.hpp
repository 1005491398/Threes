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

class GameModel:public Commponent {
public:
    const static std::string EVENT_EXCHANGE;
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
    void eliminateFruit(int x, int y);
};

#endif /* GameModel_hpp */
