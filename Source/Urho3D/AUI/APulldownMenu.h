//
// Copyright (c) 2017, THUNDERBEAST GAMES LLC All rights reserved
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

#include "../AUI/ASelectItem.h"
#include "../AUI/AButton.h"

namespace Urho3D
{

//@ASBindGen Class ObjectType=Ref
class URHO3D_API APulldownMenu : public AButton
{
    URHO3D_OBJECT(APulldownMenu, AButton)

public:

    //@ASBindGen Constructor UseUrho3DScriptContext_arg0
    APulldownMenu(Context* context, bool createWidget = true);
    virtual ~APulldownMenu();

    //@ASBindGen Function AddRef_arg0
    void SetSource(ASelectItemSource* source); /// for programming the pulled down menu

    //@ASBindGen Function
    const String& GetSelectedId(); /// return id of entry selected in menu

#ifdef URHO3D_ANGELSCRIPT
    /// Angelscript Register object factory. (semi-manditory)
    static void RegisterObject(Context* context);
#endif

protected:

    virtual bool OnEvent(const tb::TBWidgetEvent &ev) override;
    String sid_;  /// cached selected item tbid

};

}
