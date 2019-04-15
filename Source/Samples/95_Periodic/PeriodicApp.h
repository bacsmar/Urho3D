//
// Copyright (c) 2008-2016 the Urho3D project.
// Copyright (c) 2014-2017, THUNDERBEAST GAMES LLC All rights reserved
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#pragma once

#include <../Engine/Application.h>
#include <../Input/Input.h>
#include <../AUI/AEvents.h>
#include <../AUI/AWidget.h>
#include <../IO/Log.h>

namespace Urho3D
{
class Node;
class Scene;
class AView;
class ATextField;
}

using namespace Urho3D;

class PeriodicApp : public Application
{
    URHO3D_OBJECT(PeriodicApp, Application)

public:
    /// Constructor
    PeriodicApp(Context* context);
    /// Setup before engine initialization. Modifies the engine parameters.
    virtual void Setup();
    /// Setup after engine initialization. Creates the logo, console & debug HUD.
    virtual void Start();
    /// Cleanup after the main loop. Called by Application.
    virtual void Stop();

    void setup_table( AWidget *layout);
    void setup_abargraph( AWidget *layout);
    void setup_abutton( AWidget *layout);
    void setup_acheckbox( AWidget *layout);
    void setup_aclicklabel( AWidget *layout);
    void setup_acolorwheel( AWidget *layout);
    void setup_acolorwidget( AWidget *layout);
    void setup_acontainer( AWidget *layout);
    void setup_aeditfield( AWidget *layout);
    void setup_afinderwindow( AWidget *layout, AView *someview);
    void setup_afontdescription( AWidget *layout);
    void setup_aimagewidget( AWidget *layout);
    void setup_ainlineselect( AWidget *layout);
    void setup_alayoutparams( AWidget *layout);
    void setup_alayout( AWidget *layout, AView *someview);
    void setup_amenuitem( AWidget *layout);
    void setup_amenuwindow( AWidget *layout);
    void setup_amessagewindow( AWidget *layout);
    void setup_amultiitem( AWidget *layout);
    void setup_apromptwindow( AWidget *layout, AView *someview);
    void setup_apulldownmenu( AWidget *layout);
    void setup_aradiobutton( AWidget *layout);
    void setup_asceneview( AWidget *layout);
    void setup_ascrollbar( AWidget *layout);
    void setup_ascrollcontainer( AWidget *layout);
    void setup_asection( AWidget *layout);
    void setup_aselectdropdown( AWidget *layout);
    void setup_aselectitem( AWidget *layout);
    void setup_aselectlist( AWidget *layout);
    void setup_aseparator( AWidget *layout);
    void setup_askinimage( AWidget *layout);
    void setup_aslider( AWidget *layout);
    void setup_atabcontainer( AWidget *layout);
    void setup_atextfield( AWidget *layout);
    void setup_atexturewidget( AWidget *layout);
    void setup_awidget( AWidget *layout);
    void setup_awindow( AWidget *layout, AView *someview);

protected:

    void HandleExitEvent(StringHash eventType, VariantMap& eventData);  // handle exit (atomic logo) button.

    void HandleTableEvent(StringHash eventType, VariantMap& eventData);  // handle table clicks
    void HandleAbargraphEvent(StringHash eventType, VariantMap& eventData);
    void HandleAbuttonEvent(StringHash eventType, VariantMap& eventData);
    void HandleAcheckboxEvent(StringHash eventType, VariantMap& eventData);
    void HandleAclicklabelEvent(StringHash eventType, VariantMap& eventData);
    void HandleAcolorwheelEvent(StringHash eventType, VariantMap& eventData);
    void HandleAcolorwidgetEvent(StringHash eventType, VariantMap& eventData);
    void HandleAcontainerEvent(StringHash eventType, VariantMap& eventData);
    void HandleAeditfieldEvent(StringHash eventType, VariantMap& eventData);
    void HandleAfinderwindowEvent(StringHash eventType, VariantMap& eventData);
    void HandleAfontdescriptionEvent(StringHash eventType, VariantMap& eventData);
    void HandleAimagewidgetEvent(StringHash eventType, VariantMap& eventData);
    void HandleAinlineselectEvent(StringHash eventType, VariantMap& eventData);
    void HandleAlayoutparamsEvent(StringHash eventType, VariantMap& eventData);
    void HandleAlayoutEvent(StringHash eventType, VariantMap& eventData);
    void HandleAmenuitemEvent(StringHash eventType, VariantMap& eventData);
    void HandleAmenuwindowEvent(StringHash eventType, VariantMap& eventData);
    void HandleAmessagewindowEvent(StringHash eventType, VariantMap& eventData);
    void HandleAmultiitemEvent(StringHash eventType, VariantMap& eventData);
    void HandleApromptwindowEvent(StringHash eventType, VariantMap& eventData);
    void HandleApulldownmenuEvent(StringHash eventType, VariantMap& eventData);
    void HandleAradiobuttonEvent(StringHash eventType, VariantMap& eventData);
    void HandleAsceneviewEvent(StringHash eventType, VariantMap& eventData);
    void HandleAscrollbarEvent(StringHash eventType, VariantMap& eventData);
    void HandleAscrollcontainerEvent(StringHash eventType, VariantMap& eventData);
    void HandleAsectionEvent(StringHash eventType, VariantMap& eventData);
    void HandleAselectdropdownEvent(StringHash eventType, VariantMap& eventData);
    void HandleAselectitemEvent(StringHash eventType, VariantMap& eventData);
    void HandleAselectlistEvent(StringHash eventType, VariantMap& eventData);
    void HandleAseparatorEvent(StringHash eventType, VariantMap& eventData);
    void HandleAskinimageEvent(StringHash eventType, VariantMap& eventData);
    void HandleAsliderEvent(StringHash eventType, VariantMap& eventData);
    void HandleAtabcontainerEvent(StringHash eventType, VariantMap& eventData);
    void HandleAtextfieldEvent(StringHash eventType, VariantMap& eventData);
    void HandleAtexturewidgetEvent(StringHash eventType, VariantMap& eventData);
    void HandleAwidgetEvent(StringHash eventType, VariantMap& eventData);
    void HandleAwindowEvent(StringHash eventType, VariantMap& eventData);

    void HandleFinderCompleteEvent(StringHash eventType, VariantMap& eventData);
    void HandlePromptCompleteEvent(StringHash eventType, VariantMap& eventData);
    void HandleMessageCompleteEvent(StringHash eventType, VariantMap& eventData);

    // for widget class event handlers
    void HandleAllScrollcontainerEvent(StringHash eventType, VariantMap& eventData);
    void HandleAllSelectdropdownEvent(StringHash eventType, VariantMap& eventData);
    void HandleAllSliderEvent(StringHash eventType, VariantMap& eventData);
    void HandleAllTabcontainerEvent(StringHash eventType, VariantMap& eventData);

    void AppLog ( const String &logtext );
    void ViewCode ( String filename, AWidget *layoutParent );
    void HandleViewCodeEvent(StringHash eventType, VariantMap& eventData);
    String EventReport ( int eventNumber );
    AWidget *FindTheWindowParent( AWidget* fromThisWidget ); // for use with close buttons in windows
     
private:

    void HandleKeyDown(StringHash eventType, VariantMap& eventData); // basic service to collect keys
    void SetWindowTitleAndIcon(); // basic service to fix up window

    void DoSomething();  // This is your game, any questions?
    WeakPtr<Scene> scene_;  // scene support for your game
    WeakPtr<AView> uiview_; // widget support for your game
    WeakPtr<ATextField> uilog_; // widget support for your game

};

