// ATabContainer application source code


void setup_uitabcontainer( AWidget @layout )
{
    Array<AWidget@> dest = layout.SearchAWidgetClass( "TBButton" ); 
    for (uint ii = 0; ii < dest.length; ii++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest[ii], "WidgetEvent", "HandleUitabcontainerEvent" );

    ATabContainer @tcx = cast<ATabContainer@>(layout.GetWidget("ATabContainerDemo"));
    if ( tcx !is null)
    {
        tcx.SetCurrentPage(0);   // fix or it looks like crap
        SubscribeToEvent(tcx, "WidgetEvent", "HandleAllTabcontainerEvent" );
       // HELP this (below) doesnt work in Urho3D, it didnt work too well in Atomic
      //  tcx.SubscribeToEvent( "WidgetEvent", "HandleAllTabcontainerEvent" );
       // warning - this will route for all ATabContainer instances events into this event handler.
    }
}

void HandleAllTabcontainerEvent(StringHash eventType, VariantMap& eventData)
{
    String refid = eventData["RefID"].GetString();
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;

    AWidget @demo = widget.FindWidget("ATabContainerDemo");  // find our specific widget
    if ( widget !is demo ) return; // if its not ours, bail

    if (eventData["Type"] == UI_EVENT_TYPE_TAB_CHANGED )
    {
        if ( widget.GetId() ==  "ATabContainerDemo" )
        {
            ATabContainer @tcx = cast<ATabContainer@>(widget);  // check the focus & stuff, or it gets a little spammy
            if ( tcx !is null && ( tcx.GetState(UI_WIDGET_STATE_FOCUSED) == true ) )
                AppLog( "ATabContainer event : " + widget.GetId() + " UI_EVENT_TYPE_TAB_CHANGED to " + String( tcx.GetCurrentPage() )
                        + " id: " + tcx.GetCurrentPageWidget().GetId() );
        }
    }
}


void HandleUitabcontainerEvent(StringHash eventType, VariantMap& eventData)
{
    String refid = eventData["RefID"].GetString();
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() == "uitabcontainercode" )
        {
            AppLog( "ATabContainer support : " + widget.GetId() + " was pressed " );
            ViewCode ( "Scripts/code_atabcontainer.as", widget.GetParent() );
        }
        if (widget.GetId() ==  "uitabcontainerlayout" )
        {
            AppLog( "ATabContainer support : " + widget.GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_atabcontainer.ui.txt", widget.GetParent() );
        }

        if (widget.GetId() ==  "uitabcontainerremove" )
        {
            AppLog( "ATabContainer action : " + widget.GetId() + " was pressed ");
            ATabContainer @tcx = cast<ATabContainer@>(widget.FindWidget("ATabContainerDemo"));
            int current = tcx.GetCurrentPage();
            tcx.DeletePage(current);
        }
        if (widget.GetId() ==  "uitabcontaineradd" )
        {
            AppLog( "ATabContainer action : " + widget.GetId() + " was pressed ");
            ATabContainer @tcx = cast<ATabContainer@>(widget.FindWidget("ATabContainerDemo"));
            tcx.AddTabPageFile("New File", "Scenes/sheet.ui.txt" );
        }
        if (widget.GetId() ==  "uitabcontainermake" )
        {
            AppLog( "ATabContainer action : " + widget.GetId() + " was pressed ");
            ATabContainer @tcx = cast<ATabContainer@>(widget.FindWidget("ATabContainerDemo"));
            ALayout @lo = ALayout();
            lo.SetLayoutConfig ( "YAGAC" );  // YACAC!
            AEditField @myeditfield = AEditField();
            myeditfield.SetGravity( UI_GRAVITY_ALL);
            myeditfield.SetMultiline(true);
            File@ filex = cache.GetFile("Scripts/code_atabcontainer.as");
            String textx = filex.ReadString();
            filex.Close();
            myeditfield.SetText(textx);
            AFontDescription @myfont = AFontDescription(); // put in a coder font
            myfont.SetSize(16);
            myfont.SetId("Vera");
            myeditfield.SetFontDescription (myfont);
            lo.AddChild (myeditfield);
            tcx.AddTabPageWidget("New Code", lo);
        }
        if (widget.GetId() ==  "uitabcontainerundock" )
        {
            AppLog( "ATabContainer action : " + widget.GetId() + " was pressed ");
            ATabContainer @tcx = cast<ATabContainer@>(widget.FindWidget("ATabContainerDemo"));
            int current = tcx.GetCurrentPage();
            tcx.UndockPage(current);
        }
        if (widget.GetId() ==  "uitabcontainerredock" )
        {
            AppLog( "ATabContainer action : " + widget.GetId() + " was pressed ");
            ATabContainer @tcx = cast<ATabContainer@>(widget.FindWidget("ATabContainerDemo"));
            if ( !tcx.DockWindow ( "tab1" ) )
                if ( !tcx.DockWindow ( "tab2" )  )
                    if ( !tcx.DockWindow ( "tab3" )  )
                        if ( !tcx.DockWindow ( "New File" )  )
                            if ( !tcx.DockWindow ( "New Code" ) )
                                AppLog( "ATabContainer action : no more windows to dock.");
        }
    }
}

