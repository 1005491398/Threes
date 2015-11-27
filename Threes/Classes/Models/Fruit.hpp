//
//  Fruit.hpp
//  Threes
//
//  Created by CT on 11/6/15.
//
//

#ifndef Fruit_hpp
#define Fruit_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "CocosGUI.h"
#include "Const.h"

USING_NS_CC;
using namespace cocos2d::ui;

class Fruit {

private:
    ImageView* _sprite;
    int _x,_y;
    FruitType _type;
    
    bool init();
public:
//    Fruit();
    Fruit(FruitType type);
    ~Fruit();
    
    static std::shared_ptr<Fruit> create(FruitType type);
    ImageView* getSprite();
    
    void setXY(int x, int y)
    {
        _x = x;
        _y = y;
    }
    
    inline int px() {return _x;}
    inline int py() {return _y;}
    inline int ftype() {return static_cast<int>(_type);}
    void remove();
};
using Fruit_Ptr = std::shared_ptr<Fruit>;

#endif /* Fruit_hpp */
