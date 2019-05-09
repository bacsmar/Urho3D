-- AScrollContainer application source code

function setup_uiscrollcontainer( layout )
    local dest = layout:SearchAWidgetClass( "TBButton" )
    for i, awid in ipairs(dest) do
        SubscribeToEvent(awid, "WidgetEvent", "HandleUiscrollcontainerEvent")
	end
end

function HandleUiscrollcontainerEvent( eventType, eventData)
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
 		return
	end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if widget:GetId() == "uiscrollcontainercode" then
            AppLog( " support : " .. widget:GetId() .. " was pressed " )
            ViewCode ( "LuaScripts/code_ascrollcontainer.lua", widget:GetParent())
        end
        if widget:GetId() ==  "uiscrollcontainerlayout" then
            AppLog( " support : " .. widget:GetId() .. " was pressed ")
            ViewCode ( "Scenes/layout_ascrollcontainer.ui.txt", widget:GetParent())
        end
    end
end

