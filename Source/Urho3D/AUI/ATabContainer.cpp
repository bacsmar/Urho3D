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
#include <TurboBadger/tb_tab_container.h>

#include "../Precompiled.h"

#include "../AUI/AUI.h"
#include "../AUI/AEvents.h"
#include "../AUI/ATabContainer.h"
#include "../AUI/ALayout.h"
#include "../AUI/AButton.h"

#ifdef URHO3D_ANGELSCRIPT
#include "../Core/Context.h"
#include "../Scene/Serializable.h"
extern const char* AUI_CATEGORY;  /// for angelscript binding
#endif

using namespace tb;

namespace Urho3D
{

ATabContainer::ATabContainer(Context* context, bool createWidget) : AWidget(context, false)
{
    if (createWidget)
    {
        widget_ = new TBTabContainer();
        widget_->SetDelegate(this);
        GetSubsystem<AUI>()->WrapWidget(this, widget_);
    }
}

ATabContainer::~ATabContainer()
{
}

AWidget* ATabContainer::GetCurrentPageWidget()
{
    if (!widget_)
        return 0;

    TBWidget* w = ((TBTabContainer*)widget_)->GetCurrentPageWidget();

    return GetSubsystem<AUI>()->WrapWidget(w);
}

int ATabContainer::GetNumPages()
{
    if (!widget_)
        return -1;

    return ((TBTabContainer*)widget_)->GetNumPages();

}

ALayout* ATabContainer::GetTabLayout()
{
    if (!widget_)
        return 0;

    TBLayout* layout = ((TBTabContainer*)widget_)->GetTabLayout();

    if (!layout)
        return 0;

    AUI* ui = GetSubsystem<AUI>();
    return (ALayout*) ui->WrapWidget(layout);
}

AWidget* ATabContainer::GetPageTab(int page)
{
    if (!widget_ || page < 0 || page > GetNumPages() - 1)
        return 0;

    TBLayout* layout = ((TBTabContainer*)widget_)->GetTabLayout();

     if (!layout)
        return 0;

   TBWidget* myWidget = layout->GetChildFromIndex(page);

    if (!myWidget)
        return 0;

    AUI* ui = GetSubsystem<AUI>();
    return (AWidget*) ui->WrapWidget(myWidget);
}

AWidget* ATabContainer::GetPageContent(int page)
{
    if (!widget_ || page < 0 || page > GetNumPages() - 1)
        return 0;

    TBWidget *conroot = ((TBTabContainer*)widget_)->GetContentRoot();

     if (!conroot)
        return 0;

   TBWidget* myWidget = conroot->GetChildFromIndex(page);

    if (!myWidget)
        return 0;

    AUI* ui = GetSubsystem<AUI>();
    return (AWidget*) ui->WrapWidget(myWidget);
}

void ATabContainer::SetCurrentPage(int page)
{
    if (!widget_)
        return;

    ((TBTabContainer*)widget_)->SetCurrentPage(page);

}

bool ATabContainer::OnEvent(const tb::TBWidgetEvent &ev)
{
    return AWidget::OnEvent(ev);
}


/// returns the current page number
int ATabContainer::GetCurrentPage()
{
    if (!widget_)
        return -1;

    return ((TBTabContainer*)widget_)->GetCurrentPage();

}

/// deletes a tab + page, returns true if successful
bool ATabContainer::DeletePage( int page )
{
    if (!widget_ || page < 0 || page > GetNumPages() - 1)
        return false;

    int lastcurrentpg = GetCurrentPage();
    
    ALayout *uil = GetTabLayout();
    if (uil)
    {
        AWidget* mytab = NULL;
        int nn=0; 
        for (AWidget *child = uil->GetFirstChild(); child; child = child->GetNext())
        {
            if (nn == page)
                mytab = child;
            nn++;
        }
        if (mytab)
        {
            mytab->UnsubscribeFromAllEvents();
            uil->RemoveChild( mytab, true );
        }
    }

    AWidget *pages = GetContentRoot(); 
    if (pages)
    {
        AWidget* mypage = NULL;
        int nn=0; 
        for (AWidget *child = pages->GetFirstChild(); child; child = child->GetNext())
        {
            if (nn == page)
                mypage = child;
            nn++;
        }
        if (mypage)
        {
            mypage->UnsubscribeFromAllEvents();
            pages->RemoveChild( mypage, true );
        }
    }
    
    Invalidate();
    
    if (lastcurrentpg == 0)
        widget_->SetValue(-1); // reset the current page

    // tab container "feature", can not set it to the page number that was removed.
    int num = 0;
    if ( page - 1 > 0 ) num = page - 1;
    SetCurrentPage(num);

    return true;
}

/// adds a tab + page from layout file
void ATabContainer::AddTabPageFile ( const String &tabname, const String &layoutFile, bool selecttab )
{
    AButton* button = new AButton(context_);
    button->SetText(tabname);
    button->SetId(tabname);
    ALayout *uil = GetTabLayout();
    if (uil && button)
        uil->AddChild(button);
    ALayout* layout = new ALayout(context_);
    layout->SetAxis(UI_AXIS_Y);
    layout->SetLayoutSize(UI_LAYOUT_SIZE_AVAILABLE); 
    layout->SetLayoutPosition(UI_LAYOUT_POSITION_GRAVITY); 
    layout->SetLayoutDistribution(UI_LAYOUT_DISTRIBUTION_AVAILABLE); 
    layout->Load (layoutFile);
    AWidget *pages = GetContentRoot();
    if (pages && layout)
        pages->AddChild(layout);

    Invalidate();

    if (selecttab) 
        SetCurrentPage( GetNumPages() -1 );
}

/// adds a tab + page widget(s)
void ATabContainer::AddTabPageWidget ( const String &tabname, AWidget *widget, bool selecttab ) 
{
    AButton* button = new AButton(context_);
    button->SetText(tabname);
    button->SetId(tabname);
    ALayout *uil = GetTabLayout();
    if (uil && button)
        uil->AddChild(button);
    ALayout* layout = new ALayout(context_);
    layout->SetAxis(UI_AXIS_Y);
    layout->SetLayoutSize(UI_LAYOUT_SIZE_AVAILABLE);
    layout->SetLayoutPosition(UI_LAYOUT_POSITION_GRAVITY);
    layout->SetLayoutDistribution(UI_LAYOUT_DISTRIBUTION_AVAILABLE);
    layout->AddChild(widget);
    AWidget *pages = GetContentRoot();
    if (pages && layout)
        pages->AddChild(layout);

    Invalidate();

    if (selecttab) 
        SetCurrentPage( GetNumPages() -1 );
}

/// undocks the page into a window with the tab name, and removes the tab
void ATabContainer::UndockPage ( int page )
{
    if (!widget_)
        return;

    ((TBTabContainer*)widget_)->UndockPage(page);

    // tab container "feature", can not set it to the page number that was removed.
    int num = 0;
    if ( page - 1 > 0 ) num = page - 1;
    SetCurrentPage(num);

    Invalidate();
}

/// docks content from a ADockWindow with specified title
bool ATabContainer::DockWindow ( String windowTitle )
{
    if (!widget_)
        return false;
    bool done = ((TBTabContainer*)widget_)->DockFromWindow(windowTitle.CString());
    if (done)
    {
        SetCurrentPage( GetNumPages() -1 );
        Invalidate();
    }
    return done;
}

#ifdef URHO3D_ANGELSCRIPT
/// Angelscript Register object factory. (semi-manditory)
void ATabContainer::RegisterObject(Context* context)
{
    context->RegisterFactory<ATabContainer>(AUI_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(AWidget);
}
#endif

}
