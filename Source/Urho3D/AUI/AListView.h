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
#include "../AUI/ASelectList.h"

namespace Urho3D
{

class ListViewItemSource;
class ListViewItem;

//@ASBindGen Class ObjectType=Ref
class URHO3D_API AListView : public AWidget
{
    URHO3D_OBJECT(AListView, AWidget);

public:
    /// Construct.
    //@ASBindGen Constructor UseUrho3DScriptContext_arg0
    AListView(Context* context, bool createWidget = true);

    /// Destruct.
    virtual ~AListView();

    //@ASBindGen Function
    unsigned AddRootItem(const String& text, const String& icon, const String& id);

    //@ASBindGen Function
    unsigned AddChildItem(unsigned parentItemID, const String& text, const String& icon, const String& id);


    //@ASBindGen Function
    void SetItemText(const String& id, const String& text);
    //@ASBindGen Function
    void SetItemTextSkin(const String& id, const String& skin);
    //@ASBindGen Function
    void SetItemIcon(const String& id, const String& icon);
    //@ASBindGen Function
    void DeleteItemByID(const String& id);

    //@ASBindGen Function
    void ScrollToSelectedItem();

    //@ASBindGen Function
    void SetExpanded(unsigned itemID, bool value);
    //@ASBindGen Function
    bool GetExpanded(unsigned itemID);
    //@ASBindGen Function
    bool GetExpandable(unsigned itemID);

    //@ASBindGen Function
    bool GetMultiSelect() const { return multiSelect_; }
    //@ASBindGen Function
    void SetMultiSelect(bool value) { multiSelect_ = value; }

    //@ASBindGen Function
    void DeleteAllItems();
    //@ASBindGen Function
    void SelectItemByID(const String& id, bool selected = true);

    //@ASBindGen Function
    String GetHoverItemID() { return rootList_.Null() ? "" : rootList_->GetHoverItemID(); }
    //@ASBindGen Function
    String GetSelectedItemID() { return rootList_.Null() ? "" : rootList_->GetSelectedItemID(); }

    //@ASBindGen Function AddRef_arg-1
    ASelectList* GetRootList() { return rootList_; }

    //@ASBindGen Function
    void UpdateItemVisibility();

    //@ASBindGen Function
    void SelectAllItems(bool select = true);

#ifdef URHO3D_ANGELSCRIPT
    /// Angelscript Register object factory. (semi-manditory)
    static void RegisterObject(Context* context);
#endif

protected:

    virtual bool OnEvent(const tb::TBWidgetEvent &ev) override;

private:

    void SendItemSelectedChanged(ListViewItem* item);

    void SelectSingleItem(ListViewItem* item, bool expand = true);
    void SetValueFirstSelected();
    void Move(tb::SPECIAL_KEY key);

    bool multiSelect_;

    float moveDelta_;

    SharedPtr<ASelectList> rootList_;
    ListViewItemSource* source_;

    HashMap<unsigned,ListViewItem*> itemLookup_;

    unsigned itemLookupId_;

    void SelectItem(ListViewItem* item, bool select);

    ListViewItem* pivot_;
    int pivotIndex_;
    bool startNewSelection_;

};

}
