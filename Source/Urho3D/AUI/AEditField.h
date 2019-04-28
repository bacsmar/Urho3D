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

#include <TurboBadger/tb_editfield.h>

#include "../AUI/AWidget.h"

namespace Urho3D
{

//@ASBindGen Enum
enum UI_EDIT_TYPE {
    UI_EDIT_TYPE_TEXT = 0, // tb::EDIT_TYPE_TEXT,
    UI_EDIT_TYPE_SEARCH = 1, // tb::EDIT_TYPE_SEARCH,
    UI_EDIT_TYPE_PASSWORD = 2, // tb::EDIT_TYPE_PASSWORD,
    UI_EDIT_TYPE_EMAIL = 3, // tb::EDIT_TYPE_EMAIL,
    UI_EDIT_TYPE_PHONE = 4, // tb::EDIT_TYPE_PHONE,
    UI_EDIT_TYPE_URL = 5, // tb::EDIT_TYPE_URL,
    UI_EDIT_TYPE_NUMBER = 6 // tb::EDIT_TYPE_NUMBER
};

//@ASBindGen Class ObjectType=Ref
class URHO3D_API AEditField : public AWidget
{
    URHO3D_OBJECT(AEditField, AWidget)

public:

    //@ASBindGen Constructor UseUrho3DScriptContext_arg0
    AEditField(Context* context, bool createWidget = true);
    virtual ~AEditField();

    //@ASBindGen Function
    void AppendText(const String& text);

    //@ASBindGen Function
    void SetTextAlign(UI_TEXT_ALIGN align);

    //@ASBindGen Function
    void SetAdaptToContentSize(bool adapt);
    //@ASBindGen Function
    bool GetAdaptToContentSize() const;

    //@ASBindGen Function
    void SetEditType(UI_EDIT_TYPE type);

    //@ASBindGen Function
    void SetReadOnly(bool readonly);
    //@ASBindGen Function
    void SetStyling(bool styling);
    //@ASBindGen Function
    void SetMultiline(bool multiline);

    //@ASBindGen Function
    void Reformat(bool update_fragments = false);

    //@ASBindGen Function
    void ScrollTo(int x, int y);

    //@ASBindGen Function
    void SetWrapping(bool wrap);
    //@ASBindGen Function
    bool GetWrapping();

#ifdef URHO3D_ANGELSCRIPT
    /// Angelscript Register object factory. (semi-manditory)
    static void RegisterObject(Context* context);
#endif

protected:

    virtual bool OnEvent(const tb::TBWidgetEvent &ev) override;

    virtual void OnFocusChanged(bool focused) override;

private:
    // Used to keep track of if we have just been focused for the click select
    bool firstFocusFlag_;
};

}
