#pragma once
#include <../AngelScript/Script.h>
#include <../ThirdParty/AngelScript/angelscript.h>
#include <../AngelScript/APITemplates.h>
#include <../AUI/AMenubar.h>
#include "ASelectItem.h"

namespace Bindings
{

using namespace Urho3D;

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

}

