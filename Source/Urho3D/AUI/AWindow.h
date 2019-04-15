//
// Copyright (c) 2014-2015, THUNDERBEAST GAMES LLC All rights reserved
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

#include<TurboBadger/tb_window.h>

#include "AWidget.h"

namespace Urho3D
{

//@ASBindGen Enum
enum UI_WINDOW_SETTINGS {

    ///< Chrome less window without any other settings.
    UI_WINDOW_SETTINGS_NONE             = 0, // tb::WINDOW_SETTINGS_NONE,
    ///< Show a title bar that can also move the window.
    UI_WINDOW_SETTINGS_TITLEBAR         = 1, // tb::WINDOW_SETTINGS_TITLEBAR,
    ///< Show a widget for resizing the window.
    UI_WINDOW_SETTINGS_RESIZABLE        = 2, // tb::WINDOW_SETTINGS_RESIZABLE,
    ///< Show a widget for closing the window.
    UI_WINDOW_SETTINGS_CLOSE_BUTTON     = 4, // tb::WINDOW_SETTINGS_CLOSE_BUTTON,
    ///< Can be activated and deactivate other windows.
    UI_WINDOW_SETTINGS_CAN_ACTIVATE     = 8, // tb::WINDOW_SETTINGS_CAN_ACTIVATE,

    UI_WINDOW_SETTINGS_DEFAULT          = 15 // tb::WINDOW_SETTINGS_DEFAULT
};


//@ASBindGen Class ObjectType=Ref
class AWindow : public AWidget
{
    URHO3D_OBJECT(AWindow, AWidget)

    public:

    //@ASBindGen Constructor UseUrho3DScriptContext_arg0
    AWindow(Context* context, bool createWidget = true);
    virtual ~AWindow();

    //@ASBindGen Function
    UI_WINDOW_SETTINGS GetSettings();
    //@ASBindGen Function
    void SetSettings(UI_WINDOW_SETTINGS settings);

    //@ASBindGen Function
    void ResizeToFitContent();

    void AddChild(AWidget *child);

    //@ASBindGen Function
    void Close();
    
    void SetAxis(UI_AXIS axis);  /// Axis orientation of titlebar, UI_AXIS_Y = top(default), UI_AXIS_X = left side

#ifdef URHO3D_ANGELSCRIPT
    /// Angelscript Register object factory. (semi-manditory)
    static void RegisterObject(Context* context);
#endif

protected:

    virtual bool OnEvent(const tb::TBWidgetEvent &ev);

private:

};

}
