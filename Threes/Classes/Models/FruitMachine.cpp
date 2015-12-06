//
//  FruitMachine.cpp
//  Threes
//
//  Created by CT on 12/4/15.
//
//

#include "FruitMachine.hpp"
#include "FruitFactory.hpp"

FruitMachine::FruitMachine()
{

}

FruitMachine::~FruitMachine()
{
	
}

Fruit_Ptr FruitMachine::createNewFruit()
{
    return FruitFactory::getInstance()->getFruitByType(FruitType::Apple);
}