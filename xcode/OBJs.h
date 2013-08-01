//
//  OBJs.h
//  Brainbow
//
//  Created by Andrew Gormley on 2013-07-31.
//
//

#ifndef __Brainbow__OBJs__
#define __Brainbow__OBJs__

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

#endif /* defined(__Brainbow__OBJs__) */

using namespace ci;
using namespace ci::app;
using namespace std;

class OBJs{
public:
    OBJs();
    OBJs(string objectRef, string textureRef);
    gl::VboMesh getVBO();
    
    
	TriMesh			mMesh;
	gl::VboMesh		mVBO;
	gl::GlslProg	mShader;
	gl::Texture		mTexture;
};