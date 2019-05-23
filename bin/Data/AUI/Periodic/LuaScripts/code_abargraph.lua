-- ABargraph application source code

function setup_uibargraph( layout )
    dest = layout:SearchAWidgetClass( "TBButton" )
    for i, awid in ipairs(dest) do  -- set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(awid, "WidgetEvent", "HandleUibargraphEvent")
    end
end

function HandleUibargraphEvent( eventType, eventData )
    local widget = eventData["Target"]:GetPtr("AWidget")
    if ( widget == nil) then
        return;
    end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if widget:GetId() == "uibargraphcode" then
            AppLog( "ABargraph support : " .. widget:GetId() .. " was pressed " )
            ViewCode ( "LuaScripts/code_abargraph.lua", widget:GetParent() )
        end
        if widget:GetId() ==  "uibargraphlayout" then
            AppLog( "ABargraph support : " .. widget:GetId() .. " was pressed ")
            ViewCode ( "Scenes/layout_abargraph.ui.txt", widget:GetParent() )
        end
    end
end

