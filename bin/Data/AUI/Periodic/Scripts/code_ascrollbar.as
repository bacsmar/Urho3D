// AScrollBar application source code

void setup_uiscrollbar( AWidget @layout )
{
    Array<AWidget@> dest = layout.SearchAWidgetClass( "TBButton" ); 
    for (uint ii = 0; ii < dest.length; ii++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest[ii], "WidgetEvent", "HandleUiscrollbarEvent" );

    AWidget @sbx = layout.GetWidget("scrollbardemo");
    if (sbx !is null)  // warning - this will route for all scrollbar instances events into this event handler.
       SubscribeToEvent(sbx, "WidgetEvent", "HandleAllScrollcontainerEvent" );
       // HELP this (below) doesnt work in Urho3D, it didnt work too well in Atomic
       // sbx.SubscribeToEvent( "WidgetEvent", "HandleAllScrollcontainerEvent" );
}

void HandleAllScrollcontainerEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;

    AWidget @sbx = widget.FindWidget("scrollbardemo");  // find our scrollbar
    if ( widget !is sbx ) return; // if its not ours, bail

    if (eventData["Type"] == UI_EVENT_TYPE_CHANGED )
    {
        if (widget.GetId() ==  "scrollbardemo" )
        {
            AppLog( "AScrollBar action : " + widget.GetId() + " changed value to " + String (widget.GetValue()));
        }
    }
}

void HandleUiscrollbarEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() == "uiscrollbarcode" )
        {
            AppLog( "AScrollBar support : " + widget.GetId() + " was pressed " );
            ViewCode ( "Scripts/code_ascrollbar.as", widget.GetParent() );
        }
        if (widget.GetId() ==  "uiscrollbarlayout" )
        {
            AppLog( "AScrollBar support : " + widget.GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_ascrollbar.ui.txt", widget.GetParent() );
        }
    }
}

