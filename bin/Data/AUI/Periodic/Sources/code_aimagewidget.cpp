// AImageWidget application source code
#include <Urho3D/AUI/AImageWidget.h>
#include "PeriodicApp.h"

void PeriodicApp::setup_aimagewidget( AWidget *layout )
{
    PODVector<AWidget*> dest;
    layout->SearchWidgetClass( "TBButton", dest );
    for (unsigned ii = 0; ii < dest.Size(); ii++)
        SubscribeToEvent(dest[ii], E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAimagewidgetEvent ));
}

void PeriodicApp::HandleAimagewidgetEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    if ( widget == NULL ) return;
    if (eventData[P_TYPE] == UI_EVENT_TYPE_CLICK)
    {
        if (widget->GetId() == "uiimagewidgetcode" )
        {
            AppLog( "AImageWidget support : " + widget->GetId() + " was pressed " );
            ViewCode ( "Sources/code_aimagewidget.cpp", widget->GetParent() );
        }
        if (widget->GetId() ==  "uiimagewidgetlayout" )
        {
            AppLog( "AImageWidget support : " + widget->GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_aimagewidget.ui.txt", widget->GetParent() );
        }

        if (widget->GetId() ==  "imagecolor" )
        {
            AppLog( "AImageWidget action : " + widget->GetId() + " was pressed ");
            AImageWidget *img1 = static_cast<AImageWidget*>( widget->FindWidget("imagewidgetdemo") );
            img1->SetImage("Textures/HSV21.png");
        }
        if (widget->GetId() ==  "imagenewbuild" )
        {
            AppLog( "AImageWidget action : " + widget->GetId() + " was pressed ");
            AImageWidget *img2 = static_cast<AImageWidget*>( widget->FindWidget("imagewidgetdemo") );
            img2->SetImage("Textures/newbuilddetected_header.jpg");
        }
    }
}

