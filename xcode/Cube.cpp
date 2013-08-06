//
//  Cube.cpp
//  Brainbow
//
//  Created by Andrew Gormley on 2013-08-05.
//
//

#include "Cube.h"

Cube::Cube(){}

Cube::Cube(Vec3f loc, Vec3f colour){
    cubeMaterial.setSpecular( ColorA (colour.x, colour.y, colour.z, 1) );
	cubeMaterial.setDiffuse( ColorA (colour.x, colour.y, colour.z, 1));
	cubeMaterial.setAmbient(ColorA (colour.x, colour.y, colour.z, 1)) ;
	cubeMaterial.setShininess( 600.0f );
    cubeMaterial.setEmission(ColorA(1, 1, 1, 1 ));
    
    gl::lineWidth(20);
    
    tempCube = cinder::gl::DisplayList (GL_COMPILE);
    tempCube.newList();
    gl::drawStrokedCube(Vec3f(0,0,0), Vec3f (100, 100, 100));
    tempCube.endList();
    tempCube.setMaterial( cubeMaterial );
    
    location = loc;
}

void Cube::update (float rotateSpeed, Vec3f screenCol){
    
    tempCube.getModelMatrix().rotate( Vec3f(.2, 0, 0), rotateSpeed );
    
    cubeMaterial.setSpecular( Color(screenCol.x, screenCol.y, screenCol.z) );
	cubeMaterial.setDiffuse( Color(screenCol.x, screenCol.y, screenCol.z)  );
	cubeMaterial.setAmbient(Color(screenCol.x, screenCol.y, .05f)  );
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