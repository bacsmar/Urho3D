// ATextureWidget application source code


void setup_uitexturewidget( AWidget @layout )
{
    Array<AWidget@> dest = layout.SearchAWidgetClass( "TBButton" ); 
    for (uint ii = 0; ii < dest.length; ii++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest[ii], "WidgetEvent", "HandleUitexturewidgetEvent" );

    ATextureWidget@ mytexturewidget = ATextureWidget();
    mytexturewidget.SetId( "ATextureWidgetDemo");
    if ( mytexturewidget !is null )
    {
        Texture2D@ mytex = Texture2D();
        if ( mytex !is null)
        {
            mytex = cache.GetResource("Texture2D", "Textures/planet.jpg");
            mytexturewidget.SetTexture(mytex);
        }
    }
    SubscribeToEvent(mytexturewidget, "WidgetEvent", "HandleUitexturewidgetEvent" );
    ALayoutParams @lpx = ALayoutParams();
    lpx.SetWidth (256);
    lpx.SetHeight(256);
    lpx.SetMinWidth(256);
    lpx.SetMinHeight(256);
    lpx.SetMaxWidth (256);
    lpx.SetMaxHeight(256);
    mytexturewidget.SetLayoutParams(lpx);
    AWidget@ lower = layout.GetWidget("uitexturewidgetlower");
    AWidget@ mysvc = layout.GetWidget("uitwcontainer");
    mysvc.AddChildBefore( mytexturewidget, lower);

    ALayout @lo1 = ALayout();
    mysvc.AddChildBefore(lo1, lower);

    AButton @b1 =  AButton();
    b1.SetId( "uitexturewidgetch1");
    b1.SetText("Change texture to  build");
    lo1.AddChild(b1);
    SubscribeToEvent(b1, "WidgetEvent", "HandleUitexturewidgetEvent" );
    AButton @b2 =  AButton();
    b2.SetId( "uitexturewidgetch2");
    b2.SetText("Change texture to colorwheel");
    lo1.AddChild(b2);
    SubscribeToEvent(b2, "WidgetEvent", "HandleUitexturewidgetEvent" );
    AButton @b3 =  AButton();
    b3.SetId( "uitexturewidgetch3");
    b3.SetText("Change texture to planet");
    lo1.AddChild(b3);
    SubscribeToEvent(b3, "WidgetEvent", "HandleUitexturewidgetEvent" );
    
}

void HandleUitexturewidgetEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() == "uitexturewidgetcode" )
        {
            AppLog( "ATextureWidget support : " + widget.GetId() + " was pressed " );
            ViewCode ( "Scripts/code_atexturewidget.as", widget.GetParent() );
        }
        if (widget.GetId() ==  "uitexturewidgetlayout" )
        {
            AppLog( "ATextureWidget support : " + widget.GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_atexturewidget.ui.txt", widget.GetParent() );
        }

        if (widget.GetId() ==  "uitexturewidgetch1" )
        {
            AppLog( "ATextureWidget support : " + widget.GetId() + " was pressed ");
            ATextureWidget @tw = cast<ATextureWidget@>(widget.FindWidget("ATextureWidgetDemo"));
            tw.SetTexture( cache.GetResource("Texture2D","Textures/newbuilddetected_header.jpg") );
        }
        if (widget.GetId() ==  "uitexturewidgetch2" )
        {
            AppLog( "ATextureWidget support : " + widget.GetId() + " was pressed ");
            ATextureWidget @tw = cast<ATextureWidget@>(widget.FindWidget("ATextureWidgetDemo"));
            tw.SetTexture( cache.GetResource( "Texture2D", "Textures/HSV21.png") );
        }
        if (widget.GetId() ==  "uitexturewidgetch3" )
        {
            AppLog( "ATextureWidget support : " + widget.GetId() + " was pressed ");
            ATextureWidget @tw = cast<ATextureWidget@>(widget.FindWidget("ATextureWidgetDemo"));
            tw.SetTexture( cache.GetResource( "Texture2D", "Textures/planet.jpg") );
        }
    }
}

