-- AColorWheel application source code

function setup_uicolorwheel( layout )
    local dest = layout:SearchAWidgetClass( "TBButton" )
    for i, awid in ipairs(dest) do
        SubscribeToEvent(awid, "WidgetEvent", "HandleUicolorwheelEvent")
    end

    local cwx = layout:GetWidget ("colorwheeldemo")
    if cwx ~= nil then
        local c1 = tolua.cast(cwx, "AWidget")
        SubscribeToEvent(c1, "WidgetEvent", "HandleUicolorwheelEvent")
    end
end

function HandleUicolorwheelEvent( eventType, eventData)
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
        return
    end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if widget:GetId() ==  "uicolorwheelcode" then
            AppLog( "AColorWheel support : " .. widget:GetId() .. " was pressed " )
            ViewCode ( "LuaScripts/code_acolorwheel.lua", widget:GetParent())
        end
        if widget:GetId() ==  "uicolorwheellayout" then
            AppLog( "AColorWheel support : " .. widget:GetId() .. " was pressed ")
            ViewCode ( "Scenes/layout_acolorwheel.ui.txt", widget:GetParent())
        end
    elseif eventData["Type"]:GetInt() == UI_EVENT_TYPE_CHANGED then
        if widget:GetId() ==  "colorwheeldemo" then
            local cwx = tolua.cast(widget, "AColorWheel") -- collect click color info
            if cwx ~= nil then
                AppLog( "AColorWheel event : " .. widget:GetId() .. " hue = " .. cwx:GetHue() .. " saturation = " .. cwx:GetSaturation())
            end
        end
    end
end

