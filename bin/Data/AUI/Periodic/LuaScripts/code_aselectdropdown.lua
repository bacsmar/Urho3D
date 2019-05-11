-- ASelectDropdown application source code
-- when menu entry is selected, the ASelectDropdown value (and string) is updated, theoritically:

function setup_uiselectdropdown( layout )
    local dest = layout:SearchAWidgetClass( "TBButton" )
    for i, awid in ipairs(dest) do
        SubscribeToEvent(awid, "WidgetEvent", "HandleUiselectdropdownEvent")
	end
 
    local demo = layout:GetWidget("selectdropdowndemo")
    if demo ~= nil then
		SubscribeToEvent(demo, "WidgetEvent", "HandleAllSelectdropdownEvent" )
    end
end

function HandleAllSelectdropdownEvent(eventType, eventData)
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
 		return
	end
  	if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CHANGED then   
		AppLog( "ASelectDropdown changed event : " .. widget:GetId() .. " changed value to " .. widget:GetText())
	elseif eventData["Type"]:GetInt() > 0 then
		AppLog( "ASelectDropdown " .. widget:GetId() .. " got event : " .. eventData["Type"]:GetInt())
    end
end

function HandleUiselectdropdownEvent( eventType, eventData)
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
 		return
	end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if widget:GetId() == "uiselectdropdowncode" then
            AppLog( "ASelectDropdown support : " .. widget:GetId() .. " was pressed " .. widget:GetText() )
            ViewCode ( "LuaScripts/code_aselectdropdown.lua", widget:GetParent())
       end
        if widget:GetId() ==  "uiselectdropdownlayout" then
            AppLog( "ASelectDropdown support : " .. widget:GetId() .. " was pressed ")
            ViewCode ( "Scenes/layout_aselectdropdown.ui.txt", widget:GetParent())
        end
    end
end

