#pragma once
#include <../AngelScript/Script.h>
#include <../ThirdParty/AngelScript/angelscript.h>
#include <../AngelScript/APITemplates.h>
#include <../AUI/AView.h>
#include "AWidget.h"

namespace Bindings
{

using namespace Urho3D;

AView * wrapper_AView_constructor ()
{
    return new AView (Urho3D::GetScriptContext ());
}

template <class T> void RegisterAView (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f ()").CString (), asFUNCTION (wrapper_AView_constructor), asCALL_CDECL);
    }

}

}

