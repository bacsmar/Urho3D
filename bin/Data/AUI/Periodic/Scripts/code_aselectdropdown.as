// ASelectDropdown application source code
// when menu entry is selected, the ASelectDropdown value (and string) is updated, theoritically.

void setup_uiselectdropdown( AWidget @layout )
{
    Array<AWidget@> dest = layout.SearchAWidgetClass( "TBButton" ); 
    for (uint ii = 0; ii < dest.length; ii++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest[ii], "WidgetEvent", "HandleUiselectdropdownEvent" ); 
//        log.Info("HandleUiselectdropdownEvent on " + dest[ii].GetId() );
 
    //AWidget @demo = 
    //ASelectDropdown @demo = cast<AButton@>(layout.GetWidget("selectdropdowndemo"));
    //AButton @demo = cast<AButton@>(layout.GetWidget("selectdropdowndemo"));
    AWidget @demo = layout.GetWidget("selectdropdowndemo");
    if ( demo !is null ) // warning - this will route for all ASelectDropdown instances events into this event handler.
    {
 //       log.Info("HandleUiselectdropdownEvent on " + demo.GetId() );
        SubscribeToEvent(demo, "WidgetEvent", "HandleAllSelectdropdownEvent" );
  //      SubscribeToEvent(demo, "UIListViewSelectionChanged", "HandleAllSelectdropdownEvent" ); // try this! noo
  //      SubscribeToEvent(demo, "UIPopupMenuSelect", "HandleAllSelectdropdownEvent" ); // try this! noo
       // HELP this (below) doesnt work in Urho3D, it didnt work too well in Atomic
      // demo.SubscribeToEvent("WidgetEvent", "HandleAllSelectdropdownEvent" );
     }

}

void HandleAllSelectdropdownEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) 
        return;
    
  //  AWidget @demo = widget.FindWidget("selectdropdowndemo");  // find our specific widget
  //  if ( widget !is demo ) return; // if its not ours, bail

  //  if (eventData["Type"] == UI_EVENT_TYPE_CHANGED )
  //  {
     //   if (widget.GetId() ==  "selectdropdowndemo" )
    //    {
            AppLog( "ASelectDropdown event : " + widget.GetId() + " changed value to " + widget.GetText());
     //   }
   // }
}

void HandleUiselectdropdownEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() == "uiselectdropdowncode" )
        {
            AppLog( "ASelectDropdown support : " + widget.GetId() + " was pressed " + widget.GetText() );
            ViewCode ( "Scripts/code_aselectdropdown.as", widget.GetParent() );
       }
        if (widget.GetId() ==  "uiselectdropdownlayout" )
        {
            AppLog( "ASelectDropdown support : " + widget.GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_aselectdropdown.ui.txt", widget.GetParent() );
        }

    }
}

