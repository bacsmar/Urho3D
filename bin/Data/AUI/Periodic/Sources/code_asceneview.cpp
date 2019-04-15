// ASceneView application source code
// some code from UISceneview2D sample program
#include <Urho3D/AUI/ASceneView.h>
#include <Urho3D/AUI/ALayout.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Resource/ResourceCache.h>
#include "PeriodicApp.h"
#include "Spinner.h"

void PeriodicApp::setup_asceneview( AWidget *layout)
{
    PODVector<AWidget*> dest;
    layout->SearchWidgetClass( "TBButton", dest );
    for (unsigned ii = 0; ii < dest.Size(); ii++)
        SubscribeToEvent(dest[ii], E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAsceneviewEvent ));

    ASceneView * mysceneview = new ASceneView(context_);  // make a scene...view
    mysceneview->SetId( "ASceneViewDemo"); // tag it, in case we want to get it again later
    SubscribeToEvent(mysceneview, E_WIDGETEVENT, URHO3D_HANDLER(PeriodicApp, HandleAsceneviewEvent ));

    /*
        Scene *myscene = GetSubsystem<Urho3DPlayer::Player>()->LoadScene("Scenes/sceneview.scene");
    	DONT DO IT THIS WAY for C++! Make a scene, then LoadXML!
    */

    ResourceCache* cache = GetSubsystem<ResourceCache>();
    Scene *myscene = new Scene(context_);
    if ( myscene )
    {
        if ( myscene->LoadXML(*(cache->GetFile("Scenes/sceneview.scene"))))
        {
            Node *cameraNode = myscene->GetChild("Camera", true);
            Camera* mycamera = cameraNode->GetComponent<Camera>();
            Node* planetNode = myscene->GetChild("TheWorld", true);
            if(planetNode) // spin-o-rama, c++ style
            {
                Rotator* rotator = planetNode->CreateComponent<Rotator>();
                rotator->SetRotationSpeed(Vector3(0.0f, 20.0f, 1.0f));
            }
            mysceneview->SetView(myscene, mycamera);
            mysceneview->SetAutoUpdate(true);
        }
    }

    ALayoutParams *lpx = new ALayoutParams(context_);
    lpx->SetWidth (640);
    lpx->SetHeight(320);
    lpx->SetMinWidth(640);
    lpx->SetMinHeight(320);
    lpx->SetMaxWidth (640);
    lpx->SetMaxHeight(320);
    mysceneview->SetLayoutParams(lpx);

    AWidget* lower = layout->GetWidget("uisceneviewlower");
    AWidget* mysvc = layout->GetWidget("sceneviewcontainer");
    mysvc->AddChildBefore(mysceneview, lower);

}

void PeriodicApp::HandleAsceneviewEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace WidgetEvent;
    AWidget* widget = static_cast<AWidget*>(eventData[P_TARGET].GetPtr());
    if ( widget == NULL ) return;
    if (eventData[P_TYPE] == UI_EVENT_TYPE_CLICK)
    {
        if (widget->GetId() == "uisceneviewcode" )
        {
            AppLog( "ASceneView support : " + widget->GetId() + " was pressed " );
            ViewCode ( "Sources/code_asceneview.cpp", widget->GetParent() );
        }
        if (widget->GetId() ==  "uisceneviewlayout" )
        {
            AppLog( "ASceneView support : " + widget->GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_asceneview.ui.txt", widget->GetParent() );
        }
    }
    if ( widget->GetId() ==  "ASceneViewDemo" )
    {
        AppLog( "ASceneView event : " + widget->GetId() + " got event= "+ EventReport(eventData[P_TYPE].GetInt()) );
    }
}

