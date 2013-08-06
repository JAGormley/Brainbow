//
//  Cube.h
//  Brainbow
//
//  Created by Andrew Gormley on 2013-08-05.
//
//

#ifndef __Brainbow__Cube__
#define __Brainbow__Cube__

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

#endif /* defined(__Brainbow__OBJs__) */

using namespace ci;
using namespace ci::app;
using namespace std;

class Cube{
public:
    Cube();
    Cube(Vec3f loc, Vec3f colour);   
    void draw();
    void update (float rotateSpeed, Vec3f screenCol);
    Vec3f getLocation();
    
    gl::Material cubeMaterial;
    cinder::gl::DisplayList tempCube;
    Vec3f location;
    
};
