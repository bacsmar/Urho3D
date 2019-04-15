// ARadioButton application source code
#include <Urho3D/AUI/ARadioButton.h>
#include "PeriodicApp.h"

void PeriodicApp::setup_aradiobutton( AWidget *layout)
{
    PODVector<AWidget*> dest;
    layout->SearchWidgetClass( "TBButton", dest );
    for (unsigned ii = 0; ii < dest.Size(); ii++)
        SubscribeToEvent(dest[ii], E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAradiobuttonEvent ));

    AWidget *demochk = layout->GetWidget ("demoradio");
    if ( demochk)
        SubscribeToEvent( demochk, E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAradiobuttonEvent ));
}

void PeriodicApp::HandleAradiobuttonEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    if ( widget == NULL ) return;
    if (eventData[P_TYPE] == UI_EVENT_TYPE_CLICK)
    {
        if (widget->GetId() == "uiradiobuttoncode" )
        {
            AppLog( "ARadioButton support : " + widget->GetId() + " was pressed " );
            ViewCode ( "Sources/code_aradiobutton.cpp", widget->GetParent() );
        }
        if (widget->GetId() ==  "uiradiobuttonlayout" )
        {
            AppLog( "ARadioButton support : " + widget->GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_aradiobutton.ui.txt", widget->GetParent() );
        }

        if (widget->GetId() == "demoradio" )
        {
            AppLog( "ARadioButton event : " + widget->GetId() + " was pressed, state = " + String ( widget->GetValue() ) );
        }

        if (widget->GetId() ==  "radioset" )
        {
            AWidget *demochk = widget->FindWidget ("demoradio");
            if (demochk)
            {
                demochk->SetValue (1);
                AppLog( "ARadioButton action : " + widget->GetId() + " was pressed, set state to 1" );
            }
        }
        if (widget->GetId() ==  "radiounset" )
        {
            AWidget *demochk = widget->FindWidget ("demoradio");
            if (demochk)
            {
                demochk->SetValue (0);
                AppLog( "ARadioButton action : " + widget->GetId() + " was pressed, set state to 0" );
            }
        }
    }
}

