// ACheckBox application source code

void setup_uicheckbox( AWidget @layout )
{
    Array<AWidget@> dest = layout.SearchAWidgetClass( "TBButton" ); 
    for (uint ii = 0; ii < dest.length; ii++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest[ii], "WidgetEvent", "HandleUicheckboxEvent" );

    AWidget @demochk = layout.GetWidget ("democheck");
    if (demochk !is null)
        SubscribeToEvent(demochk, "WidgetEvent", "HandleUicheckboxEvent");
}

void HandleUicheckboxEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() == "uicheckboxcode" )
        {
            AppLog( "ACheckBox support : " + widget.GetId() + " was pressed " );
            ViewCode ( "Scripts/code_acheckbox.as", widget.GetParent() );
        }
        if (widget.GetId() ==  "uicheckboxlayout" )
        {
            AppLog( "ACheckBox support : " + widget.GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_acheckbox.ui.txt", widget.GetParent() );
        }

        if (widget.GetId() == "democheck" )
        {
            AppLog( "ACheckBox event : " + widget.GetId() + " was pressed, state = " + String ( widget.GetValue() ) );
        }

        if (widget.GetId() ==  "checkset" )
        {
            AWidget @demochk = widget.FindWidget ("democheck");
            if (demochk !is null)
            {
                demochk.SetValue (1);
                AppLog( "ACheckBox action : " + widget.GetId() + " was pressed, set state to 1" );
            }
        }
        if (widget.GetId() ==  "checkunset" )
        {
            AWidget @demochk = widget.FindWidget ("democheck");
            if (demochk !is null)
            {
                demochk.SetValue (0);
                AppLog( "ACheckBox action : " + widget.GetId() + " was pressed, set state to 0" );
            }
        }
    }
}

