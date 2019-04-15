#pragma once
#include <../AngelScript/Script.h>
#include <../ThirdParty/AngelScript/angelscript.h>
#include <../AngelScript/APITemplates.h>
#include <../AUI/ASkinImage.h>
#include "AWidget.h"

namespace Bindings
{

using namespace Urho3D;

ASkinImage * wrapper_ASkinImage_constructor_bitmapID_createWidget (const String& bitmapID, bool createWidget = true)
{
    return new ASkinImage (Urho3D::GetScriptContext (), bitmapID, createWidget);
}

template <class T> void RegisterASkinImage (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (const String& bitmapID, bool createWidget = true)").CString (), asFUNCTION (wrapper_ASkinImage_constructor_bitmapID_createWidget), asCALL_CDECL);
    }

}

}

