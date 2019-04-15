#pragma once
#include <../AngelScript/Script.h>
#include <../ThirdParty/AngelScript/angelscript.h>
#include <../AngelScript/APITemplates.h>
#include <../AUI/ABargraph.h>
#include "AWidget.h"

namespace Bindings
{

using namespace Urho3D;

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

}

