//
//  OBJs.cpp
//  Brainbow
//
//  Created by Andrew Gormley on 2013-07-31.
//
//

#include "OBJs.h"

#include "cinder/ObjLoader.h"
#include "cinder/app/AppBasic.h"
#include "cinder/Arcball.h"
#include "cinder/MayaCamUI.h"
#include "cinder/Sphere.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/gl/Vbo.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"

using namespace ci;
using namespace ci::app;
using namespace std;

OBJs::OBJs(){}

OBJs::OBJs(string objectRef, string textureRef){
    ObjLoader loader( (DataSourceRef)loadResource( objectRef ) );
    loader.load( &mMesh );
    mVBO = gl::VboMesh( mMesh );   
}

gl::VboMesh OBJs::getVBO(){
    return mVBO;
}
