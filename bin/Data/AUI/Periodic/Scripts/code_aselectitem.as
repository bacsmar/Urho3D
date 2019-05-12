// ASelectItem and ASelectItemSource application source code

// persistant copy of menu contents
ASelectItemSource @globalasis = null;

void setup_uiselectitem( AWidget @layout )
{
    Array<AWidget@> dest = layout.SearchAWidgetClass( "TBButton" ); 
    for (uint ii = 0; ii < dest.length; ii++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest[ii], "WidgetEvent", "HandleUiselectitemEvent" );

    ASelectList @mylist =  ASelectList();
    mylist.SetId( "ASelectItemList"); // tag it, in case we want to get it again later
    ALayoutParams @lpx =  ALayoutParams();
    lpx.SetWidth (200);
    lpx.SetHeight(256);
    lpx.SetMinWidth(200);
    lpx.SetMinHeight(256);
    lpx.SetMaxWidth (200);
    lpx.SetMaxHeight(256);
    mylist.SetLayoutParams(lpx);
    AWidget@ lower = layout.GetWidget("selectitemlower");
    AWidget@ mysvc = layout.GetWidget("selectitemlayout");
    mysvc.AddChildBefore(mylist, lower);
    SubscribeToEvent(mylist, "WidgetEvent", "HandleUiselectitemEvent" );

    globalasis = ASelectItemSource();
    globalasis.AddItem( ASelectItem(  "ASelectItem1", "sitem1", "" ) );
    globalasis.AddItem( ASelectItem(  "ASelectItem2", "sitem2", "" ) );
    globalasis.AddItem( ASelectItem(  "ASelectItem3", "sitem3", "DuckButton" ) );
    globalasis.AddItem( ASelectItem(  "ASelectItem4", "sitem4", "LogoAtomic" ) );

    mylist.SetSource(globalasis); // assign this into the list
}

void HandleUiselectitemEvent(StringHash eventType, VariantMap& eventData)
{
    String refid = eventData["RefID"].GetString();
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() == "uiselectitemcode" )
        {
            AppLog( "ASelectItem support : " + widget.GetId() + " was pressed " );
            ViewCode ( "Scripts/code_aselectitem.as", widget.GetParent() );
        }
        if (widget.GetId() ==  "uiselectitemlayout" )
        {
            AppLog( "ASelectItem support : " + widget.GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_aselectitem.ui.txt", widget.GetParent() );
        }

        if (widget.GetId() ==  "ASelectItemList" )
        {
            AppLog( "ASelectItem event : " + widget.GetId() + " and " + refid + " was selected ");
        }

        if (widget.GetId() ==  "uisi1" )
        {
            AppLog( "ASelectItem action : " + widget.GetId() + " was pressed ");
            ASelectList@ slist = cast<ASelectList@>(widget.FindWidget("ASelectItemList"));
            globalasis.AddItem( ASelectItem( "New ASelectItem", "newitem", "") );
            slist.SetSource(globalasis);
        }
        if (widget.GetId() ==  "uisi2" )
        {
            AppLog( "ASelectItem action : " + widget.GetId() + " was pressed ");
            ASelectList@ slist = cast<ASelectList@>(widget.FindWidget("ASelectItemList"));
            globalasis.AddItem(  ASelectItem( "Newer ASelectItem", "neweritem", "" ) );
            slist.SetSource(globalasis);
        }
        if (widget.GetId() ==  "uisi3" )
        {
            AppLog( "ASelectItem action : " + widget.GetId() + " was pressed ");
            ASelectList@ slist = cast<ASelectList@>(widget.FindWidget("ASelectItemList"));
            globalasis.AddItem( ASelectItem(  "A Duck", "aduck", "DuckButton" ) );
            slist.SetSource(globalasis);
        }
        if (widget.GetId() ==  "uisi4" )
        {
            AppLog( "ASelectItem action : " + widget.GetId() + " was pressed ");
            ASelectList@ slist = cast<ASelectList@>(widget.FindWidget("ASelectItemList"));
            globalasis.AddItem( ASelectItem( "Atomic!", "atomic", "LogoAtomic" ) );
            slist.SetSource(globalasis);
        }
        if (widget.GetId() ==  "uisi5" )
        {
            AppLog( "ASelectItem action : " + widget.GetId() + " was pressed ");
            ASelectList@ slist = cast<ASelectList@>(widget.FindWidget("ASelectItemList"));
            globalasis.Clear();
            slist.SetSource(globalasis);
        }
    }
}

