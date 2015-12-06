//
//  IFruiMachine.hpp
//  Threes
//
//  Created by 陈 玉涛 on 12/5/15.
//
//

#ifndef IFruiMachine_hpp
#define IFruiMachine_hpp

#include <stdio.h>
#include "Fruit.hpp"

class IFruitMachine {
    
    
public:
    IFruitMachine() {}
    virtual ~IFruitMachine() {}
    
    virtual Fruit_Ptr createNewFruit() = 0;
};

#endif /* IFruiMachine_hpp */
