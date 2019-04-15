// ASkinImage application source code
#include "PeriodicApp.h"

void PeriodicApp::setup_askinimage( AWidget *layout )
{
    PODVector<AWidget*> dest;
    layout->SearchWidgetClass( "TBButton", dest );
    for (unsigned ii = 0; ii < dest.Size(); ii++)
        SubscribeToEvent(dest[ii], E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAskinimageEvent ));
}

void PeriodicApp::HandleAskinimageEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    if ( widget == NULL ) return;
    if (eventData[P_TYPE] == UI_EVENT_TYPE_CLICK)
    {
        if (widget->GetId() == "uiskinimagecode" )
        {
            AppLog( "ASkinImage support : " + widget->GetId() + " was pressed " );
            ViewCode ( "Sources/code_askinimage.cpp", widget->GetParent() );
        }
        if (widget->GetId() ==  "uiskinimagelayout" )
        {
            AppLog( "ASkinImage support : " + widget->GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_askinimage.ui.txt", widget->GetParent() );
        }
    }
}

