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
#include <TurboBadger/tb_layout.h>

#include "AUI.h"
#include "AEvents.h"
#include "AWidget.h"
#include "ALayout.h"

#ifdef URHO3D_ANGELSCRIPT
#include "../Core/Context.h"
#include "../Scene/Serializable.h"
extern const char* AUI_CATEGORY;  /// for angelscript binding
#endif

using namespace tb;

namespace Urho3D
{

ALayoutParams::ALayoutParams(Context* context) : Object(context)
{
}

ALayoutParams::~ALayoutParams()
{
}

#if URHO3D_ANGELSCRIPT
/// Angelscript Register object factory. (semi-manditory)
void ALayoutParams::RegisterObject(Context* context)
{
    context->RegisterFactory<ALayoutParams>(AUI_CATEGORY);
}
#endif


ALayout::ALayout(Context* context, UI_AXIS axis, bool createWidget) : AWidget(context, false)
{
    if (createWidget)
    {
        widget_ = new TBLayout();
        widget_->SetDelegate(this);
        widget_->SetGravity(WIDGET_GRAVITY_ALL);
        widget_->SetAxis((AXIS) axis);
        GetSubsystem<AUI>()->WrapWidget(this, widget_);
    }
}

ALayout::~ALayout()
{
}

void ALayout::SetSpacing(int spacing)
{
    if (!widget_)
        return;

    ((tb::TBLayout*)widget_)->SetSpacing(spacing);
}

void ALayout::SetLayoutPosition(UI_LAYOUT_POSITION position)
{
    if (!widget_)
        return;

    ((tb::TBLayout*)widget_)->SetLayoutPosition( (LAYOUT_POSITION) position);
}

void ALayout::SetLayoutDistributionPosition(UI_LAYOUT_DISTRIBUTION_POSITION distribution_pos)
{
    if (!widget_)
        return;

    ((tb::TBLayout*)widget_)->SetLayoutDistributionPosition( (LAYOUT_DISTRIBUTION_POSITION) distribution_pos);

}

void ALayout::SetLayoutSize(UI_LAYOUT_SIZE size)
{
    if (!widget_)
        return;

    ((tb::TBLayout*)widget_)->SetLayoutSize((LAYOUT_SIZE) size);

}

void ALayout::SetAxis(UI_AXIS axis)
{
    if (!widget_)
        return;

    ((tb::TBLayout*)widget_)->SetAxis((AXIS) axis);
}

void ALayout::SetLayoutDistribution(UI_LAYOUT_DISTRIBUTION distribution)
{
    if (!widget_)
        return;

    ((tb::TBLayout*)widget_)->SetLayoutDistribution((LAYOUT_DISTRIBUTION) distribution);
}


bool ALayout::OnEvent(const tb::TBWidgetEvent &ev)
{
    return AWidget::OnEvent(ev);
}

/// one step to configure the main 5 fields in a ALayout
void ALayout::SetLayoutConfig ( const String &settings )
{
    if (!widget_)
        return;

    ((tb::TBLayout*)widget_)->SetLayoutConfig(settings.CString());
}

String ALayout::GetLayoutConfig ()  /// return the state of the Layout
{
    if (!widget_)
        return String::EMPTY;

    return ((tb::TBLayout*)widget_)->GetLayoutConfig().CStr();

}

#if URHO3D_ANGELSCRIPT
/// Angelscript Register object factory. (semi-manditory)
void ALayout::RegisterObject(Context* context)
{
    context->RegisterFactory<ALayout>(AUI_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(AWidget);
}
#endif

}
