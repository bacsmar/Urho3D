// AScrollBar application source code
#include <Urho3D/AUI/AScrollBar.h>
#include "PeriodicApp.h"

void PeriodicApp::setup_ascrollbar( AWidget *layout )
{
    PODVector<AWidget*> dest;
    layout->SearchWidgetClass( "TBButton", dest );
    for (unsigned ii = 0; ii < dest.Size(); ii++)
        SubscribeToEvent(dest[ii], E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAscrollbarEvent ));

    AWidget *sbx = layout->GetWidget("scrollbardemo");
    if (sbx)  // warning - this will route for all scrollbar instances events into this event handler.
        sbx->SubscribeToEvent( E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAllScrollcontainerEvent ));
}

void PeriodicApp::HandleAllScrollcontainerEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    if ( widget == NULL ) return;

    AWidget *sbx = widget->FindWidget("scrollbardemo");  // find our scrollbar
    if ( widget != sbx ) return; // if its not ours, bail

    if (eventData[P_TYPE] == UI_EVENT_TYPE_CHANGED )
    {
        if (widget->GetId() ==  "scrollbardemo" )
        {
            AppLog( "AScrollBar action : " + widget->GetId() + " changed value to " + String (widget->GetValue()));
        }
    }
}

void PeriodicApp::HandleAscrollbarEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    if ( widget == NULL ) return;

    if (eventData[P_TYPE] == UI_EVENT_TYPE_CLICK)
    {
        if (widget->GetId() == "uiscrollbarcode" )
        {
            AppLog( "AScrollBar support : " + widget->GetId() + " was pressed " );
            ViewCode ( "Sources/code_ascrollbar.cpp", widget->GetParent() );
        }
        if (widget->GetId() ==  "uiscrollbarlayout" )
        {
            AppLog( "AScrollBar support : " + widget->GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_ascrollbar.ui.txt", widget->GetParent() );
        }
    }
}

