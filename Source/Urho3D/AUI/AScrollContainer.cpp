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
#include "AScrollContainer.h"

#ifdef URHO3D_ANGELSCRIPT
#include "../Core/Context.h"
#include "../Scene/Serializable.h"
extern const char* AUI_CATEGORY;  /// for angelscript binding
#endif

using namespace tb;

namespace Urho3D
{

AScrollContainer::AScrollContainer(Context* context, bool createWidget) : AWidget(context, false)
{
    if (createWidget)
    {
        widget_ = new TBScrollContainer();
        widget_->SetDelegate(this);
        GetSubsystem<AUI>()->WrapWidget(this, widget_);
    }
}

AScrollContainer::~AScrollContainer()
{
}

void AScrollContainer::SetScrollMode(UI_SCROLL_MODE mode)
{
    if (!widget_)
        return;

    ((TBScrollContainer*) widget_)->SetScrollMode((tb::SCROLL_MODE) mode);
}

void AScrollContainer::SetAdaptToContentSize(bool adapt)
{
    if (!widget_)
        return;

    ((TBScrollContainer*) widget_)->SetAdaptToContentSize(adapt);
}

bool AScrollContainer::GetAdaptToContentSize()
{
    if (!widget_)
        return false;

    return ((TBScrollContainer*) widget_)->GetAdaptToContentSize();
}

void AScrollContainer::SetAdaptContentSize(bool adapt)
{
    if (!widget_)
        return;

    ((TBScrollContainer*) widget_)->SetAdaptContentSize(adapt);
}

bool AScrollContainer::GetAdaptContentSize()
{
    if (!widget_)
        return false;

    return ((TBScrollContainer*) widget_)->GetAdaptContentSize();
}


UI_SCROLL_MODE AScrollContainer::GetScrollMode()
{
    if (!widget_)
        return UI_SCROLL_MODE_OFF;

    return (UI_SCROLL_MODE) ((TBScrollContainer*) widget_)->GetScrollMode();
}

void AScrollContainer::ScrollTo(int x, int y)
{
    if (!widget_)
        return;

    return ((TBScrollContainer *)widget_)->ScrollTo(x, y);
}

bool AScrollContainer::OnEvent(const tb::TBWidgetEvent &ev)
{
    return AWidget::OnEvent(ev);
}


void AScrollContainer::AddChild(AWidget* child)
{
    if (!widget_ || !child || !child->GetInternalWidget() )
        return;

   ((TBScrollContainer*) widget_)->GetContentRoot()->AddChild(child->GetInternalWidget());
}

#ifdef URHO3D_ANGELSCRIPT
/// Angelscript Register object factory. (semi-manditory)
void AScrollContainer::RegisterObject(Context* context)
{
    context->RegisterFactory<AScrollContainer>(AUI_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(AWidget);
}
#endif

}
