// uEdit-lite a (real) simple text editor, using AUI
// uEdit preferences
// JimMarlowe
// MIT License

class user_settings
{
    int selectFontName;
    int selectFontSize;
    int selectEditorSkin;
    int selectTheme;
    int selectToolbar;
    int selectStatusbar;

    user_settings()
    {
        selectFontName = 0;
        selectFontSize = 4;
        selectEditorSkin = 0;
        selectTheme = 0;
        selectToolbar = 1;
        selectStatusbar = 1;
    }

    void SetSetting ( int num, int value )
    {
        switch (num )
        {
        case 0 :
            selectFontName = value;
            break;
        case 1 :
            selectFontSize = value;
            break;
        case 2 :
            selectEditorSkin = value;
            break;
        case 3 :
            selectTheme = value;
            break;
        case 4 :
            selectToolbar = value;
            break;
        case 5 :
            selectStatusbar = value;
            break;
        default:
            break;
        }
    }

    int GetSetting (int num )
    {
        switch (num )
        {
        case 0 :
            return selectFontName;
        case 1 :
            return selectFontSize;
        case 2 :
            return selectEditorSkin;
        case 3 :
            return selectTheme;
        case 4 :
            return selectToolbar;
        case 5 :
            return selectStatusbar;
        default:
            return -1;
        }
        return -1;
    }

};

void HandleSaveOnClose(StringHash eventType, VariantMap& eventData)
{
    AWidget @widgetwin = eventData["Widget"].GetPtr();
    if ( widgetwin is null ) return;
    AWindow @mywin = cast<AWindow@>(widgetwin);
    if ( mywin !is null )
    {
        AWidget @widget = mywin.GetWidget("selectFontName");
        if ( widget !is null ) settings.selectFontName = int(widget.GetValue());
        widget = mywin.GetWidget("selectFontSize");
        if ( widget !is null ) settings.selectFontSize = int(widget.GetValue());
        widget = mywin.GetWidget("selectEditorSkin");
        if ( widget !is null ) settings.selectEditorSkin = int(widget.GetValue());
        widget = mywin.GetWidget("selectTheme");
        if ( widget !is null ) settings.selectTheme = int(widget.GetValue());
        widget = mywin.GetWidget("selectToolbar");
        if ( widget !is null ) settings.selectToolbar = int(widget.GetValue());
        widget = mywin.GetWidget("selectStatusbar");
        if ( widget !is null ) settings.selectStatusbar = int(widget.GetValue());

        mywin.Close();
    }
}


// fill in the box with current settings
void PresetConfiguration( AWindow @win )
{
    AWidget @widget = win.GetWidget("selectFontName");
    if ( widget !is null ) widget.SetValue(settings.selectFontName);
    widget = win.GetWidget("selectFontSize");
    if ( widget !is null )  widget.SetValue(settings.selectFontSize);
    widget = win.GetWidget("selectEditorSkin");
    if ( widget !is null )  widget.SetValue(settings.selectEditorSkin);
    widget = win.GetWidget("selectTheme");
    if ( widget !is null )  widget.SetValue(settings.selectTheme);
    widget = win.GetWidget("selectToolbar");
    if ( widget !is null )  widget.SetValue(settings.selectToolbar);
    widget = win.GetWidget("selectStatusbar");
    if ( widget !is null )  widget.SetValue(settings.selectStatusbar);

    widget = win.GetWidget("ClearRecentButton");
    SubscribeToEvent(widget, "WidgetEvent", "HandleClearRecentEvent" );
}


void HandleClearRecentEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        recentfiles.Clear();

        APulldownMenu @pdr = cast<AButton@>(widget.FindWidget("RecentMenu"));
        if ( pdr !is null )
        {
            // block the events for the pulldownmenu or else it will report a change
            aui.SetBlockChangedEvents(true);
            ASelectItemSource @amis = ASelectItemSource();
            pdr.SetSource(amis);
            aui.SetBlockChangedEvents(false);
        }
    }
}

void ReadConfiguration()
{
    String configFilename = localVars["SettingsPath"].GetString() + "settings.txt";
    int count = 0;
    if ( fileSystem.FileExists(configFilename) )
    {
        File file( configFilename, FILE_READ);
        if ( file.open )
        {
            while (!file.eof)
            {
                String line = file.ReadLine().Trimmed();
                settings.SetSetting( count, line.ToInt() );
                count++;
            }
            file.Close();
        }
    }
}

void WriteConfiguration()
{
    String configFilename = localVars["SettingsPath"].GetString() + "settings.txt";
    File file( configFilename, FILE_WRITE);
    if (file.open)
    {
        for (int nn=0; nn<6; nn++ )
        {
            file.WriteLine( String ( settings.GetSetting(nn) ) );
        }
        file.Close();
    }
}


void ReadRecent()
{
    String configFilename = localVars["SettingsPath"].GetString() + "recent.txt";
    if ( fileSystem.FileExists(configFilename) )
    {
        File file( configFilename, FILE_READ);
        if ( file.open )
        {
            while (!file.eof)
            {
                String line = file.ReadLine();
                recentfiles.Push(GetNativePath(line));
            }
            file.Close();
        }
    }
}

void WriteRecent()
{
    String configFilename = localVars["SettingsPath"].GetString() + "recent.txt";
    File file( configFilename, FILE_WRITE);
    if (file.open)
    {
        for (uint nn=0; nn<recentfiles.length; nn++ )
        {
            file.WriteLine( GetNativePath(recentfiles[nn]) );
        }
        file.Close();
    }
}
