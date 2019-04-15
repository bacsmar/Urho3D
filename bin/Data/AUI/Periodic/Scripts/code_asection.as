// ASection application source code

void setup_uisection( AWidget @layout )
{
    Array<AWidget@> dest = layout.SearchAWidgetClass( "TBButton" ); 
    for (uint ii = 0; ii < dest.length; ii++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest[ii], "WidgetEvent", "HandleUisectionEvent" );

    AWidget @sec1 = layout.GetWidget("ASectionDemo");
    if (sec1 !is null)
       SubscribeToEvent(sec1, "WidgetEvent", "HandleUisectionEvent" );
    AWidget @sec2 = layout.GetWidget("ASection2Demo");
    if (sec2 !is null)
        SubscribeToEvent(sec2, "WidgetEvent", "HandleUisectionEvent" );
}

void HandleUisectionEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() == "uisectioncode" )
        {
            AppLog( "ASection support : " + widget.GetId() + " was pressed " );
            ViewCode ( "Scripts/code_asection.as", widget.GetParent() );
        }
        if (widget.GetId() ==  "uisectionlayout" )
        {
            AppLog( "ASection support : " + widget.GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_asection.ui.txt", widget.GetParent() );
        }
    }
    if (eventData["Type"] == UI_EVENT_TYPE_CHANGED )
    {
        AWidget @demo1 = widget.FindWidget("ASectionDemo"); // event comes in on child widget!
        if ( demo1.IsAncestorOf(widget) )
            AppLog( "ASection event : " +  demo1.GetId() + " changed to value = " + String(demo1.GetValue()));

        AWidget @demo2 = widget.FindWidget("ASection2Demo");
        if ( demo2.IsAncestorOf(widget)  )
            AppLog( "ASection event : " +  demo2.GetId() + " changed to value = " + String(demo2.GetValue()));
    }
}

