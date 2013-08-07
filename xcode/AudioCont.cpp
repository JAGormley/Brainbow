//
//  Audio.cpp
//  Brainbow
//
//  Created by Andrew Gormley on 2013-07-27.
//
//

#include "AudioCont.h"
#include "Resources.h"

#include "cinder/Utilities.h"
#include "cinder/audio/Output.h"
#include "cinder/audio/Io.h"


using namespace ci;
using namespace ci::app;
using namespace std;

AudioCont::AudioCont(){
}

void AudioCont::setUp(){
    
    bubbleCount = 5;
    boxCount = 5;
    
    //STRIKES
    mAudioSource = audio::load( loadResource( "activation.wav" ) );
    activate = audio::Output::addTrack(mAudioSource, false);
    activate->setVolume(1.0f);
    
    mAudioSource2 = audio::load( loadResource( "drone2.wav" ) );
    drone = audio::Output::addTrack(mAudioSource2, false);
    
    mAudioSource = audio::load( loadResource( "activation2.wav" ) );
    activate2 = audio::Output::addTrack(mAudioSource, false);
    activate2->setVolume(1.0f);
    
    mAudioSource = audio::load( loadResource( "loadtarg.wav" ) );
    target = audio::Output::addTrack(mAudioSource, false);
    target->setVolume(.1f);
    
    mAudioSource = audio::load( loadResource( "charge.wav" ) );
    charge = audio::Output::addTrack(mAudioSource, false);
    charge->setVolume(.1f);
    
    mAudioSource = audio::load( loadResource( "bubble1.wav" ) );
    bubble1 = audio::Output::addTrack(mAudioSource, false);
    bubble1->setVolume(.1f);
    
    mAudioSource = audio::load( loadResource( "bubble2.wav" ) );
    bubble2 = audio::Output::addTrack(mAudioSource, false);
    bubble2->setVolume(.1f);
    
    mAudioSource = audio::load( loadResource( "bubble3.wav" ) );
    bubble3 = audio::Output::addTrack(mAudioSource, false);
    bubble3->setVolume(.1f);
    
    mAudioSource = audio::load( loadResource( "bubble4.wav" ) );
    bubble4 = audio::Output::addTrack(mAudioSource, false);
    bubble4->setVolume(.1f);
    
    mAudioSource = audio::load( loadResource( "bubble5.wav" ) );
    bubble5 = audio::Output::addTrack(mAudioSource, false);
    bubble5->setVolume(0);
    
    mAudioSource = audio::load( loadResource( "box1.wav" ) );
    box1 = audio::Output::addTrack(mAudioSource, false);
    box1->setVolume(1.0f);
    
    mAudioSource2 = audio::load( loadResource( "box2.wav" ) );
    box2 = audio::Output::addTrack(mAudioSource2, false);
    box2->setVolume(1.0f);
    
    mAudioSource = audio::load( loadResource( "box3.wav" ) );
    box3 = audio::Output::addTrack(mAudioSource, false);
    box3->setVolume(1.0f);
    
    mAudioSource2 = audio::load( loadResource( "box4.wav" ) );
    box4 = audio::Output::addTrack(mAudioSource2, false);
    box4->setVolume(1.0f);
    
    mAudioSource = audio::load( loadResource( "box5.wav" ) );
    box5 = audio::Output::addTrack(mAudioSource, false);
    box5->setVolume(1.0f);
    
}

void AudioCont::playTraz(string s){
    
    if (s == "activate"){
        activate->stop();
        activate->setTime(0);
        activate->play();
    }
    
    if (s == "activate2"){
        activate2->stop();
        activate2->setTime(0);
        activate2->play();
    }
    
    if (s == "drone"){
        drone->setLooping(true);
        drone->play();
    }
    
    if (s == "charge"){
        charge->stop();
        charge->setTime(0);
        charge->play();
    }
    
    if (s == "box"){
        if (boxCount % 5 == 0){
            box1->setLooping(true);
            box1->play();
            box1->setVolume(1.0f);        }
        
        if (boxCount % 5 == 1){
            box2->setLooping(true);
            box2->play();
            box2->setVolume(1.0f);
        }
        if (boxCount % 5 == 2){
            box3->setLooping(true);
            box3->play();
            box3->setVolume(1.0f);
            cout << "yepp" << endl;
        }
        if (boxCount % 5 == 3){
            box4->setLooping(true);
            box4->play();
            box4->setVolume(1.0f);
        }
        if (boxCount % 5 == 4){
            box5->setLooping(true);
            box5->play();
            box5->setVolume(1.0f);
        }
        boxCount++;
    }
    
    if (s == "bubble"){
        if (bubbleCount%5 == 0){
            bubble1->setTime(0);            
            bubble1->play();
            bubble1->setVolume(.05f);
        }
        
        if (bubbleCount%5 == 1){
            bubble2->setTime(0);
            
            bubble2->play();
            bubble2->setVolume(.05f);
        }
        if (bubbleCount%5 == 2){
            bubble3->setTime(0);
            
            bubble3->play();
            bubble3->setVolume(.05f);
        }
        if (bubbleCount%5 == 3){
            bubble4->setTime(0);
            
            bubble4->play();
            bubble4->setVolume(.05f);
        }
        if (bubbleCount%5 == 4){
            bubble5->setTime(0);
            
            bubble5->play();
            bubble5->setVolume(.05f);
        }
        bubbleCount++;
    }
    
    if (s == "target"){
        target->stop();
        target->setTime(0);
        target->play();
    }
}

bool AudioCont::isPlaying(string s){
    if (s == "charge"){
        return charge->isPlaying();
    }
    return false;
}

void AudioCont::stopTraz(string s){
    cinder::audio::TrackRef a;
    cinder::audio::TrackRef b;
    
    if (s == "charge"){
        charge->stop();
        charge->setTime(0);
    }
    
    //    // STOP
    //    if (b->isPlaying()){
    //        a->stop();
    //        a->setTime(0);
    //    }
    //    if (a->isPlaying()){
    //        b->stop();
    //        b->setTime(0);
    //    }
}


//void AudioCont::update(){
//
//    updateLoop(lowDshortA, lowDshortB, 3, 4.5);
//    updateLoop(midDshortA, midDshortB, 3, 4.5);
//}

//void AudioCont::updateLoop(cinder::audio::TrackRef track){
//        if (one->getTime() > startTime){
//            two->play();
//            if (one->getTime() > endTime){
//                one->stop();
//                one->setTime(0);
//            }
//        }
//        if (two->getTime() > startTime){
//            one->play();
//            if (two->getTime() > endTime){
//                two->stop();
//                two->setTime(0);
//        }
//    }
