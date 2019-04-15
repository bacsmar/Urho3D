// UIFontdescription application source code


void setup_uifontdescription( AWidget @layout )
{
    Array<AWidget@> dest = layout.SearchAWidgetClass( "TBButton" ); 
    for (uint ii = 0; ii < dest.length; ii++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest[ii], "WidgetEvent", "HandleUifontdescriptionEvent" );

    ASlider @steps = cast<ASlider@>(layout.GetWidget("fontstep"));
    if(steps !is null)
        SubscribeToEvent(steps, "WidgetEvent", "HandleUifontdescriptionEvent" );
}

void HandleUifontdescriptionEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() == "uifontdescriptioncode" )
        {
            AppLog( "UIFontdescription support : " + widget.GetId() + " was pressed " );
            ViewCode ( "Scripts/code_afontdescription.as", widget.GetParent() );
        }
        if (widget.GetId() ==  "uifontdescriptionlayout" )
        {
            AppLog( "UIFontdescription support : " + widget.GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_afontdescription.ui.txt", widget.GetParent() );
        }
    }
    else if (eventData["Type"] == UI_EVENT_TYPE_CHANGED )
    {
        if ( widget.GetId() ==  "fontstep" )
        {
            ASlider @uis = cast<ASlider@>(widget);
            if (uis !is null)
            {
                ATextField @mytext = cast<ATextField@>(widget.FindWidget("changetext"));
                AFontDescription @myfont = AFontDescription();
                myfont.SetSize(int(uis.GetValue()));
                myfont.SetId("Vera");
                mytext.SetFontDescription (myfont);
                mytext.SetText ( "Size " + String (int (uis.GetValue())));
                AppLog( "UIFontdescription action : " + widget.GetId() + " step size changed to " + String (uis.GetValue()));
            }
        }
    }
}

