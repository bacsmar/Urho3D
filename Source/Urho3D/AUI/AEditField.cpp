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

#include <TurboBadger/tb_widgets.h>
#include <TurboBadger/tb_widgets_common.h>
#include <TurboBadger/tb_editfield.h>

#include "../Precompiled.h"
#include "../Input/Input.h"

#include "../AUI/AUI.h"
#include "../AUI/AEvents.h"
#include "../AUI/AEditField.h"


#ifdef URHO3D_ANGELSCRIPT
#include "../Core/Context.h"
#include "../Scene/Serializable.h"
extern const char* AUI_CATEGORY;  /// for angelscript binding
#endif

using namespace tb;

namespace Urho3D
{

AEditField::AEditField(Context* context, bool createWidget) : AWidget(context, false),
    firstFocusFlag_(false)
{
    if (createWidget)
    {
        widget_ = new TBEditField();
        widget_->SetDelegate(this);
        GetSubsystem<AUI>()->WrapWidget(this, widget_);
    }
}

AEditField::~AEditField()
{

}

void AEditField::SetReadOnly(bool readonly)
{
    if (!widget_)
        return;

    TBEditField* w = (TBEditField*) widget_;

    w->SetReadOnly(readonly);

}

void AEditField::SetStyling(bool styling)
{
    if (!widget_)
        return;

    TBEditField* w = (TBEditField*) widget_;

    w->SetStyling(styling);

}

void AEditField::SetMultiline(bool multiline)
{
    if (!widget_)
        return;

    TBEditField* w = (TBEditField*) widget_;

    w->SetMultiline(multiline);

}

void AEditField::SetWrapping(bool wrap)
{
    if (!widget_)
        return;

    TBEditField* w = (TBEditField*) widget_;

    w->SetWrapping(wrap);
}

bool AEditField::GetWrapping()
{
    if (!widget_)
        return false;

    TBEditField* w = (TBEditField*) widget_;

    return w->GetWrapping();

}

void AEditField::SetEditType(UI_EDIT_TYPE type)
{
    if (!widget_)
        return;

    // safe cast?
    TBEditField* w = (TBEditField*) widget_;

    w->SetEditType((tb::EDIT_TYPE) type);

}

void AEditField::ScrollTo(int x, int y)
{
    if (!widget_)
        return;

    // safe cast?
    TBEditField* w = (TBEditField*) widget_;

    w->ScrollTo(x, y);

}

void AEditField::AppendText(const String& text)
{
    if (!widget_)
        return;

    // safe cast?
    TBEditField* w = (TBEditField*) widget_;

    w->AppendText(text.CString());

}

void AEditField::SetAdaptToContentSize(bool adapt)
{
    if (!widget_)
        return;

    TBEditField* w = (TBEditField*) widget_;

    w->SetAdaptToContentSize(adapt);

}

bool AEditField::GetAdaptToContentSize() const
{
    if (!widget_)
        return false;

    // safe cast?
    TBEditField* w = (TBEditField*) widget_;

    return w->GetAdaptToContentSize();

}

void AEditField::Reformat(bool update_fragments)
{
    if (!widget_)
        return;

    TBEditField* w = (TBEditField*) widget_;
    w->Reformat(update_fragments);
}


void AEditField::SetTextAlign(UI_TEXT_ALIGN align)
{
    if (!widget_)
        return;

    // safe cast?
    TBEditField* w = (TBEditField*) widget_;

    switch (align)
    {
        case UI_TEXT_ALIGN_CENTER:
            w->SetTextAlign(TB_TEXT_ALIGN_CENTER);
            break;
        case UI_TEXT_ALIGN_LEFT:
            w->SetTextAlign(TB_TEXT_ALIGN_LEFT);
            break;
        case UI_TEXT_ALIGN_RIGHT:
            w->SetTextAlign(TB_TEXT_ALIGN_RIGHT);
            break;
    }

}

void AEditField::OnFocusChanged(bool focused)
{
    AWidget::OnFocusChanged(focused);

    if (!widget_)
        return;

    // safe cast?
    TBEditField* w = (TBEditField*) widget_;

    TBStyleEdit* styleEdit = w->GetStyleEdit();
    if (styleEdit != NULL)
    {
        if (focused)
        {
            if (!w->GetMultiline())
                styleEdit->selection.SelectAll();
            firstFocusFlag_ = true;

#if defined(__ANDROID__) || defined(IOS)  || defined(TVOS)

            // click on field to gain focus and bring up the onscreen keyboard to edit
            if ( !(w->GetReadOnly() || w->GetState(WIDGET_STATE_DISABLED)) )
            { 
                Input* input = GetSubsystem<Input>();
                input->SetScreenKeyboardVisible(true); 
            }
#endif  

        }
        else
        {
            styleEdit->selection.SelectNothing();
        }
    }

}

bool AEditField::OnEvent(const tb::TBWidgetEvent &ev)
{
    if (ev.type == EVENT_TYPE_CUSTOM && ev.ref_id == TBIDC("edit_complete"))
    {
        VariantMap eventData;
        eventData[AWidgetEditComplete::P_WIDGET] = this;
        SendEvent(E_AWIDGETEDITCOMPLETE, eventData);
        return true;
    }
    else if (ev.type == EVENT_TYPE_POINTER_DOWN)
    {
        // Select the entire value in the field when it is selected
        if (widget_ && firstFocusFlag_)
        {
            firstFocusFlag_ = false;

            // safe cast?
            TBEditField* w = (TBEditField*) widget_;

            TBStyleEdit* styleEdit = w->GetStyleEdit();
            if (styleEdit != NULL && !w->GetMultiline())
            {
                styleEdit->selection.SelectAll();
            }
        }

#if defined(__ANDROID__) || defined(IOS)  || defined(TVOS)

        // triple click to get the onscreen keyboard, in case it is auto-focused
        else if ( ev.count == 3 ) 
        {
            TBEditField* w = (TBEditField*) widget_;
            if ( !(w->GetReadOnly() || w->GetState(WIDGET_STATE_DISABLED)) )
            { 
                Input* input = GetSubsystem<Input>();
                input->SetScreenKeyboardVisible(true); 
            }
        }

#endif

    }

    return AWidget::OnEvent(ev);
}

#if URHO3D_ANGELSCRIPT
/// Angelscript Register object factory. (semi-manditory)
void AEditField::RegisterObject(Context* context)
{
    context->RegisterFactory<AEditField>(AUI_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(AWidget);
}
#endif


}
