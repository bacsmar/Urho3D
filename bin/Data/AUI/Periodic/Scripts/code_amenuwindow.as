// AMenuWindow application source code


void setup_uimenuwindow( AWidget @layout )
{
    Array<AWidget@> dest = layout.SearchAWidgetClass( "TBButton" ); 
    for (uint ii = 0; ii < dest.length; ii++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest[ii], "WidgetEvent", "HandleUimenuwindowEvent" );
}

void HandleUimenuwindowEvent(StringHash eventType, VariantMap& eventData)
{
    String refid = eventData["RefID"].GetString();
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() == "uimenuwindowcode" )
        {
            AppLog( "AMenuWindow support : " + widget.GetId() + " was pressed " );
            ViewCode ( "Scripts/code_amenuwindow.as", widget.GetParent() );
        }
        if (widget.GetId() ==  "uimenuwindowlayout" )
        {
            AppLog( "AMenuWindow support : " + widget.GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_amenuwindow.ui.txt", widget.GetParent() );
        }

        if (widget.GetId() ==  "uimenuwindowpush" )
        {
            AppLog( "AMenuWindow action : " + widget.GetId() + " was pressed " );
            AMenuWindow@ mymenuwindow =  AMenuWindow(  widget, "MenuWindowDemo");
            AMenuItemSource @mis =  AMenuItemSource();
            mis.AddItem(  AMenuItem( "ASelectItem1", "item1", "", "" ) );
            mis.AddItem(  AMenuItem( "ASelectItem2", "item2", "Ctrl+C", "" ) );
            mis.AddItem(  AMenuItem( "ASelectItem3", "item3", "Ctrl+A", "DuckButton" ) );
            mis.AddItem(  AMenuItem( "ASelectItem4", "item4", "Ctrl+O", "LogoAtomic" ) );
            int xx = widget.GetX() + (widget.GetWidth()/2);
            int yy = widget.GetY() + (widget.GetHeight()/2);
            SubscribeToEvent(mymenuwindow, "WidgetEvent", "HandleUimenuwindowEvent" );
            mymenuwindow.ShowMenu(mis, xx, yy);
        }

        if (widget.GetId() ==  "MenuWindowDemo" )
        {
            AppLog( "AMenuWindow event : " + widget.GetId() + " and " + refid + " was selected ");
        }
    }
    else
    {
        if (widget.GetId() ==  "MenuWindowDemo" )
        {
            AppLog( "AMenuWindow event : " + widget.GetId() +  " refid=" + refid );
        }
    }
}

