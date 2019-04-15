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

#include "APreferredSize.h"

namespace Urho3D
{

APreferredSize::APreferredSize(int w, int h) :
    preferredSize_(w, h)
{
    preferredSize_.max_w = w == 0 ? 10000 : w;
    preferredSize_.max_h = h == 0 ? 10000 : h;
}

APreferredSize::~APreferredSize()
{

}

int APreferredSize::GetMinWidth() const
{
    return preferredSize_.min_w;

}

int APreferredSize::GetMinHeight() const
{
    return preferredSize_.min_h;
}

int APreferredSize::GetMaxWidth() const
{
    return preferredSize_.max_w;
}

int APreferredSize::GetMaxHeight() const
{
    return preferredSize_.max_h;
}

int APreferredSize::GetPrefWidth() const
{
    return preferredSize_.pref_w;
}

int APreferredSize::GetPrefHeight() const
{
    return preferredSize_.pref_h;
}

UI_SIZE_DEP APreferredSize::GetSizeDep() const
{
    return (UI_SIZE_DEP) preferredSize_.size_dependency;
}

void APreferredSize::SetMinWidth(int w)
{
    preferredSize_.min_w = w;
}

void APreferredSize::SetMinHeight(int h)
{
    preferredSize_.min_h = h;
}

void APreferredSize::SetMaxWidth(int w)
{
    preferredSize_.max_w = w;
}

void APreferredSize::SetMaxHeight(int h)
{
    preferredSize_.max_h = h;
}

void APreferredSize::SetPrefWidth(int w)
{
    preferredSize_.pref_w = w;
}

void APreferredSize::SetPrefHeight(int h)
{
    preferredSize_.pref_h = h;
}

void APreferredSize::SetSizeDep(UI_SIZE_DEP dep)
{
    preferredSize_.size_dependency = (tb::SIZE_DEP) dep;
}

}
