// AInlineSelect application source code
#include <Urho3D/AUI/AInlineSelect.h>
#include <Urho3D/AUI/ASlider.h>
#include "PeriodicApp.h"

void PeriodicApp::setup_ainlineselect( AWidget *layout )
{
    PODVector<AWidget*> dest;
    layout->SearchWidgetClass( "TBButton", dest );
    for (unsigned ii = 0; ii < dest.Size(); ii++)
        SubscribeToEvent(dest[ii], E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAinlineselectEvent ));

    ASlider *steps = static_cast<ASlider*>(layout->GetWidget("ilsstep"));
    if(steps)
        SubscribeToEvent(steps, E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAinlineselectEvent ));

    AInlineSelect *ils = static_cast<AInlineSelect*>(layout->GetWidget("inlineselectdemo"));
    if (ils)
        SubscribeToEvent( ils, E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAinlineselectEvent ));
}

void PeriodicApp::HandleAinlineselectEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    if ( widget == NULL ) return;
    if (eventData[P_TYPE] == UI_EVENT_TYPE_CLICK)
    {
        if (widget->GetId() == "uiinlineselectcode" )
        {
            AppLog( "AInlineSelect support : " + widget->GetId() + " was pressed " );
            ViewCode ( "Sources/code_ainlineselect.cpp", widget->GetParent() );
        }
        if (widget->GetId() ==  "uiinlineselectlayout" )
        {
            AppLog( "AInlineSelect support : " + widget->GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_ainlineselect.ui.txt", widget->GetParent() );
        }
    }
    else if (eventData[P_TYPE] == UI_EVENT_TYPE_CHANGED )
    {
        if (widget->GetId() == "inlineselectdemo" )
        {
            AInlineSelect *ils = static_cast<AInlineSelect*>(widget);
            if(ils)
            {
                AppLog( "AInlineSelect event : " + widget->GetId() + " changed value to " + String (ils->GetValue()) );
            }
        }

        if (widget->GetId() == "ilsstep" )
        {
            ASlider *steps = static_cast<ASlider*>(widget);
            if(steps)
            {
                AInlineSelect *ils = static_cast<AInlineSelect*>(widget->FindWidget("inlineselectdemo"));
                if(ils)
                {
                    ils->SetStepSize (steps->GetValue());
                }
                AppLog( "AInlineSelect event : " + widget->GetId() + " step size changed to " + String (steps->GetValue()));
            }
        }
    }
}

