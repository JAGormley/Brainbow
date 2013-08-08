//
//  Cube.cpp
//  Brainbow
//
//  Created by Andrew Gormley on 2013-08-05.
//
//

#include "Cube.h"

Cube::Cube(){}

Cube::Cube(Vec3f loc, Vec3f colour, string type){
    cubeMaterial.setSpecular( ColorA (colour.x, colour.y, colour.z, .3) );
	cubeMaterial.setDiffuse( ColorA (colour.x, colour.y, colour.z, .3));
	cubeMaterial.setAmbient(ColorA (colour.x, colour.y, .05f, .01f)) ;
	cubeMaterial.setShininess( 600.0f );
    cubeMaterial.setEmission(ColorA(1, 1, 1, 1 ));
    
    gl::lineWidth(15);
    
    tempCube = cinder::gl::DisplayList (GL_COMPILE);
    tempCube.newList();
    if (type == "stroked")
    gl::drawStrokedCube(Vec3f(0,0,0), Vec3f (80, 80, 80));
    if (type == "solid")
    gl::drawCube(Vec3f(0,0,0), Vec3f (80, 80, 80));
    tempCube.endList();
    tempCube.setMaterial( cubeMaterial );
    
    location = loc;
    rotator = Vec3f(sin(getElapsedSeconds()), cos (getElapsedSeconds()), tan(getElapsedFrames()));
}

void Cube::update (float rotateSpeed, Vec3f screenCol){
    
    tempCube.getModelMatrix().rotate( rotator, rotateSpeed );
    
    cubeMaterial.setSpecular( ColorA(screenCol.x, screenCol.y, screenCol.z, .6) );
	cubeMaterial.setDiffuse( ColorA(screenCol.x, screenCol.y, screenCol.z, .6)  );
	cubeMaterial.setAmbient(ColorA(screenCol.x, screenCol.y, screenCol.z, .01f)  );
	cubeMaterial.setShininess( 600.0f );
    cubeMaterial.setEmission(ColorA(1, 1, 1, 1 ));
    tempCube.setMaterial( cubeMaterial );
    tempCube.draw();
}

//void Cube::draw(){
//}

Vec3f Cube::getLocation(){
    return location;
}
Vec3f Cube::getRotator(){
    return rotator;
}
