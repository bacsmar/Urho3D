// ATextureWidget application source code
#include <Urho3D/AUI/ATextureWidget.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/AUI/ALayout.h>
#include <Urho3D/AUI/AButton.h>
#include <Urho3D/Graphics/Texture2D.h>
#include "PeriodicApp.h"

void PeriodicApp::setup_atexturewidget( AWidget *layout )
{
    PODVector<AWidget*> dest;
    layout->SearchWidgetClass( "TBButton", dest );
    for (unsigned ii = 0; ii < dest.Size(); ii++)
        SubscribeToEvent(dest[ii], E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAtexturewidgetEvent ));

    ResourceCache* cache = GetSubsystem<ResourceCache>();
    ATextureWidget* mytexturewidget = new ATextureWidget(context_);
    mytexturewidget->SetId( "ATextureWidgetDemo");
    if ( mytexturewidget )
    {
        Texture2D *mytex = new Texture2D(context_);
        if ( mytex )
        {
            mytex = cache->GetResource<Texture2D>("Textures/planet.jpg");
            mytexturewidget->SetTexture(mytex);
        }
    }
    SubscribeToEvent( mytexturewidget, E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAtexturewidgetEvent ));
    ALayoutParams *lpx = new ALayoutParams(context_);
    lpx->SetWidth (256);
    lpx->SetHeight(256);
    lpx->SetMinWidth(256);
    lpx->SetMinHeight(256);
    lpx->SetMaxWidth (256);
    lpx->SetMaxHeight(256);
    mytexturewidget->SetLayoutParams(lpx);
    AWidget* lower = layout->GetWidget("uitexturewidgetlower");
    AWidget* mysvc = layout->GetWidget("uitwcontainer");
    mysvc->AddChildBefore( mytexturewidget, lower);

    ALayout *lo1 = new ALayout(context_);
    mysvc->AddChildBefore(lo1, lower);

    AButton *b1 = new AButton(context_);
    b1->SetId( "uitexturewidgetch1");
    b1->SetText("Change texture to new build");
    lo1->AddChild(b1);
    SubscribeToEvent( b1, E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAtexturewidgetEvent ));
    AButton *b2 = new AButton(context_);
    b2->SetId( "uitexturewidgetch2");
    b2->SetText("Change texture to colorwheel");
    lo1->AddChild(b2);
    SubscribeToEvent( b2, E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAtexturewidgetEvent ));
    AButton *b3 = new AButton(context_);
    b3->SetId( "uitexturewidgetch3");
    b3->SetText("Change texture to planet");
    lo1->AddChild(b3);
    SubscribeToEvent( b3, E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAtexturewidgetEvent ));

}

void PeriodicApp::HandleAtexturewidgetEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    if ( widget == NULL ) return;
    if (eventData[P_TYPE] == UI_EVENT_TYPE_CLICK)
    {
        if (widget->GetId() == "uitexturewidgetcode" )
        {
            AppLog( "ATextureWidget support : " + widget->GetId() + " was pressed " );
            ViewCode ( "Sources/code_atexturewidget.cpp", widget->GetParent() );
        }
        if (widget->GetId() ==  "uitexturewidgetlayout" )
        {
            AppLog( "ATextureWidget support : " + widget->GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_atexturewidget.ui.txt", widget->GetParent() );
        }

        if (widget->GetId() ==  "uitexturewidgetch1" )
        {
            AppLog( "ATextureWidget support : " + widget->GetId() + " was pressed ");
            ResourceCache* cache = GetSubsystem<ResourceCache>();
            ATextureWidget *tw = static_cast<ATextureWidget*>(widget->FindWidget("ATextureWidgetDemo"));
            tw->SetTexture( cache->GetResource<Texture2D>("Textures/newbuilddetected_header.jpg") );
        }
        if (widget->GetId() ==  "uitexturewidgetch2" )
        {
            AppLog( "ATextureWidget support : " + widget->GetId() + " was pressed ");
            ResourceCache* cache = GetSubsystem<ResourceCache>();
            ATextureWidget *tw = static_cast<ATextureWidget*>(widget->FindWidget("ATextureWidgetDemo"));
            tw->SetTexture( cache->GetResource<Texture2D>("Textures/HSV21.png") );
        }
        if (widget->GetId() ==  "uitexturewidgetch3" )
        {
            AppLog( "ATextureWidget support : " + widget->GetId() + " was pressed ");
            ResourceCache* cache = GetSubsystem<ResourceCache>();
            ATextureWidget *tw = static_cast<ATextureWidget*>(widget->FindWidget("ATextureWidgetDemo"));
            tw->SetTexture( cache->GetResource<Texture2D>("Textures/planet.jpg") );
        }
    }
}

