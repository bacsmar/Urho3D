// AFinderWindow application source code

void setup_uifinderwindow( AWidget @layout, AView @uiview )
{
    Array<AWidget@> dest = layout.SearchAWidgetClass( "TBButton" ); 
    for (uint ii = 0; ii < dest.length; ii++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest[ii], "WidgetEvent", "HandleUifinderwindowEvent" );
}

void HandleFinderCompleteEvent(StringHash eventType, VariantMap& eventData)
{
    AppLog( "AFinderWindow event : the window " + eventData["Title"].GetString()
            + " file was " + eventData["Selected"].GetString()
            + ", the button pressed was " + eventData["Reason"].GetString());
}

void HandleUifinderwindowEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() == "uifinderwindowcode" )
        {
            AppLog( "AFinderWindow support : " + widget.GetId() + " was pressed " );
            ViewCode ( "Scripts/code_afinderwindow.as", widget.GetParent() );
        }
        if (widget.GetId() ==  "uifinderwindowlayout" )
        {
            AppLog( "AFinderWindow support : " + widget.GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_afinderwindow.ui.txt", widget.GetParent() );
        }

        if (widget.GetId() == "filefinder" )
        {
            AppLog( "AFinderWindow action : " + widget.GetId() + " was pressed ");
            AFinderWindow @winf = AFinderWindow(uiview, widget.GetId());
            SubscribeToEvent(winf, "AFinderComplete", "HandleFinderCompleteEvent" );
            winf.FindFile("Find a File", "", 0, 0, 0);
        }
        if (widget.GetId() ==  "folderfinder" )
        {
            AppLog( "AFinderWindow action : " + widget.GetId() + " was pressed ");
            AFinderWindow @windowd = AFinderWindow(uiview, widget.GetId() );
            SubscribeToEvent(windowd, "AFinderComplete", "HandleFinderCompleteEvent" );
            windowd.FindPath("Find a Folder", "", 0, 0, 0);
        }
    }
}

