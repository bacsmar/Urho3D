// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================
// ATOMIC BEGINEND displays animated sprite ( via Urho3D SpritePacker ) 2019, JimMarlowe

#ifndef TB_IMAGE_WIDGET_H
#define TB_IMAGE_WIDGET_H

#include "../tb_widgets.h"
#include "../tb_msg.h"

#ifdef TB_IMAGE

#define TB_DEFAULT_SPEED 250

#include "tb_image_manager.h"

namespace tb {

/** TBImageWidget is a widget showing a image loaded by TBImageManager,
    constrained in size to its skin.
    If you need to show a image from the skin, you can use TBSkinImage. */

class TBImageWidget : public TBWidget, protected TBMessageHandler
{
public:
    // For safe typecasting
    TBOBJECT_SUBCLASS(TBImageWidget, TBWidget);

    TBImageWidget() : TBWidget()
    , m_value(0)
    , m_frame(0)
    , m_sprite_speed(TB_DEFAULT_SPEED)
    , m_sprites() 
    , m_iamvisible(0)
    {}

    void SetImage(const TBImage &image) { m_image = image; }
    void SetImage(const char *filename);

    int32 GetImageWidth() { return m_image.Width(); }
    int32 GetImageHeight() { return m_image.Height(); }

    virtual PreferredSize OnCalculatePreferredContentSize(const SizeConstraints &constraints);

    virtual void OnInflate(const INFLATE_INFO &info);
    virtual void OnPaint(const PaintProps &paint_props);
    
    // ATOMIC BEGIN

    /// returns true if in sprite mode, otherwise it is in the default Image mode
    bool SpriteMode() const;
    /// Loads file.xml to switch from Image mode to Sprite mode, until the next item is loaded.
    void SetSprite(const char *filename); 
    /// returns the sprite width, it takes this from sprite[0], and assumes all sprites have the same dimensions.
    int32 GetSpriteWidth() const; 
    /// returns the sprite height
    int32 GetSpriteHeight() const;
    /// returns the number of sprites loaded
    int32 GetNumSprites() const;
    /// returns the current sprite animation frame rate
    int32 GetSpriteSpeed() const;
    /// sets the current sprite animation frame rate    
    void SetSpriteSpeed( int32 speed );
    /// sets the sprite animation frame number, for single stepping
    void SetSpriteFrame( int32 frame );
    /// returns the current sprites frame
    int32 GetSpriteFrame() const;

    bool IsRunning() { return m_value > 0; } /** Return true if the animation is running. from TBProgressSpinner */
    void Begin() { SetValue(GetValue() + 1); } /** Begin/End are used to start or stop the animation in a incremental way. */
    void End() { SetValue(GetValue() - 1); } /**If several tasks may activate the same spinner, calling Begin/End instead
        of using SetValue, so it will keep running as long as any source wants it to. */       
    virtual void SetValue(int value); /** Setting the value to 1 will start the sprite. Setting it to 0 will stop it. */
    virtual int GetValue() { return m_value; } /** returns the animation control state */

    virtual void OnMessageReceived(TBMessage *msg); ///< essential part of animation sequencing
    virtual void OnProcessStates();  // FIX: Make it post messages only if visible(ish)

    // ATOMIC END

private:
    TBImage m_image;
    
    void SetAmIVisible() { m_iamvisible = 1; } 
    void ClearAmIVisible() { m_iamvisible = 0; }
    int32 GetAmIVisible() const { return m_iamvisible; }

    // ATOMIC BEGIN
    int32 m_value;  ///<  controls if sprites are animating
    int32 m_frame;  ///< current frame of sprite animation
    int32 m_sprite_speed; ///< How fast should the sprite animation animate.
    TBRegion m_sprites; ///< dynamic collection of TBRects for the sprite definitions in the image
    int32 m_iamvisible; ///< state to control message generation if widget not visible.
    // ATOMIC END

};

}; // namespace tb

#endif // TB_IMAGE
#endif // TB_IMAGE_WIDGET_H
