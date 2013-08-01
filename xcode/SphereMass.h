//
//  SphereMass.h
//  Brainbow
//
//  Created by Andrew Gormley on 2013-07-19.
//
//

#ifndef __Brainbow__SphereMass__
#define __Brainbow__SphereMass__
#include <iostream>
#include <vector>
#pragma once
#include "cinder/Channel.h"
#include "cinder/Vector.h"
#include "cinder/Color.h"
#endif /* defined(__Brainbow__SphereMass__) */



class SphereMass {
public:
	SphereMass();
//	void update( const ci::Vec3f &handLoc );
    void update();
	void draw();
	
	ci::Vec3f	massLoc;
    ci::Vec3f   handLoc;
};