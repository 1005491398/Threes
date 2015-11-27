//
//  GameControl.hpp
//  Threes
//
//  Created by CT on 11/12/15.
//
//

#ifndef GameControl_hpp
#define GameControl_hpp

#include <stdio.h>
#include "Singleton.hpp"
#include "GameModel.hpp"
#include "GameView.h"

class  GameController {
    
private:
    shared_ptr<GameModel> _gameModel;
    GameView* _gameView;
    
protected:
    
    friend class Singleton<GameController>;
public:
    GameController();
    ~GameController();
    
    void gameStart();
};

#endif /* GameControl_hpp */
