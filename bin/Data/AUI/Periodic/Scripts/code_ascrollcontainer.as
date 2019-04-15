// AScrollContainer application source code

void setup_uiscrollcontainer( AWidget @layout )
{
    Array<AWidget@> dest = layout.SearchAWidgetClass( "TBButton" ); 
    for (uint ii = 0; ii < dest.length; ii++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest[ii], "WidgetEvent", "HandleUiscrollcontainerEvent" );
}

void HandleUiscrollcontainerEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() == "uiscrollcontainercode" )
        {
            AppLog( " support : " + widget.GetId() + " was pressed " );
            ViewCode ( "Scripts/code_ascrollcontainer.as", widget.GetParent() );
        }
        if (widget.GetId() ==  "uiscrollcontainerlayout" )
        {
            AppLog( " support : " + widget.GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_ascrollcontainer.ui.txt", widget.GetParent() );
        }
    }
}

