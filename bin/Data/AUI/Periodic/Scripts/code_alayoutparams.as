// ALayoutParams application source code

void setup_uilayoutparams( AWidget @layout )
{
    Array<AWidget@> dest = layout.SearchAWidgetClass( "TBButton" ); 
    for (uint ii = 0; ii < dest.length; ii++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest[ii], "WidgetEvent", "HandleUilayoutparamsEvent" );
}

void HandleUilayoutparamsEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() == "uilayoutparamscode" )
        {
            AppLog( "ALayoutParams support : " + widget.GetId() + " was pressed " );
            ViewCode ( "Scripts/code_alayoutparams.as", widget.GetParent() );
        }
        if (widget.GetId() ==  "uilayoutparamslayout" )
        {
            AppLog( "ALayoutParams support : " + widget.GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_alayoutparams.ui.txt", widget.GetParent() );
        }
    }
}

