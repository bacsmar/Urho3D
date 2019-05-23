// AWindow application source code
#include <Urho3D/AUI/AMessageWindow.h>
#include <Urho3D/AUI/AWindow.h>
#include <Urho3D/AUI/AView.h>
#include "PeriodicApp.h"

void PeriodicApp::setup_awindow( AWidget *layout, AView *uiview )
{
    PODVector<AWidget*> dest;
    layout->SearchWidgetClass( "TBButton", dest );
    for (unsigned ii = 0; ii < dest.Size(); ii++)
        SubscribeToEvent(dest[ii], E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAwindowEvent ));
}

void PeriodicApp::HandleAwindowEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    if ( widget == NULL ) return;
    if (eventData[P_TYPE] == UI_EVENT_TYPE_CLICK)
    {
        if (widget->GetId() == "uiwindowcode" )
        {
            AppLog( "AWindow support : " + widget->GetId() + " was pressed " );
            ViewCode ( "Sources/code_awindow.cpp", widget->GetParent() );
        }
        if (widget->GetId() ==  "uiwindowlayout" )
        {
            AppLog( "AWindow support : " + widget->GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_awindow.ui.txt", widget->GetParent() );
        }

        if (widget->GetId() == "windowdemo" )
        {
            AppLog( "AWindow action : " + widget->GetId() + " was pressed " );
            AView *someview = widget->GetView();
            AWindow *window = new AWindow(context_);
            window->SetSettings ( UI_WINDOW_SETTINGS_DEFAULT );
            window->SetText("AWindow demo (a login dialog)");
            window->Load("Scenes/login_dialog.ui.txt");
            window->ResizeToFitContent();
            someview->AddChild(window);
            window->Center();
            AWidget *login = window->GetWidget("login");
            SubscribeToEvent(login, E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAwindowEvent ));
            AWidget *cancel = window->GetWidget("cancel");
            SubscribeToEvent(cancel, E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAwindowEvent ));
        }
        if (widget->GetId() == "login" )
        {
            AppLog( "AWindow action : " + widget->GetId() + " was pressed " );
            AWindow *mywindow = static_cast<AWindow *>(FindTheWindowParent(widget));
            if (mywindow)
                mywindow->Close();
        }
        if (widget->GetId() == "cancel" )
        {
            AppLog( "AWindow action : " + widget->GetId() + " was pressed " );
            AWindow *mywindow = static_cast<AWindow *>(FindTheWindowParent(widget));
            if (mywindow)
                mywindow->Close();
        }
        if (widget->GetId() == "windowdemo1" )
        {
            AppLog( "AWindow action : " + widget->GetId() + " was pressed " );
            AView *someview = widget->GetView();
            AWindow *window = new AWindow(context_);
            window->SetSettings ( UI_WINDOW_SETTINGS_DEFAULT );
            window->SetText("AWindow demo (a table)" );
            window->Load("Scenes/sheet.ui.txt");
            window->ResizeToFitContent();
            someview->AddChild(window);
            window->Center();
        }
        if (widget->GetId() == "windowdemo2" )
        {
            AppLog( "AWindow action : " + widget->GetId() + " was pressed " );
            AView *someview = widget->GetView();
            AWindow *window = new AWindow(context_);
            window->SetAxis(UI_AXIS_X);
            window->SetSettings ( UI_WINDOW_SETTINGS_DEFAULT );
            window->SetText(" ");
            window->Load("Scenes/sheet.ui.txt");
            window->ResizeToFitContent();
            someview->AddChild(window);
            window->Center();
        }
        if (widget->GetId() == "windowdemo3" )
        {
            AppLog( "AWindow action : " + widget->GetId() + " was pressed " );
            AView *someview = widget->GetView();
            AWindow *window = new AWindow(context_);
            window->SetId ("WinCloseOverride" );
            window->SetSettings ( UI_WINDOW_SETTINGS_DEFAULT );
            window->SetText("AWindow with Close Override action" );
            window->Load("Scenes/sheet.ui.txt");
            window->ResizeToFitContent();
            window->SetCloseDelegate(true);
            SubscribeToEvent(window, E_AWIDGETEDITCANCELED, URHO3D_HANDLER(PeriodicApp,HandleCloseOverrideEvent));
            someview->AddChild(window);
            window->Center();
        }
    }
}

void PeriodicApp::HandleCloseOverrideEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace AWidgetEditCanceled;
    AWidget* widget = static_cast<AWidget*>(eventData[P_WIDGET].GetPtr());
    if ( widget == NULL ) return;

    AView *someview = widget->GetView();
    AMessageWindow *mess4 = new AMessageWindow(context_, someview, "mymess4");
    SubscribeToEvent(mess4, E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleCloseYesNoEvent ));
    mess4->Show( "Close Window Request", "Do you really want to close this window?", UI_MESSAGEWINDOW_SETTINGS_YES_NO, 0, 0, 0);
}

void PeriodicApp::HandleCloseYesNoEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    if ( widget == NULL ) return;
    AWindow* mywin = static_cast<AWindow*>(widget->FindWidget("WinCloseOverride"));
    String refid = eventData[P_REFID].GetString();
    if (eventData[P_TYPE] == UI_EVENT_TYPE_CLICK)
    {
        if (refid == "TBMessageWindow.yes" )
        {
            AppLog( "AWindow event : " + refid + " closed the AMessageWindow");
            if (mywin)
                mywin->Close();
        }
        if (refid == "TBMessageWindow.no" )
        {
            AppLog( "AWindow event : " + refid + " closed the AMessageWindow");
            //wait for it ...
        }
    }
}

