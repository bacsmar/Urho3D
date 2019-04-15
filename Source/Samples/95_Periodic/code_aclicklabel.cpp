// AClickLabel application source code
#include "PeriodicApp.h"


void PeriodicApp::setup_aclicklabel( AWidget *layout )
{
    PODVector<AWidget*> dest;
    layout->SearchWidgetClass( "TBButton", dest );
    for (unsigned ii = 0; ii < dest.Size(); ii++)
        SubscribeToEvent(dest[ii], E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAclicklabelEvent ));

    AWidget *chk1 = layout->GetWidget ("somecheck");
    if (chk1)
        SubscribeToEvent(chk1, E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAclicklabelEvent ));

    AWidget *chk2 = layout->GetWidget ("someradio");
    if (chk2)
        SubscribeToEvent(chk2, E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAclicklabelEvent ));
}

void PeriodicApp::HandleAclicklabelEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    if ( widget == NULL ) return;
    if (eventData[P_TYPE] == UI_EVENT_TYPE_CLICK)
    {
        if (widget->GetId() == "uiclicklabelcode" )
        {
            AppLog( "AClickLabel support : " + widget->GetId() + " was pressed " );
            ViewCode ( "Sources/code_aclicklabel.cpp", widget->GetParent() );
        }
        if (widget->GetId() ==  "uiclicklabellayout" )
        {
            AppLog( "AClickLabel support : " + widget->GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_aclicklabel.ui.txt", widget->GetParent() );
        }

        if (widget->GetId() == "somecheck" )
        {
            AppLog( "AClickLabel event : " + widget->GetId() + " was pressed, state = " + String ( widget->GetValue() ) );
        }
        if (widget->GetId() == "someradio" )
        {
            AppLog( "AClickLabel event : " + widget->GetId() + " was pressed, state = " + String ( widget->GetValue() ) );
        }
    }
}

