// AScrollContainer application source code
#include "PeriodicApp.h"

void PeriodicApp::setup_ascrollcontainer( AWidget *layout )
{
    PODVector<AWidget*> dest;
    layout->SearchWidgetClass( "TBButton", dest );
    for (unsigned ii = 0; ii < dest.Size(); ii++)
        SubscribeToEvent(dest[ii], E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAscrollcontainerEvent ));
}

void PeriodicApp::HandleAscrollcontainerEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    if ( widget == NULL ) return;
    if (eventData[P_TYPE] == UI_EVENT_TYPE_CLICK)
    {
        if (widget->GetId() == "uiscrollcontainercode" )
        {
            AppLog( " support : " + widget->GetId() + " was pressed " );
            ViewCode ( "Sources/code_ascrollcontainer.cpp", widget->GetParent() );
        }
        if (widget->GetId() ==  "uiscrollcontainerlayout" )
        {
            AppLog( " support : " + widget->GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_ascrollcontainer.ui.txt", widget->GetParent() );
        }
    }
}

