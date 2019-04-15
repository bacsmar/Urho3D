// APromptWindow application source code
#include <Urho3D/AUI/AEvents.h>
#include <Urho3D/AUI/APromptWindow.h>
#include "PeriodicApp.h"

void PeriodicApp::setup_apromptwindow( AWidget *layout, AView *uiview )
{
    PODVector<AWidget*> dest;
    layout->SearchWidgetClass( "TBButton", dest );
    for (unsigned ii = 0; ii < dest.Size(); ii++)
        SubscribeToEvent(dest[ii], E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleApromptwindowEvent ));
}

void PeriodicApp::HandlePromptCompleteEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace APromptComplete;

    AppLog( "APromptWindow event : the window " + eventData[P_TITLE].GetString()
            + " file was " + eventData[P_SELECTED].GetString()
            + ", the button pressed was " + eventData[P_REASON].GetString());
}

void PeriodicApp::HandleApromptwindowEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    if ( widget == NULL ) return;
    if (eventData[P_TYPE] == UI_EVENT_TYPE_CLICK)
    {
        if (widget->GetId() == "uipromptwindowcode" )
        {
            AppLog( "APromptWindow support : " + widget->GetId() + " was pressed " );
            ViewCode ( "Sources/code_apromptwindow.cpp", widget->GetParent() );
        }
        if (widget->GetId() ==  "uipromptwindowlayout" )
        {
            AppLog( "APromptWindow support : " + widget->GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_apromptwindow.ui.txt", widget->GetParent() );
        }

        if (widget->GetId() == "stringfinder" )
        {
            AppLog( "APromptWindow action : " + widget->GetId() + " was pressed ");
            AWidget *someview = (AWidget *)widget->GetView();
            APromptWindow *windowp = new  APromptWindow(context_, someview, widget->GetId());
            SubscribeToEvent( windowp, E_APROMPTCOMPLETE, URHO3D_HANDLER(PeriodicApp, HandlePromptCompleteEvent ));
            windowp->Show( "WindowTitle", "Message in window", "preset value", 0, 0, 0);
        }
    }
}

