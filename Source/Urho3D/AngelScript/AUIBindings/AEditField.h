#pragma once
#include <../AngelScript/Script.h>
#include <../ThirdParty/AngelScript/angelscript.h>
#include <../AngelScript/APITemplates.h>
#include <../AUI/AEditField.h>
#include "AWidget.h"

namespace Bindings
{

using namespace Urho3D;

AEditField * wrapper_AEditField_constructor_createWidget (bool createWidget = true)
{
    return new AEditField (Urho3D::GetScriptContext (), createWidget);
}

template <class T> void RegisterAEditField (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true)").CString (), asFUNCTION (wrapper_AEditField_constructor_createWidget), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "void AppendText (const String& text) ", asMETHOD (T, AppendText), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetTextAlign (UI_TEXT_ALIGN align) ", asMETHOD (T, SetTextAlign), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetAdaptToContentSize (bool adapt) ", asMETHOD (T, SetAdaptToContentSize), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "bool GetAdaptToContentSize () const", asMETHOD (T, GetAdaptToContentSize), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetEditType (UI_EDIT_TYPE type) ", asMETHOD (T, SetEditType), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetReadOnly (bool readonly) ", asMETHOD (T, SetReadOnly), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetStyling (bool styling) ", asMETHOD (T, SetStyling), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetMultiline (bool multiline) ", asMETHOD (T, SetMultiline), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void Reformat (bool update_fragments = false) ", asMETHOD (T, Reformat), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void ScrollTo (int x, int y) ", asMETHOD (T, ScrollTo), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetWrapping (bool wrap) ", asMETHOD (T, SetWrapping), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "bool GetWrapping () ", asMETHOD (T, GetWrapping), asCALL_THISCALL);
}

void RegisterUI_EDIT_TYPE (asIScriptEngine *engine)
{
    engine->RegisterEnum ("UI_EDIT_TYPE");
    engine->RegisterEnumValue ("UI_EDIT_TYPE", "UI_EDIT_TYPE_EMAIL", UI_EDIT_TYPE_EMAIL);
    engine->RegisterEnumValue ("UI_EDIT_TYPE", "UI_EDIT_TYPE_SEARCH", UI_EDIT_TYPE_SEARCH);
    engine->RegisterEnumValue ("UI_EDIT_TYPE", "UI_EDIT_TYPE_NUMBER", UI_EDIT_TYPE_NUMBER);
    engine->RegisterEnumValue ("UI_EDIT_TYPE", "UI_EDIT_TYPE_PASSWORD", UI_EDIT_TYPE_PASSWORD);
    engine->RegisterEnumValue ("UI_EDIT_TYPE", "UI_EDIT_TYPE_PHONE", UI_EDIT_TYPE_PHONE);
    engine->RegisterEnumValue ("UI_EDIT_TYPE", "UI_EDIT_TYPE_TEXT", UI_EDIT_TYPE_TEXT);
    engine->RegisterEnumValue ("UI_EDIT_TYPE", "UI_EDIT_TYPE_URL", UI_EDIT_TYPE_URL);
}

}

