//
//  Util.cpp
//  LighthouseScene
//
//  Created by Arno in Wolde Luebke on 21.02.14.
//  Copyright (c) 2014 Arno in Wolde Luebke. All rights reserved.
//

#include "Util.h"

bool readFile(
    std::string* contents,
    const std::string& filename
)
{
    std::ifstream file(filename);
    
    if (!file.is_open())
    {
        return false;
    }
    
    *contents = std::string(
            (std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>()
        );
    
    return true;
}

void dumpFormattedError(
    std::string filename,
    std::string function,
    int line,
    std::string msg
)
{
    std::cout << "In [" << filename << "], function [" << function << "], line[" << line << "]" << std::endl;
    std::cout << "Error: " << msg << std::endl;
}