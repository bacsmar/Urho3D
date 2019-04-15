// AClickLabel application source code


void setup_uiclicklabel( AWidget @layout )
{
    Array<AWidget@> dest = layout.SearchAWidgetClass( "TBButton" ); 
    for (uint ii = 0; ii < dest.length; ii++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest[ii], "WidgetEvent", "HandleUiclicklabelEvent");

    AWidget @chk1 = layout.GetWidget ("somecheck");
    if (chk1 !is null)
        SubscribeToEvent(chk1, "WidgetEvent", "HandleUiclicklabelEvent");

    AWidget @chk2 = layout.GetWidget ("someradio");
    if (chk2 !is null)
        SubscribeToEvent(chk2, "WidgetEvent", "HandleUiclicklabelEvent");
}

void HandleUiclicklabelEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() == "uiclicklabelcode" )
        {
            AppLog( "AClickLabel support : " + widget.GetId() + " was pressed " );
            ViewCode ( "Scripts/code_aclicklabel.as", widget.GetParent() );
        }
        if (widget.GetId() ==  "uiclicklabellayout" )
        {
            AppLog( "AClickLabel support : " + widget.GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_aclicklabel.ui.txt", widget.GetParent() );
        }
        if (widget.GetId() == "somecheck" )
        {
            AppLog( "AClickLabel event : " + widget.GetId() + " was pressed, state = " + String ( widget.GetValue() ) );
        }
        if (widget.GetId() == "someradio" )
        {
            AppLog( "AClickLabel event : " + widget.GetId() + " was pressed, state = " + String ( widget.GetValue() ) );
        }
    }
}

