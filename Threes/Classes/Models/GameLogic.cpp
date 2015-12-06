//
//  GameLogic.cpp
//  Threes
//
//  Created by CT on 11/25/15.
//
//

#include "GameLogic.hpp"
#include "CommponentManager.hpp"
#include "GameModel.hpp"
#include "Drop.hpp"
#include "FruitMachine.hpp"

const string GameLogic::EVENT_DROP = "EVENT_DROP";

GameLogic::GameLogic()
:Commponent("GameLogic")
,_selectX(NIL)
,_selectY(NIL)
{

}

GameLogic::~GameLogic()
{
	
}

void eliminateRange(int line, int start, int end, bool isy = false)
{
    for (int i=start; i<=end; i++) {
        isy?GetCommponent<GameModel*>("GameModel")->eliminateFruit(i, line):GetCommponent<GameModel*>("GameModel")->eliminateFruit(line, i);
    }
}

void GameLogic::processEliminate(ThreesVec_ptr threeVec)
{
    for (auto three:*threeVec) {
        switch (three->prrority) {
            case Priority::FIVE:
                CCLOG("FIVE");
            case Priority::FOUR:
                CCLOG("FOUR");
            case Priority::THREE:
                CCLOG("THREE");
            case Priority::CROSS:
                CCLOG("CROSS");
            default:
                if (three->xLine != NIL) {
                    eliminateRange(three->xLine, three->xstart, three->xend);
                }
                if (three->yLine != NIL) {
                    eliminateRange(three->yLine, three->ystart, three->yend, true);
                }
                break;
        }
    }
}

void GameLogic::processDrop(ThreesVec_ptr threeVec)
{
    auto dropPoints = Singleton<Drop>::getInstance().doDrop();
    for (auto points:*dropPoints) {
//        if (points->size() != 0) {
//            GetCommponent<GameModel*>("GameModel")->exchange(points->front()->x, points->front()->y, points->back()->x, points->back()->y);
//        }
        auto lastx = points->back()->x, lasty = points->back()->y;
        if ( lastx == 0 && GetCommponent<GameModel*>("GameModel")->getFuit(lastx, lasty) == nullptr) {
            auto fruit = Singleton<FruitMachine>::getInstance().createNewFruit();
            GetCommponent<GameModel*>("GameModel")->addNewFruit(lastx, lasty, fruit);
        }
        for (int i=points->size()/2-1; i>=0; i--) {
            int index = i*2;
            GetCommponent<GameModel*>("GameModel")->moveDown(points->at(index+1)->x, points->at(index+1)->y, points->at(index)->x, points->at(index)->y);
        }
        dispatchEvent(EVENT_DROP);
    }
}

void GameLogic::setSelect(int x, int y)
{
    if (_selectX!=NIL&&_selectY!=NIL&&(x!=_selectX||y!=_selectY)) {
        GetCommponent<GameModel*>("GameModel")->exchange(_selectX, _selectY, x, y);
        _selectX = NIL;
        _selectY = NIL;
        processEliminate(Singleton<Eliminate>::getInstance().doEliminate());
        processDrop(nullptr);
        return;
    }
    _selectX = x;
    _selectY = y;
}