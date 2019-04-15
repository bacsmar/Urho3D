#pragma once
#include <../AngelScript/Script.h>
#include <../ThirdParty/AngelScript/angelscript.h>
#include <../AngelScript/APITemplates.h>
#include <../AUI/ALayout.h>
#include "AWidget.h"

namespace Bindings
{

using namespace Urho3D;

ALayoutParams * wrapper_ALayoutParams_constructor ()
{
    return new ALayoutParams (Urho3D::GetScriptContext ());
}

ALayout * wrapper_ALayout_constructor_axis_createWidget (UI_AXIS axis = UI_AXIS_X, bool createWidget = true)
{
    return new ALayout (Urho3D::GetScriptContext (), axis, createWidget);
}

void RegisterUI_LAYOUT_DISTRIBUTION_POSITION (asIScriptEngine *engine)
{
    engine->RegisterEnum ("UI_LAYOUT_DISTRIBUTION_POSITION");
    engine->RegisterEnumValue ("UI_LAYOUT_DISTRIBUTION_POSITION", "UI_LAYOUT_DISTRIBUTION_POSITION_CENTER", UI_LAYOUT_DISTRIBUTION_POSITION_CENTER);
    engine->RegisterEnumValue ("UI_LAYOUT_DISTRIBUTION_POSITION", "UI_LAYOUT_DISTRIBUTION_POSITION_LEFT_TOP", UI_LAYOUT_DISTRIBUTION_POSITION_LEFT_TOP);
    engine->RegisterEnumValue ("UI_LAYOUT_DISTRIBUTION_POSITION", "UI_LAYOUT_DISTRIBUTION_POSITION_RIGHT_BOTTOM", UI_LAYOUT_DISTRIBUTION_POSITION_RIGHT_BOTTOM);
}

template <class T> void RegisterALayoutParams (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    Urho3D::RegisterObject <T> (engine, className);

    if (registerConstructors)
    {

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f ()").CString (), asFUNCTION (wrapper_ALayoutParams_constructor), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "void SetWidth (int width) ", asMETHOD (T, SetWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetHeight (int height) ", asMETHOD (T, SetHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetMinWidth (int width) ", asMETHOD (T, SetMinWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetMinHeight (int height) ", asMETHOD (T, SetMinHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetMaxWidth (int width) ", asMETHOD (T, SetMaxWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetMaxHeight (int height) ", asMETHOD (T, SetMaxHeight), asCALL_THISCALL);
}

template <class T> void RegisterALayout (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (UI_AXIS axis = UI_AXIS_X, bool createWidget = true)").CString (), asFUNCTION (wrapper_ALayout_constructor_axis_createWidget), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "void SetLayoutSize (UI_LAYOUT_SIZE size) ", asMETHOD (T, SetLayoutSize), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetLayoutPosition (UI_LAYOUT_POSITION position) ", asMETHOD (T, SetLayoutPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetLayoutDistribution (UI_LAYOUT_DISTRIBUTION distribution) ", asMETHOD (T, SetLayoutDistribution), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetLayoutDistributionPosition (UI_LAYOUT_DISTRIBUTION_POSITION distribution_pos) ", asMETHOD (T, SetLayoutDistributionPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetLayoutConfig (const String & settings) ", asMETHOD (T, SetLayoutConfig), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "String GetLayoutConfig () ", asMETHOD (T, GetLayoutConfig), asCALL_THISCALL);
}

void RegisterUI_LAYOUT_POSITION (asIScriptEngine *engine)
{
    engine->RegisterEnum ("UI_LAYOUT_POSITION");
    engine->RegisterEnumValue ("UI_LAYOUT_POSITION", "UI_LAYOUT_POSITION_LEFT_TOP", UI_LAYOUT_POSITION_LEFT_TOP);
    engine->RegisterEnumValue ("UI_LAYOUT_POSITION", "UI_LAYOUT_POSITION_CENTER", UI_LAYOUT_POSITION_CENTER);
    engine->RegisterEnumValue ("UI_LAYOUT_POSITION", "UI_LAYOUT_POSITION_GRAVITY", UI_LAYOUT_POSITION_GRAVITY);
    engine->RegisterEnumValue ("UI_LAYOUT_POSITION", "UI_LAYOUT_POSITION_RIGHT_BOTTOM", UI_LAYOUT_POSITION_RIGHT_BOTTOM);
}

void RegisterUI_LAYOUT_SIZE (asIScriptEngine *engine)
{
    engine->RegisterEnum ("UI_LAYOUT_SIZE");
    engine->RegisterEnumValue ("UI_LAYOUT_SIZE", "UI_LAYOUT_SIZE_GRAVITY", UI_LAYOUT_SIZE_GRAVITY);
    engine->RegisterEnumValue ("UI_LAYOUT_SIZE", "UI_LAYOUT_SIZE_PREFERRED", UI_LAYOUT_SIZE_PREFERRED);
    engine->RegisterEnumValue ("UI_LAYOUT_SIZE", "UI_LAYOUT_SIZE_AVAILABLE", UI_LAYOUT_SIZE_AVAILABLE);
}

void RegisterUI_LAYOUT_DISTRIBUTION (asIScriptEngine *engine)
{
    engine->RegisterEnum ("UI_LAYOUT_DISTRIBUTION");
    engine->RegisterEnumValue ("UI_LAYOUT_DISTRIBUTION", "UI_LAYOUT_DISTRIBUTION_AVAILABLE", UI_LAYOUT_DISTRIBUTION_AVAILABLE);
    engine->RegisterEnumValue ("UI_LAYOUT_DISTRIBUTION", "UI_LAYOUT_DISTRIBUTION_PREFERRED", UI_LAYOUT_DISTRIBUTION_PREFERRED);
    engine->RegisterEnumValue ("UI_LAYOUT_DISTRIBUTION", "UI_LAYOUT_DISTRIBUTION_GRAVITY", UI_LAYOUT_DISTRIBUTION_GRAVITY);
}

}

