//
//  CommponentManager.hpp
//  TestCommponent
//
//  Created by CT on 11/24/15.
//  Copyright © 2015 CT. All rights reserved.
//

#ifndef CommponentManager_hpp
#define CommponentManager_hpp

#include <stdio.h>
#include <iostream>
#include <unordered_map>
#include "Commponent.hpp"
using namespace std;
typedef Commponent* commponent_ptr;

class CommponentManager
{
public:
    static CommponentManager* getInstance()
    {
        static CommponentManager instance;
        return &instance;
    }
    
    template<typename T>
    inline T getCommponent(const string &name) {return static_cast<T>(find(name));}
protected:
    friend class Commponent;
private:
    CommponentManager(void);
    ~CommponentManager();
    void insert(const string &key, commponent_ptr comp);
    void remove(const string &key);
    commponent_ptr find(const string &key);
    
    unordered_map<string, commponent_ptr> _commpoents;
};

template <typename T>
inline T GetCommponent(const string &name) {
    return CommponentManager::getInstance()->getCommponent<T>(name);
}

#endif /* CommponentManager_hpp */
