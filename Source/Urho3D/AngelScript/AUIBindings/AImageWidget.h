#pragma once
#include <../AngelScript/Script.h>
#include <../ThirdParty/AngelScript/angelscript.h>
#include <../AngelScript/APITemplates.h>
#include <../AUI/AImageWidget.h>
#include "AWidget.h"

namespace Bindings
{

using namespace Urho3D;

AImageWidget * wrapper_AImageWidget_constructor_createWidget (bool createWidget = true)
{
    return new AImageWidget (Urho3D::GetScriptContext (), createWidget);
}

template <class T> void RegisterAImageWidget (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true)").CString (), asFUNCTION (wrapper_AImageWidget_constructor_createWidget), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "void SetImage (const String& imagePath) ", asMETHOD (T, SetImage), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "int GetImageWidth () const", asMETHOD (T, GetImageWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "int GetImageHeight () const", asMETHOD (T, GetImageHeight), asCALL_THISCALL);
}

}

