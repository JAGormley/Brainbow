//
//  SphereCloud.h
//  Brainbow
//
//  Created by Andrew Gormley on 2013-07-29.
//
//

#ifndef __Brainbow__sphereCloud__
#define __Brainbow__sphereCloud__

#include <iostream>
#include "cinder/gl/Material.h"
#include "cinder/Rand.h"
#include "cinder/gl/DisplayList.h"
#include "cinder/gl/gl.h"

#endif /* defined(__Brainbow__SphereCloud__) */

using namespace ci;
using namespace ci::app;
using namespace std;

class SphereCloud {
public:
    SphereCloud();
    SphereCloud(int number, int size);
    
    //VARS
    int mNumber;
    int mSize;
    int range;
    int count;
    cinder::gl::DisplayList cloud;
    vector<cinder::gl::DisplayList> cList;
    Rand coords;
    cinder::gl::DisplayList tempCloud;
    gl::Material ballMaterial;
    vector<Vec3f> rotations;
    vector<Vec3f> locations;
    Vec3f testLoc;
    bool hexClear;
    
    //FNS
    void draw();
    void update(float x, float y, float z, float fade);
    void addSphere();
    int getNumber();
    bool getHexClear();
    Vec3f getLocation();
    Vec3f repel(Vec3f shiftedBall, Vec3f hand, int i);

    
};