//
//  PongOverlay.cpp
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 28/01/2013.
//
//

#include "PongOverlay.h"

#include "PaddleSensor.h"

const int paddleWidth = 10;
const int paddleHeight = 30;
const int paddlePadding = 5;

const std::string PongOverlay::NAME = "pong overlay";

std::string PongOverlay::getName()
{
    return NAME;
}

void PongOverlay::setup(float width, float height)
{
    _width = width; _height = height;
    _ballVel.x = 4;
    _ballVel.y = 4;
    resetBall();
}

void PongOverlay::resetBall()
{
    _ballPos.x = _width/2;
    _ballPos.y = _height/2;
}

void PongOverlay::update(ofxCvColorImage *input)
{
    PaddleSensor* paddles = dynamic_cast<PaddleSensor*> (sensors[0]);
    if (_ballPos.y>_height-20 || _ballPos.y<20) _ballVel.y = -_ballVel.y;
    
    if (_ballVel.x > 0) // ball travelling left-to-right
    {
        if (_ballPos.x + _ballVel.x > _width-paddleWidth-paddlePadding) // will we go past the bat?
        {
            if (_ballPos.y > paddles->rightPaddle && _ballPos.y < paddles->rightPaddle + paddleHeight)
            {
                _ballVel.x = - _ballVel.x;
            }
            else
            {
                resetBall();
            }
        }
    }
    else // ball travelling right-to-left
    {
        if (_ballPos.x + _ballVel.x < paddleWidth + paddlePadding) // will we go past the bat?
        {
            if (_ballPos.y > paddles->leftPaddle && _ballPos.y < paddles->leftPaddle + paddleHeight)
            {
                _ballVel.x = - _ballVel.x;
            }
            else
            {
                resetBall();
            }
        }
    }
    
    _ballPos += _ballVel;
}

void PongOverlay::draw()
{
    PaddleSensor* paddles = dynamic_cast<PaddleSensor*> (sensors[0]);
    ofColor(0xFFFFFF);
    
    ofRect(paddlePadding, paddles->leftPaddle, paddleWidth , paddleHeight);
    ofRect(_width-paddleWidth-paddlePadding, paddles->rightPaddle, paddleWidth, paddleHeight);
    
    ofRect(0,10,_width,10);
    ofRect(0,_height-20,_width,10);
    
    ofCircle(_ballPos, paddleWidth/2);
}
