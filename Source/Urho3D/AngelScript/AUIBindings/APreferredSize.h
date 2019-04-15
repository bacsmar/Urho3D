#pragma once
#include <../AngelScript/Script.h>
#include <../ThirdParty/AngelScript/angelscript.h>
#include <../AngelScript/APITemplates.h>
#include <../AUI/APreferredSize.h>

namespace Bindings
{
void RegisterUI_SIZE_DEP (asIScriptEngine *engine)
{
    engine->RegisterEnum ("UI_SIZE_DEP");
    engine->RegisterEnumValue ("UI_SIZE_DEP", "UI_SIZE_DEP_BOTH", UI_SIZE_DEP_BOTH);
    engine->RegisterEnumValue ("UI_SIZE_DEP", "UI_SIZE_DEP_WIDTH_DEPEND_ON_HEIGHT", UI_SIZE_DEP_WIDTH_DEPEND_ON_HEIGHT);
    engine->RegisterEnumValue ("UI_SIZE_DEP", "UI_SIZE_DEP_NONE", UI_SIZE_DEP_NONE);
    engine->RegisterEnumValue ("UI_SIZE_DEP", "UI_SIZE_DEP_HEIGHT_DEPEND_ON_WIDTH", UI_SIZE_DEP_HEIGHT_DEPEND_ON_WIDTH);
}

}

