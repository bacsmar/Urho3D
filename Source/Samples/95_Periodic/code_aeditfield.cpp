// AEditField application source code
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/AUI/AEditField.h>
#include "PeriodicApp.h"

void PeriodicApp::setup_aeditfield( AWidget *layout )
{
    PODVector<AWidget*> dest;
    layout->SearchWidgetClass( "TBButton", dest );
    for (unsigned ii = 0; ii < dest.Size(); ii++)
        SubscribeToEvent(dest[ii], E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAeditfieldEvent ));

    AWidget *ed1 = layout->GetWidget("editfieldsingle");
    if ( ed1)
        SubscribeToEvent(ed1, E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAeditfieldEvent ));
    AWidget *ed2 = layout->GetWidget("editfieldmulti");
    if ( ed2)
        SubscribeToEvent(ed2, E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAeditfieldEvent ));
}

void PeriodicApp::HandleAeditfieldEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    if ( widget == NULL ) return;
    if (eventData[P_TYPE] == UI_EVENT_TYPE_CLICK)
    {
        if (widget->GetId() == "uieditfieldcode" )
        {
            AppLog( "AEditField support : " + widget->GetId() + " was pressed " );
            ViewCode ( "Sources/code_aeditfield.cpp", widget->GetParent() );
        }
        if (widget->GetId() ==  "uieditfieldlayout" )
        {
            AppLog( "AEditField support : " + widget->GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_aeditfield.ui.txt", widget->GetParent() );
        }

        if (widget->GetId() ==  "editfieldadd" )
        {
            AppLog( "AEditField action : " + widget->GetId() + " was pressed ");
            AEditField *ef1 = static_cast<AEditField*>(widget->FindWidget("editfieldmulti"));
            if(ef1)
            {
                ResourceCache* cache = GetSubsystem<ResourceCache>();
                SharedPtr<File> filex = cache->GetFile("Scenes/layout_aeditfield.ui.txt");
                String textx = filex->ReadText();
                filex->Close();
                ef1->SetText(textx);
            }
        }
        if (widget->GetId() ==  "editfieldclr" )
        {
            AppLog( "AEditField action : " + widget->GetId() + " was pressed ");
            AEditField *ef2 = static_cast<AEditField*>(widget->FindWidget("editfieldmulti"));
            if(ef2)
                ef2->SetText("");
        }
    }
    else
    {
        if ( widget->GetId() ==  "editfieldsingle" )
        {
            AEditField *efx = static_cast<AEditField*>(widget);
            AppLog( "AEditField event : " + widget->GetId() + " text = `" + efx->GetText() + "` event type = " + EventReport(eventData[P_TYPE].GetInt()));
        }
        if ( widget->GetId() ==  "editfieldmulti" )
        {
            AEditField *efx = static_cast<AEditField*>(widget);
            AppLog( "AEditField event : " + widget->GetId() + " text = `" + efx->GetText() + "` event type = " + EventReport(eventData[P_TYPE].GetInt()));
        }
    }
}

