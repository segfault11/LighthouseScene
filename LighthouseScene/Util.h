//
//  Util.h
//  LighthouseScene
//
//  Created by Arno in Wolde Luebke on 21.02.14.
//  Copyright (c) 2014 Arno in Wolde Luebke. All rights reserved.
//

#ifndef __LighthouseScene__Util__
#define __LighthouseScene__Util__

#include <iostream>
#include <fstream>
#include <streambuf>

#define DUMP_ERROR(msg) dumpFormattedError(__FILE__, __FUNCTION__, __LINE__, msg);

bool readFile(
    std::string* contents,
    const std::string& filename
);

void dumpFormattedError(
    std::string filename,
    std::string function,
    int line,
    std::string msg
);

#endif /* defined(__LighthouseScene__Util__) */
