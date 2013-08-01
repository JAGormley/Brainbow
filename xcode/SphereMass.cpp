//
//  SphereMass.cpp
//  Brainbow
//
//  Created by Andrew Gormley on 2013-07-19.
//
//

#include "SphereMass.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;


SphereMass::SphereMass( )
{
	massLoc = Rand::randVec3f().normalized();
}

void SphereMass::update( )
{

}

void SphereMass::draw()
{
    gl::color(1, 1, 1);
//    gl::drawSolidRect(glRectf(0.5f, 0.5f, 0.5f, 0.5f));
}