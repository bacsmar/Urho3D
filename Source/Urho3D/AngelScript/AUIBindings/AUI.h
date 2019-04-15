#pragma once
#include <../AngelScript/Script.h>
#include <../ThirdParty/AngelScript/angelscript.h>
#include <../AngelScript/APITemplates.h>
#include <../AUI/AUI.h>

namespace Bindings
{

using namespace Urho3D;

AUI * wrapper_AUI_constructor ()
{
    return new AUI (Urho3D::GetScriptContext ());
}

AUI *wrapper_AUI ()
{
    return Urho3D::GetScriptContext ()->GetSubsystem <AUI> ();
}

template <class T> void RegisterAUI (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    Urho3D::RegisterObject <T> (engine, className);

    if (registerConstructors)
    {

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f ()").CString (), asFUNCTION (wrapper_AUI_constructor), asCALL_CDECL);
    }

    engine->RegisterGlobalFunction ("AUI @+ get_AUI ()", asFUNCTION (wrapper_AUI), asCALL_CDECL);

    engine->RegisterObjectMethod (className, "AWidget@+ GetRootAWidget () ", asMETHOD (T, GetRootAWidget), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetKeyboardDisabled (bool disabled) ", asMETHOD (T, SetKeyboardDisabled), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetInputDisabled (bool disabled) ", asMETHOD (T, SetInputDisabled), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void Initialize (const String& languageFile) ", asMETHOD (T, Initialize), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void LoadSkin (const String& skin, const String& overrideSkin = String::EMPTY) ", asMETHOD (T, LoadSkin), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void LoadDefaultPlayerSkin () ", asMETHOD (T, LoadDefaultPlayerSkin), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void AddFont (const String& fontFile, const String & name) ", asMETHOD (T, AddFont), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetDefaultFont (const String& name, int size) ", asMETHOD (T, SetDefaultFont), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void GetTBIDString (uint id, String& value) ", asMETHOD (T, GetTBIDString), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "bool GetFocusedWidget () ", asMETHOD (T, GetFocusedWidget), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "AWidget@+ GetWidgetAt (int x, int y, bool include_children) ", asMETHOD (T, GetWidgetAt), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "bool GetBlockChangedEvents () const", asMETHOD (T, GetBlockChangedEvents), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetBlockChangedEvents (bool blocked = true) ", asMETHOD (T, SetBlockChangedEvents), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "AWidget@+ GetHoveredWidget () ", asMETHOD (T, GetHoveredWidget), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "AView@+ GetFocusedView () const", asMETHOD (T, GetFocusedView), asCALL_THISCALL);
}

}

