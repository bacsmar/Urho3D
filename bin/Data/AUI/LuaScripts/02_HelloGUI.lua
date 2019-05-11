-- A simple 'HelloWorld' GUI created purely from code.
-- This sample demonstrates:
--     - Creation of controls and building a UI hierarchy
--     - Loading UI style from XML and applying it to controls
--     - Handling of global and per-control events
-- For more advanced users (beginners can skip this section):
--     - Dragging UIElements
--     - Displaying tooltips
--     - Accessing available Events data (eventData)

require "AUI/LuaScripts/Utilities/Sample"

local window = nil
local dragBeginPosition = IntVector2(0, 0)

function Start()
    -- Execute the common startup for samples
    SampleStart()

    -- Enable OS cursor
    input.mouseVisible = true

    -- Load XML file containing default UI style sheet
    local style = cache:GetResource("XMLFile", "UI/DefaultStyle.xml")

    -- Set the loaded style as default style
    ui.root.defaultStyle = style

    -- Initialize Window
    InitWindow()

    -- Create and add some controls to the Window
    InitControls()

    -- Create a draggable Fish
    CreateDraggableFish()

    -- Set the mouse mode to use in the sample
    SampleInitMouseMode(MM_FREE)
end

function InitControls()
    -- Create a CheckBox
    -- Create a Button
    -- Create a LineEdit
    -- Add controls to Window
    -- Apply previously set default style

    local uiview = aui:GetFocusedView()
    
    local win1 = AWindow:new()
    win1:SetSettings ( UI_WINDOW_SETTINGS_DEFAULT )
    win1:SetId ("myWindow")
    win1:SetText("")
    win1:Load("../Scenes/02_layout.ui.txt")
    win1:ResizeToFitContent()
    uiview:AddChild(win1)
    win1:Center()
  
    local checkplease = win1:GetWidget("aCheck")
    SubscribeToEvent( checkplease, "WidgetEvent", "HandleWidgetEvent" )

    local abutton = win1:GetWidget("aButton")
    SubscribeToEvent( abutton, "WidgetEvent", "HandleWidgetEvent" )
  
    local aedit = win1:GetWidget("aEditfield")
    SubscribeToEvent( aedit, "WidgetEvent", "HandleWidgetEvent" )

    SubscribeToEvent( win1, "WidgetEvent", "HandleWidgetEvent" )
    SubscribeToEvent( win1, "AWindowClosed", "HandleClosePressed" ) -- window close = exit

 end

function InitWindow()
    -- Create the Window and add it to the UI's root node
    -- Create Window 'titlebar' container
    -- Create the Window title Text
    -- Create the Window's close button
    -- Add the title bar to the Window
    -- Apply styles
    -- Subscribe to buttonClose release (following a 'press') events
       -- SubscribeToEvent(buttonClose, "Released",
       --  function (eventType, eventData)
       --      engine:Exit()
       --  end)

    -- Subscribe also to all UI mouse clicks just to see where we have clicked
    -- SubscribeToEvent("UIMouseClick", HandleControlClicked)

    AUIInit ( "AUI/resources/default_font/vera.ttf", "Vera", 12, "" )

end

function CreateDraggableFish()
    -- Create a draggable Fish button
    -- Add a tooltip to Fish button 
    -- Subscribe draggableFish to Drag Events (in order to make it draggable)
    -- See "Event list" in documentation's Main Page for reference on available Events and their eventData
end

function HandleControlClicked(eventType, eventData)
    -- Get the Text control acting as the Window's title
    local element = window:GetChild("WindowTitle", true)
    local windowTitle = tolua.cast(element, 'Text')

    -- Get control that was clicked
    local clicked = eventData["Element"]:GetPtr("UIElement")
    local name = "...?"
    if clicked ~= nil then
        -- Get the name of the control that was clicked
        name = clicked.name
    end

    -- Update the Window's title text
    windowTitle.text = "Hello " .. name .. "!"
end

function HandleWidgetEvent(eventType, eventData)
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
 		return
	end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK or eventData["Type"]:GetInt() == UI_EVENT_TYPE_CHANGED then
		local win = tolua.cast( widget:FindWidget("myWindow"), "AWindow" )
		if win ~= nil then
			win:SetText("Hello ".. widget:GetId() .. "!" )
		end
    end
end

function HandleClosePressed( eventType, eventData)
   engine:Exit()
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
