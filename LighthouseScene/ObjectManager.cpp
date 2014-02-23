//
//  ObjectManager.cpp
//  LighthouseScene
//
//  Created by Arno in Wolde Luebke on 21.02.14.
//  Copyright (c) 2014 Arno in Wolde Luebke. All rights reserved.
//

#include "ObjectManager.h"
#include "json.h"
#include "Util.h"

#define FILE_NAME "Objects.json"

ObjectManager& ObjectManager::instance()
{
    static ObjectManager instance;
    return instance;
}

ObjectManager::ObjectManager()
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
    
    for (int i = 0; i < root.size(); i++)
    {
        Object* o = new Object();
        
        if (!o)
        {
            DUMP_ERROR("MEM ERROR");
            exit(0);
        }
        
        o->id = root[i]["id"].asInt();
        o->filename = root[i]["filename"].asString();
        o->translation[0] = root[i]["translation"][0].asFloat();
        o->translation[1] = root[i]["translation"][1].asFloat();
        o->translation[2] = root[i]["translation"][2].asFloat();
        o->rotation[0] = M_PI/180.0*root[i]["rotation"][0].asFloat();
        o->rotation[1] = M_PI/180.0*root[i]["rotation"][1].asFloat();
        o->rotation[2] = M_PI/180.0*root[i]["rotation"][2].asFloat();
        o->scale = root[i]["scale"].asFloat();
        
        this->objects[o->id] = o;
    }
}

ObjectManager::~ObjectManager()
{
    for (auto o : this->objects)
    {
        delete o.second;
    }
    
    this->objects.clear();
}

const Object* ObjectManager::getObjectForID(int id) const
{
    if (this->objects.end() == this->objects.find(id))
    {
        return nullptr;
    }
    
    Object* o = this->objects[id];

    return o;
}




