// This first example, maintaining tradition, prints a "Hello World" message.
// Furthermore it shows:
//     - Using the Sample utility functions as a base for the application
//     - Adding a Text element to the graphical user interface
//     - Subscribing to and handling of update events

#include "AUI/Scripts/Utilities/Sample.as"

//Button@ startServer;
//Button@ stopServer;
//Button@ refreshServerList;
//Text@ serverList;
AEditField @aserverList;
AWidget @astartButton;
AWidget @astopButton;

const int SERVER_PORT = 54654;

void Start()
{
    // Execute the common startup for samples
    SampleStart();

    // Create "Hello World" Text
    CreateText();

    // Set the mouse mode to use in the sample
    SampleInitMouseMode(MM_FREE);

    // Finally, hook-up this HelloWorld instance to handle update events
    SubscribeToEvents();
}

void CreateText()
{
    /*
    XMLFile@ uiStyle = cache.GetResource("XMLFile", "UI/DefaultStyle.xml");
    // Set style to the UI root so that elements will inherit it
    ui.root.defaultStyle = uiStyle;

    int marginTop = 20;
    CreateLabel("1. Start server", IntVector2(20, marginTop-20));
    startServer = CreateButton("Start server", 160, IntVector2(20, marginTop));
    stopServer = CreateButton("Stop server", 160, IntVector2(20, marginTop));
    stopServer.visible = false;

    // Create client connection related fields
    marginTop += 80;
    CreateLabel("2. Discover LAN servers", IntVector2(20, marginTop-20));
    refreshServerList = CreateButton("Search...", 160, IntVector2(20, marginTop));

    marginTop += 80;
    CreateLabel("Local servers:", IntVector2(20, marginTop - 20));
    serverList = CreateLabel("", IntVector2(20, marginTop));
    */
    
    AUIInit ( "AUI/resources/default_font/vera.ttf", "Vera", 20, "AUI/Scripts/53_layout.ui.txt" );
    AView@ uiview = aui.GetFocusedView(); // get the topmost aui widget
    aserverList = uiview.FindWidget("serverList");
    astartButton = uiview.FindWidget("startButton");
    astartButton.SetState(UI_WIDGET_STATE_NONE, true);
    astopButton = uiview.FindWidget("stopButton");
    astopButton.SetState(UI_WIDGET_STATE_DISABLED, true);

 }

void SubscribeToEvents()
{
    SubscribeToEvent("NetworkHostDiscovered", "HandleNetworkHostDiscovered");

    SubscribeToEvent(astartButton, "WidgetEvent", "HandleStartServer");
    SubscribeToEvent(astopButton, "WidgetEvent", "HandleStopServer"); 
    AView@ uiview = aui.GetFocusedView(); // get the topmost aui widget
    AWidget @asearchButton = uiview.FindWidget("searchButton");
    SubscribeToEvent(asearchButton, "WidgetEvent", "HandleDoNetworkDiscovery");

   // SubscribeToEvent(startServer, "Released", "HandleStartServer");
   // SubscribeToEvent(stopServer, "Released", "HandleStopServer");
   // SubscribeToEvent(refreshServerList, "Released", "HandleDoNetworkDiscovery");
}

/*
Text@ CreateLabel(const String&in text, IntVector2 pos)
{
    // Create log element to view latest logs from the system
    Font@ font = cache.GetResource("Font", "Fonts/Anonymous Pro.ttf");
    Text@ label = ui.root.CreateChild("Text");
    label.SetFont(font, 12);
    label.color = Color(0.0f, 1.0f, 0.0f);
    label.SetPosition(pos.x, pos.y);
    label.text = text;
    return label;
}

Button@ CreateButton(const String&in text, int width, IntVector2 pos)
{
    Font@ font = cache.GetResource("Font", "Fonts/Anonymous Pro.ttf");

    Button@ button = ui.root.CreateChild("Button");
    button.SetStyleAuto();
    button.SetFixedWidth(width);
    button.SetFixedHeight(30);
    button.SetPosition(pos.x, pos.y);

    Text@ buttonText = button.CreateChild("Text");
    buttonText.SetFont(font, 12);
    buttonText.SetAlignment(HA_CENTER, VA_CENTER);
    buttonText.text = text;

    return button;
}
*/

void HandleNetworkHostDiscovered(StringHash eventType, VariantMap& eventData)
{
    log.Info("Server discovered!");
    String text = aserverList.GetText();  //serverList.text;
    VariantMap data = eventData["Beacon"].GetVariantMap();
    text += "\n" + data["Name"].GetString() + "(" + String(data["Players"].GetInt()) + ")" + eventData["Address"].GetString() + ":" + String(eventData["Port"].GetInt());
    aserverList.SetText(text); // serverList.text = text;
}

void HandleStartServer(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) 
        return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK )
    {
        if (network.StartServer(SERVER_PORT))
        {
            VariantMap data;
            data["Name"] = "Test server";
            data["Players"] = 100;
            /// Set data which will be sent to all who requests LAN network discovery
            network.SetDiscoveryBeacon(data);
            astartButton.SetState(UI_WIDGET_STATE_DISABLED, true); // startServer.visible = false;
            astopButton.SetState(UI_WIDGET_STATE_DISABLED, false);  //stopServer.visible = true;
        }
    }
}

void HandleStopServer(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) 
        return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK )
    {
        network.StopServer();
        astartButton.SetState(UI_WIDGET_STATE_DISABLED, false); //startServer.visible = true;
        astopButton.SetState(UI_WIDGET_STATE_DISABLED, true);  //stopServer.visible = false;
    }
}

void HandleDoNetworkDiscovery(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) 
        return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK )
    {
        /// Pass in the port that should be checked
        network.DiscoverHosts(SERVER_PORT);
        aserverList.SetText(""); // serverList.text = "";
    }
}

// Create XML patch instructions for screen joystick layout specific to this sample app
String patchInstructions =
        "<patch>" +
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Hat0']]\">" +
        "        <attribute name=\"Is Visible\" value=\"false\" />" +
        "    </add>" +
        "</patch>";
