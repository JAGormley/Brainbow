//
//  Target.h
//  Brainbow
//
//  Created by Andrew Gormley on 2013-08-06.
//
//

#ifndef __Brainbow__Target__
#define __Brainbow__Target__

#include <iostream>

#include "cinder/ObjLoader.h"
#include "cinder/app/AppBasic.h"
#include "cinder/Arcball.h"
#include "cinder/MayaCamUI.h"
#include "cinder/Sphere.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/gl/Vbo.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Material.h"
#include "cinder/gl/DisplayList.h"

#endif /* defined(__Brainbow__Target__) */

using namespace ci;
using namespace ci::app;
using namespace std;

class Target{
public:
    Target();
    Target(Vec3f loc);
    void draw();
    void update (float rotateSpeed, Vec3f cursor, Vec3f screenCol);
    Vec3f getLocation();
    void charge(Vec3f screenCol);
    bool getBoxed();
    bool getFilled();
    void setFilled(bool isFilled);
    void addBox();
    int getBoxNumber();
    
    gl::Material targetMaterial;
    gl::Material centerMaterial;
    cinder::gl::DisplayList tempTarget;
    cinder::gl::DisplayList centerTarget;
    Vec3f location;
    Vec3f rotator;
    float fade;
    int boxNumber;
    bool newT;
    bool boxed;
    bool newBox;
    bool filled;
    
};
