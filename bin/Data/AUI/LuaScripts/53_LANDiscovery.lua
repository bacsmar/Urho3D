-- Chat example
-- This sample demonstrates:
--     - Starting up a network server or connecting to it
--     - Implementing simple chat functionality with network messages

require "AUI/LuaScripts/Utilities/Sample"

local aserverList = nil
local astartButton = nil
local astopButton = nil

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

    AUIInit ( "AUI/resources/default_font/vera.ttf", "Vera", 20, "AUI/Scenes/53_layout.ui.txt" )
    local uiview = aui:GetFocusedView()
    aserverList = uiview:FindWidget("serverList")
    astartButton = uiview:FindWidget("startButton")
    astartButton:SetState(UI_WIDGET_STATE_DISABLED, false)
    astopButton = uiview:FindWidget("stopButton")
    astopButton:SetState(UI_WIDGET_STATE_DISABLED, true)

end

function SubscribeToEvents()
    SubscribeToEvent("NetworkHostDiscovered", "HandleNetworkHostDiscovered");

    SubscribeToEvent(astartButton, "WidgetEvent", "HandleStartServer")
    SubscribeToEvent(astopButton, "WidgetEvent", "HandleStopServer")
    local uiview = aui:GetFocusedView() 
    local asearchButton = uiview:FindWidget("searchButton")
    SubscribeToEvent(asearchButton, "WidgetEvent", "HandleDoNetworkDiscovery")
end

function HandleNetworkHostDiscovered(eventType, eventData)
    local text = aserverList:GetText()
    local data = eventData["Beacon"]:GetVariantMap()
    text = text .. "\n" .. data["Name"]:GetString() .. "(" .. data["Players"]:GetInt() .. ")" .. eventData["Address"]:GetString() .. ":" .. eventData["Port"]:GetInt()
    aserverList:SetText(text)
end

function HandleStartServer(eventType, eventData)
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
 		return
	end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
    	if network:StartServer(SERVER_PORT) == true then
        	local data = VariantMap()
        	data["Name"] = "Test server"
        	data["Players"] = 100
        	-- Set data which will be sent to all who requests LAN network discovery
        	network:SetDiscoveryBeacon(data);
            astartButton:SetState(UI_WIDGET_STATE_DISABLED, true)
            astopButton:SetState(UI_WIDGET_STATE_DISABLED, false)
		end
    end
end

function HandleStopServer(eventType, eventData)
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
 		return
	end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
    	network:StopServer()
        astartButton:SetState(UI_WIDGET_STATE_DISABLED, false)
        astopButton:SetState(UI_WIDGET_STATE_DISABLED, true)
	end
end

function HandleDoNetworkDiscovery(eventType, eventData)
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
 		return
	end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
     	network:DiscoverHosts(SERVER_PORT)
    	aserverList:SetText("")
	end
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
