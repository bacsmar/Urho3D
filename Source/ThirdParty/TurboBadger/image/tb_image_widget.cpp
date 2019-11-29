// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "image/tb_image_widget.h"
#include "tb_widgets_reader.h"
#include "tb_node_tree.h"
// ATOMIC BEGIN
#include <stdio.h>
#include <libgen.h>
//ATOMIC END

#ifdef TB_IMAGE

namespace tb {

PreferredSize TBImageWidget::OnCalculatePreferredContentSize(const SizeConstraints &constraints)
{
    if (SpriteMode()) return PreferredSize(GetSpriteWidth(), GetSpriteHeight());
    return PreferredSize(m_image.Width(), m_image.Height());
}

void TBImageWidget::OnPaint(const PaintProps &paint_props)
{
    if (TBBitmapFragment *fragment = m_image.GetBitmap())
    {
        if (SpriteMode())
        {
            TBRect local_frame = m_sprites.GetRect(m_frame);
            g_renderer->DrawBitmap(GetPaddingRect(), local_frame, fragment);
        }
        else
            g_renderer->DrawBitmap(GetPaddingRect(), TBRect(0, 0, m_image.Width(), m_image.Height()), fragment);
    }
}

void TBImageWidget::SetImage(const char *filename) 
{ 
    End();
    m_sprites.RemoveAll(false);
    m_image = g_image_manager->GetImage(filename);
}

// ATOMIC BEGIN

/// Loads file.xml to switch from Image mode to Sprite mode, until the next item is loaded.
void TBImageWidget::SetSprite(const char *filename)
{
    m_sprites.RemoveAll(false);  // clear sprite rectangle cache

    if ( filename == NULL ) return;
    FILE* xmlfile = fopen(filename, "r"); // ugh, xml. lets just read the file without an xml subsystem.
    if ( xmlfile )
    {
        char line[1024]="", img[1024]="", work[1024]="", tag[256]="", imgpath[1024]="";
        int frames=0, xx=0, yy=0, ww=0, hh=0, fw=0, fh=0, ox=0, oy=0;
        char *dirc = strdup(filename);
        strcpy ( imgpath, dirname(dirc)); // get the path
        while (fgets(line, sizeof(line), xmlfile)) // read line by line
        {
            sscanf( line, "%s *", work ); // get the 1st token in line ...
            if ( strcmp( work, "<TextureAtlas" ) == 0 )  // its the TextureAtlas
            {
                sscanf( line, "%s imagePath=\"%49[^\"]\">", work, img );
                strcat (imgpath, "/" );
                strcat (imgpath, img );
                SetImage( imgpath ); // and load it in...
            }
            if ( strcmp( work, "<SubTexture" ) == 0 ) // its a SubTexture
            {
                sscanf( line, "%s name=\"%49[^\"]\" x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" frameWidth=\"%d\" frameHeight=\"%d\" offsetX=\"%d\" offsetY=\"%d\" />", work, tag, &xx,&yy,&ww,&hh,&fw,&fh,&ox,&oy );
                TBRect myrect( xx, yy, ww, hh );
                m_sprites.AddRect(myrect,false);
                frames++;
            }
        }
        fclose(xmlfile);
    }
}

/// returns true if in sprite mode, otherwise it is in the default Image mode
bool TBImageWidget::SpriteMode() const
{
    return (!m_sprites.IsEmpty()); // determined if we loaded any sprite frames.
}

/// returns the sprite width, it takes this from sprite[0], and assumes all sprites have the same dimensions.
int32 TBImageWidget::GetSpriteWidth() const
{
    if (SpriteMode())
        return m_sprites.GetRect(0).w;
    return 0;
}

/// returns the sprite height
int32 TBImageWidget::GetSpriteHeight() const
{
    if (SpriteMode())
        return m_sprites.GetRect(0).h;
    return 0;
}

/// returns the number of sprites loaded
int32 TBImageWidget::GetNumSprites() const
{
    if (SpriteMode())
        return m_sprites.GetNumRects();
    return 0;
}

/// returns the current sprite animation frame rate
int32 TBImageWidget::GetSpriteSpeed() const
{
    return m_sprite_speed;
}

/// sets the current sprite animation frame rate    
void TBImageWidget::SetSpriteSpeed( int32 speed )
{
    m_sprite_speed = speed;
}

/// sets the sprite animation frame number, so when stopped, can change the displayed sprite
void TBImageWidget::SetSpriteFrame( int32 frame )
{
    if ( SpriteMode() && frame >= 0 && frame < m_sprites.GetNumRects() )
    {
        m_frame = frame;  // set the frame number
        Invalidate();     // make it draw
    }
}

/// returns the current sprites frame
int32 TBImageWidget::GetSpriteFrame() const
{
    return m_frame;
}

/// Setting the value to 1 will start the sprite. Setting it to 0 will stop it. Stole this from TBProgressWidget
void TBImageWidget::SetValue(int value)
{
    if (value == m_value)
        return;
    InvalidateSkinStates();
    assert(value >= 0); // If this happens, you probably have unballanced Begin/End calls.
    m_value = value;
    if (value > 0) // Start animation
    {
        if ( SpriteMode() )  // ONLY in sprite mode.
        {
            if (!GetMessageByID(TBID(1)))
            {
                m_frame = 0;
                PostMessageDelayed(TBID(1), nullptr, m_sprite_speed);
            }
        }
    }
    else // Stop animation
    {
        if ( SpriteMode() )  // ONLY in sprite mode.
        {
            if (TBMessage *msg = GetMessageByID(TBID(1)))
                DeleteMessage(msg);
        }
    }
}

/// essential part of animation sequencing. Stole this from TBProgressWidget 
// FIX: Make it post messages only if visible -- did it.
void TBImageWidget::OnMessageReceived(TBMessage *msg)
{
    if ( SpriteMode() && GetAmIVisible() > 0 ) // ONLY in sprite mode and if visible
    {
        m_frame++;
        if ( m_frame >= m_sprites.GetNumRects() ) // auto-loop
            m_frame = 0;

        Invalidate();
        // Keep animation running
        PostMessageDelayed(TBID(1), nullptr, m_sprite_speed);
    }
}

// one of the few functions called when tb visibility state changes.
void TBImageWidget::OnProcessStates() 
{ 
    if ( SpriteMode() )  // ONLY in sprite mode.
    {
        bool gvc = GetVisibilityCombined(); // because this such a heavy call :(
        if ( gvc == true && GetAmIVisible() == 0 ) // un-suspend messages, we are seen!
        {
            SetAmIVisible();
            if ( GetValue() > 0 && !GetMessageByID(TBID(1))) // and start the messages again
            {
                PostMessageDelayed(TBID(1), nullptr, m_sprite_speed);
            }
        }
        else if ( gvc == false && GetAmIVisible() == 1 )  // we've gone dark, if we were animating, stop it.
        {
            ClearAmIVisible();
        }
    }
}


//ATOMIC END


}; // namespace tb

#endif // TB_IMAGE
