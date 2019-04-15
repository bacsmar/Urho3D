#pragma once
#include <../AngelScript/Script.h>
#include <../ThirdParty/AngelScript/angelscript.h>
#include <../AngelScript/APITemplates.h>
#include <../AUI/ATabContainer.h>
#include "AWidget.h"

namespace Bindings
{

using namespace Urho3D;

ATabContainer * wrapper_ATabContainer_constructor_createWidget (bool createWidget = true)
{
    return new ATabContainer (Urho3D::GetScriptContext (), createWidget);
}

template <class T> void RegisterATabContainer (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true)").CString (), asFUNCTION (wrapper_ATabContainer_constructor_createWidget), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "int GetNumPages () ", asMETHOD (T, GetNumPages), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetCurrentPage (int page) ", asMETHOD (T, SetCurrentPage), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "AWidget@+ GetCurrentPageWidget () ", asMETHOD (T, GetCurrentPageWidget), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "int GetCurrentPage () ", asMETHOD (T, GetCurrentPage), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "bool DeletePage (int page) ", asMETHOD (T, DeletePage), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void AddTabPageFile (const String & tabname, const String & layoutFile, bool selecttab = true) ", asMETHOD (T, AddTabPageFile), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void AddTabPageWidget (const String & tabname, AWidget @+ widget, bool selecttab = true) ", asMETHOD (T, AddTabPageWidget), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void UndockPage (int page) ", asMETHOD (T, UndockPage), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "bool DockWindow (String windowTitle) ", asMETHOD (T, DockWindow), asCALL_THISCALL);
}

}

