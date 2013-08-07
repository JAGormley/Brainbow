#include "Resources.h"
#include "SphereCloud.h"
#include "AudioCont.h"
#include "OBJs.h"
#include "Cube.h"
#include "Target.h"


#include "cinder/app/AppNative.h"
//#include "cinder/Camera.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/DisplayList.h"

#include "cinder/Rand.h"
#include "cinder/Timer.h"
#include "Cinder-LeapSdk.h"
#include <cmath>
#include "cinder/gl/Material.h"
#include "cinder/gl/Light.h"

#include "cinder/Utilities.h"
#include "cinder/gl/Fbo.h"
#include "cinder/gl/GlslProg.h"

#include "cinder/ImageIo.h"
#include "cinder/ip/Hdr.h"
#include "cinder/Color.h"

#include "cinder/audio/Output.h"
#include "cinder/audio/Io.h"

using namespace ci;
using namespace ci::app;
using namespace std;

static const Color BLUE( 0.25f, 0.25f, 1.0f );
static const Color RED( 1.0f, 0.25f, 0.25f );
static const int SHADOW_MAP_RESOLUTION = 1024;

class BrainbowApp : public ci::app::AppNative
{
public:
	void 					draw();
	void 					setup();
	void 					shutdown();
	void 					update();
    void keyDown( KeyEvent event );
    void initShadowMap();
	void updateShadowMap();
    void addCube(float x, float y, float z);
    void addTarget (Vec3f loc);
    void scene1();
    void scene2();
    
    gl::GlslProg		mShader;
    
    cinder::gl::DisplayList         mSphere, mDisc, mCur, mCyl;
    ci::Timer timer;
    ci::Timer ballTimer;
    gl::Light			*mLight;
    CameraPersp			*mCamera;
    gl::Fbo				mDepthFbo;
    gl::Texture         myImage;
    vector<Cube> cubes;
    Cube tempCube;
    vector<Target> targets;
    Target tempTarget;
    
    
private:
    
    void prepareSettings( Settings *settings );
    
    //MISCVARS
    bool musicOn = false;
    bool gong = false;
    bool shift2 = false;
    bool drawDiamond = true;
    bool newLight = false;
    bool newCloud = false;
    bool targetFilled = false;
    bool sceneOne;
    bool sceneTwo;
    float lightFade = 0;
    float discOp = 0;
    float diamondFade;
    Vec3f screenCol;
    
    int zshift = 0;
    gl::Material discMaterial;
    gl::Material sphereMaterial;
    
    //LEAP
	uint32_t				mCallbackId;
	LeapSdk::HandMap		mHands;
	LeapSdk::DeviceRef		mLeap;
	void 					onFrame( LeapSdk::Frame frame );
    //LEAP PARAMS
    Vec3f lightPos;
    Vec3f lightPos2;
    Vec3f handPos;
    
    float scaledX;
    float scaledY;
    float scaledZ;
    float colorSat;
    
    //OBJECTS
    
    SphereCloud mCloud;
    Cube mCube;
    OBJs sphere;
    
    //AUDIO
    //    AudioCont mAudio;
    
    float volume1;
    ci::Timer gongTimer;
    ci::Timer cubeTimer;
    
    
};

void BrainbowApp::prepareSettings( Settings *settings )
{
	settings->setWindowSize( 1280, 800 );
	settings->setFrameRate( 60.0f );
}

void BrainbowApp::setup()
{
    //    mAudio = AudioCont();
    //    mAudio.setUp();
    
    // start scene1
    sceneOne = true;
    sceneTwo = false;
    
    // Set up OpenGL
    
	gl::enableAlphaBlending();
	gl::enableDepthRead();
	gl::enableDepthWrite();
    
    gongTimer.start();
    ballTimer.start();
    
    // LIGHTING
    //here
    glPolygonOffset( 1.0f, 1.0f );
	glEnable( GL_LIGHTING );
	glEnable( GL_DEPTH_TEST );
    
    
    mLight = new gl::Light( gl::Light::POINT, 0 );
	mLight->lookAt( Vec3f( 1, 5, 1 ), Vec3f (getWindowWidth(), getWindowHeight() * 0.5f, 0.0f ));
    mLight->setAmbient( Color( 0.3f, 0.3f, 0.3f ) );
	mLight->setDiffuse( Color( 1.0f, 1.0f, 1.0f ) );
	mLight->setSpecular( Color( 1.0f, 1.0f, 1.0f ) );
	mLight->setShadowParams( 60.0f, 0.5f, 8.0f );
    //	mLight->update( *mCamera );
	mLight->enable();
    
    
    //LOAD SHAPES
    colorSat = 1.0f;
    
	sphereMaterial.setSpecular( ColorA(colorSat-0.3f, colorSat, colorSat, .4f ) );
	sphereMaterial.setDiffuse( ColorA(colorSat-0.3f, colorSat, colorSat, .4f ) );
	sphereMaterial.setAmbient( ColorA(colorSat-0.3f, colorSat, colorSat, .05f ) );
	sphereMaterial.setShininess( 1.0f );
    
    sphereMaterial.setEmission(ColorA(1, 1, 1, 1 ));
    gl::Material cylMaterial;
    cylMaterial.setSpecular( ColorA(0, 1.0f, 1.0f, .2f ));
	cylMaterial.setDiffuse( ColorA(0, 1.0f, 1.0f, .2f ) );
	cylMaterial.setAmbient( ColorA(0, 1.0f, 1.0f, .2f ) );
	cylMaterial.setShininess( 600.0f );
    cylMaterial.setEmission(ColorA(1, 1, 1, 1 ));
    
    gl::Material curMaterial;
    curMaterial.setSpecular( ColorA(1, .5, 0, .5f ));
	curMaterial.setDiffuse( ColorA(1, .5, 0, .5f ) );
	curMaterial.setAmbient( ColorA(1, 1.0f, 1.0f, .05f ) );
	curMaterial.setShininess( 600.0f );
    curMaterial.setEmission(ColorA(1, 1, 1, 1 ));
    
    
	discMaterial.setSpecular( ColorA(colorSat-0.3f, colorSat, colorSat, .4f ) );
	discMaterial.setDiffuse( ColorA(colorSat-0.3f, colorSat, colorSat, .4f ) );
	discMaterial.setAmbient( ColorA(colorSat-0.3f, colorSat, colorSat, .05f ) );
	discMaterial.setShininess( 600.0f );
    discMaterial.setEmission(ColorA(1, 1, 1, 1 ));
    
    initShadowMap();
    
    mCloud = SphereCloud(0, 70);
    mCloud.addSphere();
    
    mSphere = gl::DisplayList( GL_COMPILE );
    mSphere.newList();
    gl::drawSphere(Vec3f(0, 0, 0), 300, 4);
    mSphere.endList();
    mSphere.setMaterial( sphereMaterial );
    
    mCyl = gl::DisplayList( GL_COMPILE );
    mCyl.newList();
    //    gl::drawCylinder(200, 200, 200);
    gl::drawColorCube(Vec3f(0, 0, 0), Vec3f(300, 300, 300));
    mCyl.endList();
    mCyl.setMaterial(cylMaterial);
    
    mCur = gl::DisplayList( GL_COMPILE );
    mCur.newList();
    gl::drawSphere(Vec3f(0, 0, 0), 5);
    mCur.endList();
    mCur.setMaterial(curMaterial);
    
    mDisc = gl::DisplayList( GL_COMPILE );
    mDisc.newList();
    //    mCloud.draw();
    gl::drawSolidCircle(Vec2f(0, 0), 60, 6);
    mDisc.endList();
    mDisc.setMaterial( discMaterial );
    
	// Set up camera
    //	mCamera = CameraPersp( getWindowWidth(), getWindowHeight(), 60.0f, 0.01f, 1000.0f );
    //	mCamera.lookAt( Vec3f( 0.0f, 125.0f, 500.0f ), Vec3f( 0.0f, 250.0f, 0.0f ) );
	
	// START LEAP
	mLeap 		= LeapSdk::Device::create();
	mCallbackId = mLeap->addCallback( &BrainbowApp::onFrame, this );
    
    
    mShader = gl::GlslProg( loadResource( RES_SHADOWMAP_VERT ), loadResource( RES_SHADOWMAP_FRAG ) );
	mShader.bind();
	mShader.uniform( "depthTexture", 0 );
    
    //    sphere = OBJs("sphere.obj", "purpleflower.png");
    //    myImage = gl::Texture( loadImage( loadResource( "purpleflower.png" ) ) );
    
}

void BrainbowApp::draw()
{
	gl::setViewport( getWindowBounds() );
    
    // SCREENPULSE
    // changes every 12.5 seconds
    float gray = (cos(getElapsedSeconds()/4)*.3)/2 ;
    float otherCol = (sin(getElapsedSeconds()/4)*.2)/2;
    
    screenCol = Vec3f (lightFade+gray, lightFade, (lightFade*2)-otherCol);
    
    if (sceneOne)
        gl::clear( Color(lightFade+gray, lightFade, (lightFade*2)-otherCol) );
    if (sceneTwo)
        gl::clear( Color(1, 1, 1) );
    
    
    // FADE IN INTRO
    if (lightFade < .5){
        lightFade += .0005;
    }
    
    if (mHands.empty())
        mLight->disable();
    
    updateShadowMap();
    
    gl::enableDepthRead();
    gl::enableDepthWrite();
    mShader.bind();
    glEnable( GL_TEXTURE_2D );
	mDepthFbo.bindDepthTexture();
    mShader.bind();
    
    // SHAPES
    
    //cyl
    //    glPushMatrix();
    //    glTranslated( scaledX, scaledY, scaledZ-400 );
    //    mCyl.draw();
    //    glPopMatrix();
    
    
    // FIRST SCENE
    if (sceneOne){
        
        // disc
        glPushMatrix();
        glTranslated( 640, 400, zshift - 200);
        if (shift2 && discOp > 1)
            glScalef(discOp, discOp, 0);
        //    cout << discOp << endl;
        mDisc.draw();
        glPopMatrix();
        
        //cloud
        glPushMatrix();
        glTranslated( getWindowWidth() * 0.5f, getWindowHeight() * 0.5f, zshift );
        //    if (lightFade > .45f)
        mCloud.update(scaledX, scaledY, scaledZ, diamondFade);
        glPopMatrix();
        
        if (drawDiamond){
            glPushMatrix();
            glTranslated( getWindowWidth() * 0.5f, getWindowHeight() * 0.5f, zshift);
            mSphere.draw();
            glPopMatrix();
        }
    }
    
    // SECOND SCENE
    if (sceneTwo){
        
        mLight->lookAt( Vec3f(scaledX, scaledY, scaledZ +200), Vec3f (getWindowWidth()*.05, getWindowHeight() * 0.5f, 0.0f ));
        
        // cursor
        glPushMatrix();
        glTranslated( scaledX, scaledY, scaledZ );
        mCur.draw();
        
        if (scaledZ < 375 && scaledZ > 350)
            gl::drawSphere(Vec3f(0,0,0), (scaledZ-350)*.4);
        if (scaledZ >= 375)
            gl::drawSphere(Vec3f(0,0,0), 25*.4);
        glPopMatrix();
        
        
            // rotate whole scene; implement this
//        if (targetFilled){
//            glPushMatrix();
//            glRotatef(getElapsedSeconds()*10, Vec3f (640, 400, 350) );
//        }
            for (int i = 0; i < cubes.size() ; i++){
                glPushMatrix();
                glTranslatef(cubes[i].getLocation());
                cubes[i].update(.01f, screenCol);
                glPopMatrix();
            }
            
            for (int i = 0; i < targets.size() ; i++){
                glPushMatrix();
                glTranslatef(targets[i].getLocation());
                targets[i].update(.01f, handPos, screenCol);
                if (targets[i].getBoxed() && targets[i].getBoxNumber() < 15 ){
                    addCube(targets[i].getLocation().x, targets[i].getLocation().y, targets[i].getLocation().z);
                    targets[i].addBox();
                }                
                glPopMatrix();
            }
//        if (targetFilled)
//            glPopMatrix();
//        
        
        //cloud
        glPushMatrix();
        glTranslated( getWindowWidth() * 0.5f, getWindowHeight() * 0.5f, zshift );
        mCloud.update(0, 0, 0, 0);
        glPopMatrix();
    }
    
    mShader.unbind();
    mDepthFbo.unbindTexture();
    
    //    writeImage( getHomeDirectory() / ("image_" + toString( getElapsedFrames() ) + ".png"), copyWindowSurface() );
	
}

void BrainbowApp::onFrame( LeapSdk::Frame frame )
{
	mHands = frame.getHands();
}

void BrainbowApp::initShadowMap()
{
	mDepthFbo = gl::Fbo( SHADOW_MAP_RESOLUTION, SHADOW_MAP_RESOLUTION, false, false, true );
	mDepthFbo.bindDepthTexture();
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
}
//
void BrainbowApp::updateShadowMap()
{
	mDepthFbo.bindFramebuffer();
    
	glPolygonOffset( 1.0f, 1.0f );
	glEnable( GL_POLYGON_OFFSET_FILL );
	glClear( GL_DEPTH_BUFFER_BIT );
    
	glPushAttrib( GL_VIEWPORT_BIT );
	glViewport( 0, 0, SHADOW_MAP_RESOLUTION, SHADOW_MAP_RESOLUTION );
    
	gl::pushMatrices();
	
    mLight->setShadowRenderMatrices();
    
    mDisc.draw();
    //    mCyl.draw();
    //    mCur.draw();
    mSphere.draw();
    
	gl::popMatrices();
    
	glPopAttrib();
    
	glDisable( GL_POLYGON_OFFSET_FILL );
    
	mDepthFbo.unbindFramebuffer();
}
//
void BrainbowApp::keyDown( ci::app::KeyEvent event )
{
    //	if( event.getChar() == 'l') {
    //		mLight->disable();
    //    }
}

void BrainbowApp::shutdown()
{
	mLeap->removeCallback( mCallbackId );
	mHands.clear();
}

void BrainbowApp::update()
{
    //LEAP
    if ( mLeap && mLeap->isConnected() ) {
		mLeap->update();
	}
    //GET HAND
    for ( LeapSdk::HandMap::const_iterator handIter = mHands.begin(); handIter != mHands.end(); ++handIter ) {
		const LeapSdk::Hand& hand = handIter->second;
        //        cout << hand.getPosition().x << endl;
        //        cout << hand.getDirection();
        
        scaledX = (hand.getPosition().x *(getWindowWidth()/400))+(getWindowWidth()/2);
        scaledY = (-hand.getPosition().y*(getWindowHeight()/400) + getWindowHeight())*2.5 - 400;
        scaledZ = hand.getPosition().z*2+300;
        handPos = Vec3f(scaledX, scaledY, scaledZ);
    }
    
    //AUDIO
    //    mAudio.update();
    
    
    //SCENES
    if (sceneOne)
        scene1();
    if (sceneTwo)
        scene2();
    
    
    //LIGHT
    
    mLight->lookAt( handPos, Vec3f::zero() );
    
    //MOVE SHAPES
    //    mCyl.getModelMatrix().rotate( Vec3f( .02, .04, 0), 0.01f );
    if (gong)
        mSphere.getModelMatrix().rotate( Vec3f( 0.0f, 0.5f, 0), 0.01f );
    //    mBall.getModelMatrix().rotate(Vec3f(0, -abs(sinSecs), 0), .01f);
    //    mCur.getModelMatrix().rotate(Vec3f(0.0f, 0.5f, 0), .03f);
    
}

void BrainbowApp::scene1(){
    
    if (!musicOn && getElapsedSeconds() > 2){
        //        mAudio.playTraz("lowdrone");
        musicOn = true;    }
    
    //    //addspheres
    if (lightFade >= 0.45f && ballTimer.getSeconds() > 0.2f && mCloud.getNumber() < 20){
        mCloud.addSphere();
        ballTimer = 0;
        ballTimer.start();
    }
    else if (lightFade >= 0.45f && ballTimer.getSeconds() > 1.0f && mCloud.getNumber() < 600 && !gong){
        mCloud.addSphere();
        ballTimer = 0;
        ballTimer.start();
    }
    //
    //into diamond
    if (gongTimer.getSeconds()>1 && scaledZ < 290 && scaledZ > 100 && !gong && getElapsedSeconds() > 0){
        //        mAudio.playTraz("activate");
        mCloud.addSphere();
        gong = true;
        //        mAudio.playTraz("middrone");
        gongTimer.stop();
        gongTimer.start();
    }
    
    if (gong && zshift < 500 ){
        //        zshift = 1;
        zshift++;
        scaledZ += zshift;
    }
    if (mCloud.getNumber() < 200 && ballTimer.getSeconds() > 0.1f && gong && zshift > 0){
        mCloud.addSphere();
        ballTimer = 0;
        ballTimer.start();
    }
    
    //    cout << "x: " << scaledX << endl;
    //    cout << "y: " << scaledY << endl;
    //    cout << "z: " << scaledZ << endl;
    if ((mCloud.getHexClear() || shift2) && getElapsedSeconds() > 10 && zshift < 750){
        //        if (getElapsedSeconds() > 10 && zshift < 720){
        shift2 = true;
        zshift++;
        scaledZ += zshift;
        discMaterial.setSpecular( ColorA(colorSat, colorSat, colorSat, .4f + discOp ) );
        discMaterial.setDiffuse( ColorA(colorSat, colorSat, colorSat, .4f + discOp) );
        discMaterial.setAmbient( ColorA(colorSat, colorSat, colorSat, .05f ) );
        discMaterial.setShininess( 600.0f );
        discMaterial.setEmission(ColorA(1, 1, 1, 1 ));
        mDisc.setMaterial( discMaterial );
        
        discOp += .01;
        if (zshift > 650){
            
            diamondFade += .005;
            sphereMaterial.setSpecular( ColorA(colorSat-0.3f, colorSat, colorSat, .4f-diamondFade ) );
            sphereMaterial.setDiffuse( ColorA(colorSat-0.3f, colorSat, colorSat, .4f-diamondFade ) );
            sphereMaterial.setAmbient( ColorA(colorSat-0.3f, colorSat, colorSat, .05f-diamondFade ) );
            mSphere.setMaterial( sphereMaterial );
            //                drawDiamond = false;
        }
    }
    if (zshift >= 750 && scaledZ > 700 && scaledY < 450 && scaledY > 320 && scaledX <685 && scaledX > 590){
        sceneOne = false;
        sceneTwo = true;
        
        zshift = 0;
    }
}

void BrainbowApp::scene2(){
    //    cout << "x: " << scaledX << endl;
    //    cout << "y: " << scaledY << endl;
    //    cout << "z: " << scaledZ << endl;
    
    if (!newLight){
        mCloud.clear();
        mLight->setAmbient( Color( 0.0f, 0.0f, 0.0f ) );
        mLight->setDiffuse( Color( 1.0f, 1.0f, 1.0f ) );
        mLight->setSpecular( Color( 1.0f, 1.0f, 1.0f ) );
        mLight->setShadowParams( 60.0f, 0.5f, 8.0f );
        newLight = true;
        cubeTimer.start();
    }
    
    //    if (cubeTimer.getSeconds() > .05 && scaledZ < 350 ){
    //        addCube(scaledX, scaledY, scaledZ-200);
    //        cubeTimer = 0;
    //        cubeTimer.start();
    //    }
    
    if (scaledZ < 350 && targets.size() < 5 && cubeTimer.getSeconds() > 2){
        addTarget(Vec3f (scaledX, scaledY, scaledZ));
        cubeTimer = 0;
        cubeTimer.start();
    }
    
    if (cubes.size() >= 45){
        if ( !newCloud){
            mCloud = SphereCloud(0, 500);
            newCloud = true;
        }
        if (newCloud && mCloud.getNumber() < 300 && gongTimer.getSeconds() > .5){
            gongTimer = 0;
            gongTimer.start();
            mCloud.addSphere();
        }
    }
    
}

void BrainbowApp::addCube(float x, float y, float z){
    tempCube = Cube(Vec3f(x, y, z), screenCol, "solid");
    cubes.push_back(tempCube);
}

void BrainbowApp::addTarget(Vec3f loc){
    tempTarget = Target(loc);
    targets.push_back(tempTarget);
}


CINDER_APP_NATIVE( BrainbowApp, RendererGl )
