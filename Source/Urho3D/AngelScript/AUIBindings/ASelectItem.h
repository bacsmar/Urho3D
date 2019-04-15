#pragma once
#include <../AngelScript/Script.h>
#include <../ThirdParty/AngelScript/angelscript.h>
#include <../AngelScript/APITemplates.h>
#include <../AUI/ASelectItem.h>

namespace Bindings
{

using namespace Urho3D;

ASelectItem * wrapper_ASelectItem_constructor_str_id_skinImage (const String& str = String::EMPTY, const String& id = String::EMPTY, const String& skinImage = String::EMPTY)
{
    return new ASelectItem (Urho3D::GetScriptContext (), str, id, skinImage);
}

ASelectItemSource * wrapper_ASelectItemSource_constructor ()
{
    return new ASelectItemSource (Urho3D::GetScriptContext ());
}

template <class T> void RegisterASelectItem (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    Urho3D::RegisterObject <T> (engine, className);

    if (registerConstructors)
    {

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f (const String& str = String::EMPTY, const String& id = String::EMPTY, const String& skinImage = String::EMPTY)").CString (), asFUNCTION (wrapper_ASelectItem_constructor_str_id_skinImage), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "void SetString (const String& str) ", asMETHOD (T, SetString), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetID (const String& id) ", asMETHOD (T, SetID), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "const String& GetStr () ", asMETHOD (T, GetStr), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetSkinImage (const String& skinImage) ", asMETHOD (T, SetSkinImage), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void SetSubSource (ASelectItemSource @+ subSource) ", asMETHOD (T, SetSubSource), asCALL_THISCALL);
}

template <class T> void RegisterASelectItemSource (asIScriptEngine *engine, const char *className, bool registerConstructors)
{
    Urho3D::RegisterObject <T> (engine, className);

    if (registerConstructors)
    {

        engine->RegisterObjectBehaviour (className, asBEHAVE_FACTORY, (Urho3D::String (className) + "@+ f ()").CString (), asFUNCTION (wrapper_ASelectItemSource_constructor), asCALL_CDECL);
    }

    engine->RegisterObjectMethod (className, "void AddItem (ASelectItem@+ item) ", asMETHOD (T, AddItem), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void RemoveItemWithId (const String& id) ", asMETHOD (T, RemoveItemWithId), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void RemoveItemWithStr (const String& str) ", asMETHOD (T, RemoveItemWithStr), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "int GetItemCount () ", asMETHOD (T, GetItemCount), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "void Clear () ", asMETHOD (T, Clear), asCALL_THISCALL);
    engine->RegisterObjectMethod (className, "const String& GetItemStr (int index) ", asMETHOD (T, GetItemStr), asCALL_THISCALL);
}

}

