// APromptWindow application source code


void setup_uipromptwindow( AWidget @layout, AView @uiview )
{
    Array<AWidget@> dest = layout.SearchAWidgetClass( "TBButton" ); 
    for (uint ii = 0; ii < dest.length; ii++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest[ii], "WidgetEvent", "HandleUipromptwindowEvent" );
}

void HandlePromptCompleteEvent(StringHash eventType, VariantMap& eventData)
{
    AppLog( "APromptWindow event : the window " + eventData["Title"].GetString()
            + " file was " + eventData["Selected"].GetString()
            + ", the button pressed was " + eventData["Reason"].GetString());
}

void HandleUipromptwindowEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() == "uipromptwindowcode" )
        {
            AppLog( "APromptWindow support : " + widget.GetId() + " was pressed " );
            ViewCode ( "Scripts/code_apromptwindow.as", widget.GetParent() );
        }
        if (widget.GetId() ==  "uipromptwindowlayout" )
        {
            AppLog( "APromptWindow support : " + widget.GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_apromptwindow.ui.txt", widget.GetParent() );
        }

        if (widget.GetId() == "stringfinder" )
        {
            AppLog( "APromptWindow action : " + widget.GetId() + " was pressed ");
            APromptWindow @windowp = APromptWindow( uiview, widget.GetId());
            SubscribeToEvent(windowp, "APromptComplete", "HandlePromptCompleteEvent" );
            windowp.Show( "WindowTitle", "Message in window", "preset value", 0, 0, 0);
        }
    }
}

