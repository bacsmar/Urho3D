#pragma once
#include <../AngelScript/Script.h>
#include <../ThirdParty/AngelScript/angelscript.h>
#include <../AngelScript/APITemplates.h>
#include <../AUI/AColorWidget.h>
#include "AWidget.h"

namespace Bindings
{

using namespace Urho3D;

AColorWidget * wrapper_AColorWidget_constructor_createWidget (bool createWidget = true)
{
    return new AColorWidget (Urho3D::GetScriptContext (), createWidget);
}

template <class T> void RegisterAColorWidget (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true)").CString (), asFUNCTION (wrapper_AColorWidget_constructor_createWidget), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "void SetColor (const Color& color) ", asMETHOD (T, SetColor), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetColorString (const String & name) ", asMETHOD (T, SetColorString), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "Color GetColor () const", asMETHOD (T, GetColor), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetAlpha (float value) ", asMETHOD (T, SetAlpha), asCALL_THISCALL);
}

}

