// ALayoutParams application source code
#include "PeriodicApp.h"

void PeriodicApp::setup_alayoutparams( AWidget *layout )
{
    PODVector<AWidget*> dest;
    layout->SearchWidgetClass( "TBButton", dest );
    for (unsigned ii = 0; ii < dest.Size(); ii++)
        SubscribeToEvent(dest[ii], E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp,HandleAlayoutparamsEvent  ));
}

void PeriodicApp::HandleAlayoutparamsEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    if ( widget == NULL ) return;
    if (eventData[P_TYPE] == UI_EVENT_TYPE_CLICK)
    {
        if (widget->GetId() == "uilayoutparamscode" )
        {
            AppLog( "ALayoutParams support : " + widget->GetId() + " was pressed " );
            ViewCode ( "Sources/code_alayoutparams.cpp", widget->GetParent() );
        }
        if (widget->GetId() ==  "uilayoutparamslayout" )
        {
            AppLog( "ALayoutParams support : " + widget->GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_alayoutparams.ui.txt", widget->GetParent() );
        }
    }
}

