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

class GameLogic:public Commponent
{
public:
	GameLogic(void);
	~GameLogic();
    
    void setSelect(int x, int y);
    inline const cocos2d::Point& getSelect() const { return cocos2d::Point(_selectX,_selectY); }
	/* data */
protected:
	
private:
    int _selectX, _selectY;
};

#endif /* GameLogic_hpp */
