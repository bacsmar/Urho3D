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

#include "AWidget.h"

namespace Urho3D
{

class ALayout;

//@ASBindGen Class ObjectType=Ref
class ATabContainer : public AWidget
{
    URHO3D_OBJECT(ATabContainer, AWidget)

public:

    //@ASBindGen Constructor UseUrho3DScriptContext_arg0
    ATabContainer(Context* context, bool createWidget = true);
    virtual ~ATabContainer();

    //@ASBindGen Function
    int GetNumPages();
    //@ASBindGen Function
    void SetCurrentPage(int page);

    //@ASBindGen Function AddRef_arg-1
    AWidget* GetCurrentPageWidget();

    ALayout* GetTabLayout();
    
    //@ASBindGen Function
    int GetCurrentPage(); /// returns the current page number
    //@ASBindGen Function
    bool DeletePage( int page ); /// deletes a tab + page, returns true if successful
    //@ASBindGen Function
    void AddTabPageFile ( const String &tabname, const String &layoutFile, bool selecttab = true ); /// adds a tab + page from file
    //@ASBindGen Function AddRef_arg1
   void AddTabPageWidget ( const String &tabname, AWidget *widget, bool selecttab = true ); /// adds a tab + page widget(s)

    //@ASBindGen Function
    void UndockPage ( int page ); /// undocks the page into a window with the tab name, and removes the tab
    //@ASBindGen Function
    bool DockWindow ( String windowTitle ); /// docks content from a ADockWindow with specified title

#ifdef URHO3D_ANGELSCRIPT
    /// Angelscript Register object factory. (semi-manditory)
    static void RegisterObject(Context* context);
#endif

protected:

    virtual bool OnEvent(const tb::TBWidgetEvent &ev);

private:

};

}
