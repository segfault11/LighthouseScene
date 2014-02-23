//
//  ObjectManager.h
//  LighthouseScene
//
//  Created by Arno in Wolde Luebke on 21.02.14.
//  Copyright (c) 2014 Arno in Wolde Luebke. All rights reserved.
//

#ifndef __LighthouseScene__ObjectManager__
#define __LighthouseScene__ObjectManager__

#include <iostream>
#include <map>
#include "Object.h"

class ObjectManager
{
public:
    static ObjectManager& instance();

    const Object* getObjectForID(int id) const;
    int getCount() const;

private:
    ObjectManager();
    ~ObjectManager();

    mutable std::map<int, Object*> objects;
};

#endif /* defined(__LighthouseScene__ObjectManager__) */
