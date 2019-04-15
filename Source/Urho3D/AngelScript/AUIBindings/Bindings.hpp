#pragma once
#include <../AngelScript/Script.h>
#include <../ThirdParty/AngelScript/angelscript.h>
#include <../AngelScript/APITemplates.h>

namespace Bindings
{
void RegisterAnything (asIScriptEngine *engine);
void RegisterClassesForwardDeclarations (asIScriptEngine *engine);
void RegisterEnums (asIScriptEngine *engine);
void RegisterConstants (asIScriptEngine *engine);
void RegisterFreeFunctions (asIScriptEngine *engine);
void RegisterUrho3DSubsystems (asIScriptEngine *engine);
void RegisterClasses (asIScriptEngine *engine);
}

