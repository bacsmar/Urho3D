// AMenuItem and AMenuItemSource application source code

void setup_uimenuitem( AWidget @layout )
{
    Array<AWidget@> dest = layout.SearchAWidgetClass( "TBButton" ); 
    for (uint ii = 0; ii < dest.length; ii++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest[ii], "WidgetEvent", "HandleUimenuitemEvent" );

    AMenuItemSource @mis = AMenuItemSource();
    mis.AddItem( AMenuItem( "ASelectItem1", "item1", "", "" ) );
    mis.AddItem( AMenuItem( "ASelectItem2", "item2", "Ctrl+.", "" ) );
    mis.AddItem( AMenuItem( "ASelectItem3", "item3", "Ctrl+A", "DuckButton" ) );
    mis.AddItem( AMenuItem( "ASelectItem4", "item4", "Ctrl+O", "LogoAtomic" ) );
    Variant misx ( mis );
    SetGlobalVar( "menuitemptr", misx );
}

void HandleUimenuitemEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    String refid = eventData["RefID"].GetString();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() == "uimenuitemcode" )
        {
            AppLog( "AMenuItem support : " + widget.GetId() + " was pressed " );
            ViewCode ( "Scripts/code_amenuitem.as", widget.GetParent() );
        }
        if (widget.GetId() ==  "uimenuitemlayout" )
        {
            AppLog( "AMenuItem support : " + widget.GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_amenuitem.ui.txt", widget.GetParent() );
        }

        if (widget.GetId() ==  "uimenuitempush" )
        {
            AMenuItemSource @gmis = cast<AMenuItemSource@>(GetGlobalVar("menuitemptr").GetPtr());
            AMenuWindow@ mymenuwindow = AMenuWindow( widget, "MenuItemDemo");
            int xx = widget.GetX() + (widget.GetWidth()/2);
            int yy = widget.GetY() + (widget.GetHeight()/2);
            SubscribeToEvent(mymenuwindow, "WidgetEvent", "HandleUimenuitemEvent" );
            mymenuwindow.ShowMenu(gmis, xx, yy);
        }

        if (widget.GetId() ==  "MenuItemDemo" )
        {
            AppLog( "AMenuItem event : " + widget.GetId() + " and " + refid + " was selected ");
        }

        if (widget.GetId() ==  "uimi1" )
        {
            AppLog( "AMenuItem action : " + widget.GetId() + " was pressed ");
            AMenuItemSource @gmis = cast<AMenuItemSource@>(GetGlobalVar("menuitemptr").GetPtr());
            gmis.AddItem( AMenuItem( "New AMenuItem", "", "", "") );
        }
        if (widget.GetId() ==  "uimi2" )
        {
            AppLog( "AMenuItem action : " + widget.GetId() + " was pressed ");
            AMenuItemSource @gmis = cast<AMenuItemSource@>(GetGlobalVar("menuitemptr").GetPtr());
            gmis.AddItem( AMenuItem( "Newer AMenuItem", "neweritem", "", "" ) );
        }
        if (widget.GetId() ==  "uimi3" )
        {
            AppLog( "AMenuItem action : " + widget.GetId() + " was pressed ");
            AMenuItemSource @gmis = cast<AMenuItemSource@>(GetGlobalVar("menuitemptr").GetPtr());
            gmis.AddItem( AMenuItem( "A Duck", "aduck", "", "DuckButton" ) );
        }
        if (widget.GetId() ==  "uimi4" )
        {
            AppLog( "AMenuItem action : " + widget.GetId() + " was pressed ");
            AMenuItemSource @gmis = cast<AMenuItemSource@>(GetGlobalVar("menuitemptr").GetPtr());
            gmis.AddItem( AMenuItem( "Atomic!", "atomic", "", "LogoAtomic") );
        }
        if (widget.GetId() ==  "uimi5" )
        {
            AppLog( "AMenuItem action : " + widget.GetId() + " was pressed ");
            AMenuItemSource @gmis = cast<AMenuItemSource@>(GetGlobalVar("menuitemptr").GetPtr());
            gmis.Clear();
        }
    }
}

