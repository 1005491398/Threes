//
//  Singleton.hpp
//  Threes
//
//  Created by CT on 11/9/15.
//
//

#ifndef Singleton_hpp
#define Singleton_hpp

#include <stdio.h>

template <class T>
struct Singleton {
    
public:
    static T &getInstance()
    {
        static T instance;
        return instance;
    }
};

#endif /* Singleton_hpp */
