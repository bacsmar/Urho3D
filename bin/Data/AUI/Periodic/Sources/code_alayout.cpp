// ALayout application source code
#include <Urho3D/AUI/AView.h>
#include <Urho3D/AUI/ALayout.h>
#include <Urho3D/AUI/ACheckBox.h>
#include <Urho3D/AUI/ARadioButton.h>
#include <Urho3D/AUI/ATextField.h>
#include <Urho3D/AUI/AButton.h>
#include <Urho3D/AUI/AEditField.h>
#include <Urho3D/AUI/ATabContainer.h>
#include <Urho3D/AUI/AWindow.h>
#include "PeriodicApp.h"

void PeriodicApp::setup_alayout( AWidget *layout, AView *uiview )
{
    PODVector<AWidget*> dest;
    layout->SearchWidgetClass( "TBButton", dest );
    for (unsigned ii = 0; ii < dest.Size(); ii++)
        SubscribeToEvent(dest[ii], E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAlayoutEvent ));

    ALayout *myc = static_cast<ALayout *>(layout->GetWidget("uilayoutcontainer")); // get the container layout

    AButton *tf0 = new AButton(context_);  // the layout-o-matic spawner
    tf0->SetText( "LAYOUT-O-MATIC");
    tf0->SetId( "go_layout_config");
    ALayout *lo0 = new ALayout(context_);
    lo0->SetId( "target_layout");
    lo0->SetLayoutConfig ( "-----" );
    lo0->Load("Scenes/simp_button.ui.txt");
    lo0->AddChildBefore(tf0, lo0->GetFirstChild() );
    myc->AddChild(lo0);  // drop it in
    SubscribeToEvent(tf0, E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAlayoutEvent ));

    ATextField *tf1 = new ATextField(context_);
    tf1->SetText( "layout config XACAC");
    ALayout *lo1 = new ALayout(context_);
    lo1->SetLayoutConfig ( "XACAC" );
    lo1->Load("Scenes/simp_button.ui.txt");
    lo1->AddChildBefore(tf1, lo1->GetFirstChild() );
    myc->AddChild(lo1);

    ATextField *tf2 = new ATextField(context_);
    tf2->SetText( "layout config XGCAC");
    ALayout *lo2 = new ALayout(context_);
    lo2->SetLayoutConfig ( "XGCAC" );
    lo2->Load("Scenes/simp_button.ui.txt");
    lo2->AddChildBefore(tf2, lo2->GetFirstChild() );
    myc->AddChild(lo2);

    ATextField *tf3 = new ATextField(context_);
    tf3->SetText( "layout config XPCAC");
    ALayout *lo3 = new ALayout(context_);
    lo3->SetLayoutConfig ( "XPCAC" );
    lo3->Load("Scenes/simp_button.ui.txt");
    lo3->AddChildBefore(tf3, lo3->GetFirstChild() );
    myc->AddChild(lo3);

    ATextField *tf4 = new ATextField(context_);
    tf4->SetText( "layout config XACGC");
    ALayout *lo4 = new ALayout(context_);
    lo4->SetLayoutConfig ( "XACGC" );
    lo4->Load("Scenes/simp_button.ui.txt");
    lo4->AddChildBefore(tf4, lo4->GetFirstChild() );
    myc->AddChild(lo4);

    ATextField *tf5 = new ATextField(context_);
    tf5->SetText( "layout config XGRGC");
    ALayout *lo5 = new ALayout(context_);
    lo5->SetLayoutConfig ( "XGRGC" );
    lo5->Load("Scenes/simp_button.ui.txt");
    lo5->AddChildBefore(tf5, lo5->GetFirstChild() );
    myc->AddChild(lo5);

    ATextField *tf6 = new ATextField(context_);
    tf6->SetText( "layout config XPLGC");
    ALayout *lo6 = new ALayout(context_);
    lo6->SetLayoutConfig ( "XPLGC" );
    lo6->Load("Scenes/simp_button.ui.txt");
    lo6->AddChildBefore(tf6, lo6->GetFirstChild() );
    myc->AddChild(lo6);

    ATextField *tf7 = new ATextField(context_);
    tf7->SetText( "layout config XACPC");
    ALayout *lo7 = new ALayout(context_);
    lo7->SetLayoutConfig ( "XACPC" );
    lo7->Load("Scenes/simp_button.ui.txt");
    lo7->AddChildBefore(tf7, lo7->GetFirstChild() );
    myc->AddChild(lo7);

    ATextField *tf8 = new ATextField(context_);
    tf8->SetText( "layout config XGLPL");
    ALayout *lo8 = new ALayout(context_);
    lo8->SetLayoutConfig ( "XGLPL" );
    lo8->Load("Scenes/simp_button.ui.txt");
    lo8->AddChildBefore(tf8, lo8->GetFirstChild() );
    myc->AddChild(lo8);

    ATextField *tf9 = new ATextField(context_);
    tf9->SetText( "layout config XPCPR");
    ALayout *lo9 = new ALayout(context_);
    lo9->SetLayoutConfig ( "XPCPR" );
    lo9->Load("Scenes/simp_button.ui.txt");
    lo9->AddChildBefore(tf9, lo9->GetFirstChild() );
    myc->AddChild(lo9);

    context_->SetGlobalVar("layoutomaticstr", "XGCPC" ); // LAYOUT-O-MATIC string, cheating, using a globalvar

}

void PeriodicApp::HandleAlayoutEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    if ( widget == NULL ) return;
    if (eventData[P_TYPE] == UI_EVENT_TYPE_CLICK)
    {
        if (widget->GetId() == "go_layout_config" ) // its LAYOUT-O-MATIC time.
        {
            AppLog( "ALayout action : " + widget->GetId() + " was pressed, its LAYOUT-O-MATIC time");
            AView *someview = widget->GetView();
            AWindow* window = new AWindow(context_);
            window->SetSettings ( UI_WINDOW_SETTINGS_DEFAULT );
            window->SetText( "LAYOUT-O-MATIC(tm)");
            window->Load("Scenes/view_layout.ui.txt");
            window->ResizeToFitContent();
            someview->AddChild(window);

            AWidget *okbutt = window->GetWidget("ok");
            SubscribeToEvent(okbutt, E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAlayoutEvent ));

            PODVector<AWidget*> lox;
            window->SearchWidgetClass( "TBRadioButton", lox );
            for (unsigned ii = 0; ii < lox.Size(); ii++)
                SubscribeToEvent(lox[ii], E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAlayoutEvent ));
        }
        if (widget->GetId() ==  "ok" )
        {
            AWindow *mywindow = static_cast<AWindow *>(FindTheWindowParent(widget));
            if (mywindow)
                mywindow->Close();
        }
        if (widget->GetId() ==  "set_ax" )
        {
            ALayout *targetl = static_cast<ALayout *>(widget->FindWidget("target_layout")); // who to operate on.
            ARadioButton *setax = static_cast< ARadioButton*>(widget); // who we are
            if (targetl && setax)
            {
                if ( setax->GetValue() == 1)
                {
                    String current = context_->GetGlobalVar("layoutomaticstr").GetString();
                    current.Replace (0, 1, "X");
                    targetl->SetLayoutConfig(current);
                    context_->SetGlobalVar("layoutomaticstr", current );
                }
            }
        }
        if (widget->GetId() ==  "set_ay" )
        {
            ALayout *targetl = static_cast<ALayout *>(widget->FindWidget("target_layout")); // who to operate on.
            ARadioButton *setay = static_cast< ARadioButton*>(widget); // who we are
            if (targetl && setay)
            {
                if ( setay->GetValue() == 1)
                {
                    String current = context_->GetGlobalVar("layoutomaticstr").GetString();
                    current.Replace (0, 1, "Y");
                    targetl->SetLayoutConfig(current );
                    context_->SetGlobalVar("layoutomaticstr", current );
                }
            }
        }

        if (widget->GetId() ==  "set_sza" )
        {
            ALayout *targetl = static_cast<ALayout *>(widget->FindWidget("target_layout")); // who to operate on.
            ARadioButton *setay = static_cast< ARadioButton*>(widget); // who we are
            if (targetl && setay)
            {
                if ( setay->GetValue() == 1)
                {
                    String current = context_->GetGlobalVar("layoutomaticstr").GetString();
                    current.Replace (1, 1, "A");
                    targetl->SetLayoutConfig(current );
                    context_->SetGlobalVar("layoutomaticstr", current );
                }
            }
        }
        if (widget->GetId() ==  "set_szg" )
        {
            ALayout *targetl = static_cast<ALayout *>(widget->FindWidget("target_layout")); // who to operate on.
            ARadioButton *setay = static_cast< ARadioButton*>(widget); // who we are
            if (targetl && setay)
            {
                if ( setay->GetValue() == 1)
                {
                    String current = context_->GetGlobalVar("layoutomaticstr").GetString();
                    current.Replace (1, 1, "G");
                    targetl->SetLayoutConfig(current );
                    context_->SetGlobalVar("layoutomaticstr", current );
                }
            }
        }
        if (widget->GetId() ==  "set_szp" )
        {
            ALayout *targetl = static_cast<ALayout *>(widget->FindWidget("target_layout")); // who to operate on.
            ARadioButton *setay = static_cast< ARadioButton*>(widget); // who we are
            if (targetl && setay)
            {
                if ( setay->GetValue() == 1)
                {
                    String current = context_->GetGlobalVar("layoutomaticstr").GetString();
                    current.Replace (1, 1, "P");
                    targetl->SetLayoutConfig(current );
                    context_->SetGlobalVar("layoutomaticstr", current );
                }
            }
        }


        if (widget->GetId() ==  "set_posc" )
        {
            ALayout *targetl = static_cast<ALayout *>(widget->FindWidget("target_layout")); // who to operate on.
            ARadioButton *setay = static_cast< ARadioButton*>(widget); // who we are
            if (targetl && setay)
            {
                if ( setay->GetValue() == 1)
                {
                    String current = context_->GetGlobalVar("layoutomaticstr").GetString();
                    current.Replace (2, 1, "C");
                    targetl->SetLayoutConfig(current );
                    context_->SetGlobalVar("layoutomaticstr", current );
                }
            }
        }
        if (widget->GetId() ==  "set_posg" )
        {
            ALayout *targetl = static_cast<ALayout *>(widget->FindWidget("target_layout")); // who to operate on.
            ARadioButton *setay = static_cast< ARadioButton*>(widget); // who we are
            if (targetl && setay)
            {
                if ( setay->GetValue() == 1)
                {
                    String current = context_->GetGlobalVar("layoutomaticstr").GetString();
                    current.Replace (2, 1, "G");
                    targetl->SetLayoutConfig(current );
                    context_->SetGlobalVar("layoutomaticstr", current );
                }
            }
        }
        if (widget->GetId() ==  "set_posl" )
        {
            ALayout *targetl = static_cast<ALayout *>(widget->FindWidget("target_layout")); // who to operate on.
            ARadioButton *setay = static_cast< ARadioButton*>(widget); // who we are
            if (targetl && setay)
            {
                if ( setay->GetValue() == 1)
                {
                    String current = context_->GetGlobalVar("layoutomaticstr").GetString();
                    current.Replace (2, 1, "L");
                    targetl->SetLayoutConfig(current );
                    context_->SetGlobalVar("layoutomaticstr", current );
                }
            }
        }
        if (widget->GetId() ==  "set_posr" )
        {
            ALayout *targetl = static_cast<ALayout *>(widget->FindWidget("target_layout")); // who to operate on.
            ARadioButton *setay = static_cast< ARadioButton*>(widget); // who we are
            if (targetl && setay)
            {
                if ( setay->GetValue() == 1)
                {
                    String current = context_->GetGlobalVar("layoutomaticstr").GetString();
                    current.Replace (2, 1, "R");
                    targetl->SetLayoutConfig(current );
                    context_->SetGlobalVar("layoutomaticstr", current );
                }
            }
        }

        if (widget->GetId() ==  "set_dista" )
        {
            ALayout *targetl = static_cast<ALayout *>(widget->FindWidget("target_layout")); // who to operate on.
            ARadioButton *setay = static_cast< ARadioButton*>(widget); // who we are
            if (targetl && setay)
            {
                if ( setay->GetValue() == 1)
                {
                    String current = context_->GetGlobalVar("layoutomaticstr").GetString();
                    current.Replace (3, 1, "A");
                    targetl->SetLayoutConfig(current );
                    context_->SetGlobalVar("layoutomaticstr", current );
                }
            }
        }
        if (widget->GetId() ==  "set_distg" )
        {
            ALayout *targetl = static_cast<ALayout *>(widget->FindWidget("target_layout")); // who to operate on.
            ARadioButton *setay = static_cast< ARadioButton*>(widget); // who we are
            if (targetl && setay)
            {
                if ( setay->GetValue() == 1)
                {
                    String current = context_->GetGlobalVar("layoutomaticstr").GetString();
                    current.Replace (3, 1, "G");
                    targetl->SetLayoutConfig(current );
                    context_->SetGlobalVar("layoutomaticstr", current );
                }
            }
        }
        if (widget->GetId() ==  "set_distp" )
        {
            ALayout *targetl = static_cast<ALayout *>(widget->FindWidget("target_layout")); // who to operate on.
            ARadioButton *setay = static_cast< ARadioButton*>(widget); // who we are
            if (targetl && setay)
            {
                if ( setay->GetValue() == 1)
                {
                    String current = context_->GetGlobalVar("layoutomaticstr").GetString();
                    current.Replace (3, 1, "P");
                    targetl->SetLayoutConfig(current );
                    context_->SetGlobalVar("layoutomaticstr", current );
                }
            }
        }

        if (widget->GetId() ==  "set_dpc" )
        {
            ALayout *targetl = static_cast<ALayout *>(widget->FindWidget("target_layout")); // who to operate on.
            ARadioButton *setay = static_cast< ARadioButton*>(widget); // who we are
            if (targetl && setay)
            {
                if ( setay->GetValue() == 1)
                {
                    String current = context_->GetGlobalVar("layoutomaticstr").GetString();
                    current.Replace (4, 1, "C");
                    targetl->SetLayoutConfig(current );
                    context_->SetGlobalVar("layoutomaticstr", current );
                }
            }
        }
        if (widget->GetId() ==  "set_dpl" )
        {
            ALayout *targetl = static_cast<ALayout *>(widget->FindWidget("target_layout")); // who to operate on.
            ARadioButton *setay = static_cast< ARadioButton*>(widget); // who we are
            if (targetl && setay)
            {
                if ( setay->GetValue() == 1)
                {
                    String current = context_->GetGlobalVar("layoutomaticstr").GetString();
                    current.Replace (4, 1, "L");
                    targetl->SetLayoutConfig(current );
                    context_->SetGlobalVar("layoutomaticstr", current );
                }
            }
        }
        if (widget->GetId() ==  "set_dpr" )
        {
            ALayout *targetl = static_cast<ALayout *>(widget->FindWidget("target_layout")); // who to operate on.
            ARadioButton *setay = static_cast< ARadioButton*>(widget); // who we are
            if (targetl && setay)
            {
                if ( setay->GetValue() == 1)
                {
                    String current = context_->GetGlobalVar("layoutomaticstr").GetString();
                    current.Replace (4, 1, "R");
                    targetl->SetLayoutConfig(current );
                    context_->SetGlobalVar("layoutomaticstr", current );
                }
            }
        }
    }
}

