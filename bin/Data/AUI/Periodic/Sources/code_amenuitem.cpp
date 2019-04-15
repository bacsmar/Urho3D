// AMenuItem and AMenuItemSource application source code
#include <TurboBadger/tb_widgets.h>
#include <Urho3D/AUI/AMenuWindow.h>
#include <Urho3D/AUI/AMenubar.h>
#include "PeriodicApp.h"

void PeriodicApp::setup_amenuitem( AWidget *layout )
{
    PODVector<AWidget*> dest;
    layout->SearchWidgetClass( "TBButton", dest );
    for (unsigned ii = 0; ii < dest.Size(); ii++)
        SubscribeToEvent(dest[ii], E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAmenuitemEvent ));

    AMenuItemSource *mis = new AMenuItemSource(context_);
    mis->AddItem( new AMenuItem( context_,"ASelectItem1", "item1" ) );
    mis->AddItem( new AMenuItem( context_,"ASelectItem2", "item2", "Ctrl+." ) );
    mis->AddItem( new AMenuItem( context_,"ASelectItem3", "item3", "Ctrl+A", "DuckButton" ) );
    mis->AddItem( new AMenuItem( context_,"ASelectItem4", "item4", "Ctrl+O", "LogoAtomic" ) );
    context_->SetGlobalVar( "menuitemptr", mis );
}

void PeriodicApp::HandleAmenuitemEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    String refid = eventData[P_REFID].GetString();
    if ( widget == NULL ) return;
    if (eventData[P_TYPE] == UI_EVENT_TYPE_CLICK)
    {
        if (widget->GetId() == "uimenuitemcode" )
        {
            AppLog( "AMenuItem support : " + widget->GetId() + " was pressed " );
            ViewCode ( "Sources/code_amenuitem.cpp", widget->GetParent() );
        }
        if (widget->GetId() ==  "uimenuitemlayout" )
        {
            AppLog( "AMenuItem support : " + widget->GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_amenuitem.ui.txt", widget->GetParent() );
        }

        if (widget->GetId() ==  "uimenuitempush" )
        {
            AMenuItemSource *gmis = (AMenuItemSource*)context_->GetGlobalVar("menuitemptr").GetPtr();
            AMenuWindow* mymenuwindow = new AMenuWindow( context_, widget, "MenuItemDemo");
            int xx = widget->GetX() + (widget->GetWidth()/2);
            int yy = widget->GetY() + (widget->GetHeight()/2);
            SubscribeToEvent(mymenuwindow, E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAmenuitemEvent ));
            mymenuwindow->Show(gmis, xx, yy);
        }

        if (widget->GetId() ==  "MenuItemDemo" )
        {
            AppLog( "AMenuItem event : " + widget->GetId() + " and " + refid + " was selected ");
        }

        if (widget->GetId() ==  "uimi1" )
        {
            AppLog( "AMenuItem action : " + widget->GetId() + " was pressed ");
            AMenuItemSource *gmis = (AMenuItemSource*)context_->GetGlobalVar("menuitemptr").GetPtr();
            gmis->AddItem( new AMenuItem( context_, "New AMenuItem") );
        }
        if (widget->GetId() ==  "uimi2" )
        {
            AppLog( "AMenuItem action : " + widget->GetId() + " was pressed ");
            AMenuItemSource *gmis = (AMenuItemSource*)context_->GetGlobalVar("menuitemptr").GetPtr();
            gmis->AddItem( new AMenuItem( context_, "Newer AMenuItem", "neweritem" ) );
        }
        if (widget->GetId() ==  "uimi3" )
        {
            AppLog( "AMenuItem action : " + widget->GetId() + " was pressed ");
            AMenuItemSource *gmis = (AMenuItemSource*)context_->GetGlobalVar("menuitemptr").GetPtr();
            gmis->AddItem( new AMenuItem( context_, "A Duck", "aduck", "", "DuckButton" ) );
        }
        if (widget->GetId() ==  "uimi4" )
        {
            AppLog( "AMenuItem action : " + widget->GetId() + " was pressed ");
            AMenuItemSource *gmis = (AMenuItemSource*)context_->GetGlobalVar("menuitemptr").GetPtr();
            gmis->AddItem( new AMenuItem( context_, "Atomic!", "atomic", "", "LogoAtomic" ) );
        }
        if (widget->GetId() ==  "uimi5" )
        {
            AppLog( "AMenuItem action : " + widget->GetId() + " was pressed ");
            AMenuItemSource *gmis = (AMenuItemSource*)context_->GetGlobalVar("menuitemptr").GetPtr();
            gmis->Clear();
        }
    }
}

