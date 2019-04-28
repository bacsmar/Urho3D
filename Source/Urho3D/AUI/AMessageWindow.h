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

#include <TurboBadger/tb_message_window.h>

#include "../AUI/AWindow.h"

namespace Urho3D
{

//@ASBindGen Enum
enum UI_MESSAGEWINDOW_SETTINGS
{
    UI_MESSAGEWINDOW_SETTINGS_NONE = 0,
    UI_MESSAGEWINDOW_SETTINGS_OK = 1, // tb::TB_MSG_OK,
    UI_MESSAGEWINDOW_SETTINGS_OK_CANCEL = 2, // tb::TB_MSG_OK_CANCEL,
    UI_MESSAGEWINDOW_SETTINGS_YES_NO = 3 // tb::TB_MSG_YES_NO
};


//@ASBindGen Class ObjectType=Ref
class URHO3D_API AMessageWindow : public AWindow
{
    URHO3D_OBJECT(AMessageWindow, AWindow)

public:

    //@ASBindGen Constructor UseUrho3DScriptContext_arg0
    AMessageWindow(Context* context, AWidget* target = NULL, const String& id = String::EMPTY, bool createWidget = true);
    virtual ~AMessageWindow();

    //@ASBindGen Function
    void Show(const String& title, const String& message, UI_MESSAGEWINDOW_SETTINGS settings, bool dimmer, int width, int height);

#ifdef URHO3D_ANGELSCRIPT
    /// Angelscript Register object factory. (semi-manditory)
    static void RegisterObject(Context* context);
#endif

protected:

    virtual bool OnEvent(const tb::TBWidgetEvent &ev) override;

private:

};

}
