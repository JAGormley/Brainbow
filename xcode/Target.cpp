//
//  Target.cpp
//  Brainbow
//
//  Created by Andrew Gormley on 2013-08-06.
//
//

#include "Target.h"
#include "AudioCont.h"

Target::Target(){}

Target::Target(Vec3f loc){
    
    newT = true;
    newBox = false;
    boxed = false;
    soundPlaying = false;
    fade = .6;
    boxNumber = 0;
    
    targetMaterial.setSpecular( ColorA (.9, .9, .9, .0) );
	targetMaterial.setDiffuse( ColorA (.9, .9, .9, .0));
	targetMaterial.setAmbient(ColorA (.3, .3, .3f, .0)) ;
	targetMaterial.setShininess( 600.0f )
    
    gl::lineWidth(600);
    
    tempTarget = cinder::gl::DisplayList (GL_COMPILE);
    tempTarget.newList();
    gl::drawStrokedCircle(Vec2f(0,0), 100);
    gl::drawStrokedCircle(Vec2f(0,0), 97);
    gl::drawStrokedCircle(Vec2f(0,0), 94);
    gl::drawStrokedCircle(Vec2f(0,0), 91);
    gl::drawStrokedCircle(Vec2f(0,0), 88);
    gl::drawStrokedCircle(Vec2f(0,0), 85);
    gl::drawStrokedCircle(Vec2f(0,0), 82);
    
    gl::drawStrokedCircle(Vec2f(0,0), 20);
    
    tempTarget.endList();
    tempTarget.setMaterial( targetMaterial );
    
    location = loc;
    rotator = Vec3f(sin (getElapsedSeconds()), cos(getElapsedSeconds()), 0);
}

void Target::update (float rotateSpeed, Vec3f cursor, Vec3f screenCol){
    
    // fade in
    if (newT && fade >= 0){
        targetMaterial.setSpecular( ColorA (.9, .9, .9, .6-fade) );
        targetMaterial.setDiffuse( ColorA (.9, .9, .9, .6-fade));
        targetMaterial.setAmbient(ColorA (.3, .3, .3f, .05f-(fade/12))) ;
        targetMaterial.setShininess( 600.0f );
        tempTarget.setMaterial( targetMaterial );
        fade -= .01;
        if (fade <= 0)
            newT = false;
    }
    
    // light up inner cirle
    if (!boxed && cursor.z < location.z && cursor.y < location.y+50 && cursor.y > location.y-50
        && cursor.x < location.x+50 && cursor.x > location.x-50 &&!newT){
         soundPlaying = true;
        
        charge(screenCol);
        fade -= .005;  
            
        if (fade <= 0){
            boxed = true;
            newBox = true;
        }
    }
    // reset fade
    else if (!newT){
        fade = .6;
        soundPlaying = false;
    }
    
    //stop drawing inner circle
    if (boxed && newBox){
        tempTarget = cinder::gl::DisplayList (GL_COMPILE);
        tempTarget.newList();
        gl::drawStrokedCircle(Vec2f(0,0), 100);
        gl::drawStrokedCircle(Vec2f(0,0), 97);
        gl::drawStrokedCircle(Vec2f(0,0), 94);
        gl::drawStrokedCircle(Vec2f(0,0), 91);
        gl::drawStrokedCircle(Vec2f(0,0), 88);
        gl::drawStrokedCircle(Vec2f(0,0), 85);
        gl::drawStrokedCircle(Vec2f(0,0), 82);
        tempTarget.endList();
        tempTarget.setMaterial( targetMaterial );
        newBox = false;
    }   
    
    if (boxed)
    tempTarget.getModelMatrix().rotate( rotator, rotateSpeed );    

    tempTarget.draw();
}

void Target::charge(Vec3f screenCol){
   
    float chargeFade = fade * 1.3333;
    centerMaterial.setSpecular( ColorA(screenCol.x, screenCol.y, screenCol.z, .6-chargeFade) );
	centerMaterial.setDiffuse( ColorA(screenCol.x, screenCol.y, screenCol.z, .6-chargeFade)  );
	centerMaterial.setAmbient(ColorA(screenCol.x, screenCol.y, screenCol.z, .05f-(fade/12))  );
	centerMaterial.setShininess( 600.0f );
    centerMaterial.setEmission(ColorA(1, 1, 1, 1 ));
    
    centerTarget = cinder::gl::DisplayList (GL_COMPILE);
    centerTarget.newList();
    gl::drawSolidCircle(Vec2f(0,0), 18);
    centerTarget.endList();
    centerTarget.setMaterial(centerMaterial);
    centerTarget.draw();
}

bool Target::getBoxed(){
    return boxed;
}

Vec3f Target::getLocation(){
    return location;
}

bool Target::getFilled(){
    return filled;
}
void Target::setFilled(bool isFilled){
    filled = isFilled;
}

void Target::addBox(){
    boxNumber++;
}

int Target::getBoxNumber(){
    return boxNumber;
}

bool Target::getChargeSound(){
    return soundPlaying;
}