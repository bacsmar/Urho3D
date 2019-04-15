#pragma once
#include <../AngelScript/Script.h>
#include <../ThirdParty/AngelScript/angelscript.h>
#include <../AngelScript/APITemplates.h>
#include <../AUI/AWindow.h>
#include "AWidget.h"

namespace Bindings
{

using namespace Urho3D;

void RegisterUI_WINDOW_SETTINGS (asIScriptEngine *engine)
{
    engine->RegisterEnum ("UI_WINDOW_SETTINGS");
    engine->RegisterEnumValue ("UI_WINDOW_SETTINGS", "UI_WINDOW_SETTINGS_CLOSE_BUTTON", UI_WINDOW_SETTINGS_CLOSE_BUTTON);
    engine->RegisterEnumValue ("UI_WINDOW_SETTINGS", "UI_WINDOW_SETTINGS_DEFAULT", UI_WINDOW_SETTINGS_DEFAULT);
    engine->RegisterEnumValue ("UI_WINDOW_SETTINGS", "UI_WINDOW_SETTINGS_NONE", UI_WINDOW_SETTINGS_NONE);
    engine->RegisterEnumValue ("UI_WINDOW_SETTINGS", "UI_WINDOW_SETTINGS_RESIZABLE", UI_WINDOW_SETTINGS_RESIZABLE);
    engine->RegisterEnumValue ("UI_WINDOW_SETTINGS", "UI_WINDOW_SETTINGS_CAN_ACTIVATE", UI_WINDOW_SETTINGS_CAN_ACTIVATE);
    engine->RegisterEnumValue ("UI_WINDOW_SETTINGS", "UI_WINDOW_SETTINGS_TITLEBAR", UI_WINDOW_SETTINGS_TITLEBAR);
}

AWindow * wrapper_AWindow_constructor_createWidget (bool createWidget = true)
{
    return new AWindow (Urho3D::GetScriptContext (), createWidget);
}

template <class T> void RegisterAWindow (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);
        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true)").CString (), asFUNCTION (wrapper_AWindow_constructor_createWidget), asCALL_CDECL);

    }

    engine->RegisterObjectMethod (className, "UI_WINDOW_SETTINGS GetSettings () ", asMETHOD (T, GetSettings), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetSettings (UI_WINDOW_SETTINGS settings) ", asMETHOD (T, SetSettings), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void ResizeToFitContent () ", asMETHOD (T, ResizeToFitContent), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void Close () ", asMETHOD (T, Close), asCALL_THISCALL);
}

}

