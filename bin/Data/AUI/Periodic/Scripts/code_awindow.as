// AWindow application source code


void setup_uiwindow( AWidget @layout, AView @uiview )
{
    Array<AWidget@> dest = layout.SearchAWidgetClass( "TBButton" ); 
    for (uint ii = 0; ii < dest.length; ii++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest[ii], "WidgetEvent", "HandleUiwindowEvent" );
}

void HandleUiwindowEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() == "uiwindowcode" )
        {
            AppLog( "AWindow support : " + widget.GetId() + " was pressed " );
            ViewCode ( "Scripts/code_awindow.as", widget.GetParent() );
        }
        if (widget.GetId() ==  "uiwindowlayout" )
        {
            AppLog( "AWindow support : " + widget.GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_awindow.ui.txt", widget.GetParent() );
        }

        if (widget.GetId() == "windowdemo" )
        {
            AppLog( "AWindow action : " + widget.GetId() + " was pressed " );
            AWindow @win1 = AWindow();
            win1.SetSettings ( UI_WINDOW_SETTINGS_DEFAULT );
            win1.SetText("AWindow demo (a login dialog)");
            win1.Load("Scenes/login_dialog.ui.txt");
            win1.ResizeToFitContent();
            uiview.AddChild(win1);
            win1.Center();
            AWidget @login = win1.GetWidget("login");
            SubscribeToEvent(login, "WidgetEvent", "HandleUiwindowEvent" );
            AWidget @cancel = win1.GetWidget("cancel");
            SubscribeToEvent(cancel, "WidgetEvent", "HandleUiwindowEvent" );
        }
        if (widget.GetId() == "login" )
        {
            AppLog( "AWindow action : " + widget.GetId() + " was pressed " );
            AWindow @mywin = cast<AWindow @>(FindTheWindowParent(widget));
            if (mywin !is null)
                mywin.Close();
        }
        if (widget.GetId() == "cancel" )
        {
            AppLog( "AWindow action : " + widget.GetId() + " was pressed " );
            AWindow @mywindow = cast<AWindow @>(FindTheWindowParent(widget));
            if (mywindow !is null)
                mywindow.Close();
        }
        if (widget.GetId() == "windowdemo1" )
        {
            AppLog( "AWindow action : " + widget.GetId() + " was pressed " );
            AWindow @win2 = AWindow();
            win2.SetSettings ( UI_WINDOW_SETTINGS_DEFAULT );
            win2.SetText("AWindow demo (a table)" );
            win2.Load("Scenes/sheet.ui.txt");
            win2.ResizeToFitContent();
            uiview.AddChild(win2);
            win2.Center();
        }
        if (widget.GetId() == "windowdemo2" )
        {
            AppLog( "AWindow action : " + widget.GetId() + " was pressed " );
            AWindow @win3 = AWindow();
            win3.SetAxis(UI_AXIS_X);
            win3.SetSettings ( UI_WINDOW_SETTINGS_DEFAULT );
            win3.SetText(" " );
            win3.Load("Scenes/sheet.ui.txt");
            win3.ResizeToFitContent();
            uiview.AddChild(win3);
            win3.Center();
        }
        if (widget.GetId() == "windowdemo3" )
        {
            AppLog( "AWindow action : " + widget.GetId() + " was pressed " );
            AWindow@window = AWindow();
            window.SetId ("WinCloseOverride" );
            window.SetSettings ( UI_WINDOW_SETTINGS_DEFAULT );
            window.SetText("AWindow with Close Override action" );
            window.Load("Scenes/sheet.ui.txt");
            window.ResizeToFitContent();
            window.SetCloseDelegate(true);
            SubscribeToEvent(window, "AWidgetEditCanceled", "HandleCloseOverrideEvent");
            uiview.AddChild(window);
            window.Center();
        }
    }
}

void HandleCloseOverrideEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget@ widget = cast<AWidget@>(eventData["Widget"].GetPtr());
    if ( widget is null ) return;

    AMessageWindow @mess4 = AMessageWindow(uiview, "mymess4");
    SubscribeToEvent(mess4, "WidgetEvent", "HandleCloseYesNoEvent");
    mess4.Show( "Close Window Request", "Do you really want to close this window?", UI_MESSAGEWINDOW_SETTINGS_YES_NO, false, 0, 0);
}

void HandleCloseYesNoEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget@ widget = cast<AWidget@>(eventData["Target"].GetPtr());
    if ( widget is null ) return;
    AWindow@ mywin = cast<AWindow@>(widget.FindWidget("WinCloseOverride"));
    String refid = eventData["RefID"].GetString();
    if (eventData["Type"].GetInt() == UI_EVENT_TYPE_CLICK)
    {
        if (refid == "TBMessageWindow.yes" )
        {
            AppLog( "AWindow event : " + refid + " closed the AMessageWindow");
            if (mywin !is null)
                mywin.Close();
        }
        if (refid == "TBMessageWindow.no" )
        {
            AppLog( "AWindow event : " + refid + " closed the AMessageWindow");
            //wait for it ...
        }
    }
}

