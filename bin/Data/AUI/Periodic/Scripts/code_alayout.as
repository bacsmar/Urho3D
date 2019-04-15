// ALayout application source code

String currentxxxxx;

void setup_uilayout( AWidget @layout, AView @uiview )
{
    Array<AWidget@> dest = layout.SearchAWidgetClass( "TBButton" ); 
    for (uint ii = 0; ii < dest.length; ii++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest[ii], "WidgetEvent", "HandleUilayoutEvent" );

    ALayout @myc = cast<ALayout @>(layout.GetWidget("uilayoutcontainer")); // get the container layout

    AButton @tf0 = AButton();  // the layout-o-matic spawner
    tf0.SetText( "LAYOUT-O-MATIC");
    tf0.SetId( "go_layout_config");
    ALayout @lo0 = ALayout();
    lo0.SetId( "target_layout");
    lo0.SetLayoutConfig ( "-----" );
    lo0.Load("Scenes/simp_button.ui.txt");
    lo0.AddChildBefore(tf0, lo0.GetFirstChild() );
    myc.AddChild(lo0);  // drop it in
    SubscribeToEvent(tf0, "WidgetEvent", "HandleUilayoutEvent" );

    ATextField @tf1 = ATextField();
    tf1.SetText( "layout config XACAC");
    ALayout @lo1 = ALayout();
    lo1.SetLayoutConfig ( "XACAC" );
    lo1.Load("Scenes/simp_button.ui.txt");
    lo1.AddChildBefore(tf1, lo1.GetFirstChild() );
    myc.AddChild(lo1);

    ATextField @tf2 = ATextField();
    tf2.SetText( "layout config XGCAC");
    ALayout @lo2 = ALayout();
    lo2.SetLayoutConfig ( "XGCAC" );
    lo2.Load("Scenes/simp_button.ui.txt");
    lo2.AddChildBefore(tf2, lo2.GetFirstChild() );
    myc.AddChild(lo2);

    ATextField @tf3 =  ATextField();
    tf3.SetText( "layout config XPCAC");
    ALayout @lo3 = ALayout();
    lo3.SetLayoutConfig ( "XPCAC" );
    lo3.Load("Scenes/simp_button.ui.txt");
    lo3.AddChildBefore(tf3, lo3.GetFirstChild() );
    myc.AddChild(lo3);

    ATextField @tf4 = ATextField();
    tf4.SetText( "layout config XACGC");
    ALayout @lo4 = ALayout();
    lo4.SetLayoutConfig ( "XACGC" );
    lo4.Load("Scenes/simp_button.ui.txt");
    lo4.AddChildBefore(tf4, lo4.GetFirstChild() );
    myc.AddChild(lo4);

    ATextField @tf5 =  ATextField();
    tf5.SetText( "layout config XGRGC");
    ALayout @lo5 = ALayout();
    lo5.SetLayoutConfig ( "XGRGC" );
    lo5.Load("Scenes/simp_button.ui.txt");
    lo5.AddChildBefore(tf5, lo5.GetFirstChild() );
    myc.AddChild(lo5);

    ATextField @tf6 = ATextField();
    tf6.SetText( "layout config XPLGC");
    ALayout @lo6 = ALayout();
    lo6.SetLayoutConfig ( "XPLGC" );
    lo6.Load("Scenes/simp_button.ui.txt");
    lo6.AddChildBefore(tf6, lo6.GetFirstChild() );
    myc.AddChild(lo6);

    ATextField @tf7 = ATextField();
    tf7.SetText( "layout config XACPC");
    ALayout @lo7 = ALayout();
    lo7.SetLayoutConfig ( "XACPC" );
    lo7.Load("Scenes/simp_button.ui.txt");
    lo7.AddChildBefore(tf7, lo7.GetFirstChild() );
    myc.AddChild(lo7);

    ATextField @tf8 =  ATextField();
    tf8.SetText( "layout config XGLPL");
    ALayout @lo8 =  ALayout();
    lo8.SetLayoutConfig ( "XGLPL" );
    lo8.Load("Scenes/simp_button.ui.txt");
    lo8.AddChildBefore(tf8, lo8.GetFirstChild() );
    myc.AddChild(lo8);

    ATextField @tf9 =  ATextField();
    tf9.SetText( "layout config XPCPR");
    ALayout @lo9 =  ALayout();
    lo9.SetLayoutConfig ( "XPCPR" );
    lo9.Load("Scenes/simp_button.ui.txt");
    lo9.AddChildBefore(tf9, lo9.GetFirstChild() );
    myc.AddChild(lo9);

    currentxxxxx = "XGCPC";  // needs to be more persistant? no.
    Variant strx (currentxxxxx);
    SetGlobalVar("layoutomaticstr", strx ); // LAYOUT-O-MATIC string, cheating, using a globalvar

}

void HandleUilayoutEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() == "go_layout_config" ) // its LAYOUT-O-MATIC time.
        {
            AppLog( "ALayout action : " + widget.GetId() + " was pressed, its LAYOUT-O-MATIC time");
            AWindow@ win = AWindow();
            win.SetSettings ( UI_WINDOW_SETTINGS_DEFAULT );
            win.SetText( "LAYOUT-O-MATIC(tm)");
            win.Load("Scenes/view_layout.ui.txt");
            win.ResizeToFitContent();
            uiview.AddChild(win);
            AWidget @okbutt = win.GetWidget("ok");
            SubscribeToEvent(okbutt, "WidgetEvent", "HandleUilayoutEvent" );
            Array<AWidget@> lox = win.SearchAWidgetClass( "TBRadioButton" ); 
            for (uint ii = 0; ii < lox.length; ii++)  // set bulk event handlers on all buttons -- boom!
                SubscribeToEvent(lox[ii], "WidgetEvent", "HandleUilayoutEvent" );
       }
        if (widget.GetId() ==  "ok" )
        {
            AWindow @mywindow = cast<AWindow @>(FindTheWindowParent(widget));
            if (mywindow !is null)
                mywindow.Close();
        }
        if (widget.GetId() ==  "set_ax" )
        {
            ALayout @targetl = cast<ALayout @>(widget.FindWidget("target_layout")); // who to operate on.
            ARadioButton @setax = cast< ARadioButton@>(widget); // who we are
            if (targetl !is null && setax !is null)
            {
                if ( setax.GetValue() == 1)
                {
                    currentxxxxx = GetGlobalVar("layoutomaticstr").GetString();
                    currentxxxxx[0] = 'X'; //current.Replace (0, 1, "X");
                    targetl.SetLayoutConfig(currentxxxxx);
                    Variant currentx ( currentxxxxx );
                    SetGlobalVar("layoutomaticstr", currentx );
                }
            }
        }
        if (widget.GetId() ==  "set_ay" )
        {
            ALayout @targetl = cast<ALayout @>(widget.FindWidget("target_layout")); // who to operate on.
            ARadioButton @setay = cast< ARadioButton@>(widget); // who we are
            if (targetl !is null  && setay !is null )
            {
                if ( setay.GetValue() == 1)
                {
                    currentxxxxx = GetGlobalVar("layoutomaticstr").GetString();
                    currentxxxxx[0] = 'Y'; //current.Replace (0, 1, "Y");
                    targetl.SetLayoutConfig(currentxxxxx );
                    Variant currentx ( currentxxxxx );
                    SetGlobalVar("layoutomaticstr", currentx );
                }
            }
        }

        if (widget.GetId() ==  "set_sza" )
        {
            ALayout @targetl = cast<ALayout @>(widget.FindWidget("target_layout")); // who to operate on.
            ARadioButton @setay = cast< ARadioButton@>(widget); // who we are
            if (targetl  !is null && setay !is null )
            {
                if ( setay.GetValue() == 1)
                {
                    currentxxxxx = GetGlobalVar("layoutomaticstr").GetString();
                    currentxxxxx[1] = 'A'; //current.Replace (1, 1, "A");
                    targetl.SetLayoutConfig(currentxxxxx );
                    Variant currentx ( currentxxxxx );
                    SetGlobalVar("layoutomaticstr", currentx );
                }
            }
        }
        if (widget.GetId() ==  "set_szg" )
        {
            ALayout @targetl = cast<ALayout @>(widget.FindWidget("target_layout")); // who to operate on.
            ARadioButton @setay = cast< ARadioButton@>(widget); // who we are
            if (targetl !is null && setay !is null )
            {
                if ( setay.GetValue() == 1)
                {
                    currentxxxxx = GetGlobalVar("layoutomaticstr").GetString();
                    currentxxxxx[1] = 'G'; //current.Replace (1, 1, "G");
                    targetl.SetLayoutConfig(currentxxxxx );
                    Variant currentx ( currentxxxxx );
                    SetGlobalVar("layoutomaticstr", currentx );
                }
            }
        }
        if (widget.GetId() ==  "set_szp" )
        {
            ALayout @targetl = cast<ALayout @>(widget.FindWidget("target_layout")); // who to operate on.
            ARadioButton @setay = cast< ARadioButton@>(widget); // who we are
            if (targetl !is null && setay !is null)
            {
                if ( setay.GetValue() == 1)
                {
                    currentxxxxx = GetGlobalVar("layoutomaticstr").GetString();
                    currentxxxxx[1] = 'P'; //current.Replace (1, 1, "P");
                    targetl.SetLayoutConfig(currentxxxxx );
                    Variant currentx ( currentxxxxx );
                    SetGlobalVar("layoutomaticstr", currentx );
                }
            }
        }

        if (widget.GetId() ==  "set_posc" )
        {
            ALayout @targetl = cast<ALayout @>(widget.FindWidget("target_layout")); // who to operate on.
            ARadioButton @setay = cast< ARadioButton@>(widget); // who we are
            if (targetl !is null && setay !is null)
            {
                if ( setay.GetValue() == 1)
                {
                    currentxxxxx = GetGlobalVar("layoutomaticstr").GetString();
                    currentxxxxx[2] = 'C'; //current.Replace (2, 1, "C");
                    targetl.SetLayoutConfig(currentxxxxx );
                    Variant currentx ( currentxxxxx );
                    SetGlobalVar("layoutomaticstr", currentx );
                }
            }
        }
        if (widget.GetId() ==  "set_posg" )
        {
            ALayout @targetl = cast<ALayout @>(widget.FindWidget("target_layout")); // who to operate on.
            ARadioButton @setay = cast< ARadioButton@>(widget); // who we are
            if (targetl !is null && setay !is null)
            {
                if ( setay.GetValue() == 1)
                {
                    String currentxxxxx = GetGlobalVar("layoutomaticstr").GetString();
                    currentxxxxx[2] = 'G'; //current.Replace (2, 1, "G");
                    targetl.SetLayoutConfig(currentxxxxx );
                    Variant currentx ( currentxxxxx );
                    SetGlobalVar("layoutomaticstr", currentx );
                }
            }
        }
        if (widget.GetId() ==  "set_posl" )
        {
            ALayout @targetl = cast<ALayout @>(widget.FindWidget("target_layout")); // who to operate on.
            ARadioButton @setay = cast< ARadioButton@>(widget); // who we are
            if (targetl !is null && setay !is null)
            {
                if ( setay.GetValue() == 1)
                {
                    currentxxxxx = GetGlobalVar("layoutomaticstr").GetString();
                    currentxxxxx[2] = 'L'; //current.Replace (2, 1, "L");
                    targetl.SetLayoutConfig(currentxxxxx );
                    Variant currentx ( currentxxxxx );
                    SetGlobalVar("layoutomaticstr", currentx );
                }
            }
        }
        if (widget.GetId() ==  "set_posr" )
        {
            ALayout @targetl = cast<ALayout @>(widget.FindWidget("target_layout")); // who to operate on.
            ARadioButton @setay = cast<ARadioButton@>(widget); // who we are
            if (targetl !is null && setay !is null)
            {
                if ( setay.GetValue() == 1)
                {
                    currentxxxxx = GetGlobalVar("layoutomaticstr").GetString();
                    currentxxxxx[2] = 'R'; //current.Replace (2, 1, "R");
                    targetl.SetLayoutConfig(currentxxxxx );
                    Variant currentx ( currentxxxxx );
                    SetGlobalVar("layoutomaticstr", currentx );
                }
            }
        }

        if (widget.GetId() ==  "set_dista" )
        {
            ALayout @targetl = cast<ALayout @>(widget.FindWidget("target_layout")); // who to operate on.
            ARadioButton @setay = cast< ARadioButton@>(widget); // who we are
            if (targetl !is null && setay !is null)
            {
                if ( setay.GetValue() == 1)
                {
                    currentxxxxx = GetGlobalVar("layoutomaticstr").GetString();
                    currentxxxxx[3] = 'A'; //current.Replace (3, 1, "A");
                    targetl.SetLayoutConfig(currentxxxxx );
                    Variant currentx ( currentxxxxx );
                    SetGlobalVar("layoutomaticstr", currentx );
                }
            }
        }
        if (widget.GetId() ==  "set_distg" )
        {
            ALayout @targetl = cast<ALayout @>(widget.FindWidget("target_layout")); // who to operate on.
            ARadioButton @setay = cast< ARadioButton@>(widget); // who we are
            if (targetl !is null && setay !is null)
            {
                if ( setay.GetValue() == 1)
                {
                    currentxxxxx = GetGlobalVar("layoutomaticstr").GetString();
                    currentxxxxx[3] = 'G'; //current.Replace (3, 1, "G");
                    targetl.SetLayoutConfig(currentxxxxx );
                    Variant currentx ( currentxxxxx );
                    SetGlobalVar("layoutomaticstr", currentx );
                }
            }
        }
        if (widget.GetId() ==  "set_distp" )
        {
            ALayout @targetl = cast<ALayout @>(widget.FindWidget("target_layout")); // who to operate on.
            ARadioButton @setay = cast< ARadioButton@>(widget); // who we are
            if (targetl !is null && setay !is null)
            {
                if ( setay.GetValue() == 1)
                {
                    currentxxxxx = GetGlobalVar("layoutomaticstr").GetString();
                    currentxxxxx[3] = 'P'; //current.Replace (3, 1, "P");
                    targetl.SetLayoutConfig(currentxxxxx );
                    Variant currentx ( currentxxxxx );
                    SetGlobalVar("layoutomaticstr", currentx );
                }
            }
        }

        if (widget.GetId() ==  "set_dpc" )
        {
            ALayout @targetl = cast<ALayout @>(widget.FindWidget("target_layout")); // who to operate on.
            ARadioButton @setdpc = cast<ARadioButton@>(widget); // who we are
            if (targetl !is null && setdpc !is null)
            {
                if ( setdpc.GetValue() == 1 )
                {
                    currentxxxxx = GetGlobalVar("layoutomaticstr").GetString();
                    currentxxxxx[4] = 'C'; //current.Replace (4, 1, "C");
                    targetl.SetLayoutConfig(currentxxxxx);
                    Variant currentx ( currentxxxxx );
                    SetGlobalVar("layoutomaticstr", currentx );
                }
            }
        }
        if (widget.GetId() ==  "set_dpl" )
        {
            ALayout @targetl = cast<ALayout @>(widget.FindWidget("target_layout")); // who to operate on.
            ARadioButton @setdpl = cast< ARadioButton@>(widget); // who we are
            if (targetl !is null && setdpl !is null)
            {
                if ( setdpl.GetValue() == 1)
                {
                    currentxxxxx = GetGlobalVar("layoutomaticstr").GetString();
                    currentxxxxx[4] = 'L'; //current.Replace (4, 1, "L");
                     targetl.SetLayoutConfig(currentxxxxx );
                    Variant currentx ( currentxxxxx );
                    SetGlobalVar("layoutomaticstr", currentx );
                }
            }
        }
        if (widget.GetId() ==  "set_dpr" )
        {
            ALayout @targetl = cast<ALayout @>(widget.FindWidget("target_layout")); // who to operate on.
            ARadioButton @setdpr = cast< ARadioButton@>(widget); // who we are
            if (targetl !is null && setdpr !is null)
            {
                if ( setdpr.GetValue() == 1)
                {
                    currentxxxxx = GetGlobalVar("layoutomaticstr").GetString();
                    currentxxxxx[4] = 'R'; //current.Replace (4, 1, "R");
                    targetl.SetLayoutConfig(currentxxxxx);
                    Variant currentx ( currentxxxxx );
                    SetGlobalVar("layoutomaticstr", currentx );
                }
            }
        }
    }
}

