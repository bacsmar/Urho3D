// AListView application source code
// some code from UISceneview2D sample program

int wcount = 0;

void PrintPretty( AListView @alv, AWidget @me, uint recenthandle )
{
    wcount++;

    String wname = "Widget[" + String(wcount) + "]" + String(me.GetClassName()) + " " + me.GetText();
    String iconx = ""; // make it look prettier
    if ( me.GetClassName() == "TBButton" ) iconx = "ButtonIcon";
    if ( me.GetClassName() == "TBLayout" ) iconx = "LayoutIcon";
    if ( me.GetClassName() == "TBTextField" ) iconx = "TextFieldIcon";

    uint nxt = alv.AddChildItem(recenthandle, wname, iconx, "widget"+me.GetId());

    uint num = me.numChildren();
    for (uint ii = 0; ii < num; ii++)
    {
        AWidget @child = me.GetChildFromIndex(ii);
        PrintPretty( alv, child, nxt );
    }
}


void setup_uilistview( AWidget @layout)
{
    Array<AWidget@> dest = layout.SearchAWidgetClass( "TBButton" ); 
    for (uint ii = 0; ii < dest.length; ii++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest[ii], "WidgetEvent", "HandleUilistviewEvent" );

    AListView @ mylistview = AListView();  // make a list...view
    mylistview.SetId( "AListViewDemo"); // tag it, in case we want to get it again later
    SubscribeToEvent(mylistview, "WidgetEvent", "HandleUilistviewEvent" );

    // fill the listview, feel the joy
    uint roothandle = mylistview.AddRootItem("Widgets", "LogoAtomic", "root_");
    PrintPretty( mylistview, uiview, roothandle ); 

    ALayoutParams @lpx = ALayoutParams();
    lpx.SetWidth (600);
    lpx.SetHeight(320);
    lpx.SetMinWidth(600);
    lpx.SetMinHeight(320);
    lpx.SetMaxWidth (600);
    lpx.SetMaxHeight(320);
    mylistview.SetLayoutParams(lpx);

    AWidget@ lower = layout.GetWidget("uilistviewlower");
    AWidget@ mysvc = layout.GetWidget("listviewcontainer");
    mysvc.AddChildBefore(mylistview, lower);

}

void HandleUilistviewEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() == "uilistviewcode" )
        {
            AppLog( "AListView support : " + widget.GetId() + " was pressed " );
            ViewCode ( "Scripts/code_alistview.as", widget.GetParent() );
        }
        if (widget.GetId() ==  "uilistviewlayout" )
        {
            AppLog( "AListView support : " + widget.GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_alistview.ui.txt", widget.GetParent() );
        }
    }
    if ( widget.GetId() ==  "AListViewDemo" )
    {
       // AppLog( "AListView event : " + widget.GetId() + " got event= "+ EventReport(eventData[P_TYPE].GetInt()) );
        AppLog( "AListView event : " + widget.GetId() );
    }
}

