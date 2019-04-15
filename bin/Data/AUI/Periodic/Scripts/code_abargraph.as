// ABargraph application source code

void setup_uibargraph( AWidget @layout )
{
    Array<AWidget@> dest = layout.SearchAWidgetClass( "TBButton" ); 
    for (uint ii = 0; ii < dest.length; ii++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest[ii], "WidgetEvent", "HandleUibargraphEvent");
}

void HandleUibargraphEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() == "uibargraphcode" )
        {
            AppLog( "ABargraph support : " + widget.GetId() + " was pressed " );
            ViewCode ( "Scripts/code_abargraph.as", widget.GetParent() );
        }
        if (widget.GetId() ==  "uibargraphlayout" )
        {
            AppLog( "ABargraph support : " + widget.GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_abargraph.ui.txt", widget.GetParent() );
        }
    }
}

