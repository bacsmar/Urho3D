// AMenuWindow application source code
#include <TurboBadger/tb_widgets.h>
#include <Urho3D/AUI/AMenuWindow.h>
#include <Urho3D/AUI/AMenubar.h>
#include "PeriodicApp.h"

void PeriodicApp::setup_amenuwindow( AWidget *layout )
{
    PODVector<AWidget*> dest;
    layout->SearchWidgetClass( "TBButton", dest );
    for (unsigned ii = 0; ii < dest.Size(); ii++)
        SubscribeToEvent(dest[ii], E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAmenuwindowEvent ));
}

void PeriodicApp::HandleAmenuwindowEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    String refid = eventData[P_REFID].GetString();
    if ( widget == NULL) return;
    if (eventData[P_TYPE] == UI_EVENT_TYPE_CLICK)
    {
        if (widget->GetId() == "uimenuwindowcode" )
        {
            AppLog( "AMenuWindow support : " + widget->GetId() + " was pressed " );
            ViewCode ( "Sources/code_amenuwindow.cpp", widget->GetParent() );
        }
        if (widget->GetId() ==  "uimenuwindowlayout" )
        {
            AppLog( "AMenuWindow support : " + widget->GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_amenuwindow.ui.txt", widget->GetParent() );
        }

        if (widget->GetId() ==  "uimenuwindowpush" )
        {
            AppLog( "AMenuWindow action : " + widget->GetId() + " was pressed " );
            AMenuWindow* mymenuwindow = new AMenuWindow( context_, widget, "MenuWindowDemo");
            AMenuItemSource *mis = new AMenuItemSource(context_);
            mis->AddItem( new AMenuItem( context_,"ASelectItem1", "item1" ) );
            mis->AddItem( new AMenuItem( context_,"ASelectItem2", "item2", "Ctrl+C" ) );
            mis->AddItem( new AMenuItem( context_,"ASelectItem3", "item3", "Ctrl+A", "DuckButton" ) );
            mis->AddItem( new AMenuItem( context_,"ASelectItem4", "item4", "Ctrl+O", "LogoAtomic" ) );
            int xx = widget->GetX() + (widget->GetWidth()/2);
            int yy = widget->GetY() + (widget->GetHeight()/2);
            SubscribeToEvent(mymenuwindow, E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAmenuwindowEvent ));
            mymenuwindow->Show(mis, xx, yy);
        }

        if (widget->GetId() ==  "MenuWindowDemo" )
        {
            AppLog( "AMenuWindow event : " + widget->GetId() + " and " + refid + " was selected ");
        }
    }
    else
    {
        if (widget->GetId() ==  "MenuWindowDemo" )
        {
            AppLog( "AMenuWindow event : " + widget->GetId() +  " refid=" + refid + " event type=" + EventReport(eventData[P_TYPE].GetInt()));
        }
    }
}

