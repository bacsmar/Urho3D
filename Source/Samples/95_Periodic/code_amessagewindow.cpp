// AMessageWindow application source code
#include <Urho3D/AUI/AMessageWindow.h>
#include "PeriodicApp.h"

void PeriodicApp::setup_amessagewindow( AWidget *layout )
{
    PODVector<AWidget*> dest;
    layout->SearchWidgetClass( "TBButton", dest );
    for (unsigned ii = 0; ii < dest.Size(); ii++)
        SubscribeToEvent(dest[ii], E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAmessagewindowEvent ));
}

void PeriodicApp::HandleAmessagewindowEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    if ( widget == NULL ) return;
    AWidget* mylayout = static_cast<AWidget*>(widget->FindWidget("pageuimessagewindow"));
    String refid = eventData[P_REFID].GetString();
    if (eventData[P_TYPE] == UI_EVENT_TYPE_CLICK)
    {
        if (widget->GetId() == "uimessagewindowcode" )
        {
            AppLog( "AMessageWindow support : " + widget->GetId() + " was pressed " );
            ViewCode ( "Sources/code_amessagewindow.cpp", widget->GetParent() );
        }
        if (widget->GetId() ==  "uimessagewindowlayout" )
        {
            AppLog( "AMessageWindow support : " + widget->GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_amessagewindow.ui.txt", widget->GetParent() );
        }

        if (widget->GetId() ==  "msgnone" )
        {
            AppLog( "AMessageWindow support : " + widget->GetId() + " was pressed ");
            AMessageWindow *mess1 = new AMessageWindow(context_, mylayout, "mymess1");
            mess1->Show("MessageWindow - NONE", "this is a MessageWindow - None button", (UI_MESSAGEWINDOW_SETTINGS)0, 0, 0, 0);
        }
        if (widget->GetId() ==  "msgok" )
        {
            AppLog( "AMessageWindow support : " + widget->GetId() + " was pressed ");
            AMessageWindow *mess2 = new AMessageWindow(context_, mylayout, "mymess2");
            SubscribeToEvent(mess2, E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAmessagewindowEvent ));
            mess2->Show("MessageWindow - OK", "this is a MessageWindow - OK button", UI_MESSAGEWINDOW_SETTINGS_OK, 0, 0, 0);
        }
        if (widget->GetId() ==  "msgkcancel" )
        {
            AppLog( "AMessageWindow support : " + widget->GetId() + " was pressed ");
            AMessageWindow *mess3 = new AMessageWindow(context_, mylayout, "mymess3");
            SubscribeToEvent(mess3, E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAmessagewindowEvent ));
            mess3->Show("MessageWindow - OK CANCEL", "this is a MessageWindow - OK CANCEL buttons", UI_MESSAGEWINDOW_SETTINGS_OK_CANCEL, 0, 0, 0);
        }
        if (widget->GetId() ==  "msgyesno" )
        {
            AppLog( "AMessageWindow support : " + widget->GetId() + " was pressed ");
            AMessageWindow *mess4 = new AMessageWindow(context_, mylayout, "mymess4");
            SubscribeToEvent(mess4, E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAmessagewindowEvent ));
            mess4->Show( "MessageWindow - YES NO", "this is a MessageWindow - YES NO buttons", UI_MESSAGEWINDOW_SETTINGS_YES_NO, 0, 0, 0);
        }

        if (refid ==  "TBMessageWindow.ok" )
        {
            AppLog( "AMessageWindow event : " + refid + " closed the AMessageWindow");
        }
        if (refid ==  "TBMessageWindow.cancel" )
        {
            AppLog( "AMessageWindow event : " + refid + " closed the AMessageWindow");
        }
        if (refid ==  "TBMessageWindow.yes" )
        {
            AppLog( "AMessageWindow event : " + refid + " closed the AMessageWindow");
        }
        if (refid ==  "TBMessageWindow.no" )
        {
            AppLog( "AMessageWindow event : " + refid + " closed the AMessageWindow");
        }
    }
    else
    {
        AppLog( "AMessageWindow event : " + widget->GetId() + " event type = " + EventReport(eventData[P_TYPE].GetInt()));
    }
}

