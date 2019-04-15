#pragma once
#include <../AngelScript/Script.h>
#include <../ThirdParty/AngelScript/angelscript.h>
#include <../AngelScript/APITemplates.h>
#include <../AUI/AMenuWindow.h>
#include "AWidget.h"

namespace Bindings
{

using namespace Urho3D;

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

}

