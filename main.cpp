//
//  main.cpp
//  Cartotheque
//
//  Created by Olivier Ross on 17/09/2014.
//  Copyright (c) 2014 Rossimulatorus. All rights reserved.
//

// http://wiki.openstreetmap.org/wiki/Overpass_API/Language_Guide#Select_region_by_polygon

// Inspiration pour les requetes : http://overpass-api.de/api/convert?data=%3Cosm-script%3E%0D%0A++%3Cquery+type%3D%22node%22%3E%0D%0A++++%3Chas-kv+k%3D%22name%22+v%3D%22Gielgen%22%2F%3E%0D%0A++%3C%2Fquery%3E%0D%0A++%3Cprint%2F%3E%0D%0A%3C%2Fosm-script%3E&target=compact
// On veut quelque chose comme ca
//way
// (around:1000) // Facultatif
//["name"="Montreal"] // Facultatif
//(50.7,7.1,50.8,7.25);
//out;

#include "client.h"
#include <iostream>

int main(int argc, const char * argv[])
{
    //client request("api06.dev.openstreetmap.org", "/#map=10/44.1334/-70.8037");
    client request("overpass-api.de", "/api/interpreter?data=node%5B%22name%22%3D%22Seattle%22%5D%3Bout%3B");
    try {
        request.execute();
    } catch (int e) {
        std::cout << "Wrong site" << std::endl;
    }

    request.parse_response();
}
