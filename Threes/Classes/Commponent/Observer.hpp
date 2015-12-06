//
//  Observer.hpp
//  TestCommponent
//
//  Created by CT on 11/25/15.
//  Copyright © 2015 CT. All rights reserved.
//

#ifndef Observer_hpp
#define Observer_hpp

#include <stdio.h>
#include <iostream>
#include <unordered_map>
using namespace std;

struct Msg {
    void *data;
};

typedef function<void(const Msg &msg)> eventFunc;

class IObserver
{
public:
	IObserver(void);
	virtual ~IObserver();
    
    virtual void registerEvent(const string &name, eventFunc event) = 0;
    virtual void removeEvent(const string &name) = 0;
    virtual void dispatchEvent(const string &name, const Msg& msg) = 0;
	/* data */
protected:
	unordered_map<string, eventFunc> _events;
private:
    
};

#endif /* Observer_hpp */
