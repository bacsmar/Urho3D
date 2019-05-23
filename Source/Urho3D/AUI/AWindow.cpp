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
#include <TurboBadger/tb_window.h>

#include "../Precompiled.h"
#include "../IO/Log.h"

#include "../AUI/AUI.h"
#include "../AUI/AEvents.h"
#include "../AUI/AWindow.h"

#ifdef URHO3D_ANGELSCRIPT
#include "../Core/Context.h"
#include "../Scene/Serializable.h"
extern const char* AUI_CATEGORY;  /// for angelscript binding
#endif


using namespace tb;

namespace Urho3D
{

AWindow::AWindow(Context* context, bool createWidget) : AWidget(context, false)
{
    if (createWidget)
    {
        widget_ = new TBWindow();
        widget_->SetDelegate(this);
        GetSubsystem<AUI>()->WrapWidget(this, widget_);
    }
}
UI_WINDOW_SETTINGS AWindow::GetSettings()
{
    if (!widget_)
        return UI_WINDOW_SETTINGS_DEFAULT;

    return (UI_WINDOW_SETTINGS) ((TBWindow*)widget_)->GetSettings();

}

void AWindow::SetSettings(UI_WINDOW_SETTINGS settings)
{
    if (!widget_)
        return;

    ((TBWindow*)widget_)->SetSettings((WINDOW_SETTINGS) settings);
}

void AWindow::ResizeToFitContent()
{
    if (!widget_)
        return;

    ((TBWindow*)widget_)->ResizeToFitContent();

}

void AWindow::Close()
{
    if (!widget_)
        return;

    ((TBWindow*)widget_)->Close();

}


void AWindow::AddChild(AWidget *child)
{
    if (!widget_ || !child->GetInternalWidget())
        return;

    AWidget::AddChild(child);

    // this is to get proper padding, this may cause problems
    // as this is called from the widget_reader, and not as part of
    // AddChild.  This may also need to be called from other widgets
    // that have padding, etc
    widget_->OnInflateChild(child->GetInternalWidget());

}

AWindow::~AWindow()
{
}

bool AWindow::OnEvent(const tb::TBWidgetEvent &ev)
{
	// user can override the closing of a window
    if (ev.type == EVENT_TYPE_CUSTOM && ev.ref_id == TBIDC("window_close_request"))
    {
        VariantMap eventData;
        eventData[AWidgetEditCanceled::P_WIDGET] = this;
        SendEvent(E_AWIDGETEDITCANCELED, eventData);
        return true;
    }
    return AWidget::OnEvent(ev);
}

void AWindow::SetAxis(UI_AXIS axis)
{
    if (!widget_)
        return;

    widget_->SetAxis((AXIS) axis);
}

void AWindow::SetCloseDelegate ( bool setdel )
{
    if (!widget_)
        return;

    ((TBWindow*)widget_)->SetCloseDelegate (setdel);
}

bool AWindow::GetCloseDelegate ()
{
    if (!widget_)
        return false;

    return ((TBWindow*)widget_)->GetCloseDelegate();
}

#ifdef URHO3D_ANGELSCRIPT
/// Angelscript Register object factory. (semi-manditory)
void AWindow::RegisterObject(Context* context)
{
    context->RegisterFactory<AWindow>(AUI_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(AWidget);
}
#endif

}
