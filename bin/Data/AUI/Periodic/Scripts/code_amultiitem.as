// ASelectItem and ASelectItemSource application source code

// persistant copy of menu contents
AMultiItemSource @gmsis = null;

void setup_uimultiitem( AWidget @layout )
{
    Array<AWidget@> dest = layout.SearchAWidgetClass( "TBButton" ); 
    for (uint ii = 0; ii < dest.length; ii++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest[ii], "WidgetEvent", "HandleUimultiitemEvent" );

    ASelectList @mylist = ASelectList();
    mylist.SetId( "AMultiItemList"); // tag it, in case we want to get it again later
    ALayoutParams @lpx =  ALayoutParams();
    lpx.SetWidth (200);
    lpx.SetHeight(256);
    lpx.SetMinWidth(200);
    lpx.SetMinHeight(256);
    lpx.SetMaxWidth (200);
    lpx.SetMaxHeight(256);
    mylist.SetLayoutParams(lpx);
    mylist.SetLayoutParams(lpx);
    AWidget@ lower = layout.GetWidget("multiitemlower");
    AWidget@ mysvc = layout.GetWidget("multiitemlayout");
    mysvc.AddChildBefore(mylist, lower);
    SubscribeToEvent(mylist, "WidgetEvent", "HandleUimultiitemEvent" );

    gmsis = AMultiItemSource();
    AMultiItem @mi1 =  AMultiItem(  "sitem1", "TEXT", "AMultiItem1", 88,0 );
    mi1.AddColumn ( "TEXT", "Col2", 44 );
    mi1.AddColumn ( "TEXT", "Col3", 44 );
    gmsis.AddItem(mi1);
    AMultiItem @mi2 =  AMultiItem(  "sitem2", "TEXT", "AMultiItem2",  88,0  );
    mi2.AddColumn ( "TEXT", "Col4", 44 );
    mi2.AddColumn ( "TEXT", "Col5", 44 );
    gmsis.AddItem(mi2);
    AMultiItem @mi3 =  AMultiItem(  "sitem3", "TEXT", "AMultiItem3",  88,0 );
    mi3.AddColumn ( "TEXT", "Col6", 44 );
    mi3.AddColumn ( "TEXT", "Col7", 44 );
    gmsis.AddItem(mi3);
    AMultiItem @mi4 =  AMultiItem(  "sitem4", "TEXT", "AMultiItem4",  88,0 );
    mi4.AddColumn ( "TEXT", "Col8", 44 );
    mi4.AddColumn ( "TEXT", "PASS", 44 );
    gmsis.AddItem(mi4);
    mylist.SetSource(gmsis); // assign this into the list
      
}

void HandleUimultiitemEvent(StringHash eventType, VariantMap& eventData)
{
    String refid = eventData["RefID"].GetString();
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() == "uimultiitemcode" )
        {
            AppLog( "AMultiItem support : " + widget.GetId() + " was pressed " );
            ViewCode ( "Scripts/code_amultiitem.as", widget.GetParent() );
        }
        if (widget.GetId() ==  "uimultiitemlayout" )
        {
            AppLog( "ASelectItem support : " + widget.GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_amultiitem.ui.txt", widget.GetParent() );
        }

        if (widget.GetId() ==  "AMultiItemList" )
        {
            AppLog( "AMultiItemList event : " + widget.GetId() + " and " + refid + " was selected ");
        }

        if (widget.GetId() ==  "uimi1" )
        {
            AppLog( "AMultiItem1 action : " + widget.GetId() + " was pressed ");
            ASelectList@ slist = cast<ASelectList@>(widget.FindWidget("AMultiItemList"));
            if ( slist !is null )
            {
                AppLog( "AMultiItem2 action : " + widget.GetId() + " was pressed ");
                if ( gmsis !is null )
                {
                    AppLog( "AMultiItem3 action : " + widget.GetId() + " was pressed ");
                    AMultiItem @mi1 = AMultiItem( "sitem1", "TEXT", " MultiItem", 88, 0 );
                    mi1.AddColumn ( "TEXT", "Col2", 44 );
                    mi1.AddColumn ( "TEXT", "Col3", 44 );
                    gmsis.AddItem(mi1);
                    slist.SetSource(gmsis);
                }
            }
        }
        if (widget.GetId() ==  "uimi2" )
        {
            AppLog( "AMultiItem action : " + widget.GetId() + " was pressed");
            ASelectList@ slist = cast<ASelectList@>(widget.FindWidget("AMultiItemList"));
            AMultiItem @mi2 =  AMultiItem( "sitem2", "TEXT", "Another Item",  88, 0 );
            mi2.AddColumn ( "COLOR", "#3333FF", 44 );
            mi2.AddColumn ( "TEXT", "Col5", 44 );
            gmsis.AddItem(mi2);
            slist.SetSource(gmsis);
        }
        if (widget.GetId() ==  "uimi3" )
        {
            AppLog( "AMultiItem action : " + widget.GetId() + " was pressed ");
            ASelectList@ slist = cast<ASelectList@>(widget.FindWidget("AMultiItemList"));
            AMultiItem @mi3 =  AMultiItem(  "Duck", "ICON", "DuckButton", 88, 0 );
            mi3.AddColumn ( "TEXT", "Col6", 44 );
            mi3.AddColumn ( "TEXT", "Col7", 44 );
            gmsis.AddItem(mi3);
            slist.SetSource(gmsis);
        }
        if (widget.GetId() ==  "uimi4" )
        {
            AppLog( "AMultiItem action : " + widget.GetId() + " was pressed ");
            ASelectList@ slist = cast<ASelectList@>(widget.FindWidget("AMultiItemList"));
            AMultiItem @mi4 =  AMultiItem(  "Atomic", "ICON", "LogoAtomic", 88,0 );
            mi4.AddColumn ( "TEXT", "Col8", 44 );
            mi4.AddColumn ( "TEXT", "Col9", 44 );
            gmsis.AddItem(mi4);
            slist.SetSource(gmsis);
        }
        if (widget.GetId() ==  "uimi5" )
        {
            AppLog( "AMultiItem action : " + widget.GetId() + " was pressed ");
            ASelectList@ slist = cast<ASelectList@>(widget.FindWidget("AMultiItemList"));
            gmsis.Clear();
            slist.SetSource(gmsis);
        }
    }
}

