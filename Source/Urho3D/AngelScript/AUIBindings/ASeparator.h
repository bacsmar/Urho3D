#pragma once
#include <../AngelScript/Script.h>
#include <../ThirdParty/AngelScript/angelscript.h>
#include <../AngelScript/APITemplates.h>
#include <../AUI/ASeparator.h>
#include "AWidget.h"

namespace Bindings
{

using namespace Urho3D;

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

}

