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

#pragma once

#include <TurboBadger/tb_widgets_listener.h>

#include "../Core/Object.h"
#include "../Graphics/Graphics.h"

#include "../AUI/AEnums.h"
#include "../AUI/ABatch.h"

namespace Urho3D
{

class VertexBuffer;
class ARenderer;
class AWidget;
class AView;
class APopupWindow;
class MessageBox;

//@AS Bind Gen Urho3DSubsystem BindingName=AUI Type=AUI --no

//@ASBindGen ExternalClass Name=Object ExcludeSubclassRegistration
//@ASBindGen    Urho3D::RegisterObject <${templateName}> (engine, ${bindingName});

//used to be class URHO3D_API AUI : public Object, private tb::TBWidgetListener
//@ASBindGen Class ObjectType=Ref
class URHO3D_API AUI : public Object, private tb::TBWidgetListener
{
    friend class AView;

    URHO3D_OBJECT(AUI, Object)

public:

    /// Construct.
    //@ASBindGen Constructor UseUrho3DScriptContext_arg0
    AUI(Context* context);
    /// Destruct.
    virtual ~AUI();

    tb::TBWidget* GetRootWidget() { return rootWidget_; }

    //@ASBindGen Function AddRef_arg-1
    AWidget* GetRootAWidget() { return rootAWidget_; } // to help bindings

    bool LoadResourceFile(tb::TBWidget* widget, const String& filename);
    bool LoadResourceFile(AWidget* widget, const String& filename);

    //@ASBindGen Function
    void SetKeyboardDisabled(bool disabled) {keyboardDisabled_ = disabled; }
    //@ASBindGen Function
    void SetInputDisabled(bool disabled) { inputDisabled_ = disabled; }

    void Render(bool resetRenderTargets = true);

    //@ASBindGen Function
    void Initialize(const String& languageFile);

    void Shutdown();

    //@ASBindGen Function
    void LoadSkin(const String& skin, const String& overrideSkin = String::EMPTY);
    bool GetSkinLoaded() { return skinLoaded_; }

    /// Load the default skin, will also look in resoures for UI/Skin/skin.ui.txt and
    /// UI/Skin/Override/skin.ui.txt for base skin and possible override (TODO: baked in UI setting for load from project)

    //@ASBindGen Function
    void LoadDefaultPlayerSkin();

    //@ASBindGen Function
    void AddFont(const String& fontFile, const String &name);

    //@ASBindGen Function
    void SetDefaultFont(const String& name, int size);

    bool IsWidgetWrapped(tb::TBWidget* widget);

    // wrap an existing widget we new'd from script
    void WrapWidget(AWidget* widget, tb::TBWidget* tbwidget);

    // given a TB widget, creating a AWidget
    AWidget* WrapWidget(tb::TBWidget* widget);

    bool UnwrapWidget(tb::TBWidget* widget);

    unsigned DebugGetWrappedWidgetCount() { return widgetWrap_.Size(); }

    void PruneUnreachableWidgets();

    //@ASBindGen Function
    void GetTBIDString(unsigned id, String& value);

    //@ASBindGen Function
    bool GetFocusedWidget();

    /// request exit on next frame
    void RequestExit() { exitRequested_ = true; inputDisabled_ = true; }

    ARenderer* GetRenderer() { return renderer_; }

    //@ASBindGen Function AddRef_arg-1
    AWidget* GetWidgetAt(int x, int y, bool include_children);

    //@ASBindGen Function
    bool GetBlockChangedEvents() const { return changedEventsBlocked_ > 0; }

    //@ASBindGen Function
    void SetBlockChangedEvents(bool blocked = true);

    //@ASBindGen Function AddRef_arg-1
    AWidget* GetHoveredWidget();

    /// Get the currently focused view
    //@ASBindGen Function AddRef_arg-1
    AView* GetFocusedView() const { return focusedView_; }

private:

    static WeakPtr<Context> uiContext_;
    static void TBFileReader(const char* filename, void** data, unsigned* length);
    static void TBIDRegisterStringCallback(unsigned id, const char* value);

    void HandlePostUpdate(StringHash eventType, VariantMap& eventData);
    void HandleRenderUpdate(StringHash eventType, VariantMap& eventData);
    void HandleExitRequested(StringHash eventType, VariantMap& eventData);

    // TBWidgetListener
    void OnWidgetDelete(tb::TBWidget *widget) override;
    bool OnWidgetDying(tb::TBWidget *widget) override;    
    void OnWidgetFocusChanged(tb::TBWidget *widget, bool focused) override;
    bool OnWidgetInvokeEvent(tb::TBWidget *widget, const tb::TBWidgetEvent &ev) override;
    void OnWindowClose(tb::TBWindow *window) override;

    /// Add a AView to UI subsystem, happens immediately at AView creation
    void AddAView(AView* uiView);
    /// Set the currently focused view
    void SetFocusedView(AView* uiView);
    /// Removes a AView from the UI subsystem, readding a view is not encouraged
    void RemoveAView(AView* uiView);

    tb::TBWidget* rootWidget_;
    AWidget* rootAWidget_;  // to help bindings
    ARenderer* renderer_;

    WeakPtr<Graphics> graphics_;

    HashMap<tb::TBWidget*, SharedPtr<AWidget> > widgetWrap_;
    HashMap<unsigned, String> tbidToString_;

    WeakPtr<APopupWindow> tooltip_;

    int changedEventsBlocked_;

    bool inputDisabled_;
    bool keyboardDisabled_;
    bool initialized_;
    bool skinLoaded_;
    bool consoleVisible_;
    bool exitRequested_;
    
    float tooltipHoverTime_;

    Vector<SharedPtr<AView>> uiViews_;

    WeakPtr<AView> focusedView_;

    // Events
    void HandleScreenMode(StringHash eventType, VariantMap& eventData);
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    void HandleConsoleClosed(StringHash eventType, VariantMap& eventData);
};

#ifdef URHO3D_ANGELSCRIPT
/// Register UI library objects.
void URHO3D_API RegisterAUILibrary(Context* context);
#endif

}
