// APromptWindow application source code
#include <Urho3D/AUI/AUI.h>
#include <Urho3D/AUI/AEvents.h>
#include <Urho3D/AUI/APromptWindow.h>
#include <Urho3D/AUI/AMessageWindow.h>
#include <Urho3D/AUI/AFinderWindow.h>
#include <Urho3D/AUI/ADimmer.h>
#include "PeriodicApp.h"

void PeriodicApp::setup_adimmer( AWidget *layout )
{
    PODVector<AWidget*> dest;
    layout->SearchWidgetClass( "TBButton", dest );
    for (unsigned ii = 0; ii < dest.Size(); ii++)
        SubscribeToEvent(dest[ii], E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAdimmerEvent ));
}

void PeriodicApp::HandleModalCompleteEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace APromptComplete;

    AppLog( "Modal Selection event : the window " + eventData[P_TITLE].GetString()
            + " selection was " + eventData[P_SELECTED].GetString()
            + ", the button pressed was " + eventData[P_REASON].GetString());

    AUI* aui = GetSubsystem<AUI>();  // manually undim the app
    AWidget *someview = (AWidget *)aui->GetFocusedView();
    AWidget *dimmer = someview->FindWidget("dimmer");
    if ( dimmer )
        dimmer->Remove();

}

void PeriodicApp::HandleAdimmerEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    if ( widget == NULL ) return;
    AWidget *someview = (AWidget *)widget->GetView();

    if (eventData[P_TYPE] == UI_EVENT_TYPE_CLICK)
    {
        if (widget->GetId() == "uidimmercode" )
        {
            AppLog( "ADimmer support : " + widget->GetId() + " was pressed " );
            ViewCode ( "Sources/code_adimmer.cpp", widget->GetParent() );
        }
        if (widget->GetId() ==  "uidimmerlayout" )
        {
            AppLog( "ADimmer support : " + widget->GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_adimmer.ui.txt", widget->GetParent() );
        }

        if (widget->GetId() == "modalfinder" )
        {
            AppLog( "ADimmer action : " + widget->GetId() + " was pressed ");
            APromptWindow *windowp = new APromptWindow(context_, someview, widget->GetId());
            SubscribeToEvent( windowp, E_APROMPTCOMPLETE, URHO3D_HANDLER(PeriodicApp, HandleModalCompleteEvent ));

            ADimmer *dimmer = new ADimmer(context_);  //manually set app dimming
            dimmer->SetId ("dimmer");
            someview->AddChild(dimmer);

            windowp->Show( "Modal Selection", "ADimmer in effect", "preset value", 0, 0, 0);
        }

        if (widget->GetId() ==  "modalok" )
        {
            AppLog( "ADimmer support : " + widget->GetId() + " was pressed ");
            AMessageWindow *mess2 = new AMessageWindow(context_, someview, "mymess2");
            mess2->Show("MessageWindow - OK", "Modal MessageWindow - OK button", UI_MESSAGEWINDOW_SETTINGS_OK, 1, 0, 0);
        }
        if (widget->GetId() ==  "modalokcancel" )
        {
            AppLog( "ADimmer support : " + widget->GetId() + " was pressed ");
            AMessageWindow *mess3 = new AMessageWindow(context_, someview, "mymess3");
            mess3->Show("MessageWindow - OK CANCEL", "Modal MessageWindow - OK CANCEL buttons", UI_MESSAGEWINDOW_SETTINGS_OK_CANCEL, 1, 0, 0);
        }
        if (widget->GetId() ==  "modalyesno" )
        {
            AppLog( "ADimmer support : " + widget->GetId() + " was pressed ");
            AMessageWindow *mess4 = new AMessageWindow(context_, someview, "mymess4");
            mess4->Show( "MessageWindow - YES NO", "this is a MessageWindow - YES NO buttons", UI_MESSAGEWINDOW_SETTINGS_YES_NO, 1, 0, 0);
        }
        if (widget->GetId() == "modalfilefinder" )
        {
            AppLog( "ADimmer action : " + widget->GetId() + " was pressed ");
            AFinderWindow *windowf = new AFinderWindow(context_, someview, widget->GetId());
            windowf->FindFile("Modal Find a File", "", 1, 0, 0);
        }
        if (widget->GetId() ==  "modalfolderfinder" )
        {
            AppLog( "ADimmer action : " + widget->GetId() + " was pressed ");
            AFinderWindow *windowd = new AFinderWindow(context_, someview, widget->GetId() );
            windowd->FindPath("Modal Find a Folder", "", 1, 0, 0);
        }

    }
}

