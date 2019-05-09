-- AContainer application source code

function setup_uicontainer( layout )
    local dest = layout:SearchAWidgetClass( "TBButton" )
    for i, awid in ipairs(dest) do
        SubscribeToEvent(awid, "WidgetEvent", "HandleUicontainerEvent")
	end
end

function HandleUicontainerEvent( eventType, eventData )
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
 		return
	end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if widget:GetId() == "uicontainercode" then
            AppLog( "AContainer support : " .. widget:GetId() .. " was pressed " )
            ViewCode ( "LuaScripts/code_acontainer.lua", widget:GetParent())
        end
        if widget:GetId() ==  "uicontainerlayout" then
            AppLog( "AContainer support : " .. widget:GetId() .. " was pressed ")
            ViewCode ( "Scenes/layout_acontainer.ui.txt", widget:GetParent())
        end
    end
end

