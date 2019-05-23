-- ASlider application source code

function setup_uislider( layout )
    local dest = layout:SearchAWidgetClass( "TBButton" )
    for i, awid in ipairs(dest) do
        SubscribeToEvent(awid, "WidgetEvent", "HandleUisliderEvent")
    end

    local sld1 = layout:GetWidget ("sliderdemo")
    if sld1 ~= nil then
        local d1 = tolua.cast(sld1, "AWidget")
        if d1 ~= nil then
            SubscribeToEvent(d1, "WidgetEvent", "HandleUisliderEvent" )
        end
    end
end

function HandleUisliderEvent( eventType, eventData)
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
        return
    end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if widget:GetId() == "uislidercode" then
            AppLog( "ASlider support : " .. widget:GetId() .. " was pressed " )
            ViewCode ( "LuaScripts/code_aslider.lua", widget:GetParent())
        end
        if widget:GetId() == "uisliderlayout" then
            AppLog( "ASlider support : " .. widget:GetId() .. " was pressed ")
            ViewCode ( "Scenes/layout_aslider.ui.txt", widget:GetParent())
        end
    elseif  eventData["Type"]:GetInt() == UI_EVENT_TYPE_CHANGED then
        if widget:GetId() =="sliderdemo" then
            AppLog( "ASlider event : " .. widget:GetId() .. " changed value to " .. widget:GetValue())
        end
    end
end

