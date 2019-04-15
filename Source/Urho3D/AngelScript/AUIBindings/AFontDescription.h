#pragma once
#include <../AngelScript/Script.h>
#include <../ThirdParty/AngelScript/angelscript.h>
#include <../AngelScript/APITemplates.h>
#include <../AUI/AFontDescription.h>

namespace Bindings
{

using namespace Urho3D;

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

}

