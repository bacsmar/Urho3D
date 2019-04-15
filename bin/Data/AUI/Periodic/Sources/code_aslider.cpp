// ASlider application source code
#include <Urho3D/AUI/ASlider.h>
#include "PeriodicApp.h"

void PeriodicApp::setup_aslider( AWidget *layout )
{
    PODVector<AWidget*> dest;
    layout->SearchWidgetClass( "TBButton", dest );
    for (unsigned ii = 0; ii < dest.Size(); ii++)
        SubscribeToEvent(dest[ii], E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAsliderEvent ));

    ASlider *slider = static_cast<ASlider*>(layout->GetWidget("sliderdemo"));
    if (slider) // warning - this will route for all ASlider instances events into this event handler.
        slider->SubscribeToEvent( E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAllSliderEvent ));
}

void PeriodicApp::HandleAllSliderEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    if ( widget == NULL ) return;

    AWidget *demo = widget->FindWidget("sliderdemo");  // find our specific widget
    if ( widget != demo ) return; // if its not ours, bail

    if (eventData[P_TYPE] == UI_EVENT_TYPE_CHANGED )
    {
        if (widget->GetId() ==  "sliderdemo" )
        {
            AppLog( "ASlider event : " + widget->GetId() + " changed value to " + String (widget->GetValue()));
        }
    }
}

void PeriodicApp::HandleAsliderEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    if ( widget == NULL ) return;
    if (eventData[P_TYPE] == UI_EVENT_TYPE_CLICK)
    {
        if (widget->GetId() == "uislidercode" )
        {
            AppLog( "ASlider support : " + widget->GetId() + " was pressed " );
            ViewCode ( "Sources/code_aslider.cpp", widget->GetParent() );
        }
        if (widget->GetId() ==  "uisliderlayout" )
        {
            AppLog( "ASlider support : " + widget->GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_aslider.ui.txt", widget->GetParent() );
        }
    }
}

