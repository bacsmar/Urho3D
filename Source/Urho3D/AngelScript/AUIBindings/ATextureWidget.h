#pragma once
#include <../AngelScript/Script.h>
#include <../ThirdParty/AngelScript/angelscript.h>
#include <../AngelScript/APITemplates.h>
#include <../AUI/ATextureWidget.h>
#include "AWidget.h"

namespace Bindings
{

using namespace Urho3D;

ATextureWidget * wrapper_ATextureWidget_constructor_createWidget (bool createWidget = true)
{
    return new ATextureWidget (Urho3D::GetScriptContext (), createWidget);
}

template <class T> void RegisterATextureWidget (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true)").CString (), asFUNCTION (wrapper_ATextureWidget_constructor_createWidget), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "void SetTexture (Texture @+ texture) ", asMETHOD (T, SetTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "Texture@+ GetTexture () ", asMETHOD (T, GetTexture), asCALL_THISCALL);
}

}

