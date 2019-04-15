// AMessageWindow application source code


void setup_uimessagewindow( AWidget @layout )
{
    Array<AWidget@> dest = layout.SearchAWidgetClass( "TBButton" ); 
    for (uint ii = 0; ii < dest.length; ii++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest[ii], "WidgetEvent", "HandleUimessagewindowEvent" );
}

void HandleUimessagewindowEvent(StringHash eventType, VariantMap& eventData)
{
    String refid = eventData["RefID"].GetString();
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    AWidget@ mylayout = cast<AWidget@>(widget.FindWidget("pageuimessagewindow"));
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() == "uimessagewindowcode" )
        {
            AppLog( "AMessageWindow support : " + widget.GetId() + " was pressed " );
            ViewCode ( "Scripts/code_amessagewindow.as", widget.GetParent() );
        }
        if (widget.GetId() ==  "uimessagewindowlayout" )
        {
            AppLog( "AMessageWindow support : " + widget.GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_amessagewindow.ui.txt", widget.GetParent() );
        }

        if (widget.GetId() ==  "msgnone" )
        {
            AppLog( "AMessageWindow support : " + widget.GetId() + " was pressed ");
            AMessageWindow @mess1 = AMessageWindow( mylayout, "mymess1");
            mess1.Show("MessageWindow - NONE", "this is a MessageWindow - None button", UI_MESSAGEWINDOW_SETTINGS_NONE, false, 0, 0);
        }
        if (widget.GetId() ==  "msgok" )
        {
            AppLog( "AMessageWindow support : " + widget.GetId() + " was pressed ");
            AMessageWindow @mess2 = AMessageWindow( mylayout, "mymess2");
            SubscribeToEvent(mess2, "WidgetEvent", "HandleUimessagewindowEvent" );
            mess2.Show("MessageWindow - OK", "this is a MessageWindow - OK button", UI_MESSAGEWINDOW_SETTINGS_OK, false, 0, 0);
        }
        if (widget.GetId() ==  "msgkcancel" )
        {
            AppLog( "AMessageWindow support : " + widget.GetId() + " was pressed ");
            AMessageWindow @mess3 = AMessageWindow(mylayout, "mymess3");
            SubscribeToEvent(mess3, "WidgetEvent", "HandleUimessagewindowEvent" );
            mess3.Show("MessageWindow - OK CANCEL", "this is a MessageWindow - OK CANCEL buttons", UI_MESSAGEWINDOW_SETTINGS_OK_CANCEL, false, 0, 0);
        }
        if (widget.GetId() ==  "msgyesno" )
        {
            AppLog( "AMessageWindow support : " + widget.GetId() + " was pressed ");
            AMessageWindow @mess4 = AMessageWindow( mylayout, "mymess4");
            SubscribeToEvent(mess4, "WidgetEvent", "HandleUimessagewindowEvent" );
            mess4.Show( "MessageWindow - YES NO", "this is a MessageWindow - YES NO buttons", UI_MESSAGEWINDOW_SETTINGS_YES_NO, false, 0, 0);
        }

        if (refid ==  "TBMessageWindow.ok" )
        {
            AppLog( "AMessageWindow event : " + refid + " closed the AMessageWindow");
        }
        if (refid ==  "TBMessageWindow.cancel" )
        {
            AppLog( "AMessageWindow event : " + refid + " closed the AMessageWindow");
        }
        if (refid ==  "TBMessageWindow.yes" )
        {
            AppLog( "AMessageWindow event : " + refid + " closed the AMessageWindow");
        }
        if (refid ==  "TBMessageWindow.no" )
        {
            AppLog( "AMessageWindow event : " + refid + " closed the AMessageWindow");
        }
    }
    else
    {
        //AppLog( "AMessageWindow event : " + widget.GetId() + " event type = " + EventReport(eventData[P_TYPE].GetInt()));
        AppLog( "AMessageWindow event : " + widget.GetId() );
    }
}

