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

#include "../Precompiled.h"
#include "../IO/Log.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/VertexBuffer.h"
#include "../Graphics/Texture2D.h"
#include "../Input/InputEvents.h"

#include "../AUI/AUI.h"
#include "../AUI/AView.h"
#include "../AUI/ARenderer.h"

#ifdef URHO3D_ANGELSCRIPT
#include "../Core/Context.h"
#include "../Scene/Serializable.h"
extern const char* AUI_CATEGORY;  /// for angelscript binding
#endif

using namespace tb;

namespace Urho3D
{

AView::AView(Context* context) : AWidget(context, false),
    autoFocus_(true),
    mouseEnabled_(true),
    keyboardEnabled_(true)
{
    graphics_ = GetSubsystem<Graphics>();
    assert(graphics_.NotNull());
    assert(graphics_->IsInitialized());

    ui_ = GetSubsystem<AUI>();
    assert(ui_.NotNull());

    renderer_ = ui_->GetRenderer();

    widget_ = new TBWidget();
    widget_->SetDelegate(this);

    // Set gravity all so we resize correctly
    widget_->SetGravity(WIDGET_GRAVITY_ALL);

    ui_->WrapWidget(this, widget_);

    // Set initial size for view
    TBRect rect = ui_->GetRootWidget()->GetRect();
    widget_->SetSize(rect.w, rect.h);

    vertexBuffer_ = new VertexBuffer(context_);

    ui_->AddAView(this);
}

AView::~AView()
{
}

void AView::SetFocus()
{
    if (ui_.Null() || ui_->GetFocusedView() == this)
    {
        return;
    }

    if (ui_->GetFocusedView())
    {
        ui_->GetFocusedView()->ResignFocus();
    }

    AWidget::SetFocus();

    ui_->SetFocusedView(this);
}

bool AView::GetFocus() const
{
    if (ui_.Null())
    {
        return false;
    }

    return ui_->GetFocusedView() == this;
}

void AView::BecomeFocused()
{
    widget_->SetZ(WIDGET_Z_TOP);

    SubscribeToEvent(E_MOUSEBUTTONDOWN, URHO3D_HANDLER(AView, HandleMouseButtonDown));
    SubscribeToEvent(E_MOUSEBUTTONUP, URHO3D_HANDLER(AView, HandleMouseButtonUp));
    SubscribeToEvent(E_MOUSEMOVE, URHO3D_HANDLER(AView, HandleMouseMove));
    SubscribeToEvent(E_MOUSEWHEEL, URHO3D_HANDLER(AView, HandleMouseWheel));
    SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(AView, HandleKeyDown));
    SubscribeToEvent(E_KEYUP, URHO3D_HANDLER(AView, HandleKeyUp));
    SubscribeToEvent(E_TEXTINPUT, URHO3D_HANDLER(AView, HandleTextInput));

    SubscribeToEvent(E_TOUCHBEGIN, URHO3D_HANDLER(AView, HandleTouchBegin));
    SubscribeToEvent(E_TOUCHEND, URHO3D_HANDLER(AView, HandleTouchEnd));
    SubscribeToEvent(E_TOUCHMOVE, URHO3D_HANDLER(AView, HandleTouchMove));

}

void AView::ResignFocus()
{        
    if (ui_.Null() || ui_->GetFocusedView() != this)
    {
        return;
    }

    widget_->SetZ(WIDGET_Z_BOTTOM);

    UnsubscribeFromEvent(E_MOUSEBUTTONDOWN);
    UnsubscribeFromEvent(E_MOUSEBUTTONUP);
    UnsubscribeFromEvent(E_MOUSEMOVE);
    UnsubscribeFromEvent(E_MOUSEWHEEL);
    UnsubscribeFromEvent(E_KEYDOWN);
    UnsubscribeFromEvent(E_KEYUP);
    UnsubscribeFromEvent(E_TEXTINPUT);

    UnsubscribeFromEvent(E_TOUCHBEGIN);
    UnsubscribeFromEvent(E_TOUCHEND);
    UnsubscribeFromEvent(E_TOUCHMOVE);

    ui_->SetFocusedView(0);

}

void AView::Remove()
{
    ResignFocus();

    if (ui_.NotNull())
    {
        ui_->RemoveAView(this);
    }

    AWidget::Remove();
}

bool AView::SetRenderToTexture(bool value, const int width, const int height)
{
    if (!value && renderTexture_.NotNull())
    {
        renderTexture_ = 0;
    }
    else if (value && renderTexture_.Null())
    {
        renderTexture_ = new Texture2D(context_);
        SetAutoFocus(false);
    }

    return SetSize(width, height);
}

bool AView::SetSize(int width, int height)
{
    if (!widget_)
        return false;

    if (width < UIVIEW_MIN_TEXTURE_SIZE || width > UIVIEW_MAX_TEXTURE_SIZE ||
        height < UIVIEW_MIN_TEXTURE_SIZE || height > UIVIEW_MAX_TEXTURE_SIZE)
    {
        URHO3D_LOGERROR("AView::SetSize() - Attempting to set invalid size, failed");
        return false;
    }

    if (renderTexture_.NotNull())
    {
        renderTexture_->SetSize(width, height, graphics_->GetRGBAFormat(), TEXTURE_RENDERTARGET);
        renderTexture_->SetFilterMode(FILTER_BILINEAR);
        renderTexture_->SetAddressMode(COORD_U, ADDRESS_CLAMP);
        renderTexture_->SetAddressMode(COORD_V, ADDRESS_CLAMP);
        renderTexture_->SetNumLevels(1); // No mipmaps
        renderTexture_->GetRenderSurface()->SetUpdateMode(SURFACE_MANUALUPDATE);

    }

    return AWidget::SetSize(width, height);
}

void AView::Render(VertexBuffer* buffer, const PODVector<ABatch>& batches, unsigned batchStart, unsigned batchEnd)
{

    if (batches.Empty())
    {
        graphics_->ResetRenderTargets();
        return;
    }

    IntVector2 size;

    if (renderTexture_)
    {
        size.x_ = renderTexture_->GetWidth();
        size.y_ = renderTexture_->GetHeight();
    }
    else
    {
        size.x_ = graphics_->GetWidth();
        size.y_ = graphics_->GetHeight();
    }

    bool scissorEnabled = true;
    IntRect rect(0, 0, size.x_, size.y_);
    Vector2 invScreenSize(1.0f / (float)size.x_, 1.0f / (float)size.y_);
    Vector2 scale(2.0f * invScreenSize.x_, -2.0f * invScreenSize.y_);
    Vector2 offset(-1.0f, 1.0f);

    // On OpenGL, flip the projection if rendering to a texture so that the texture can be addressed in the same way
    // as a render texture produced on Direct3D
#ifdef URHO3D_OPENGL
    if (renderTexture_)
    {
        // ATOMIC ISSUE: https://github.com/AtomicGameEngine/AtomicGameEngine/issues/1581
        // this needs to be fixed, scissors can't be disabled
        // and there is a flip to D3D in SetScissorTest        
        scissorEnabled = false;
        offset.y_ = -offset.y_;
        scale.y_  = -scale.y_;
    }
#endif

    Matrix4 projection(Matrix4::IDENTITY);
    projection.m00_ = scale.x_;
    projection.m03_ = offset.x_;
    projection.m11_ = scale.y_;
    projection.m13_ = offset.y_;
    projection.m22_ = 1.0f;
    projection.m23_ = 0.0f;
    projection.m33_ = 1.0f;

    graphics_->ClearParameterSources();
    graphics_->SetColorWrite(true);
    graphics_->SetCullMode(CULL_NONE);
    graphics_->SetDepthTest(CMP_ALWAYS);
    graphics_->SetDepthWrite(false);
    graphics_->SetFillMode(FILL_SOLID);
    graphics_->SetStencilTest(false);

    graphics_->ResetRenderTargets();

    if (renderTexture_)
    {
        graphics_->SetRenderTarget(0, renderTexture_->GetRenderSurface());
    }

    graphics_->SetViewport(rect);

    graphics_->SetVertexBuffer(buffer);

    ShaderVariation* noTextureVS = graphics_->GetShader(VS, "Basic", "VERTEXCOLOR");
    ShaderVariation* diffTextureVS = graphics_->GetShader(VS, "Basic", "DIFFMAP VERTEXCOLOR");
    ShaderVariation* noTexturePS = graphics_->GetShader(PS, "Basic", "VERTEXCOLOR");
    ShaderVariation* diffTexturePS = graphics_->GetShader(PS, "Basic", "DIFFMAP VERTEXCOLOR");
    ShaderVariation* diffMaskTexturePS = graphics_->GetShader(PS, "Basic", "DIFFMAP ALPHAMASK VERTEXCOLOR");
    ShaderVariation* alphaTexturePS = graphics_->GetShader(PS, "Basic", "ALPHAMAP VERTEXCOLOR");

    unsigned alphaFormat = Graphics::GetAlphaFormat();

    if (renderTexture_)
    {
        graphics_->Clear(CLEAR_COLOR);
    }

    for (unsigned i = batchStart; i < batchEnd; ++i)
    {
        const ABatch& batch = batches[i];
        if (batch.vertexStart_ == batch.vertexEnd_)
            continue;

        ShaderVariation* ps;
        ShaderVariation* vs;

        if (!batch.texture_)
        {
            ps = noTexturePS;
            vs = noTextureVS;
        }
        else
        {
            // If texture contains only an alpha channel, use alpha shader (for fonts)
            vs = diffTextureVS;

            if (batch.texture_->GetFormat() == alphaFormat)
                ps = alphaTexturePS;
            else if (batch.blendMode_ != BLEND_ALPHA && batch.blendMode_ != BLEND_ADDALPHA && batch.blendMode_ != BLEND_PREMULALPHA)
                ps = diffMaskTexturePS;
            else
                ps = diffTexturePS;
        }

        graphics_->SetShaders(vs, ps);
        if (graphics_->NeedParameterUpdate(SP_OBJECT, this))
            graphics_->SetShaderParameter(VSP_MODEL, Matrix3x4::IDENTITY);
        if (graphics_->NeedParameterUpdate(SP_CAMERA, this))
            graphics_->SetShaderParameter(VSP_VIEWPROJ, projection);
        if (graphics_->NeedParameterUpdate(SP_MATERIAL, this))
            graphics_->SetShaderParameter(PSP_MATDIFFCOLOR, Color(1.0f, 1.0f, 1.0f, 1.0f));

        graphics_->SetBlendMode(batch.blendMode_);
        graphics_->SetScissorTest(scissorEnabled, batch.scissor_);
        graphics_->SetTexture(0, batch.texture_);
        graphics_->Draw(TRIANGLE_LIST, batch.vertexStart_ / AUI_VERTEX_SIZE, (batch.vertexEnd_ - batch.vertexStart_) /
            AUI_VERTEX_SIZE);
    }

    if (renderTexture_)
    {
        graphics_->ResetRenderTargets();
    }
}

void AView::SetVertexData(VertexBuffer* dest, const PODVector<float>& vertexData)
{
    if (vertexData.Empty())
        return;

    // Update quad geometry into the vertex buffer
    // Resize the vertex buffer first if too small or much too large
    unsigned numVertices = vertexData.Size() / AUI_VERTEX_SIZE;
    if (dest->GetVertexCount() < numVertices || dest->GetVertexCount() > numVertices * 2)
        dest->SetSize(numVertices, MASK_POSITION | MASK_COLOR | MASK_TEXCOORD1, true);

    dest->SetData(&vertexData[0]);
}


void AView::Render(bool resetRenderTargets)
{
    SetVertexData(vertexBuffer_, vertexData_);
    Render(vertexBuffer_, batches_, 0, batches_.Size());
}

void AView::UpdateUIBatches()
{
    batches_.Clear();
    vertexData_.Clear();

    tb::TBRect rect = widget_->GetRect();
    IntRect currentScissor = IntRect(0, 0, rect.w, rect.h);
    GetBatches(batches_, vertexData_, currentScissor);
}

void AView::GetBatches(PODVector<ABatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor)
{
    tb::g_renderer->BeginPaint(currentScissor.Width(), currentScissor.Height());

    renderer_->currentScissor_ = currentScissor;
    renderer_->batches_ = &batches;
    renderer_->vertexData_ = &vertexData;
    widget_->InvokePaint(tb::TBWidget::PaintProps());

    tb::g_renderer->EndPaint();
}

void AView::SubmitBatchVertexData(Texture* texture, const PODVector<float>& vertexData)
{
    ABatch b(BLEND_ALPHA , renderer_->currentScissor_, texture, &vertexData_);

    unsigned begin = b.vertexData_->Size();
    b.vertexData_->Resize(begin + vertexData.Size());
    float* dest = &(b.vertexData_->At(begin));
    b.vertexEnd_ = b.vertexData_->Size();

    for (unsigned i = 0; i < vertexData.Size(); i++, dest++)
    {
        *dest = vertexData[i];
    }

    ABatch::AddOrMerge(b, batches_);

}

#ifdef URHO3D_ANGELSCRIPT
/// Angelscript Register object factory. (semi-manditory)
void AView::RegisterObject(Context* context)
{
    context->RegisterFactory<AView>(AUI_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(AWidget);
}
#endif

}
