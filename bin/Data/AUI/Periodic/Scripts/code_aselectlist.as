// ASelectList application source code

void setup_uiselectlist( AWidget @layout )
{
     Array<AWidget@> dest = layout.SearchAWidgetClass( "TBButton" ); 
    for (uint ii = 0; ii < dest.length; ii++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest[ii], "WidgetEvent", "HandleUiselectlistEvent" );

    AWidget @slist = layout.GetWidget ("ASelectListDemo");
    if ( slist !is null)
        SubscribeToEvent(slist, "WidgetEvent", "HandleUiselectlistEvent" );
}

void HandleUiselectlistEvent(StringHash eventType, VariantMap& eventData)
{
    String refid = eventData["RefID"].GetString();
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() == "uiselectlistcode" )
        {
            AppLog( "ASelectList support : " + widget.GetId() + " was pressed " );
            ViewCode ( "Scripts/code_aselectlist.as", widget.GetParent() );
        }
        if (widget.GetId() ==  "uiselectlistlayout" )
        {
            AppLog( "ASelectList support : " + widget.GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_aselectlist.ui.txt", widget.GetParent() );
        }

        if (widget.GetId() ==  "ASelectListDemo" )
        {
            AppLog( "ASelectList event : " + widget.GetId() + " and " + refid + " was selected ");
        }

        if (widget.GetId() ==  "selectlistadd" )
        {
            AppLog( "ASelectList action : " + widget.GetId() + " was pressed ");
            ASelectList@ slist = cast<ASelectList@>(widget.FindWidget("ASelectListDemo"));
            slist.AddItem(slist.GetNumItems(), "New Entry", "");
        }
        if (widget.GetId() ==  "selectlistdel" )
        {
            AppLog( "ASelectList action : " + widget.GetId() + " was pressed ");
            ASelectList@ slist = cast<ASelectList@>(widget.FindWidget("ASelectListDemo"));
            // Float value truncated in implicit conversion to integer
            int si = int(slist.GetValue()); // this is the selected index
            slist.DeleteItem(si);
        }
        if (widget.GetId() ==  "selectlistdelall" )
        {
            AppLog( "ASelectList action : " + widget.GetId() + " was pressed ");
            ASelectList@ slist = cast<ASelectList@>(widget.FindWidget("ASelectListDemo"));
            slist.DeleteAllItems();
        }
        if (widget.GetId() ==  "selectlist" )
        {
            AppLog( "ASelectList action : " + widget.GetId() + " was pressed ");
            ASelectList@ slist = cast<ASelectList@>(widget.FindWidget("ASelectListDemo"));
            ASelectItemSource @sis = ASelectItemSource();
            sis.AddItem(  ASelectItem(  "list 1","list1", "LogoAtomic" ));
            sis.AddItem(  ASelectItem(  "list 2","list2", "" ));
            sis.AddItem(  ASelectItem(  "list 3","list3", "" ));
            sis.AddItem(  ASelectItem(  "list 4","list4", "" ));
            sis.AddItem(  ASelectItem(  "list 5","list5", "" ));
            sis.AddItem(  ASelectItem(  "list 6","list6", "" ));
            slist.SetSource(sis);
        }
    }
}

