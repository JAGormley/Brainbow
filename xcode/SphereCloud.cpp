//
//  SphereCloud.cpp
//  Brainbow
//
//  Created by Andrew Gormley on 2013-07-29.
//
//

#include "SphereCloud.h"

#include "cinder/gl/Material.h"
#include "cinder/Rand.h"
#include "cinder/gl/DisplayList.h"
#include "cinder/gl/gl.h"
#include "cinder/Utilities.h"

using namespace ci;
using namespace ci::app;
using namespace std;

SphereCloud::SphereCloud(){}

SphereCloud::SphereCloud(int number, int size){
    mNumber = number;
    mSize = size;
    
	ballMaterial.setSpecular( ColorA(1, 1-0.5f, 1, .3f ) );
	ballMaterial.setDiffuse( ColorA(1, 1-0.5f, 1, .3f ) );
	ballMaterial.setAmbient( ColorA(1, 1-0.5f, 1, .05f ) );
	ballMaterial.setShininess( 600.0f );
    ballMaterial.setEmission(ColorA(1, 1, 1, 1 ));
    
    for (int i = 0; i < mNumber ; i++){
        int x = coords.nextInt(-mSize, mSize);
        int y = coords.nextInt(-mSize, mSize);
        int z = coords.nextInt(-mSize, mSize);
        tempCloud = cinder::gl::DisplayList (GL_COMPILE);
        tempCloud.newList();
        gl::drawSphere(Vec3f(x, y, z), 10);
        tempCloud.endList();
        tempCloud.setMaterial( ballMaterial );
        
        rotations[i] = coords.nextVec3f();
        cList.push_back(tempCloud);
    }
}

// to keep track of sphere, use rotation vec3f 

void SphereCloud::addSphere(){
    int x = coords.nextInt(-mSize, mSize);
    int y = coords.nextInt(-mSize, mSize);
    int z = coords.nextInt(-mSize, mSize);
    tempCloud = cinder::gl::DisplayList (GL_COMPILE);
    tempCloud.newList();
    gl::drawSphere(Vec3f(x, y, z), 10);
    tempCloud.endList();    
    tempCloud.setMaterial( ballMaterial );
    
    rotations.push_back(coords.nextVec3f());
    cList.push_back(tempCloud);
    mNumber++;
}

void SphereCloud::update(){
    int i = 0;
    for( vector<cinder::gl::DisplayList>::iterator sphereDL = cList.begin(); sphereDL != cList.end(); ++sphereDL){
//        bool minus = coords.nextBool();
//        float one = coords.nextFloat()/70;
//        float two = coords.nextFloat();
//        float three = coords.nextFloat();
            sphereDL->getModelMatrix().rotate(rotations[i], .005f);
        
          // how is rotating the model matrix affecting the draw location of the sphere

//        cout << "m00: " << sphereDL->getModelMatrix().m00<< endl;
//        cout << "m01: " << sphereDL->getModelMatrix().m01<< endl;
//        cout << "m10: " << sphereDL->getModelMatrix().m10<< endl;
//        cout << "m11: " << sphereDL->getModelMatrix().m11<< endl;
            sphereDL->draw();
        i++;
    }
}

int SphereCloud::getNumber(){
    return mNumber;
}


void SphereCloud::draw(){
    //    for( vector<cinder::gl::DisplayList>::iterator sphereDL = cList.begin(); sphereDL != cList.end(); ++sphereDL){
    //       sphereDL->getModelMatrix().rotate(Vec3f(0,0,.5f), 0.01f);
    //    }
}