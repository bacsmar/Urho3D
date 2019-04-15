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

#include "ASelectItem.h"

namespace Urho3D
{

class AMenuItemSource;

//@ASBindGen Class ObjectType=Ref
class AMenuItem : public ASelectItem
{
    URHO3D_OBJECT(AMenuItem, ASelectItem)

public:

    //@ASBindGen Constructor UseUrho3DScriptContext_arg0
    AMenuItem(Context* context, const String& str = String::EMPTY, const String& id = String::EMPTY, const String& shortcut = String::EMPTY, const String& skinBg = String::EMPTY);
    virtual ~AMenuItem();

    tb::TBGenericStringItem* GetTBItem();

#ifdef URHO3D_ANGELSCRIPT
    /// Angelscript Register object factory. (semi-manditory)
    static void RegisterObject(Context* context);
#endif

private:

    String shortcut_;
    String skinBg_;

};

//@ASBindGen Class ObjectType=Ref
class AMenuItemSource : public ASelectItemSource
{
    URHO3D_OBJECT(AMenuItemSource, ASelectItemSource)

public:

    //@ASBindGen Constructor UseUrho3DScriptContext_arg0
    AMenuItemSource(Context* context);
    virtual ~AMenuItemSource();

    // caller's responsibility to clean up
   tb::TBSelectItemSource *GetTBItemSource();

#ifdef URHO3D_ANGELSCRIPT
    /// Angelscript Register object factory. (semi-manditory)
    static void RegisterObject(Context* context);
#endif

private:

};

}
