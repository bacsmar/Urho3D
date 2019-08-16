// uEdit-lite a (real) simple text editor, using AUI
// JimMarlowe
// MIT License
#include "uGlobals.as"
#include "configuration.as"
#include "EditorHolder.as"

void Start()
{
    // Set custom window Title & Icon
    SetWindowTitleAndIcon();

    // Enable OS cursor
    input.mouseVisible = true;

    // for settings load&save
    poke_at_android();

    // Create the user interface
    CreateAUI();

    SubscribeToEvent( "DropFile", "HandleDropFileEvent" );

    // this is how scripts get the command line args
    Array<String>@ args = GetArguments();
    for (uint ii = 2; ii < args.length; ++ii)
    {
        String argx = args[ii];
        if ( argx.Compare("-pp") == 0 ) { ii = ii + 1; continue; } // skip next arg
        else if ( argx.Compare("-p") == 0 ) { ii = ii + 1; continue; } // skip next arg
        else if ( argx.Compare("-pf") == 0 ) { ii = ii + 1; continue; } // skip next arg
        else if ( argx.Compare("-ap") == 0 ) { ii = ii + 1; continue; } // skip next arg
        else if ( argx.Compare("-ds") == 0 ) { ii = ii + 1; continue; } // skip next arg
        else if ( fileSystem.FileExists(argx) )
        {
            OpenAnEditor(argx);
        }
    }
}

// this happens at the window corner exit and Alt+F4
// cant interrupt them like file-exit
void Stop()
{
    WriteConfiguration();
    WriteRecent();
    log.Close();
}

void CloseProgram()
{
    bool alerted = false;
    for (uint nn = 0; nn < myFiles.length; nn++ )
    {
        if ( myFiles[nn].changed )
        { 
            alerted = true;
        }
    }

    if ( alerted )
    {
        AMessageWindow @mess1 = AMessageWindow(  aui.GetFocusedView(), "savebeforeclose");
        SubscribeToEvent(mess1, "WidgetEvent", "HandleExitQuizEvent" );
        mess1.Show( "Unsaved Files", "Save the unsaved files before exit?",
            UI_MESSAGEWINDOW_SETTINGS_YES_NO, true, 0, 0);
    }
    else
    {
        WriteConfiguration();
        WriteRecent();
        log.Close();
        engine.Exit();
    }
}

void HandleExitQuizEvent(StringHash eventType, VariantMap& eventData)
{
    String refid = eventData["RefID"].GetString();
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (refid == "TBMessageWindow.yes" )
        {
            for (uint nn = 0; nn < myFiles.length; nn++ )
            {
                if ( myFiles[nn].changed )
                { 
                    myFiles[nn].SaveTheFile();
                }
            }
            WriteConfiguration();
            WriteRecent();
            log.Close();
            engine.Exit();
        }
        if (refid == "TBMessageWindow.no" )
        {
            WriteConfiguration();
            WriteRecent();
            log.Close();
            engine.Exit();
       }
    }
}


void poke_at_android() // actually pokes at everything.
{
    // make some global paths
    String platform = GetPlatform();
    if ((platform == "Android") || (platform == "iOS"))
        localVars["BasePath"] = fileSystem.userDocumentsDir; // somewhere writable on mobile
    else
        localVars["BasePath"] = fileSystem.GetAppPreferencesDir("urho3d", "uEdit"); // desktop systems

    localVars["SettingsPath"] = localVars["BasePath"].GetString() + "settings/";
    localVars["LogPath"] = localVars["BasePath"].GetString() + "logs/";

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
    if ( !fileSystem.DirExists ( localVars["LogPath"].GetString() ) )  // install scaffolding
    {
        if (!fileSystem.CreateDir(localVars["LogPath"].GetString()) )
            log.Debug ( "poke_at_android() Could not create = " +  localVars["LogPath"].ToString() );
    }

    // capture logs into file instead of stdout, stderr, and only what we need
    String logFilename = localVars["LogPath"].GetString() + "uEditLog.txt";
    log.Open( logFilename );
    log.level = LOG_ERROR;
    log.quiet = true; // stop spamming

    @settings = user_settings(); // user settings

    ReadConfiguration();
}


void SetWindowTitleAndIcon()
{
    Image@ icon = cache.GetResource("Image", "Textures/AtomicLogo32.png");
    graphics.windowIcon = icon;
    graphics.windowTitle = "uEdit";
}


void AUIInit ( String defaultFont, String defaultFontHandle, int defaultFontSize, String layoutfile )
{
    aui = AUI; // Make some Atomic UI
    aui.Initialize("resources/language/lng_en.tb.txt");
    aui.LoadDefaultPlayerSkin();
    aui.AddFont( defaultFont, defaultFontHandle );
    aui.SetDefaultFont( defaultFontHandle, defaultFontSize );
    AView @uiview = AView(); // create new UIView
    uiview.SetSkinBg ("");  // no background skin, transparent.
    ALayout@ lo0 = ALayout();  // make the host widget for all visible ui
    lo0.SetId( "alayout0" ); //name it, incase we need to change it
    lo0.SetRect( uiview.GetRect()); //size it to fill the screen area
    lo0.SetLayoutConfig( "YAGAC" );  //all-in-one setting
    if ( layoutfile != "" )
        lo0.Load(layoutfile ); // load the main layout
    uiview.AddChild(lo0); // And make it show up.

    SubscribeToEvent( "AShortcut", "HandleShortcutEvent" );
}


void CreateAUI()
{
    int fontpt = 14;
    String platform = GetPlatform();
    if ( (platform == "Android" ) || (platform == "iOS"))  // dance with the font size
    { 
        if (graphics.width > 1200) fontpt = 14;
        else fontpt = 10;
    }
    else
    {
        if (graphics.width > 1900) fontpt = 24; // lots-o-pixels
    }
    
    AUIInit ( "resources/default_font/vera.ttf", "Vera", fontpt, "Scenes/uEdit.ui.txt" );
    aui.AddFont( "Fonts/Anonymous Pro.ttf", "AnonymousPro" );
    aui.AddFont( "Fonts/BlueHighway.ttf", "BlueHighway" );

    LoadUserSkins();

    AView@ uiview = aui.GetFocusedView(); // get the topmost aui widget

    Array<AWidget@> dest1 = uiview.SearchAWidgetClass( "TBPulldownMenu" );
    for (uint i1 = 0; i1 < dest1.length; i1++)
        SubscribeToEvent(dest1[i1], "WidgetEvent", "HandlePulldownmenuEvent" );

    AWidget @toolbar = uiview.FindWidget("uedit_toolbar");
    Array<AWidget@> dest2 = toolbar.SearchAWidgetClass( "TBButton" );
    for (uint i2 = 0; i2 < dest2.length; i2++)
        SubscribeToEvent(dest2[i2], "WidgetEvent", "HandleToolbarEvent" );

    ATabContainer @tcx = cast<ATabContainer@>(uiview.GetWidget("uedit_tabcontainer"));
    if ( tcx !is null)
    {
        tcx.SetCurrentPage(0);  // fix or it looks like crap

        // get the layout and make tabs start at the left.
        ALayout @uil = tcx.GetTabLayout();
        uil.SetLayoutConfig("XGLPL");
    }

    ReadRecent(); // fetch the latest recent files from last session

    // block the events for the pulldownmenu or else it will report a change
    aui.SetBlockChangedEvents(true);

    APulldownMenu @pdr = cast<AButton@>(uiview.GetWidget("RecentMenu"));
    if ( pdr !is null)
    {
        ASelectItemSource @amis = ASelectItemSource();
        for ( uint nn=0; nn<recentfiles.length; nn++)
        {
            amis.AddItem( ASelectItem( recentfiles[nn], recentfiles[nn], "" ) );
        }
        pdr.SetSource(amis);
    }

    AWidget @widx = uiview.FindWidget("uedit_toolbar");
    if ( widx !is null )
    {
        if ( settings.selectToolbar == 0 ) widx.SetVisibility(UI_WIDGET_VISIBILITY_GONE);
        else widx.SetVisibility(UI_WIDGET_VISIBILITY_VISIBLE);
    }
    widx = uiview.FindWidget("uedit_statusbar");
    if ( widx !is null )
    {
        if ( settings.selectStatusbar == 0 ) widx.SetVisibility(UI_WIDGET_VISIBILITY_GONE);
        else widx.SetVisibility(UI_WIDGET_VISIBILITY_VISIBLE);
    }
    
    if ( settings.selectTheme == 1 )
        aui.LoadSkin( "resources/default_skin_light/skin.tb.txt", "");

    aui.SetBlockChangedEvents(false);

    SubscribeToEvent("AWidgetFocusChanged", "HandleFocusEvent" );

    fix_menus_for_activeeditor();
}


void LoadUserSkins()
{
    // set up some stuff for mobile, so we can use the same app code & layouts
    // by lying about the device DPI. Everyone lies about DPI.
    String platform = GetPlatform();
    if ( (platform == "Android" ) || (platform == "iOS"))
    {
        aui.LoadSkin("Textures/mobile.tb.txt","");
    }
    else
    {
        if (graphics.width > 1900) // lots-o-pixels
            aui.LoadSkin("Textures/hitop.tb.txt","");
        else
            aui.LoadSkin("Textures/desktop.tb.txt","");
    }
}


void fix_menus_for_activeeditor()
{
    AView@ uiview = aui.GetFocusedView(); // get the topmost aui widget
    APulldownMenu @puf = cast<AButton@>(uiview.GetWidget("FileMenu"));
    if ( puf !is null )
    {
        for ( int nn=0; nn<puf.NumMenuItems(); nn++)
        {
            if ( puf.GetMenuItemId(nn) == "FileSave" )
            {
                if ( activeEditor is null) puf.SetMenuItemState(nn, 0);
                else puf.SetMenuItemState(nn, 1);
            }
            if ( puf.GetMenuItemId(nn) == "FileSaveAs" )
            {
                if ( activeEditor is null) puf.SetMenuItemState(nn, 0);
                else puf.SetMenuItemState(nn, 1);
            }
            if ( puf.GetMenuItemId(nn) == "FileClose" )
            {
                if ( activeEditor is null) puf.SetMenuItemState(nn, 0);
                else puf.SetMenuItemState(nn, 1);
            }
        }
    }
    APulldownMenu @pue = cast<AButton@>(uiview.GetWidget("EditMenu"));
    if ( pue !is null )
    {
        for ( int nn=0; nn<pue.NumMenuItems(); nn++)
        {
            if ( pue.GetMenuItemId(nn) == "EditUndo" )
            {
                if ( activeEditor is null) pue.SetMenuItemState(nn, 0);
                else
                {
                    if ( activeEditor.Editor.CanUndo()) pue.SetMenuItemState(nn, 1);
                    else pue.SetMenuItemState(nn, 0);
                }
            }
            if ( pue.GetMenuItemId(nn) == "EditRedo" )
            {
                if ( activeEditor is null) pue.SetMenuItemState(nn, 0);
                else
                {
                    if ( activeEditor.Editor.CanRedo()) pue.SetMenuItemState(nn, 1);
                    else pue.SetMenuItemState(nn, 0);
                }
            }
        }
    }
}


void HandleShortcutEvent(StringHash eventType, VariantMap& eventData)
{
    int mykey = eventData["Key"].GetInt();
    int myqual = eventData["Qualifiers"].GetInt();
    
    if ( mykey == KEY_Z && myqual == QUAL_CTRL ) // undo
    {
        if ( activeEditor !is null  )
            activeEditor.EditorUndo();
    }
    else if ( mykey == KEY_Y && myqual == QUAL_CTRL ) // redo
    {
        if ( activeEditor !is null  )
            activeEditor.EditorRedo();
    }
    else if ( mykey == KEY_S && myqual == QUAL_CTRL ) // save
    {
        if ( activeEditor !is null )
            activeEditor.SaveTheFile();
    }
    else if ( mykey == KEY_O && myqual == QUAL_CTRL ) // open
    {
        String preset = "";
        if ( activeEditor !is null )
            preset = GetPath ( activeEditor.FullPath );
        AFinderWindow @winfw = AFinderWindow(aui.GetFocusedView(), "KeyOpen" );
        SubscribeToEvent(winfw, "AFinderComplete", "HandleFinderCompleteEvent" );
        winfw.FindFile("Find a File", preset, 1, 0, 0);
    }
    else if ( mykey == KEY_N && myqual == QUAL_CTRL ) // new
    {
        OpenAnEditor ( "" );
    }
    else if ( mykey == KEY_Q && myqual == QUAL_CTRL ) // exit
    {
        CloseProgram();
    }
    else if ( mykey == KEY_W && myqual == QUAL_CTRL ) // close
    {
        if ( activeEditor !is null )
        {
            if ( activeEditor.changed ) // if its dirty, ask them if they'd like to save it
            {
                AMessageWindow @mess42 = AMessageWindow(  aui.GetFocusedView(), "savebeforeclose");
                SubscribeToEvent(mess42, "WidgetEvent", "HandleEditorSaveEvent" );
                mess42.Show( "Save File", "Save the current file before close?", 
                    UI_MESSAGEWINDOW_SETTINGS_YES_NO, true, 0, 0);
            }
            else
                CloseAnEditor ( activeEditor.FullPath ); // capture this
        }
    }
    else if ( mykey == KEY_F1 && myqual == QUAL_CTRL ) // help
    {
        ViewCode("Scripts/uedit_help.txt");
    }
}


// this is where we establish the "active" editor
void HandleFocusEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Widget"].GetPtr();
    bool gotfocus = eventData["Focused"].GetBool();
    if ( widget !is null )
    {
        if ( gotfocus )
        {
            for (uint nn = 0; nn < myFiles.length; nn++ )
            {
                if ( (myFiles[nn].TabWin is widget) || (myFiles[nn].Editor is widget) )
                {
                    @activeEditor = myFiles[nn];
                    activeEditor.MadeActive();
                }
            }
        }
    }
}


void HandleToolbarEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        AView@ uiview = aui.GetFocusedView(); // get the topmost aui widget
        if (widget.GetId() == "newtb" )
        {
            OpenAnEditor ( "" );
        }
        if (widget.GetId() == "opentb" )
        {
            String preset = "";
            if ( activeEditor !is null )
                preset = GetPath ( activeEditor.FullPath );
            AFinderWindow @winf = AFinderWindow(aui.GetFocusedView(), widget.GetId());
            SubscribeToEvent(winf, "AFinderComplete", "HandleFinderCompleteEvent" );
            winf.FindFile("Find a File", preset, 1, 0, 0);
        }
        if (widget.GetId() == "savetb" )
        {
            if ( activeEditor !is null )
                activeEditor.SaveTheFile();
        }
        if (widget.GetId() == "undotb" )
        {
            if ( activeEditor !is null  )
                activeEditor.EditorUndo();
        }
        if (widget.GetId() == "redotb" )
        {
            if ( activeEditor !is null  )
                activeEditor.EditorRedo();
        }
    }
}


void HandlePulldownmenuEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CHANGED )
    {
        AView@ uiview = aui.GetFocusedView(); // get the topmost aui widget
        if (widget.GetId() ==  "FileMenu" )
        {
            APulldownMenu @pdm = cast<AButton@>(widget);
            if ( pdm !is null)
            {
                if (  pdm.GetSelectedId() == "FileNew" )
                {
                    OpenAnEditor ( "" );
                }
                if ( pdm.GetSelectedId() == "FileOpen" )
                {
                    String preset = "";
                    if ( activeEditor !is null )
                        preset = GetPath ( activeEditor.FullPath );
                    AFinderWindow @winf = AFinderWindow(aui.GetFocusedView(), widget.GetId());
                    SubscribeToEvent(winf, "AFinderComplete", "HandleFinderCompleteEvent" );
                    winf.FindFile("Find a File", preset, 1, 0, 0);
                }
                if ( pdm.GetSelectedId() == "FileSave" )
                {
                    if ( activeEditor !is null )
                        activeEditor.SaveTheFile();
                }
                if ( pdm.GetSelectedId() == "FileSaveAs" )
                {
                    String preset = "";
                    if ( activeEditor !is null )
                        preset = GetPath ( activeEditor.FullPath );
                    AFinderWindow @winf = AFinderWindow(aui.GetFocusedView(), widget.GetId());
                    SubscribeToEvent(winf, "AFinderComplete", "HandleSaveAsEvent" );
                    winf.FindFile("Save File As", preset, 1, 0, 0);
                }
                if ( pdm.GetSelectedId() == "FileClose" )
                {
                    if ( activeEditor !is null )
                    {
                        if ( activeEditor.changed ) // if its dirty, ask them if they'd like to save it
                        {
                            AMessageWindow @mess4 = AMessageWindow(  aui.GetFocusedView(), "savebeforeclose");
                            SubscribeToEvent(mess4, "WidgetEvent", "HandleEditorSaveEvent" );
                            mess4.Show( "Save File", "Save the current file before close?", 
                                UI_MESSAGEWINDOW_SETTINGS_YES_NO, true, 0, 0);
                        }
                        else
                            CloseAnEditor ( activeEditor.FullPath ); // capture this
                    }
                }
                if ( pdm.GetSelectedId() == "FileExit" )
                {
                    CloseProgram();
                }
            }
        }
        if (widget.GetId() == "EditMenu" )
        {
            APulldownMenu @pdm = cast<AButton@>(widget);
            if ( pdm.GetSelectedId() == "EditUndo" )
            {
                if ( activeEditor !is null )
                {
                    if ( activeEditor.Editor.CanUndo() )
                        activeEditor.EditorUndo();
                }
            }
            if ( pdm.GetSelectedId() == "EditRedo" )
            {
                if ( activeEditor !is null )
                {
                    if ( activeEditor.Editor.CanRedo() )
                        activeEditor.EditorRedo();
                }
            }
        }
        if (widget.GetId() == "ViewMenu" )
        {
            APulldownMenu @pdm = cast<AButton@>(widget);
            if ( pdm.GetSelectedId() == "ViewToolbar" )
            {
                AWidget @widx = widget.FindWidget("uedit_toolbar");
                if ( widx !is null )
                {
                    if ( settings.selectToolbar == 0 ) settings.selectToolbar = 1; //toggle it
                    else settings.selectToolbar = 0;

                    if ( settings.selectToolbar == 0 )
                        widx.SetVisibility(UI_WIDGET_VISIBILITY_GONE);
                    else
                        widx.SetVisibility(UI_WIDGET_VISIBILITY_VISIBLE);
                }
            }
            if ( pdm.GetSelectedId() == "ViewStatusbar" )
            {
                AWidget @widx = widget.FindWidget("uedit_statusbar");
                if ( widx !is null )
                {
                    if ( settings.selectStatusbar == 0 ) settings.selectStatusbar = 1; //toggle it
                    else settings.selectStatusbar = 0;

                    if ( settings.selectStatusbar == 0 )
                        widx.SetVisibility(UI_WIDGET_VISIBILITY_GONE);
                    else
                        widx.SetVisibility(UI_WIDGET_VISIBILITY_VISIBLE);
                }
            }
            if ( pdm.GetSelectedId() == "ViewTheme" )
            {
                if ( settings.selectTheme == 0 ) settings.selectTheme = 1; //toggle it
                else settings.selectTheme = 0;

                if ( settings.selectTheme == 0 )
                    aui.LoadSkin( "resources/default_skin/skin.tb.txt", "");
                else
                    aui.LoadSkin( "resources/default_skin_light/skin.tb.txt", "");

                LoadUserSkins(); // and fix user app skins
            }
            if ( pdm.GetSelectedId() == "ViewPreferences" )
            {
                AWindow @win2 = AWindow();
                win2.SetSettings ( UI_WINDOW_SETTINGS_DEFAULT );
                win2.SetText("Preferences" );
                win2.Load("Scenes/configuration.ui.txt");
                win2.ResizeToFitContent();
                uiview.AddChild(win2);
                win2.Center();
                PresetConfiguration( win2 );
                win2.SetCloseDelegate(true);
                SubscribeToEvent( win2, "AWidgetEditCanceled", "HandleSaveOnClose" );
            }
        }
        if (widget.GetId() == "RecentMenu" )
        {
            APulldownMenu @pdr = cast<AButton@>(widget);
            if ( pdr !is null)
            {
                ATabContainer @tcx = cast<ATabContainer@>( widget.FindWidget("uedit_tabcontainer"));
                for (uint nn = 0; nn < myFiles.length; nn++ ) // check for same file
                {
                    if ( myFiles[nn].FullPath == String( pdr.GetSelectedId()) )
                    {
                        tcx.SetCurrentPage(nn); //turn the page
                        @activeEditor = myFiles[nn];   // feed it this file
                        activeEditor.Editor.SetFocus(); // give it focus
                        activeEditor.MadeActive(); //fix shit.
                        return;
                    }
                }
                // should we purge this entry ???
                if ( !fileSystem.FileExists( pdr.GetSelectedId() ))
                {
                    AMessageWindow @mess2a = AMessageWindow( aui.GetFocusedView(), "mymess2a");
                    mess2a.Show("File Error", "The selected file does not exist.",
                        UI_MESSAGEWINDOW_SETTINGS_OK, true, 0, 0);
                    return;
                }
                OpenAnEditor ( pdr.GetSelectedId() );
            }
        }
        if (widget.GetId() ==  "HelpMenu" )
        {
            APulldownMenu @pdm = cast<AButton@>(widget);
            if ( pdm.GetSelectedId() == "HelpHelp" )
            {
                ViewCode("Scripts/uedit_help.txt");
            }
            if ( pdm.GetSelectedId() == "HelpAbout" )
            {
                AMessageWindow @mess2 = AMessageWindow( uiview, "mymess2");
                mess2.Show("Help About", "This is the uEdit text editor. v1.0",
                    UI_MESSAGEWINDOW_SETTINGS_OK, false, 0, 0);
            }
       }
    }
}


void OpenAnEditor ( String filePathName )
{
    AView@ uiview = aui.GetFocusedView(); // get the topmost aui widget
    ATabContainer @tcx = cast<ATabContainer@>( uiview.FindWidget("uedit_tabcontainer"));
    EditorHolder fred = EditorHolder(); // make a new one, for an empty doc
    fred.CreateEditorWidgets ( tcx, GetNativePath(filePathName) );
    myFiles.Push(fred); //push it in.
    fred.Editor.SetFocus(); // give it focus
    activeEditor = fred; // feed it fred
    activeEditor.MadeActive(); //fix shit.
}


void CloseAnEditor (String recentFile)
{
    AView@ uiview = aui.GetFocusedView(); // get the topmost aui widget

    // then dump it.
    ATabContainer @tcx = cast<ATabContainer@>( uiview.FindWidget("uedit_tabcontainer"));
    int current = tcx.GetCurrentPage();
    tcx.DeletePage(current);
    tcx.Invalidate(); // invalidate isnt enough, a new tab has to be set.

    // clean up the holders
    UnsubscribeFromEvents( activeEditor.Editor );

    int where = myFiles.FindByRef( activeEditor );
    if ( where >= 0 )
        myFiles.Erase(where);

    @activeEditor = null;
    fix_menus_for_activeeditor(); //fix shit.

    // update the recent filelist
    APulldownMenu @pdr = cast<AButton@>(uiview.FindWidget("RecentMenu"));
    if ( pdr !is null && recentFile.Compare("") != 0 )
    {
        if ( recentfiles.Find(GetNativePath(recentFile)) < 0 ) // is it in there?
        {
            // block the events for the pulldownmenu or else it will report a change
            aui.SetBlockChangedEvents(true);
            recentfiles.Push(GetNativePath(recentFile));

            if (recentfiles.length > 14)  // limit it to 14 files
            {
                recentfiles.Erase(0); // pop one off the top.
            }

            ASelectItemSource @amis = ASelectItemSource();
            for ( uint nn=0; nn<recentfiles.length; nn++)
            {
                amis.AddItem( ASelectItem( recentfiles[nn], recentfiles[nn], "" ) );
            }
            pdr.SetSource(amis);
            aui.SetBlockChangedEvents(false); // unblock events
        }
    }
}


void HandleEditorSaveEvent(StringHash eventType, VariantMap& eventData)
{
    String refid = eventData["RefID"].GetString();
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (refid == "TBMessageWindow.yes" )
        {
            activeEditor.SaveTheFile();
            CloseAnEditor( activeEditor.FullPath );
        }
        if (refid == "TBMessageWindow.no" )
        {
            CloseAnEditor( activeEditor.FullPath );
        }
    }
}


void HandleSaveAsEvent(StringHash eventType, VariantMap& eventData)
{
    if ( eventData["Reason"].GetString() == "CANCEL" ) return; // they bailed

    if (activeEditor !is null )
    {
        activeEditor.SaveTheFileAs(eventData["Selected"].GetString());
    }
}


void HandleDropFileEvent(StringHash eventType, VariantMap& eventData)
{
    for (uint nn = 0; nn < myFiles.length; nn++ ) // check for same file
    {
        if ( myFiles[nn].FullPath == eventData["FileName"].GetString() )
        {
            AWidget @logger = aui.GetRootAWidget().FindWidget("LogText");
            if ( logger !is null )
            {
                logger.SetText ( "File " + eventData["Selected"].GetString() + " already loaded" );
            }
            return;
        }
    }

    OpenAnEditor ( eventData["FileName"].GetString() );
}


void HandleFinderCompleteEvent(StringHash eventType, VariantMap& eventData)
{
    if ( eventData["Reason"].GetString() == "CANCEL" ) return; // they bailed

    if ( !fileSystem.FileExists( eventData["Selected"].GetString()))
    {
        AMessageWindow @mess2a = AMessageWindow( aui.GetFocusedView(), "mymess2a");
        mess2a.Show("File Error", "The selected file does not exist.",
            UI_MESSAGEWINDOW_SETTINGS_OK, true, 0, 0);
        return;
    }

    for (uint nn = 0; nn < myFiles.length; nn++ ) // check for same file
    {
        if ( myFiles[nn].FullPath == eventData["Selected"].GetString() )
        {
            AWidget @logger = aui.GetRootAWidget().FindWidget("LogText");
            if ( logger !is null )
            {
                logger.SetText ( "File " + eventData["Selected"].GetString() + " already loaded" );
            }
            return;
        }
    }

    OpenAnEditor ( eventData["Selected"].GetString() );
}


void ViewCode ( String filename )
{
    AView@ uiview = aui.GetFocusedView(); // get the topmost aui widget

    AWindow @window = AWindow();
    if ( window !is null )
    {
        window.SetSettings ( UI_WINDOW_SETTINGS_DEFAULT );
        window.SetText( "uEdit Help Viewer");
        window.Load("Scenes/view_code.ui.txt");

        String textx = filename + " Not Found.";
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
        AWidget @wtf = cast<AWidget>(uiview);
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
        AWindow @mywindow = widget.GetParent().GetParent(); 
            if (mywindow !is null)     
                mywindow.Close();
    }
}


String GetNativePath(const String& pathName)
{
    if ( GetPlatform() == "Windows" )
        return pathName.Replaced('/', '\\');
    
    return pathName;
}
