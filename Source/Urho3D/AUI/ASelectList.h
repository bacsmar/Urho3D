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

#include "../AUI/AWidget.h"
#include "../AUI/ASelectItem.h"

namespace tb
{
    class TBSelectList;
}

namespace Urho3D
{

//@ASBindGen Class ObjectType=Ref
class URHO3D_API ASelectList : public AWidget
{
    URHO3D_OBJECT(ASelectList, AWidget)

public:

    //@ASBindGen Constructor UseUrho3DScriptContext_arg0
    ASelectList(Context* context, bool createWidget = true);
    virtual ~ASelectList();

    //@ASBindGen Function
    void SetFilter(const String& filter);

    //@ASBindGen Function AddRef_arg0
    void SetSource(ASelectItemSource* source);
    //@ASBindGen Function
    void InvalidateList();

    //@ASBindGen Function
    void SetValue(int value);
    double GetValue() override;

    //@ASBindGen Function
    String GetHoverItemID();

    //@ASBindGen Function
    String GetSelectedItemID();

    //@ASBindGen Function
    void ScrollToSelectedItem();

    //@ASBindGen Function
    String GetItemID(int index);
    //@ASBindGen Function
    bool GetItemSelected(int index);

    //@ASBindGen Function
    int GetNumItems() const;

    //@ASBindGen Function
    void SelectItem(int index, bool selected = true);

    tb::TBSelectList* GetTBSelectList();

    //@ASBindGen Function
    void SelectNextItem();
    //@ASBindGen Function
    void SelectPreviousItem();

    //@ASBindGen Function
    void SetAListView(bool value);

    /// Returns the string of item at the requested index
    //@ASBindGen Function
    String GetItemString(int index);
    /// Returns the string of the selected item
    //@ASBindGen Function
    String GetSelectedItemString();
    /// Add a new item at the given index
    //@ASBindGen Function
    bool AddItem(int index, const String& str, const String& id = String::EMPTY );
    /// Delete the item at the given index.
    //@ASBindGen Function
    void DeleteItem(int index);
    /// Delete all items.
    //@ASBindGen Function
    void DeleteAllItems();
    /// Searches the items for the id as a number, returns index, -1 if not found 
    //@ASBindGen Function
    int FindId ( int idnum );

#ifdef URHO3D_ANGELSCRIPT
    /// Angelscript Register object factory. (semi-manditory)
    static void RegisterObject(Context* context);
#endif

protected:

    void HandleUIUpdate(StringHash eventType, VariantMap& eventData);

    virtual bool OnEvent(const tb::TBWidgetEvent &ev) override;

private:

};

}
