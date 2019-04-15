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

#include "AWidget.h"

#include "../Input/Input.h"

namespace Urho3D
{


//@ASBindGen Class ObjectType=Ref
class AButton : public AWidget
{
    URHO3D_OBJECT(AButton, AWidget)

public:

    //@ASBindGen Constructor UseUrho3DScriptContext_arg0
    AButton(Context* context, bool createWidget = true);
    virtual ~AButton();

    /// Set if the button's text field should be allowed to squeeze below its preferred size
    /// If squeezable it may shrink to width 0
    //@ASBindGen Function
    void SetSqueezable(bool value);

    //@ASBindGen Function
    void SetEmulationButton(int button);

    /// A URL link may be set via the URL value (or the Text value if using TBButton.link skin)
    /// If enabled, a FileSystem open will be called when the button is clicked
    /// for example a http:// link will open the default browser
    void SetURLEnabled(bool enabled) { urlEnabled_ = enabled; }

    /// Set the URL which is opened when this button is clicked
    void SetURL (const String& url);

    /// Get the URL which is opened when this button is clicked
    String GetURL ();

    ///Set to true if the button should toggle on and off    
    //@ASBindGen Function
    void SetToggleMode(bool toggle);
    //@ASBindGen Function
    bool GetToggleMode() const;

#ifdef URHO3D_ANGELSCRIPT
    /// Angelscript Register object factory. (semi-manditory)
    static void RegisterObject(Context* context);
#endif

protected:

    virtual bool OnEvent(const tb::TBWidgetEvent &ev);

private:

    int emulationButton_;
    bool urlEnabled_;
};

}
