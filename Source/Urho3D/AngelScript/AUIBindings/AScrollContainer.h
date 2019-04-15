#pragma once
#include <../AngelScript/Script.h>
#include <../ThirdParty/AngelScript/angelscript.h>
#include <../AngelScript/APITemplates.h>
#include <../AUI/AScrollContainer.h>
#include "AWidget.h"

namespace Bindings
{

using namespace Urho3D;

AScrollContainer * wrapper_AScrollContainer_constructor_createWidget (bool createWidget = true)
{
    return new AScrollContainer (Urho3D::GetScriptContext (), createWidget);
}

template <class T> void RegisterAScrollContainer (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true)").CString (), asFUNCTION (wrapper_AScrollContainer_constructor_createWidget), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "void SetScrollMode (UI_SCROLL_MODE mode) ", asMETHOD (T, SetScrollMode), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "UI_SCROLL_MODE GetScrollMode () ", asMETHOD (T, GetScrollMode), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetAdaptToContentSize (bool adapt) ", asMETHOD (T, SetAdaptToContentSize), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "bool GetAdaptToContentSize () ", asMETHOD (T, GetAdaptToContentSize), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetAdaptContentSize (bool adapt) ", asMETHOD (T, SetAdaptContentSize), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "bool GetAdaptContentSize () ", asMETHOD (T, GetAdaptContentSize), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void ScrollTo (int x, int y) ", asMETHOD (T, ScrollTo), asCALL_THISCALL);
}

void RegisterUI_SCROLL_MODE (asIScriptEngine *engine)
{
    engine->RegisterEnum ("UI_SCROLL_MODE");
    engine->RegisterEnumValue ("UI_SCROLL_MODE", "UI_SCROLL_MODE_Y_AUTO", UI_SCROLL_MODE_Y_AUTO);
    engine->RegisterEnumValue ("UI_SCROLL_MODE", "UI_SCROLL_MODE_Y", UI_SCROLL_MODE_Y);
    engine->RegisterEnumValue ("UI_SCROLL_MODE", "UI_SCROLL_MODE_X_AUTO_Y_AUTO", UI_SCROLL_MODE_X_AUTO_Y_AUTO);
    engine->RegisterEnumValue ("UI_SCROLL_MODE", "UI_SCROLL_MODE_X_Y", UI_SCROLL_MODE_X_Y);
    engine->RegisterEnumValue ("UI_SCROLL_MODE", "UI_SCROLL_MODE_OFF", UI_SCROLL_MODE_OFF);
}

}

