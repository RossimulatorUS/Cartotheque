//
//  Node.h
//  Cartotheque
//
//  Created by Olivier Ross on 24/09/2014.
//  Copyright (c) 2014 Rossimulatorus. All rights reserved.
//

#ifndef __Cartotheque__Node__
#define __Cartotheque__Node__

class node
{
public:
    node(double longitude, double lattitude) : x(longitude), y(lattitude){}
    double longitude(){return x;}
    double lattitude(){return y;}
    void longtiude(double longitude){x = longitude;}
    void lattitude(double lattitude){y = lattitude;}

private:
    double x;
    double y;
};

#endif /* defined(__Cartotheque__Node__) */
