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

#include <TurboBadger/tb_widgets.h>
#include <TurboBadger/tb_widgets_common.h>
#include <TurboBadger/tb_font_renderer.h>

#include "../Core/Object.h"

#include "../AUI/APreferredSize.h"
#include "../AUI/ADragObject.h"

namespace Urho3D
{

// UI_WIDGET_* enums must match TurboBadger internal enum values, we assign directly to TB enum values
// as C# script bindings need the values 
// Note, this could be automated with a dumper util that compiles values in, however that is quite complicated

/// Defines widget visibility, used with AWidget::SetVisibility.
//@ASBindGen Enum
enum UI_WIDGET_VISIBILITY
{
    /// Visible (default)
    UI_WIDGET_VISIBILITY_VISIBLE = 0, //tb::WIDGET_VISIBILITY_VISIBLE,
    /// Invisible, but layouted. Interaction disabled.
    UI_WIDGET_VISIBILITY_INVISIBLE = 1, //tb::WIDGET_VISIBILITY_INVISIBLE,
    /// Invisible and no layout. Interaction disabled.
    UI_WIDGET_VISIBILITY_GONE = 2 //tb::WIDGET_VISIBILITY_GONE
};

/// TBWidget gravity (may be combined).
/// Gravity gives hints about positioning and sizing preferences.
//@ASBindGen Enum
enum UI_GRAVITY {

    UI_GRAVITY_NONE = 0,   // tb::WIDGET_GRAVITY_NONE,
    UI_GRAVITY_LEFT = 1,   // tb::WIDGET_GRAVITY_LEFT,
    UI_GRAVITY_RIGHT = 2,  // tb::WIDGET_GRAVITY_RIGHT,
    UI_GRAVITY_TOP = 4,    // tb::WIDGET_GRAVITY_TOP,
    UI_GRAVITY_BOTTOM = 8, // tb::WIDGET_GRAVITY_BOTTOM,

    UI_GRAVITY_LEFT_RIGHT    = 3 ,  // tb::WIDGET_GRAVITY_LEFT_RIGHT,
    UI_GRAVITY_TOP_BOTTOM    = 12,  // tb::WIDGET_GRAVITY_TOP_BOTTOM,
    UI_GRAVITY_ALL           = 15, // tb::WIDGET_GRAVITY_ALL,
    UI_GRAVITY_DEFAULT       = 5   // tb::WIDGET_GRAVITY_DEFAULT
};


    /** UI_EVENT_TYPE_CLICK Click event is what should be used to trig actions in almost all cases.
        It is invoked on a widget after POINTER_UP if the pointer is still inside
        its hit area. It can also be invoked by keyboard on some clickable widgets
        (see TBWidget::SetClickByKey).
        If panning of scrollable widgets start while the pointer is down, CLICK
        won't be invoked when releasing the pointer (since that should stop panning). */
    /** UI_EVENT_TYPE_LONG_CLICK Long click event is sent when the pointer has been down for some time
        without moving much.
        It is invoked on a widget that has enabled it (TBWidget::SetWantLongClick
        If this event isn't handled, the widget will invoke a CONTEXT_MENU event.
        If any of those are handled, the CLICK event that would normally be
        invoked after the pending POINTER_UP will be suppressed. */
    /** UI_EVENT_TYPE_CHANGED Invoked after changing text in a TBTextField, changing selected item
        in a TBSelectList etc. Invoking this event trigs synchronization with
        connected TBWidgetValue and other widgets connected to it. */
    /** UI_EVENT_TYPE_SHORTCUT Invoked by the platform when a standard keyboard shortcut is pressed.
        It's called before InvokeKeyDown (EVENT_TYPE_KEY_DOWN) and if the event
        is handled (returns true), the KeyDown is canceled.
        The ref_id will be set to one of the following:
            "cut", "copy", "paste", "selectall", "undo", "redo", "new", "open", "save". */
    /** UI_EVENT_TYPE_CONTEXT_MENU Invoked when a context menu should be opened at the event x and y coordinates.
        It may be invoked automatically for a widget on long click, if nothing handles
        the long click event. */
    /** UI_EVENT_TYPE_FILE_DROP Invoked by the platform when one or multiple files has been dropped on
        the widget. The event is guaranteed to be a TBWidgetEventFileDrop. */
    /** UI_EVENT_TYPE_TAB_CHANGED Invoked by the platform when a tab container's tab changed */
    /** UI_EVENT_TYPE_CUSTOM Custom event. Not used internally. ref_id may be used for additional type info. */
    /** UI_EVENT_TYPE_TOUCH_DOWN - UI_EVENT_TYPE_TOUCH_CANCEL Local Turbobadger touch events */

//@ASBindGen Enum
enum UI_EVENT_TYPE {

    UI_EVENT_TYPE_CLICK = 0, // tb::EVENT_TYPE_CLICK,
    UI_EVENT_TYPE_LONG_CLICK = 1, // tb::EVENT_TYPE_LONG_CLICK,
    UI_EVENT_TYPE_POINTER_DOWN = 2, // tb::EVENT_TYPE_POINTER_DOWN,
    UI_EVENT_TYPE_POINTER_UP = 3, // tb::EVENT_TYPE_POINTER_UP,
    UI_EVENT_TYPE_POINTER_MOVE = 4, // tb::EVENT_TYPE_POINTER_MOVE,
    UI_EVENT_TYPE_RIGHT_POINTER_DOWN = 5, // tb::EVENT_TYPE_RIGHT_POINTER_DOWN,
    UI_EVENT_TYPE_RIGHT_POINTER_UP = 6, // tb::EVENT_TYPE_RIGHT_POINTER_UP,
    UI_EVENT_TYPE_WHEEL = 7, // tb::EVENT_TYPE_WHEEL,

    UI_EVENT_TYPE_CHANGED = 8, // tb::EVENT_TYPE_CHANGED,
    UI_EVENT_TYPE_KEY_DOWN = 9, // tb::EVENT_TYPE_KEY_DOWN,
    UI_EVENT_TYPE_KEY_UP = 10, // tb::EVENT_TYPE_KEY_UP,

    UI_EVENT_TYPE_SHORTCUT = 11, // tb::EVENT_TYPE_SHORTCUT,
    UI_EVENT_TYPE_CONTEXT_MENU = 12, // tb::EVENT_TYPE_CONTEXT_MENU,
    UI_EVENT_TYPE_FILE_DROP = 13, // tb::EVENT_TYPE_FILE_DROP,
    UI_EVENT_TYPE_TAB_CHANGED = 14, // tb::EVENT_TYPE_TAB_CHANGED,
    UI_EVENT_TYPE_CUSTOM = 15, // tb::EVENT_TYPE_CUSTOM

    UI_EVENT_TYPE_TOUCH_DOWN,  //Local Turbobadger touch events
    UI_EVENT_TYPE_TOUCH_UP,
    UI_EVENT_TYPE_TOUCH_MOVE,
    UI_EVENT_TYPE_TOUCH_CANCEL
};

/** Defines widget z level relative to another widget, used with TBWidget::AddChildRelative. */
//@ASBindGen Enum
enum UI_WIDGET_Z_REL {
    UI_WIDGET_Z_REL_BEFORE = 0, // tb::WIDGET_Z_REL_BEFORE,        ///< Before the reference widget (visually behind reference).
    UI_WIDGET_Z_REL_AFTER = 1   // tb::WIDGET_Z_REL_AFTER            ///< After the reference widget (visually above reference).
};

/// TB_TEXT_ALIGN specifies horizontal text alignment
//@ASBindGen Enum
enum UI_TEXT_ALIGN
{
    UI_TEXT_ALIGN_LEFT = 0,     // tb::TB_TEXT_ALIGN_LEFT,
    UI_TEXT_ALIGN_RIGHT = 1,    // tb::TB_TEXT_ALIGN_RIGHT,
    UI_TEXT_ALIGN_CENTER = 2    // tb::TB_TEXT_ALIGN_CENTER
};

//@ASBindGen Enum
enum UI_WIDGET_STATE {

    UI_WIDGET_STATE_NONE = 0,       // tb::WIDGET_STATE_NONE,
    UI_WIDGET_STATE_DISABLED = 1,   // tb::WIDGET_STATE_DISABLED,
    UI_WIDGET_STATE_FOCUSED = 2,    // tb::WIDGET_STATE_FOCUSED,
    UI_WIDGET_STATE_PRESSED = 4,    // tb::WIDGET_STATE_PRESSED,
    UI_WIDGET_STATE_SELECTED = 8,   // tb::WIDGET_STATE_SELECTED,
    UI_WIDGET_STATE_HOVERED = 16,   // tb::WIDGET_STATE_HOVERED,

    UI_WIDGET_STATE_ALL = 31        // tb::WIDGET_STATE_ALL

};

//@ASBindGen Enum
enum UI_AXIS {
    UI_AXIS_X = 0, ///< Horizontal layout tb::AXIS_X,
    UI_AXIS_Y = 1  ///< Vertical layout tb::AXIS_Y,
};


class AView;
class ALayoutParams;
class AFontDescription;
class ASelectItemSource;

/// Wraps a TurboBadger widget in our Object model
//@ASBindGen Class ObjectType=Ref
class URHO3D_API AWidget : public Object, public tb::TBWidgetDelegate
{
    friend class AUI;

    URHO3D_OBJECT(AWidget, Object)

    public:

    //@ASBindGen Constructor UseUrho3DScriptContext_arg0
    AWidget(Context* context, bool createWidget = true);
    virtual ~AWidget();

    //@ASBindGen Function
    bool Load(const String& filename);

    //@ASBindGen Function
    const String& GetId();

    //@ASBindGen Function
    const String GetClassName();  // for binding

    //@ASBindGen Function AddRef_arg-1
    AWidget* GetParent();
    //@ASBindGen Function AddRef_arg-1
    AWidget* GetContentRoot();
    //@ASBindGen Function
    IntRect GetRect();

    APreferredSize* GetPreferredSize();
    //@ASBindGen Function
    String GetText();

    //@ASBindGen Function
    void SetRect(IntRect r);
    //@ASBindGen Function
    virtual bool SetSize(int width, int height);
    //@ASBindGen Function
    void SetPosition(int x, int y);
    //@ASBindGen Function
    void SetText(const String& text);
    //@ASBindGen Function
    void SetSkinBg(const String& id);
    //@ASBindGen Function AddRef_arg0
    void SetLayoutParams(ALayoutParams* params);
    //@ASBindGen Function AddRef_arg0
    void SetFontDescription(AFontDescription* fd);

    //@ASBindGen Function
    virtual void Remove();
    //@ASBindGen Function AddRef_arg0
    void RemoveChild(AWidget* child, bool cleanup = true);

    //@ASBindGen Function
    void DeleteAllChildren();

    /// searches for specified widget ID from the top of the widget tree, returns the 1st one found.
    //@ASBindGen Function AddRef_arg-1
    virtual AWidget *FindWidget ( const String& searchid );
    /// return all of the widgets of the specified classname and id that is not 0 from the current widget
    virtual void SearchWidgetClass ( const String& className, PODVector<AWidget*> &results );
    ///  return all of the widgets of the specified id and id that is not 0 from the current widget
     virtual void SearchWidgetId ( const String& searchid, PODVector<AWidget*> &results );
    /// return all of the widgets with the specified text and id that is not 0 from the current widget
    virtual void SearchWidgetText ( const String& searchText, PODVector<AWidget*> &results );
    /// print out the widget tree to stdout from the current widget
    //@ASBindGen Function 
    virtual void PrintPrettyTree();

    // for AS binding hopefully
    //@ASBindGen Function AddRef_arg-1
    PODVector<AWidget*> SearchAWidgetClass (const String& className );
    //@ASBindGen Function AddRef_arg-1
    PODVector<AWidget*> SearchAWidgetId ( const String& searchid );
    //@ASBindGen Function AddRef_arg-1
    PODVector<AWidget*> SearchAWidgetText ( const String& searchText);

    // String ID
    //@ASBindGen Function
    virtual void SetId(const String& id);

    //@ASBindGen Function
    void Center();
    //@ASBindGen Function
    void SetGravity(UI_GRAVITY gravity);
    //@ASBindGen Function
    void SetAxis(UI_AXIS axis);

    //@ASBindGen Function
    void SetValue(double value);
    //@ASBindGen Function
    virtual double GetValue();

    //@ASBindGen Function
    virtual void SetFocus();
    //@ASBindGen Function
    virtual bool GetFocus() const;

    /// Set focus to first widget which accepts it
    //@ASBindGen Function
    void SetFocusRecursive();
    void OnFocusChanged(bool focused) override; //note this method is in a protected area in subclasses!

    //@ASBindGen Function
    void SetState(UI_WIDGET_STATE state, bool on);
    //@ASBindGen Function
    bool GetState(UI_WIDGET_STATE state);

    //@ASBindGen Function
    void SetVisibility(UI_WIDGET_VISIBILITY visibility);
    //@ASBindGen Function
    UI_WIDGET_VISIBILITY GetVisibility();

    //@ASBindGen Function
    void SetStateRaw(UI_WIDGET_STATE state);
    //@ASBindGen Function
    UI_WIDGET_STATE GetStateRaw();

    //@ASBindGen Function
    void Invalidate();
    void Die();

    void SetDragObject(ADragObject* object) { dragObject_ = object; }
    ADragObject* GetDragObject() { return dragObject_; }

    //@ASBindGen Function AddRef_arg-1
    AWidget* GetFirstChild();
    //@ASBindGen Function AddRef_arg-1
    AWidget* GetNext();

    //@ASBindGen Function AddRef_arg0
    bool IsAncestorOf(AWidget* widget);

    //@ASBindGen Function
    void SetIsFocusable(bool value);

    // get this or child widget with id
    //@ASBindGen Function AddRef_arg-1
    AWidget* GetWidget(const String& id);

    //@ASBindGen Function AddRef_arg-1
    AView* GetView();

    //@ASBindGen Function AddRef_arg0
    virtual void AddChild(AWidget* child);

    //@ASBindGen Function AddRef_arg0  AddRef_arg1
    void AddChildAfter(AWidget* child, AWidget* otherChild);
    //@ASBindGen Function AddRef_arg0 AddRef_arg1
    void AddChildBefore(AWidget* child, AWidget* otherChild);

    /// Add the child to this widget. See AddChild for adding a child to the top or bottom.
    /// This takes a relative Z and insert the child before or after the given reference widget.
    //@ASBindGen Function AddRef_arg0 AddRef_arg2
    void AddChildRelative(AWidget* child, UI_WIDGET_Z_REL z, AWidget* reference);

    //@ASBindGen Function
    void InvalidateLayout();

    tb::TBWidget* GetInternalWidget() { return widget_; }

    //@ASBindGen Function AddRef_arg0
    void SetDelegate(AWidget* widget) { widget_->SetDelegate(widget); }

    //@ASBindGen Function
    void SetMultiTouch(bool multiTouch) { multiTouch_ = multiTouch; }

    //@ASBindGen Function
    bool IsMultiTouch() { return multiTouch_; }

    //@ASBindGen Function
    bool GetCaptured();

    //@ASBindGen Function
    void SetCapturing(bool capturing);
    //@ASBindGen Function
    bool GetCapturing();

    //@ASBindGen Function
    void InvokeShortcut(const String& shortcut);

    //@ASBindGen Function
    bool GetShortened();

    //@ASBindGen Function
    void SetShortened(bool shortened);

    //@ASBindGen Function
    String GetTooltip();

    //@ASBindGen Function
    void SetTooltip(const String& text);

    //@ASBindGen Function
    void Enable();
    //@ASBindGen Function
    void Disable();

    // Font Description
    //@ASBindGen Function
    void SetFontId(const String& fontId);
    //@ASBindGen Function
    String GetFontId();
    //@ASBindGen Function
    void SetFontSize(int size);
    //@ASBindGen Function
    int GetFontSize();

    // Rect
    //@ASBindGen Function
    void SetX(int x) { IntRect r(GetRect()); r.right_ = x + r.Width(); r.left_ = x; SetRect(r); }
    //@ASBindGen Function
    int GetX() { return GetRect().left_; }
    //@ASBindGen Function
    void SetY(int y) { IntRect r(GetRect()); r.bottom_ = y + r.Height(); r.top_ = y; SetRect(r); }
    //@ASBindGen Function
    int GetY() { return GetRect().top_; }
    //@ASBindGen Function
    void SetWidth(int width) { IntRect r(GetRect()); r.right_ = r.left_ + width; SetRect(r); }
    //@ASBindGen Function
    int GetWidth() { return GetRect().Width(); }
    //@ASBindGen Function
    void SetHeight(int height) { IntRect r(GetRect()); r.bottom_ = r.top_ + height; SetRect(r); }
    //@ASBindGen Function
    int GetHeight() { return GetRect().Height(); }

    // Layout Params
    //@ASBindGen Function
    void SetLayoutWidth(int width);
    //@ASBindGen Function
    int GetLayoutWidth();
    //@ASBindGen Function
    void SetLayoutHeight(int height);
    //@ASBindGen Function
    int GetLayoutHeight();
    //@ASBindGen Function
    void SetLayoutPrefWidth(int width);
    //@ASBindGen Function
    int GetLayoutPrefWidth();
    //@ASBindGen Function
    void SetLayoutPrefHeight(int height);
    //@ASBindGen Function
    int GetLayoutPrefHeight();
    //@ASBindGen Function
    void SetLayoutMinWidth(int width);
    //@ASBindGen Function
    int GetLayoutMinWidth();
    //@ASBindGen Function
    void SetLayoutMinHeight(int height);
    //@ASBindGen Function
    int GetLayoutMinHeight();
    //@ASBindGen Function
    void SetLayoutMaxWidth(int width);
    //@ASBindGen Function
    int GetLayoutMaxWidth();
    //@ASBindGen Function
    void SetLayoutMaxHeight(int height);
    //@ASBindGen Function
    int GetLayoutMaxHeight();

    //  Get x and y (relative to this widget) relative to the upper left corner of the root widget
    //@ASBindGen Function
    IntVector2 ConvertToRoot(const IntVector2 position ) const;

    // Get x and y (relative to the upper left corner of the root widget) relative to this widget
    //@ASBindGen Function
    IntVector2 ConvertFromRoot(const IntVector2 position) const;


    // Opacity and AutoOpacity (AutoOpacity sets visibility as well based on opacity being 0.0 or non-0.0).
    //@ASBindGen Function
    void SetOpacity(float opacity);
    //@ASBindGen Function
    float GetOpacity();
    //@ASBindGen Function
    void SetAutoOpacity(float autoOpacity);
    //@ASBindGen Function
    float GetAutoOpacity();

#ifdef URHO3D_ANGELSCRIPT
    /// Angelscript Register object factory. (semi-manditory)
    static void RegisterObject(Context* context);
#endif

protected:

    void ConvertEvent(AWidget* handler, AWidget* target, const tb::TBWidgetEvent &ev, VariantMap& data);

    void SetWidget(tb::TBWidget* widget);

    virtual bool OnEvent(const tb::TBWidgetEvent &ev) override;
    virtual void OnDelete() override;
    virtual void OnResized(int old_w, int old_h) override;

    String id_;
    tb::TBWidget* widget_;

    SharedPtr<APreferredSize> preferredSize_;

    SharedPtr<ADragObject> dragObject_;

    bool multiTouch_;

};

}
