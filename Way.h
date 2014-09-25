//
//  Way.h
//  Cartotheque
//
//  Created by Olivier Ross on 24/09/2014.
//  Copyright (c) 2014 Rossimulatorus. All rights reserved.
//

#ifndef __Cartotheque__Way__
#define __Cartotheque__Way__

#include <vector>

#include "Node.h"

class way
{
public:
    way(std::vector<node>);

private:
    std::vector<node> path;

};

#endif /* defined(__Cartotheque__Way__) */
