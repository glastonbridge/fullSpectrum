//
//  DebugMenu.cpp
//  fullSpectrum
//
//  Created by Alex Shaw on 24/05/2013.
//
//

#include "DebugMenu.h"

#include "Parameterisable.h"

static const unsigned int WIDGET_HEIGHT = 32;

DebugMenu::DebugMenu() : videoOverlayer(0) {}

void DebugMenu::setSize(float width, float height)
{
    tabBar = auto_ptr<ofxUICanvas>(new ofxUICanvas(0,0, width, 80));
    
    parameterTweakGui = auto_ptr<ofxUIScrollableCanvas>(new ofxUIScrollableCanvas(0,80 , width, height));
    //sensorTweakGui->setSnapping(false);
    //overlayTweakGui->setSnapping(false);
    ofAddListener(parameterTweakGui->newGUIEvent,this, &DebugMenu::parameterisableGuiEvent);
    ofAddListener(tabBar->newGUIEvent,this, &DebugMenu::tabGuiEvent);
    
    tabBar->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    drawTabBar();
    recalculateParameterTweakUI();
    
    //parameterTweakGui->setScrollArea(0,controlHeight+40, streamWidth, streamHeight);
    //parameterTweakGui->getRect()->setY(controlHeight+40);
}

void DebugMenu::setVideoOverlayer(VideoOverlayer *newVideoOverlayer)
{
    videoOverlayer= newVideoOverlayer;
    drawTabBar();
}


void drawParams(ofxUICanvas* canvas, Parameterisable* toParameterise, int width)
{
    for (int paramNum = 0; paramNum < toParameterise->getParamCount(); ++paramNum)
    {
        //canvas->addWidgetDown(new ofxUILabel(toParameterise->getParamName(paramNum), OFX_UI_FONT_SMALL));
        if (toParameterise->getParamType(paramNum) == Parameterisable::PARAM_FLOAT)
        {
            canvas->addSlider(toParameterise->getParamName(paramNum),
                              toParameterise->getFloatMin(paramNum),
                              toParameterise->getFloatMax(paramNum),
                              toParameterise->getFloatValue(paramNum),
                              width, WIDGET_HEIGHT);
        }
        else if (toParameterise->getParamType(paramNum) == Parameterisable::PARAM_INT)
        {
            canvas->addSlider(toParameterise->getParamName(paramNum),
                              toParameterise->getIntMin(paramNum),
                              toParameterise->getIntMax(paramNum),
                              toParameterise->getIntValue(paramNum),
                              width, WIDGET_HEIGHT);
        }
        else if (toParameterise->getParamType(paramNum) == Parameterisable::PARAM_BOOL)
        {
            canvas->addToggle(toParameterise->getParamName(paramNum),
                              toParameterise->getBoolValue(paramNum),
                              12, WIDGET_HEIGHT);
        }
    }
}

void DebugMenu::recalculateParameterTweakUI()
{
    std::vector<ofxUIWidget*> widgets = parameterTweakGui->getWidgets();
    std::vector<ofxUIWidget*>::const_iterator widgiterator = widgets.begin();
    for (;widgiterator < widgets.end(); ++widgiterator)
    {
        if ((*widgiterator)->getKind() != OFX_UI_WIDGET_LABEL)
            parameterTweakGui->removeWidget(*widgiterator);
    }
    
    parameterTweakGui->resetPlacer();
    
    if (!activeOverlay.empty())
    {
        drawParams(parameterTweakGui.get(), videoOverlayer->getActiveOverlays()[0], 700);
    }
}

void DebugMenu::drawTabBar()
{
    if (!videoOverlayer) return;

    /*std::vector<ofxUIWidget*> widgets = tabBar->getWidgets();
    std::vector<ofxUIWidget*>::const_iterator widgiterator = widgets.begin();
    for (;widgiterator < widgets.end(); ++widgiterator)
    {
        if ((*widgiterator)->getKind() != OFX_UI_WIDGET_LABEL)
            parameterTweakGui->removeWidget(*widgiterator);
    }
    
    tabBar->resetPlacer();*/
    
    std::vector<std::string> options = videoOverlayer->getAllEffectNames();
     //std::vector<Overlay*> activeOverlays = videoOverlayer->getActiveOverlays();
     //for (int i = 0; i < activeOverlays.size(); ++i)
     //options.push_back(std::string("e:") + activeOverlays[i]->getInstanceName());
    tabBar->addRadio("", options, OFX_UI_ORIENTATION_HORIZONTAL, 32, WIDGET_HEIGHT);
}

void DebugMenu::tabGuiEvent(ofxUIEventArgs &e)
{
    //if (ofGetMousePressed()==false ) return;
    if (e.widget->getKind() == OFX_UI_WIDGET_TOGGLE)
    {
        std::string widgetName((e.widget)->getName());

        //if (widgetName.substr(0,2)=="e:")
        //{
            if (!activeOverlay.empty())
            {
                videoOverlayer->removeEffect(activeOverlay);
            }
        activeOverlay = widgetName;//.substr(2);
            videoOverlayer->addEffect(activeOverlay);
        //}
        recalculateParameterTweakUI();
    }
}

void parameteriseGuiEvent(Parameterisable* p, ofxUIEventArgs& e)
{
	if (e.widget->getKind() == OFX_UI_WIDGET_SLIDER_H)
    {
        int paramIndex = 0;
        while (paramIndex < p->getParamCount())
        {
            if (p->getParamName(paramIndex) == e.widget->getName())
            {
                break;
            }
            ++paramIndex;
        }
        if (paramIndex < p->getParamCount())
        {
            
            if (p->getParamType(paramIndex) == Parameterisable::PARAM_FLOAT)
                p->setFloatValue(paramIndex, dynamic_cast<ofxUISlider*>(e.widget)->getScaledValue());
            else if (p->getParamType(paramIndex) == Parameterisable::PARAM_INT)
                p->setIntValue(paramIndex, dynamic_cast<ofxUISlider*>(e.widget)->getScaledValue());
        }
    }
    else if (e.widget->getKind() == OFX_UI_WIDGET_TOGGLE)
    {
        int paramIndex = 0;
        while (paramIndex < p->getParamCount())
        {
            if (p->getParamName(paramIndex) == e.widget->getName())
            {
                break;
            }
            ++paramIndex;
        }
        if (paramIndex < p->getParamCount())
        {
            p->setBoolValue(paramIndex, dynamic_cast<ofxUIToggle*>(e.widget)->getValue());
        }
    }
}

void DebugMenu::parameterisableGuiEvent(ofxUIEventArgs &e)
{
    parameteriseGuiEvent(videoOverlayer->getActiveOverlays()[0], e);
}

void DebugMenu::setVisible(bool visible)
{
    tabBar->setVisible(visible);
    parameterTweakGui->setVisible(visible);
}

bool DebugMenu::getVisible()
{
    return tabBar->isVisible();
}
