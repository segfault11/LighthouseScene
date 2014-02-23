//
//  CameraManager.cpp
//  LighthouseScene
//
//  Created by Arno in Wolde Luebke on 21.02.14.
//  Copyright (c) 2014 Arno in Wolde Luebke. All rights reserved.
//

#include "CameraManager.h"
#include "json.h"
#include "Util.h"
#include <CGK/App/Application.h>

#define FILE_NAME "Cameras.json"

CameraManager& CameraManager::instance()
{
    static CameraManager instance;
    return instance;
}

CameraManager::CameraManager()
{
    Json::Value root;
    Json::Reader reader;
    std::string fileContents;
    
    if (!readFile(&fileContents, FILE_NAME))
    {
        DUMP_ERROR("Could not open file.");
        exit(0);
    }
    
    if (!reader.parse(fileContents, root))
    {
        DUMP_ERROR("Error Parsing file.");
        exit(0);
    }
    
    float h = CGKAppGetScreenHeight();
    float w = CGKAppGetScreenWidth();
    float asp = w/h;
    
    for (int i = 0; i < root.size(); i++)
    {
        CGKOpenGLCamera* cam = new CGKOpenGLCamera();
        
        if (!cam)
        {
            DUMP_ERROR("could not allocate [cam]");
            exit(0);
        }
        
        CGKVector3f eye;
        CGKVector3f focus;
        CGKVector3f up;
        
        eye[0] = root[i]["eye"][0].asFloat();
        eye[1] = root[i]["eye"][1].asFloat();
        eye[2] = root[i]["eye"][2].asFloat();

        focus[0] = root[i]["focus"][0].asFloat();
        focus[1] = root[i]["focus"][1].asFloat();
        focus[2] = root[i]["focus"][2].asFloat();

        up[0] = root[i]["up"][0].asFloat();
        up[1] = root[i]["up"][1].asFloat();
        up[2] = root[i]["up"][2].asFloat();
        
        float fovy = M_PI/180.0*root[i]["fovy"].asFloat();
        float near = root[i]["near"].asFloat();
        float far = root[i]["far"].asFloat();
        
        cam->SetView(eye, focus, up);
        cam->SetPerspective(fovy, asp, near, far);
        
        int id = root[i]["id"].asInt();
        
        this->cameras[id] = cam;
    }
    
    // set main camera
    if (this->cameras.size())
    {
        this->mainCamera = this->cameras.begin()->second;
    }
    else
    {
        this->mainCamera = new CGKOpenGLCamera();
    }
}

CameraManager::~CameraManager()
{
    for (auto o : this->cameras)
    {
        delete o.second;
    }
    
    this->cameras.clear();
}

