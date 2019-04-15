//
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

#include <TurboBadger/tb_widgets.h>
#include <TurboBadger/tb_select_item.h>
#include <TurboBadger/tb_atomic_widgets.h>

#include "../Core/Object.h"
#include "../Container/List.h"
#include "../IO/Log.h"

#include "ASelectItem.h"

namespace Urho3D
{

class AMultiItemSource;

//@ASBindGen Class ObjectType=Ref
class AMultiItem : public  ASelectItem
{
    URHO3D_OBJECT(AMultiItem, ASelectItem )

public:

    //@ASBindGen Constructor UseUrho3DScriptContext_arg0
    AMultiItem(Context* context, const String& colid = String::EMPTY, const String& widgettype = String::EMPTY, const String& str = String::EMPTY, int colwidth = 80, int colheight=24 );
    virtual ~AMultiItem();

    //@ASBindGen Function
    void AddColumn ( const String& widgettype, const String& str, int colwidth );
    //@ASBindGen Function
    const String& GetColumnStr( int col );
    //@ASBindGen Function
    const String& GetColumnWidget( int col );
    //@ASBindGen Function
    int GetColumnWidth( int col );
    //@ASBindGen Function
    int GetNumColumns();

    virtual tb::MultiItem * GetTBItem();

#ifdef URHO3D_ANGELSCRIPT
    /// Angelscript Register object factory. (semi-manditory)
    static void RegisterObject(Context* context);
#endif

protected:

    Vector <String> colStr_;
    Vector <String> colWidget_; 
    Vector <int>  colWidth_;
    int colHeight_; 
};

//@ASBindGen Class ObjectType=Ref
class AMultiItemSource : public ASelectItemSource
{
    URHO3D_OBJECT(AMultiItemSource, ASelectItemSource )

public:

    //@ASBindGen Constructor UseUrho3DScriptContext_arg0
    AMultiItemSource(Context* context);
    virtual ~AMultiItemSource();

    void AddItem(AMultiItem* item) { items_.Push(SharedPtr<AMultiItem>(item)); }
    void RemoveItemWithId(const String& id);
    void RemoveItemWithStr(const String& str);
    int GetItemCount() { return items_.Size(); }

    void Clear() { items_.Clear(); }

    /// Returns item string for the index. Returns empty string for invalid indexes.
    const String& GetItemStr(int index);

    // caller's responsibility to clean up
    virtual tb::MultiItemSource* GetTBItemSource();

#ifdef URHO3D_ANGELSCRIPT
    /// Angelscript Register object factory. (semi-manditory)
    static void RegisterObject(Context* context);
#endif

protected:

    List<SharedPtr<AMultiItem>> items_;

};

}
