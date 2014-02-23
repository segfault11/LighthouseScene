//
//  Object.h
//  LighthouseScene
//
//  Created by Arno in Wolde Luebke on 21.02.14.
//  Copyright (c) 2014 Arno in Wolde Luebke. All rights reserved.
//

#ifndef __LighthouseScene__Object__
#define __LighthouseScene__Object__

#include <iostream>
#include <string>
#include <CGK/Math/Vector3.h>

class Object
{
public:
    int id;
    std::string filename;
    CGKVector3f translation;
    CGKVector3f rotation;
    float scale;
};


#endif /* defined(__LighthouseScene__Object__) */
