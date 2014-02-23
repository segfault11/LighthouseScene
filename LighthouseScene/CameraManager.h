//
//  CameraManager.h
//  LighthouseScene
//
//  Created by Arno in Wolde Luebke on 21.02.14.
//  Copyright (c) 2014 Arno in Wolde Luebke. All rights reserved.
//

#ifndef __LighthouseScene__CameraManager__
#define __LighthouseScene__CameraManager__

#include <iostream>
#include <CGK/OpenGL/Camera.h>
#include <map>

class CameraManager
{
public:
    static CameraManager& instance();

    CGKOpenGLCamera* getMainCamera() {return mainCamera;};
    
private:
    CameraManager();
    ~CameraManager();
    
    CGKOpenGLCamera* mainCamera;
    std::map<int, CGKOpenGLCamera*> cameras;
};

#endif /* defined(__LighthouseScene__CameraManager__) */
