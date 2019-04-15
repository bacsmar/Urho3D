// ASelectItem and ASelectItemSource application source code
#include <TurboBadger/tb_widgets.h>
#include <Urho3D/AUI/ASelectItem.h>
#include <Urho3D/AUI/ASelectList.h>
#include <Urho3D/AUI/ALayout.h>
#include "PeriodicApp.h"

void PeriodicApp::setup_aselectitem( AWidget *layout )
{
    PODVector<AWidget*> dest;
    layout->SearchWidgetClass( "TBButton", dest );
    for (unsigned ii = 0; ii < dest.Size(); ii++)
        SubscribeToEvent(dest[ii], E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAselectitemEvent ));

    ASelectList *mylist = new ASelectList(context_);
    mylist->SetId( "ASelectItemList"); // tag it, in case we want to get it again later
    ALayoutParams *lpx = new ALayoutParams(context_);
    lpx->SetWidth (200);
    lpx->SetHeight(256);
    lpx->SetMinWidth(200);
    lpx->SetMinHeight(256);
    lpx->SetMaxWidth (200);
    lpx->SetMaxHeight(256);
    mylist->SetLayoutParams(lpx);
    AWidget* lower = layout->GetWidget("selectitemlower");
    AWidget* mysvc = layout->GetWidget("selectitemlayout");
    mysvc->AddChildBefore(mylist, lower);
    SubscribeToEvent(mylist, E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAselectitemEvent ));

    ASelectItemSource *sis = new ASelectItemSource(context_);
    sis->AddItem( new ASelectItem( context_, "ASelectItem1", "sitem1" ) );
    sis->AddItem( new ASelectItem( context_, "ASelectItem2", "sitem2" ) );
    sis->AddItem( new ASelectItem( context_, "ASelectItem3", "sitem3", "DuckButton" ) );
    sis->AddItem( new ASelectItem( context_, "ASelectItem4", "sitem4", "LogoAtomic" ) );
    context_->SetGlobalVar( "selectitemptr", sis );  // make a global reference.

    mylist->SetSource(sis); // assign this into the list
}

void PeriodicApp::HandleAselectitemEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    String refid = eventData[P_REFID].GetString();
    if ( widget == NULL ) return;
    if (eventData[P_TYPE] == UI_EVENT_TYPE_CLICK)
    {
        if (widget->GetId() == "uiselectitemcode" )
        {
            AppLog( "ASelectItem support : " + widget->GetId() + " was pressed " );
            ViewCode ( "Sources/code_aselectitem.cpp", widget->GetParent() );
        }
        if (widget->GetId() ==  "uiselectitemlayout" )
        {
            AppLog( "ASelectItem support : " + widget->GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_aselectitem.ui.txt", widget->GetParent() );
        }

        if (widget->GetId() ==  "ASelectItemList" )
        {
            AppLog( "ASelectItem event : " + widget->GetId() + " and " + refid + " was selected ");
        }

        if (widget->GetId() ==  "uisi1" )
        {
            AppLog( "ASelectItem action : " + widget->GetId() + " was pressed ");
            ASelectItemSource *gsis = (ASelectItemSource*)context_->GetGlobalVar("selectitemptr").GetPtr();
            ASelectList* slist = static_cast<ASelectList*>(widget->FindWidget("ASelectItemList"));
            gsis->AddItem( new ASelectItem( context_, "New ASelectItem") );
            slist->SetSource(gsis);
        }
        if (widget->GetId() ==  "uisi2" )
        {
            AppLog( "ASelectItem action : " + widget->GetId() + " was pressed ");
            ASelectItemSource *gsis = (ASelectItemSource*)context_->GetGlobalVar("selectitemptr").GetPtr();
            ASelectList* slist = static_cast<ASelectList*>(widget->FindWidget("ASelectItemList"));
            gsis->AddItem( new ASelectItem( context_,"Newer ASelectItem", "neweritem" ) );
            slist->SetSource(gsis);
        }
        if (widget->GetId() ==  "uisi3" )
        {
            AppLog( "ASelectItem action : " + widget->GetId() + " was pressed ");
            ASelectItemSource *gsis = (ASelectItemSource*)context_->GetGlobalVar("selectitemptr").GetPtr();
            ASelectList* slist = static_cast<ASelectList*>(widget->FindWidget("ASelectItemList"));
            gsis->AddItem( new ASelectItem(context_,  "A Duck", "aduck", "DuckButton" ) );
            slist->SetSource(gsis);
        }
        if (widget->GetId() ==  "uisi4" )
        {
            AppLog( "ASelectItem action : " + widget->GetId() + " was pressed ");
            ASelectItemSource *gsis = (ASelectItemSource*)context_->GetGlobalVar("selectitemptr").GetPtr();
            ASelectList* slist = static_cast<ASelectList*>(widget->FindWidget("ASelectItemList"));
            gsis->AddItem( new ASelectItem(context_, "Atomic!", "atomic", "LogoAtomic" ) );
            slist->SetSource(gsis);
        }
        if (widget->GetId() ==  "uisi5" )
        {
            AppLog( "ASelectItem action : " + widget->GetId() + " was pressed ");
            ASelectItemSource *gsis = (ASelectItemSource*)context_->GetGlobalVar("selectitemptr").GetPtr();
            ASelectList* slist = static_cast<ASelectList*>(widget->FindWidget("ASelectItemList"));
            gsis->Clear();
            slist->SetSource(gsis);
        }
    }
}

