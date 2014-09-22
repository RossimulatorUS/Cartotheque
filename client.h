//
//  HTTPRequest.h
//  Cartotheque
//
//  Created by Olivier Ross on 21/09/2014.
//  Copyright (c) 2014 Rossimulatorus. All rights reserved.
//

#ifndef __Cartotheque__client__
#define __Cartotheque__client__

#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "lib/happyhttp/happyhttp.h"

class client
{
public:
    client(const char*, const char*);

    // Before we start fetching
    static void onBegin(const happyhttp::Response* r, void* userdata );

    // Invoked to process response body data (may be called multiple times)
    static void onData( const happyhttp::Response* r, void* userdata, const unsigned char* data, int n );

    // Invoked when response is complete
    static void onComplete( const happyhttp::Response* r, void* userdata );

    void send_request();
    void clean_response();
    void print_dirty();
    

private:
    int count;
    const char* site;
    const char* site_path;
    std::string response;

    // Change the cout destination
    std::streambuf* oldCout;
    std::stringstream strCout;
};

#endif /* defined(__Cartotheque__client__) */