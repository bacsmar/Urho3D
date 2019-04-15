// AWidget application source code


void setup_uiwidget( AWidget @layout )
{
    Array<AWidget@> dest = layout.SearchAWidgetClass( "TBButton" ); 
    for (uint ii = 0; ii < dest.length; ii++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest[ii], "WidgetEvent", "HandleUiwidgetEvent" );
}

void HandleUiwidgetEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() == "uiwidgetcode" )
        {
            AppLog( "AWidget support : " + widget.GetId() + " was pressed " );
            ViewCode ( "Scripts/code_awidget.as", widget.GetParent() );
        }
        if (widget.GetId() ==  "uiwidgetlayout" )
        {
            AppLog( "AWidget support : " + widget.GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_awidget.ui.txt", widget.GetParent() );
        }
    }
}

