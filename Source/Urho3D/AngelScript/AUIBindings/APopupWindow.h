#pragma once
#include <../AngelScript/Script.h>
#include <../ThirdParty/AngelScript/angelscript.h>
#include <../AngelScript/APITemplates.h>
#include <../AUI/APopupWindow.h>
#include "AWidget.h"

namespace Bindings
{

using namespace Urho3D;

APopupWindow * wrapper_APopupWindow_constructor_createWidget_target_id (bool createWidget, AWidget* target = nullptr, const String& id = String::EMPTY)
{
    return new APopupWindow (Urho3D::GetScriptContext (), createWidget, target, id);
}

template <class T> void RegisterAPopupWindow (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget, AWidget@ target = nullptr, const String& id = String::EMPTY)").CString (), asFUNCTION (wrapper_APopupWindow_constructor_createWidget_target_id), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "void Close () ", asMETHOD (T, Close), asCALL_THISCALL);
}

}

