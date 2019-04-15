// AButton application source code

void setup_uibutton( AWidget @layout)
{
    Array<AWidget@> dest = layout.SearchAWidgetClass( "TBButton" ); 
    for (uint ii = 0; ii < dest.length; ii++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest[ii], "WidgetEvent", "HandleUibuttonEvent" );
}

void HandleUibuttonEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() == "uibuttoncode" )
        {
            AppLog( "AButton support : " + widget.GetId() + " was pressed " );
            ViewCode ( "Scripts/code_abutton.as", widget.GetParent() );
        }
        if (widget.GetId() == "uibuttonlayout" )
        {
            AppLog( "AButton support : " + widget.GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_abutton.ui.txt", widget.GetParent() );
        }
        if (widget.GetId() == "demobutton" )
        {
            AppLog( "AButton action : " + widget.GetId() + " was pressed ");
        }
        if (widget.GetId() == "buttonducky" )
        {
            AppLog( "AButton action : " + widget.GetId() + " was pressed ");
        }
        if (widget.GetId() == "buttonready" )
        {
            AppLog( "AButton action : " + widget.GetId() + " was pressed ");
        }
        if (widget.GetId() == "buttonatomic" )
        {
            AppLog( "AButton action : " + widget.GetId() + " was pressed ");
        }
        if (widget.GetId() == "buttongreen" )
        {
            AppLog( "AButton action : " + widget.GetId() + " was pressed ");
        }
    }
}

