// AColorWheel application source code

void setup_uicolorwheel( AWidget @layout )
{
    Array<AWidget@> dest = layout.SearchAWidgetClass( "TBButton" ); 
    for (uint ii = 0; ii < dest.length; ii++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest[ii], "WidgetEvent", "HandleUicolorwheelEvent" );

    AWidget @cwx = layout.GetWidget("colorwheeldemo");
    if (cwx !is null)
        SubscribeToEvent(cwx, "WidgetEvent", "HandleUicolorwheelEvent" );
}

void HandleUicolorwheelEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() ==  "uicolorwheelcode" )
        {
            AppLog( "AColorWheel support : " + widget.GetId() + " was pressed " );
            ViewCode ( "Scripts/code_acolorwheel.as", widget.GetParent() );
        }
        if (widget.GetId() ==  "uicolorwheellayout" )
        {
            AppLog( "AColorWheel support : " + widget.GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_acolorwheel.ui.txt", widget.GetParent() );
        }
    }
    else if (eventData["Type"] == UI_EVENT_TYPE_CHANGED )
    {
        if (widget.GetId() ==  "colorwheeldemo" )
        {
            AColorWheel @cwx = cast<AColorWheel@>(widget); // collect click color info
            if (cwx !is null )
            {
                AppLog( "AColorWheel event : " + widget.GetId() + " hue = " + String(cwx.GetHue()) + " saturation = " + String(cwx.GetSaturation()) );
            }
        }
    }
}

