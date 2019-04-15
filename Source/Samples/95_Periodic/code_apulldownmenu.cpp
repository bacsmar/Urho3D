// APulldownMenu application source code
#include <Urho3D/AUI/APulldownMenu.h>
#include "PeriodicApp.h"

void PeriodicApp::setup_apulldownmenu( AWidget *layout )
{
    unsigned ii = 0;
    PODVector<AWidget*> dest;
    layout->SearchWidgetClass( "TBButton", dest );
    for ( ii = 0; ii < dest.Size(); ii++)
        SubscribeToEvent(dest[ii], E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleApulldownmenuEvent ));
    layout->SearchWidgetClass( "TBPulldownMenu", dest );
    for ( ii = 0;  ii < dest.Size(); ii++)
        SubscribeToEvent(dest[ii], E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleApulldownmenuEvent ));
}

void PeriodicApp::HandleApulldownmenuEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    if ( widget == NULL ) return;
    if (eventData[P_TYPE] == UI_EVENT_TYPE_CLICK)
    {
        if (widget->GetId() == "uipulldownmenucode" )
        {
            AppLog( "APulldownMenu support : " + widget->GetId() + " was pressed " );
            ViewCode ( "Sources/code_apulldownmenu.cpp", widget->GetParent() );
        }
        if (widget->GetId() ==  "uipulldownmenulayout" )
        {
            AppLog( "APulldownMenu support : " + widget->GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_apulldownmenu.ui.txt", widget->GetParent() );
        }
    }
    else if (eventData[P_TYPE] == UI_EVENT_TYPE_CHANGED )
    {
        if (widget->GetId() ==  "FileMenu" )
        {
            APulldownMenu *pdm = static_cast<APulldownMenu*>(widget);
            if ( pdm)
                AppLog( "APulldownMenu event : " + widget->GetId() + " selected entry = " + String( pdm->GetSelectedId()) );
        }
        if (widget->GetId() ==  "EditMenu" )
        {
            APulldownMenu *pdm = static_cast<APulldownMenu*>(widget);
            if ( pdm)
                AppLog( "APulldownMenu event : " + widget->GetId() + " selected entry = " + String( pdm->GetSelectedId()) );
        }
        if (widget->GetId() ==  "ViewMenu" )
        {
            APulldownMenu *pdm = static_cast<APulldownMenu*>(widget);
            if ( pdm)
                AppLog( "APulldownMenu event : " + widget->GetId() + " selected entry = " + String( pdm->GetSelectedId()) );
        }
        if (widget->GetId() ==  "HelpMenu" )
        {
            APulldownMenu *pdm = static_cast<APulldownMenu*>(widget);
            if ( pdm)
                AppLog( "APulldownMenu event : " + widget->GetId() + " selected entry = " + String( pdm->GetSelectedId()) );
        }
    }
}

