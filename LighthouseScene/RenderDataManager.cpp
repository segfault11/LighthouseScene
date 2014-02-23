//------------------------------------------------------------------------------
//
//  RenderDataManager.cpp
//  LighthouseScene
//
//  Created by Arno in Wolde Luebke on 21.02.14.
//  Copyright (c) 2014 Arno in Wolde Luebke. All rights reserved.
//
//------------------------------------------------------------------------------
#include "RenderDataManager.h"
#include <CGK/Obj/Object.h>
//------------------------------------------------------------------------------
static bool initRenderData(ObjectRenderData* objectRenderData, CGKObjFile* objFile)
{
    // count # of faces
    size_t nFaces = 0;
    
    for (CGKObjObject& obj : objFile->Objects)
    {
        for (CGKObjGroup& grp : obj.Groups)
        {
            nFaces += grp.Faces.size();
        }
    }
    
    // allocated memory for positions
    CGKVector3f* positions = new CGKVector3f[nFaces*3];
    
    if (!positions)
    {
        return false;
    }
    
    size_t c = 0;
    
    for (CGKObjObject& obj : objFile->Objects)
    {
        for (CGKObjGroup& grp : obj.Groups)
        {
            for (CGKObjFace& face : grp.Faces)
            {
                CGKTuple3ui posIndices = face.PositionIndices;
                
                positions[c + 0] = objFile->Positions[posIndices[0]];
                positions[c + 1] = objFile->Positions[posIndices[1]];
                positions[c + 2] = objFile->Positions[posIndices[2]];
                
                c += 3;
            }
        }
    }

    objectRenderData->nVertices = static_cast<GLuint>(nFaces*3);
    
    // prepare gl buffer
    glGenBuffers(1, &objectRenderData->positions);
    glBindBuffer(GL_ARRAY_BUFFER, objectRenderData->positions);
    glBufferData(GL_ARRAY_BUFFER, sizeof(CGKVector3f)*nFaces*3, positions[0], GL_STATIC_DRAW);
    
    glGenVertexArrays(1, &objectRenderData->vao);
    glBindVertexArray(objectRenderData->vao);
    glBindBuffer(GL_ARRAY_BUFFER, objectRenderData->positions);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    
    delete[] positions;
    
    if (GL_NO_ERROR != glGetError())
    {
        return false;
    }
    
    return true;
}
//------------------------------------------------------------------------------
ObjectRenderDataManager& ObjectRenderDataManager::instance()
{
    static ObjectRenderDataManager instance;
    
    return  instance;
}
//------------------------------------------------------------------------------
ObjectRenderDataManager::ObjectRenderDataManager()
{
    this->objectManager = &ObjectManager::instance();
}
//------------------------------------------------------------------------------
ObjectRenderDataManager::~ObjectRenderDataManager()
{
    for (auto o : this->objectRenderData)
    {
        glDeleteBuffers(1, &o.second->positions);
        glDeleteVertexArrays(1, &o.second->vao);
        delete o.second;
    }
    
    this->objectRenderData.clear();
}
//------------------------------------------------------------------------------
const ObjectRenderData* ObjectRenderDataManager::getObjectRenderData(const Object& object) const
{
    //
    // if data is found return it
    //
    if (!(this->objectRenderData.find(object.id) == this->objectRenderData.end()))
    {
        return this->objectRenderData[object.id];
    }
    
    //
    // otherwise allocate it
    //
    const Object* o = this->objectManager->getObjectForID(object.id);
    
    // if we cant find the object return nullptr
    if (!o)
    {
        return nullptr;
    }
    
    CGKObjFile* objFile = CGKObjFileLoad(o->filename);
    
    // if we can't load the object file return nullptr
    if (!objFile)
    {
        return nullptr;
    }
    
    ObjectRenderData* ord = new ObjectRenderData();
    
    if (!ord)
    {
        return nullptr;
    }
    
    // if we fail to init the render data return null
    if (!initRenderData(ord, objFile))
    {
        delete ord;
        return nullptr;
    }
    
    this->objectRenderData[object.id] = ord;
    
    return ord;
}
//------------------------------------------------------------------------------