// AInlineSelect application source code


void setup_uiinlineselect( AWidget @layout )
{
    Array<AWidget@> dest = layout.SearchAWidgetClass( "TBButton" ); 
    for (uint ii = 0; ii < dest.length; ii++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest[ii], "WidgetEvent", "HandleUiinlineselectEvent" );

    ASlider @steps = cast<ASlider@>(layout.GetWidget("ilsstep"));
    if(steps !is null)
        SubscribeToEvent(steps, "WidgetEvent", "HandleUiinlineselectEvent" );

    AInlineSelect @ils = cast<AInlineSelect@>(layout.GetWidget("inlineselectdemo"));
    if (ils !is null)
        SubscribeToEvent(ils, "WidgetEvent", "HandleUiinlineselectEvent" );
}

void HandleUiinlineselectEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() == "uiinlineselectcode" )
        {
            AppLog( "AInlineSelect support : " + widget.GetId() + " was pressed " );
            ViewCode ( "Scripts/code_ainlineselect.as", widget.GetParent() );
        }
        if (widget.GetId() ==  "uiinlineselectlayout" )
        {
            AppLog( "AInlineSelect support : " + widget.GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_ainlineselect.ui.txt", widget.GetParent() );
        }
    }
    else if (eventData["Type"] == UI_EVENT_TYPE_CHANGED )
    {
        if (widget.GetId() == "inlineselectdemo" )
        {
            AInlineSelect @ils = cast<AInlineSelect@>(widget);
            if(ils !is null)
            {
                AppLog( "AInlineSelect event : " + widget.GetId() + " changed value to " + String (ils.GetValue()) );
            }
        }

        if (widget.GetId() == "ilsstep" )
        {
            ASlider @steps = cast<ASlider@>(widget);
            if(steps !is null)
            {
                AInlineSelect @ils = cast<AInlineSelect@>(widget.FindWidget("inlineselectdemo"));
                if(ils !is null)
                {
                    ils.SetStepSize (steps.GetValue());
                }
                AppLog( "AInlineSelect event : " + widget.GetId() + " step size changed to " + String (steps.GetValue()));
            }
        }
    }
}

