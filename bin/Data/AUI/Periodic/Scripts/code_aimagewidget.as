// AImageWidget application source code


void setup_uiimagewidget( AWidget @layout )
{
    Array<AWidget@> dest = layout.SearchAWidgetClass( "TBButton" ); 
    for (uint ii = 0; ii < dest.length; ii++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest[ii], "WidgetEvent", "HandleUiimagewidgetEvent" );
}

void HandleUiimagewidgetEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() == "uiimagewidgetcode" )
        {
            AppLog( "AImageWidget support : " + widget.GetId() + " was pressed " );
            ViewCode ( "Scripts/code_aimagewidget.as", widget.GetParent() );
        }
        if (widget.GetId() ==  "uiimagewidgetlayout" )
        {
            AppLog( "AImageWidget support : " + widget.GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_aimagewidget.ui.txt", widget.GetParent() );
        }

        if (widget.GetId() ==  "imagecolor" )
        {
            AppLog( "AImageWidget action : " + widget.GetId() + " was pressed ");
            AImageWidget @img1 = cast<AImageWidget@>( widget.FindWidget("imagewidgetdemo") );
            img1.SetImage("Textures/HSV21.png");
        }
        if (widget.GetId() ==  "imagenewbuild" )
        {
            AppLog( "AImageWidget action : " + widget.GetId() + " was pressed ");
            AImageWidget @img2 = cast<AImageWidget@>( widget.FindWidget("imagewidgetdemo") );
            img2.SetImage("Textures/newbuilddetected_header.jpg");
        }
    }
}

