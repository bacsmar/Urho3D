#pragma once
#include <../AngelScript/Script.h>
#include <../ThirdParty/AngelScript/angelscript.h>
#include <../AngelScript/APITemplates.h>
#include <../AUI/AClickLabel.h>
#include "AWidget.h"

namespace Bindings
{

using namespace Urho3D;

AClickLabel * wrapper_AClickLabel_constructor_createWidget (bool createWidget = true)
{
    return new AClickLabel (Urho3D::GetScriptContext (), createWidget);
}

template <class T> void RegisterAClickLabel (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true)").CString (), asFUNCTION (wrapper_AClickLabel_constructor_createWidget), asCALL_CDECL);
    }

}

}

