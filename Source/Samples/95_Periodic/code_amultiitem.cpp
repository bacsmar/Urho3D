// ASelectItem and ASelectItemSource application source code
#include <TurboBadger/tb_widgets.h>
#include <Urho3D/AUI/AMultiItem.h>
#include <Urho3D/AUI/ASelectList.h>
#include <Urho3D/AUI/ALayout.h>
#include "PeriodicApp.h"

void PeriodicApp::setup_amultiitem( AWidget *layout )
{
    PODVector<AWidget*> dest;
    layout->SearchWidgetClass( "TBButton", dest );
    for (unsigned ii = 0; ii < dest.Size(); ii++)
        SubscribeToEvent(dest[ii], E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAmultiitemEvent ));

    ASelectList *mylist = new ASelectList(context_);
    mylist->SetId( "AMultiItemList"); // tag it, in case we want to get it again later
    ALayoutParams *lpx = new ALayoutParams(context_);
    lpx->SetWidth(300);
    lpx->SetHeight(256);
    lpx->SetMinWidth(300);
    lpx->SetMinHeight(256);
    lpx->SetMaxWidth (300);
    lpx->SetMaxHeight(256);
    mylist->SetLayoutParams(lpx);
    mylist->SetLayoutParams(lpx);
    AWidget* lower = layout->GetWidget("multiitemlower");
    AWidget* mysvc = layout->GetWidget("multiitemlayout");
    mysvc->AddChildBefore(mylist, lower);
    SubscribeToEvent(mylist, E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAmultiitemEvent ));

    AMultiItemSource *sis = new AMultiItemSource(context_);
    AMultiItem *mi1 = new AMultiItem( context_, "sitem1", "TEXT", "AMultiItem1", 88,0 );
    mi1->AddColumn ( "TEXT", "Col2", 44 );
    mi1->AddColumn ( "TEXT", "Col3", 44 );
    sis->AddItem(mi1);
    AMultiItem *mi2 = new AMultiItem( context_, "sitem2", "TEXT", "AMultiItem2",  88,0  );
    mi2->AddColumn ( "TEXT", "Col4", 44 );
    mi2->AddColumn ( "TEXT", "Col5", 44 );
    sis->AddItem(mi2);
    AMultiItem *mi3 = new AMultiItem( context_, "sitem3", "TEXT", "AMultiItem3",  88,0 );
    mi3->AddColumn ( "TEXT", "Col6", 44 );
    mi3->AddColumn ( "TEXT", "Col7", 44 );
    sis->AddItem(mi3);
    AMultiItem *mi4 = new AMultiItem( context_, "sitem4", "TEXT", "AMultiItem4",  88,0 );
    mi4->AddColumn ( "TEXT", "Col8", 44 );
    mi4->AddColumn ( "TEXT", "Col9", 44 );
    sis->AddItem(mi4);

    context_->SetGlobalVar( "multiitemptr", sis );  // make a global reference.

    mylist->SetSource(sis); // assign this into the list
}

void PeriodicApp::HandleAmultiitemEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    String refid = eventData[P_REFID].GetString();
    if ( widget == NULL ) return;
    if (eventData[P_TYPE] == UI_EVENT_TYPE_CLICK)
    {
        if (widget->GetId() == "uimultiitemcode" )
        {
            AppLog( "AMultiItem support : " + widget->GetId() + " was pressed " );
            ViewCode ( "Sources/code_amultiitem.cpp", widget->GetParent() );
        }
        if (widget->GetId() ==  "uimultiitemlayout" )
        {
            AppLog( "ASelectItem support : " + widget->GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_amultiitem.ui.txt", widget->GetParent() );
        }

        if (widget->GetId() ==  "AMultiItemList" )
        {
            AppLog( "AMultiItemList event : " + widget->GetId() + " and " + refid + " was selected ");
        }

        if (widget->GetId() ==  "uimi1" )
        {
            AppLog( "AMultiItem action : " + widget->GetId() + " was pressed ");
            AMultiItemSource *gsis = (AMultiItemSource*)context_->GetGlobalVar("multiitemptr").GetPtr();
            ASelectList* slist = static_cast<ASelectList*>(widget->FindWidget("AMultiItemList"));
            AMultiItem *mi1 = new AMultiItem( context_, "ADD1", "TEXT", "new MultiItem", 88,0 );
            mi1->AddColumn ( "TEXT", "Col2", 44 );
            mi1->AddColumn ( "TEXT", "Col3", 44 );
            gsis->AddItem(mi1);
            slist->SetSource(gsis);
        }
        if (widget->GetId() ==  "uimi2" )
        {
            AppLog( "AMultiItem action : " + widget->GetId() + " was pressed ");
            AMultiItemSource *gsis = (AMultiItemSource*)context_->GetGlobalVar("multiitemptr").GetPtr();
            ASelectList* slist = static_cast<ASelectList*>(widget->FindWidget("AMultiItemList"));
            AMultiItem *mi2 = new AMultiItem( context_, "ADD2", "TEXT", "Another Item",  88,0  );
            mi2->AddColumn ( "COLOR", "#3333FF", 44 );
            mi2->AddColumn ( "TEXT", "Col5", 44 );
            gsis->AddItem(mi2);
            slist->SetSource(gsis);
        }
        if (widget->GetId() ==  "uimi3" )
        {
            AppLog( "AMultiItem action : " + widget->GetId() + " was pressed ");
            AMultiItemSource *gsis = (AMultiItemSource*)context_->GetGlobalVar("multiitemptr").GetPtr();
            ASelectList* slist = static_cast<ASelectList*>(widget->FindWidget("AMultiItemList"));
            AMultiItem *mi3 = new AMultiItem( context_, "Duck", "ICON", "DuckButton",  88,0 );
            mi3->AddColumn ( "TEXT", "Col6", 44 );
            mi3->AddColumn ( "TEXT", "Col7", 44 );
            gsis->AddItem(mi3);
            slist->SetSource(gsis);
        }
        if (widget->GetId() ==  "uimi4" )
        {
            AppLog( "AMultiItem action : " + widget->GetId() + " was pressed ");
            AMultiItemSource *gsis = (AMultiItemSource*)context_->GetGlobalVar("multiitemptr").GetPtr();
            ASelectList* slist = static_cast<ASelectList*>(widget->FindWidget("AMultiItemList"));
            AMultiItem *mi4 = new AMultiItem( context_, "Atomic", "ICON", "LogoAtomic", 88,0 );
            mi4->AddColumn ( "TEXT", "Col8", 44 );
            mi4->AddColumn ( "TEXT", "Col9", 44 );
            gsis->AddItem(mi4);
            slist->SetSource(gsis);
        }
        if (widget->GetId() ==  "uimi5" )
        {
            AppLog( "AMultiItem action : " + widget->GetId() + " was pressed ");
            AMultiItemSource *gsis = (AMultiItemSource*)context_->GetGlobalVar("multiitemptr").GetPtr();
            ASelectList* slist = static_cast<ASelectList*>(widget->FindWidget("AMultiItemList"));
            gsis->Clear();
            slist->SetSource(gsis);
        }
    }
}

