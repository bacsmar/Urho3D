// ACheckBox application source code
#include "PeriodicApp.h"

void PeriodicApp::setup_acheckbox( AWidget *layout )
{
    PODVector<AWidget*> dest;
    layout->SearchWidgetClass( "TBButton", dest );
    for (unsigned ii = 0; ii < dest.Size(); ii++)
        SubscribeToEvent(dest[ii], E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAcheckboxEvent ));

    AWidget *demochk = layout->GetWidget ("democheck");
    if (demochk)
        SubscribeToEvent(demochk, E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAcheckboxEvent ));
}

void PeriodicApp::HandleAcheckboxEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    if ( widget == NULL ) return;
    if (eventData[P_TYPE] == UI_EVENT_TYPE_CLICK)
    {
        if (widget->GetId() == "uicheckboxcode" )
        {
            AppLog( "ACheckBox support : " + widget->GetId() + " was pressed " );
            ViewCode ( "Sources/code_acheckbox.cpp", widget->GetParent() );
        }
        if (widget->GetId() ==  "uicheckboxlayout" )
        {
            AppLog( "ACheckBox support : " + widget->GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_acheckbox.ui.txt", widget->GetParent() );
        }

        if (widget->GetId() == "democheck" )
        {
            AppLog( "ACheckBox event : " + widget->GetId() + " was pressed, state = " + String ( widget->GetValue() ) );
        }

        if (widget->GetId() ==  "checkset" )
        {
            AWidget *demochk = widget->FindWidget ("democheck");
            if (demochk)
            {
                demochk->SetValue (1);
                AppLog( "ACheckBox action : " + widget->GetId() + " was pressed, set state to 1" );
            }
        }
        if (widget->GetId() ==  "checkunset" )
        {
            AWidget *demochk = widget->FindWidget ("democheck");
            if (demochk)
            {
                demochk->SetValue (0);
                AppLog( "ACheckBox action : " + widget->GetId() + " was pressed, set state to 0" );
            }
        }
    }
}

