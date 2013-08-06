//
//  SphereCloud.cpp
//  Brainbow
//
//  Created by Andrew Gormley on 2013-07-29.
//

#include "SphereCloud.h"

#include "cinder/gl/Material.h"
#include "cinder/Rand.h"
#include "cinder/gl/DisplayList.h"
#include "cinder/gl/gl.h"
#include "cinder/Utilities.h"
#include <math.h>

using namespace ci;
using namespace ci::app;
using namespace std;

SphereCloud::SphereCloud(){}

SphereCloud::SphereCloud(int number, int size){
    
    hexClear = true;
    range = 150;
    mNumber = number;
    mSize = size;
    
	ballMaterial.setSpecular( ColorA(1, 1-0.5f, 1, .3f ) );
	ballMaterial.setDiffuse( ColorA(1, 1-0.5f, 1, .3f ) );
	ballMaterial.setAmbient( ColorA(1, 1-0.5f, 1, .05f ) );
	ballMaterial.setShininess( 600.0f );
    ballMaterial.setEmission(ColorA(1, 1, 1, 1 ));
    
    for (int i = 0; i < mNumber ; i++){
        addSphere();
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
    
    //seed rotation vector
    Vec3f randVec = coords.nextVec3f();
    randVec.normalize();
    rotations.push_back(randVec);
    
    locations.push_back(Vec3f(x,y,z));
    cList.push_back(tempCloud);
    mNumber++;
    
    testLoc = Vec3f(x, y, z);
}

void SphereCloud::update(float x, float y, float z, float fade){
    int i = 0;
    double elSecs = getElapsedSeconds();
    hexClear = true;
    for( vector<cinder::gl::DisplayList>::iterator sphereDL = cList.begin(); sphereDL != cList.end(); ++sphereDL){
        //        bool minus = coords.nextBool();
        //
        Vec3f rotater = Vec3f(cos(elSecs*rotations[i].x), sin(elSecs*rotations[i].y), cos(elSecs*rotations[i].z))*.2;
        //            sphereDL->getModelMatrix().rotate(rotations[i], .005f);
        
        //        if (locations[i].x > x-range && locations[i].x < x+range)
        //                        range/ abs(x - locations[i].x);    
        
        sphereDL->getModelMatrix().translate (rotater);        
        
        //HANDREPEL
        int shiftBallx = locations[i].x+getWindowWidth()/2;
        int shiftBally = locations[i].y+getWindowHeight()/2;
        int shiftBallz = locations[i].z+400;
        Vec3f shiftedBall = Vec3f(shiftBallx, shiftBally, shiftBallz);
        Vec3f hand = Vec3f (x,y,z);
        
        if ((shiftBallx > x-range && shiftBallx < x+range)
        &&(shiftBally > y-range && shiftBally < y+range)
        &&(shiftBallz > z-range && shiftBallz < z+range)){
            count++;         
            sphereDL->getModelMatrix().translate(repel(shiftedBall, hand, i));
        }        
        locations[i] += rotater;
        if (shiftBallx > 600 && shiftBallx < 680
            && shiftBally > 360 && shiftBally < 440){
            hexClear = false;
        }
        if (fade != 0){
        ballMaterial.setSpecular( ColorA(1, 1-0.5f, 1, .3f - fade) );
        ballMaterial.setDiffuse( ColorA(1, 1-0.5f, 1, .3f - fade) );
        ballMaterial.setAmbient( ColorA(1, 1-0.5f, 1, .05f - fade ) );
        ballMaterial.setShininess( 600.0f );
        ballMaterial.setEmission(ColorA(1, 1, 1, 1 ));
            sphereDL->setMaterial(ballMaterial);
        }
        
        sphereDL->draw();
        i++;
    }
}

Vec3f SphereCloud::repel(Vec3f shiftedBall, Vec3f hand, int i){
    Vec3f translator;
    
    if (shiftedBall.x < hand.x && shiftedBall.x >= hand.x - range){
        translator.x = -((shiftedBall.x - (hand.x - range) ) / range)*.4;
//        cout << "left: "<< endl;
    }
    if (shiftedBall.x >= hand.x && shiftedBall.x <= hand.x + range){
        translator.x = ((hand.x + range - shiftedBall.x) / range)*.4;
//        cout << "right: "<< endl;
    }
    if (shiftedBall.y < hand.y && shiftedBall.y >= hand.y - range){
        translator.y = -((shiftedBall.y - (hand.y - range) ) / range)*.4;
//        cout << "up: "<< endl;
    }
    if (shiftedBall.y >= hand.y && shiftedBall.y <= hand.y + range){
        translator.y = ((hand.y + range - shiftedBall.y) / range)*.4;
//        cout << "down: "<< endl;
    }
    if (shiftedBall.z < hand.z && shiftedBall.z >= hand.z - range){
        translator.z = -((shiftedBall.z - (hand.z - range) ) / range);
//        cout << "away: "<< endl;
    }
    if (shiftedBall.z >= hand.z && shiftedBall.z <= hand.z + range){
        translator.z = ((hand.z + range - shiftedBall.z) / range);
//        cout << "toward: "<< endl;
    }
    locations[i] += translator;
    return translator;
}


int SphereCloud::getNumber(){
    return mNumber;
}
Vec3f SphereCloud::getLocation(){
    return locations[0];
}

void SphereCloud::draw(){
    //    for( vector<cinder::gl::DisplayList>::iterator sphereDL = cList.begin(); sphereDL != cList.end(); ++sphereDL){
    //       sphereDL->getModelMatrix().rotate(Vec3f(0,0,.5f), 0.01f);
    //    }
}

bool SphereCloud::getHexClear(){
    return hexClear;
}


//if (x within range of sphere){
//    repel(){
//        add amount to coordinate that is fraction of range depending on how far from range
//        distance += range * range-distance
// pos += range / (pos<->source)