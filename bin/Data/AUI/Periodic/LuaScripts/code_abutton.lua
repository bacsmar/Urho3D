-- AButton application source code

function setup_uibutton( layout)
    local dest = layout:SearchAWidgetClass( "TBButton" )
    for i, awid in ipairs(dest) do
        SubscribeToEvent(awid, "WidgetEvent", "HandleUibuttonEvent")
	end
end

function HandleUibuttonEvent( eventType, eventData )

    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
 		return;
	end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if widget:GetId() == "demobutton" then
            AppLog( "AButton action : " .. widget:GetId() .. " was pressed ")
        end
        if widget:GetId() == "uibuttoncode" then
            AppLog( "AButton support : " .. widget:GetId() .. " was pressed " )
            ViewCode ( "LuaScripts/code_abutton.lua", widget:GetParent() );
        end
        if widget:GetId() == "uibuttonlayout" then
            AppLog( "AButton support : " .. widget:GetId() .. " was pressed ")
            ViewCode ( "Scenes/layout_abutton.ui.txt", widget:GetParent() )
        end
        if widget:GetId() == "buttonducky" then
            AppLog( "AButton action : " .. widget:GetId() .. " was pressed ")
        end
        if widget:GetId() == "buttonready" then
            AppLog( "AButton action : " .. widget:GetId() .. " was pressed ")
        end
        if widget:GetId() == "buttonatomic" then
            AppLog( "AButton action : " .. widget:GetId() .. " was pressed ")
        end
        if widget:GetId() == "buttongreen" then
            AppLog( "AButton action : " .. widget:GetId() .. " was pressed ")
        end
    end
end

