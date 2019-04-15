#pragma once
#include <../AngelScript/Script.h>
#include <../ThirdParty/AngelScript/angelscript.h>
#include <../AngelScript/APITemplates.h>
#include <../AUI/AInlineSelect.h>
#include "AWidget.h"

namespace Bindings
{

using namespace Urho3D;

AInlineSelect * wrapper_AInlineSelect_constructor_createWidget (bool createWidget = true)
{
    return new AInlineSelect (Urho3D::GetScriptContext (), createWidget);
}

template <class T> void RegisterAInlineSelect (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true)").CString (), asFUNCTION (wrapper_AInlineSelect_constructor_createWidget), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "void SetLimits (double minimum, double maximum) ", asMETHOD (T, SetLimits), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetStepSize (double step) ", asMETHOD (T, SetStepSize), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "double GetStepSize () ", asMETHOD (T, GetStepSize), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetEditFieldLayoutParams (ALayoutParams@+ params) ", asMETHOD (T, SetEditFieldLayoutParams), asCALL_THISCALL);
}

}

