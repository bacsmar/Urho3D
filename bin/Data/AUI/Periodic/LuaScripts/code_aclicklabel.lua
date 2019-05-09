-- AClickLabel application source code


function setup_uiclicklabel( layout )
    local dest = layout:SearchAWidgetClass( "TBButton" )
    for i, awid in ipairs(dest) do
        SubscribeToEvent(awid, "WidgetEvent", "HandleUiclicklabelEvent")
	end

    chk1 = layout:GetWidget ("somecheck")
    if chk1 ~= nil then
		local c1 = tolua.cast(chk1, "AWidget")
        SubscribeToEvent(c1, "WidgetEvent", "HandleUiclicklabelEvent")
	end
    chk2 = layout:GetWidget ("someradio")
    if chk2 ~= nil then
		local c2 = tolua.cast(chk2, "AWidget")
        SubscribeToEvent(c2, "WidgetEvent", "HandleUiclicklabelEvent")
	end
end

function HandleUiclicklabelEvent( eventType, eventData )
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
 		return
	end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if widget:GetId() == "uiclicklabelcode" then
            AppLog( "AClickLabel support : " .. widget:GetId() .. " was pressed " )
            ViewCode ( "LuaScripts/code_aclicklabel.lua", widget:GetParent() )
        end
        if widget:GetId() == "uiclicklabellayout" then
            AppLog( "AClickLabel support : " .. widget:GetId() .. " was pressed ")
            ViewCode ( "Scenes/layout_aclicklabel.ui.txt", widget:GetParent() )
        end
        if widget:GetId() == "somecheck" then
            AppLog( "AClickLabel event : " .. widget:GetId() .. " was pressed, state = " .. widget:GetValue())
        end
        if widget:GetId() == "someradio" then
            AppLog( "AClickLabel event : " .. widget:GetId() .. " was pressed, state = " .. widget:GetValue())
        end
    end
end

