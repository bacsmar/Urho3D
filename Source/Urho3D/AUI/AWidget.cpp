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

#include "../Precompiled.h"
#include "../Core/Context.h"
#include "../IO/Log.h"
#include "../Input/InputEvents.h"

#include "../AUI/AEvents.h"
#include "../AUI/AUI.h"
#include "../AUI/AWidget.h"
#include "../AUI/ALayout.h"
#include "../AUI/AFontDescription.h"
#include "../AUI/AView.h"
#include "../AUI/ASelectItem.h"

#ifdef URHO3D_ANGELSCRIPT
extern const char* AUI_CATEGORY;  /// for angelscript binding
#endif

using namespace tb;

namespace Urho3D
{

AWidget::AWidget(Context* context, bool createWidget) : Object(context),
    widget_(0),
    preferredSize_(new APreferredSize()),
    multiTouch_(false)
{
    if (createWidget)
    {
        widget_ = new TBWidget();
        widget_->SetDelegate(this);
        GetSubsystem<AUI>()->WrapWidget(this, widget_);
    }
}

AWidget::~AWidget()
{
}

void AWidget::SetIsFocusable(bool value)
{
    if (!widget_)
        return;

    widget_->SetIsFocusable(value);
}

bool AWidget::Load(const String& filename)
{
    AUI* ui = GetSubsystem<AUI>();

    if  (!ui->LoadResourceFile(widget_ , filename))
        return false;

    VariantMap eventData;
    eventData[AWidgetLoaded::P_WIDGET] = this;
    SendEvent(E_AWIDGETLOADED, eventData);
    return true;
}

APreferredSize* AWidget::GetPreferredSize()
{
    // error
    if (!widget_)
        return preferredSize_;

    preferredSize_->SetFromTBPreferredSize(widget_->GetPreferredSize());

    return preferredSize_;
}

AWidget* AWidget::GetWidget(const String& id)
{
    if (!widget_)
        return 0;

    TBWidget* child = widget_->GetWidgetByID(TBID(id.CString()));

    if (!child)
        return 0;

    AUI* ui = GetSubsystem<AUI>();
    return ui->WrapWidget(child);
}

void AWidget::SetWidget(tb::TBWidget* widget)
{
    widget_ = widget;
    widget_->SetDelegate(this);
}

/*
enum SPECIAL_KEY
{
    TB_KEY_UNDEFINED = 0,
    TB_KEY_UP, TB_KEY_DOWN, TB_KEY_LEFT, TB_KEY_RIGHT,
    TB_KEY_PAGE_UP, TB_KEY_PAGE_DOWN, TB_KEY_HOME, TB_KEY_END,
    TB_KEY_TAB, TB_KEY_BACKSPACE, TB_KEY_INSERT, TB_KEY_DELETE,
    TB_KEY_ENTER, TB_KEY_ESC,
    TB_KEY_F1, TB_KEY_F2, TB_KEY_F3, TB_KEY_F4, TB_KEY_F5, TB_KEY_F6,
    TB_KEY_F7, TB_KEY_F8, TB_KEY_F9, TB_KEY_F10, TB_KEY_F11, TB_KEY_F12
};
*/


void AWidget::ConvertEvent(AWidget *handler, AWidget* target, const tb::TBWidgetEvent &ev, VariantMap& data)
{
    AUI* ui = GetSubsystem<AUI>();

    String refid;

    ui->GetTBIDString(ev.ref_id, refid);

    int key = ev.key;

    if (ev.special_key)
    {
        switch (ev.special_key)
        {
        case TB_KEY_ENTER:
            key = KEY_RETURN;
            break;
        case TB_KEY_BACKSPACE:
            key = KEY_BACKSPACE;
            break;
        case TB_KEY_DELETE:
            key = KEY_DELETE;
            break;
        case TB_KEY_DOWN:
            key = KEY_DOWN;
            break;
        case TB_KEY_UP:
            key = KEY_UP;
            break;
        case TB_KEY_LEFT:
            key = KEY_LEFT;
            break;
        case TB_KEY_RIGHT:
            key = KEY_RIGHT;
            break;
        default:
            break;
        }
    }

    unsigned modifierKeys = 0;

    if( ev.special_key && TB_SHIFT)
        modifierKeys |= QUAL_SHIFT;
    if( ev.special_key && TB_CTRL)
        modifierKeys |= QUAL_CTRL;
    if( ev.special_key && TB_ALT)
        modifierKeys |= QUAL_ALT;

    using namespace WidgetEvent;
    data[P_HANDLER] = handler;
    data[P_TARGET] = target;
    data[P_TYPE] = (unsigned) ev.type;
    data[P_X] = ev.target_x;
    data[P_Y] = ev.target_y;
    data[P_DELTAX] = ev.delta_x;
    data[P_DELTAY] = ev.delta_y;
    data[P_COUNT] = ev.count;
    data[P_KEY] = key;

    data[P_SPECIALKEY] = (unsigned) ev.special_key;
    data[P_MODIFIERKEYS] = modifierKeys;
    data[P_REFID] = refid;
    data[P_TOUCH] = (unsigned) ev.touch;
}

void AWidget::OnDelete()
{
    VariantMap eventData;
    eventData[WidgetDeleted::P_WIDGET] = this;
    this->SendEvent(E_WIDGETDELETED, eventData);

    UnsubscribeFromAllEvents();

    if (widget_)
    {
        // if we don't have a AUI subsystem, we are exiting
        AUI* aui = GetSubsystem<AUI>();

        if (aui)
        {
            aui->UnwrapWidget(widget_);
        }
    }

    widget_ = 0;
}

void AWidget::AddChildAfter(AWidget* child, AWidget* otherChild)
{
    if (!widget_ || !child || !child->widget_ || !otherChild || !otherChild->widget_)
        return;

    widget_->AddChildRelative(child->widget_, tb::WIDGET_Z_REL_AFTER, otherChild->widget_);
}

void AWidget::AddChildBefore(AWidget* child, AWidget* otherChild)
{
    if (!widget_ || !child || !child->widget_ || !otherChild || !otherChild->widget_)
        return;

    widget_->AddChildRelative(child->widget_, tb::WIDGET_Z_REL_BEFORE, otherChild->widget_);
}

void AWidget::AddChild(AWidget* child)
{
    if (!widget_ || !child || !child->widget_)
        return;

    widget_->AddChild(child->widget_);
}

void AWidget::AddChildRelative(AWidget* child, UI_WIDGET_Z_REL z, AWidget* reference)
{
    if (!widget_ || !child || !child->widget_ || !reference || !reference->widget_)
        return;

    widget_->AddChildRelative(child->widget_, (WIDGET_Z_REL) z, reference->widget_);
}

const String AWidget::GetClassName()
{
    if (!widget_)
        return String::EMPTY;

    return widget_->GetClassName();
}

String AWidget::GetText()
{
    if (!widget_)
        return String::EMPTY;

    return widget_->GetText().CStr();
}

void AWidget::SetText(const String& text)
{
    if (!widget_)
        return;

    widget_->SetText(text.CString());
}

void AWidget::SetGravity(UI_GRAVITY gravity)
{
    if (!widget_)
        return;

    widget_->SetGravity((WIDGET_GRAVITY) gravity);
}

void AWidget::SetAxis(UI_AXIS axis)
{
    if (!widget_)
        return;

    widget_->SetAxis((AXIS) axis);
}

bool AWidget::IsAncestorOf(AWidget* widget)
{
    if (!widget_ || !widget || !widget->widget_)
        return false;

    return widget_->IsAncestorOf(widget->widget_);
}

void AWidget::SetPosition(int x, int y)
{
    if (!widget_)
        return;

    widget_->SetPosition(TBPoint(x, y));
}

IntRect AWidget::GetRect()
{
    IntRect rect(0, 0, 0, 0);

    if (!widget_)
        return rect;

    tb::TBRect tbrect = widget_->GetRect();

    rect.top_ = tbrect.y;
    rect.left_ = tbrect.x;
    rect.right_ = tbrect.x + tbrect.w;
    rect.bottom_ = tbrect.y + tbrect.h;

    return rect;
}

void AWidget::SetRect(IntRect rect)
{
    if (!widget_)
        return;

    tb::TBRect tbrect;

    tbrect.y = rect.top_;
    tbrect.x = rect.left_;
    tbrect.w = rect.right_ - rect.left_;
    tbrect.h = rect.bottom_ - rect.top_;

    widget_->SetRect(tbrect);
}


bool AWidget::SetSize(int width, int height)
{
    if (!widget_)
        return false;

    widget_->SetSize(width, height);

    return true;
}

void AWidget::Invalidate()
{
    if (!widget_)
        return;

    widget_->Invalidate();
}

/// searches for specified widget ID from the top of the widget tree, returns the 1st one found.
AWidget *AWidget::FindWidget ( const String& searchid )
{
    if (!widget_)
        return NULL;

    TBWidget* child = widget_->FindWidget(TBID(searchid.CString()));

    if (!child)
        return 0;

    AUI* ui = GetSubsystem<AUI>();
    return ui->WrapWidget(child);
}

void AWidget::PrintPrettyTree()
{
    if (!widget_)
        return;

    widget_->PrintPretty("", true);
}

/// return all of the widgets of the specified classname
void AWidget::SearchWidgetClass ( const String& className, PODVector<AWidget*> &results ) 
{
    results.Clear();

    if (!widget_)
        return;

    tb::TBValue tbval(TBValue::TYPE_ARRAY); // TB array of values
    tbval.SetArray(new tb::TBValueArray(), TBValue::SET_AS_STATIC); // dont delete pointers on destruction
    widget_->SearchWidgetClass(className.CString(), tbval ); // visit all children for search

    AUI* ui = GetSubsystem<AUI>();
    int nn=0;
    for ( nn=0; nn<tbval.GetArrayLength(); nn++ ) // copy tbwidget ptr to uiwidget ptr
    {
        tb::TBWidget *tbw = (tb::TBWidget *)tbval.GetArray()->GetValue(nn)->GetObject();
        AWidget *wrp = ui->WrapWidget(tbw);
        results.Push( wrp );
    }
}

///  return all of the widgets of the specified id
void AWidget::SearchWidgetId ( const String& searchid, PODVector<AWidget*> &results )
{

    results.Clear();

    if (!widget_)
        return;

    tb::TBValue tbval(TBValue::TYPE_ARRAY);
    tbval.SetArray(new tb::TBValueArray(), TBValue::SET_AS_STATIC);
    widget_->SearchWidgetId(TBID(searchid.CString()), tbval );

    AUI* ui = GetSubsystem<AUI>();
    int nn=0;
    for ( nn=0; nn<tbval.GetArrayLength(); nn++ )
    {
        tb::TBWidget *tbw = (tb::TBWidget *)tbval.GetArray()->GetValue(nn)->GetObject();
        AWidget *wrp = ui->WrapWidget(tbw);
        results.Push( wrp );
    }
}

/// return all of the widgets with the specified text
void AWidget::SearchWidgetText ( const String& searchText, PODVector<AWidget*> &results )
{
    results.Clear();

    if (!widget_)
        return;

    tb::TBValue tbval(TBValue::TYPE_ARRAY);
    tbval.SetArray(new tb::TBValueArray(), TBValue::SET_AS_STATIC);
    widget_->SearchWidgetText(searchText.CString(), tbval );

    AUI* ui = GetSubsystem<AUI>();
    int nn=0;
    for ( nn=0; nn<tbval.GetArrayLength(); nn++ )
    {
        tb::TBWidget *tbw = (tb::TBWidget *)tbval.GetArray()->GetValue(nn)->GetObject();
        AWidget *wrp = ui->WrapWidget(tbw);
        results.Push( wrp );
    }
}

PODVector<AWidget*> AWidget::SearchAWidgetClass (const String& className ) // for AS binding
{
   PODVector<AWidget*> myresults;
   SearchWidgetClass( className, myresults );
   return myresults;
}

PODVector<AWidget*> AWidget::SearchAWidgetId ( const String& searchid ) // for AS binding
{
   PODVector<AWidget*> results;
   SearchWidgetId( searchid, results );
   return results;
}

PODVector<AWidget*> AWidget::SearchAWidgetText ( const String& searchText) // for AS binding
{
   PODVector<AWidget*> results;
   SearchWidgetText( searchText, results );
   return results;
}


void AWidget::Center()
{
    if (!widget_)
        return;

    TBRect rect = widget_->GetRect();
    TBWidget* root = widget_->GetParent();
    if (!root)
    {
        AUI* ui = GetSubsystem<AUI>();
        root = ui->GetRootWidget();
    }

    TBRect bounds(0, 0, root->GetRect().w, root->GetRect().h);
    widget_->SetRect(rect.CenterIn(bounds).MoveIn(bounds).Clip(bounds));
}

AWidget* AWidget::GetParent()
{
    if (!widget_)
        return 0;

    TBWidget* parent = widget_->GetParent();

    if (!parent)
        return 0;

    AUI* ui = GetSubsystem<AUI>();

    return ui->WrapWidget(parent);
}

AWidget* AWidget::GetContentRoot()
{
    if (!widget_)
        return 0;

    TBWidget* root = widget_->GetContentRoot();

    if (!root)
        return 0;

    AUI* ui = GetSubsystem<AUI>();

    return ui->WrapWidget(root);
}

void AWidget::Die()
{
    if (!widget_)
        return;

    // clear delegate
    widget_->SetDelegate(NULL);
    // explictly die (can trigger an animation)
    widget_->Die();
    // call OnDelete, which unwraps the widget and does some bookkeeping
    OnDelete();
}

void AWidget::SetLayoutParams(ALayoutParams* params)
{
    if (!widget_)
        return;

    widget_->SetLayoutParams(*(params->GetTBLayoutParams()));
}

void AWidget::SetFontDescription(AFontDescription* fd)
{
    if (!widget_)
        return;

    widget_->SetFontDescription(*(fd->GetTBFontDescription()));
}

void AWidget::SetFontId(const String& fontId)
{
    if (!widget_)
        return;

    tb::TBFontDescription fd(widget_->GetFontDescription());
    fd.SetID(fontId.CString());
    widget_->SetFontDescription(fd);
}

String AWidget::GetFontId()
{
    if (!widget_)
        return "";

    tb::TBFontDescription fd(widget_->GetFontDescription());
    if (!g_font_manager->HasFontFace(fd))
    {
        return "";
    }
    return g_font_manager->GetFontInfo(fd.GetID())->GetName();
}

void AWidget::SetFontSize(int size)
{
    if (!widget_)
        return;

    tb::TBFontDescription fd(widget_->GetFontDescription());
    fd.SetSize(size);
    widget_->SetFontDescription(fd);
}

int AWidget::GetFontSize()
{
    if (!widget_)
        return 0;

    tb::TBFontDescription fd(widget_->GetFontDescription());
    return fd.GetSize();
}

void AWidget::SetLayoutWidth(int width)
{
    if (!widget_)
        return;

    tb::LayoutParams lp;

    const tb::LayoutParams *oldLp(widget_->GetLayoutParams());
    if (oldLp)
        lp = *oldLp;

    lp.SetWidth(width);
    widget_->SetLayoutParams(lp);
}

int AWidget::GetLayoutWidth()
{
    if (!widget_)
        return tb::LayoutParams::UNSPECIFIED;

    const tb::LayoutParams *lp(widget_->GetLayoutParams());
    if (!lp)
        return tb::LayoutParams::UNSPECIFIED;

    return lp->pref_w;
}

void AWidget::SetLayoutHeight(int height)
{
    if (!widget_)
        return;

    tb::LayoutParams lp;

    const tb::LayoutParams *oldLp(widget_->GetLayoutParams());
    if (oldLp)
        lp = *oldLp;

    lp.SetHeight(height);
    widget_->SetLayoutParams(lp);
}

int AWidget::GetLayoutHeight()
{
    if (!widget_)
        return tb::LayoutParams::UNSPECIFIED;

    const tb::LayoutParams *lp(widget_->GetLayoutParams());
    if (!lp)
        return tb::LayoutParams::UNSPECIFIED;

    return lp->pref_h;
}

void AWidget::SetLayoutPrefWidth(int width)
{
    if (!widget_)
        return;

    tb::LayoutParams lp;

    const tb::LayoutParams *oldLp(widget_->GetLayoutParams());
    if (oldLp)
        lp = *oldLp;

    lp.pref_w = width;
    widget_->SetLayoutParams(lp);
}

int AWidget::GetLayoutPrefWidth()
{
    if (!widget_)
        return tb::LayoutParams::UNSPECIFIED;

    const tb::LayoutParams *lp(widget_->GetLayoutParams());
    if (!lp)
        return tb::LayoutParams::UNSPECIFIED;

    return lp->pref_w;
}

void AWidget::SetLayoutPrefHeight(int height)
{
    if (!widget_)
        return;

    tb::LayoutParams lp;

    const tb::LayoutParams *oldLp(widget_->GetLayoutParams());
    if (oldLp)
        lp = *oldLp;

    lp.pref_h = height;
    widget_->SetLayoutParams(lp);
}

int AWidget::GetLayoutPrefHeight()
{
    if (!widget_)
        return tb::LayoutParams::UNSPECIFIED;

    const tb::LayoutParams *lp(widget_->GetLayoutParams());
    if (!lp)
        return tb::LayoutParams::UNSPECIFIED;

    return lp->pref_h;
}

void AWidget::SetLayoutMinWidth(int width)
{
    if (!widget_)
        return;

    tb::LayoutParams lp;

    const tb::LayoutParams *oldLp(widget_->GetLayoutParams());
    if (oldLp)
        lp = *oldLp;

    lp.min_w = width;
    widget_->SetLayoutParams(lp);
}

int AWidget::GetLayoutMinWidth()
{
    if (!widget_)
        return tb::LayoutParams::UNSPECIFIED;

    const tb::LayoutParams *lp(widget_->GetLayoutParams());
    if (!lp)
        return tb::LayoutParams::UNSPECIFIED;

    return lp->min_w;
}

void AWidget::SetLayoutMinHeight(int height)
{
    if (!widget_)
        return;

    tb::LayoutParams lp;

    const tb::LayoutParams *oldLp(widget_->GetLayoutParams());
    if (oldLp)
        lp = *oldLp;

    lp.min_h = height;
    widget_->SetLayoutParams(lp);
}

int AWidget::GetLayoutMinHeight()
{
    if (!widget_)
        return tb::LayoutParams::UNSPECIFIED;

    const tb::LayoutParams *lp(widget_->GetLayoutParams());
    if (!lp)
        return tb::LayoutParams::UNSPECIFIED;

    return lp->min_h;
}

void AWidget::SetLayoutMaxWidth(int width)
{
    if (!widget_)
        return;

    tb::LayoutParams lp;

    const tb::LayoutParams *oldLp(widget_->GetLayoutParams());
    if (oldLp)
        lp = *oldLp;

    lp.max_w = width;
    widget_->SetLayoutParams(lp);
}

int AWidget::GetLayoutMaxWidth()
{
    if (!widget_)
        return tb::LayoutParams::UNSPECIFIED;

    const tb::LayoutParams *lp(widget_->GetLayoutParams());
    if (!lp)
        return tb::LayoutParams::UNSPECIFIED;

    return lp->max_w;
}

void AWidget::SetLayoutMaxHeight(int height)
{
    if (!widget_)
        return;

    tb::LayoutParams lp;

    const tb::LayoutParams *oldLp(widget_->GetLayoutParams());
    if (oldLp)
        lp = *oldLp;

    lp.max_h = height;
    widget_->SetLayoutParams(lp);
}

int AWidget::GetLayoutMaxHeight()
{
    if (!widget_)
        return tb::LayoutParams::UNSPECIFIED;

    const tb::LayoutParams *lp(widget_->GetLayoutParams());
    if (!lp)
        return tb::LayoutParams::UNSPECIFIED;

    return lp->max_h;
}

void AWidget::SetOpacity(float opacity)
{
    if (!widget_)
        return;

    widget_->SetOpacity(opacity);
}

float AWidget::GetOpacity()
{
    if (!widget_)
        return -0.0f;

    return widget_->GetOpacity();
}

void AWidget::SetAutoOpacity(float autoOpacity)
{
    if (!widget_)
        return;

    if (autoOpacity == 0.0f)
    {
        widget_->SetOpacity(autoOpacity);
        widget_->SetVisibilility(tb::WIDGET_VISIBILITY_INVISIBLE);
    }
    else
    {
        widget_->SetVisibilility(tb::WIDGET_VISIBILITY_VISIBLE);
        widget_->SetOpacity(autoOpacity);
    }
}

float AWidget::GetAutoOpacity()
{
    if (!widget_)
        return -0.0f;

    float autoOpacity(widget_->GetOpacity());

    if (autoOpacity == 0.0f)
    {
        if (widget_->GetVisibility() == tb::WIDGET_VISIBILITY_VISIBLE)
            return 0.0001f; // Don't say that it's completly invisible.
    }
    else
    {
        if (widget_->GetVisibility() != tb::WIDGET_VISIBILITY_VISIBLE)
            return 0.0f; // Say it's invisible.
    }
    return autoOpacity;
}

void AWidget::DeleteAllChildren()
{
    if (!widget_)
        return;

    widget_->DeleteAllChildren();
}

void AWidget::SetSkinBg(const String& id)
{
    if (!widget_)
        return;

    widget_->SetSkinBg(TBIDC(id.CString()));
}

void AWidget::Remove()
{
    if (!widget_ || !widget_->GetParent())
        return;

    widget_->GetParent()->RemoveChild(widget_);
}

void AWidget::RemoveChild(AWidget* child, bool cleanup)
{
    if (!widget_ || !child)
        return;

    TBWidget* childw = child->GetInternalWidget();

    if (!childw)
        return;

    widget_->RemoveChild(childw);

    if (cleanup)
        delete childw;
}


const String& AWidget::GetId()
{
    if (!widget_ || !widget_->GetID())
    {
        if (id_.Length())
            id_.Clear();

        return id_;
    }

    if (id_.Length())
        return id_;

    AUI* ui = GetSubsystem<AUI>();
    ui->GetTBIDString(widget_->GetID(), id_);

    return id_;
}

void AWidget::SetId(const String& id)
{
    if (!widget_)
    {
        if (id_.Length())
            id_.Clear();

        return;
    }

    id_ = id;
    widget_->SetID(TBIDC(id.CString()));
}

void AWidget::SetState(UI_WIDGET_STATE state, bool on)
{
    if (!widget_)
        return;

    widget_->SetState((WIDGET_STATE) state, on);
}

void AWidget::SetFocus()
{
    if (!widget_)
        return;

    widget_->SetFocus(WIDGET_FOCUS_REASON_UNKNOWN);
}

bool AWidget::GetFocus() const
{
    if (!widget_)
        return false;

    return widget_->GetIsFocused();
}

void AWidget::SetFocusRecursive()
{
    if (!widget_)
        return;

    widget_->SetFocusRecursive(WIDGET_FOCUS_REASON_UNKNOWN);
}

void AWidget::SetVisibility(UI_WIDGET_VISIBILITY visibility)
{

    if (!widget_)
        return;

    widget_->SetVisibilility((WIDGET_VISIBILITY) visibility);
}

UI_WIDGET_VISIBILITY AWidget::GetVisibility()
{
    if (!widget_)
        return UI_WIDGET_VISIBILITY_GONE;

    return (UI_WIDGET_VISIBILITY) widget_->GetVisibility();
}

AWidget* AWidget::GetChildFromIndex(int index) const
{
    if (!widget_)
        return NULL;

    return GetSubsystem<AUI>()->WrapWidget( widget_->GetChildFromIndex(index) );
}


int AWidget::numChildren() const
{
    if (!widget_)
        return 0;
	return widget_->numChildren();
}


AWidget* AWidget::GetFirstChild()
{
    if (!widget_)
        return NULL;

    return GetSubsystem<AUI>()->WrapWidget(widget_->GetFirstChild());
}

AWidget* AWidget::GetNext()
{
    if (!widget_)
        return NULL;

    return GetSubsystem<AUI>()->WrapWidget(widget_->GetNext());
}

void AWidget::SetValue(double value)
{
    if (!widget_)
        return;

    widget_->SetValueDouble(value);
}

double AWidget::GetValue()
{
    if (!widget_)
        return 0.0;

    return widget_->GetValueDouble();
}

void AWidget::Enable()
{
    if (!widget_)
        return;

    widget_->SetState(WIDGET_STATE_DISABLED, false);
}

void AWidget::Disable()
{

    if (!widget_)
        return;

    widget_->SetState(WIDGET_STATE_DISABLED, true);
}

bool AWidget::GetState(UI_WIDGET_STATE state)
{
    if (!widget_)
        return false;

    return widget_->GetState((WIDGET_STATE) state);
}

void AWidget::SetStateRaw(UI_WIDGET_STATE state)
{
    if (!widget_)
        return;

    widget_->SetStateRaw((WIDGET_STATE) state);
}

UI_WIDGET_STATE AWidget::GetStateRaw()
{
    if (!widget_)
        return UI_WIDGET_STATE_NONE;

    return (UI_WIDGET_STATE) widget_->GetStateRaw();
}

AView* AWidget::GetView()
{
    if (!widget_)
        return 0;

    if (GetType() == AView::GetTypeStatic())
        return static_cast<AView*>(this);

    TBWidget* tbw = widget_->GetParent();
    while(tbw)
    {
        TBWidgetDelegate* delegate = tbw->GetDelegate();
        if (delegate)
        {
            AWidget* d = static_cast<AWidget*>(delegate);
            if (d->GetType() == AView::GetTypeStatic())
                return static_cast<AView*>(d);
        }

        tbw = tbw->GetParent();
    }

    return 0;
}


void AWidget::OnResized(int old_w, int old_h)
{
    // default implementation does nothing
}

void AWidget::OnFocusChanged(bool focused)
{
    using namespace AWidgetFocusChanged;

    VariantMap eventData;
    eventData[AWidgetFocusChanged::P_WIDGET] = this;
    eventData[AWidgetFocusChanged::P_FOCUSED] = focused;
    SendEvent(E_AWIDGETFOCUSCHANGED, eventData);
}

bool AWidget::OnEvent(const tb::TBWidgetEvent &ev)
{
    AUI* ui = GetSubsystem<AUI>();

    if ((ev.type == EVENT_TYPE_CHANGED && !ui->GetBlockChangedEvents()) || ev.type == EVENT_TYPE_KEY_UP)
    {
        if (!ev.target || ui->IsWidgetWrapped(ev.target))
        {
            VariantMap eventData;
            ConvertEvent(this, ui->WrapWidget(ev.target), ev, eventData);
            SendEvent(E_WIDGETEVENT, eventData);

            if (eventData[WidgetEvent::P_HANDLED].GetBool())
                return true;
        }
    }
    else if (ev.type == EVENT_TYPE_RIGHT_POINTER_UP)
    {
        if (!ev.target || ui->IsWidgetWrapped(ev.target))
        {
            VariantMap eventData;
            ConvertEvent(this, ui->WrapWidget(ev.target), ev, eventData);
            SendEvent(E_WIDGETEVENT, eventData);

            if (eventData[WidgetEvent::P_HANDLED].GetBool())
                return true;
        }
    }
    else if (ev.type == EVENT_TYPE_POINTER_DOWN)
    {
        if (!ev.target || ui->IsWidgetWrapped(ev.target))
        {
            VariantMap eventData;
            ConvertEvent(this, ui->WrapWidget(ev.target), ev, eventData);
            SendEvent(E_WIDGETEVENT, eventData);

            if (eventData[WidgetEvent::P_HANDLED].GetBool())
                return true;
        }
    }
    else if (ev.type == EVENT_TYPE_SHORTCUT)
    {
        if (!ev.target || ui->IsWidgetWrapped(ev.target))
        {
            VariantMap eventData;
            ConvertEvent(this, ui->WrapWidget(ev.target), ev, eventData);
            SendEvent(E_WIDGETEVENT, eventData);

            if (eventData[WidgetEvent::P_HANDLED].GetBool())
                return true;
        }
    }
    else if (ev.type == EVENT_TYPE_TAB_CHANGED)
    {
        if (!ev.target || ui->IsWidgetWrapped(ev.target))
        {
            VariantMap eventData;
            ConvertEvent(this, ui->WrapWidget(ev.target), ev, eventData);
            SendEvent(E_WIDGETEVENT, eventData);

            if (eventData[WidgetEvent::P_HANDLED].GetBool())
                return true;
        }
    }
    else if (ev.type == EVENT_TYPE_CLICK)
    {
        if (ev.target && ev.target->GetID() == TBID("__popup-menu"))
        {
            // popup menu
#if 0
/// HELP ATOMIC this shouldnt ever work
            if (JSGetHeapPtr())
#endif
            {
                VariantMap eventData;
                eventData[APopupMenuSelect::P_BUTTON] = this;
                String id;
                ui->GetTBIDString(ev.ref_id, id);
                eventData[APopupMenuSelect::P_REFID] = id;
                SendEvent(E_APOPUPMENUSELECT, eventData);
            }

            return true;
        }
        else
        {
            if (!ev.target || ui->IsWidgetWrapped(ev.target))
            {
                VariantMap eventData;
                ConvertEvent(this, ui->WrapWidget(ev.target), ev, eventData);
                SendEvent(E_WIDGETEVENT, eventData);

                if (eventData[WidgetEvent::P_HANDLED].GetBool())
                    return true;
            }
        }

    }
    if (ev.type == EVENT_TYPE_CUSTOM)
    {
        if (!ev.target || ui->IsWidgetWrapped(ev.target))
        {
            VariantMap eventData;
            ConvertEvent(this, ui->WrapWidget(ev.target), ev, eventData);
            SendEvent(E_WIDGETEVENT, eventData);

            if (eventData[WidgetEvent::P_HANDLED].GetBool())
                return true;
        }
    }

    return false;
}

bool AWidget::GetCaptured()
{
    if (!widget_)
        return false;

    return widget_->IsCaptured();
}

void AWidget::SetCapturing(bool capturing)
{
    if (!widget_)
        return;

    widget_->SetCapturing(capturing);
}

bool AWidget::GetCapturing()
{
    if (!widget_)
        return false;

    return widget_->GetCapturing();
}

void AWidget::InvalidateLayout()
{
    if (!widget_)
        return;

    widget_->InvalidateLayout(tb::TBWidget::INVALIDATE_LAYOUT_TARGET_ONLY);
}

void AWidget::InvokeShortcut(const String& shortcut)
{
    TBWidgetEvent ev(EVENT_TYPE_SHORTCUT);
    ev.ref_id = TBIDC(shortcut.CString());
    widget_->OnEvent(ev);
}

bool AWidget::GetShortened()
{
    if (!widget_)
        return false;

    return widget_->GetShortened();
}

void AWidget::SetShortened(bool shortened)
{
    if (!widget_)
        return;

    widget_->SetShortened(shortened);
}

String AWidget::GetTooltip()
{
    if (!widget_)
        return String::EMPTY;

    return widget_->GetTooltip().CStr();
}

void AWidget::SetTooltip(const String& tooltip)
{
    if (!widget_)
        return;

    widget_->SetTooltip(tooltip.CString());
}

IntVector2 AWidget::ConvertToRoot(const IntVector2 position) const
{
    IntVector2 result = position;

    if (widget_)
        widget_->ConvertToRoot(result.x_, result.y_);

    return result;
}

IntVector2 AWidget::ConvertFromRoot(const IntVector2 position) const
{
    IntVector2 result = position;

    if (widget_)
        widget_->ConvertFromRoot(result.x_, result.y_);

    return result;
}

#ifdef URHO3D_ANGELSCRIPT
/// Angelscript Register object factory. (semi-manditory)
void AWidget::RegisterObject(Context* context)
{
    context->RegisterFactory<AWidget>(AUI_CATEGORY);
}
#endif

}
