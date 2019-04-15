// AFinderWindow application source code
#include <Urho3D/AUI/AEvents.h>
#include <Urho3D/AUI/AFinderWindow.h>
#include "PeriodicApp.h"

void PeriodicApp::setup_afinderwindow( AWidget *layout, AView *uiview )
{
    PODVector<AWidget*> dest;
    layout->SearchWidgetClass( "TBButton", dest );
    for (unsigned ii = 0; ii < dest.Size(); ii++)
        SubscribeToEvent(dest[ii], E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAfinderwindowEvent ));
}

void PeriodicApp::HandleFinderCompleteEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace AFinderComplete;
    AppLog( "AFinderWindow event : the window " + eventData[P_TITLE].GetString()
            + " file was " + eventData[P_SELECTED].GetString()
            + ", the button pressed was " + eventData[P_REASON].GetString());
}

void PeriodicApp::HandleAfinderwindowEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    if ( widget == NULL ) return;
    if (eventData[P_TYPE] == UI_EVENT_TYPE_CLICK)
    {
        if (widget->GetId() == "uifinderwindowcode" )
        {
            AppLog( "AFinderWindow support : " + widget->GetId() + " was pressed " );
            ViewCode ( "Sources/code_afinderwindow.cpp", widget->GetParent() );
        }
        if (widget->GetId() ==  "uifinderwindowlayout" )
        {
            AppLog( "AFinderWindow support : " + widget->GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_afinderwindow.ui.txt", widget->GetParent() );
        }

        if (widget->GetId() == "filefinder" )
        {
            AppLog( "AFinderWindow action : " + widget->GetId() + " was pressed ");
            AWidget *someview = (AWidget *)widget->GetView();
            AFinderWindow *windowf = new AFinderWindow(context_, someview, widget->GetId());
            SubscribeToEvent( windowf, E_AFINDERCOMPLETE, URHO3D_HANDLER(PeriodicApp, HandleFinderCompleteEvent ));
            windowf->FindFile("Find a File", "", 0, 0, 0);
        }
        if (widget->GetId() ==  "folderfinder" )
        {
            AppLog( "AFinderWindow action : " + widget->GetId() + " was pressed ");
            AWidget *someview = (AWidget *)widget->GetView();
            AFinderWindow *windowd = new AFinderWindow(context_, someview, widget->GetId() );
            SubscribeToEvent( windowd, E_AFINDERCOMPLETE, URHO3D_HANDLER(PeriodicApp, HandleFinderCompleteEvent ));
            windowd->FindPath("Find a Folder", "", 0, 0, 0);
        }
    }
}

