//
//  RenderDataManager.h
//  LighthouseScene
//
//  Created by Arno in Wolde Luebke on 21.02.14.
//  Copyright (c) 2014 Arno in Wolde Luebke. All rights reserved.
//

#ifndef __LighthouseScene__RenderDataManager__
#define __LighthouseScene__RenderDataManager__

#include <iostream>
#include "ObjectRenderData.h"
#include "Object.h"
#include "ObjectManager.h"
#include <map>

class ObjectRenderDataManager
{
public:
    static ObjectRenderDataManager& instance();
    
    // class access
    const ObjectRenderData* getObjectRenderData(const Object& object) const;
    int getCount() const;
    
private:
    ObjectRenderDataManager();
    ~ObjectRenderDataManager();
    
    mutable std::map<int, ObjectRenderData*> objectRenderData;
    ObjectManager* objectManager;
};


#endif /* defined(__LighthouseScene__RenderDataManager__) */
