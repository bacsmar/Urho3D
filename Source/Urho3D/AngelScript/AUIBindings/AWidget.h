#pragma once
#include <../AngelScript/Script.h>
#include <../ThirdParty/AngelScript/angelscript.h>
#include <../AngelScript/APITemplates.h>
#include <../AUI/AWidget.h>

namespace Bindings
{

using namespace Urho3D;

AWidget * wrapper_AWidget_constructor_createWidget (bool createWidget = true)
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

template <class T> void RegisterAWidget (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    Urho3D::RegisterObject <T> (engine, className);

    if (registerConstructors)
    {

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true)").CString (), asFUNCTION (wrapper_AWidget_constructor_createWidget), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "bool Load (const String& filename) ", asMETHOD (T, Load), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "const String& GetId () ", asMETHOD (T, GetId), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "const String GetClassName () ", asMETHOD (T, GetClassName), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "AWidget@+ GetParent () ", asMETHOD (T, GetParent), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "AWidget@+ GetContentRoot () ", asMETHOD (T, GetContentRoot), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "IntRect GetRect () ", asMETHOD (T, GetRect), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "String GetText () ", asMETHOD (T, GetText), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetRect (IntRect r) ", asMETHOD (T, SetRect), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "bool SetSize (int width, int height) ", asMETHOD (T, SetSize), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetPosition (int x, int y) ", asMETHOD (T, SetPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetText (const String& text) ", asMETHOD (T, SetText), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetSkinBg (const String& id) ", asMETHOD (T, SetSkinBg), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetLayoutParams (ALayoutParams@+ params) ", asMETHOD (T, SetLayoutParams), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetFontDescription (AFontDescription@+ fd) ", asMETHOD (T, SetFontDescription), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void Remove () ", asMETHOD (T, Remove), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void RemoveChild (AWidget@+ child, bool cleanup = true) ", asMETHOD (T, RemoveChild), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void DeleteAllChildren () ", asMETHOD (T, DeleteAllChildren), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "AWidget @+ FindWidget (const String& searchid) ", asMETHOD (T, FindWidget), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void PrintPrettyTree () ", asMETHOD (T, PrintPrettyTree), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "Array <AWidget@> @+ SearchAWidgetClass (const String& className) ", asFUNCTION (wrapper_AWidget_SearchAWidgetClass_className), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod (className, "Array <AWidget@> @+ SearchAWidgetId (const String& searchid) ", asFUNCTION (wrapper_AWidget_SearchAWidgetId_searchid), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod (className, "Array <AWidget@> @+ SearchAWidgetText (const String& searchText) ", asFUNCTION (wrapper_AWidget_SearchAWidgetText_searchText), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod (className, "void SetId (const String& id) ", asMETHOD (T, SetId), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void Center () ", asMETHOD (T, Center), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetGravity (UI_GRAVITY gravity) ", asMETHOD (T, SetGravity), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetAxis (UI_AXIS axis) ", asMETHOD (T, SetAxis), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetValue (double value) ", asMETHOD (T, SetValue), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "double GetValue () ", asMETHOD (T, GetValue), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetFocus () ", asMETHOD (T, SetFocus), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "bool GetFocus () const", asMETHOD (T, GetFocus), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetFocusRecursive () ", asMETHOD (T, SetFocusRecursive), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetState (UI_WIDGET_STATE state, bool on) ", asMETHOD (T, SetState), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "bool GetState (UI_WIDGET_STATE state) ", asMETHOD (T, GetState), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetVisibility (UI_WIDGET_VISIBILITY visibility) ", asMETHOD (T, SetVisibility), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "UI_WIDGET_VISIBILITY GetVisibility () ", asMETHOD (T, GetVisibility), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetStateRaw (UI_WIDGET_STATE state) ", asMETHOD (T, SetStateRaw), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "UI_WIDGET_STATE GetStateRaw () ", asMETHOD (T, GetStateRaw), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void Invalidate () ", asMETHOD (T, Invalidate), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "AWidget@+ GetFirstChild () ", asMETHOD (T, GetFirstChild), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "AWidget@+ GetNext () ", asMETHOD (T, GetNext), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "bool IsAncestorOf (AWidget@+ widget) ", asMETHOD (T, IsAncestorOf), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetIsFocusable (bool value) ", asMETHOD (T, SetIsFocusable), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "AWidget@+ GetWidget (const String& id) ", asMETHOD (T, GetWidget), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "AView@+ GetView () ", asMETHOD (T, GetView), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void AddChild (AWidget@+ child) ", asMETHOD (T, AddChild), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void AddChildAfter (AWidget@+ child, AWidget@+ otherChild) ", asMETHOD (T, AddChildAfter), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void AddChildBefore (AWidget@+ child, AWidget@+ otherChild) ", asMETHOD (T, AddChildBefore), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void AddChildRelative (AWidget@+ child, UI_WIDGET_Z_REL z, AWidget@+ reference) ", asMETHOD (T, AddChildRelative), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void InvalidateLayout () ", asMETHOD (T, InvalidateLayout), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetDelegate (AWidget@+ widget) ", asMETHOD (T, SetDelegate), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetMultiTouch (bool multiTouch) ", asMETHOD (T, SetMultiTouch), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "bool IsMultiTouch () ", asMETHOD (T, IsMultiTouch), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "bool GetCaptured () ", asMETHOD (T, GetCaptured), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetCapturing (bool capturing) ", asMETHOD (T, SetCapturing), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "bool GetCapturing () ", asMETHOD (T, GetCapturing), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void InvokeShortcut (const String& shortcut) ", asMETHOD (T, InvokeShortcut), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "bool GetShortened () ", asMETHOD (T, GetShortened), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetShortened (bool shortened) ", asMETHOD (T, SetShortened), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "String GetTooltip () ", asMETHOD (T, GetTooltip), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetTooltip (const String& text) ", asMETHOD (T, SetTooltip), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void Enable () ", asMETHOD (T, Enable), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void Disable () ", asMETHOD (T, Disable), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetFontId (const String& fontId) ", asMETHOD (T, SetFontId), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "String GetFontId () ", asMETHOD (T, GetFontId), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetFontSize (int size) ", asMETHOD (T, SetFontSize), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "int GetFontSize () ", asMETHOD (T, GetFontSize), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetX (int x) ", asMETHOD (T, SetX), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "int GetX () ", asMETHOD (T, GetX), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetY (int y) ", asMETHOD (T, SetY), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "int GetY () ", asMETHOD (T, GetY), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetWidth (int width) ", asMETHOD (T, SetWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "int GetWidth () ", asMETHOD (T, GetWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetHeight (int height) ", asMETHOD (T, SetHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "int GetHeight () ", asMETHOD (T, GetHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetLayoutWidth (int width) ", asMETHOD (T, SetLayoutWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "int GetLayoutWidth () ", asMETHOD (T, GetLayoutWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetLayoutHeight (int height) ", asMETHOD (T, SetLayoutHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "int GetLayoutHeight () ", asMETHOD (T, GetLayoutHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetLayoutPrefWidth (int width) ", asMETHOD (T, SetLayoutPrefWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "int GetLayoutPrefWidth () ", asMETHOD (T, GetLayoutPrefWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetLayoutPrefHeight (int height) ", asMETHOD (T, SetLayoutPrefHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "int GetLayoutPrefHeight () ", asMETHOD (T, GetLayoutPrefHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetLayoutMinWidth (int width) ", asMETHOD (T, SetLayoutMinWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "int GetLayoutMinWidth () ", asMETHOD (T, GetLayoutMinWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetLayoutMinHeight (int height) ", asMETHOD (T, SetLayoutMinHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "int GetLayoutMinHeight () ", asMETHOD (T, GetLayoutMinHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetLayoutMaxWidth (int width) ", asMETHOD (T, SetLayoutMaxWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "int GetLayoutMaxWidth () ", asMETHOD (T, GetLayoutMaxWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetLayoutMaxHeight (int height) ", asMETHOD (T, SetLayoutMaxHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "int GetLayoutMaxHeight () ", asMETHOD (T, GetLayoutMaxHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "IntVector2 ConvertToRoot (const IntVector2 position) const", asMETHOD (T, ConvertToRoot), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "IntVector2 ConvertFromRoot (const IntVector2 position) const", asMETHOD (T, ConvertFromRoot), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetOpacity (float opacity) ", asMETHOD (T, SetOpacity), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "float GetOpacity () ", asMETHOD (T, GetOpacity), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetAutoOpacity (float autoOpacity) ", asMETHOD (T, SetAutoOpacity), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "float GetAutoOpacity () ", asMETHOD (T, GetAutoOpacity), asCALL_THISCALL);
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

}

