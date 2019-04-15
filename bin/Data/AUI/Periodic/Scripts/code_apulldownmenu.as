// APulldownMenu application source code


void setup_uipulldownmenu( AWidget @layout )
{
    Array<AWidget@> dest = layout.SearchAWidgetClass( "TBButton" ); 
    for (uint ii = 0; ii < dest.length; ii++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest[ii], "WidgetEvent", "HandleUipulldownmenuEvent" );
    Array<AWidget@> dest1 = layout.SearchAWidgetClass( "TBPulldownMenu" ); 
    for (uint i1 = 0; i1 < dest1.length; i1++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest1[i1], "WidgetEvent", "HandleUipulldownmenuEvent" );
}

void HandleUipulldownmenuEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() == "uipulldownmenucode" )
        {
            AppLog( "APulldownMenu support : " + widget.GetId() + " was pressed " );
            ViewCode ( "Scripts/code_apulldownmenu.as", widget.GetParent() );
        }
        if (widget.GetId() ==  "uipulldownmenulayout" )
        {
            AppLog( "APulldownMenu support : " + widget.GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_apulldownmenu.ui.txt", widget.GetParent() );
        }
    }
    else if (eventData["Type"] == UI_EVENT_TYPE_CHANGED )
    {
        if (widget.GetId() ==  "FileMenu" )
        {
            APulldownMenu @pdm = cast<AButton@>(widget);  // HELP No conversion from 'AWidget@&' to 'APulldownMenu@' available.
            if ( pdm !is null)
                AppLog( "APulldownMenu event : " + widget.GetId() + " selected entry = " + String( pdm.GetSelectedId()) );
        }
        if (widget.GetId() ==  "EditMenu" )
        {
            APulldownMenu @pdm = cast<AButton@>(widget);
            if ( pdm !is null)
                AppLog( "APulldownMenu event : " + widget.GetId() + " selected entry = " + String( pdm.GetSelectedId()) );
        }
        if (widget.GetId() ==  "ViewMenu" )
        {
            APulldownMenu @pdm = cast<AButton@>(widget);
            if ( pdm !is null)
                AppLog( "APulldownMenu event : " + widget.GetId() + " selected entry = " + String( pdm.GetSelectedId()) );
        }
        if (widget.GetId() ==  "HelpMenu" )
        {
            APulldownMenu @pdm = cast<AButton@>(widget);
            if ( pdm !is null)
                AppLog( "APulldownMenu event : " + widget.GetId() + " selected entry = " + String( pdm.GetSelectedId()) );
        }
    }
}

