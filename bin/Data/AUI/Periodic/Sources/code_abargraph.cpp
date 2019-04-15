// ABargraph application source code
#include "PeriodicApp.h"

void PeriodicApp::setup_abargraph( AWidget *layout )
{
    PODVector<AWidget*> dest;
    layout->SearchWidgetClass( "TBButton", dest );
    for (unsigned ii = 0; ii < dest.Size(); ii++)
        SubscribeToEvent(dest[ii], E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp,HandleAbargraphEvent ));
}

void PeriodicApp::HandleAbargraphEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    if ( widget == NULL ) return;
    if (eventData[P_TYPE] == UI_EVENT_TYPE_CLICK)
    {
        if (widget->GetId() == "uibargraphcode" )
        {
            AppLog( "ABargraph support : " + widget->GetId() + " was pressed " );
            ViewCode ( "Sources/code_abargraph.cpp", widget->GetParent() );
        }
        if (widget->GetId() ==  "uibargraphlayout" )
        {
            AppLog( "ABargraph support : " + widget->GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_abargraph.ui.txt", widget->GetParent() );
        }
    }
}

