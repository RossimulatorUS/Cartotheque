//
//  HTTPRequest.cpp
//  Cartotheque
//
//  Created by Olivier Ross on 21/09/2014.
//  Copyright (c) 2014 Rossimulatorus. All rights reserved.
//

#include "client.h"

client::client(const char* site, const char* site_path) :
    count(0),
    site(site),
    site_path(site_path)
{}

void client::onBegin(const happyhttp::Response* r, void* userdata )
{
    ((client*)userdata)->oldCout = std::cout.rdbuf();
    std::cout.rdbuf(((client*)userdata)->strCout.rdbuf());
}

void client::onData( const happyhttp::Response* r, void* userdata, const unsigned char* data, int n )
{
    //fwrite(data, 1, n, stdout);
    std::cout << data;
    ((client*)userdata)->count += n;
}

void client::onComplete( const happyhttp::Response* r, void* userdata )
{
    std::cout.rdbuf(((client*)userdata)->oldCout);
}

void client::send_request()
{
    happyhttp::Connection conn( site, 80 );
    conn.setcallbacks( onBegin, onData, onComplete, this );
    conn.request( "GET", site_path );

    while( conn.outstanding() )
        conn.pump();

    // strCout contains the result
}

void client::clean_response()
{
    std::string to_be_cleaned = strCout.str();
    std::string end_tag("</osm>");
    auto end = to_be_cleaned.find(end_tag);

    response = to_be_cleaned.substr(0, (end + end_tag.size()));
    std::cout << response << std::endl;
}

void client::print_dirty()
{
    std::cout << strCout.str() << std::endl << strCout.str().size() << std::endl;
}