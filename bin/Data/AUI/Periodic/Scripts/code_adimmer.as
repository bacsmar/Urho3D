// ADimmer application source code


void setup_uidimmer( AWidget @layout )
{
    Array<AWidget@> dest = layout.SearchAWidgetClass( "TBButton" ); 
    for (uint ii = 0; ii < dest.length; ii++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest[ii], "WidgetEvent", "HandleUidimmerEvent" );
}

void HandleModalCompleteEvent(StringHash eventType, VariantMap& eventData)
{
    AppLog( "ADimmer event : the window " + eventData["Title"].GetString()
            + " file was " + eventData["Selected"].GetString()
            + ", the button pressed was " + eventData["Reason"].GetString());
}

void HandleUidimmerEvent(StringHash eventType, VariantMap& eventData)
{
    String refid = eventData["RefID"].GetString();
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    AWidget@ mylayout = cast<AWidget@>(widget.FindWidget("pageuidimmer"));
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() == "uimessagewindowcode" )
        {
            AppLog( "ADimmer support : " + widget.GetId() + " was pressed " );
            ViewCode ( "Scripts/code_amessagewindow.as", widget.GetParent() );
        }
        if (widget.GetId() ==  "uimessagewindowlayout" )
        {
            AppLog( "ADimmer support : " + widget.GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_amessagewindow.ui.txt", widget.GetParent() );
        }

        if (widget.GetId() == "modalfinder" )
        {
            AppLog( "ADimmer action : " + widget.GetId() + " was pressed ");
            APromptWindow @windowp = APromptWindow( uiview, widget.GetId());
            SubscribeToEvent(windowp, "APromptComplete", "HandleModalCompleteEvent" );
            windowp.Show( "Modal Prompt", "Modal Selection in window", "preset value", 1, 0, 0);
        }
        if (widget.GetId() ==  "modalok" )
        {
            AppLog( "ADimmer support : " + widget.GetId() + " was pressed ");
            AMessageWindow @mess2 = AMessageWindow( mylayout, "mymess2");
            SubscribeToEvent(mess2, "WidgetEvent", "HandleUimessagewindowEvent" );
            mess2.Show("MessageWindow - OK", "Modal MessageWindow - OK button", UI_MESSAGEWINDOW_SETTINGS_OK, true, 0, 0);
        }
        if (widget.GetId() ==  "modalokcancel" )
        {
            AppLog( "ADimmer support : " + widget.GetId() + " was pressed ");
            AMessageWindow @mess3 = AMessageWindow(mylayout, "mymess3");
            SubscribeToEvent(mess3, "WidgetEvent", "HandleUimessagewindowEvent" );
            mess3.Show("MessageWindow - OK CANCEL", "Modal MessageWindow - OK CANCEL buttons", UI_MESSAGEWINDOW_SETTINGS_OK_CANCEL, true, 0, 0);
        }
        if (widget.GetId() ==  "modalyesno" )
        {
            AppLog( "ADimmer support : " + widget.GetId() + " was pressed ");
            AMessageWindow @mess4 = AMessageWindow( mylayout, "mymess4");
            SubscribeToEvent(mess4, "WidgetEvent", "HandleUimessagewindowEvent" );
            mess4.Show( "MessageWindow - YES NO", "Modal MessageWindow - YES NO buttons", UI_MESSAGEWINDOW_SETTINGS_YES_NO, true, 0, 0);
        }
        if (widget.GetId() == "modalfilefinder" )
        {
            AppLog( "ADimmer action : " + widget.GetId() + " was pressed ");
            AFinderWindow @winf = AFinderWindow(uiview, widget.GetId());
            winf.FindFile("Modal Find a File", "", 1, 0, 0);
        }
        if (widget.GetId() ==  "modalfolderfinder" )
        {
            AppLog( "ADimmer action : " + widget.GetId() + " was pressed ");
            AFinderWindow @windowd = AFinderWindow(uiview, widget.GetId() );
            windowd.FindPath("Modal Find a Folder", "", 1, 0, 0);
        }
    }
    else
    {
        AppLog( "AMessageWindow event : " + widget.GetId() );
    }
}

