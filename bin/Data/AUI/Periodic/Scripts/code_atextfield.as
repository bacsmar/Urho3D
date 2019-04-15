// ATextField application source code

void setup_uitextfield( AWidget @layout )
{
    Array<AWidget@> dest = layout.SearchAWidgetClass( "TBButton" ); 
    for (uint ii = 0; ii < dest.length; ii++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest[ii], "WidgetEvent", "HandleUitextfieldEvent" );
}

void HandleUitextfieldEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() == "uitextfieldcode" )
        {
            AppLog( " support : " + widget.GetId() + " was pressed " );
            ViewCode ( "Scripts/code_atextfield.as", widget.GetParent() );
        }
        if (widget.GetId() ==  "uitextfieldlayout" )
        {
            AppLog( " support : " + widget.GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_atextfield.ui.txt", widget.GetParent() );
        }
    }
}

