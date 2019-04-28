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

#include <TurboBadger/tb_types.h>
#include <TurboBadger/renderers/tb_renderer_batcher.h>
#include "../Core/Context.h"
#include "../AUI/ABatch.h"

namespace tb
{
class TBBitmap;
class TBRect;
}

namespace Urho3D
{

class AUI;

class URHO3D_API ARenderer : public tb::TBRendererBatcher
{
    friend class AView;

public:

    ARenderer(Context* context);
    virtual ~ARenderer();

    void BeginPaint(int render_target_w, int render_target_h);
    void EndPaint();

    tb::TBBitmap *CreateBitmap(int width, int height, tb::uint32 *data);

    void RenderBatch(Batch *batch);

    void SetClipRect(const tb::TBRect &rect);

    Context* GetContext() { return context_; }

private:
    WeakPtr<Context> context_;
    PODVector<ABatch>* batches_;
    PODVector<float>* vertexData_;
    IntRect currentScissor_;
};

}
