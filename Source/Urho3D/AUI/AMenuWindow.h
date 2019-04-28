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

#include <TurboBadger/tb_select_item.h>
#include <TurboBadger/tb_menu_window.h>
#include "../AUI/AWidget.h"

namespace Urho3D
{

class ASelectItemSource;

//@ASBindGen Class ObjectType=Ref
class URHO3D_API AMenuWindow : public AWidget
{
    URHO3D_OBJECT(AMenuWindow, AWidget)

public:

    //@ASBindGen Constructor UseUrho3DScriptContext_arg0
    AMenuWindow(Context* context, AWidget* target = NULL, const String& id = String::EMPTY);
    virtual ~AMenuWindow();

    //@AS Bind Gen Function AddRef_arg0  -- HELP causes asbindgen parser fault
    void Show(ASelectItemSource* source, int x = -1, int y = -1);

    //@ASBindGen Function AddRef_arg0
    void ShowMenu(ASelectItemSource* source, int xx, int yy) // as binding
    {
        Show(source,xx,yy);
    }

    //@ASBindGen Function
    void Close();

#ifdef URHO3D_ANGELSCRIPT
    /// Angelscript Register object factory. (semi-manditory)
    static void RegisterObject(Context* context);
#endif

protected:

    virtual bool OnEvent(const tb::TBWidgetEvent &ev) override;

private:

    tb::TBSelectItemSource* source_;

};

}
