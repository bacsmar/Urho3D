#pragma once
#include <../AngelScript/Script.h>
#include <../ThirdParty/AngelScript/angelscript.h>
#include <../AngelScript/APITemplates.h>
#include <../AUI/ATextField.h>
#include "AWidget.h"

namespace Bindings
{

using namespace Urho3D;

ATextField * wrapper_ATextField_constructor_createWidget (bool createWidget = true)
{
    return new ATextField (Urho3D::GetScriptContext (), createWidget);
}

template <class T> void RegisterATextField (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true)").CString (), asFUNCTION (wrapper_ATextField_constructor_createWidget), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "void SetTextAlign (UI_TEXT_ALIGN align) ", asMETHOD (T, SetTextAlign), asCALL_THISCALL);
}

}

