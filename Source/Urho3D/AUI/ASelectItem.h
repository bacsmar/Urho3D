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

#include <TurboBadger/tb_widgets.h>
#include <TurboBadger/tb_select_item.h>

#include "../Core/Object.h"
#include "../Container/List.h"

namespace Urho3D
{

class ASelectItemSource;

//@ASBindGen Class ObjectType=Ref
class ASelectItem : public Object
{
    URHO3D_OBJECT(ASelectItem, Object)

public:

    //@ASBindGen Constructor UseUrho3DScriptContext_arg0
    ASelectItem(Context* context, const String& str = String::EMPTY, const String& id = String::EMPTY, const String& skinImage = String::EMPTY);
    virtual ~ASelectItem();

    //@ASBindGen Function
    void SetString(const String& str) { str_ = str; }
    //@ASBindGen Function
    void SetID(const String& id);
    //@ASBindGen Function
    const String& GetStr() { return str_; }
    tb::TBID GetID() { return id_; }
    //@ASBindGen Function
    void SetSkinImage(const String& skinImage);
    //@ASBindGen Function AddRef_arg0
    void SetSubSource(ASelectItemSource *subSource);

    virtual tb::TBGenericStringItem* GetTBItem();

#ifdef URHO3D_ANGELSCRIPT
    /// Angelscript Register object factory. (semi-manditory)
    static void RegisterObject(Context* context);
#endif

protected:

    String str_;

    // TBID
    tb::TBID id_;
    // TBID
    tb::TBID skinImage_;

    SharedPtr<ASelectItemSource> subSource_;

};

//@ASBindGen Class ObjectType=Ref
class ASelectItemSource : public Object
{
    URHO3D_OBJECT(ASelectItemSource, Object)

public:

    //@ASBindGen Constructor UseUrho3DScriptContext_arg0
    ASelectItemSource(Context* context);
    virtual ~ASelectItemSource();

    //@ASBindGen Function AddRef_arg0
    void AddItem(ASelectItem* item) { items_.Push(SharedPtr<ASelectItem>(item)); }
    //@ASBindGen Function
    void RemoveItemWithId(const String& id);
    //@ASBindGen Function
    void RemoveItemWithStr(const String& str);
    //@ASBindGen Function
    int GetItemCount() { return items_.Size(); }

    //@ASBindGen Function
    void Clear() { items_.Clear(); }

    /// Returns item string for the index. Returns empty string for invalid indexes.
    //@ASBindGen Function
    const String& GetItemStr(int index);

    // caller's responsibility to clean up
    virtual tb::TBSelectItemSource* GetTBItemSource();

#ifdef URHO3D_ANGELSCRIPT
    /// Angelscript Register object factory. (semi-manditory)
    static void RegisterObject(Context* context);
#endif

protected:

    List<SharedPtr<ASelectItem>> items_;

};

}
