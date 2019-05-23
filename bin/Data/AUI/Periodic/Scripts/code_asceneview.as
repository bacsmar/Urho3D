// ASceneView application source code
// some code from UISceneview2D sample program


void setup_uisceneview( AWidget @layout)
{
    Array<AWidget@> dest = layout.SearchAWidgetClass( "TBButton" ); 
    for (uint ii = 0; ii < dest.length; ii++)  // set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(dest[ii], "WidgetEvent", "HandleUisceneviewEvent" );

    ASceneView @ mysceneview = ASceneView();  // make a scene...view
    mysceneview.SetId( "ASceneViewDemo"); // tag it, in case we want to get it again later
    SubscribeToEvent(mysceneview, "WidgetEvent", "HandleUisceneviewEvent" );

    /*
        Scene @myscene = GetSubsystem<Urho3DPlayer::Player>().LoadScene("Scenes/sceneview.scene");
        DONT DO IT THIS WAY for C++! Make a scene, then LoadXML!
    */

    Scene @myscene = Scene();
    if ( myscene !is null )
    {
        if ( myscene.LoadXML(@(cache.GetFile("Scenes/sceneview.scene"))))
        {
            Node @cameraNode = myscene.GetChild("Camera", true);
            Camera@ mycamera = cameraNode.GetComponent("Camera");
            Node@ planetNode = myscene.GetChild("TheWorld", true);
            if(planetNode !is null) // spin-o-rama, c++ style
            {
                Rotator@ rotator = cast<Rotator>(planetNode.CreateScriptObject(scriptFile, "Rotator"));
                rotator.SetRotationSpeed(Vector3(0.0f, 20.0f, 1.0f));
            }
            mysceneview.SetView(myscene, mycamera);
            mysceneview.SetAutoUpdate(true);
        }
    }

    ALayoutParams @lpx = ALayoutParams();
    lpx.SetWidth (640);
    lpx.SetHeight(320);
    lpx.SetMinWidth(640);
    lpx.SetMinHeight(320);
    lpx.SetMaxWidth (640);
    lpx.SetMaxHeight(320);
    mysceneview.SetLayoutParams(lpx);

    AWidget@ lower = layout.GetWidget("uisceneviewlower");
    AWidget@ mysvc = layout.GetWidget("sceneviewcontainer");
    mysvc.AddChildBefore(mysceneview, lower);

}

void HandleUisceneviewEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        if (widget.GetId() == "uisceneviewcode" )
        {
            AppLog( "ASceneView support : " + widget.GetId() + " was pressed " );
            ViewCode ( "Scripts/code_asceneview.as", widget.GetParent() );
        }
        if (widget.GetId() ==  "uisceneviewlayout" )
        {
            AppLog( "ASceneView support : " + widget.GetId() + " was pressed ");
            ViewCode ( "Scenes/layout_asceneview.ui.txt", widget.GetParent() );
        }
    }
    if ( widget.GetId() ==  "ASceneViewDemo" )
    {
       // AppLog( "ASceneView event : " + widget.GetId() + " got event= "+ EventReport(eventData[P_TYPE].GetInt()) );
        AppLog( "ASceneView event : " + widget.GetId() );
    }
}

