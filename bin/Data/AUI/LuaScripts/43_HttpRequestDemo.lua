-- Http request example.
-- This example demonstrates:
--     - How to use Http request API

require "AUI/LuaScripts/Utilities/Sample"

local message = ""
local text = nil
local httpRequest = nil

function Start()
    -- Execute the common startup for samples
    SampleStart()

    -- Create the user interface
    CreateUI()

    -- Set the mouse mode to use in the sample
    SampleInitMouseMode(MM_FREE)

    -- Subscribe to basic events such as update
    SubscribeToEvents()
end

function CreateUI()
    -- Construct new Text object
    AUIInit ( "AUI/resources/default_font/vera.ttf", "Vera", 20, "AUI/Scenes/01_layout.ui.txt" )
    writeText ( "Ready" )
end

function writeText( mystr )
    local mytext = aui:GetRootAWidget():FindWidget("helloText")
	if mytext ~= nil then
    	mytext:SetText ( mystr )
	end
end

function SubscribeToEvents()
    -- Subscribe HandleUpdate() function for processing HTTP request
    SubscribeToEvent("Update", "HandleUpdate")
end

function HandleUpdate(eventType, eventData)
    -- Create HTTP request
    if httpRequest == nil then
        httpRequest = network:MakeHttpRequest("http://httpbin.org/ip")
    else
        -- Initializing HTTP request
        if httpRequest.state == HTTP_INITIALIZING then
            return
        -- An error has occurred
        elseif httpRequest.state == HTTP_ERROR then
            writeText( "An error has occurred." )
            UnsubscribeFromEvent("Update")
        -- Get message data
        else
            if httpRequest.availableSize > 0 then
                message = message .. httpRequest:ReadLine()
            else
                writeText("Processing...")

                local json = JSONFile:new()
                json:FromString(message)

                local val = json:GetRoot():Get("origin")

                if val.isNull then
                    writeText( "Invalid string." )
                else
                    writeText( "Your IP is: " .. val:GetString() )
                end

                json = nil         --json:delete()
                httpRequest = nil  --httpRequest:delete()

                UnsubscribeFromEvent("Update")
            end       
        end
    end
end

-- Create XML patch instructions for screen joystick layout specific to this sample app
function GetScreenJoystickPatchString()
    return
        "<patch>" ..
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Hat0']]\">" ..
        "        <attribute name=\"Is Visible\" value=\"false\" />" ..
        "    </add>" ..
        "</patch>"
end
