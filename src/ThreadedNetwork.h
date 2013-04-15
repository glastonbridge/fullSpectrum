//
//  ThreadedNetwork.h
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 12/04/2013.
//
//

#pragma once

#ifndef fullSpectrumAnalyser_ThreadedNetwork_h
#define fullSpectrumAnalyser_ThreadedNetwork_h

#include "ofMain.h"
#include "ofxNetwork.h"

class ThreadedNetwork : public ofThread
{
    
public:
    int users = 0;
    
    static ofEvent<std::string> networkKeypressEvent;

    ThreadedNetwork();
    ~ThreadedNetwork();
    
    void start();
    
    void stop();
    
    void threadedFunction();
    static ThreadedNetwork* instance;
    
private:
    ofxTCPClient prism;
};

#endif
