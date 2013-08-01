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
    
    //STRIKES
    mAudioSource = audio::load( loadResource( "activation.wav" ) );
    activate = audio::Output::addTrack(mAudioSource, false);
    activate->setVolume(1.0f);
    
    //LOOPS
    mAudioSource = audio::load( loadResource( "lowdroneSHORT.wav" ) );
    lowDshortA = audio::Output::addTrack(mAudioSource, false);
    mAudioSource2 = audio::load( loadResource( "lowdroneSHORT.wav" ) );
    lowDshortB = audio::Output::addTrack(mAudioSource2, false);
    
    mAudioSource = audio::load( loadResource( "middrone.wav" ) );
    midDshortA = audio::Output::addTrack(mAudioSource, false);
    mAudioSource2 = audio::load( loadResource( "middrone.wav" ) );
    midDshortB = audio::Output::addTrack(mAudioSource2, false);
    
}

void AudioCont::playTraz(string s){
    
    if (s == "activate"){
        activate->stop();
        activate->setTime(0);
        activate->play();
    }
    
    if (s == "lowdrone"){
        lowDshortA->play();
    }
    
    if (s == "middrone"){
        midDshortA->play();
    }
}

void AudioCont::stopTraz(string s){
    cinder::audio::TrackRef a;
    cinder::audio::TrackRef b;
    
    // WHICH CLIP
    if (s == "lowdrone"){
        a = lowDshortA;
        b = lowDshortB;
    }
    if (s == "middrone"){
        a = midDshortA;
        b = midDshortB;
    }    
    
    // STOP
    if (b->isPlaying()){
        a->stop();
        a->setTime(0);
    }
    if (a->isPlaying()){
        b->stop();
        b->setTime(0);
    }
}


void AudioCont::update(){
    
    updateLoop(lowDshortA, lowDshortB, 3, 4.5);
    updateLoop(midDshortA, midDshortB, 3, 4.5);
}

void AudioCont::updateLoop(cinder::audio::TrackRef one, cinder::audio::TrackRef two, float startTime, float endTime){
        if (one->getTime() > startTime){
            two->play();
            if (one->getTime() > endTime){
                one->stop();
                one->setTime(0);
            }
        }
        if (two->getTime() > startTime){
            one->play();
            if (two->getTime() > endTime){
                two->stop();
                two->setTime(0);
        }
    }
}