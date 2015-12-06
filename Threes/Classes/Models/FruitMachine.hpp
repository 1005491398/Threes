//
//  FruitMachine.hpp
//  Threes
//
//  Created by CT on 12/4/15.
//
//

#ifndef FruitMachine_hpp
#define FruitMachine_hpp

#include <stdio.h>
#include <iostream>
#include "Singleton.hpp"
#include "IFruiMachine.hpp"

class FruitMachine: public IFruitMachine
{
public:
	FruitMachine(void);
	~FruitMachine();

    virtual Fruit_Ptr createNewFruit();
protected:
    friend class Singleton<FruitMachine>;
    
private:
    
};

#endif /* FruitMachine_hpp */
