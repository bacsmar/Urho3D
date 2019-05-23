// AButtonGrid application source code


void setup_uibuttongrid( AWidget @layout)
{
    Array<AWidget@> dest = layout.SearchAWidgetClass( "TBButton" ); 
    for (uint ii = 0; ii < dest.length; ii++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest[ii], "WidgetEvent", "HandleUibuttongridEvent" );

    AButtonGrid @ mybuttongrid = AButtonGrid(6,4);  // make a list...view
    mybuttongrid.SetId( "AButtonGridDemo"); // tag it, in case we want to get it again later

    // fill the buttongrid, feel the joy
    for ( uint row = 0; row<mybuttongrid.GetNumRows(); row++)
        for ( uint col = 0; col<mybuttongrid.GetNumColumns(); col++)
        {
            mybuttongrid.SetGridText (row, col, mybuttongrid.GetGridId(row, col));
            AWidget@ bx = mybuttongrid.GetGridWidget( row, col );
            SubscribeToEvent(bx, "WidgetEvent", "HandleUibuttongridEvent" );
        }

    ALayoutParams @lpx = ALayoutParams();
    lpx.SetWidth (320);
    lpx.SetHeight(320);
    lpx.SetMinWidth(320);
    lpx.SetMinHeight(320);
    lpx.SetMaxWidth (320);
    lpx.SetMaxHeight(320);
    mybuttongrid.SetLayoutParams(lpx);

    AWidget@ lower = layout.GetWidget("uibuttongridlower");
    AWidget@ mysvc = layout.GetWidget("buttongridcontainer");
    mysvc.AddChildBefore(mybuttongrid, lower);
}

void HandleUibuttongridEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() == "uibuttongridcode" )
        {
            AppLog( "AButtonGrid support : " + widget.GetId() + " was pressed " );
            ViewCode ( "Scripts/code_abuttongrid.as", widget.GetParent() );
        }
        else if (widget.GetId() ==  "uibuttongridlayout" )
        {
            AppLog( "AButtonGrid support : " + widget.GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_abuttongrid.ui.txt", widget.GetParent() );
        }
        else
        {
             AppLog( "AButtonGrid support : " + widget.GetId() + " was pressed ");
        }
    }
    if ( widget.GetId() ==  "AButtonGridDemo" )
    {
       // AppLog( "AButtonGrid event : " + widget.GetId() + " got event= "+ EventReport(eventData[P_TYPE].GetInt()) );
        AppLog( "AButtonGrid event : " + widget.GetId() );
    }
}

