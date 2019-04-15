// ATabContainer application source code
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/AUI/ATabContainer.h>
#include <Urho3D/AUI/AWindow.h>
#include <Urho3D/AUI/ALayout.h>
#include <Urho3D/AUI/AEditField.h>
#include <Urho3D/AUI/AButton.h>
#include <Urho3D/AUI/AFontDescription.h>
#include "PeriodicApp.h"

void PeriodicApp::setup_atabcontainer( AWidget *layout )
{
    PODVector<AWidget*> dest;
    layout->SearchWidgetClass( "TBButton", dest );
    for (unsigned ii = 0; ii < dest.Size(); ii++)
        SubscribeToEvent(dest[ii], E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAtabcontainerEvent ));

    ATabContainer *tcx = static_cast<ATabContainer*>(layout->GetWidget("ATabContainerDemo"));
    if ( tcx)
    {
        tcx->SetCurrentPage(0);   // fix or it looks like crap
        tcx->SubscribeToEvent( E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAllTabcontainerEvent ));
        // warning - this will route for all ATabContainer instances events into this event handler.
    }
}

void PeriodicApp::HandleAllTabcontainerEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    String refid = eventData[P_REFID].GetString();
    if ( widget == NULL ) return;

    AWidget *demo = widget->FindWidget("ATabContainerDemo");  // find our specific widget
    if ( widget != demo ) return; // if its not ours, bail

    if (eventData[P_TYPE] == UI_EVENT_TYPE_TAB_CHANGED )
    {
        if ( widget->GetId() ==  "ATabContainerDemo" )
        {
            ATabContainer *tcx = static_cast<ATabContainer*>(widget);  // check the focus & stuff, or it gets a little spammy
            if ( tcx && ( tcx->GetState(UI_WIDGET_STATE_FOCUSED) == true ) )
                AppLog( "ATabContainer event : " + widget->GetId() + " UI_EVENT_TYPE_TAB_CHANGED to " + String( tcx->GetCurrentPage() )
                        + " id: " + tcx->GetCurrentPageWidget()->GetId() );
        }
    }
}


void PeriodicApp::HandleAtabcontainerEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    String refid = eventData[P_REFID].GetString();
    if ( widget == NULL ) return;
    if (eventData[P_TYPE] == UI_EVENT_TYPE_CLICK)
    {
        if (widget->GetId() == "uitabcontainercode" )
        {
            AppLog( "ATabContainer support : " + widget->GetId() + " was pressed " );
            ViewCode ( "Sources/code_atabcontainer.cpp", widget->GetParent() );
        }
        if (widget->GetId() ==  "uitabcontainerlayout" )
        {
            AppLog( "ATabContainer support : " + widget->GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_atabcontainer.ui.txt", widget->GetParent() );
        }


        if (widget->GetId() ==  "uitabcontainerremove" )
        {
            AppLog( "ATabContainer action : " + widget->GetId() + " was pressed ");
            ATabContainer *tcx = static_cast<ATabContainer*>(widget->FindWidget("ATabContainerDemo"));
            int current = tcx->GetCurrentPage();
            tcx->DeletePage(current);
        }
        if (widget->GetId() ==  "uitabcontaineradd" )
        {
            AppLog( "ATabContainer action : " + widget->GetId() + " was pressed ");
            ATabContainer *tcx = static_cast<ATabContainer*>(widget->FindWidget("ATabContainerDemo"));
            tcx->AddTabPageFile("New File", "Scenes/sheet.ui.txt" );
        }
        if (widget->GetId() ==  "uitabcontainermake" )
        {
            AppLog( "ATabContainer action : " + widget->GetId() + " was pressed ");
            ResourceCache* cache = GetSubsystem<ResourceCache>();
            ATabContainer *tcx = static_cast<ATabContainer*>(widget->FindWidget("ATabContainerDemo"));
            ALayout *lo = new ALayout(context_);
            lo->SetLayoutConfig ( "YAGAC" );  // YACAC!
            AEditField *myeditfield = new AEditField(context_);
            myeditfield->SetGravity( UI_GRAVITY_ALL);
            myeditfield->SetMultiline(true);
            SharedPtr<File> filex = cache->GetFile("Sources/code_atabcontainer.cpp");
            String textx = filex->ReadText();
            filex->Close();
            myeditfield->SetText(textx);
            AFontDescription *myfont = new AFontDescription(context_); // put in a coder font
            myfont->SetSize(16);
            myfont->SetId("Vera");
            myeditfield->SetFontDescription (myfont);
            lo->AddChild (myeditfield);
            tcx->AddTabPageWidget("New Code", lo);
        }
        if (widget->GetId() ==  "uitabcontainerundock" )
        {
            AppLog( "ATabContainer action : " + widget->GetId() + " was pressed ");
            ATabContainer *tcx = static_cast<ATabContainer*>(widget->FindWidget("ATabContainerDemo"));
            int current = tcx->GetCurrentPage();
            tcx->UndockPage(current);
        }
        if (widget->GetId() ==  "uitabcontainerredock" )
        {
            AppLog( "ATabContainer action : " + widget->GetId() + " was pressed ");
            ATabContainer *tcx = static_cast<ATabContainer*>(widget->FindWidget("ATabContainerDemo"));
            if ( !tcx->DockWindow ( "tab1" ) )
                if ( !tcx->DockWindow ( "tab2" ) )
                    if ( !tcx->DockWindow ( "tab3" ) )
                        if ( !tcx->DockWindow ( "New File" ) )
                            if ( !tcx->DockWindow ( "New Code" ) )
                                AppLog( "ATabContainer action : no more windows to dock.");
        }
    }
}

