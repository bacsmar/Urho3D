#pragma once
#include <../AngelScript/Script.h>
#include <../ThirdParty/AngelScript/angelscript.h>
#include <../AngelScript/APITemplates.h>
#include <../AUI/AFinderWindow.h>
#include "AWindow.h"

namespace Bindings
{

using namespace Urho3D;

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

}

