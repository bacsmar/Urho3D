#pragma once
#include <../AngelScript/Script.h>
#include <../ThirdParty/AngelScript/angelscript.h>
#include <../AngelScript/APITemplates.h>
#include <../AUI/ADockWindow.h>
#include "AWindow.h"

namespace Bindings
{

using namespace Urho3D;

ADockWindow * wrapper_ADockWindow_constructor_createWidget_title_contentptr_minwidth_minheight (bool createWidget = true, const String& title = String::EMPTY, AWidget * contentptr = NULL, int minwidth = 800, int minheight = 400)
{
    return new ADockWindow (Urho3D::GetScriptContext (), createWidget, title, contentptr, minwidth, minheight);
}

template <class T> void RegisterADockWindow (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWindow <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWindow, T> (engine, "AWindow", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true, const String& title = String::EMPTY, AWidget @ contentptr = NULL, int minwidth = 800, int minheight = 400)").CString (), asFUNCTION (wrapper_ADockWindow_constructor_createWidget_title_contentptr_minwidth_minheight), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "void SetDockOrigin (String dockid) ", asMETHOD (T, SetDockOrigin), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "AWidget @+ GetDockContent () ", asMETHOD (T, GetDockContent), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "bool HasDockContent () ", asMETHOD (T, HasDockContent), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void Dock (AWidget @+ target) ", asMETHOD (T, Dock), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void Show (AWidget @+ host, int xpos = 50, int ypos = 50) ", asMETHOD (T, Show), asCALL_THISCALL);
}

}

