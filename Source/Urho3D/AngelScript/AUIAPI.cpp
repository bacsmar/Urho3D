//
// Copyright (c) 2008-2019 the Urho3D project.
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
//  This was culled from ASBindGen output --JM

#include "../Precompiled.h"

#include "../AngelScript/APITemplates.h"
#include "../Input/Input.h"

#include "../AUI/AUI.h"

#include "../AUI/ABargraph.h"
#include "../AUI/ACheckBox.h"
#include "../AUI/AClickLabel.h"
#include "../AUI/AColorWheel.h"
#include "../AUI/AColorWidget.h"
#include "../AUI/AComponent.h"
#include "../AUI/AContainer.h"
#include "../AUI/ADockWindow.h"
#include "../AUI/AEditField.h"
#include "../AUI/AFinderWindow.h"
#include "../AUI/AFontDescription.h"
#include "../AUI/AImageWidget.h"
#include "../AUI/AInlineSelect.h"
#include "../AUI/ALayout.h"
#include "../AUI/AMenuWindow.h"
#include "../AUI/AMessageWindow.h"
#include "../AUI/AMultiItem.h"
#include "../AUI/APopupWindow.h"
#include "../AUI/APreferredSize.h"
#include "../AUI/APromptWindow.h"
#include "../AUI/APulldownMenu.h"
#include "../AUI/ARadioButton.h"
#include "../AUI/ASceneView.h"
#include "../AUI/AScrollBar.h"
#include "../AUI/AScrollContainer.h"
#include "../AUI/ASection.h"
#include "../AUI/ASelectDropdown.h"
#include "../AUI/ASelectList.h"
#include "../AUI/AMenubar.h"
#include "../AUI/ASeparator.h"
#include "../AUI/ADimmer.h"
#include "../AUI/AButtonGrid.h"
#include "../AUI/AListView.h"
#include "../AUI/ASkinImage.h"
#include "../AUI/ASlider.h"
#include "../AUI/ATabContainer.h"
#include "../AUI/ATextField.h"
#include "../AUI/ATextureWidget.h"
#include "../AUI/AView.h"

namespace Urho3D
{


AWidget * wrapper_AWidget_constructor_createWidget (bool createWidget)
{
    return new AWidget (Urho3D::GetScriptContext (), createWidget);
}

Urho3D::CScriptArray * wrapper_AWidget_SearchAWidgetClass_className (AWidget* objectPtr, const String& className)
{
    PODVector<AWidget*> result = objectPtr->SearchAWidgetClass (className);
    return Urho3D::VectorToArray <AWidget*> (result, "Array <AWidget@>");
}

Urho3D::CScriptArray * wrapper_AWidget_SearchAWidgetId_searchid (AWidget* objectPtr, const String& searchid)
{
    PODVector<AWidget*> result = objectPtr->SearchAWidgetId (searchid);
    return Urho3D::VectorToArray <AWidget*> (result, "Array <AWidget@>");
}

Urho3D::CScriptArray * wrapper_AWidget_SearchAWidgetText_searchText (AWidget* objectPtr, const String& searchText)
{
    PODVector<AWidget*> result = objectPtr->SearchAWidgetText (searchText);
    return Urho3D::VectorToArray <AWidget*> (result, "Array <AWidget@>");
}

AWindow * wrapper_AWindow_constructor_createWidget (bool createWidget)
{
    return new AWindow (Urho3D::GetScriptContext (), createWidget);
}

AButton * wrapper_AButton_constructor_createWidget (bool createWidget)
{
    return new AButton (Urho3D::GetScriptContext (), createWidget);
}

ASelectItem * wrapper_ASelectItem_constructor_str_id_skinImage (const String& str, const String& id , const String& skinImage )
{
    return new ASelectItem (Urho3D::GetScriptContext (), str, id, skinImage);
}

ASelectItemSource * wrapper_ASelectItemSource_constructor ()
{
    return new ASelectItemSource (Urho3D::GetScriptContext ());
}


void RegisterUI_WIDGET_VISIBILITY (asIScriptEngine *engine)
{
    engine->RegisterEnum ("UI_WIDGET_VISIBILITY");
    engine->RegisterEnumValue ("UI_WIDGET_VISIBILITY", "UI_WIDGET_VISIBILITY_GONE", UI_WIDGET_VISIBILITY_GONE);
    engine->RegisterEnumValue ("UI_WIDGET_VISIBILITY", "UI_WIDGET_VISIBILITY_INVISIBLE", UI_WIDGET_VISIBILITY_INVISIBLE);
    engine->RegisterEnumValue ("UI_WIDGET_VISIBILITY", "UI_WIDGET_VISIBILITY_VISIBLE", UI_WIDGET_VISIBILITY_VISIBLE);
}

void RegisterUI_WIDGET_STATE (asIScriptEngine *engine)
{
    engine->RegisterEnum ("UI_WIDGET_STATE");
    engine->RegisterEnumValue ("UI_WIDGET_STATE", "UI_WIDGET_STATE_PRESSED", UI_WIDGET_STATE_PRESSED);
    engine->RegisterEnumValue ("UI_WIDGET_STATE", "UI_WIDGET_STATE_NONE", UI_WIDGET_STATE_NONE);
    engine->RegisterEnumValue ("UI_WIDGET_STATE", "UI_WIDGET_STATE_SELECTED", UI_WIDGET_STATE_SELECTED);
    engine->RegisterEnumValue ("UI_WIDGET_STATE", "UI_WIDGET_STATE_ALL", UI_WIDGET_STATE_ALL);
    engine->RegisterEnumValue ("UI_WIDGET_STATE", "UI_WIDGET_STATE_HOVERED", UI_WIDGET_STATE_HOVERED);
    engine->RegisterEnumValue ("UI_WIDGET_STATE", "UI_WIDGET_STATE_FOCUSED", UI_WIDGET_STATE_FOCUSED);
    engine->RegisterEnumValue ("UI_WIDGET_STATE", "UI_WIDGET_STATE_DISABLED", UI_WIDGET_STATE_DISABLED);
}

void RegisterUI_AXIS (asIScriptEngine *engine)
{
    engine->RegisterEnum ("UI_AXIS");
    engine->RegisterEnumValue ("UI_AXIS", "UI_AXIS_Y", UI_AXIS_Y);
    engine->RegisterEnumValue ("UI_AXIS", "UI_AXIS_X", UI_AXIS_X);
}

void RegisterUI_EVENT_TYPE (asIScriptEngine *engine)
{
    engine->RegisterEnum ("UI_EVENT_TYPE");
    engine->RegisterEnumValue ("UI_EVENT_TYPE", "UI_EVENT_TYPE_KEY_DOWN", UI_EVENT_TYPE_KEY_DOWN);
    engine->RegisterEnumValue ("UI_EVENT_TYPE", "UI_EVENT_TYPE_KEY_UP", UI_EVENT_TYPE_KEY_UP);
    engine->RegisterEnumValue ("UI_EVENT_TYPE", "UI_EVENT_TYPE_LONG_CLICK", UI_EVENT_TYPE_LONG_CLICK);
    engine->RegisterEnumValue ("UI_EVENT_TYPE", "UI_EVENT_TYPE_TOUCH_UP", UI_EVENT_TYPE_TOUCH_UP);
    engine->RegisterEnumValue ("UI_EVENT_TYPE", "UI_EVENT_TYPE_CLICK", UI_EVENT_TYPE_CLICK);
    engine->RegisterEnumValue ("UI_EVENT_TYPE", "UI_EVENT_TYPE_CONTEXT_MENU", UI_EVENT_TYPE_CONTEXT_MENU);
    engine->RegisterEnumValue ("UI_EVENT_TYPE", "UI_EVENT_TYPE_WHEEL", UI_EVENT_TYPE_WHEEL);
    engine->RegisterEnumValue ("UI_EVENT_TYPE", "UI_EVENT_TYPE_RIGHT_POINTER_UP", UI_EVENT_TYPE_RIGHT_POINTER_UP);
    engine->RegisterEnumValue ("UI_EVENT_TYPE", "UI_EVENT_TYPE_POINTER_UP", UI_EVENT_TYPE_POINTER_UP);
    engine->RegisterEnumValue ("UI_EVENT_TYPE", "UI_EVENT_TYPE_FILE_DROP", UI_EVENT_TYPE_FILE_DROP);
    engine->RegisterEnumValue ("UI_EVENT_TYPE", "UI_EVENT_TYPE_TOUCH_CANCEL", UI_EVENT_TYPE_TOUCH_CANCEL);
    engine->RegisterEnumValue ("UI_EVENT_TYPE", "UI_EVENT_TYPE_TOUCH_MOVE", UI_EVENT_TYPE_TOUCH_MOVE);
    engine->RegisterEnumValue ("UI_EVENT_TYPE", "UI_EVENT_TYPE_TOUCH_DOWN", UI_EVENT_TYPE_TOUCH_DOWN);
    engine->RegisterEnumValue ("UI_EVENT_TYPE", "UI_EVENT_TYPE_POINTER_DOWN", UI_EVENT_TYPE_POINTER_DOWN);
    engine->RegisterEnumValue ("UI_EVENT_TYPE", "UI_EVENT_TYPE_CHANGED", UI_EVENT_TYPE_CHANGED);
    engine->RegisterEnumValue ("UI_EVENT_TYPE", "UI_EVENT_TYPE_RIGHT_POINTER_DOWN", UI_EVENT_TYPE_RIGHT_POINTER_DOWN);
    engine->RegisterEnumValue ("UI_EVENT_TYPE", "UI_EVENT_TYPE_POINTER_MOVE", UI_EVENT_TYPE_POINTER_MOVE);
    engine->RegisterEnumValue ("UI_EVENT_TYPE", "UI_EVENT_TYPE_CUSTOM", UI_EVENT_TYPE_CUSTOM);
    engine->RegisterEnumValue ("UI_EVENT_TYPE", "UI_EVENT_TYPE_TAB_CHANGED", UI_EVENT_TYPE_TAB_CHANGED);
    engine->RegisterEnumValue ("UI_EVENT_TYPE", "UI_EVENT_TYPE_SHORTCUT", UI_EVENT_TYPE_SHORTCUT);
}


void RegisterUI_TEXT_ALIGN (asIScriptEngine *engine)
{
    engine->RegisterEnum ("UI_TEXT_ALIGN");
    engine->RegisterEnumValue ("UI_TEXT_ALIGN", "UI_TEXT_ALIGN_RIGHT", UI_TEXT_ALIGN_RIGHT);
    engine->RegisterEnumValue ("UI_TEXT_ALIGN", "UI_TEXT_ALIGN_CENTER", UI_TEXT_ALIGN_CENTER);
    engine->RegisterEnumValue ("UI_TEXT_ALIGN", "UI_TEXT_ALIGN_LEFT", UI_TEXT_ALIGN_LEFT);
}

void RegisterUI_GRAVITY (asIScriptEngine *engine)
{
    engine->RegisterEnum ("UI_GRAVITY");
    engine->RegisterEnumValue ("UI_GRAVITY", "UI_GRAVITY_TOP_BOTTOM", UI_GRAVITY_TOP_BOTTOM);
    engine->RegisterEnumValue ("UI_GRAVITY", "UI_GRAVITY_TOP", UI_GRAVITY_TOP);
    engine->RegisterEnumValue ("UI_GRAVITY", "UI_GRAVITY_BOTTOM", UI_GRAVITY_BOTTOM);
    engine->RegisterEnumValue ("UI_GRAVITY", "UI_GRAVITY_LEFT", UI_GRAVITY_LEFT);
    engine->RegisterEnumValue ("UI_GRAVITY", "UI_GRAVITY_RIGHT", UI_GRAVITY_RIGHT);
    engine->RegisterEnumValue ("UI_GRAVITY", "UI_GRAVITY_LEFT_RIGHT", UI_GRAVITY_LEFT_RIGHT);
    engine->RegisterEnumValue ("UI_GRAVITY", "UI_GRAVITY_DEFAULT", UI_GRAVITY_DEFAULT);
    engine->RegisterEnumValue ("UI_GRAVITY", "UI_GRAVITY_NONE", UI_GRAVITY_NONE);
    engine->RegisterEnumValue ("UI_GRAVITY", "UI_GRAVITY_ALL", UI_GRAVITY_ALL);
}

void RegisterUI_WIDGET_Z_REL (asIScriptEngine *engine)
{
    engine->RegisterEnum ("UI_WIDGET_Z_REL");
    engine->RegisterEnumValue ("UI_WIDGET_Z_REL", "UI_WIDGET_Z_REL_AFTER", UI_WIDGET_Z_REL_AFTER);
    engine->RegisterEnumValue ("UI_WIDGET_Z_REL", "UI_WIDGET_Z_REL_BEFORE", UI_WIDGET_Z_REL_BEFORE);
}



void RegisterUI_WINDOW_SETTINGS (asIScriptEngine *engine)
{
    engine->RegisterEnum ("UI_WINDOW_SETTINGS");
    engine->RegisterEnumValue ("UI_WINDOW_SETTINGS", "UI_WINDOW_SETTINGS_CLOSE_BUTTON", UI_WINDOW_SETTINGS_CLOSE_BUTTON);
    engine->RegisterEnumValue ("UI_WINDOW_SETTINGS", "UI_WINDOW_SETTINGS_DEFAULT", UI_WINDOW_SETTINGS_DEFAULT);
    engine->RegisterEnumValue ("UI_WINDOW_SETTINGS", "UI_WINDOW_SETTINGS_NONE", UI_WINDOW_SETTINGS_NONE);
    engine->RegisterEnumValue ("UI_WINDOW_SETTINGS", "UI_WINDOW_SETTINGS_RESIZABLE", UI_WINDOW_SETTINGS_RESIZABLE);
    engine->RegisterEnumValue ("UI_WINDOW_SETTINGS", "UI_WINDOW_SETTINGS_CAN_ACTIVATE", UI_WINDOW_SETTINGS_CAN_ACTIVATE);
    engine->RegisterEnumValue ("UI_WINDOW_SETTINGS", "UI_WINDOW_SETTINGS_TITLEBAR", UI_WINDOW_SETTINGS_TITLEBAR);
}


ABargraph * wrapper_ABargraph_constructor_createWidget (bool createWidget = true)
{
    return new ABargraph (Urho3D::GetScriptContext (), createWidget);
}

template <class T> void RegisterABargraph (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true)").CString (), asFUNCTION (wrapper_ABargraph_constructor_createWidget), asCALL_CDECL);
    }

}



ACheckBox * wrapper_ACheckBox_constructor_createWidget (bool createWidget = true)
{
    return new ACheckBox (Urho3D::GetScriptContext (), createWidget);
}

template <class T> void RegisterACheckBox (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true)").CString (), asFUNCTION (wrapper_ACheckBox_constructor_createWidget), asCALL_CDECL);
    }

}



AClickLabel * wrapper_AClickLabel_constructor_createWidget (bool createWidget = true)
{
    return new AClickLabel (Urho3D::GetScriptContext (), createWidget);
}

template <class T> void RegisterAClickLabel (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true)").CString (), asFUNCTION (wrapper_AClickLabel_constructor_createWidget), asCALL_CDECL);
    }

}


AListView * wrapper_AListView_constructor_createWidget (bool createWidget = true)
{
    return new AListView (Urho3D::GetScriptContext (), createWidget);
}

template <class T> void RegisterAListView (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true)").CString (), asFUNCTION (wrapper_AListView_constructor_createWidget), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "uint AddRootItem(const String& text, const String& icon, const String& id) ", asMETHOD (T, AddRootItem), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "uint AddChildItem(uint parentItemID, const String& text, const String& icon, const String& id) ", asMETHOD (T, AddChildItem), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetItemText(const String& id, const String& text) ", asMETHOD (T, SetItemText), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetItemTextSkin(const String& id, const String& skin) ", asMETHOD (T, SetItemTextSkin), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetItemIcon(const String& id, const String& icon) ", asMETHOD (T, SetItemIcon), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void DeleteItemByID(const String& id) ", asMETHOD (T, DeleteItemByID), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void ScrollToSelectedItem() ", asMETHOD (T, ScrollToSelectedItem), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetExpanded(uint itemID, bool value) ", asMETHOD (T, SetExpanded), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "bool GetExpanded(uint itemID) ", asMETHOD (T, GetExpanded), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "bool GetExpandable(uint itemID) ", asMETHOD (T, GetExpandable), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "bool GetMultiSelect() const ", asMETHOD (T, GetMultiSelect), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetMultiSelect(bool value) ", asMETHOD (T, SetMultiSelect), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void DeleteAllItems() ", asMETHOD (T, DeleteAllItems), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SelectItemByID(const String& id, bool selected = true) ", asMETHOD (T, SelectItemByID), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "String GetHoverItemID() ", asMETHOD (T, GetHoverItemID), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "String GetSelectedItemID() ", asMETHOD (T, GetSelectedItemID), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "ASelectList@+ GetRootList() ", asMETHOD (T, GetRootList), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void UpdateItemVisibility() ", asMETHOD (T, UpdateItemVisibility), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SelectAllItems(bool select = true) ", asMETHOD (T, SelectAllItems), asCALL_THISCALL);
 
}


AColorWheel * wrapper_AColorWheel_constructor_createWidget (bool createWidget = true)
{
    return new AColorWheel (Urho3D::GetScriptContext (), createWidget);
}

template <class T> void RegisterAColorWheel (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true)").CString (), asFUNCTION (wrapper_AColorWheel_constructor_createWidget), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "float GetHue () ", asMETHOD (T, GetHue), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "float GetSaturation () ", asMETHOD (T, GetSaturation), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetHueSaturation (float hue, float saturation) ", asMETHOD (T, SetHueSaturation), asCALL_THISCALL);
}

AColorWidget * wrapper_AColorWidget_constructor_createWidget (bool createWidget = true)
{
    return new AColorWidget (Urho3D::GetScriptContext (), createWidget);
}

template <class T> void RegisterAColorWidget (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true)").CString (), asFUNCTION (wrapper_AColorWidget_constructor_createWidget), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "void SetColor (const Color& color) ", asMETHOD (T, SetColor), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetColorString (const String & name) ", asMETHOD (T, SetColorString), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "Color GetColor () const", asMETHOD (T, GetColor), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetAlpha (float value) ", asMETHOD (T, SetAlpha), asCALL_THISCALL);
}



AComponent * wrapper_AComponent_constructor ()
{
    return new AComponent (Urho3D::GetScriptContext ());
}

template <class T> void RegisterAComponent (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    Urho3D::RegisterObject <T> (engine, className);

    if (registerConstructors)
    {

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f ()").CString (), asFUNCTION (wrapper_AComponent_constructor), asCALL_CDECL);
    }

}


AContainer * wrapper_AContainer_constructor_createWidget (bool createWidget = true)
{
    return new AContainer (Urho3D::GetScriptContext (), createWidget);
}

template <class T> void RegisterAContainer (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true)").CString (), asFUNCTION (wrapper_AContainer_constructor_createWidget), asCALL_CDECL);
    }

}


ADockWindow * wrapper_ADockWindow_constructor_createWidget_title_contentptr_minwidth_minheight (bool createWidget = true, const String& title = String::EMPTY, AWidget * contentptr = NULL, int minwidth = 800, int minheight = 400)
{
    return new ADockWindow (Urho3D::GetScriptContext (), createWidget, title, contentptr, minwidth, minheight);
}

template <class T> void RegisterADockWindow (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWindow <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWindow, T> (engine, "AWindow", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true, const String& title = String::EMPTY, AWidget @ contentptr = NULL, int minwidth = 800, int minheight = 400)").CString (), asFUNCTION (wrapper_ADockWindow_constructor_createWidget_title_contentptr_minwidth_minheight), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "void SetDockOrigin (String dockid) ", asMETHOD (T, SetDockOrigin), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "AWidget @+ GetDockContent () ", asMETHOD (T, GetDockContent), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "bool HasDockContent () ", asMETHOD (T, HasDockContent), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void Dock (AWidget @+ target) ", asMETHOD (T, Dock), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void Show (AWidget @+ host, int xpos = 50, int ypos = 50) ", asMETHOD (T, Show), asCALL_THISCALL);
}



AEditField * wrapper_AEditField_constructor_createWidget (bool createWidget = true)
{
    return new AEditField (Urho3D::GetScriptContext (), createWidget);
}

template <class T> void RegisterAEditField (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true)").CString (), asFUNCTION (wrapper_AEditField_constructor_createWidget), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "void AppendText (const String& text, int len = 2147483647, bool clear_undo_redo = false ) ", asMETHOD (T, AppendText), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetTextAlign (UI_TEXT_ALIGN align) ", asMETHOD (T, SetTextAlign), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetAdaptToContentSize (bool adapt) ", asMETHOD (T, SetAdaptToContentSize), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "bool GetAdaptToContentSize () const", asMETHOD (T, GetAdaptToContentSize), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetEditType (UI_EDIT_TYPE type) ", asMETHOD (T, SetEditType), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetReadOnly (bool readonly) ", asMETHOD (T, SetReadOnly), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetStyling (bool styling) ", asMETHOD (T, SetStyling), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetMultiline (bool multiline) ", asMETHOD (T, SetMultiline), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void Reformat (bool update_fragments = false) ", asMETHOD (T, Reformat), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void ScrollTo (int x, int y) ", asMETHOD (T, ScrollTo), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetWrapping (bool wrap) ", asMETHOD (T, SetWrapping), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "bool GetWrapping () ", asMETHOD (T, GetWrapping), asCALL_THISCALL);

    engine->RegisterObjectMethod (className, "void SetPlaceholderText (const String &text) ", asMETHOD (T, SetPlaceholderText), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "const String GetPlaceholderText () ", asMETHOD (T, GetPlaceholderText), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void Undo () ", asMETHOD (T, Undo), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void Redo () ", asMETHOD (T, Redo), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "bool CanUndo () const ", asMETHOD (T, CanUndo), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "bool CanRedo () const ", asMETHOD (T, CanRedo), asCALL_THISCALL);

}

void RegisterUI_EDIT_TYPE (asIScriptEngine *engine)
{
    engine->RegisterEnum ("UI_EDIT_TYPE");
    engine->RegisterEnumValue ("UI_EDIT_TYPE", "UI_EDIT_TYPE_EMAIL", UI_EDIT_TYPE_EMAIL);
    engine->RegisterEnumValue ("UI_EDIT_TYPE", "UI_EDIT_TYPE_SEARCH", UI_EDIT_TYPE_SEARCH);
    engine->RegisterEnumValue ("UI_EDIT_TYPE", "UI_EDIT_TYPE_NUMBER", UI_EDIT_TYPE_NUMBER);
    engine->RegisterEnumValue ("UI_EDIT_TYPE", "UI_EDIT_TYPE_PASSWORD", UI_EDIT_TYPE_PASSWORD);
    engine->RegisterEnumValue ("UI_EDIT_TYPE", "UI_EDIT_TYPE_PHONE", UI_EDIT_TYPE_PHONE);
    engine->RegisterEnumValue ("UI_EDIT_TYPE", "UI_EDIT_TYPE_TEXT", UI_EDIT_TYPE_TEXT);
    engine->RegisterEnumValue ("UI_EDIT_TYPE", "UI_EDIT_TYPE_URL", UI_EDIT_TYPE_URL);
}


AFinderWindow * wrapper_AFinderWindow_constructor_target_id_createWidget (AWidget* target, const String& id, bool createWidget = true)
{
    return new AFinderWindow (Urho3D::GetScriptContext (), target, id, createWidget);
}

template <class T> void RegisterAFinderWindow (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWindow <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWindow, T> (engine, "AWindow", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (AWidget@ target, const String& id, bool createWidget = true)").CString (), asFUNCTION (wrapper_AFinderWindow_constructor_target_id_createWidget), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "void FindFile (const String& title, const String& preset, int dimmer = 0, int width = 0, int height = 0) ", asMETHOD (T, FindFile), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void FindPath (const String& title, const String& preset, int dimmer = 0, int width = 0, int height = 0) ", asMETHOD (T, FindPath), asCALL_THISCALL);
}



AFontDescription * wrapper_AFontDescription_constructor ()
{
    return new AFontDescription (Urho3D::GetScriptContext ());
}

template <class T> void RegisterAFontDescription (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    Urho3D::RegisterObject <T> (engine, className);

    if (registerConstructors)
    {

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f ()").CString (), asFUNCTION (wrapper_AFontDescription_constructor), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "int GetSize () ", asMETHOD (T, GetSize), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetId (const String& id) ", asMETHOD (T, SetId), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetSize (int size) ", asMETHOD (T, SetSize), asCALL_THISCALL);
}



AImageWidget * wrapper_AImageWidget_constructor_createWidget (bool createWidget = true)
{
    return new AImageWidget (Urho3D::GetScriptContext (), createWidget);
}

template <class T> void RegisterAImageWidget (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true)").CString (), asFUNCTION (wrapper_AImageWidget_constructor_createWidget), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "void SetImage (const String& imagePath) ", asMETHOD (T, SetImage), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "int GetImageWidth () const", asMETHOD (T, GetImageWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "int GetImageHeight () const", asMETHOD (T, GetImageHeight), asCALL_THISCALL);
// sprite feature
    engine->RegisterObjectMethod (className, "void SetSprite (const String& imagePath) ", asMETHOD (T, SetSprite), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "int GetSpriteWidth () const", asMETHOD (T, GetSpriteWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "int GetSpriteHeight () const", asMETHOD (T, GetSpriteHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "int GetNumSprites () const", asMETHOD (T, GetNumSprites), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "int GetSpriteSpeed () const", asMETHOD (T, GetSpriteSpeed), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetSpriteSpeed (int speed) ", asMETHOD (T, SetSpriteSpeed), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetSpriteFrame (int frame) ", asMETHOD (T, SetSpriteFrame), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "int GetSpriteFrame () const", asMETHOD (T, GetSpriteFrame), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "bool SpriteMode () const", asMETHOD (T, SpriteMode), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "bool IsRunning () ", asMETHOD (T, IsRunning), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void Begin () ", asMETHOD (T, Begin), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void End () ", asMETHOD (T, End), asCALL_THISCALL);

}


AInlineSelect * wrapper_AInlineSelect_constructor_createWidget (bool createWidget = true)
{
    return new AInlineSelect (Urho3D::GetScriptContext (), createWidget);
}

template <class T> void RegisterAInlineSelect (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true)").CString (), asFUNCTION (wrapper_AInlineSelect_constructor_createWidget), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "void SetLimits (double minimum, double maximum) ", asMETHOD (T, SetLimits), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetStepSize (double step) ", asMETHOD (T, SetStepSize), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "double GetStepSize () ", asMETHOD (T, GetStepSize), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetEditFieldLayoutParams (ALayoutParams@+ params) ", asMETHOD (T, SetEditFieldLayoutParams), asCALL_THISCALL);
}



ALayoutParams * wrapper_ALayoutParams_constructor ()
{
    return new ALayoutParams (Urho3D::GetScriptContext ());
}

ALayout * wrapper_ALayout_constructor_axis_createWidget (bool createWidget = true)
{
    return new ALayout (Urho3D::GetScriptContext (), createWidget);
}

void RegisterUI_LAYOUT_DISTRIBUTION_POSITION (asIScriptEngine *engine)
{
    engine->RegisterEnum ("UI_LAYOUT_DISTRIBUTION_POSITION");
    engine->RegisterEnumValue ("UI_LAYOUT_DISTRIBUTION_POSITION", "UI_LAYOUT_DISTRIBUTION_POSITION_CENTER", UI_LAYOUT_DISTRIBUTION_POSITION_CENTER);
    engine->RegisterEnumValue ("UI_LAYOUT_DISTRIBUTION_POSITION", "UI_LAYOUT_DISTRIBUTION_POSITION_LEFT_TOP", UI_LAYOUT_DISTRIBUTION_POSITION_LEFT_TOP);
    engine->RegisterEnumValue ("UI_LAYOUT_DISTRIBUTION_POSITION", "UI_LAYOUT_DISTRIBUTION_POSITION_RIGHT_BOTTOM", UI_LAYOUT_DISTRIBUTION_POSITION_RIGHT_BOTTOM);
}

template <class T> void RegisterALayoutParams (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    Urho3D::RegisterObject <T> (engine, className);

    if (registerConstructors)
    {

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f ()").CString (), asFUNCTION (wrapper_ALayoutParams_constructor), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "void SetWidth (int width) ", asMETHOD (T, SetWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetHeight (int height) ", asMETHOD (T, SetHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetMinWidth (int width) ", asMETHOD (T, SetMinWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetMinHeight (int height) ", asMETHOD (T, SetMinHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetMaxWidth (int width) ", asMETHOD (T, SetMaxWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetMaxHeight (int height) ", asMETHOD (T, SetMaxHeight), asCALL_THISCALL);
}

template <class T> void RegisterALayout (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true)").CString (), asFUNCTION (wrapper_ALayout_constructor_axis_createWidget), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "void SetLayoutSize (UI_LAYOUT_SIZE size) ", asMETHOD (T, SetLayoutSize), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetLayoutPosition (UI_LAYOUT_POSITION position) ", asMETHOD (T, SetLayoutPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetLayoutDistribution (UI_LAYOUT_DISTRIBUTION distribution) ", asMETHOD (T, SetLayoutDistribution), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetLayoutDistributionPosition (UI_LAYOUT_DISTRIBUTION_POSITION distribution_pos) ", asMETHOD (T, SetLayoutDistributionPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetLayoutConfig (const String & settings) ", asMETHOD (T, SetLayoutConfig), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "String GetLayoutConfig () ", asMETHOD (T, GetLayoutConfig), asCALL_THISCALL);
}

void RegisterUI_LAYOUT_POSITION (asIScriptEngine *engine)
{
    engine->RegisterEnum ("UI_LAYOUT_POSITION");
    engine->RegisterEnumValue ("UI_LAYOUT_POSITION", "UI_LAYOUT_POSITION_LEFT_TOP", UI_LAYOUT_POSITION_LEFT_TOP);
    engine->RegisterEnumValue ("UI_LAYOUT_POSITION", "UI_LAYOUT_POSITION_CENTER", UI_LAYOUT_POSITION_CENTER);
    engine->RegisterEnumValue ("UI_LAYOUT_POSITION", "UI_LAYOUT_POSITION_GRAVITY", UI_LAYOUT_POSITION_GRAVITY);
    engine->RegisterEnumValue ("UI_LAYOUT_POSITION", "UI_LAYOUT_POSITION_RIGHT_BOTTOM", UI_LAYOUT_POSITION_RIGHT_BOTTOM);
}

void RegisterUI_LAYOUT_SIZE (asIScriptEngine *engine)
{
    engine->RegisterEnum ("UI_LAYOUT_SIZE");
    engine->RegisterEnumValue ("UI_LAYOUT_SIZE", "UI_LAYOUT_SIZE_GRAVITY", UI_LAYOUT_SIZE_GRAVITY);
    engine->RegisterEnumValue ("UI_LAYOUT_SIZE", "UI_LAYOUT_SIZE_PREFERRED", UI_LAYOUT_SIZE_PREFERRED);
    engine->RegisterEnumValue ("UI_LAYOUT_SIZE", "UI_LAYOUT_SIZE_AVAILABLE", UI_LAYOUT_SIZE_AVAILABLE);
}

void RegisterUI_LAYOUT_DISTRIBUTION (asIScriptEngine *engine)
{
    engine->RegisterEnum ("UI_LAYOUT_DISTRIBUTION");
    engine->RegisterEnumValue ("UI_LAYOUT_DISTRIBUTION", "UI_LAYOUT_DISTRIBUTION_AVAILABLE", UI_LAYOUT_DISTRIBUTION_AVAILABLE);
    engine->RegisterEnumValue ("UI_LAYOUT_DISTRIBUTION", "UI_LAYOUT_DISTRIBUTION_PREFERRED", UI_LAYOUT_DISTRIBUTION_PREFERRED);
    engine->RegisterEnumValue ("UI_LAYOUT_DISTRIBUTION", "UI_LAYOUT_DISTRIBUTION_GRAVITY", UI_LAYOUT_DISTRIBUTION_GRAVITY);
}


AMenuItem * wrapper_AMenuItem_constructor_str_id_shortcut_skinBg (const String& str = String::EMPTY, const String& id = String::EMPTY, const String& shortcut = String::EMPTY, const String& skinBg = String::EMPTY)
{
    return new AMenuItem (Urho3D::GetScriptContext (), str, id, shortcut, skinBg);
}

AMenuItemSource * wrapper_AMenuItemSource_constructor ()
{
    return new AMenuItemSource (Urho3D::GetScriptContext ());
}

template <class T> void RegisterAMenuItem (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterASelectItem <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <ASelectItem, T> (engine, "ASelectItem", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (const String& str = String::EMPTY, const String& id = String::EMPTY, const String& shortcut = String::EMPTY, const String& skinBg = String::EMPTY)").CString (), asFUNCTION (wrapper_AMenuItem_constructor_str_id_shortcut_skinBg), asCALL_CDECL);
    }

}

template <class T> void RegisterAMenuItemSource (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterASelectItemSource <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <ASelectItemSource, T> (engine, "ASelectItemSource", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f ()").CString (), asFUNCTION (wrapper_AMenuItemSource_constructor), asCALL_CDECL);
    }

}



AMenuWindow * wrapper_AMenuWindow_constructor_target_id (AWidget* target, const String& id = String::EMPTY)
{
    return new AMenuWindow (Urho3D::GetScriptContext (), target, id);
}

template <class T> void RegisterAMenuWindow (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (AWidget@ target, const String& id = String::EMPTY)").CString (), asFUNCTION (wrapper_AMenuWindow_constructor_target_id), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "void ShowMenu (ASelectItemSource@+ source, int xx, int yy) ", asMETHOD (T, ShowMenu), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void Close () ", asMETHOD (T, Close), asCALL_THISCALL);
}



AMessageWindow * wrapper_AMessageWindow_constructor_target_id_createWidget (AWidget* target, const String& id, bool createWidget = true)
{
    return new AMessageWindow (Urho3D::GetScriptContext (), target, id, createWidget);
}

template <class T> void RegisterAMessageWindow (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWindow <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWindow, T> (engine, "AWindow", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (AWidget@ target, const String& id, bool createWidget = true)").CString (), asFUNCTION (wrapper_AMessageWindow_constructor_target_id_createWidget), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "void Show (const String& title, const String& message, UI_MESSAGEWINDOW_SETTINGS settings, bool dimmer, int width, int height) ", asMETHOD (T, Show), asCALL_THISCALL);
}

void RegisterUI_MESSAGEWINDOW_SETTINGS (asIScriptEngine *engine)
{
    engine->RegisterEnum ("UI_MESSAGEWINDOW_SETTINGS");
    engine->RegisterEnumValue ("UI_MESSAGEWINDOW_SETTINGS", "UI_MESSAGEWINDOW_SETTINGS_OK", UI_MESSAGEWINDOW_SETTINGS_OK);
    engine->RegisterEnumValue ("UI_MESSAGEWINDOW_SETTINGS", "UI_MESSAGEWINDOW_SETTINGS_YES_NO", UI_MESSAGEWINDOW_SETTINGS_YES_NO);
    engine->RegisterEnumValue ("UI_MESSAGEWINDOW_SETTINGS", "UI_MESSAGEWINDOW_SETTINGS_OK_CANCEL", UI_MESSAGEWINDOW_SETTINGS_OK_CANCEL);
    engine->RegisterEnumValue ("UI_MESSAGEWINDOW_SETTINGS", "UI_MESSAGEWINDOW_SETTINGS_NONE", UI_MESSAGEWINDOW_SETTINGS_NONE);
}



AMultiItem * wrapper_AMultiItem_constructor_colid_widgettype_str_colwidth_colheight (const String& colid, const String& widgettype, const String& str, int colwidth, int colheight)
{
    return new AMultiItem (Urho3D::GetScriptContext (), colid, widgettype, str, colwidth, colheight);
}

AMultiItemSource * wrapper_AMultiItemSource_constructor ()
{
    return new AMultiItemSource (Urho3D::GetScriptContext ());
}

template <class T> void RegisterAMultiItemSource (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterASelectItemSource <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <ASelectItemSource, T> (engine, "ASelectItemSource", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f ()").CString (), asFUNCTION (wrapper_AMultiItemSource_constructor), asCALL_CDECL);
    }

}

template <class T> void RegisterAMultiItem (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterASelectItem <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <ASelectItem, T> (engine, "ASelectItem", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (const String& colid, const String& widgettype, const String& str, int colwidth, int colheight)").CString (), asFUNCTION (wrapper_AMultiItem_constructor_colid_widgettype_str_colwidth_colheight), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "void AddColumn (const String& widgettype, const String& str, int colwidth) ", asMETHOD (T, AddColumn), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "const String& GetColumnStr (int col) ", asMETHOD (T, GetColumnStr), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "const String& GetColumnWidget (int col) ", asMETHOD (T, GetColumnWidget), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "int GetColumnWidth (int col) ", asMETHOD (T, GetColumnWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "int GetNumColumns () ", asMETHOD (T, GetNumColumns), asCALL_THISCALL);
}




APopupWindow * wrapper_APopupWindow_constructor_createWidget_target_id (bool createWidget, AWidget* target = nullptr, const String& id = String::EMPTY)
{
    return new APopupWindow (Urho3D::GetScriptContext (), createWidget, target, id);
}

template <class T> void RegisterAPopupWindow (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget, AWidget@ target = nullptr, const String& id = String::EMPTY)").CString (), asFUNCTION (wrapper_APopupWindow_constructor_createWidget_target_id), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "void Close () ", asMETHOD (T, Close), asCALL_THISCALL);
}


void RegisterUI_SIZE_DEP (asIScriptEngine *engine)
{
    engine->RegisterEnum ("UI_SIZE_DEP");
    engine->RegisterEnumValue ("UI_SIZE_DEP", "UI_SIZE_DEP_BOTH", UI_SIZE_DEP_BOTH);
    engine->RegisterEnumValue ("UI_SIZE_DEP", "UI_SIZE_DEP_WIDTH_DEPEND_ON_HEIGHT", UI_SIZE_DEP_WIDTH_DEPEND_ON_HEIGHT);
    engine->RegisterEnumValue ("UI_SIZE_DEP", "UI_SIZE_DEP_NONE", UI_SIZE_DEP_NONE);
    engine->RegisterEnumValue ("UI_SIZE_DEP", "UI_SIZE_DEP_HEIGHT_DEPEND_ON_WIDTH", UI_SIZE_DEP_HEIGHT_DEPEND_ON_WIDTH);
}


APromptWindow * wrapper_APromptWindow_constructor_target_id_createWidget (AWidget* target, const String& id, bool createWidget = true)
{
    return new APromptWindow (Urho3D::GetScriptContext (), target, id, createWidget);
}

template <class T> void RegisterAPromptWindow (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWindow <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWindow, T> (engine, "AWindow", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (AWidget@ target, const String& id, bool createWidget = true)").CString (), asFUNCTION (wrapper_APromptWindow_constructor_target_id_createWidget), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "void Show (const String& title, const String& message, const String& preset, int dimmer = 0, int width = 0, int height = 0) ", asMETHOD (T, Show), asCALL_THISCALL);
}



APulldownMenu * wrapper_APulldownMenu_constructor_createWidget (bool createWidget = true)
{
    return new APulldownMenu (Urho3D::GetScriptContext (), createWidget);
}

template <class T> void RegisterAPulldownMenu (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAButton <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AButton, T> (engine, "AButton", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true)").CString (), asFUNCTION (wrapper_APulldownMenu_constructor_createWidget), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "void SetSource (ASelectItemSource@+ source) ", asMETHOD (T, SetSource), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "const String& GetSelectedId () ", asMETHOD (T, GetSelectedId), asCALL_THISCALL);

    engine->RegisterObjectMethod (className, "int NumMenuItems() const ", asMETHOD (T, NumMenuItems), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "String GetMenuItemId( int index ) ", asMETHOD (T, GetMenuItemId), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "String GetMenuItemString( int index ) ", asMETHOD (T, GetMenuItemString), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "int GetMenuItemState( int index ) ", asMETHOD (T, GetMenuItemState), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetMenuItemString( int index, String newstr ) ", asMETHOD (T, SetMenuItemString), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetMenuItemState( int index, int newstate ) ", asMETHOD (T, SetMenuItemState), asCALL_THISCALL);

}


ARadioButton * wrapper_ARadioButton_constructor_createWidget (bool createWidget = true)
{
    return new ARadioButton (Urho3D::GetScriptContext (), createWidget);
}

template <class T> void RegisterARadioButton (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true)").CString (), asFUNCTION (wrapper_ARadioButton_constructor_createWidget), asCALL_CDECL);
    }

}


ASceneView * wrapper_ASceneView_constructor_createWidget (bool createWidget = true)
{
    return new ASceneView (Urho3D::GetScriptContext (), createWidget);
}

template <class T> void RegisterASceneView (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true)").CString (), asFUNCTION (wrapper_ASceneView_constructor_createWidget), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "void OnResize (const IntVector2& newSize) ", asMETHOD (T, OnResize), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetView (Scene@+ scene, Camera@+ camera) ", asMETHOD (T, SetView), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetFormat (uint format) ", asMETHOD (T, SetFormat), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetAutoUpdate (bool enable) ", asMETHOD (T, SetAutoUpdate), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void QueueUpdate () ", asMETHOD (T, QueueUpdate), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "uint GetFormat () const", asMETHOD (T, GetFormat), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "bool GetAutoUpdate () const", asMETHOD (T, GetAutoUpdate), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "Scene@+ GetScene () const", asMETHOD (T, GetScene), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "Node@+ GetCameraNode () const", asMETHOD (T, GetCameraNode), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "Texture2D@+ GetRenderTexture () const", asMETHOD (T, GetRenderTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "Texture2D@+ GetDepthTexture () const", asMETHOD (T, GetDepthTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "Viewport@+ GetViewport () const", asMETHOD (T, GetViewport), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetResizeRequired () ", asMETHOD (T, SetResizeRequired), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "const IntVector2& GetSize () const", asMETHOD (T, GetSize), asCALL_THISCALL);
}


AScrollBar * wrapper_AScrollBar_constructor_createWidget (bool createWidget = true)
{
    return new AScrollBar (Urho3D::GetScriptContext (), createWidget);
}

template <class T> void RegisterAScrollBar (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true)").CString (), asFUNCTION (wrapper_AScrollBar_constructor_createWidget), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "void SetLimits (double minimum, double maximum, double visible) ", asMETHOD (T, SetLimits), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "double GetMinValue () const", asMETHOD (T, GetMinValue), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "double GetMaxValue () const", asMETHOD (T, GetMaxValue), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "double GetVisible () const", asMETHOD (T, GetVisible), asCALL_THISCALL);
}



AScrollContainer * wrapper_AScrollContainer_constructor_createWidget (bool createWidget = true)
{
    return new AScrollContainer (Urho3D::GetScriptContext (), createWidget);
}

template <class T> void RegisterAScrollContainer (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true)").CString (), asFUNCTION (wrapper_AScrollContainer_constructor_createWidget), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "void SetScrollMode (UI_SCROLL_MODE mode) ", asMETHOD (T, SetScrollMode), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "UI_SCROLL_MODE GetScrollMode () ", asMETHOD (T, GetScrollMode), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetAdaptToContentSize (bool adapt) ", asMETHOD (T, SetAdaptToContentSize), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "bool GetAdaptToContentSize () ", asMETHOD (T, GetAdaptToContentSize), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetAdaptContentSize (bool adapt) ", asMETHOD (T, SetAdaptContentSize), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "bool GetAdaptContentSize () ", asMETHOD (T, GetAdaptContentSize), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void ScrollTo (int x, int y) ", asMETHOD (T, ScrollTo), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "int GetScrollX () ", asMETHOD (T, GetScrollX), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "int GetScrollY () ", asMETHOD (T, GetScrollY), asCALL_THISCALL);
}

void RegisterUI_SCROLL_MODE (asIScriptEngine *engine)
{
    engine->RegisterEnum ("UI_SCROLL_MODE");
    engine->RegisterEnumValue ("UI_SCROLL_MODE", "UI_SCROLL_MODE_Y_AUTO", UI_SCROLL_MODE_Y_AUTO);
    engine->RegisterEnumValue ("UI_SCROLL_MODE", "UI_SCROLL_MODE_Y", UI_SCROLL_MODE_Y);
    engine->RegisterEnumValue ("UI_SCROLL_MODE", "UI_SCROLL_MODE_X_AUTO_Y_AUTO", UI_SCROLL_MODE_X_AUTO_Y_AUTO);
    engine->RegisterEnumValue ("UI_SCROLL_MODE", "UI_SCROLL_MODE_X_Y", UI_SCROLL_MODE_X_Y);
    engine->RegisterEnumValue ("UI_SCROLL_MODE", "UI_SCROLL_MODE_OFF", UI_SCROLL_MODE_OFF);
}


ASection * wrapper_ASection_constructor_createWidget (bool createWidget = true)
{
    return new ASection (Urho3D::GetScriptContext (), createWidget);
}

template <class T> void RegisterASection (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true)").CString (), asFUNCTION (wrapper_ASection_constructor_createWidget), asCALL_CDECL);
    }

}



ASelectDropdown * wrapper_ASelectDropdown_constructor_createWidget (bool createWidget = true)
{
    return new ASelectDropdown (Urho3D::GetScriptContext (), createWidget);
}

template <class T> void RegisterASelectDropdown (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAButton <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AButton, T> (engine, "AButton", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true)").CString (), asFUNCTION (wrapper_ASelectDropdown_constructor_createWidget), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "void SetSource (ASelectItemSource@+ source) ", asMETHOD (T, SetSource), asCALL_THISCALL);
}



ASelectList * wrapper_ASelectList_constructor_createWidget (bool createWidget = true)
{
    return new ASelectList (Urho3D::GetScriptContext (), createWidget);
}

template <class T> void RegisterASelectList (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true)").CString (), asFUNCTION (wrapper_ASelectList_constructor_createWidget), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "void SetFilter (const String& filter) ", asMETHOD (T, SetFilter), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetSource (ASelectItemSource@+ source) ", asMETHOD (T, SetSource), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void InvalidateList () ", asMETHOD (T, InvalidateList), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetValue (int value) ", asMETHOD (T, SetValue), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "String GetHoverItemID () ", asMETHOD (T, GetHoverItemID), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "String GetSelectedItemID () ", asMETHOD (T, GetSelectedItemID), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void ScrollToSelectedItem () ", asMETHOD (T, ScrollToSelectedItem), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "String GetItemID (int index) ", asMETHOD (T, GetItemID), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "bool GetItemSelected (int index) ", asMETHOD (T, GetItemSelected), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "int GetNumItems () const", asMETHOD (T, GetNumItems), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SelectItem (int index, bool selected = true) ", asMETHOD (T, SelectItem), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SelectNextItem () ", asMETHOD (T, SelectNextItem), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SelectPreviousItem () ", asMETHOD (T, SelectPreviousItem), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetAListView (bool value) ", asMETHOD (T, SetAListView), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "String GetItemString (int index) ", asMETHOD (T, GetItemString), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "String GetSelectedItemString () ", asMETHOD (T, GetSelectedItemString), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "bool AddItem (int index, const String& str, const String& id = String::EMPTY) ", asMETHOD (T, AddItem), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void DeleteItem (int index) ", asMETHOD (T, DeleteItem), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void DeleteAllItems () ", asMETHOD (T, DeleteAllItems), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "int FindId (int idnum) ", asMETHOD (T, FindId), asCALL_THISCALL);
}



ASeparator * wrapper_ASeparator_constructor_createWidget (bool createWidget = true)
{
    return new ASeparator (Urho3D::GetScriptContext (), createWidget);
}

template <class T> void RegisterASeparator (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true)").CString (), asFUNCTION (wrapper_ASeparator_constructor_createWidget), asCALL_CDECL);
    }

}


ADimmer * wrapper_ADimmer_constructor_createWidget (bool createWidget = true)
{
    return new ADimmer (Urho3D::GetScriptContext (), createWidget);
}

template <class T> void RegisterADimmer (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true)").CString (), asFUNCTION (wrapper_ADimmer_constructor_createWidget), asCALL_CDECL);
    }

}

AButtonGrid * wrapper_AButtonGrid_constructor_createWidget (int numRows=0, int numColumns=0, int margin=0, bool createWidget = true)
{
    return new AButtonGrid (Urho3D::GetScriptContext (), numRows, numColumns, margin, createWidget);
}

template <class T> void RegisterAButtonGrid (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (int numRows=0, int numColumns=0, int margin=0, bool createWidget = true) ").CString (), asFUNCTION (wrapper_AButtonGrid_constructor_createWidget), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "String GetGridId( int row, int column ) ", asMETHOD (T, GetGridId), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetGridText ( int row, int column, String str ) ", asMETHOD (T, SetGridText), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "String GetGridText( int row, int column ) ", asMETHOD (T, GetGridText), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "AWidget@+ GetGridWidget( int row, int column ) ", asMETHOD (T, GetGridWidget), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "int AddGridText ( String str ) ", asMETHOD (T, AddGridText), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void ResetAddCount() ", asMETHOD (T, ResetAddCount), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "AWidget@+ AtGridWidget( int count ) ", asMETHOD (T, AtGridWidget), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "String AtGridText( int count ) ", asMETHOD (T, AtGridText), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void DisableEmptyButtons() ", asMETHOD (T, DisableEmptyButtons), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "int GetNumRows() const ", asMETHOD (T, GetNumRows), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "int GetNumColumns() const ", asMETHOD (T, GetNumColumns), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "int GetRowHeight() const ", asMETHOD (T, GetRowHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "int GetColumnWidth() const ", asMETHOD (T, GetColumnWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "int GetMargin() const ", asMETHOD (T, GetMargin), asCALL_THISCALL);

}




ASkinImage * wrapper_ASkinImage_constructor_bitmapID_createWidget (const String& bitmapID, bool createWidget = true)
{
    return new ASkinImage (Urho3D::GetScriptContext (), bitmapID, createWidget);
}

template <class T> void RegisterASkinImage (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (const String& bitmapID, bool createWidget = true)").CString (), asFUNCTION (wrapper_ASkinImage_constructor_bitmapID_createWidget), asCALL_CDECL);
    }

}




ASlider * wrapper_ASlider_constructor_createWidget (bool createWidget = true)
{
    return new ASlider (Urho3D::GetScriptContext (), createWidget);
}

template <class T> void RegisterASlider (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true)").CString (), asFUNCTION (wrapper_ASlider_constructor_createWidget), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "void SetLimits (double minimum, double maximum) ", asMETHOD (T, SetLimits), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "double GetMinValue () const", asMETHOD (T, GetMinValue), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "double GetMaxValue () const", asMETHOD (T, GetMaxValue), asCALL_THISCALL);
}




ATabContainer * wrapper_ATabContainer_constructor_createWidget (bool createWidget = true)
{
    return new ATabContainer (Urho3D::GetScriptContext (), createWidget);
}

template <class T> void RegisterATabContainer (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true)").CString (), asFUNCTION (wrapper_ATabContainer_constructor_createWidget), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "int GetNumPages () ", asMETHOD (T, GetNumPages), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetCurrentPage (int page) ", asMETHOD (T, SetCurrentPage), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "AWidget@+ GetCurrentPageWidget () ", asMETHOD (T, GetCurrentPageWidget), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "int GetCurrentPage () ", asMETHOD (T, GetCurrentPage), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "bool DeletePage (int page) ", asMETHOD (T, DeletePage), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void AddTabPageFile (const String & tabname, const String & layoutFile, bool selecttab = true) ", asMETHOD (T, AddTabPageFile), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void AddTabPageWidget (const String & tabname, AWidget @+ widget, bool selecttab = true) ", asMETHOD (T, AddTabPageWidget), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void UndockPage (int page) ", asMETHOD (T, UndockPage), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "bool DockWindow (String windowTitle) ", asMETHOD (T, DockWindow), asCALL_THISCALL);

    engine->RegisterObjectMethod (className, "ALayout@+ GetTabLayout () ", asMETHOD (T, GetTabLayout), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "AWidget@+ GetPageTab (int page) ", asMETHOD (T, GetPageTab), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "AWidget@+ GetPageContent (int page) ", asMETHOD (T, GetPageContent), asCALL_THISCALL);
}




ATextField * wrapper_ATextField_constructor_createWidget (bool createWidget = true)
{
    return new ATextField (Urho3D::GetScriptContext (), createWidget);
}

template <class T> void RegisterATextField (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true)").CString (), asFUNCTION (wrapper_ATextField_constructor_createWidget), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "void SetTextAlign (UI_TEXT_ALIGN align) ", asMETHOD (T, SetTextAlign), asCALL_THISCALL);
}



ATextureWidget * wrapper_ATextureWidget_constructor_createWidget (bool createWidget = true)
{
    return new ATextureWidget (Urho3D::GetScriptContext (), createWidget);
}

template <class T> void RegisterATextureWidget (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true)").CString (), asFUNCTION (wrapper_ATextureWidget_constructor_createWidget), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "void SetTexture (Texture @+ texture) ", asMETHOD (T, SetTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "Texture@+ GetTexture () ", asMETHOD (T, GetTexture), asCALL_THISCALL);
}



AView * wrapper_AView_constructor ()
{
    return new AView (Urho3D::GetScriptContext ());
}

template <class T> void RegisterAView (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f ()").CString (), asFUNCTION (wrapper_AView_constructor), asCALL_CDECL);
    }

}




AUI * wrapper_AUI_constructor ()
{
    return new AUI (Urho3D::GetScriptContext ());
}

AUI *wrapper_AUI ()
{
    return Urho3D::GetScriptContext ()->GetSubsystem <AUI> ();
}

template <class T> void RegisterAUI (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    Urho3D::RegisterObject <T> (engine, className);

    if (registerConstructors)
    {

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f ()").CString (), asFUNCTION (wrapper_AUI_constructor), asCALL_CDECL);
    }

    engine->RegisterGlobalFunction ("AUI @+ get_AUI ()", asFUNCTION (wrapper_AUI), asCALL_CDECL);

    engine->RegisterObjectMethod (className, "AWidget@+ GetRootAWidget () ", asMETHOD (T, GetRootAWidget), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetKeyboardDisabled (bool disabled) ", asMETHOD (T, SetKeyboardDisabled), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetInputDisabled (bool disabled) ", asMETHOD (T, SetInputDisabled), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void Initialize (const String& languageFile) ", asMETHOD (T, Initialize), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void LoadSkin (const String& skin, const String& overrideSkin = String::EMPTY) ", asMETHOD (T, LoadSkin), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void LoadDefaultPlayerSkin () ", asMETHOD (T, LoadDefaultPlayerSkin), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void AddFont (const String& fontFile, const String & name) ", asMETHOD (T, AddFont), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetDefaultFont (const String& name, int size) ", asMETHOD (T, SetDefaultFont), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void GetTBIDString (uint id, String& value) ", asMETHOD (T, GetTBIDString), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "bool GetFocusedWidget () ", asMETHOD (T, GetFocusedWidget), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "AWidget@+ GetWidgetAt (int x, int y, bool include_children) ", asMETHOD (T, GetWidgetAt), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "bool GetBlockChangedEvents () const", asMETHOD (T, GetBlockChangedEvents), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetBlockChangedEvents (bool blocked = true) ", asMETHOD (T, SetBlockChangedEvents), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "AWidget@+ GetHoveredWidget () ", asMETHOD (T, GetHoveredWidget), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "AView@+ GetFocusedView () const", asMETHOD (T, GetFocusedView), asCALL_THISCALL);
}

// Main API called from Script.cpp
void RegisterAUIAPI(asIScriptEngine* engine)
{
// do we need these?
    engine->RegisterObjectType ("AUI", 0, asOBJ_REF);
    engine->RegisterObjectType ("ABargraph", 0, asOBJ_REF);
    engine->RegisterObjectType ("AButton", 0, asOBJ_REF);
    engine->RegisterObjectType ("ACheckBox", 0, asOBJ_REF);
    engine->RegisterObjectType ("AClickLabel", 0, asOBJ_REF);
    engine->RegisterObjectType ("AColorWheel", 0, asOBJ_REF);
    engine->RegisterObjectType ("AColorWidget", 0, asOBJ_REF);
    engine->RegisterObjectType ("AComponent", 0, asOBJ_REF);
    engine->RegisterObjectType ("AContainer", 0, asOBJ_REF);
    engine->RegisterObjectType ("ADockWindow", 0, asOBJ_REF);
    engine->RegisterObjectType ("AEditField", 0, asOBJ_REF);
    engine->RegisterObjectType ("AFinderWindow", 0, asOBJ_REF);
    engine->RegisterObjectType ("AFontDescription", 0, asOBJ_REF);
    engine->RegisterObjectType ("AImageWidget", 0, asOBJ_REF);
    engine->RegisterObjectType ("AInlineSelect", 0, asOBJ_REF);
    engine->RegisterObjectType ("ALayoutParams", 0, asOBJ_REF);
    engine->RegisterObjectType ("ALayout", 0, asOBJ_REF);
    engine->RegisterObjectType ("AMenuItem", 0, asOBJ_REF);
    engine->RegisterObjectType ("AMenuItemSource", 0, asOBJ_REF);
    engine->RegisterObjectType ("AMenuWindow", 0, asOBJ_REF);
    engine->RegisterObjectType ("AMessageWindow", 0, asOBJ_REF);
    engine->RegisterObjectType ("AMultiItem", 0, asOBJ_REF);
    engine->RegisterObjectType ("AMultiItemSource", 0, asOBJ_REF);
    engine->RegisterObjectType ("APopupWindow", 0, asOBJ_REF);
    engine->RegisterObjectType ("APromptWindow", 0, asOBJ_REF);
    engine->RegisterObjectType ("APulldownMenu", 0, asOBJ_REF);
    engine->RegisterObjectType ("ARadioButton", 0, asOBJ_REF);
    engine->RegisterObjectType ("ASceneView", 0, asOBJ_REF);
    engine->RegisterObjectType ("AScrollBar", 0, asOBJ_REF);
    engine->RegisterObjectType ("AScrollContainer", 0, asOBJ_REF);
    engine->RegisterObjectType ("ASection", 0, asOBJ_REF);
    engine->RegisterObjectType ("ASelectDropdown", 0, asOBJ_REF);
    engine->RegisterObjectType ("ASelectItem", 0, asOBJ_REF);
    engine->RegisterObjectType ("ASelectItemSource", 0, asOBJ_REF);
    engine->RegisterObjectType ("ASelectList", 0, asOBJ_REF);
    engine->RegisterObjectType ("ASeparator", 0, asOBJ_REF);
    engine->RegisterObjectType ("ADimmer", 0, asOBJ_REF);
    engine->RegisterObjectType ("AListView", 0, asOBJ_REF);
    engine->RegisterObjectType ("AButtonGrid", 0, asOBJ_REF);
    engine->RegisterObjectType ("ASkinImage", 0, asOBJ_REF);
    engine->RegisterObjectType ("ASlider", 0, asOBJ_REF);
    engine->RegisterObjectType ("ATabContainer", 0, asOBJ_REF);
    engine->RegisterObjectType ("ATextField", 0, asOBJ_REF);
    engine->RegisterObjectType ("ATextureWidget", 0, asOBJ_REF);
    engine->RegisterObjectType ("AView", 0, asOBJ_REF);
    engine->RegisterObjectType ("AWidget", 0, asOBJ_REF);
    engine->RegisterObjectType ("AWindow", 0, asOBJ_REF);
// our enums
    RegisterUI_EDIT_TYPE (engine);
    RegisterUI_LAYOUT_SIZE (engine);
    RegisterUI_LAYOUT_DISTRIBUTION (engine);
    RegisterUI_LAYOUT_POSITION (engine);
    RegisterUI_LAYOUT_DISTRIBUTION_POSITION (engine);
    RegisterUI_MESSAGEWINDOW_SETTINGS (engine);
    RegisterUI_SIZE_DEP (engine);
    RegisterUI_SCROLL_MODE (engine);
    RegisterUI_WIDGET_VISIBILITY (engine);
    RegisterUI_GRAVITY (engine);
    RegisterUI_EVENT_TYPE (engine);
    RegisterUI_WIDGET_Z_REL (engine);
    RegisterUI_TEXT_ALIGN (engine);
    RegisterUI_WIDGET_STATE (engine);
    RegisterUI_AXIS (engine);
    RegisterUI_WINDOW_SETTINGS (engine);
// our classes
    RegisterAUI <AUI> (engine, "AUI", true);
    RegisterABargraph <ABargraph> (engine, "ABargraph", true);
    RegisterAButton <AButton> (engine, "AButton", true);
    RegisterACheckBox <ACheckBox> (engine, "ACheckBox", true);
    RegisterAClickLabel <AClickLabel> (engine, "AClickLabel", true);
    RegisterAColorWheel <AColorWheel> (engine, "AColorWheel", true);
    RegisterAColorWidget <AColorWidget> (engine, "AColorWidget", true);
    RegisterAComponent <AComponent> (engine, "AComponent", true);
    RegisterAContainer <AContainer> (engine, "AContainer", true);
    RegisterADockWindow <ADockWindow> (engine, "ADockWindow", true);
    RegisterAEditField <AEditField> (engine, "AEditField", true);
    RegisterAFinderWindow <AFinderWindow> (engine, "AFinderWindow", true);
    RegisterAFontDescription <AFontDescription> (engine, "AFontDescription", true);
    RegisterAImageWidget <AImageWidget> (engine, "AImageWidget", true);
    RegisterAInlineSelect <AInlineSelect> (engine, "AInlineSelect", true);
    RegisterALayoutParams <ALayoutParams> (engine, "ALayoutParams", true);
    RegisterALayout <ALayout> (engine, "ALayout", true);
    RegisterAMenuItem <AMenuItem> (engine, "AMenuItem", true);
    RegisterAMenuItemSource <AMenuItemSource> (engine, "AMenuItemSource", true);
    RegisterAMenuWindow <AMenuWindow> (engine, "AMenuWindow", true);
    RegisterAMessageWindow <AMessageWindow> (engine, "AMessageWindow", true);
    RegisterAMultiItem <AMultiItem> (engine, "AMultiItem", true);
    RegisterAMultiItemSource <AMultiItemSource> (engine, "AMultiItemSource", true);
    RegisterAPopupWindow <APopupWindow> (engine, "APopupWindow", true);
    RegisterAPromptWindow <APromptWindow> (engine, "APromptWindow", true);
    RegisterAPulldownMenu <APulldownMenu> (engine, "APulldownMenu", true);
    RegisterARadioButton <ARadioButton> (engine, "ARadioButton", true);
    RegisterASceneView <ASceneView> (engine, "ASceneView", true);
    RegisterAScrollBar <AScrollBar> (engine, "AScrollBar", true);
    RegisterAScrollContainer <AScrollContainer> (engine, "AScrollContainer", true);
    RegisterASection <ASection> (engine, "ASection", true);
    RegisterASelectDropdown <ASelectDropdown> (engine, "ASelectDropdown", true);
    RegisterASelectItem <ASelectItem> (engine, "ASelectItem", true);
    RegisterASelectItemSource <ASelectItemSource> (engine, "ASelectItemSource", true);
    RegisterASelectList <ASelectList> (engine, "ASelectList", true);
    RegisterASeparator <ASeparator> (engine, "ASeparator", true);
    RegisterADimmer <ADimmer> (engine, "ADimmer", true);
    RegisterAListView <AListView> (engine, "AListView", true);
    RegisterAButtonGrid <AButtonGrid> (engine, "AButtonGrid", true);
    RegisterASkinImage <ASkinImage> (engine, "ASkinImage", true);
    RegisterASlider <ASlider> (engine, "ASlider", true);
    RegisterATabContainer <ATabContainer> (engine, "ATabContainer", true);
    RegisterATextField <ATextField> (engine, "ATextField", true);
    RegisterATextureWidget <ATextureWidget> (engine, "ATextureWidget", true);
    RegisterAView <AView> (engine, "AView", true);
    RegisterAWidget <AWidget> (engine, "AWidget", true);
    RegisterAWindow <AWindow> (engine, "AWindow", true);

}


}



