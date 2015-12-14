//
//  FruitMachine.cpp
//  Threes
//
//  Created by CT on 12/4/15.
//
//

#include "FruitMachine.hpp"
#include "FruitFactory.hpp"
#include "cocos2d.h"

FruitMachine::FruitMachine()
{

}

FruitMachine::~FruitMachine()
{
	
}

Fruit_Ptr FruitMachine::createNewFruit()
{
    return FruitFactory::getInstance()->getFruitByType(FruitType((int)(CCRANDOM_0_1()*10)%6 + 1));
}