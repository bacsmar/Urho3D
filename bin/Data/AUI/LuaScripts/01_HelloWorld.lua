-- This first example, maintaining tradition, prints a "Hello World" message.
-- Furthermore it shows:
--     - Using the Sample utility functions as a base for the application
--     - Adding a Text element to the graphical user interface
--     - Subscribing to and handling of update events

require "AUI/LuaScripts/Utilities/Sample"

function Start()
    -- Execute the common startup for samples
    SampleStart()

    -- Create "Hello World" Text
    CreateText()

    -- Set the mouse mode to use in the sample
    SampleInitMouseMode(MM_FREE)

    -- Finally, hook-up this HelloWorld instance to handle update events
    SubscribeToEvents()
end

function CreateText()

    AUIInit ( "Fonts/Anonymous Pro.ttf", "APro", 30, "AUI/Scenes/01_layout.ui.txt" )
    
    -- get the Text object
    local mytext = aui:GetRootAWidget():FindWidget("helloText")

    -- Set String to display
    mytext:SetText ( "Hello World from Atomic Urho3D!" )

end

function SubscribeToEvents()
    -- Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent("Update", "HandleUpdate")
end

function HandleUpdate(eventType, eventData)
    -- Do nothing for now, could be extended to eg. animate the display
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
