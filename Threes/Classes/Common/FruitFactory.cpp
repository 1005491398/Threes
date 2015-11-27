//
//  FruitFacory.cpp
//  Threes
//
//  Created by CT on 11/6/15.
//
//

#include "FruitFactory.hpp"

Fruit_Ptr FruitFactory::getFruitByType(FruitType type)
{
    return Fruit::create(type);
}