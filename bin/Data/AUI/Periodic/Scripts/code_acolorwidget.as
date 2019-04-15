// AColorWidget application source code

void setup_uicolorwidget( AWidget @layout )
{
    Array<AWidget@> dest = layout.SearchAWidgetClass( "TBButton" ); 
    for (uint ii = 0; ii < dest.length; ii++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest[ii], "WidgetEvent", "HandleUicolorwidgetEvent" );
}

void HandleUicolorwidgetEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() == "uicolorwidgetcode" )
        {
            AppLog( "AColorWidget support : " + widget.GetId() + " was pressed " );
            ViewCode ( "Scripts/code_acolorwidget.as", widget.GetParent() );
        }
        if (widget.GetId() == "uicolorwidgetlayout" )
        {
            AppLog( "AColorWidget support : " + widget.GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_acolorwidget.ui.txt", widget.GetParent() );
        }

        if (widget.GetId() == "uicolorwidgetred" )
        {
            AppLog( "AColorWidget action : " + widget.GetId() + " was pressed ");
            AColorWidget @clw = cast<AColorWidget@>(widget.FindWidget("colorwidgetdemo"));
            if (clw !is null)
                clw.SetColorString("#FF1111");
        }
        if (widget.GetId() == "uicolorwidgetgreen" )
        {
            AppLog( "AColorWidget action : " + widget.GetId() + " was pressed ");
            AColorWidget @clw = cast<AColorWidget@>(widget.FindWidget("colorwidgetdemo"));
            if (clw !is null)
                clw.SetColorString("#11FF11");
        }
        if (widget.GetId() == "uicolorwidgetblue" )
        {
            AppLog( "AColorWidget action : " + widget.GetId() + " was pressed ");
            AColorWidget @clw = cast<AColorWidget@>(widget.FindWidget("colorwidgetdemo"));
            if (clw !is null)
                clw.SetColorString("#1111FF");
        }
    }
}

