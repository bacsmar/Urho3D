#pragma once
#include <../AngelScript/Script.h>
#include <../ThirdParty/AngelScript/angelscript.h>
#include <../AngelScript/APITemplates.h>
#include <../AUI/AComponent.h>

namespace Bindings
{

using namespace Urho3D;

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

}

