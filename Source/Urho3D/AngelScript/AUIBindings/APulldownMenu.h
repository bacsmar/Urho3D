#pragma once
#include <../AngelScript/Script.h>
#include <../ThirdParty/AngelScript/angelscript.h>
#include <../AngelScript/APITemplates.h>
#include <../AUI/APulldownMenu.h>
#include "AButton.h"

namespace Bindings
{

using namespace Urho3D;

APulldownMenu * wrapper_APulldownMenu_constructor_createWidget (bool createWidget = true)
{
    return new APulldownMenu (Urho3D::GetScriptContext (), createWidget);
}

template <class T> void RegisterAPulldownMenu (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAButton <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AButton, T> (engine, "AButton", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true)").CString (), asFUNCTION (wrapper_APulldownMenu_constructor_createWidget), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "void SetSource (ASelectItemSource@+ source) ", asMETHOD (T, SetSource), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "const String& GetSelectedId () ", asMETHOD (T, GetSelectedId), asCALL_THISCALL);
}

}

