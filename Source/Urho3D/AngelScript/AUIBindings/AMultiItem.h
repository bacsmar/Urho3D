#pragma once
#include <../AngelScript/Script.h>
#include <../ThirdParty/AngelScript/angelscript.h>
#include <../AngelScript/APITemplates.h>
#include <../AUI/AMultiItem.h>
#include "ASelectItem.h"

namespace Bindings
{

using namespace Urho3D;

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

}

