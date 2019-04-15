#pragma once
#include <../AngelScript/Script.h>
#include <../ThirdParty/AngelScript/angelscript.h>
#include <../AngelScript/APITemplates.h>
#include <../AUI/AColorWheel.h>
#include "AWidget.h"

namespace Bindings
{

using namespace Urho3D;

AColorWheel * wrapper_AColorWheel_constructor_createWidget (bool createWidget = true)
{
    return new AColorWheel (Urho3D::GetScriptContext (), createWidget);
}

template <class T> void RegisterAColorWheel (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true)").CString (), asFUNCTION (wrapper_AColorWheel_constructor_createWidget), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "float GetHue () ", asMETHOD (T, GetHue), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "float GetSaturation () ", asMETHOD (T, GetSaturation), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetHueSaturation (float hue, float saturation) ", asMETHOD (T, SetHueSaturation), asCALL_THISCALL);
}

}

