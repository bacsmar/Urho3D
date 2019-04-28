//
// Copyright (c) 2014-2015, THUNDERBEAST GAMES LLC All rights reserved
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include <TurboBadger/tb_core.h>
#include <TurboBadger/tb_system.h>
#include <TurboBadger/tb_debug.h>
#include <TurboBadger/animation/tb_widget_animation.h>
#include <TurboBadger/renderers/tb_renderer_batcher.h>
#include <TurboBadger/tb_font_renderer.h>
#include <TurboBadger/tb_node_tree.h>
#include <TurboBadger/tb_widgets_reader.h>
#include <TurboBadger/tb_window.h>
#include <TurboBadger/tb_message_window.h>
#include <TurboBadger/tb_editfield.h>
#include <TurboBadger/tb_select.h>
#include <TurboBadger/tb_inline_select.h>
#include <TurboBadger/tb_tab_container.h>
#include <TurboBadger/tb_toggle_container.h>
#include <TurboBadger/tb_scroll_container.h>
#include <TurboBadger/tb_menu_window.h>
#include <TurboBadger/tb_popup_window.h>
#include <TurboBadger/image/tb_image_widget.h>
#include <TurboBadger/tb_atomic_widgets.h>

void register_tbbf_font_renderer();
void register_stb_font_renderer();
void register_freetype_font_renderer();

using namespace tb;

#include "../Precompiled.h"

#include "../Core/CoreEvents.h"
#include "../IO/Log.h"
#include "../IO/FileSystem.h"
#include "../Input/Input.h"
#include "../Input/InputEvents.h"
#include "../Resource/ResourceCache.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/GraphicsEvents.h"
#include "../Graphics/Texture2D.h"
#include "../Graphics/VertexBuffer.h"

#include "../AUI/AEvents.h"

#include "../AUI/ARenderer.h"
#include "../AUI/AUI.h"
#include "../AUI/AView.h"
#include "../AUI/AButton.h"
#include "../AUI/ATextField.h"
#include "../AUI/AEditField.h"
#include "../AUI/ALayout.h"
#include "../AUI/AImageWidget.h"
#include "../AUI/AClickLabel.h"
#include "../AUI/ACheckBox.h"
#include "../AUI/ASelectList.h"
#include "../AUI/AMessageWindow.h"
#include "../AUI/ASkinImage.h"
#include "../AUI/ATabContainer.h"
#include "../AUI/ASceneView.h"
#include "../AUI/AContainer.h"
#include "../AUI/ASection.h"
#include "../AUI/AInlineSelect.h"
#include "../AUI/AScrollContainer.h"
#include "../AUI/ASeparator.h"
#include "../AUI/ADimmer.h"
#include "../AUI/ASelectDropdown.h"
#include "../AUI/AMenuWindow.h"
#include "../AUI/APopupWindow.h"
#include "../AUI/ASlider.h"
#include "../AUI/AColorWidget.h"
#include "../AUI/AColorWheel.h"
#include "../AUI/ABargraph.h"
#include "../AUI/APromptWindow.h"
#include "../AUI/AFinderWindow.h"
#include "../AUI/APulldownMenu.h"
#include "../AUI/AComponent.h"
#include "../AUI/ARadioButton.h"
#include "../AUI/AScrollBar.h"
#include "../AUI/ADockWindow.h"
#include "../AUI/AButtonGrid.h"
#include "../AUI/AFontDescription.h"
#include "../AUI/AListView.h"
#include "../AUI/AMultiItem.h"
#include "../AUI/AMenubar.h"
#include "../AUI/ATextureWidget.h"
#if 0   // HELP ATOMIC -- removed DragDrop for now
#include "../AUI/ADragDrop.h"
#endif

#ifdef URHO3D_ANGELSCRIPT
const char* AUI_CATEGORY = "AUI";  /// for Angelscript Binding
#endif

namespace tb
{

#if 1
/// HELP ATOMIC it needs to be somewhere...
void TBSystem::RescheduleTimer(double fire_time)
{

}
#endif

}

namespace Urho3D
{

#ifdef URHO3D_ANGELSCRIPT
void RegisterAUILibrary(Context* context)
{

    ABargraph::RegisterObject(context);
    AButton::RegisterObject(context);
    ACheckBox::RegisterObject(context);
    AClickLabel::RegisterObject(context);
    AColorWheel::RegisterObject(context);
    AColorWidget::RegisterObject(context);
    AComponent::RegisterObject(context);
    AContainer::RegisterObject(context);
    ADockWindow::RegisterObject(context);
    AEditField::RegisterObject(context);
    AFinderWindow::RegisterObject(context);
    AFontDescription::RegisterObject(context);
    AImageWidget::RegisterObject(context);
    AInlineSelect::RegisterObject(context);
    ALayoutParams::RegisterObject(context);
    ALayout::RegisterObject(context);
    AListView::RegisterObject(context);
    AMenuItem::RegisterObject(context);
    AMenuItemSource::RegisterObject(context);
    AMenuWindow::RegisterObject(context);
    AMessageWindow::RegisterObject(context);
    AMultiItem::RegisterObject(context);
    AMultiItemSource::RegisterObject(context);
    APopupWindow::RegisterObject(context);
    APromptWindow::RegisterObject(context);
    APulldownMenu::RegisterObject(context);
    ARadioButton::RegisterObject(context);
    ASceneView::RegisterObject(context);
    AScrollBar::RegisterObject(context);
    AScrollContainer::RegisterObject(context);
    ASection::RegisterObject(context);
    ASelectDropdown::RegisterObject(context);
    ASelectItem::RegisterObject(context);
    ASelectItemSource::RegisterObject(context);
    ASelectList::RegisterObject(context);
    ASeparator::RegisterObject(context);
    ASkinImage::RegisterObject(context);
    ASlider::RegisterObject(context);
    ATabContainer::RegisterObject(context);
    ATextField::RegisterObject(context);
    ATextureWidget::RegisterObject(context);
    AView::RegisterObject(context);
    AWidget::RegisterObject(context);
    AWindow::RegisterObject(context);
}
#endif

WeakPtr<Context> AUI::uiContext_;

AUI::AUI(Context* context) :
    Object(context),
    rootWidget_(0),
    rootAWidget_(0),
    inputDisabled_(false),
    keyboardDisabled_(false),
    initialized_(false),
    skinLoaded_(false),
    consoleVisible_(false),
    exitRequested_(false),
    changedEventsBlocked_(0),
    tooltipHoverTime_ (0.0f)
{

#ifdef URHO3D_ANGELSCRIPT
    RegisterAUILibrary(context);
#endif

    SubscribeToEvent(E_EXITREQUESTED, URHO3D_HANDLER(AUI, HandleExitRequested));

}

AUI::~AUI()
{
    if (initialized_)
    {
        initialized_ = false;

        tb::TBAnimationManager::AbortAllAnimations();
        tb::TBWidgetListener::RemoveGlobalListener(this);

        TBFile::SetReaderFunction(0);
        TBID::tbidRegisterCallback = 0;

        tb::TBWidgetsAnimationManager::Shutdown();

        delete rootWidget_;
        widgetWrap_.Clear();

        // leak
        //delete TBARenderer::renderer_;

        tb_core_shutdown();
    }

    uiContext_ = 0;

}

void AUI::HandleExitRequested(StringHash eventType, VariantMap& eventData)
{
    Shutdown();
}

void AUI::Shutdown()
{
}

bool AUI::GetFocusedWidget()
{
    if (!TBWidget::focused_widget)
        return false;

    return TBWidget::focused_widget->IsOfType<TBEditField>();
}

void AUI::SetBlockChangedEvents(bool blocked)
{
    if (blocked)
        changedEventsBlocked_++;
    else
    {
        changedEventsBlocked_--;

        if (changedEventsBlocked_ < 0)
        {
            URHO3D_LOGERROR("AUI::BlockChangedEvents - mismatched block calls, setting to 0");
            changedEventsBlocked_ = 0;
        }
    }

}

extern "C"
{
    void register_freetype_font_renderer();
    void register_tbbf_font_renderer();
    void register_stb_font_renderer();
}

void AUI::Initialize(const String& languageFile)
{
    Graphics* graphics = GetSubsystem<Graphics>();
    assert(graphics);
    assert(graphics->IsInitialized());
    graphics_ = graphics;

    uiContext_ = context_;

    TBFile::SetReaderFunction(TBFileReader);
    TBID::tbidRegisterCallback = AUI::TBIDRegisterStringCallback;

    TBWidgetsAnimationManager::Init();

    renderer_ = new ARenderer(graphics_->GetContext());
    tb_core_init(renderer_, languageFile.CString());

    // **README**
    // - define TB_FONT_RENDERER_FREETYPE (or others) in tb_config.h for non-demo
#ifdef TB_FONT_RENDERER_TBBF
    register_tbbf_font_renderer();
#endif
#ifdef TB_FONT_RENDERER_STB
    register_stb_font_renderer();
#endif
#ifdef TB_FONT_RENDERER_FREETYPE
   register_freetype_font_renderer();
#endif

    rootAWidget_ = new AWidget(uiContext_); // bind assist
    rootWidget_ =  rootAWidget_->GetInternalWidget(); // new TBWidget();
    int width = graphics_->GetWidth();
    int height = graphics_->GetHeight();
    rootAWidget_->SetSize(width, height);
    rootAWidget_->SetVisibility(UI_WIDGET_VISIBILITY_VISIBLE);

    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(AUI, HandleUpdate));
    SubscribeToEvent(E_SCREENMODE, URHO3D_HANDLER(AUI, HandleScreenMode));
    SubscribeToEvent(E_POSTUPDATE, URHO3D_HANDLER(AUI, HandlePostUpdate));
    SubscribeToEvent(E_RENDERUPDATE, URHO3D_HANDLER(AUI, HandleRenderUpdate));

#if 0   // HELP ATOMIC -- removed DragDrop for now
    // register the ADragDrop subsystem (after we have subscribed to events, so it is processed after)
    context_->RegisterSubsystem(new ADragDrop(context_));
#endif

    tb::TBWidgetListener::AddGlobalListener(this);

    initialized_ = true;

    //TB_DEBUG_SETTING(LAYOUT_BOUNDS) = 1;
}

void AUI::LoadSkin(const String& skin, const String& overrideSkin)
{
    // Load the default skin, and override skin (if any)
    tb::g_tb_skin->Load(skin.CString(), overrideSkin.CString());
    skinLoaded_ = true;
}

void AUI::LoadDefaultPlayerSkin()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();

    String skin = "resources/default_skin/skin.tb.txt";
    String overrideSkin;

    /// HELP ATOMIC the override skin path is a hack.
    // see if we have an override skin
    SharedPtr<File> skinFile = cache->GetFile("AUI/Skin/skin.ui.txt", false);
    if (skinFile.NotNull())
    {
        skinFile->Close();
        skin = "AUI/Skin/skin.ui.txt";
    }

    // see if we have an override skin
    SharedPtr<File> overrideFile = cache->GetFile("AUI/Skin/Override/skin.ui.txt", false);

    if (overrideFile.NotNull())
    {
        overrideFile->Close();
        overrideSkin = "AUI/Skin/Override/skin.ui.txt";
    }

    LoadSkin(skin, overrideSkin);

    /// HELP ATOMIC  is this default font really being programmed?
    if (skin == "resources/skin/skin.tb.txt")
    {
        AddFont( "resources/default_font/vera.ttf", "Vera" );
        SetDefaultFont("Vera", 12);
    }
}

void AUI::SetDefaultFont(const String& name, int size)
{
    tb::TBFontDescription fd;
    fd.SetID(tb::TBIDC(name.CString()));
    fd.SetSize(tb::g_tb_skin->GetDimensionConverter()->DpToPx(size));
    tb::g_font_manager->SetDefaultFontDescription(fd);

    // Create the font now.
    tb::TBFontFace *font = tb::g_font_manager->CreateFontFace(tb::g_font_manager->GetDefaultFontDescription());

    // Render some glyphs in one go now since we know we are going to use them. It would work fine
    // without this since glyphs are rendered when needed, but with some extra updating of the glyph bitmap.
    if (font)
        font->RenderGlyphs(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~•·åäöÅÄÖ");
}

void AUI::AddFont(const String& fontFile, const String& name)
{
    tb::g_font_manager->AddFontInfo(fontFile.CString(), name.CString());
}

void AUI::AddAView(AView* uiView)
{
    rootWidget_->AddChild(uiView->GetInternalWidget());
    uiViews_.Push(SharedPtr<AView>(uiView));

    if (!focusedView_ && uiView)
    {
        uiView->SetFocus();
    }
}

void AUI::RemoveAView(AView* uiView)
{
    if (focusedView_ == uiView)
    {
        SetFocusedView(0);
    }

    rootWidget_->RemoveChild(uiView->GetInternalWidget());
    uiViews_.Remove(SharedPtr<AView>(uiView));
}

void AUI::SetFocusedView(AView* uiView)
{
    if (focusedView_ == uiView)
    {
        return;
    }

    focusedView_ = uiView;

    if (focusedView_)
    {
        focusedView_->BecomeFocused();
    }
    else
    {
        focusedView_ = 0;

        // look for first auto activated AView, and recurse
        Vector<SharedPtr<AView>>::Iterator itr = uiViews_.Begin();

        while (itr != uiViews_.End())
        {
            if ((*itr)->GetAutoFocus())
            {
                SetFocusedView(*itr);
                return;
            }

            itr++;
        }

    }
}

void AUI::Render(bool resetRenderTargets)
{
    Vector<SharedPtr<AView>>::Iterator itr = uiViews_.Begin();

    while (itr != uiViews_.End())
    {
        (*itr)->Render(resetRenderTargets);

        itr++;
    }
}


void AUI::HandlePostUpdate(StringHash eventType, VariantMap& eventData)
{
    SendEvent(E_UIUPDATE);

    TBMessageHandler::ProcessMessages();
    TBAnimationManager::Update();

    rootWidget_->InvokeProcessStates();
    rootWidget_->InvokeProcess();
}

void AUI::HandleRenderUpdate(StringHash eventType, VariantMap& eventData)
{
    Vector<SharedPtr<AView>>::Iterator itr = uiViews_.Begin();

    while (itr != uiViews_.End())
    {
        (*itr)->UpdateUIBatches();
        itr++;
    }
}

void AUI::TBFileReader(const char* filename, void** data, unsigned* length)
{
    *data = 0;
    *length = 0;

    ResourceCache* cache = uiContext_->GetSubsystem<ResourceCache>();
    SharedPtr<File> file = cache->GetFile(filename);
    if (!file || !file->IsOpen())
    {
        URHO3D_LOGERRORF("AUI::TBFileReader: Unable to load file: %s", filename);
        return;
    }

    unsigned size = file->GetSize();

    if (!size)
        return;

    void* _data = malloc(size);
    if (!_data)
        return;

    if (file->Read(_data, size) != size)
    {
        free(_data);
        return;
    }

    *length = size;
    *data = _data;
}

void AUI::GetTBIDString(unsigned id, String& value)
{
    if (!id)
    {
        value = "";
    }
    else
    {
        value = tbidToString_[id];
    }
}

void AUI::TBIDRegisterStringCallback(unsigned id, const char* value)
{
    uiContext_->GetSubsystem<AUI>()->tbidToString_[id] = String(value);
}

bool AUI::LoadResourceFile(TBWidget* widget, const String& filename)
{

    tb::TBNode node;

    if (!node.ReadFile(filename.CString()))
        return false;

    tb::g_widgets_reader->LoadNodeTree(widget, &node);
    return true;
}

bool AUI::LoadResourceFile(AWidget* widget, const String& filename)
{
   TBWidget* iwidget = widget->GetInternalWidget();
    if (iwidget) return LoadResourceFile(iwidget, filename);
    return false;
}

void AUI::HandleScreenMode(StringHash eventType, VariantMap& eventData)
{
    using namespace ScreenMode;
    rootWidget_->SetSize(eventData[P_WIDTH].GetInt(), eventData[P_HEIGHT].GetInt());
}

void AUI::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    if (exitRequested_) {
        SendEvent(E_EXITREQUESTED);
        exitRequested_ = false;
        return;
    }

    tooltipHoverTime_ += eventData[Update::P_TIMESTEP].GetFloat();

    if (tooltipHoverTime_ >= 0.5f)
    {
        AWidget* hoveredWidget = GetHoveredWidget();
        if (hoveredWidget && !tooltip_ && (hoveredWidget->GetShortened() || hoveredWidget->GetTooltip().Length() > 0))
        {
            tooltip_ = new APopupWindow(context_, true, hoveredWidget, "tooltip");
            ALayout* tooltipLayout = new ALayout(context_, UI_AXIS_Y, true);
            if (hoveredWidget->GetShortened())
            {
                ATextField* fullTextField = new ATextField(context_, true);
                fullTextField->SetText(hoveredWidget->GetText());
                tooltipLayout->AddChild(fullTextField);
            }
            if (hoveredWidget->GetTooltip().Length() > 0)
            {
                ATextField* tooltipTextField = new ATextField(context_, true);
                tooltipTextField->SetText(hoveredWidget->GetTooltip());
                tooltipLayout->AddChild(tooltipTextField);
            }
            Input* input = GetSubsystem<Input>();
            IntVector2 mousePosition = input->GetMousePosition();
            tooltip_->AddChild(tooltipLayout);
            tooltip_->Show(mousePosition.x_ + 8, mousePosition.y_ + 8);
        }
    }
    else
    {
        if (tooltip_) tooltip_->Close();
    }
}

AWidget* AUI::GetHoveredWidget()
{
    return WrapWidget(TBWidget::hovered_widget);
}

bool AUI::IsWidgetWrapped(tb::TBWidget* widget)
{
    return widgetWrap_.Contains(widget);
}

bool AUI::UnwrapWidget(tb::TBWidget* widget)
{
    if (widgetWrap_.Contains(widget))
    {
        widget->SetDelegate(0);
        widgetWrap_.Erase(widget);
        return true;
    }

    return false;
}

void AUI::PruneUnreachableWidgets()
{
    HashMap<tb::TBWidget*, SharedPtr<AWidget>>::Iterator itr;

    for (itr = widgetWrap_.Begin(); itr != widgetWrap_.End(); )
    {
        if ((*itr).first_->GetParent() || (*itr).second_->Refs() > 1)
        {
            itr++;
            continue;
        }

        itr.GotoNext();

        VariantMap eventData;
        eventData[WidgetDeleted::P_WIDGET] = (AWidget*) (*itr).second_;
        (*itr).second_->SendEvent(E_WIDGETDELETED, eventData);

        tb::TBWidget* toDelete = (*itr).first_;
        UnwrapWidget(toDelete);
        delete toDelete;
    }
}

void AUI::WrapWidget(AWidget* widget, tb::TBWidget* tbwidget)
{
    assert (!widgetWrap_.Contains(tbwidget));
    widgetWrap_[tbwidget] = widget;
}

AWidget* AUI::WrapWidget(tb::TBWidget* widget)
{
    if (!widget)
        return NULL;

    if (widgetWrap_.Contains(widget))
        return widgetWrap_[widget];

    // switch this to use a factory?

    // this is order dependent as we're using IsOfType which also works if a base class

    if (widget->IsOfType<TBPopupWindow>())
    {
        APopupWindow* popupWindow = new APopupWindow(context_, false);
        popupWindow->SetWidget(widget);
        WrapWidget(popupWindow, widget);
        return popupWindow;
    }

    if (widget->IsOfType<TBDimmer>())
    {
        ADimmer* dimmer = new ADimmer(context_, false);
        dimmer->SetWidget(widget);
        WrapWidget(dimmer, widget);
        return dimmer;
    }

    if (widget->IsOfType<TBScrollContainer>())
    {
        AScrollContainer* container = new AScrollContainer(context_, false);
        container->SetWidget(widget);
        WrapWidget(container, widget);
        return container;
    }

    if (widget->IsOfType<TBInlineSelect>())
    {
        AInlineSelect* select = new AInlineSelect(context_, false);
        select->SetWidget(widget);
        WrapWidget(select, widget);
        return select;
    }

    if (widget->IsOfType<TBSlider>())
    {
        ASlider* slider = new ASlider(context_, false);
        slider->SetWidget(widget);
        WrapWidget(slider, widget);
        return slider;
    }

    if (widget->IsOfType<TBScrollBar>())
    {
        AScrollBar* slider = new AScrollBar(context_, false);
        slider->SetWidget(widget);
        WrapWidget(slider, widget);
        return slider;
    }

    if (widget->IsOfType<TBColorWidget>())
    {
        AColorWidget* colorWidget = new AColorWidget(context_, false);
        colorWidget->SetWidget(widget);
        WrapWidget(colorWidget, widget);
        return colorWidget;
    }

    if (widget->IsOfType<TBColorWheel>())
    {
        AColorWheel* colorWheel = new AColorWheel(context_, false);
        colorWheel->SetWidget(widget);
        WrapWidget(colorWheel, widget);
        return colorWheel;
    }

    if (widget->IsOfType<TBSection>())
    {
        ASection* section = new ASection(context_, false);
        section->SetWidget(widget);
        WrapWidget(section, widget);
        return section;
    }

    if (widget->IsOfType<TBSeparator>())
    {
        ASeparator* sep = new ASeparator(context_, false);
        sep->SetWidget(widget);
        WrapWidget(sep, widget);
        return sep;
    }

    if (widget->IsOfType<TBContainer>())
    {
        AContainer* container = new AContainer(context_, false);
        container->SetWidget(widget);
        WrapWidget(container, widget);
        return container;
    }

    if (widget->IsOfType<TBSelectDropdown>())
    {
        ASelectDropdown* select = new ASelectDropdown(context_, false);
        select->SetWidget(widget);
        WrapWidget(select, widget);
        return select;
    }

    if (widget->IsOfType<TBPulldownMenu>())
    {
        APulldownMenu* select = new APulldownMenu(context_, false);
        select->SetWidget(widget);
        WrapWidget(select, widget);
        return select;
    }

    if (widget->IsOfType<TBButton>())
    {
        // don't wrap the close button of a TBWindow.close
        if (widget->GetID() == TBIDC("TBWindow.close"))
            return 0;

        AButton* button = new AButton(context_, false);
        button->SetWidget(widget);
        WrapWidget(button, widget);
        return button;
    }

    if (widget->IsOfType<TBTextField>())
    {
        ATextField* textfield = new ATextField(context_, false);
        textfield->SetWidget(widget);
        WrapWidget(textfield, widget);
        return textfield;
    }

    if (widget->IsOfType<TBEditField>())
    {
        AEditField* editfield = new AEditField(context_, false);
        editfield->SetWidget(widget);
        WrapWidget(editfield, widget);
        return editfield;
    }

    if (widget->IsOfType<TBSkinImage>())
    {
        ASkinImage* skinimage = new ASkinImage(context_, "", false);
        skinimage->SetWidget(widget);
        WrapWidget(skinimage, widget);
        return skinimage;
    }

    if (widget->IsOfType<TBImageWidget>())
    {
        AImageWidget* imagewidget = new AImageWidget(context_, false);
        imagewidget->SetWidget(widget);
        WrapWidget(imagewidget, widget);
        return imagewidget;
    }
    if (widget->IsOfType<TBClickLabel>())
    {
        AClickLabel* nwidget = new AClickLabel(context_, false);
        nwidget->SetWidget(widget);
        WrapWidget(nwidget, widget);
        return nwidget;
    }

    if (widget->IsOfType<TBCheckBox>())
    {
        ACheckBox* nwidget = new ACheckBox(context_, false);
        nwidget->SetWidget(widget);
        WrapWidget(nwidget, widget);
        return nwidget;
    }

    if (widget->IsOfType<TBRadioButton>())
    {
        ARadioButton* nwidget = new ARadioButton(context_, false);
        nwidget->SetWidget(widget);
        WrapWidget(nwidget, widget);
        return nwidget;
    }

    if (widget->IsOfType<TBBarGraph>())
    {
        ABargraph* nwidget = new ABargraph(context_, false);
        nwidget->SetWidget(widget);
        WrapWidget(nwidget, widget);
        return nwidget;
    }

    if (widget->IsOfType<TBSelectList>())
    {
        ASelectList* nwidget = new ASelectList(context_, false);
        nwidget->SetWidget(widget);
        WrapWidget(nwidget, widget);
        return nwidget;
    }

    if (widget->IsOfType<TBMessageWindow>())
    {
        AMessageWindow* nwidget = new AMessageWindow(context_, NULL, "", false);
        nwidget->SetWidget(widget);
        WrapWidget(nwidget, widget);
        return nwidget;
    }

    if (widget->IsOfType<TBPromptWindow>())
    {
        APromptWindow* nwidget = new APromptWindow(context_, NULL, "", false);
        nwidget->SetWidget(widget);
        WrapWidget(nwidget, widget);
        return nwidget;
    }

    if (widget->IsOfType<TBFinderWindow>())
    {
        AFinderWindow* nwidget = new AFinderWindow(context_, NULL, "", false);
        nwidget->SetWidget(widget);
        WrapWidget(nwidget, widget);
        return nwidget;
    }

    if (widget->IsOfType<TBTabContainer>())
    {
        ATabContainer* nwidget = new ATabContainer(context_, false);
        nwidget->SetWidget(widget);
        WrapWidget(nwidget, widget);
        return nwidget;
    }

    if (widget->IsOfType<SceneViewWidget>())
    {
        ASceneView* nwidget = new ASceneView(context_, false);
        nwidget->SetWidget(widget);
        WrapWidget(nwidget, widget);
        return nwidget;
    }


    if (widget->IsOfType<TBLayout>())
    {
        ALayout* layout = new ALayout(context_, (UI_AXIS) widget->GetAxis(), false);
        layout->SetWidget(widget);
        WrapWidget(layout, widget);
        return layout;
    }

    if (widget->IsOfType<TBWidget>())
    {
        AWidget* nwidget = new AWidget(context_, false);
        nwidget->SetWidget(widget);
        WrapWidget(nwidget, widget);
        return nwidget;
    }


    return 0;
}

void AUI::OnWidgetDelete(tb::TBWidget *widget)
{

}

bool AUI::OnWidgetDying(tb::TBWidget *widget)
{
    return false;
}

void AUI::OnWindowClose(tb::TBWindow *window)
{
    if (widgetWrap_.Contains(window))
    {
        AWidget* widget = widgetWrap_[window];
        VariantMap eventData;
        eventData[AWindowClosed::P_WINDOW] = widget;
        widget->SendEvent(E_AWINDOWCLOSED, eventData);
    }
}

void AUI::OnWidgetFocusChanged(TBWidget *widget, bool focused)
{
    if (widgetWrap_.Contains(widget))
    {
        VariantMap evData;
        AWidget* uiWidget = widgetWrap_[widget];
        evData[AWidgetFocusChanged::P_WIDGET]  = uiWidget;
        evData[AWidgetFocusChanged::P_FOCUSED]  = focused;
        uiWidget->SendEvent(E_AWIDGETFOCUSCHANGED, evData);
    }
}

AWidget* AUI::GetWidgetAt(int x, int y, bool include_children)
{
    if (!initialized_)
        return 0;
    return WrapWidget(rootWidget_->GetWidgetAt(x, y, include_children));
}

bool AUI::OnWidgetInvokeEvent(tb::TBWidget *widget, const tb::TBWidgetEvent &ev)
{
    return false;
}

}
