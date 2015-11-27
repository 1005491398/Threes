//
//  CommponentManager.cpp
//  TestCommponent
//
//  Created by CT on 11/24/15.
//  Copyright © 2015 CT. All rights reserved.
//

#include "CommponentManager.hpp"

CommponentManager::CommponentManager()
{

}

CommponentManager::~CommponentManager()
{
	
}

void CommponentManager::insert(const string &key, commponent_ptr comp)
{
    _commpoents.insert(make_pair(key, comp));
}

void CommponentManager::remove(const string &key)
{
    _commpoents.erase(key);
}

commponent_ptr CommponentManager::find(const string &key)
{
//    auto ptr = _commpoents.find(key)->second;
    return _commpoents.find(key)->second;
}