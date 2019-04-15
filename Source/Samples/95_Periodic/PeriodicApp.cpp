//
// Copyright (c) 2014-2017, THUNDERBEAST GAMES LLC All rights reserved
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

#include <Urho3D/Engine/Application.h>
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/SceneEvents.h>
#include <Urho3D/Graphics/Texture2D.h>
#include <Urho3D/Graphics/Zone.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Core/Timer.h>
#include <Urho3D/AUI/AUI.h>
#include <Urho3D/AUI/AEvents.h>
#include <Urho3D/AUI/AView.h>
#include <Urho3D/AUI/ALayout.h>
#include <Urho3D/AUI/ACheckBox.h>
#include <Urho3D/AUI/ATextField.h>
#include <Urho3D/AUI/AButton.h>
#include <Urho3D/AUI/AEditField.h>
#include <Urho3D/AUI/ATabContainer.h>
#include <Urho3D/AUI/AWindow.h>
#include <Urho3D/AUI/AFinderWindow.h>
#include <Urho3D/AUI/APromptWindow.h>
#include <Urho3D/AUI/AMultiItem.h>
#include <Urho3D/Resource/XMLFile.h>
#include <Urho3D/IO/Log.h>

#include "PeriodicApp.h"
#include "Spinner.h"

URHO3D_DEFINE_APPLICATION_MAIN(PeriodicApp)

PeriodicApp::PeriodicApp(Context* context) :
    Application(context)
{
    // Register an object factory for the Rotator component
    context->RegisterFactory<Rotator>();
}


void PeriodicApp::Setup()
{
    engineParameters_["WindowWidth"] = 1280; // Modify engine startup parameters
    engineParameters_["WindowHeight"] = 720;
    engineParameters_["FullScreen"]  = false;
    engineParameters_["Headless"]    = false;
    engineParameters_["Sound"]       = false;
    engineParameters_["LogName"]     = GetSubsystem<FileSystem>()->GetAppPreferencesDir("urho3d", "logs") + GetTypeName() + ".log";
    engineParameters_["ResourcePaths"] = "Data;CoreData;Data/AUI;Data/AUI/Periodic";

    // Construct a search path to find the resource prefix with two entries:
    // The first entry is an empty path which will be substituted with program/bin directory -- this entry is for binary when it is still in build tree
    // The second and third entries are possible relative paths from the installed program/bin directory to the asset directory -- these entries are for binary when it is in the Atomic SDK installation location
#if 0
    if (!engineParameters_.Contains(EP_RESOURCE_PREFIX_PATHS))
    {
        // TODO: This is dependent on a source build
        String resourcePrefix = ToString("%s/Resources;%s/Submodules/AtomicExamples/FeatureExamples/CPlusPlus", ATOMIC_ROOT_SOURCE_DIR, ATOMIC_ROOT_SOURCE_DIR);
        engineParameters_[EP_RESOURCE_PREFIX_PATHS] = resourcePrefix;
    }
#endif
}

void PeriodicApp::Start()
{
    AUI* ui = GetSubsystem<AUI>();
    ui->Initialize("resources/language/lng_en.tb.txt"); // "DefaultUI/language/lng_en.tb.txt"
    ui->LoadDefaultPlayerSkin();
    ui->AddFont( "resources/default_font/vera.ttf", "Vera" );
    ui->SetDefaultFont("Vera", 12);

    uiview_ = new AView(context_); // create new AView

    SetWindowTitleAndIcon(); // Set custom window Title & Icon

    SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(PeriodicApp, HandleKeyDown));  // to handle the keys

    DoSomething(); // your game code goes here
}

void PeriodicApp::Stop()
{
    // possibly clean up allocated memory
}

void PeriodicApp::HandleKeyDown(StringHash eventType, VariantMap& eventData)
{
    using namespace KeyDown;

    int key = eventData[P_KEY].GetInt();
    if(key == KEY_ESCAPE)
    {
        engine_->Exit();
    }
#if 0
    else if (key == KEY_F1)    // Toggle console with F1
    {
        GetSubsystem<AUI>()->ToggleConsole();
    }
    else if (key == KEY_F2)    // Toggle debug HUD with F2
    {
        GetSubsystem<AUI>()->ToggleDebugHud();
    }
#endif
}

void PeriodicApp::SetWindowTitleAndIcon()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    Graphics* graphics = GetSubsystem<Graphics>();
    graphics->SetWindowTitle("PeriodicApp");
    Image* icon = cache->GetResource<Image>("Textures/AtomicLogo32.png");
    graphics->SetWindowIcon(icon);
}

//
// This is the entry point for your 3d game
//
void PeriodicApp::DoSomething()
{
    GetSubsystem<Input>()->SetMouseVisible(true); // mousey on!

    ResourceCache* cache = GetSubsystem<ResourceCache>();
    scene_ = new Scene(context_);
    scene_->CreateComponent<Octree>();
    Node* lightNode = scene_->CreateChild("DirectionalLight");
    lightNode->SetDirection(Vector3(0.6f, -1.0f, 0.8f));
    Light* light = lightNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_DIRECTIONAL);
    Node *cameraNode_ = scene_->CreateChild("Camera");
    cameraNode_->CreateComponent<Camera>();
    cameraNode_->SetPosition(Vector3(-4.7f, 3.6f, -16.2f));
    cameraNode_->SetRotation(Quaternion(11.4f, 15.8f, 0.0f));
    Renderer* renderer = GetSubsystem<Renderer>();
    SharedPtr<Viewport> viewport(new Viewport(context_, scene_, cameraNode_->GetComponent<Camera>()));
    renderer->SetViewport(0, viewport);

    AUI* ui = GetSubsystem<AUI>();  // get the ui pointer
    ui->AddFont("Textures/BrokenGlass.ttf", "BrokenGlass"); // add a gooder font
 
    // set up some stuff for mobile, so we can use the same app code & layouts, when we can deploy on mobile
    ui->LoadSkin("Textures/desktop.tb.txt"); // load in the app skin

    ALayout* lo0 = new ALayout(context_);  // make the host widget for all visible ui
    lo0->SetRect ( uiview_->GetRect ()); //size it to fill the screen area
    lo0->SetLayoutConfig( "YAGAC" );  //all-in-one setting
    lo0->SetSkinBg ("background_solid");  // make it look gooder
    lo0->Load("Scenes/main_layout.ui.txt"); // load the main layout
    uiview_->AddChild(lo0); // And make it show up.

    ATabContainer *maintb = (ATabContainer *)lo0->GetWidget("maintabs");
    ATabContainer *acttb = (ATabContainer *)lo0->GetWidget("primarytabs");
    ATabContainer *semitb = (ATabContainer *)lo0->GetWidget("moretabs");
    ATabContainer *viewtb = (ATabContainer *)lo0->GetWidget("supporttabs");
    ATabContainer *supporttb = (ATabContainer *)lo0->GetWidget("atomictabs");
    supporttb->SetCurrentPage(0); 
    viewtb->SetCurrentPage(0); 
    semitb->SetCurrentPage(0); 
    acttb->SetCurrentPage(0);
    maintb->SetCurrentPage(0); // do this or else the tab contents look like crap!
    
    uilog_ = (ATextField*)lo0->GetWidget("LogText");
    AView *someview = lo0->GetView();
    AWidget *ea = lo0->GetWidget("exitapp");
    SubscribeToEvent(ea, E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleExitEvent));
    AWidget *lt = lo0->GetWidget("liteapp");
    SubscribeToEvent(lt, E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleExitEvent));
    AWidget *dr = lo0->GetWidget("darkapp");
    SubscribeToEvent(dr, E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleExitEvent));
 
    setup_table( lo0 );
    setup_awidget(  lo0->GetWidget("pageuiwidget") );
    setup_abargraph(  lo0->GetWidget("pageuibargraph") );
    setup_abutton(  lo0->GetWidget("pageuibutton") );
    setup_acheckbox( lo0->GetWidget("pageuicheckbox"));
    setup_aclicklabel(  lo0->GetWidget("pageuiclicklabel") );
    setup_acolorwheel(  lo0->GetWidget("pageuicolorwheel") );
    setup_acolorwidget( lo0->GetWidget("pageuicolorwidget") );
    setup_acontainer( lo0->GetWidget("pageuicontainer"));
    setup_aeditfield(  lo0->GetWidget("pageuieditfield") );
    setup_afinderwindow( lo0->GetWidget("pageuifinderwindow"), someview );
    setup_afontdescription(  lo0->GetWidget("pageuifontdescription") );
    setup_aimagewidget(  lo0->GetWidget("pageuiimagewidget") );
    setup_ainlineselect(  lo0->GetWidget("pageuiinlineselect") );
    setup_alayoutparams(  lo0->GetWidget("pageuilayoutparams") );
    setup_alayout(  lo0->GetWidget("pageuilayout"), someview );
    setup_amenuitem( lo0->GetWidget("pageuimenuitem") );
    setup_amenuwindow(  lo0->GetWidget("pageuimenuwindow") );
    setup_amessagewindow(  lo0->GetWidget("pageuimessagewindow") );
    setup_amultiitem( lo0->GetWidget("pageuimultiitem") );
    setup_apromptwindow(  lo0->GetWidget("pageuipromptwindow"), someview );
    setup_apulldownmenu(  lo0->GetWidget("pageuipulldownmenu") );
    setup_aradiobutton(  lo0->GetWidget("pageuiradiobutton") );
    setup_asceneview(  lo0->GetWidget("pageuisceneview") );
    setup_ascrollbar(  lo0->GetWidget("pageuiscrollbar") );
    setup_ascrollcontainer(  lo0->GetWidget("pageuiscrollcontainer") );
    setup_asection(  lo0->GetWidget("pageuisection") );
    setup_aselectdropdown(  lo0->GetWidget("pageuiselectdropdown") );
    setup_aselectitem(  lo0->GetWidget("pageuiselectitem") );
    setup_aselectlist(  lo0->GetWidget("pageuiselectlist") );
    setup_aseparator(  lo0->GetWidget("pageuiseparator") );
    setup_askinimage(  lo0->GetWidget("pageuiskinimage") );
    setup_aslider(  lo0->GetWidget("pageuislider") );
    setup_atabcontainer(  lo0->GetWidget("pageuitabcontainer") );
    setup_atextfield(  lo0->GetWidget("pageuitextfield") );
    setup_atexturewidget(  lo0->GetWidget("pageuitexturewidget") );
    setup_awindow(  lo0->GetWidget("pageuiwindow"), someview );
    AppLog ( "Ready" );
}

void PeriodicApp::AppLog( const String &logtext )
{
    if (uilog_ )
        uilog_->SetText ( logtext );
}

void PeriodicApp::ViewCode ( String filename, AWidget *layoutParent )
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    AView *someview = layoutParent->GetView();
    AWindow *window = new AWindow(context_);
    window->SetSettings ( UI_WINDOW_SETTINGS_DEFAULT );
    window->SetText( "Code Viewer");
    window->Load("Scenes/view_code.ui.txt");
    SharedPtr<File> filex = cache->GetFile(filename);
    String textx = filex->ReadText();
    filex->Close();
    AWidget *coder = window->GetWidget("viewCodeText");
    coder->SetText(textx);
    window->ResizeToFitContent();
    someview->AddChild(window);
    window->Center();
    AWidget *someok = window->GetWidget("viewCodeOK");
    SubscribeToEvent(someok, E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleViewCodeEvent ));
}

void PeriodicApp::HandleViewCodeEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    if (eventData[P_TYPE] == UI_EVENT_TYPE_CLICK)
    {
        AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
        if (widget)
        {
            AWindow *mywindow = static_cast<AWindow *>(FindTheWindowParent(widget)); 
            if (mywindow)     
                mywindow->Close();
        }
    }
}

void PeriodicApp::HandleExitEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;

    if (eventData[P_TYPE] == UI_EVENT_TYPE_CLICK)
    {
        AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
        if (widget)
        {
        	if (widget->GetId() == "exitapp" )
        	{
            	engine_->Exit();
			}
        	if (widget->GetId() == "liteapp" )
        	{
    			AUI* ui = GetSubsystem<AUI>();  // get the ui pointer
				ui->LoadSkin( "resources/default_skin_light/skin.tb.txt"); //  boom!
			}
         	if (widget->GetId() == "darkapp" )
        	{
    			AUI* ui = GetSubsystem<AUI>();  // get the ui pointer
				ui->LoadSkin( "resources/default_skin/skin.tb.txt"); //  boom!
			}
       }
    }
}

String PeriodicApp::EventReport( int eventNumber)
{
    switch ( eventNumber ) {
        case 0: return "UI_EVENT_TYPE_CLICK";
        case 1: return "UI_EVENT_TYPE_LONG_CLICK";
        case 2: return "UI_EVENT_TYPE_POINTER_DOWN";
        case 3: return "UI_EVENT_TYPE_POINTER_UP";
        case 4: return "UI_EVENT_TYPE_POINTER_MOVE";
        case 5: return "UI_EVENT_TYPE_RIGHT_POINTER_DOWN";
        case 6: return "UI_EVENT_TYPE_RIGHT_POINTER_UP";
        case 7: return "UI_EVENT_TYPE_WHEEL";
        case 8: return "UI_EVENT_TYPE_CHANGED";
        case 9: return "UI_EVENT_TYPE_KEY_DOWN";
        case 10: return "UI_EVENT_TYPE_KEY_UP";
        case 11: return "UI_EVENT_TYPE_SHORTCUT";
        case 12: return "UI_EVENT_TYPE_CONTEXT_MENU";
        case 13: return "UI_EVENT_TYPE_FILE_DROP";
        case 14: return "UI_EVENT_TYPE_TAB_CHANGED";
        case 15: return "UI_EVENT_TYPE_CUSTOM";
    }
    return "EVENT_UKNOWN";
}

AWidget *PeriodicApp::FindTheWindowParent( AWidget* fromThisWidget )
{
    tb::TBWidget *widgetx = fromThisWidget->GetInternalWidget();
    AUI* ui = GetSubsystem<AUI>();
 
    if (widgetx == NULL)
        return 0;

    if ( widgetx->GetClassName() == "TBWindow" || widgetx->GetClassName() == "TBDockWindow" ) 
        return ui->WrapWidget(widgetx);
    
    tb::TBWidget* tbw = widgetx->GetParent();
    while(tbw)
    {
        if ( tbw->GetClassName() == "TBWindow" || tbw->GetClassName() == "TBDockWindow" ) 
            return ui->WrapWidget(tbw);
        tbw = tbw->GetParent();
    }

    return 0; 
}
