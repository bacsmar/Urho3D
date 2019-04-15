// ARadioButton application source code


void setup_uiradiobutton( AWidget @layout)
{
    Array<AWidget@> dest = layout.SearchAWidgetClass( "TBButton" ); 
    for (uint ii = 0; ii < dest.length; ii++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest[ii], "WidgetEvent", "HandleUiradiobuttonEvent" );

    AWidget @demochk = layout.GetWidget ("demoradio");
    if ( demochk !is null)
        SubscribeToEvent(demochk, "WidgetEvent", "HandleUiradiobuttonEvent" );
}

void HandleUiradiobuttonEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() == "uiradiobuttoncode" )
        {
            AppLog( "ARadioButton support : " + widget.GetId() + " was pressed " );
            ViewCode ( "Scripts/code_aradiobutton.as", widget.GetParent() );
        }
        if (widget.GetId() ==  "uiradiobuttonlayout" )
        {
            AppLog( "ARadioButton support : " + widget.GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_aradiobutton.ui.txt", widget.GetParent() );
        }

        if (widget.GetId() == "demoradio" )
        {
            AppLog( "ARadioButton event : " + widget.GetId() + " was pressed, state = " + String ( widget.GetValue() ) );
        }

        if (widget.GetId() ==  "radioset" )
        {
            AWidget @demochk = widget.FindWidget ("demoradio");
            if (demochk !is null)
            {
                demochk.SetValue (1);
                AppLog( "ARadioButton action : " + widget.GetId() + " was pressed, set state to 1" );
            }
        }
        if (widget.GetId() ==  "radiounset" )
        {
            AWidget @demochk = widget.FindWidget ("demoradio");
            if (demochk !is null)
            {
                demochk.SetValue (0);
                AppLog( "ARadioButton action : " + widget.GetId() + " was pressed, set state to 0" );
            }
        }
    }
}

