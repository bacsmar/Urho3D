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

#include "../IO/Log.h"

#include "AUI.h"
#include "AEvents.h"
#include "ADockWindow.h"

#ifdef URHO3D_ANGELSCRIPT
#include "../Core/Context.h"
#include "../Scene/Serializable.h"
extern const char* AUI_CATEGORY;  /// for angelscript binding
#endif

using namespace tb;

namespace Urho3D
{

/// ADockWindow is the host for AUI* content which has been transferred from the main window.
ADockWindow::ADockWindow(Context* context, bool createWidget, const String& title, AWidget *contentptr, int minwidth, int minheight ) : AWindow(context, false)
{
    if (createWidget)
    {
        tb:TBWidget *contents = contentptr->GetInternalWidget();
        widget_ = new TBDockWindow( title.CString(), contents, minwidth, minheight );
        widget_->SetDelegate(this);
        GetSubsystem<AUI>()->WrapWidget(this, widget_);
    }
}

ADockWindow::~ADockWindow()
{
}

/// ID of the redock widget. If specified, pressing the dock button, will move the content there.
void ADockWindow::SetDockOrigin( String dockid )
{
    if (!widget_)
        return;

   ((TBDockWindow*)widget_)->SetDockOrigin(TBIDC(dockid.CString()));

}

/// This returns a pointer to the docked content.
AWidget *ADockWindow::GetDockContent()
{
    if (!widget_)
        return NULL;

    TBWidget* content = ((TBDockWindow*)widget_)->GetDockContent();

    if (!content)
        return 0;

    AUI* ui = GetSubsystem<AUI>();

    return ui->WrapWidget(content);

}

/// Returns if the ADockWindow contains docked content.
bool ADockWindow::HasDockContent()
{
    if (!widget_)
        return false;

    return ((TBDockWindow*)widget_)->HasDockContent();
}

/// Transfers the dock content to the target widget
void ADockWindow::Dock( AWidget *target )
{
    if (!widget_)
        return;

    if (!target)
        return;

    ((TBDockWindow*)widget_)->Dock( target->GetInternalWidget() );
}

/// Show the ADockWindow, and optional position
void ADockWindow::Show( AWidget *host, int xpos, int ypos )
{
    if (!widget_)
        return;

    if (!host)
        return;

    ((TBDockWindow*)widget_)->Show( host->GetInternalWidget(), xpos, ypos );

}

bool ADockWindow::OnEvent(const tb::TBWidgetEvent &ev)
{
    return AWidget::OnEvent(ev);
}

void ADockWindow::SetAxis(UI_AXIS axis)
{
    if (!widget_)
        return;

    widget_->SetAxis((AXIS) axis);
}

#if URHO3D_ANGELSCRIPT
/// Angelscript Register object factory. (semi-manditory)
void ADockWindow::RegisterObject(Context* context)
{
    context->RegisterFactory<ADockWindow>(AUI_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(AWindow);
}
#endif

}
