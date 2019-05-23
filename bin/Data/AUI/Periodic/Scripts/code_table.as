// handle the periodic table jumps

void setup_table( AWidget@ mylayout) 
{
    AWidget @pgtable = mylayout.GetWidget( "pagetable");
    Array<AWidget@> dest = pgtable.SearchAWidgetClass( "TBButton" ); 
    for (uint ii = 0; ii < dest.length; ii++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest[ii], "WidgetEvent", "HandleTableEvent");

}

void HandleTableEvent(StringHash eventType, VariantMap& eventData)
{
//    URHO3D_PARAM(P_HANDLER, Handler);           // AWidget pointer of widget's OnEvent we are in
//    URHO3D_PARAM(P_TARGET, Target);             // AWidget pointer
//    URHO3D_PARAM(P_TYPE, Type);                 // enum UI_EVENT_TYPE
//    URHO3D_PARAM(P_X, X);                       // int
//    URHO3D_PARAM(P_Y, Y);                       // int
//    URHO3D_PARAM(P_DELTAX, DeltaX);             // int
//    URHO3D_PARAM(P_DELTAY, DeltaY);             // int
//    URHO3D_PARAM(P_COUNT, Count);               // int
//    URHO3D_PARAM(P_KEY, Key);                   // int
//    URHO3D_PARAM(P_SPECIALKEY, SpecialKey);     // enum SPECIAL_KEY
//    URHO3D_PARAM(P_MODIFIERKEYS, ModifierKeys); // enum MODIFIER_KEYS
//    URHO3D_PARAM(P_REFID, RefID);               // string (TBID)
//    URHO3D_PARAM(P_TOUCH, Touch);               // bool
// EventHandled can be set by event receivers to stop event bubble
//    URHO3D_PARAM(P_HANDLED, Handled);               // [OUT] -> bool

    AWidget @widget = eventData["Target"].GetPtr();  // i am sparticus!
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        ATabContainer @maintb = uiview.FindWidget("maintabs");
        ATabContainer @acttb = uiview.FindWidget("primarytabs");
        ATabContainer @semitb = uiview.FindWidget("moretabs");
        ATabContainer @viewtb = uiview.FindWidget("supporttabs");
        ATabContainer @supporttb = uiview.FindWidget("atomictabs");

        if (widget.GetId() ==  "A1" )
        {
            maintb.SetCurrentPage(1);
            acttb.SetCurrentPage(0);
        }
        if (widget.GetId() ==  "A2" )
        {
            maintb.SetCurrentPage(1);
            acttb.SetCurrentPage(1);
        }
        if (widget.GetId() ==  "A3" )
        {
            maintb.SetCurrentPage(1);
            acttb.SetCurrentPage(2);
        }
        if (widget.GetId() ==  "A4" )
        {
            maintb.SetCurrentPage(1);
            acttb.SetCurrentPage(3);
        }
        if (widget.GetId() ==  "A5" )
        {
            maintb.SetCurrentPage(1);
            acttb.SetCurrentPage(4);
        }
        if (widget.GetId() ==  "A6" )
        {
            maintb.SetCurrentPage(1);
            acttb.SetCurrentPage(5);
        }
        if (widget.GetId() ==  "A7" )
        {
            maintb.SetCurrentPage(1);
            acttb.SetCurrentPage(6);
        }
        if (widget.GetId() ==  "A8" )
        {
            maintb.SetCurrentPage(1);
            acttb.SetCurrentPage(7);
        }
        if (widget.GetId() ==  "A9" )
        {
            maintb.SetCurrentPage(1);
            acttb.SetCurrentPage(8);
        }
        if (widget.GetId() ==  "A10" )
        {
            maintb.SetCurrentPage(1);
            acttb.SetCurrentPage(9);
        }

        if (widget.GetId() ==  "B1" )
        {
            maintb.SetCurrentPage(2);
            semitb.SetCurrentPage(0);
        }
        if (widget.GetId() ==  "B2" )
        {
            maintb.SetCurrentPage(2);
            semitb.SetCurrentPage(1);
        }
        if (widget.GetId() ==  "B3" )
        {
            maintb.SetCurrentPage(2);
            semitb.SetCurrentPage(2);
        }
        if (widget.GetId() ==  "B4" )
        {
            maintb.SetCurrentPage(2);
            semitb.SetCurrentPage(3);
        }
        if (widget.GetId() ==  "B5" )
        {
            maintb.SetCurrentPage(2);
            semitb.SetCurrentPage(4);
        }
        if (widget.GetId() ==  "B6" )
        {
            maintb.SetCurrentPage(2);
            semitb.SetCurrentPage(5);
        }
        if (widget.GetId() ==  "B7" )
        {
            maintb.SetCurrentPage(2);
            semitb.SetCurrentPage(6);
        }
        if (widget.GetId() ==  "B8" )
        {
            maintb.SetCurrentPage(2);
            semitb.SetCurrentPage(7);
        }
        if (widget.GetId() ==  "B9" )
        {
            maintb.SetCurrentPage(2);
            semitb.SetCurrentPage(8);
        }

        if (widget.GetId() ==  "C1" )
        {
            maintb.SetCurrentPage(3);
            viewtb.SetCurrentPage(0);
        }
        if (widget.GetId() ==  "C2" )
        {
            maintb.SetCurrentPage(3);
            viewtb.SetCurrentPage(1);
        }
        if (widget.GetId() ==  "C3" )
        {
            maintb.SetCurrentPage(3);
            viewtb.SetCurrentPage(2);
        }
        if (widget.GetId() ==  "C4" )
        {
            maintb.SetCurrentPage(3);
            viewtb.SetCurrentPage(3);
        }
        if (widget.GetId() ==  "C5" )
        {
            maintb.SetCurrentPage(3);
            viewtb.SetCurrentPage(4);
        }
        if (widget.GetId() ==  "C6" )
        {
            maintb.SetCurrentPage(3);
            viewtb.SetCurrentPage(5);
        }
        if (widget.GetId() ==  "C7" )
        {
            maintb.SetCurrentPage(3);
            viewtb.SetCurrentPage(6);
        }
        if (widget.GetId() ==  "C8" )
        {
            maintb.SetCurrentPage(3);
            viewtb.SetCurrentPage(7);
        }
        if (widget.GetId() ==  "C9" )
        {
            maintb.SetCurrentPage(3);
            viewtb.SetCurrentPage(8);
        }
        if (widget.GetId() ==  "C10" )
        {
            maintb.SetCurrentPage(3);
            viewtb.SetCurrentPage(9);
        }

        if (widget.GetId() ==  "D1" )
        {
            maintb.SetCurrentPage(4);
            supporttb.SetCurrentPage(0);
        }
        if (widget.GetId() ==  "D2" )
        {
            maintb.SetCurrentPage(4);
            supporttb.SetCurrentPage(1);
        }
        if (widget.GetId() ==  "D3" )
        {
            maintb.SetCurrentPage(4);
            supporttb.SetCurrentPage(2);
        }
        if (widget.GetId() ==  "D4" )
        {
            maintb.SetCurrentPage(4);
            supporttb.SetCurrentPage(3);
        }
        if (widget.GetId() ==  "D5" )
        {
            maintb.SetCurrentPage(4);
            supporttb.SetCurrentPage(4);
        }
        if (widget.GetId() ==  "D6" )
        {
            maintb.SetCurrentPage(4);
            supporttb.SetCurrentPage(5);
        }
        if (widget.GetId() ==  "D7" )
        {
            maintb.SetCurrentPage(4);
            supporttb.SetCurrentPage(6);
        }
        if (widget.GetId() ==  "D8" )
        {
            maintb.SetCurrentPage(4);
            supporttb.SetCurrentPage(7);
        }
        if (widget.GetId() ==  "D9" )
        {
            maintb.SetCurrentPage(4);
            supporttb.SetCurrentPage(8);
        }
        if (widget.GetId() ==  "D10" )
        {
            maintb.SetCurrentPage(4);
            supporttb.SetCurrentPage(9);
        }
    }
}

