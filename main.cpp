//
//  main.cpp
//  Cartotheque
//
//  Created by Olivier Ross on 17/09/2014.
//  Copyright (c) 2014 Rossimulatorus. All rights reserved.
//

// http://scumways.com/happyhttp/happyhttp.html Pour la librairie http


// Utiliser http://pugixml.org/ pour le parsing

#include "client.h"

int main(int argc, const char * argv[])
{
    //client request("api06.dev.openstreetmap.org", "/#map=10/44.1334/-70.8037");
    client request("overpass-api.de", "/api/interpreter?data=node%5B%22name%22%3D%22Gielgen%22%5D%3Bout%3B");
    try {
        request.send_request(); // Devrait attraper erreurs
    } catch (int e) {
        std::cout << "Wrong site" << std::endl;
    }


    request.clean_response();
}
