// AColorWheel application source code
#include <Urho3D/AUI/AColorWheel.h>
#include "PeriodicApp.h"

void PeriodicApp::setup_acolorwheel( AWidget *layout )
{
    PODVector<AWidget*> dest;
    layout->SearchWidgetClass( "TBButton", dest );
    for (unsigned ii = 0; ii < dest.Size(); ii++)
        SubscribeToEvent(dest[ii], E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAcolorwheelEvent ));

    AWidget *cwx = layout->GetWidget("colorwheeldemo");
    if (cwx)
        SubscribeToEvent(cwx, E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAcolorwheelEvent ));
}

void PeriodicApp::HandleAcolorwheelEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    if ( widget == NULL ) return;
    if (eventData[P_TYPE] == UI_EVENT_TYPE_CLICK)
    {
        if (widget->GetId() ==  "uicolorwheelcode" )
        {
            AppLog( "AColorWheel support : " + widget->GetId() + " was pressed " );
            ViewCode ( "Sources/code_acolorwheel.cpp", widget->GetParent() );
        }
        if (widget->GetId() ==  "uicolorwheellayout" )
        {
            AppLog( "AColorWheel support : " + widget->GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_acolorwheel.ui.txt", widget->GetParent() );
        }
    }
    else if (eventData[P_TYPE] == UI_EVENT_TYPE_CHANGED )
    {
        if (widget->GetId() ==  "colorwheeldemo" )
        {
            AColorWheel *cwx = static_cast<AColorWheel*>(widget); // collect click color info
            if (cwx)
            {
                AppLog( "AColorWheel event : " + widget->GetId() + " hue = " + String(cwx->GetHue()) + " saturation = " + String(cwx->GetSaturation()) );
            }
        }
    }
}

