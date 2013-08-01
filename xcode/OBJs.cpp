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



//mShader = gl::GlslProg( loadResource( RES_SHADER_VERT ), loadResource( RES_SHADER_FRAG ) );
//
//CameraPersp initialCam;
//initialCam.setPerspective( 45.0f, getWindowAspectRatio(), 0.1, 10000 );
//mMayaCam.setCurrentCam( initialCam );
//
//
//mShader.bind();
//mShader.uniform( "tex0", 0 );
