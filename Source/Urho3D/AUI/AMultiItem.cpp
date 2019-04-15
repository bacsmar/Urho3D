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

#include "AMultiItem.h"

#ifdef URHO3D_ANGELSCRIPT
#include "../Core/Context.h"
#include "../Scene/Serializable.h"
extern const char* AUI_CATEGORY;  /// for angelscript binding
#endif

using namespace tb;

namespace Urho3D
{

AMultiItem::AMultiItem(Context* context, const String &colid, const String &widgettype, const String &str, int colwidth, int colheight )
 : ASelectItem(context, str, colid)
{
    SetID(colid);
    AddColumn ( widgettype, str, colwidth );
    colHeight_ = colheight; 
}

AMultiItem::~AMultiItem()
{
}

void AMultiItem::AddColumn ( const String& widgettype, const String& str, int cwidth ) 
{
    colStr_.Push(str);
    colWidget_.Push(widgettype);
    colWidth_.Push(cwidth);
}

const String& AMultiItem::GetColumnStr( int col )
{
    if ( col > -1 )
        return colStr_[col];
    return ( String::EMPTY );
}

const String& AMultiItem::GetColumnWidget( int col ) 
{
    if ( col > -1 )
    return colWidget_[col];
    return ( String::EMPTY );
}

int AMultiItem::GetColumnWidth( int col ) 
{
    if ( col > -1 )
        return colWidth_[col];
    return 0;
}

int AMultiItem::GetNumColumns()
{
    return colStr_.Size();
}

tb::MultiItem* AMultiItem::GetTBItem()
{
    tb::MultiItem* item = NULL;

    int col = 0;
    int numcols = GetNumColumns();
    String strx = GetColumnStr(col);
    String widx = GetColumnWidget(col);
    int wix = GetColumnWidth(col);
    item = new tb::MultiItem(id_, widx.CString(), strx.CString(), wix, colHeight_ );
    for ( col = 1; col<numcols; col++)
    {
        strx = GetColumnStr(col);
        widx = GetColumnWidget(col);
        wix = GetColumnWidth(col);
        item->AddColumn( widx.CString(), strx.CString(), wix );
    }
    return item;
}

#if URHO3D_ANGELSCRIPT
/// Angelscript Register object factory. (semi-manditory)
void AMultiItem::RegisterObject(Context* context)
{
    context->RegisterFactory<AMultiItem>(AUI_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(ASelectItem);
}
#endif


// AMultiItemSource 

AMultiItemSource::AMultiItemSource(Context* context) :  ASelectItemSource(context)
{

}

AMultiItemSource::~AMultiItemSource()
{

}

void AMultiItemSource::RemoveItemWithId(const String& id)
{
    tb::TBID test = TBID(id.CString());
    for (List<SharedPtr<AMultiItem> >::Iterator itr = items_.Begin(); itr != items_.End(); itr++)
    {
        if ((*itr)->GetID() == test) {
            items_.Erase(itr);
            break;
        }
    }
}

void AMultiItemSource::RemoveItemWithStr(const String& str)
{
    for (List<SharedPtr<AMultiItem> >::Iterator itr = items_.Begin(); itr != items_.End(); itr++)
    {
        if ((*itr)->GetColumnStr(0) == str) {
            items_.Erase(itr);
            break;
        }
    }
}

const String& AMultiItemSource::GetItemStr(int index)
{
    int nn = 0;
    for (List<SharedPtr<AMultiItem> >::Iterator itr = items_.Begin(); itr != items_.End(); itr++)
    {
        if ( nn == index) return (*itr)->GetColumnStr(0);
        nn++;
    }
    return ( String::EMPTY );
}

MultiItemSource *AMultiItemSource::GetTBItemSource()
{
    // caller's responsibility to clean up
    MultiItemSource* src = new MultiItemSource();

    for (List<SharedPtr<AMultiItem> >::Iterator itr = items_.Begin(); itr != items_.End(); itr++)
    {
        tb::MultiItem* tbitem = (*itr)->GetTBItem();
        src->AddItem(tbitem);
    }

    return src;
}

#if URHO3D_ANGELSCRIPT
/// Angelscript Register object factory. (semi-manditory)
void AMultiItemSource::RegisterObject(Context* context)
{
    context->RegisterFactory<AMultiItemSource>(AUI_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(ASelectItemSource);
}
#endif

}
