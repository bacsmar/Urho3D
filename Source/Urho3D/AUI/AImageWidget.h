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

#pragma once

#include "../AUI/AWidget.h"

namespace Urho3D
{

//@ASBindGen Class ObjectType=Ref
class URHO3D_API AImageWidget : public AWidget
{
    URHO3D_OBJECT(AImageWidget, AWidget)

public:

    //@ASBindGen Constructor UseUrho3DScriptContext_arg0
    AImageWidget(Context* context, bool createWidget = true);
    virtual ~AImageWidget();

    //@ASBindGen Function
    void SetImage(const String& imagePath);

    //@ASBindGen Function
    int GetImageWidth() const;
    //@ASBindGen Function
    int GetImageHeight() const;

    /// Sprite Feature
    void SetSprite(const String& imagePath);  /// load in xml sprite definition
    bool SpriteMode() const;  /// are we in sprite mode
    int GetSpriteWidth() const; /// returns sprite[0] width 
    int GetSpriteHeight() const; /// returns sprite[0] height 
    int GetNumSprites() const; /// number of sprites loaded
    int GetSpriteSpeed() const; /// returns the sprite animation rate
    void SetSpriteSpeed( int speed);  /// sets the sprite animation rate
    void SetSpriteFrame( int frame);  /// sets the displayed sprite
    int GetSpriteFrame() const;  /// returns the current sprite frame number
    bool IsRunning(); /// is the animation enabled 
    void Begin();  /// begin the animation, may be used instead of SetValue(1)
    void End(); /// stop the animation, may be used instead of SetValue(0)


#ifdef URHO3D_ANGELSCRIPT
    /// Angelscript Register object factory. (semi-manditory)
    static void RegisterObject(Context* context);
#endif

protected:

    virtual bool OnEvent(const tb::TBWidgetEvent &ev) override;

private:

};

}
