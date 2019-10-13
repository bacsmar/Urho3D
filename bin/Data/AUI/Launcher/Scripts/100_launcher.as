// launcher example
// using AUI et al
// JimMarlowe
// MIT License

#include "AUI/Scripts/Utilities/Sample.as"
#include "configuration.as"

VariantMap localVars;

// sample database
Array<String>cppSamples;
Array<String>asSamples;
Array<String>luaSamples;
Array<String>auiSamples;
Array<String>auiluaSamples;

String execargs = " -p \"Data;CoreData;Data/AUI;Data/AUI/Periodic\" -w -s ";

void Start()
{
    // Execute the common startup for samples
    SampleStart();

    // Create a scene which will not be actually rendered
    scene_ = Scene();

    poke_at_android();  // for settings load&save 
    
    CreateArgDatabase();
    
    CreateProgramDatabase();

    ReadConfiguration();
    
    // Create the user interface
    CreateAUI();

    // Set the mouse mode to use in the sample
    AUISetSoftMouse();
}

void CreateProgramDatabase()
{
    String cppdir = fileSystem.programDir; // where we the c++ samples live
    String asdir = cppdir + "Data/Scripts/";  // where the Angelscript samples live
    String luadir = cppdir + "Data/LuaScripts/"; // where the Lua samples live
    String auidir = cppdir + "Data/AUI/Scripts/"; // where the AUI + Angelscript samples live
    String auiluadir = cppdir + "Data/AUI/LuaScripts/"; // where the AUI + Lua samples live

    Array<String> rawFiles = fileSystem.ScanDir(cppdir, "*", SCAN_FILES, false);
    rawFiles.Sort();
    for (uint nn=0; nn< rawFiles.length; nn++ )
    {
        if ( rawFiles[nn][1] >= '0' && rawFiles[nn][1] <= '9' ) cppSamples.Push ( rawFiles[nn] ); // its a sample
    }
    rawFiles.Clear();
    rawFiles = fileSystem.ScanDir(asdir, "*", SCAN_FILES, false);
    rawFiles.Sort();
    for (uint nn=0; nn< rawFiles.length; nn++ )
    {
        if ( rawFiles[nn][1] >= '0' && rawFiles[nn][1] <= '9' && rawFiles[nn].EndsWith(".as") ) 
            asSamples.Push ( rawFiles[nn] ); // its a sample
    }
    rawFiles.Clear();
    rawFiles = fileSystem.ScanDir(luadir, "*", SCAN_FILES, false);
    rawFiles.Sort();
    for (uint nn=0; nn< rawFiles.length; nn++ )
    {
        if ( rawFiles[nn][1] >= '0' && rawFiles[nn][1] <= '9' && rawFiles[nn].EndsWith(".lua")  ) 
            luaSamples.Push ( rawFiles[nn] ); // its a sample
    }
    rawFiles.Clear();
    rawFiles = fileSystem.ScanDir(auidir, "*", SCAN_FILES, false);
    rawFiles.Sort();
    for (uint nn=0; nn< rawFiles.length; nn++ )
    {
        if ( rawFiles[nn][1] >= '0' && rawFiles[nn][1] <= '9' && rawFiles[nn].EndsWith(".as")) 
            auiSamples.Push ( rawFiles[nn] ); // its a sample
    }
    rawFiles.Clear();
    rawFiles = fileSystem.ScanDir(auiluadir, "*", SCAN_FILES, false);
    rawFiles.Sort();
    for (uint nn=0; nn< rawFiles.length; nn++ )
    {
        if ( rawFiles[nn][1] >= '0' && rawFiles[nn][1] <= '9' && rawFiles[nn].EndsWith(".lua")) 
            auiluaSamples.Push ( rawFiles[nn] ); // its a sample
    }

}


void CreateAUI()
{
    AUIInit ( "AUI/resources/default_font/vera.ttf", "Vera", 14, "AUI/Launcher/Scenes/100_launcher.ui.txt" );

    // set up some stuff for mobile, so we can use the same app code & layouts
    // by lying about the device DPI. Everyone lies about DPI.
    String platform = GetPlatform();
    if ( (platform == "Android" ) || (platform == "iOS"))
    {
        aui.LoadSkin("Textures/mobile.tb.txt","");
        if (graphics.width > 1200)
            aui.SetDefaultFont("Vera", 14);
        else 
            aui.SetDefaultFont("Vera", 10);
    }
    else {
        aui.LoadSkin("Textures/desktop.tb.txt","");
    }
    
    AView@ uiview = aui.GetFocusedView(); // get the topmost aui widget
    AWidget @button = uiview.FindWidget("uiexit");
    SubscribeToEvent( button, "WidgetEvent", "HandleButtons" );
    button = uiview.FindWidget("uilaunchargs");
    SubscribeToEvent( button, "WidgetEvent", "HandleButtons" );
    AWidget @samples = uiview.FindWidget("uisamples");

    for (uint nn=0; nn<99; nn++) // add the samples
    {
        CreateSampleEntry( nn, samples );
    }

}

void CreateSampleEntry ( int num, AWidget @container )
{
    // calc if anyone has this number ...
    String mynumstr = String(num);  //search string
    
    if ( mynumstr.length < 2 ) mynumstr = "0" + String(num);  // single digits get a 0 infront...
    
    int cppgot = -1, asgot = -1, luagot = -1, auigot = -1, auiluagot = -1; //who
    
    for ( uint n1 = 0; n1<cppSamples.length; n1++) 
        if ( cppSamples[n1].StartsWith ( mynumstr ) ) cppgot = n1;
    for ( uint n2 = 0; n2<asSamples.length; n2++) 
        if ( asSamples[n2].StartsWith ( mynumstr ) ) asgot = n2;
    for ( uint n3 = 0; n3<luaSamples.length; n3++) 
        if ( luaSamples[n3].StartsWith ( mynumstr ) ) luagot = n3;
    for ( uint n4 = 0; n4<auiSamples.length; n4++) 
        if ( auiSamples[n4].StartsWith ( mynumstr ) ) auigot = n4;
    for ( uint n5 = 0; n5<auiluaSamples.length; n5++) 
        if ( auiluaSamples[n5].StartsWith ( mynumstr ) ) auiluagot = n5;
        
    if (num == 95)  // this is a funny program... tag it
    {   
        asgot = 0;
        luagot = 0;
    }

    if ( cppgot == -1 && asgot == -1 && luagot == -1 && auigot == -1 && auiluagot == -1 )
        return;
        
    ALayout @holder = ALayout();
    holder.Load("Scenes/sample_entry.ui.txt");

    AWidget @ mywidget = holder.GetWidget("titlew"); // get the component parts and rename, gray as necessary...
    if ( mywidget !is null )
    {
        String title = FindProgramCpp(mynumstr);
        mywidget.SetText( title );
    }

    AImageWidget@ myimg = cast<AImageWidget>(holder.GetWidget("imagew")); 
    if ( myimg !is null )
    {
        myimg.SetImage(FindProgramPix(mynumstr));
    }

    mywidget = holder.GetWidget("00cpp");
    if ( mywidget !is null )
    {
        if ( cppgot > -1 )
            mywidget.SetId ( mynumstr + "cpp" );
        else 
            mywidget.SetState(UI_WIDGET_STATE_DISABLED,true);
        SubscribeToEvent( mywidget, "WidgetEvent", "HandleSpawn" );
    }
    mywidget = holder.GetWidget("00as");
    if ( mywidget !is null )
    {
        if ( asgot > -1 )
        {
            mywidget.SetId( mynumstr + "as" );
        }
        else 
            mywidget.SetState(UI_WIDGET_STATE_DISABLED,true);
        SubscribeToEvent( mywidget, "WidgetEvent", "HandleSpawn" );
    }
    mywidget = holder.GetWidget("00lua");
    if ( mywidget !is null )
    {
        if ( luagot > -1 )
        {
            mywidget.SetId ( mynumstr + "lua" );
        }
        else 
            mywidget.SetState(UI_WIDGET_STATE_DISABLED,true);
        SubscribeToEvent( mywidget, "WidgetEvent", "HandleSpawn" );
    }
    mywidget = holder.GetWidget("00auias");
    if ( mywidget !is null )
    {
        if ( auigot > -1 )
        {
            mywidget.SetId ( mynumstr + "auias" );
        }
        else 
            mywidget.SetState(UI_WIDGET_STATE_DISABLED,true);
        SubscribeToEvent( mywidget, "WidgetEvent", "HandleSpawn" );
    }
    mywidget = holder.GetWidget("00auilua");
    if ( mywidget !is null )
    {
        if ( auiluagot > -1 )
        {
            mywidget.SetId ( mynumstr + "auilua" );
        }
        else 
            mywidget.SetState(UI_WIDGET_STATE_DISABLED,true);
        SubscribeToEvent( mywidget, "WidgetEvent", "HandleSpawn" );
    }

    container.AddChild(holder);
}

String FindProgramCpp ( String numstr )
{
    for ( uint n1 = 0; n1<cppSamples.length; n1++) 
        if ( cppSamples[n1].StartsWith ( numstr ) ) return cppSamples[n1];
    return "";
}

String FindProgramAs ( String numstr )
{
    if ( numstr == "95" ) // exception -funny program, return fullish path
      return "Data/AUI/Periodic/Scripts/periodic.as";

    for ( uint n1 = 0; n1<asSamples.length; n1++) 
        if ( asSamples[n1].StartsWith ( numstr ) ) return "Data/Scripts/" + asSamples[n1];
    return "";
}

String FindProgramLua ( String numstr )
{
    if ( numstr == "95" ) // exception -funny program, return fullish path
      return "Data/AUI/Periodic/LuaScripts/periodic.lua";

    for ( uint n1 = 0; n1<luaSamples.length; n1++) 
        if ( luaSamples[n1].StartsWith ( numstr ) ) return "Data/LuaScripts/" + luaSamples[n1];
    return "";
}

String FindProgramAuiAs ( String numstr )
{
    for ( uint n1 = 0; n1<auiSamples.length; n1++) 
        if ( auiSamples[n1].StartsWith ( numstr ) ) return "Data/AUI/Scripts/" + auiSamples[n1];
    return "";
}

String FindProgramAuiLua ( String numstr )
{
    for ( uint n1 = 0; n1<auiluaSamples.length; n1++) 
        if ( auiluaSamples[n1].StartsWith ( numstr ) ) return "Data/AUI/LuaScripts/" + auiluaSamples[n1];
    return "";
}

String FindProgramPix ( String numstr )
{
   return "Textures/" + numstr + "_pix.jpg";
}

void run_program ( String myprogram )
{
    String numstr = myprogram.Substring(0,2); //decompose string XXtech
    String tech = myprogram.Substring(2);
    String execstr;
    String pgmdir = fileSystem.programDir;
    
    if ( tech == "cpp" )
    {
         execstr = pgmdir + FindProgramCpp ( numstr );   
    }
    if ( tech == "as" )
    {
           execstr = pgmdir + "Urho3DPlayer " +  pgmdir + FindProgramAs ( numstr );   
    }
    if ( tech == "lua" )
    {
         execstr = pgmdir + "Urho3DPlayer " +  pgmdir + FindProgramLua ( numstr );   
    }
    if ( tech == "auias" )
    {
         execstr = pgmdir + "Urho3DPlayer " +  pgmdir + FindProgramAuiAs ( numstr );   
    }
    if ( tech == "auilua" )
    {
         execstr = pgmdir + "Urho3DPlayer " +  pgmdir + FindProgramAuiLua ( numstr );   
    }

    if ( execstr != "" )
        fileSystem.SystemCommandAsync ( execstr + execargs);

}


void HandleButtons(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() == "uiexit" )
        {
            engine.Exit();
        }
        if (widget.GetId() ==  "uilaunchargs" )
        {
            AView@ uiview = aui.GetFocusedView();
            AWindow @win2 = AWindow();
            win2.SetSettings ( UI_WINDOW_SETTINGS_DEFAULT );
            win2.SetText("Launch Arguments" );
            win2.Load("Scenes/configuration.ui.txt");
            win2.ResizeToFitContent();
            uiview.AddChild(win2);
            win2.Center();
            PresetConfiguration( win2 );
            win2.SetCloseDelegate(true);
            SubscribeToEvent( win2, "AWidgetEditCanceled", "HandleUserWindowClose" );
        }
    }
}

void HandleUserWindowClose(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Widget"].GetPtr();
    if ( widget is null ) return;
    AWindow @mywin = cast<AWindow@>(widget);
    if ( mywin !is null )
        mywin.Close();
}

void HandleSpawn(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK )
    {
        run_program ( widget.GetId() );
    }
}

void poke_at_android() // actually pokes at everything.
{
    // make some global paths

    String platform = GetPlatform();
    if ((platform == "Android") || (platform == "iOS"))
        localVars["BasePath"] = fileSystem.userDocumentsDir; // somewhere writable on mobile
    else
        localVars["BasePath"] = fileSystem.GetAppPreferencesDir("urho3d", "100_launcher"); // desktop systems

    localVars["SettingsPath"] = localVars["BasePath"].GetString() + "settings/";

    // install scaffolding if it does not exist
    if ( !fileSystem.DirExists ( localVars["BasePath"].GetString() ) )  // install scaffolding
    {
        if (!fileSystem.CreateDir(localVars["BasePath"].GetString()) )
            log.Debug ( "poke_at_android() Could not create = " + localVars["BasePath"].ToString() );
    }
    if ( !fileSystem.DirExists ( localVars["SettingsPath"].GetString() ) )  // install scaffolding
    {
        if (!fileSystem.CreateDir(localVars["SettingsPath"].GetString()) )
            log.Debug ( "poke_at_android() Could not create = " +  localVars["SettingsPath"].ToString() );
    }
}

// Create XML patch instructions for screen joystick layout specific to this sample app
String patchInstructions =
        "<patch>" +
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button2']]\">" +
        "        <attribute name=\"Is Visible\" value=\"false\" />" +
        "    </add>" +
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Hat0']]\">" +
        "        <attribute name=\"Is Visible\" value=\"false\" />" +
        "    </add>" +
        "</patch>";
