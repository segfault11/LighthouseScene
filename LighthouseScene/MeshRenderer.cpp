//
//  MeshRenderer.cpp
//  LighthouseScene
//
//  Created by Arno in Wolde Luebke on 23.02.14.
//  Copyright (c) 2014 Arno in Wolde Luebke. All rights reserved.
//

#include "MeshRenderer.h"
#include <CGK/OpenGL/Program.h>
#include <CGK/Math/Matrix4.h>

MeshRenderer::MeshRenderer()
:
    cameraManager(CameraManager::instance()),
    renderDataManager(ObjectRenderDataManager::instance()),
    objectManager(ObjectManager::instance())
{
    this->program = glCreateProgram();
    CGKOpenGLProgramAttachShaderFromFile(this->program, GL_VERTEX_SHADER, "MRVS.glsl");
    CGKOpenGLProgramAttachShaderFromFile(this->program, GL_FRAGMENT_SHADER, "MRFS.glsl");
    glBindFragDataLocation(this->program, 0, "fragOut");
    glBindAttribLocation(this->program, 0, "position");
    CGKOpenGLProgramLink(this->program);
}

MeshRenderer::~MeshRenderer()
{

}

void MeshRenderer::Draw()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    CGKOpenGLCamera* cam = this->cameraManager.getMainCamera();

    const float* view = cam->GetViewMatrix();
    const float* projection = cam->GetPerspectiveMatrix();
    
    glUseProgram(this->program);
    
    for (int i = 0; i < 2; i++)
    {
        const Object* o = this->objectManager.getObjectForID(i);
        const ObjectRenderData* ord = this->renderDataManager.getObjectRenderData(*o);
        
        CGKMatrix4f translation;
        CGKMatrix4f rotationX;
        CGKMatrix4f rotationY;
        CGKMatrix4f rotationZ;
        CGKMatrix4f scale;
        
        translation.MakeTranslation(o->translation.GetX(), o->translation.GetY(), o->translation.GetZ());
        rotationX.MakeRotationY(o->rotation.GetX());
        rotationY.MakeRotationY(o->rotation.GetY());
        rotationZ.MakeRotationY(o->rotation.GetZ());
        scale.MakeScale(o->scale, o->scale, o->scale);

        CGKMatrix4f model = translation*rotationX*rotationY*rotationZ*scale;

        CGKOpenGLProgramUniformMatrix4f(this->program, "model", model.GetData(), GL_TRUE);
        CGKOpenGLProgramUniformMatrix4f(this->program, "view", view, GL_FALSE);
        CGKOpenGLProgramUniformMatrix4f(this->program, "projection", projection, GL_FALSE);
    
        glBindVertexArray(ord->vao);
        glDrawArrays(GL_TRIANGLES, 0, ord->nVertices);
    }
}