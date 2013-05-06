//
//  ThreadedNetwork.cpp
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 12/04/2013.
//
//

#include "ThreadedNetwork.h"


ofEvent<std::string> ThreadedNetwork::networkKeypressEvent;

ThreadedNetwork* ThreadedNetwork::instance;


ThreadedNetwork::ThreadedNetwork(){}
ThreadedNetwork::~ThreadedNetwork()
{
}

void ThreadedNetwork::start(){
    startThread(true, false);   // blocking, verbose
}

void ThreadedNetwork::stop(){
    stopThread();
}

//--------------------------
void ThreadedNetwork::threadedFunction(){
    
    prism.setup("169.254.230.192",11999);
//    prism.setup("localhost",11999);
    prism.setMessageDelimiter("\n");
    
    while( isThreadRunning() != 0 && prism.isConnected())
    {
        std::string message = prism.receive();
        if (message != "")
            ofNotifyEvent(networkKeypressEvent, message);
        sleep(10);
    }
}
