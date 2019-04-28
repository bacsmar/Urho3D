// ASelectList application source code
#include <TurboBadger/tb_widgets.h>
#include <Urho3D/AUI/ASelectItem.h>
#include <Urho3D/AUI/ASelectList.h>
#include <Urho3D/AUI/ALayout.h>
#include "PeriodicApp.h"

void PeriodicApp::setup_aselectlist( AWidget *layout )
{
    PODVector<AWidget*> dest;
    layout->SearchWidgetClass( "TBButton", dest );
    for (unsigned ii = 0; ii < dest.Size(); ii++)
        SubscribeToEvent(dest[ii], E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAselectlistEvent ));

    AWidget *slist = layout->GetWidget ("ASelectListDemo");
    if ( slist)
        SubscribeToEvent(slist, E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAselectlistEvent ));
}

void PeriodicApp::HandleAselectlistEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    String refid = eventData[P_REFID].GetString();
    if ( widget == NULL ) return;
    if (eventData[P_TYPE] == UI_EVENT_TYPE_CLICK)
    {
        if (widget->GetId() == "uiselectlistcode" )
        {
            AppLog( "ASelectList support : " + widget->GetId() + " was pressed " );
            ViewCode ( "Sources/code_aselectlist.cpp", widget->GetParent() );
        }
        if (widget->GetId() ==  "uiselectlistlayout" )
        {
            AppLog( "ASelectList support : " + widget->GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_aselectlist.ui.txt", widget->GetParent() );
        }

        if (widget->GetId() ==  "ASelectListDemo" )
        {
            AppLog( "ASelectList event : " + widget->GetId() + " and " + refid + " was selected ");
        }

        if (widget->GetId() ==  "selectlistadd" )
        {
            AppLog( "ASelectList action : " + widget->GetId() + " was pressed ");
            ASelectList* slist = static_cast<ASelectList*>(widget->FindWidget("ASelectListDemo"));
            slist->AddItem(slist->GetNumItems(), "New Entry", "NewEntryX");
        }
        if (widget->GetId() ==  "selectlistdel" )
        {
            AppLog( "ASelectList action : " + widget->GetId() + " was pressed ");
            ASelectList* slist = static_cast<ASelectList*>(widget->FindWidget("ASelectListDemo"));
            int si = slist->GetValue(); // this is the selected index
            slist->DeleteItem(si);
        }
        if (widget->GetId() ==  "selectlistdelall" )
        {
            AppLog( "ASelectList action : " + widget->GetId() + " was pressed ");
            ASelectList* slist = static_cast<ASelectList*>(widget->FindWidget("ASelectListDemo"));
            slist->DeleteAllItems();
        }
        if (widget->GetId() ==  "selectlistnew" )
        {
            AppLog( "ASelectList action : " + widget->GetId() + " was pressed ");
            ASelectList* slist = static_cast<ASelectList*>(widget->FindWidget("ASelectListDemo"));
            ASelectItemSource *sis = new ASelectItemSource(context_);
            sis->AddItem( new ASelectItem( context_, "list 1","list1", "LogoAtomic" ));
            sis->AddItem( new ASelectItem( context_, "list 2","list2", "" ));
            sis->AddItem( new ASelectItem( context_, "list 3","list3", "" ));
            sis->AddItem( new ASelectItem( context_, "list 4","list4", "" ));
            sis->AddItem( new ASelectItem( context_, "list 5","list5", "" ));
            sis->AddItem( new ASelectItem( context_, "list 6","list6", "" ));
            slist->SetSource(sis);
        }
    }
}

