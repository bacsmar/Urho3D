// AListView application source code
// some code from UISceneview2D sample program
#include <TurboBadger/tb_widgets.h>
#include <Urho3D/AUI/AUI.h>
#include <Urho3D/AUI/AListView.h>
#include <Urho3D/AUI/ALayout.h>
#include "PeriodicApp.h"

int wcount = 0;

void PrintPretty( AListView *alv, tb::TBWidget *me, unsigned recenthandle )
{
 	wcount++;

	String wname = "Widget[" + String(wcount) + "]" + String(me->GetClassName()) + " " + me->GetText().CStr();

	String iconx = ""; // make it look prettier
	if ( String(me->GetClassName()) == "TBButton" ) iconx = "ButtonIcon";
	if ( String(me->GetClassName()) == "TBLayout" ) iconx = "LayoutIcon";
	if ( String(me->GetClassName()) == "TBTextField" ) iconx = "TextFieldIcon";

	unsigned nxt = alv->AddChildItem(recenthandle, wname, iconx, "widget"+String((unsigned int)me->GetID()));

    int num = me->numChildren();
    for (int ii = 0; ii < num; ii++)
    {
        tb::TBWidget *child = me->GetChildFromIndex(ii);
		PrintPretty( alv, child, nxt );
    }
}



void PeriodicApp::setup_alistview( AWidget *layout)
{
    PODVector<AWidget*> dest;
    layout->SearchWidgetClass( "TBButton", dest );
    for (unsigned ii = 0; ii < dest.Size(); ii++)
        SubscribeToEvent(dest[ii], E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAlistviewEvent ));

    AListView *mylistview = new AListView(context_);  // make a scene...view
    mylistview->SetId( "AListViewDemo"); // tag it, in case we want to get it again later
    SubscribeToEvent(mylistview, E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAlistviewEvent ));

	// fill the listview, feel the joy
 	unsigned roothandle = mylistview->AddRootItem("Widgets", "LogoAtomic", "root_");

	AUI* aui = GetSubsystem<AUI>();  // manually undim the app
	AWidget *someview = (AWidget *)aui->GetFocusedView();

	PrintPretty( mylistview, someview->GetInternalWidget(), roothandle ); 

    ALayoutParams *lpx = new ALayoutParams(context_);
    lpx->SetWidth (600);
    lpx->SetHeight(320);
    lpx->SetMinWidth(600);
    lpx->SetMinHeight(320);
    lpx->SetMaxWidth (600);
    lpx->SetMaxHeight(320);
    mylistview->SetLayoutParams(lpx);

    AWidget* lower = layout->GetWidget("uilistviewlower");
    AWidget* mysvc = layout->GetWidget("listviewcontainer");
    mysvc->AddChildBefore(mylistview, lower);

}

void PeriodicApp::HandleAlistviewEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    if ( widget == NULL ) return;
    if (eventData[P_TYPE] == UI_EVENT_TYPE_CLICK)
    {
        if (widget->GetId() == "uilistviewcode" )
        {
            AppLog( "AListView support : " + widget->GetId() + " was pressed " );
            ViewCode ( "Sources/code_alistview.cpp", widget->GetParent() );
        }
        if (widget->GetId() ==  "uilistviewlayout" )
        {
            AppLog( "AListView support : " + widget->GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_alistview.ui.txt", widget->GetParent() );
        }
    }
    if ( widget->GetId() ==  "AListViewDemo" )
    {
        AppLog( "AListView event : " + widget->GetId() + " got event= "+ EventReport(eventData[P_TYPE].GetInt()) );
    }
}

