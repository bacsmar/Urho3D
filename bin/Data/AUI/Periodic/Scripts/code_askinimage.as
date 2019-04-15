// ASkinImage application source code

void setup_uiskinimage( AWidget @layout )
{
    Array<AWidget@> dest = layout.SearchAWidgetClass( "TBButton" ); 
    for (uint ii = 0; ii < dest.length; ii++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest[ii], "WidgetEvent", "HandleUiskinimageEvent" );
}

void HandleUiskinimageEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() == "uiskinimagecode" )
        {
            AppLog( "ASkinImage support : " + widget.GetId() + " was pressed " );
            ViewCode ( "Scripts/code_askinimage.as", widget.GetParent() );
        }
        if (widget.GetId() ==  "uiskinimagelayout" )
        {
            AppLog( "ASkinImage support : " + widget.GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_askinimage.ui.txt", widget.GetParent() );
        }
    }
}

