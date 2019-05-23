// This script is the main entry point of the example 

// include the components
#include "code_table.as"
#include "code_abargraph.as"
#include "code_abutton.as"
#include "code_acheckbox.as"
#include "code_aclicklabel.as"
#include "code_acolorwheel.as"
#include "code_acolorwidget.as"
#include "code_acontainer.as"
#include "code_aeditfield.as"
#include "code_afinderwindow.as"
#include "code_afontdescription.as"
#include "code_aimagewidget.as"
#include "code_ainlineselect.as"
#include "code_alayout.as"
#include "code_alayoutparams.as"
#include "code_amenuitem.as"
#include "code_amenuwindow.as"
#include "code_amessagewindow.as"
#include "code_amultiitem.as"
#include "code_apromptwindow.as"
#include "code_apulldownmenu.as"
#include "code_aradiobutton.as"
#include "code_asceneview.as"
#include "code_ascrollbar.as"
#include "code_ascrollcontainer.as"
#include "code_asection.as"
#include "code_aselectdropdown.as"
#include "code_aselectitem.as"
#include "code_aselectlist.as"
#include "code_aseparator.as"
#include "code_askinimage.as"
#include "code_aslider.as"
#include "code_atabcontainer.as"
#include "code_atextfield.as"
#include "code_atexturewidget.as"
#include "code_awidget.as"
#include "code_awindow.as"
#include "code_adimmer.as"
#include "code_alistview.as"
#include "code_abuttongrid.as"

// "globals"
AUI@ uia;
AView@ uiview;
AWidget@ uiroot;
ATextField@ logger;

void Start()
{
    // Enable OS cursor
    input.mouseVisible = true;

    //Load scene
    Scene @scene_ = Scene();
    // Load scene content prepared in the editor (XML format). GetFile() returns an open file from the resource system
    // which scene.LoadXML() will read
    scene_.LoadXML(cache.GetFile("Scenes/Scene.scene"));

    // build host for GUI, which there will be a lot of.
    @uia = AUI;
    // Create the Window and add it to the UI's root node
    uia.Initialize("AUI/resources/language/lng_en.tb.txt");
    uia.LoadDefaultPlayerSkin();
    uia.AddFont( "AUI/resources/default_font/vera.ttf", "Vera" );
    uia.SetDefaultFont("Vera", 12);
    @uiview = AView(); // create new AView
    @uiroot = uia.GetRootAWidget();

    ALayout@ lo0 = ALayout();  // make the host widget for all visible ui
    lo0.SetRect (uiview.GetRect()); //size it to fill the screen area
    lo0.SetLayoutConfig( "YAGAC" );  //all-in-one setting
    lo0.SetSkinBg ("background_solid");  // make it look presentable.

    // example of adding a font, will be used later
    uia.AddFont("Textures/BrokenGlass.ttf", "BrokenGlass");

    // set up some stuff for mobile, so we can use the same app code & layouts
    // by lying about the device DPI. Everyone lies about DPI.
    String platform = GetPlatform();
    if ( (platform == "Android" ) || (platform == "iOS"))
    {
        uia.LoadSkin("Textures/mobile.tb.txt","");
        if (graphics.width > 1200)
            uia.SetDefaultFont("Vera", 14);
        else 
            uia.SetDefaultFont("Vera", 10);
    }
    else {
        uia.LoadSkin("Textures/desktop.tb.txt","");
    }

    // load the main UI layout
    lo0.Load("Scenes/main_layout.ui.txt"); // load the main layout
    uiview.AddChild(lo0); // And make it show up.
    // uiwindow.PrintPrettyTree();

    // and get going
    @logger = lo0.GetWidget("LogText");  
    ATabContainer@ maintb = lo0.GetWidget("maintabs");
    ATabContainer@ acttb = lo0.GetWidget("primarytabs");
    ATabContainer@ semitb = lo0.GetWidget("moretabs");
    ATabContainer@ viewtb = lo0.GetWidget("supporttabs");
    ATabContainer@ supporttb = lo0.GetWidget("atomictabs");

    supporttb.SetCurrentPage(0); 
    viewtb.SetCurrentPage(0); 
    semitb.SetCurrentPage(0); 
    acttb.SetCurrentPage(0);
    maintb.SetCurrentPage(0); // do this or esle the tab contents look like crap!

    SubscribeToEvent("KeyDown","HandleKeyDown");
 
    AWidget @ea = lo0.GetWidget("exitapp");
    SubscribeToEvent(ea, "WidgetEvent", "HandleExitEvent");
    AWidget @lt = lo0.GetWidget("liteapp");
    SubscribeToEvent(lt, "WidgetEvent", "HandleExitEvent");
    AWidget @dr = lo0.GetWidget("darkapp");
    SubscribeToEvent(dr, "WidgetEvent", "HandleExitEvent");

    setup_table (lo0);
    setup_uibargraph( lo0.GetWidget("pageuibargraph") );
    setup_uibutton( lo0.GetWidget("pageuibutton") );
    setup_uicheckbox( lo0.GetWidget("pageuicheckbox"));
    setup_uiclicklabel( lo0.GetWidget("pageuiclicklabel") );
    setup_uicolorwheel(  lo0.GetWidget("pageuicolorwheel") );
    setup_uicolorwidget( lo0.GetWidget("pageuicolorwidget") );
    setup_uicontainer( lo0.GetWidget("pageuicontainer"));
    setup_uieditfield(  lo0.GetWidget("pageuieditfield") );
    setup_uifinderwindow( lo0.GetWidget("pageuifinderwindow"), uiview );
    setup_uifontdescription(  lo0.GetWidget("pageuifontdescription") );
    setup_uiimagewidget(  lo0.GetWidget("pageuiimagewidget") );
    setup_uiinlineselect(  lo0.GetWidget("pageuiinlineselect") );
    setup_uilayoutparams(  lo0.GetWidget("pageuilayoutparams") );
    setup_uilayout(  lo0.GetWidget("pageuilayout"), uiview );
    setup_uimenuitem( lo0.GetWidget("pageuimenuitem") );
    setup_uimenuwindow(  lo0.GetWidget("pageuimenuwindow") );
    setup_uimessagewindow(  lo0.GetWidget("pageuimessagewindow") );
    setup_uimultiitem( lo0.GetWidget("pageuimultiitem") );
    setup_uipromptwindow(  lo0.GetWidget("pageuipromptwindow"), uiview );
    setup_uipulldownmenu(  lo0.GetWidget("pageuipulldownmenu") );
    setup_uiradiobutton(  lo0.GetWidget("pageuiradiobutton") );
    setup_uisceneview(  lo0.GetWidget("pageuisceneview") );
    setup_uiscrollbar(  lo0.GetWidget("pageuiscrollbar") );
    setup_uiscrollcontainer(  lo0.GetWidget("pageuiscrollcontainer") );
    setup_uisection(  lo0.GetWidget("pageuisection") );
    setup_uiselectdropdown(  lo0.GetWidget("pageuiselectdropdown") );
    setup_uiselectitem(  lo0.GetWidget("pageuiselectitem") );
    setup_uiselectlist(  lo0.GetWidget("pageuiselectlist") );
    setup_uiseparator(  lo0.GetWidget("pageuiseparator") );
    setup_uiskinimage(  lo0.GetWidget("pageuiskinimage") );
    setup_uislider(  lo0.GetWidget("pageuislider") );
    setup_uitabcontainer(  lo0.GetWidget("pageuitabcontainer") );
    setup_uitextfield(  lo0.GetWidget("pageuitextfield") );
    setup_uitexturewidget(  lo0.GetWidget("pageuitexturewidget") );
    setup_uiwindow(  lo0.GetWidget("pageuiwindow"), uiview );
    setup_uiwidget(  lo0.GetWidget("pageuiwidget") );
    setup_uidimmer( lo0.GetWidget("pageuidimmer") );
    setup_uilistview( lo0.GetWidget("pageuilistview") );
    setup_uibuttongrid( lo0.GetWidget("pageuibuttongrid") );

    AppLog ( "Ready" );

}

void HandleExitEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() == "exitapp" )
        {
            engine.Exit();
        }
        if (widget.GetId() == "liteapp" )
        {
            uia.LoadSkin( "resources/default_skin_light/skin.tb.txt", ""); //  boom!
        }
        if (widget.GetId() == "darkapp" )
        {
            uia.LoadSkin( "resources/default_skin/skin.tb.txt", ""); //  boom!
        }
    }
}



void HandleKeyDown(StringHash eventType, VariantMap& eventData)
{
    int key = eventData["key"].GetInt();
    
    if(key == KEY_ESCAPE)
        engine.Exit();
}

void AppLog( const String &logtext )
{
    if (logger !is null)
        logger.SetText ( logtext );
}

void ViewCode ( String filename, AWidget @layoutParent )
{
    AView @someview = layoutParent.GetView();

    AWindow @window = AWindow();
    if ( window !is null )
    {
        window.SetSettings ( UI_WINDOW_SETTINGS_DEFAULT );
        window.SetText( "Code Viewer");
        window.Load("Scenes/view_code.ui.txt");

        String textx = "File Not Found.";
        File @filex = cache.GetFile(filename);
        if ( filex !is null )
        {
            textx = filex.ReadString();
            filex.Close();
        }
        AWidget @coder = window.GetWidget("viewCodeText");
        if ( coder !is null )
            coder.SetText(textx);
        window.ResizeToFitContent();
        AWidget @wtf = cast<AWidget>(someview);
        if ( wtf !is null )
        {
            AWindow @wtf1 = cast<AWindow>(window);
            if ( wtf1 !is null )
                wtf.AddChild(wtf1);
        }
        window.Center();
        AWidget @someok = window.GetWidget("viewCodeOK");
        if ( someok !is null )
            SubscribeToEvent(someok, "WidgetEvent", "HandleViewCodeEvent");
    }
}

void HandleViewCodeEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
            AWindow @mywindow = FindTheWindowParent(widget); 
            if (mywindow !is null)     
                mywindow.Close();
    }
}


AWidget @ FindTheWindowParent( AWidget@ fromThisWidget )
{
    if ( fromThisWidget is null )
        return null;

    if ( fromThisWidget.GetClassName() == "TBWindow" || fromThisWidget.GetClassName() == "TBDockWindow" ) 
        return fromThisWidget;
    
    AWidget@ tbw = fromThisWidget.GetParent();
    while(tbw !is null)
    {
        if ( tbw.GetClassName() == "TBWindow" || tbw.GetClassName() == "TBDockWindow" ) 
            return tbw;
        tbw = tbw.GetParent();
    }

    return null; 
}

// Rotator script object class. Script objects to be added to a scene node must implement the empty ScriptObject interface
class Rotator : ScriptObject
{
    Vector3 rotationSpeed;

    void SetRotationSpeed(const Vector3&in speed)
    {
        rotationSpeed = speed;
    }

    // Update is called during the variable timestep scene update
    void Update(float timeStep)
    {
        node.Rotate(Quaternion(rotationSpeed.x * timeStep, rotationSpeed.y * timeStep, rotationSpeed.z * timeStep));
    }
}

