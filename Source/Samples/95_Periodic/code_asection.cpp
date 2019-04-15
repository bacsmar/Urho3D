// ASection application source code
#include <Urho3D/AUI/ASection.h>
#include "PeriodicApp.h"

void PeriodicApp::setup_asection( AWidget *layout )
{
    PODVector<AWidget*> dest;
    layout->SearchWidgetClass( "TBButton", dest );
    for (unsigned ii = 0; ii < dest.Size(); ii++)
        SubscribeToEvent(dest[ii], E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAsectionEvent ));

    AWidget *sec1 = layout->GetWidget("ASectionDemo");
    if (sec1)
        SubscribeToEvent( sec1, E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAsectionEvent ));
    AWidget *sec2 = layout->GetWidget("ASection2Demo");
    if (sec2)
        SubscribeToEvent( sec2, E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAsectionEvent ));
}

void PeriodicApp::HandleAsectionEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    if ( widget == NULL ) return;

    if (eventData[P_TYPE] == UI_EVENT_TYPE_CLICK)
    {
        if (widget->GetId() == "uisectioncode" )
        {
            AppLog( "ASection support : " + widget->GetId() + " was pressed " );
            ViewCode ( "Sources/code_asection.cpp", widget->GetParent() );
        }
        if (widget->GetId() ==  "uisectionlayout" )
        {
            AppLog( "ASection support : " + widget->GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_asection.ui.txt", widget->GetParent() );
        }
    }
    if (eventData[P_TYPE] == UI_EVENT_TYPE_CHANGED )
    {
        AWidget *demo1 = widget->FindWidget("ASectionDemo"); // event comes in on child widget!
        if ( demo1->IsAncestorOf(widget) )
            AppLog( "ASection event : " +  demo1->GetId() + " changed to value = " + String(demo1->GetValue()));

        AWidget *demo2 = widget->FindWidget("ASection2Demo");
        if ( demo2->IsAncestorOf(widget)  )
            AppLog( "ASection event : " +  demo2->GetId() + " changed to value = " + String(demo2->GetValue()));
    }
}

