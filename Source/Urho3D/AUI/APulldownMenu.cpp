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

#include <TurboBadger/tb_widgets.h>
#include <TurboBadger/tb_widgets_common.h>
#include <TurboBadger/tb_atomic_widgets.h>

#include "../Precompiled.h"
#include "../IO/Log.h"

#include "../AUI/AUI.h"
#include "../AUI/AEvents.h"
#include "../AUI/APulldownMenu.h"

#ifdef URHO3D_ANGELSCRIPT
#include "../Core/Context.h"
#include "../Scene/Serializable.h"
extern const char* AUI_CATEGORY;  /// for angelscript binding
#endif

using namespace tb;

namespace Urho3D
{

APulldownMenu::APulldownMenu(Context* context, bool createWidget) : AButton(context, false)
{
    if (createWidget)
    {
        widget_ = new TBPulldownMenu();
        widget_->SetDelegate(this);
        GetSubsystem<AUI>()->WrapWidget(this, widget_);
    }
}

APulldownMenu::~APulldownMenu()
{

}

void APulldownMenu::SetSource(ASelectItemSource* source)
{
    if (!widget_)
        return;

    ((TBSelectDropdown*)widget_)->SetSource(source ? source->GetTBItemSource() : NULL);

}

const String& APulldownMenu::GetSelectedId()
{
    if (!widget_)
    {
        if (sid_.Length())
            sid_.Clear();
        return sid_;
    }

    AUI* ui = GetSubsystem<AUI>();
    ui->GetTBIDString(((TBPulldownMenu*)widget_)->GetValueID(), sid_);

    return sid_;
}

// for operational updates 
int APulldownMenu::NumMenuItems() const
{
    if (!widget_)
        return 0;

    TBGenericStringItemSource *menusrc = ((TBSelectDropdown*)widget_)->GetDefaultSource();
	if (menusrc)
	{
		return menusrc->GetNumItems();
	}

	return 0;
}

String APulldownMenu::GetMenuItemId( int index )
{
	String idx;

    if (widget_)
	{
    	TBGenericStringItemSource *menusrc = ((TBSelectDropdown*)widget_)->GetDefaultSource();
		if (menusrc)
		{
   			AUI* ui = GetSubsystem<AUI>();
    		ui->GetTBIDString( menusrc->GetItemID(index), idx);
		}
	}

    return idx;
}

String APulldownMenu::GetMenuItemString( int index )
{
    if (widget_)
	{
    	TBGenericStringItemSource *menusrc = ((TBSelectDropdown*)widget_)->GetDefaultSource();
		if (menusrc)
		{
			const char* istr = menusrc->GetItemString(index);
			if (istr)
    			return String(istr);
		}
	}
	return String::EMPTY;
}

int APulldownMenu::GetMenuItemState( int index )
{
    if (widget_)
	{
    	TBGenericStringItemSource *menusrc = ((TBSelectDropdown*)widget_)->GetDefaultSource();
		if (menusrc)
		{
			return menusrc->GetItemState(index);
		}
	}
	return 0;
}

void APulldownMenu::SetMenuItemString( int index, String newstr )
{
    if (widget_)
	{
    	TBGenericStringItemSource *menusrc = ((TBSelectDropdown*)widget_)->GetDefaultSource();
		if (menusrc)
		{
			menusrc->ChangeItemString(index, newstr.CString());
		}
	}
}

void APulldownMenu::SetMenuItemState( int index, int newstate )
{
    if (widget_)
	{
    	TBGenericStringItemSource *menusrc = ((TBSelectDropdown*)widget_)->GetDefaultSource();
		if (menusrc)
		{
			menusrc->ChangeItemState(index, newstate);
		}
	}
}

bool APulldownMenu::OnEvent(const tb::TBWidgetEvent &ev)
{

   return AButton::OnEvent(ev);

}

#if URHO3D_ANGELSCRIPT
/// Angelscript Register object factory. (semi-manditory)
void APulldownMenu::RegisterObject(Context* context)
{
    context->RegisterFactory<APulldownMenu>(AUI_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(AWidget);
}
#endif

}
