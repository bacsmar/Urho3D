#pragma once
#include <../AngelScript/Script.h>
#include <../ThirdParty/AngelScript/angelscript.h>
#include <../AngelScript/APITemplates.h>
#include <../AUI/AMessageWindow.h>
#include "AWindow.h"

namespace Bindings
{

using namespace Urho3D;

AMessageWindow * wrapper_AMessageWindow_constructor_target_id_createWidget (AWidget* target, const String& id, bool createWidget = true)
{
    return new AMessageWindow (Urho3D::GetScriptContext (), target, id, createWidget);
}

template <class T> void RegisterAMessageWindow (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWindow <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWindow, T> (engine, "AWindow", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (AWidget@ target, const String& id, bool createWidget = true)").CString (), asFUNCTION (wrapper_AMessageWindow_constructor_target_id_createWidget), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "void Show (const String& title, const String& message, UI_MESSAGEWINDOW_SETTINGS settings, bool dimmer, int width, int height) ", asMETHOD (T, Show), asCALL_THISCALL);
}

void RegisterUI_MESSAGEWINDOW_SETTINGS (asIScriptEngine *engine)
{
    engine->RegisterEnum ("UI_MESSAGEWINDOW_SETTINGS");
    engine->RegisterEnumValue ("UI_MESSAGEWINDOW_SETTINGS", "UI_MESSAGEWINDOW_SETTINGS_OK", UI_MESSAGEWINDOW_SETTINGS_OK);
    engine->RegisterEnumValue ("UI_MESSAGEWINDOW_SETTINGS", "UI_MESSAGEWINDOW_SETTINGS_YES_NO", UI_MESSAGEWINDOW_SETTINGS_YES_NO);
    engine->RegisterEnumValue ("UI_MESSAGEWINDOW_SETTINGS", "UI_MESSAGEWINDOW_SETTINGS_OK_CANCEL", UI_MESSAGEWINDOW_SETTINGS_OK_CANCEL);
    engine->RegisterEnumValue ("UI_MESSAGEWINDOW_SETTINGS", "UI_MESSAGEWINDOW_SETTINGS_NONE", UI_MESSAGEWINDOW_SETTINGS_NONE);
}

}

