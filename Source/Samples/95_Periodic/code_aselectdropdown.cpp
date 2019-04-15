// ASelectDropdown application source code
#include "PeriodicApp.h"

void PeriodicApp::setup_aselectdropdown( AWidget *layout )
{
    PODVector<AWidget*> dest;
    layout->SearchWidgetClass( "TBButton", dest );
    for (unsigned ii = 0; ii < dest.Size(); ii++)
        SubscribeToEvent(dest[ii], E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAselectdropdownEvent ));

    AWidget *demo = layout->GetWidget("selectdropdowndemo");
    if ( demo) // warning - this will route for all ASelectDropdown instances events into this event handler.
        demo->SubscribeToEvent(E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAllSelectdropdownEvent ));
}

void PeriodicApp::HandleAllSelectdropdownEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    if ( widget == NULL ) return;

    AWidget *demo = widget->FindWidget("selectdropdowndemo");  // find our specific widget
    if ( widget != demo ) return; // if its not ours, bail

    if (eventData[P_TYPE] == UI_EVENT_TYPE_CHANGED )
    {
        if (widget->GetId() ==  "selectdropdowndemo" )
        {
            AppLog( "ASelectDropdown event : " + widget->GetId() + " changed value to " + widget->GetText());
        }
    }
}

void PeriodicApp::HandleAselectdropdownEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    if ( widget == NULL ) return;
    if (eventData[P_TYPE] == UI_EVENT_TYPE_CLICK)
    {
        if (widget->GetId() == "uiselectdropdowncode" )
        {
            AppLog( "ASelectDropdown support : " + widget->GetId() + " was pressed " );
            ViewCode ( "Sources/code_aselectdropdown.cpp", widget->GetParent() );
        }
        if (widget->GetId() ==  "uiselectdropdownlayout" )
        {
            AppLog( "ASelectDropdown support : " + widget->GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_aselectdropdown.ui.txt", widget->GetParent() );
        }

    }
}

