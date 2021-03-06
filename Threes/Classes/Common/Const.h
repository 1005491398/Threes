//
//  Const.h
//  Threes
//
//  Created by CT on 11/6/15.
//
//

#ifndef Const_h
#define Const_h

enum class FruitType {
    Apple = 1,
    Orange,
    Pear,
    Grapes,
    Blueberry,
    Watermelon
};

const int Height = 80;
const int Width = 80;
const int xCount = 8;
const int yCount = 8;
const int NIL = -1;

extern void printMap(int Map[xCount][yCount]);

struct drop_point {
    int x, y;
    drop_point(int _x, int _y):x(_x),y(_y) {}
};

#endif /* Const_h */
