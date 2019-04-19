#ifdef URHO3D_AUI
#include <../ThirdParty/AngelScript/angelscript.h>
#include <../AngelScript/APITemplates.h>
#include "Bindings.hpp"
#include "AUI.h"
#include "ABargraph.h"
#include "AButton.h"
#include "ACheckBox.h"
#include "AClickLabel.h"
#include "AColorWheel.h"
#include "AColorWidget.h"
#include "AComponent.h"
#include "AContainer.h"
#include "ADockWindow.h"
#include "AEditField.h"
#include "AFinderWindow.h"
#include "AFontDescription.h"
#include "AImageWidget.h"
#include "AInlineSelect.h"
#include "ALayout.h"
#include "AMenubar.h"
#include "AMenuWindow.h"
#include "AMessageWindow.h"
#include "AMultiItem.h"
#include "APopupWindow.h"
#include "APreferredSize.h"
#include "APromptWindow.h"
#include "APulldownMenu.h"
#include "ARadioButton.h"
#include "ASceneView.h"
#include "AScrollBar.h"
#include "AScrollContainer.h"
#include "ASection.h"
#include "ASelectDropdown.h"
#include "ASelectItem.h"
#include "ASelectList.h"
#include "ASeparator.h"
#include "ASkinImage.h"
#include "ASlider.h"
#include "ATabContainer.h"
#include "ATextField.h"
#include "ATextureWidget.h"
#include "AView.h"
#include "AWidget.h"
#include "AWindow.h"

namespace Bindings
{
void RegisterAnything (asIScriptEngine *engine)
{
    RegisterClassesForwardDeclarations (engine);
    RegisterEnums (engine);
    RegisterConstants (engine);
    RegisterFreeFunctions (engine);
    RegisterUrho3DSubsystems (engine);
    RegisterClasses (engine);
}

void RegisterClassesForwardDeclarations (asIScriptEngine *engine)
{
    engine->RegisterObjectType ("AUI", 0, asOBJ_REF);
    engine->RegisterObjectType ("ABargraph", 0, asOBJ_REF);
    engine->RegisterObjectType ("AButton", 0, asOBJ_REF);
    engine->RegisterObjectType ("ACheckBox", 0, asOBJ_REF);
    engine->RegisterObjectType ("AClickLabel", 0, asOBJ_REF);
    engine->RegisterObjectType ("AColorWheel", 0, asOBJ_REF);
    engine->RegisterObjectType ("AColorWidget", 0, asOBJ_REF);
    engine->RegisterObjectType ("AComponent", 0, asOBJ_REF);
    engine->RegisterObjectType ("AContainer", 0, asOBJ_REF);
    engine->RegisterObjectType ("ADockWindow", 0, asOBJ_REF);
    engine->RegisterObjectType ("AEditField", 0, asOBJ_REF);
    engine->RegisterObjectType ("AFinderWindow", 0, asOBJ_REF);
    engine->RegisterObjectType ("AFontDescription", 0, asOBJ_REF);
    engine->RegisterObjectType ("AImageWidget", 0, asOBJ_REF);
    engine->RegisterObjectType ("AInlineSelect", 0, asOBJ_REF);
    engine->RegisterObjectType ("ALayoutParams", 0, asOBJ_REF);
    engine->RegisterObjectType ("ALayout", 0, asOBJ_REF);
    engine->RegisterObjectType ("AMenuItem", 0, asOBJ_REF);
    engine->RegisterObjectType ("AMenuItemSource", 0, asOBJ_REF);
    engine->RegisterObjectType ("AMenuWindow", 0, asOBJ_REF);
    engine->RegisterObjectType ("AMessageWindow", 0, asOBJ_REF);
    engine->RegisterObjectType ("AMultiItem", 0, asOBJ_REF);
    engine->RegisterObjectType ("AMultiItemSource", 0, asOBJ_REF);
    engine->RegisterObjectType ("APopupWindow", 0, asOBJ_REF);
    engine->RegisterObjectType ("APromptWindow", 0, asOBJ_REF);
    engine->RegisterObjectType ("APulldownMenu", 0, asOBJ_REF);
    engine->RegisterObjectType ("ARadioButton", 0, asOBJ_REF);
    engine->RegisterObjectType ("ASceneView", 0, asOBJ_REF);
    engine->RegisterObjectType ("AScrollBar", 0, asOBJ_REF);
    engine->RegisterObjectType ("AScrollContainer", 0, asOBJ_REF);
    engine->RegisterObjectType ("ASection", 0, asOBJ_REF);
    engine->RegisterObjectType ("ASelectDropdown", 0, asOBJ_REF);
    engine->RegisterObjectType ("ASelectItem", 0, asOBJ_REF);
    engine->RegisterObjectType ("ASelectItemSource", 0, asOBJ_REF);
    engine->RegisterObjectType ("ASelectList", 0, asOBJ_REF);
    engine->RegisterObjectType ("ASeparator", 0, asOBJ_REF);
    engine->RegisterObjectType ("ASkinImage", 0, asOBJ_REF);
    engine->RegisterObjectType ("ASlider", 0, asOBJ_REF);
    engine->RegisterObjectType ("ATabContainer", 0, asOBJ_REF);
    engine->RegisterObjectType ("ATextField", 0, asOBJ_REF);
    engine->RegisterObjectType ("ATextureWidget", 0, asOBJ_REF);
    engine->RegisterObjectType ("AView", 0, asOBJ_REF);
    engine->RegisterObjectType ("AWidget", 0, asOBJ_REF);
    engine->RegisterObjectType ("AWindow", 0, asOBJ_REF);
}

void RegisterEnums (asIScriptEngine *engine)
{
    RegisterUI_EDIT_TYPE (engine);
    RegisterUI_LAYOUT_SIZE (engine);
    RegisterUI_LAYOUT_DISTRIBUTION (engine);
    RegisterUI_LAYOUT_POSITION (engine);
    RegisterUI_LAYOUT_DISTRIBUTION_POSITION (engine);
    RegisterUI_MESSAGEWINDOW_SETTINGS (engine);
    RegisterUI_SIZE_DEP (engine);
    RegisterUI_SCROLL_MODE (engine);
    RegisterUI_WIDGET_VISIBILITY (engine);
    RegisterUI_GRAVITY (engine);
    RegisterUI_EVENT_TYPE (engine);
    RegisterUI_WIDGET_Z_REL (engine);
    RegisterUI_TEXT_ALIGN (engine);
    RegisterUI_WIDGET_STATE (engine);
    RegisterUI_AXIS (engine);
    RegisterUI_WINDOW_SETTINGS (engine);
}

void RegisterConstants (asIScriptEngine *engine)
{
}

void RegisterFreeFunctions (asIScriptEngine *engine)
{
}

void RegisterUrho3DSubsystems (asIScriptEngine *engine)
{
   // RegisterAUI (engine);
}

void RegisterClasses (asIScriptEngine *engine)
{
    RegisterAUI <AUI> (engine, "AUI", true);
    RegisterABargraph <ABargraph> (engine, "ABargraph", true);
    RegisterAButton <AButton> (engine, "AButton", true);
    RegisterACheckBox <ACheckBox> (engine, "ACheckBox", true);
    RegisterAClickLabel <AClickLabel> (engine, "AClickLabel", true);
    RegisterAColorWheel <AColorWheel> (engine, "AColorWheel", true);
    RegisterAColorWidget <AColorWidget> (engine, "AColorWidget", true);
    RegisterAComponent <AComponent> (engine, "AComponent", true);
    RegisterAContainer <AContainer> (engine, "AContainer", true);
    RegisterADockWindow <ADockWindow> (engine, "ADockWindow", true);
    RegisterAEditField <AEditField> (engine, "AEditField", true);
    RegisterAFinderWindow <AFinderWindow> (engine, "AFinderWindow", true);
    RegisterAFontDescription <AFontDescription> (engine, "AFontDescription", true);
    RegisterAImageWidget <AImageWidget> (engine, "AImageWidget", true);
    RegisterAInlineSelect <AInlineSelect> (engine, "AInlineSelect", true);
    RegisterALayoutParams <ALayoutParams> (engine, "ALayoutParams", true);
    RegisterALayout <ALayout> (engine, "ALayout", true);
    RegisterAMenuItem <AMenuItem> (engine, "AMenuItem", true);
    RegisterAMenuItemSource <AMenuItemSource> (engine, "AMenuItemSource", true);
    RegisterAMenuWindow <AMenuWindow> (engine, "AMenuWindow", true);
    RegisterAMessageWindow <AMessageWindow> (engine, "AMessageWindow", true);
    RegisterAMultiItem <AMultiItem> (engine, "AMultiItem", true);
    RegisterAMultiItemSource <AMultiItemSource> (engine, "AMultiItemSource", true);
    RegisterAPopupWindow <APopupWindow> (engine, "APopupWindow", true);
    RegisterAPromptWindow <APromptWindow> (engine, "APromptWindow", true);
    RegisterAPulldownMenu <APulldownMenu> (engine, "APulldownMenu", true);
    RegisterARadioButton <ARadioButton> (engine, "ARadioButton", true);
    RegisterASceneView <ASceneView> (engine, "ASceneView", true);
    RegisterAScrollBar <AScrollBar> (engine, "AScrollBar", true);
    RegisterAScrollContainer <AScrollContainer> (engine, "AScrollContainer", true);
    RegisterASection <ASection> (engine, "ASection", true);
    RegisterASelectDropdown <ASelectDropdown> (engine, "ASelectDropdown", true);
    RegisterASelectItem <ASelectItem> (engine, "ASelectItem", true);
    RegisterASelectItemSource <ASelectItemSource> (engine, "ASelectItemSource", true);
    RegisterASelectList <ASelectList> (engine, "ASelectList", true);
    RegisterASeparator <ASeparator> (engine, "ASeparator", true);
    RegisterASkinImage <ASkinImage> (engine, "ASkinImage", true);
    RegisterASlider <ASlider> (engine, "ASlider", true);
    RegisterATabContainer <ATabContainer> (engine, "ATabContainer", true);
    RegisterATextField <ATextField> (engine, "ATextField", true);
    RegisterATextureWidget <ATextureWidget> (engine, "ATextureWidget", true);
    RegisterAView <AView> (engine, "AView", true);
    RegisterAWidget <AWidget> (engine, "AWidget", true);
    RegisterAWindow <AWindow> (engine, "AWindow", true);
}

}

#endif
