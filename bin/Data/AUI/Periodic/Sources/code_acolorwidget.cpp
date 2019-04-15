// AColorWidget application source code
#include <Urho3D/AUI/AColorWidget.h>
#include "PeriodicApp.h"

void PeriodicApp::setup_acolorwidget( AWidget *layout )
{
    PODVector<AWidget*> dest;
    layout->SearchWidgetClass( "TBButton", dest );
    for (unsigned ii = 0; ii < dest.Size(); ii++)
        SubscribeToEvent(dest[ii], E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAcolorwidgetEvent ));
}

void PeriodicApp::HandleAcolorwidgetEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    if ( widget == NULL ) return;
    if (eventData[P_TYPE] == UI_EVENT_TYPE_CLICK)
    {
        if (widget->GetId() == "uicolorwidgetcode" )
        {
            AppLog( "AColorWidget support : " + widget->GetId() + " was pressed " );
            ViewCode ( "Sources/code_acolorwidget.cpp", widget->GetParent() );
        }
        if (widget->GetId() == "uicolorwidgetlayout" )
        {
            AppLog( "AColorWidget support : " + widget->GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_acolorwidget.ui.txt", widget->GetParent() );
        }

        if (widget->GetId() == "uicolorwidgetred" )
        {
            AppLog( "AColorWidget action : " + widget->GetId() + " was pressed ");
            AColorWidget *clw = static_cast<AColorWidget*>(widget->FindWidget("colorwidgetdemo"));
            if (clw)
                clw->SetColorString("#FF1111");
        }
        if (widget->GetId() == "uicolorwidgetgreen" )
        {
            AppLog( "AColorWidget action : " + widget->GetId() + " was pressed ");
            AColorWidget *clw = static_cast<AColorWidget*>(widget->FindWidget("colorwidgetdemo"));
            if (clw)
                clw->SetColorString("#11FF11");
        }
        if (widget->GetId() == "uicolorwidgetblue" )
        {
            AppLog( "AColorWidget action : " + widget->GetId() + " was pressed ");
            AColorWidget *clw = static_cast<AColorWidget*>(widget->FindWidget("colorwidgetdemo"));
            if (clw)
                clw->SetColorString("#1111FF");
        }
    }
}

