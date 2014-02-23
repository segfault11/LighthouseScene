//
//  MeshRenderer.h
//  LighthouseScene
//
//  Created by Arno in Wolde Luebke on 23.02.14.
//  Copyright (c) 2014 Arno in Wolde Luebke. All rights reserved.
//

#ifndef __LighthouseScene__MeshRenderer__
#define __LighthouseScene__MeshRenderer__

#include <iostream>
#include <CGK/App/IDrawable.h>
#include <GL/glew.h>
#include "RenderDataManager.h"
#include "ObjectManager.h"
#include "CameraManager.h"

class MeshRenderer : public CGKAppIDrawable
{
public:
    MeshRenderer();
    ~MeshRenderer();
    
    void Draw();
    
private:
    GLuint program;
    ObjectRenderDataManager& renderDataManager;
    ObjectManager& objectManager;
    CameraManager& cameraManager;
};

#endif /* defined(__LighthouseScene__MeshRenderer__) */
