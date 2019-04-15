// AWidget application source code
#include "PeriodicApp.h"

void PeriodicApp::setup_awidget( AWidget *layout )
{
    PODVector<AWidget*> dest;
    layout->SearchWidgetClass( "TBButton", dest );
    for (unsigned ii = 0; ii < dest.Size(); ii++)
        SubscribeToEvent(dest[ii], E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAwidgetEvent ));
}

void PeriodicApp::HandleAwidgetEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    if ( widget == NULL ) return;
    if (eventData[P_TYPE] == UI_EVENT_TYPE_CLICK)
    {
        if (widget->GetId() == "uiwidgetcode" )
        {
            AppLog( "AWidget support : " + widget->GetId() + " was pressed " );
            ViewCode ( "Sources/code_awidget.cpp", widget->GetParent() );
        }
        if (widget->GetId() ==  "uiwidgetlayout" )
        {
            AppLog( "AWidget support : " + widget->GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_awidget.ui.txt", widget->GetParent() );
        }
    }
}

