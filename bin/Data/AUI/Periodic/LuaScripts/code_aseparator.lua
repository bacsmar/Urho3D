-- ASeparator application source code


function setup_uiseparator( layout )
    local dest = layout:SearchAWidgetClass( "TBButton" )
    for i, awid in ipairs(dest) do
        SubscribeToEvent(awid, "WidgetEvent", "HandleUiseparatorEvent")
	end
end

function HandleUiseparatorEvent(eventType, eventData)
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
 		return
	end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if widget:GetId() == "uiseparatorcode" then
            AppLog( "ASeparator support : " .. widget:GetId() .. " was pressed " )
            ViewCode ( "LuaScripts/code_aseparator.lua", widget:GetParent())
        end
        if widget:GetId() ==  "uiseparatorlayout" then
            AppLog( "ASeparator support : " .. widget:GetId() .. " was pressed ")
            ViewCode ( "Scenes/layout_aseparator.ui.txt", widget:GetParent())
        end
    end
end

