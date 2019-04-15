// ASeparator application source code


void setup_uiseparator( AWidget @layout )
{
    Array<AWidget@> dest = layout.SearchAWidgetClass( "TBButton" ); 
    for (uint ii = 0; ii < dest.length; ii++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest[ii], "WidgetEvent", "HandleUiseparatorEvent" );
}

void HandleUiseparatorEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() == "uiseparatorcode" )
        {
            AppLog( "ASeparator support : " + widget.GetId() + " was pressed " );
            ViewCode ( "Scripts/code_aseparator.as", widget.GetParent() );
        }
        if (widget.GetId() ==  "uiseparatorlayout" )
        {
            AppLog( "ASeparator support : " + widget.GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_aseparator.ui.txt", widget.GetParent() );
        }
    }
}

