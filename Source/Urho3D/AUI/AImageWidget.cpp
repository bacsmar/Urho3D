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
#include <TurboBadger/image/tb_image_widget.h>

#include "../Precompiled.h"
#include "../IO/Log.h"

#include "../AUI/AUI.h"
#include "../AUI/AEvents.h"
#include "../AUI/AWidget.h"
#include "../AUI/AImageWidget.h"

#ifdef URHO3D_ANGELSCRIPT
#include "../Core/Context.h"
#include "../Scene/Serializable.h"
extern const char* AUI_CATEGORY;  /// for angelscript binding
#endif

using namespace tb;

namespace Urho3D
{

AImageWidget::AImageWidget(Context* context, bool createWidget) : AWidget(context, false)
{
    if (createWidget)
    {
        widget_ = new TBImageWidget();
        widget_->SetDelegate(this);
        GetSubsystem<AUI>()->WrapWidget(this, widget_);
    }
}

AImageWidget::~AImageWidget()
{
}

int AImageWidget::GetImageWidth() const
{
    if (!widget_)
        return 0;

    return ((TBImageWidget*) widget_)->GetImageWidth();

}

int AImageWidget::GetImageHeight() const
{
    if (!widget_)
        return 0;

    return ((TBImageWidget*) widget_)->GetImageHeight();

}

void AImageWidget::SetImage(const String& imagePath)
{
    if (!widget_)
        return;

    ((TBImageWidget*) widget_)->SetImage(imagePath.CString());

}

bool AImageWidget::OnEvent(const tb::TBWidgetEvent &ev)
{
    return AWidget::OnEvent(ev);
}

/// Sprite Feature

void AImageWidget::SetSprite(const String& imagePath)  /// load in xml sprite definition
{
    if (!widget_)
        return;

    ((TBImageWidget*) widget_)->SetSprite(imagePath.CString());
}

bool AImageWidget::SpriteMode() const  /// are we in sprite mode
{
    if (!widget_)
        return 0;

    return ((TBImageWidget*) widget_)->SpriteMode();
}

int AImageWidget::GetSpriteWidth() const /// returns sprite[0] width 
{
    if (!widget_)
        return 0;

    return ((TBImageWidget*) widget_)->GetSpriteWidth();
}

int AImageWidget::GetSpriteHeight() const /// returns sprite[0] height 
{
    if (!widget_)
        return 0;

    return ((TBImageWidget*) widget_)->GetSpriteHeight();
}

int AImageWidget::GetNumSprites() const /// number of sprites loaded
{
    if (!widget_)
        return 0;

    return ((TBImageWidget*) widget_)->GetNumSprites();
}

int AImageWidget::GetSpriteSpeed() const /// returns the sprite animation rate
{
    if (!widget_)
        return 0;

    return ((TBImageWidget*) widget_)->GetSpriteSpeed();
}

void AImageWidget::SetSpriteSpeed( int speed)  /// sets the sprite animation rate
{
    if (!widget_)
        return;

    ((TBImageWidget*) widget_)->SetSpriteSpeed(speed);
}

void AImageWidget::SetSpriteFrame(int frame)  /// sets the displayed sprite frame
{
    if (!widget_)
        return;

    ((TBImageWidget*) widget_)->SetSpriteFrame(frame);
}

int AImageWidget::GetSpriteFrame() const /// returns the current sprite frame
{
    if (!widget_)
        return 0;

    return ((TBImageWidget*) widget_)->GetSpriteFrame();
}

bool AImageWidget::IsRunning() /// is the animation enabled 
{
    if (!widget_)
        return 0;

    return ((TBImageWidget*) widget_)->IsRunning();
}

void AImageWidget::Begin()  /// begin the animation, may be used instead of SetValue(1)
{
    if (!widget_)
        return;

    ((TBImageWidget*) widget_)->Begin();
}

void AImageWidget::End() /// stop the animation, may be used instead of SetValue(0)
{
    if (!widget_)
        return;

    ((TBImageWidget*) widget_)->End();
}


#if URHO3D_ANGELSCRIPT
/// Angelscript Register object factory. (semi-manditory)
void AImageWidget::RegisterObject(Context* context)
{
    context->RegisterFactory<AImageWidget>(AUI_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(AWidget);
}
#endif

}
