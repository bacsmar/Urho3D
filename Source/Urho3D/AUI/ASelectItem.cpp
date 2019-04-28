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
#include "../Precompiled.h"

#include "../AUI/ASelectItem.h"

#ifdef URHO3D_ANGELSCRIPT
#include "../Core/Context.h"
#include "../Scene/Serializable.h"
extern const char* AUI_CATEGORY;  /// for angelscript binding
#endif

using namespace tb;

namespace Urho3D
{

ASelectItem::ASelectItem(Context* context, const String &str, const String &id, const String &skinImage) :
    Object(context),
    subSource_(nullptr)
{
    SetID(id);
    SetString(str);
    SetSkinImage(skinImage);
}

ASelectItem::~ASelectItem()
{
}

void ASelectItem::SetID(const String& id)
{
    id_ = TBID(id.CString());
}

void ASelectItem::SetSkinImage(const String& skinImage)
{
    skinImage_ = TBID(skinImage.CString());
}

void ASelectItem::SetSubSource(ASelectItemSource *subSource)
{
    subSource_ = subSource;
}

tb::TBGenericStringItem* ASelectItem::GetTBItem()
{
    tb::TBGenericStringItem* item;
    if (!subSource_)
    {
         item = new tb::TBGenericStringItem(str_.CString(), id_);
         if (skinImage_)
             item->SetSkinImage(skinImage_);
    }
    else
    {
        item = new tb::TBGenericStringItem(str_.CString(), subSource_->GetTBItemSource());
    }

    return item;
}

#if URHO3D_ANGELSCRIPT
/// Angelscript Register object factory. (semi-manditory)
void ASelectItem::RegisterObject(Context* context)
{
    context->RegisterFactory<ASelectItem>(AUI_CATEGORY);
}
#endif


// Source

ASelectItemSource::ASelectItemSource(Context* context) : Object(context)
{

}

ASelectItemSource::~ASelectItemSource()
{

}

void ASelectItemSource::RemoveItemWithId(const String& id)
{
    tb::TBID test = TBID(id.CString());
    for (List<SharedPtr<ASelectItem> >::Iterator itr = items_.Begin(); itr != items_.End(); itr++)
    {
        if ((*itr)->GetID() == test) {
            items_.Erase(itr);
            break;
        }
    }
}

void ASelectItemSource::RemoveItemWithStr(const String& str)
{
    for (List<SharedPtr<ASelectItem> >::Iterator itr = items_.Begin(); itr != items_.End(); itr++)
    {
        if ((*itr)->GetStr() == str) {
            items_.Erase(itr);
            break;
        }
    }
}

const String& ASelectItemSource::GetItemStr(int index)
{
    int nn = 0;
    for (List<SharedPtr<ASelectItem> >::Iterator itr = items_.Begin(); itr != items_.End(); itr++)
    {
        if ( nn == index) return (*itr)->GetStr();
        nn++;
    }
    return ( String::EMPTY );
}

TBSelectItemSource *ASelectItemSource::GetTBItemSource()
{
    // caller's responsibility to clean up
    TBGenericStringItemSource* src = new TBGenericStringItemSource();

    for (List<SharedPtr<ASelectItem> >::Iterator itr = items_.Begin(); itr != items_.End(); itr++)
    {
        tb::TBGenericStringItem* tbitem = (*itr)->GetTBItem();
        src->AddItem(tbitem);
    }

    return src;
}

#ifdef URHO3D_ANGELSCRIPT
/// Angelscript Register object factory. (semi-manditory)
void ASelectItemSource::RegisterObject(Context* context)
{
    context->RegisterFactory<ASelectItemSource>(AUI_CATEGORY);
}
#endif

}
