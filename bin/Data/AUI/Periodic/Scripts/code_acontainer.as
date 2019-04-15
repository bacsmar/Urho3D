// AContainer application source code

void setup_uicontainer( AWidget @layout )
{
    Array<AWidget@> dest = layout.SearchAWidgetClass( "TBButton" ); 
    for (uint ii = 0; ii < dest.length; ii++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest[ii], "WidgetEvent", "HandleUicontainerEvent" );
}

void HandleUicontainerEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() == "uicontainercode" )
        {
            AppLog( "AContainer support : " + widget.GetId() + " was pressed " );
            ViewCode ( "Scripts/code_acontainer.as", widget.GetParent() );
        }
        if (widget.GetId() ==  "uicontainerlayout" )
        {
            AppLog( "AContainer support : " + widget.GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_acontainer.ui.txt", widget.GetParent() );
        }
    }
}

