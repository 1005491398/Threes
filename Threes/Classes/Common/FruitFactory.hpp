//
//  FruitFactory.hpp
//  Threes
//
//  Created by CT on 11/6/15.
//
//

#ifndef FruitFactory_hpp
#define FruitFactory_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "Fruit.hpp"

USING_NS_CC;

class FruitFactory {
    FruitFactory() {}
    
public:
    ~FruitFactory() {}
    
    static FruitFactory* getInstance() {
        static FruitFactory fruitFactory;
        return &fruitFactory;
    }
    
    Fruit_Ptr getFruitByType(FruitType type);
    
};

#endif /* FruitFacory_hpp */
