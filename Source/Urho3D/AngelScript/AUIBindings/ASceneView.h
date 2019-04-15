#pragma once
#include <../AngelScript/Script.h>
#include <../ThirdParty/AngelScript/angelscript.h>
#include <../AngelScript/APITemplates.h>
#include <../AUI/ASceneView.h>
#include "AWidget.h"

namespace Bindings
{

using namespace Urho3D;

ASceneView * wrapper_ASceneView_constructor_createWidget (bool createWidget = true)
{
    return new ASceneView (Urho3D::GetScriptContext (), createWidget);
}

template <class T> void RegisterASceneView (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    RegisterAWidget <T> (engine, className, false);

    if (registerConstructors)
    {
        Urho3D::RegisterSubclass <AWidget, T> (engine, "AWidget", className);

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (bool createWidget = true)").CString (), asFUNCTION (wrapper_ASceneView_constructor_createWidget), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "void OnResize (const IntVector2& newSize) ", asMETHOD (T, OnResize), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetView (Scene@+ scene, Camera@+ camera) ", asMETHOD (T, SetView), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetFormat (uint format) ", asMETHOD (T, SetFormat), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetAutoUpdate (bool enable) ", asMETHOD (T, SetAutoUpdate), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void QueueUpdate () ", asMETHOD (T, QueueUpdate), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "uint GetFormat () const", asMETHOD (T, GetFormat), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "bool GetAutoUpdate () const", asMETHOD (T, GetAutoUpdate), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "Scene@+ GetScene () const", asMETHOD (T, GetScene), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "Node@+ GetCameraNode () const", asMETHOD (T, GetCameraNode), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "Texture2D@+ GetRenderTexture () const", asMETHOD (T, GetRenderTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "Texture2D@+ GetDepthTexture () const", asMETHOD (T, GetDepthTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "Viewport@+ GetViewport () const", asMETHOD (T, GetViewport), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetResizeRequired () ", asMETHOD (T, SetResizeRequired), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "const IntVector2& GetSize () const", asMETHOD (T, GetSize), asCALL_THISCALL);
}

}

