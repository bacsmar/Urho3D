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

#include "../Core/Object.h"

namespace Urho3D
{

// UIUpdate event which is sent post engine update, ensuring all input events have been processed
// Used primarily for drag+drop operations
URHO3D_EVENT(E_UIUPDATE, UIUpdate)
{

}

// General AWidget event
URHO3D_EVENT(E_WIDGETEVENT, WidgetEvent)
{
    URHO3D_PARAM(P_HANDLER, Handler);           // AWidget pointer of widget's OnEvent we are in
    URHO3D_PARAM(P_TARGET, Target);             // AWidget pointer
    URHO3D_PARAM(P_TYPE, Type);                 // enum UI_EVENT_TYPE
    URHO3D_PARAM(P_X, X);                       // int
    URHO3D_PARAM(P_Y, Y);                       // int
    URHO3D_PARAM(P_DELTAX, DeltaX);             // int
    URHO3D_PARAM(P_DELTAY, DeltaY);             // int
    URHO3D_PARAM(P_COUNT, Count);               // int
    URHO3D_PARAM(P_KEY, Key);                   // int
    URHO3D_PARAM(P_SPECIALKEY, SpecialKey);     // enum SPECIAL_KEY
    URHO3D_PARAM(P_MODIFIERKEYS, ModifierKeys); // enum MODIFIER_KEYS
    URHO3D_PARAM(P_REFID, RefID);               // string (TBID)
    URHO3D_PARAM(P_TOUCH, Touch);               // bool

    // EventHandled can be set by event receivers to stop event bubble
    URHO3D_PARAM(P_HANDLED, Handled);               // [OUT] -> bool

}

// Reports when a resource file is loaded into the AWidget
URHO3D_EVENT(E_AWIDGETLOADED, AWidgetLoaded)
{
    URHO3D_PARAM(P_WIDGET, Widget);             // AWidget pointer
}

// Reports when the input focus move to or from the Awidget
//URHO3D_EVENT(E_WIDGETFOCUSCHANGED, WidgetFocusChanged)
//{
//    URHO3D_PARAM(P_WIDGET, Widget);             // AWidget pointer
//    URHO3D_PARAM(P_FOCUSED, Focused);             // bool
//}

// Reports that this AWidget is about to be deleted
URHO3D_EVENT(E_WIDGETDELETED, WidgetDeleted)
{
    URHO3D_PARAM(P_WIDGET, Widget);             // AWidget pointer
}

// AWidget Drag+Drop operations
URHO3D_EVENT(E_ADRAGBEGIN, ADragBegin)
{
    URHO3D_PARAM(P_TARGET, Source);             // AWidget source
    URHO3D_PARAM(P_DRAGOBJECT, DragObject);     // ADragObject pointer
}

// AWidget Drag+Drop operations
URHO3D_EVENT(E_ADRAGENTERWIDGET, ADragEnterWidget)
{
    URHO3D_PARAM(P_WIDGET, Widget);             // AWidget pointer
    URHO3D_PARAM(P_DRAGOBJECT, DragObject);     // ADragObject pointer
}

// AWidget Drag+Drop operations
URHO3D_EVENT(E_ADRAGEXITWIDGET, ADragExitWidget)
{
    URHO3D_PARAM(P_WIDGET, Widget);             // AWidget pointer
    URHO3D_PARAM(P_DRAGOBJECT, DragObject);     // ADragObject pointer
}

// AWidget Drag+Drop operations
URHO3D_EVENT(E_ADRAGENDED, ADragEnded)
{
    URHO3D_PARAM(P_TARGET, Target);             // AWidget pointer
    URHO3D_PARAM(P_DRAGOBJECT, DragObject);     // ADragObject pointer
}

// Report when an internal popup menu is invoked
URHO3D_EVENT(E_APOPUPMENUSELECT, APopupMenuSelect)
{
    URHO3D_PARAM(P_BUTTON, Button);             // AButton that created popup
    URHO3D_PARAM(P_REFID, RefID);               // string tbid
}

// Report when a shortcut key has been pressed
URHO3D_EVENT(E_AUISHORTCUT, AShortcut)
{
    URHO3D_PARAM(P_KEY, Key);                    // int
    URHO3D_PARAM(P_QUALIFIERS, Qualifiers);      // int
}

//Reports when the shortcut key was pressed that is not programmed (so apps can make shortcuts)
URHO3D_EVENT(E_AUNHANDLEDSHORTCUT, AUnhandledShortcut)
{
    URHO3D_PARAM(P_REFID, RefID);                // string tbid
}

// Report when the window has been closed
URHO3D_EVENT(E_AWINDOWCLOSED, AWindowClosed)
{
    URHO3D_PARAM(P_WINDOW, Window);               // AWindow
}

// Reports when the input focus move to or from the Awidget (remove dupish above?)
URHO3D_EVENT(E_AWIDGETFOCUSCHANGED, AWidgetFocusChanged)
{
    URHO3D_PARAM(P_WIDGET, Widget);               // AWidget pointer
    URHO3D_PARAM(P_FOCUSED, Focused);             // bool
}

// Reports when the Escape key is pressed in the focused AWidget
URHO3D_EVENT(E_AWIDGETFOCUSESCAPED, AWidgetFocusEscaped)
{
}

// Reports when the edit is cancelled in the AWidget
URHO3D_EVENT(E_AWIDGETEDITCANCELED, AWidgetEditCanceled)
{
    URHO3D_PARAM(P_WIDGET, Widget);            // AWidget pointer
}

// Reports when the edit is completed in the AWidget
URHO3D_EVENT(E_AWIDGETEDITCOMPLETE, AWidgetEditComplete)
{
    URHO3D_PARAM(P_WIDGET, Widget);             // AWidget pointer
}


// Reports the selected item change in a list 
URHO3D_EVENT(E_ALISTVIEWSELECTIONCHANGED, AListViewSelectionChanged)
{
    URHO3D_PARAM(P_REFID, RefID);               // string tbid
    URHO3D_PARAM(P_SELECTED, Selected);         // bool
}

/// event for PromptWindow
URHO3D_EVENT(E_APROMPTCOMPLETE, APromptComplete)
{
    URHO3D_PARAM(P_TITLE, Title);               // string
    URHO3D_PARAM(P_REASON, Reason);             // string
    URHO3D_PARAM(P_SELECTED, Selected);         // string
}

/// event for FinderWindow
URHO3D_EVENT(E_AFINDERCOMPLETE, AFinderComplete)
{
    URHO3D_PARAM(P_TITLE, Title);               // string
    URHO3D_PARAM(P_REASON, Reason);             // string
    URHO3D_PARAM(P_SELECTED, Selected);         // string
}

}
