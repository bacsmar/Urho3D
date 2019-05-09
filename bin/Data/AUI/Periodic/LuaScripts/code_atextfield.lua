-- ATextField application source code

function setup_uitextfield( layout )
    local dest = layout:SearchAWidgetClass( "TBButton" )
    for i, awid in ipairs(dest) do
        SubscribeToEvent(awid, "WidgetEvent", "HandleUitextfieldEvent")
	end
end

function HandleUitextfieldEvent(eventType, eventData)
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
 		return
	end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if widget:GetId() == "uitextfieldcode" then
            AppLog( " support : " .. widget:GetId() .. " was pressed " )
            ViewCode ( "LuaScripts/code_atextfield.lua", widget:GetParent())
        end
        if widget:GetId() ==  "uitextfieldlayout" then
            AppLog( " support : " .. widget:GetId() .. " was pressed ")
            ViewCode ( "Scenes/layout_atextfield.ui.txt", widget:GetParent())
        end
    end
end

