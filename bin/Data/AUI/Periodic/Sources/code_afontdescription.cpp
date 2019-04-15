// UIFontdescription application source code
#include <Urho3D/AUI/ASlider.h>
#include <Urho3D/AUI/AFontDescription.h>
#include <Urho3D/AUI/ATextField.h>
#include "PeriodicApp.h"

void PeriodicApp::setup_afontdescription( AWidget *layout )
{
    PODVector<AWidget*> dest;
    layout->SearchWidgetClass( "TBButton", dest );
    for (unsigned ii = 0; ii < dest.Size(); ii++)
        SubscribeToEvent(dest[ii], E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAfontdescriptionEvent ));

    ASlider *steps = static_cast<ASlider*>(layout->GetWidget("fontstep"));
    if(steps)
        SubscribeToEvent(steps, E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAfontdescriptionEvent ));
}

void PeriodicApp::HandleAfontdescriptionEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    if ( widget == NULL ) return;
    if (eventData[P_TYPE] == UI_EVENT_TYPE_CLICK)
    {
        if (widget->GetId() == "uifontdescriptioncode" )
        {
            AppLog( "UIFontdescription support : " + widget->GetId() + " was pressed " );
            ViewCode ( "Sources/code_afontdescription.cpp", widget->GetParent() );
        }
        if (widget->GetId() ==  "uifontdescriptionlayout" )
        {
            AppLog( "UIFontdescription support : " + widget->GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_afontdescription.ui.txt", widget->GetParent() );
        }
    }
    else if (eventData[P_TYPE] == UI_EVENT_TYPE_CHANGED )
    {
        if ( widget->GetId() ==  "fontstep" )
        {
            ASlider *uis = static_cast<ASlider*>(widget);
            if (uis)
            {
                ATextField *mytext = static_cast<ATextField*>(widget->FindWidget("changetext"));
                AFontDescription *myfont = new AFontDescription(context_);
                myfont->SetSize(int(uis->GetValue()));
                myfont->SetId("Vera");
                mytext->SetFontDescription (myfont);
                mytext->SetText ( "Size " + String (int (uis->GetValue())));
                AppLog( "UIFontdescription action : " + widget->GetId() + " step size changed to " + String (uis->GetValue()));
            }
        }
    }
}

