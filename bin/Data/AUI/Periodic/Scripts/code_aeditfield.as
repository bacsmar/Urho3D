// AEditField application source code

void setup_uieditfield( AWidget @layout )
{
    Array<AWidget@> dest = layout.SearchAWidgetClass( "TBButton" ); 
    for (uint ii = 0; ii < dest.length; ii++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest[ii], "WidgetEvent", "HandleUieditfieldEvent" );

    AWidget @ed1 = layout.GetWidget("editfieldsingle");
    if ( ed1 !is null)
        SubscribeToEvent(ed1, "WidgetEvent", "HandleUieditfieldEvent" );
    AWidget @ed2 = layout.GetWidget("editfieldmulti");
    if ( ed2 !is null)
        SubscribeToEvent(ed2, "WidgetEvent", "HandleUieditfieldEvent" );
}

void HandleUieditfieldEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() == "uieditfieldcode" )
        {
            AppLog( "AEditField support : " + widget.GetId() + " was pressed " );
            ViewCode ( "Scripts/code_aeditfield.as", widget.GetParent() );
        }
        if (widget.GetId() ==  "uieditfieldlayout" )
        {
            AppLog( "AEditField support : " + widget.GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_aeditfield.ui.txt", widget.GetParent() );
        }

        if (widget.GetId() ==  "editfieldadd" )
        {
            AppLog( "AEditField action : " + widget.GetId() + " was pressed ");
            AEditField @ef1 = cast<AEditField@>(widget.FindWidget("editfieldmulti"));
            if(ef1 !is null)
            {
                File@ filex = cache.GetFile("Scenes/layout_aeditfield.ui.txt");
                String textx = filex.ReadString();
                filex.Close();
                ef1.SetText(textx);
            }
        }
        if (widget.GetId() ==  "editfieldclr" )
        {
            AppLog( "AEditField action : " + widget.GetId() + " was pressed ");
            AEditField @ef2 = cast<AEditField@>(widget.FindWidget("editfieldmulti"));
            if(ef2 !is null)
                ef2.SetText("");
        }
    }
    else
    {
        if ( widget.GetId() ==  "editfieldsingle" )
        {
            AEditField @efx = cast<AEditField@>(widget);
            AppLog( "AEditField event : " + widget.GetId() + " text = `" + efx.GetText() );
        }
        if ( widget.GetId() ==  "editfieldmulti" )
        {
            AEditField @efx = cast<AEditField@>(widget);
            AppLog( "AEditField event : " + widget.GetId() + " text = `" + efx.GetText());
        }
    }
}

