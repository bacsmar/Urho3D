-- Chat example
-- This sample demonstrates:
--     - Starting up a network server or connecting to it
--     - Implementing simple chat functionality with network messages

require "AUI/LuaScripts/Utilities/Sample"

local asaveButton = nil
local aconnectButton = nil
local astartServerButton = nil
local alogHistoryText = nil
local anatServerAddress = nil
local anatServerPort = nil
local aserverGuid = nil
local aguid = nil

local logHistory = {}

-- Local server port
local SERVER_PORT = 54654

function Start()
    -- Execute the common startup for samples
    SampleStart()

    -- Enable OS cursor
    input.mouseVisible = true

    -- Create the user interface
    CreateUI()

    -- Set the mouse mode to use in the sample
    SampleInitMouseMode(MM_FREE)

    -- Subscribe to UI and network events
    SubscribeToEvents()
end

function CreateUI()

    SetLogoVisible(true) -- We need the full rendering window

    local uiStyle = cache:GetResource("XMLFile", "UI/DefaultStyle.xml")
    -- Set style to the UI root so that elements will inherit it
    ui.root.defaultStyle = uiStyle

    AUIInit ( "AUI/resources/default_font/vera.ttf", "Vera", 20, "AUI/Scenes/52_layout.ui.txt" )
    local uiview = aui:GetFocusedView()
    anatServerAddress = uiview:FindWidget("addrEdit")
    anatServerPort = uiview:FindWidget("portEdit")
    aserverGuid = uiview:FindWidget("rguidEdit")
    aguid = uiview:FindWidget("sguidEdit")
    alogHistoryText = uiview:FindWidget("historyText")

    local size = 16
    for i = 1, size do
        table.insert(logHistory, "")
    end

    ShowLogMessage("Ready.");

    -- No viewports or scene is defined. However, the default zone's fog color controls the fill color
    renderer.defaultZone.fogColor = Color(0.0, 0.0, 0.1)
end

function SubscribeToEvents()
    SubscribeToEvent("ServerConnected", "HandleServerConnected");
    SubscribeToEvent("ServerDisconnected", "HandleServerDisconnected");
    SubscribeToEvent("ConnectFailed", "HandleConnectFailed");

    -- NAT server connection related events
    SubscribeToEvent("NetworkNatMasterConnectionFailed", "HandleNatConnectionFailed");
    SubscribeToEvent("NetworkNatMasterConnectionSucceeded", "HandleNatConnectionSucceeded");

    -- NAT punchtrough request events
    SubscribeToEvent("NetworkNatPunchtroughSucceeded", "HandleNatPunchtroughSucceeded");
    SubscribeToEvent("NetworkNatPunchtroughFailed", "HandleNatPunchtroughFailed");

    SubscribeToEvent("ClientConnected", "HandleClientConnected");
    SubscribeToEvent("ClientDisconnected", "HandleClientDisconnected");

    -- Subscribe to UI element events
    local uiview = aui:GetFocusedView()
    asaveButton = uiview:FindWidget("saveButton");
    SubscribeToEvent(asaveButton, "WidgetEvent", "HandleSaveNatSettings")
    aconnectButton = uiview:FindWidget("connectButton")
    SubscribeToEvent(aconnectButton, "WidgetEvent", "HandleConnect")
    astartServerButton = uiview:FindWidget("startButton")
    SubscribeToEvent(astartServerButton, "WidgetEvent", "HandleStartServer")
end

function ShowLogMessage(row)
    table.remove(logHistory, 1)
    table.insert(logHistory, row)

    -- Concatenate all the rows in history
    local allRows = ""
    for i, r in ipairs(logHistory) do
        allRows = allRows .. r .. "\n"
    end
    alogHistoryText:SetText(allRows)
end


function HandleLogMessage(eventType, eventData)
    ShowChatText(eventData["Message"]:GetString())
end

function HandleSaveNatSettings(eventType, eventData)
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
        return
    end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        local address = anatServerAddress:GetText()
        local port = anatServerPort:GetText()
        -- Save NAT server configuration
        network:SetNATServerInfo(address, port);
        ShowLogMessage("Saving NAT settings: " .. address .. ":" .. port);
    end
end

function HandleServerConnected(eventType, eventData)
end

function HandleServerConnected(eventType, eventData)
    ShowLogMessage("Client: Server connected!");
end

function HandleServerDisconnected(eventType, eventData)
    ShowLogMessage("Client: Server disconnected!");
end

function HandleConnectFailed(eventType, eventData)
    ShowLogMessage("Client: Connection failed!");
end

function HandleStartServer(eventType, eventData)
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
        return
    end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        network:StartServer(SERVER_PORT)
        ShowLogMessage("Server: Server started on port: " .. SERVER_PORT)

        -- Connect to the NAT server
        network:StartNATClient()
        ShowLogMessage("Server: Starting NAT client for server...")

        -- Output our assigned GUID which others will use to connect to our server
        aguid.SetText(network:GetGUID())
    end
end

function HandleConnect(eventType, eventData)
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
        return
    end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        local userData = VariantMap()
        userData["Name"] = "Urho3D"

        -- Attempt connecting to server using custom GUID, Scene = null as a second parameter and user identity is passed as third parameter
        network:AttemptNATPunchtrough(aserverGuid:GetText(), null, userData)
        ShowLogMessage("Client: Attempting NAT punchtrough to guid: " + aserverGuid:GetText())
    end
end

function HandleNatConnectionFailed(eventType, eventData)
    ShowLogMessage("Connection to NAT master server failed!");
end

function HandleNatConnectionSucceeded(eventType, eventData)
    ShowLogMessage("Connection to NAT master server succeeded!");   
end

function HandleNatPunchtroughSucceeded(eventType, eventData)
    ShowLogMessage("NAT punchtrough succeeded!");
end

function HandleNatPunchtroughFailed(eventType, eventData)
    ShowLogMessage("NAT punchtrough failed!");
end

function HandleClientConnected(eventType, eventData)
    ShowLogMessage("Server: Client connected!");
end

function HandleClientDisconnected(eventType, eventData)
    ShowLogMessage("Server: Client disconnected!");   
end

-- Create XML patch instructions for screen joystick layout specific to this sample app
function GetScreenJoystickPatchString()
    return
        "<patch>" ..
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button2']]\">" ..
        "        <attribute name=\"Is Visible\" value=\"false\" />" ..
        "    </add>" ..
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Hat0']]\">" ..
        "        <attribute name=\"Is Visible\" value=\"false\" />" ..
        "    </add>" ..
        "</patch>"
end
