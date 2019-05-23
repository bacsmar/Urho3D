// AButtonGrid application source code
// some code from UISceneview2D sample program
#include <Urho3D/AUI/AButtonGrid.h>
#include <Urho3D/AUI/ALayout.h>
#include "PeriodicApp.h"

void PeriodicApp::setup_abuttongrid( AWidget *layout)
{
    PODVector<AWidget*> dest;
    layout->SearchWidgetClass( "TBButton", dest );
    for (unsigned ii = 0; ii < dest.Size(); ii++)
        SubscribeToEvent(dest[ii], E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAbuttongridEvent ));

    AButtonGrid * mybuttongrid = new AButtonGrid(context_, 6, 4);  // make a mess
    mybuttongrid->SetId( "AButtonGridDemo"); // tag it, in case we want to get it again later
 
    // fill the buttongrid, feel the joy
    for ( unsigned row = 0; row<mybuttongrid->GetNumRows(); row++)
        for ( unsigned col = 0; col<mybuttongrid->GetNumColumns(); col++)
        {
            mybuttongrid->SetGridText (row, col, mybuttongrid->GetGridId(row, col));
            AWidget* bx = mybuttongrid->GetGridWidget( row, col );
            SubscribeToEvent(bx, E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAbuttongridEvent ));
        }

    ALayoutParams *lpx = new ALayoutParams(context_);
    lpx->SetWidth (320);
    lpx->SetHeight(320);
    lpx->SetMinWidth(320);
    lpx->SetMinHeight(320);
    lpx->SetMaxWidth (320);
    lpx->SetMaxHeight(320);
    mybuttongrid->SetLayoutParams(lpx);

    AWidget* lower = layout->GetWidget("uibuttongridlower");
    AWidget* mysvc = layout->GetWidget("buttongridcontainer");
    mysvc->AddChildBefore(mybuttongrid, lower);

}

void PeriodicApp::HandleAbuttongridEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    if ( widget == NULL ) return;
    if (eventData[P_TYPE] == UI_EVENT_TYPE_CLICK)
    {
        if (widget->GetId() == "uibuttongridcode" )
        {
            AppLog( "AButtonGrid support : " + widget->GetId() + " was pressed " );
            ViewCode ( "Sources/code_abuttongrid.cpp", widget->GetParent() );
        }
        else if (widget->GetId() ==  "uibuttongridlayout" )
        {
            AppLog( "AButtonGrid support : " + widget->GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_abuttongrid.ui.txt", widget->GetParent() );
        }
        else
        {
           AppLog( "AButtonGrid action grid button : " + widget->GetId() + " was pressed ");
        }
    }
    if ( widget->GetId() ==  "AButtonGridDemo" )
    {
        AppLog( "AButtonGrid event : " + widget->GetId() + " got event= "+ EventReport(eventData[P_TYPE].GetInt()) );
    }
}

