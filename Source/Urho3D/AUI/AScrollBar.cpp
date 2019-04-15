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

#include <../IO/Log.h>

#include "AEvents.h"
#include "AUI.h"
#include "ALayout.h"
#include "AScrollBar.h"

#ifdef URHO3D_ANGELSCRIPT
#include "../Core/Context.h"
#include "../Scene/Serializable.h"
extern const char* AUI_CATEGORY;  /// for angelscript binding
#endif

using namespace tb;

namespace Urho3D
{

AScrollBar::AScrollBar(Context* context, bool createWidget) : AWidget(context, false)
{
    if (createWidget)
    {
        widget_ = new TBScrollBar();
        widget_->SetDelegate(this);
        GetSubsystem<AUI>()->WrapWidget(this, widget_);
    }
}

AScrollBar::~AScrollBar()
{

}

void AScrollBar::SetLimits(double minimum, double maximum, double visible)
{
    if (!widget_)
        return;
    ((TBScrollBar*) widget_)->SetLimits(minimum, maximum, visible);
}

double AScrollBar::GetMinValue() const
{
    if (!widget_)
        return 0.0;

   return ((TBScrollBar*) widget_)->GetMinValue();
}

double AScrollBar::GetMaxValue() const
{
    if (!widget_)
        return 0.0;

   return ((TBScrollBar*) widget_)->GetMaxValue();
}

double AScrollBar::GetVisible() const
{
    if (!widget_)
        return 0.0;

   return ((TBScrollBar*) widget_)->GetVisible();
}

bool AScrollBar::OnEvent(const tb::TBWidgetEvent &ev)
{
    if (ev.type == EVENT_TYPE_CUSTOM && ev.ref_id == TBIDC("edit_complete"))
    {
        VariantMap eventData;
        eventData[AWidgetEditComplete::P_WIDGET] = this;
        SendEvent(E_AWIDGETEDITCOMPLETE, eventData);

        return true;
    }
    return AWidget::OnEvent(ev);
}

#ifdef URHO3D_ANGELSCRIPT
/// Angelscript Register object factory. (semi-manditory)
void AScrollBar::RegisterObject(Context* context)
{
    context->RegisterFactory<AScrollBar>(AUI_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(AWidget);
}
#endif

}
