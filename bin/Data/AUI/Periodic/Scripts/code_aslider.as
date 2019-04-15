// ASlider application source code

void setup_uislider( AWidget @layout )
{
    Array<AWidget@> dest = layout.SearchAWidgetClass( "TBButton" ); 
    for (uint ii = 0; ii < dest.length; ii++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest[ii], "WidgetEvent", "HandleUisliderEvent" );

    ASlider @slider = cast<ASlider@>(layout.GetWidget("sliderdemo"));
    if (slider !is null) // warning - this will route for all ASlider instances events into this event handler.
        SubscribeToEvent(slider, "WidgetEvent", "HandleAllSliderEvent" );
       // HELP this (below) doesnt work in Urho3D, it didnt work too well in Atomic
      //  slider.SubscribeToEvent( "WidgetEvent", "HandleAllSliderEvent" );
}

void HandleAllSliderEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;

    AWidget @demo = widget.FindWidget("sliderdemo");  // find our specific widget
    if ( widget !is demo ) return; // if its not ours, bail

    if (eventData["Type"] == UI_EVENT_TYPE_CHANGED )
    {
        if (widget.GetId() ==  "sliderdemo" )
        {
            AppLog( "ASlider event : " + widget.GetId() + " changed value to " + String (widget.GetValue()));
        }
    }
}

void HandleUisliderEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() == "uislidercode" )
        {
            AppLog( "ASlider support : " + widget.GetId() + " was pressed " );
            ViewCode ( "Scripts/code_aslider.as", widget.GetParent() );
        }
        if (widget.GetId() ==  "uisliderlayout" )
        {
            AppLog( "ASlider support : " + widget.GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_aslider.ui.txt", widget.GetParent() );
        }
    }
}

