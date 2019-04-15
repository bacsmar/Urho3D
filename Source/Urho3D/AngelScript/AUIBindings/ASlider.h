#pragma once
#include <../AngelScript/Script.h>
#include <../ThirdParty/AngelScript/angelscript.h>
#include <../AngelScript/APITemplates.h>
#include <../AUI/ASlider.h>
#include "AWidget.h"

namespace Bindings
{

using namespace Urho3D;

ASlider * wrapper_ASlider_constructor_createWidget (bool createWidget = true)
{
    return new ASlider (Urho3D::GetScriptContext (), createWidget);
}

template <class T> void RegisterASlider (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true)").CString (), asFUNCTION (wrapper_ASlider_constructor_createWidget), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "void SetLimits (double minimum, double maximum) ", asMETHOD (T, SetLimits), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "double GetMinValue () const", asMETHOD (T, GetMinValue), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "double GetMaxValue () const", asMETHOD (T, GetMaxValue), asCALL_THISCALL);
}

}

