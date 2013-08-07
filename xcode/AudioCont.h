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
    bool isPlaying(string s);
    void updateLoop(cinder::audio::TrackRef one, cinder::audio::TrackRef two, float startTime, float endTime);
    
    //SRCs
    audio::SourceRef mAudioSource;
    audio::SourceRef mAudioSource2;
    
    //CLIPS    
    audio::TrackRef activate;
    audio::TrackRef activate2;
    audio::TrackRef drone;
    audio::TrackRef target;
    audio::TrackRef charge;
    
    audio::TrackRef bubble1;
    audio::TrackRef bubble2;    
    audio::TrackRef bubble3;
    audio::TrackRef bubble4;
    audio::TrackRef bubble5;
    
    audio::TrackRef box1;
    audio::TrackRef box2;
    audio::TrackRef box3;
    audio::TrackRef box4;
    audio::TrackRef box5;

    
    //MISC
    float volume1;
    ci::Timer gongTimer;
    bool isStopped;
    int bubbleCount;
    int boxCount;
    
    
};