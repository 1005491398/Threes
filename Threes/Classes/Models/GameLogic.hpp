//
//  GameLogic.hpp
//  Threes
//
//  Created by CT on 11/25/15.
//
//

#ifndef GameLogic_hpp
#define GameLogic_hpp
#pragma once

#include <stdio.h>
#include <iostream>
#include "Commponent.hpp"
#include "Eliminate.hpp"

class GameLogic:public Commponent
{
public:
    static const string EVENT_DROP;
    
	GameLogic(void);
	~GameLogic();
    
    void setSelect(int x, int y);
    inline const cocos2d::Point getSelect() const { return cocos2d::Point(_selectX,_selectY);
    }
    void processEliminate(ThreesVec_ptr threeVec);
    void processDrop(ThreesVec_ptr threeVec);
protected:
	
private:
    int _selectX, _selectY;
};

#endif /* GameLogic_hpp */
