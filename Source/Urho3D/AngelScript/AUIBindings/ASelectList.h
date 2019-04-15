#pragma once
#include <../AngelScript/Script.h>
#include <../ThirdParty/AngelScript/angelscript.h>
#include <../AngelScript/APITemplates.h>
#include <../AUI/ASelectList.h>
#include "AWidget.h"

namespace Bindings
{

using namespace Urho3D;

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

}

