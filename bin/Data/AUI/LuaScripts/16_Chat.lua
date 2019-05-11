-- Chat example
-- This sample demonstrates:
--     - Starting up a network server or connecting to it
--     - Implementing simple chat functionality with network messages

require "AUI/LuaScripts/Utilities/Sample"

-- Identifier for the chat network messages
local MSG_CHAT = 153
-- UDP port we will use
local CHAT_SERVER_PORT = 2345

local chatHistory = {}

local asendButton = nil
local aconnectButton = nil
local adisconnectButton = nil
local astartServerButton = nil
local achatHistoryText = nil
local atextEdit = nil

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
    SetLogoVisible(false) -- We need the full rendering window

    local uiStyle = cache:GetResource("XMLFile", "UI/DefaultStyle.xml")
    -- Set style to the UI root so that elements will inherit it
    ui.root.defaultStyle = uiStyle

    AUIInit ( "AUI/resources/default_font/vera.ttf", "Vera", 20, "AUI/Scenes/16_layout.ui.txt" )
    local uiview = aui:GetFocusedView()
    asendButton = uiview:FindWidget("sendButton")
    aconnectButton = uiview:FindWidget("connectButton")
    adisconnectButton = uiview:FindWidget("disconnectButton")
    astartServerButton = uiview:FindWidget("startServerButton")
    achatHistoryText = uiview:FindWidget("chatHistoryText")
    atextEdit = uiview:FindWidget("LineEdit")

    UpdateButtons()

    local size = 16
    for i = 1, size do
        table.insert(chatHistory, "")
    end

    -- No viewports or scene is defined. However, the default zone's fog color controls the fill color
    renderer.defaultZone.fogColor = Color(0.0, 0.0, 0.1)
end

function SubscribeToEvents()
    -- Subscribe to UI element events
    SubscribeToEvent( atextEdit, "WidgetEvent", "HandleSend" )
    SubscribeToEvent( asendButton, "WidgetEvent", "HandleSend" )
    SubscribeToEvent( aconnectButton, "WidgetEvent", "HandleConnect" )
    SubscribeToEvent( adisconnectButton, "WidgetEvent", "HandleDisconnect" )
    SubscribeToEvent( astartServerButton, "WidgetEvent", "HandleStartServer" )

    -- Subscribe to log messages so that we can pipe them to the chat window
    SubscribeToEvent("LogMessage", "HandleLogMessage")

    -- Subscribe to network events
    SubscribeToEvent("NetworkMessage", "HandleNetworkMessage")
    SubscribeToEvent("ServerConnected", "HandleConnectionStatus")
    SubscribeToEvent("ServerDisconnected", "HandleConnectionStatus")
    SubscribeToEvent("ConnectFailed", "HandleConnectionStatus")
end


function ShowChatText(row)
    table.remove(chatHistory, 1)
    table.insert(chatHistory, row)

    -- Concatenate all the rows in history
    local allRows = ""
    for i, r in ipairs(chatHistory) do
        allRows = allRows .. r .. "\n"
    end
    achatHistoryText:SetText(allRows)
end

function UpdateButtons()
    local serverConnection = network.serverConnection
    local serverRunning = network.serverRunning

    -- Show and hide buttons so that eg. Connect and Disconnect are never shown at the same time

    if (serverConnection == nil) and (not serverRunning) then
        aconnectButton:SetState(UI_WIDGET_STATE_DISABLED, false)
        astartServerButton:SetState(UI_WIDGET_STATE_DISABLED, false)
    else 
        aconnectButton:SetState(UI_WIDGET_STATE_DISABLED, true)
        astartServerButton:SetState(UI_WIDGET_STATE_DISABLED, true)
    end
    
    if (serverConnection ~= nil) or serverRunning then
        adisconnectButton:SetState(UI_WIDGET_STATE_DISABLED, false)
    else 
        adisconnectButton:SetState(UI_WIDGET_STATE_DISABLED, true)
    end

    if serverConnection ~= nil then 
        asendButton:SetState(UI_WIDGET_STATE_DISABLED, false)
    else 
        asendButton:SetState(UI_WIDGET_STATE_DISABLED, true)
    end
end

function HandleLogMessage(eventType, eventData)
    ShowChatText(eventData["Message"]:GetString())
end

function HandleSend(eventType, eventData)
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
 		return
	end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then

    	local text = atextEdit:GetText()
    	if text == "" then
        	return -- Do not send an empty message
    	end

    	local serverConnection = network.serverConnection
    	if serverConnection ~= nil then
        	-- A VectorBuffer object is convenient for constructing a message to send
        	local msg = VectorBuffer()
        	msg:WriteString(text)
        	-- Send the chat message as in-order and reliable
        	serverConnection:SendMessage(MSG_CHAT, true, true, msg)
        	-- Empty the text edit after sending
        	atextEdit:SetText("")
		end
    end
end

function HandleConnect(eventType, eventData)
    local address = atextEdit:GetText() --:Trimmed()
    if address == "" then
        address = "localhost" -- Use localhost to connect if nothing else specified
    end

    -- Empty the text edit after reading the address to connect to
    atextEdit:SetText("")

    -- Connect to server, do not specify a client scene as we are not using scene replication, just messages.
    -- At connect time we could also send identity parameters (such as username) in a VariantMap, but in this
    -- case we skip it for simplicity
    network:Connect(address, CHAT_SERVER_PORT, nil)

    UpdateButtons()
end

function HandleDisconnect(eventType, eventData)
    local serverConnection = network.serverConnection
    -- If we were connected to server, disconnect
    if serverConnection ~= nil then
        serverConnection:Disconnect()
    -- Or if we were running a server, stop it
    else
        if network.serverRunning then
            network:StopServer()
        end
    end

    UpdateButtons()
end

function HandleStartServer(eventType, eventData)
    network:StartServer(CHAT_SERVER_PORT)

    UpdateButtons()
end

function HandleNetworkMessage(eventType, eventData)
    local msgID = eventData["MessageID"]:GetInt()
    if msgID == MSG_CHAT then
        local msg = eventData["Data"]:GetBuffer()
        local text = msg:ReadString()
        -- If we are the server, prepend the sender's IP address and port and echo to everyone
        -- If we are a client, just display the message
        if network.serverRunning then
            local sender = eventData["Connection"]:GetPtr("Connection")
            text = sender:ToString() .. " " .. text
            local sendMsg = VectorBuffer()
            sendMsg:WriteString(text)
            -- Broadcast as in-order and reliable
            network:BroadcastMessage(MSG_CHAT, true, true, sendMsg)
        end
        ShowChatText(text)
    end
end

function HandleConnectionStatus(eventType, eventData)
    UpdateButtons()
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
