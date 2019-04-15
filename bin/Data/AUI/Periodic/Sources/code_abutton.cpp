// AButton application source code
#include "PeriodicApp.h"

void PeriodicApp::setup_abutton( AWidget *layout)
{
    PODVector<AWidget*> dest;
    layout->SearchWidgetClass( "TBButton", dest );
    for (unsigned ii = 0; ii < dest.Size(); ii++)
        SubscribeToEvent(dest[ii], E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAbuttonEvent ));
}

void PeriodicApp::HandleAbuttonEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    if ( widget == NULL ) return;
    if (eventData[P_TYPE] == UI_EVENT_TYPE_CLICK)
    {
        if (widget->GetId() == "uibuttoncode" )
        {
            AppLog( "AButton support : " + widget->GetId() + " was pressed " );
            ViewCode ( "Sources/code_abutton.cpp", widget->GetParent() );
        }
        if (widget->GetId() == "uibuttonlayout" )
        {
            AppLog( "AButton support : " + widget->GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_abutton.ui.txt", widget->GetParent() );
        }

        if (widget->GetId() == "demobutton" )
        {
            AppLog( "AButton action : " + widget->GetId() + " was pressed ");
        }
        if (widget->GetId() == "buttonducky" )
        {
            AppLog( "AButton action : " + widget->GetId() + " was pressed ");
        }
        if (widget->GetId() == "buttonready" )
        {
            AppLog( "AButton action : " + widget->GetId() + " was pressed ");
        }
        if (widget->GetId() == "buttonatomic" )
        {
            AppLog( "AButton action : " + widget->GetId() + " was pressed ");
        }
        if (widget->GetId() == "buttongreen" )
        {
            AppLog( "AButton action : " + widget->GetId() + " was pressed ");
        }
    }
}

