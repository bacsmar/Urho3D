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

#include <TurboBadger/tb_widgets.h>
#include <TurboBadger/tb_widgets_common.h>
#include <TurboBadger/tb_atomic_widgets.h>

#include "../Precompiled.h"

#include "../AUI/AEvents.h"
#include "../AUI/AUI.h"
#include "../AUI/ABargraph.h"

#ifdef URHO3D_ANGELSCRIPT
#include "../Core/Context.h"
extern const char* AUI_CATEGORY;  /// for angelscript binding
#endif

using namespace tb;

namespace Urho3D
{

ABargraph::ABargraph(Context* context, bool createWidget) : AWidget(context, false)
{
    if (createWidget)
    {
        widget_ = new TBBarGraph();
        widget_->SetDelegate(this);
        GetSubsystem<AUI>()->WrapWidget(this, widget_);
    }
}

ABargraph::~ABargraph()
{
}

void ABargraph::SetColor(Color color) 
{

    if (!widget_)
          return;

    ((TBBarGraph*)widget_)->SetColor(color.r_ * 255, color.g_ * 255, color.b_ * 255, color.a_ * 255);
}

bool ABargraph::OnEvent(const tb::TBWidgetEvent &ev)
{
    return AWidget::OnEvent(ev);
}

#if URHO3D_ANGELSCRIPT
/// Angelscript Register object factory. (semi-manditory)
void ABargraph::RegisterObject(Context* context)
{
    context->RegisterFactory<ABargraph>(AUI_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(AWidget);
}
#endif


}
