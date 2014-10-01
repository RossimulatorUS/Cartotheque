//
//  HTTPRequest.cpp
//  Cartotheque
//
//  Created by Olivier Ross on 21/09/2014.
//  Copyright (c) 2014 Rossimulatorus. All rights reserved.
//

#include <iostream>
#include <vector>
#include "Node.h"

#include "client.h"
#include "lib/pugixml-1.4/src/pugixml.hpp"
#include <boost/network/protocol/http/client.hpp>
#include <boost/network/uri.hpp>

// From https://code.google.com/p/twitcurl/source/browse/trunk/libtwitcurl/urlencode.cpp?r=47
std::string char2hex( char dec )
{
    char dig1 = (dec&0xF0)>>4;
    char dig2 = (dec&0x0F);
    if ( 0<= dig1 && dig1<= 9) dig1+=48;    //0,48 in ascii
    if (10<= dig1 && dig1<=15) dig1+=65-10; //A,65 in ascii
    if ( 0<= dig2 && dig2<= 9) dig2+=48;
    if (10<= dig2 && dig2<=15) dig2+=65-10;

    std::string r;
    r.append( &dig1, 1);
    r.append( &dig2, 1);
    return r;
}

client::client(const char* site, const char* site_path) :
    count(0),
    site(site),
    site_path(site_path),
    strCout(),
    download_file()
{
    url_encode();
    //strCout.clear();
}

// http://scumways.com/happyhttp/happyhttp.html
void client::onBegin(const happyhttp::Response* r, void* userdata )
{
    ((client*)userdata)->download_file.open("download.xml"); //, std::ofstream::trunc);
    ((client*)userdata)->oldCout = std::cout.rdbuf();
    std::cout.rdbuf(((client*)userdata)->strCout.rdbuf());
}

// http://scumways.com/happyhttp/happyhttp.html
void client::onData( const happyhttp::Response* r, void* userdata, const unsigned char* data, int n )
{
    ((client*)userdata)->download_file << "test";
    std::cout << data;
    //((client*)userdata)->count += n;
}

// http://scumways.com/happyhttp/happyhttp.html
void client::onComplete( const happyhttp::Response* r, void* userdata )
{
    std::cout.rdbuf(((client*)userdata)->oldCout);
    ((client*)userdata)->download_file.close();
}

// http://scumways.com/happyhttp/happyhttp.html
void client::send_request()
{
    happyhttp::Connection conn( site, 80 );
    conn.setcallbacks( onBegin, onData, onComplete, this );
    conn.request("GET", site_path);

    while( conn.outstanding() )
        conn.pump();

    // strCout contains the result
}

void client::clean_response()
{
    std::string to_be_cleaned = strCout.str();
    std::string end_tag("</osm>");
    auto end = to_be_cleaned.find(end_tag);

    response = to_be_cleaned.substr(0, (end + end_tag.size() + 1));
}

// From https://code.google.com/p/twitcurl/source/browse/trunk/libtwitcurl/urlencode.cpp?r=47
void client::url_encode()
{
    std::string c(site_path);
    std::string escaped;
    unsigned long max = c.size();
    for(auto i(0); i < max; i++)
    {
        if ( (48 <= c[i] && c[i] <= 57) ||//0-9
             (65 <= c[i] && c[i] <= 90) ||//ABC...XYZ
             (97 <= c[i] && c[i] <= 122) || //abc...xyz
             (c[i]=='~' || c[i]=='-' || c[i]=='_' || c[i]=='.')
           )
        {
            escaped.append(&c[i], 1);
        }
        else
        {
            escaped.append("%");
            escaped.append(char2hex(c[i]));//converts char 255 to string "FF"
        }
    }
    request = escaped;
}

void client::execute()
{
    //url_encode();
    send_request();
    clean_response();
}

// http://pugixml.org
std::vector<way> client::parse_response()
{
    pugi::xml_document doc;
    std::vector<way> ways;

    auto res = doc.load(response.c_str());

    std::cout << response.substr(0, res.offset + 10);
    std::cout << res.offset;

    // If we have an error or the map is empty
    if (!res) return ways;

    // Parse the xml and store in data structure
    pugi::xml_node osm = doc.child("osm");

    for (pugi::xml_node tool: osm.children("node"))
    {
        std::cout << "Node:";

        for (pugi::xml_attribute attr: tool.attributes())
        {
            std::cout << " " << attr.name() << "=" << attr.value();
        }

        for (pugi::xml_node child: tool.children())
        {
            std::cout << ", child " << child.name();
        }
        
        std::cout << std::endl;
    }


    return ways;
}

void client::print()
{
    std::cout << response << std::endl << response.size() << std::endl;
}

void client::print_dirty()
{
    std::cout << strCout.str() << std::endl << strCout.str().size() << std::endl;
}