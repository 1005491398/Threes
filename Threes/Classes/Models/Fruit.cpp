//
//  Fruit.cpp
//  Threes
//
//  Created by CT on 11/6/15.
//
//

#include "Fruit.hpp"
#include "CommponentManager.hpp"
#include "GameLogic.hpp"

Fruit::Fruit(FruitType type):
_x(0),
_y(0),
_sprite(nullptr),
_type(type)
{
    
}

Fruit::~Fruit()
{
    CCLOG("Fruit is destoryed!!");
//    CC_SAFE_DELETE(_sprite);
}

std::shared_ptr<Fruit> Fruit::create(FruitType type)
{
    auto fruit = std::make_shared<Fruit>(type);
    if (fruit->init()) {
        return fruit;
    }
    return nullptr;
}

bool Fruit::init()
{
    _sprite = ImageView::create(StringUtils::format("fruit_type_%d.png", (int)_type), Widget::TextureResType::PLIST);
    auto label = Label::create();
    label->setString(StringUtils::format("%d", (int)_type));
    label->setSystemFontSize(24);
    label->setPosition(Point(Width/2, Height/2));
    
    _sprite->addChild(label);
    _sprite->setTouchEnabled(true);
    _sprite->addTouchEventListener([this](Ref* sender,Widget::TouchEventType type){
        if (type == Widget::TouchEventType::ENDED) {
            CCLOG("Touch me %d-%d", _x, _y);
            GetCommponent<GameLogic*>("GameLogic")->setSelect(_x, _y);
        }
    });
    return true;
}

ImageView* Fruit::getSprite()
{
    return _sprite;
}

void Fruit::remove()
{
    _sprite->removeFromParent();
}