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

#include <TurboBadger/tb_scroll_container.h>

#include "../AUI/AWidget.h"

namespace Urho3D
{

//@ASBindGen Enum
enum UI_SCROLL_MODE {
    ///< X and Y always             scroll-mode: xy
    UI_SCROLL_MODE_X_Y =            0, // tb::SCROLL_MODE_X_Y,
    ///< Y always (X never)         scroll-mode: y
    UI_SCROLL_MODE_Y =              1, // tb::SCROLL_MODE_Y,
    ///< Y auto (X never)           scroll-mode: y-auto
    UI_SCROLL_MODE_Y_AUTO =         2, // tb::SCROLL_MODE_Y_AUTO,
    ///< X auto, Y auto             scroll-mode: auto
    UI_SCROLL_MODE_X_AUTO_Y_AUTO =  3, // tb::SCROLL_MODE_X_AUTO_Y_AUTO,
    ///< X any Y never              scroll-mode: off
    UI_SCROLL_MODE_OFF =            4 // tb::SCROLL_MODE_OFF
};


//@ASBindGen Class ObjectType=Ref
class URHO3D_API AScrollContainer : public AWidget
{
    URHO3D_OBJECT(AScrollContainer, AWidget)

public:

    //@ASBindGen Constructor UseUrho3DScriptContext_arg0
    AScrollContainer(Context* context, bool createWidget = true);
    virtual ~AScrollContainer();

    //@ASBindGen Function
    void SetScrollMode(UI_SCROLL_MODE mode);
    //@ASBindGen Function
    UI_SCROLL_MODE GetScrollMode();

    /// Set to true if the preferred size of this container should adapt to the preferred size of the content. This is disabled by default.
    //@ASBindGen Function
    void SetAdaptToContentSize(bool adapt);
    //@ASBindGen Function
    bool GetAdaptToContentSize();

    /// Set to true if the content should adapt to the available size of this container when it's larger than the preferred size.
    //@ASBindGen Function
    void SetAdaptContentSize(bool adapt);
    //@ASBindGen Function
    bool GetAdaptContentSize();

    //@ASBindGen Function
    void ScrollTo(int x, int y);
    
    // return where scrolled to
    int GetScrollX();
    int GetScrollY();

    /// This is overriden to add children to the widget that is being scrolled rather than the container
    virtual void AddChild(AWidget* child) override;

#ifdef URHO3D_ANGELSCRIPT
    /// Angelscript Register object factory. (semi-manditory)
    static void RegisterObject(Context* context);
#endif

protected:

    virtual bool OnEvent(const tb::TBWidgetEvent &ev) override;

private:

};

}
