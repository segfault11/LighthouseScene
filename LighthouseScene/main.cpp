//
//  main.cpp
//  LighthouseScene
//
//  Created by Arno in Wolde Luebke on 21.02.14.
//  Copyright (c) 2014 Arno in Wolde Luebke. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <CGK/App/Application.h>
#include "ObjectManager.h"
#include "MeshRenderer.h"


int main(int argc, const char * argv[])
{
    CGKAppCreate("test", 0, 0, 800, 600);
    MeshRenderer mr;
    CGKAppRegisterDrawable(mr);
    CGKAppRun();
    CGKAppDestroy();
    
    return 0;
}

