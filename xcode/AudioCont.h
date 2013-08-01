//
//  Audio.h
//  Brainbow
//
//  Created by Andrew Gormley on 2013-07-27.
//
//

#ifndef __Brainbow__Audio__
#define __Brainbow__Audio__

#include <iostream>
#include "cinder/audio/Output.h"
#include "cinder/audio/Io.h"
#endif /* defined(__Brainbow__Audio__) */

using namespace ci;
using namespace ci::app;
using namespace std;

class AudioCont {
public:
    AudioCont();
    
    //FNS
    void setUp();
    void update();
    void playTraz(string s);
    void stopTraz(string s);
    void updateLoop(cinder::audio::TrackRef one, cinder::audio::TrackRef two, float startTime, float endTime);
    
    //SRCs
    audio::SourceRef mAudioSource;
    audio::SourceRef mAudioSource2;
    
    //CLIPS    
    audio::TrackRef activate;
    audio::TrackRef lowDshortA;
    audio::TrackRef lowDshortB;
    audio::TrackRef midDshortA;
    audio::TrackRef midDshortB;
    
    //MISC
    float volume1;
    ci::Timer gongTimer;
    bool isStopped;
    
    
};