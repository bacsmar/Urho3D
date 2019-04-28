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

#include "../Precompiled.h"
#include "../IO/Log.h"
#include "../IO/FileSystem.h"

#include "../AUI/AEvents.h"
#include "../AUI/AUI.h"
#include "../AUI/AButton.h"

#ifdef URHO3D_ANGELSCRIPT
#include "../Core/Context.h"
extern const char* AUI_CATEGORY;  /// for angelscript binding
#endif

using namespace tb;

namespace Urho3D
{

AButton::AButton(Context* context, bool createWidget) : AWidget(context, false),
    emulationButton_(-1),
    urlEnabled_(true)
{
    if (createWidget)
    {
        widget_ = new TBButton();
        widget_->SetDelegate(this);
        GetSubsystem<AUI>()->WrapWidget(this, widget_);
    }
}

AButton::~AButton()
{

}

void AButton::SetSqueezable(bool value)
{
    if (!widget_)
        return;

    ((TBButton*)widget_)->SetSqueezable(value);
}

void AButton::SetToggleMode(bool toggle)
{
    if (!widget_)
        return;

    ((TBButton*)widget_)->SetToggleMode(toggle);

}

bool AButton::GetToggleMode() const
{
    if (!widget_)
        return false;

    return ((TBButton*)widget_)->GetToggleMode();
}

void AButton::SetEmulationButton(int emulationButton)
{
    emulationButton_ = emulationButton;
}

bool AButton::OnEvent(const tb::TBWidgetEvent &ev)
{
    if (ev.type == EVENT_TYPE_CLICK)
    {
        if (urlEnabled_)
        {
            // First see if we have a url specified, if not and the button uses the TBButton.link skin try text
            String url = GetURL();
            String skinname = widget_->GetSkinBgElement() ? widget_->GetSkinBgElement()->name.CStr() : String::EMPTY;
            if (!url.Length() && skinname == "TBButton.link")
            {
                String text = GetText();

                if (text.StartsWith("http://") || text.StartsWith("https://") || text.StartsWith("file://"))
                {
                    url = text;
                }
            }

            if (url.Length())
            {
                FileSystem* fileSystem = GetSubsystem<FileSystem>();
                fileSystem->SystemOpen(url);
            }
        }
    }
    /// ATOMIC adds Input functions SimulateButtonDown SimulateButtonUp
    if (ev.type == EVENT_TYPE_POINTER_DOWN && emulationButton_ >= 0)
    {
        GetSubsystem<Input>()->SimulateButtonDown(emulationButton_);
    }
    if (ev.type == EVENT_TYPE_POINTER_UP && emulationButton_ >= 0)
    {
        GetSubsystem<Input>()->SimulateButtonUp(emulationButton_);
    }
    return AWidget::OnEvent(ev);
}

/// Set the URL which is opened when this button is clicked, this overrides the text attr
void AButton::SetURL (const String& url)
{
    if (!widget_)
        return;

    ((TBButton*)widget_)->SetURL(url.CString());

}

/// Get the URL which is opened when this button is clicked
String AButton::GetURL()
{
    if (!widget_)
        return String::EMPTY;

    return ((TBButton*)widget_)->GetURL().CStr();

}

#if URHO3D_ANGELSCRIPT
/// Angelscript Register object factory. (semi-manditory)
void AButton::RegisterObject(Context* context)
{
    context->RegisterFactory<AButton>(AUI_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(AWidget);
}
#endif

}
