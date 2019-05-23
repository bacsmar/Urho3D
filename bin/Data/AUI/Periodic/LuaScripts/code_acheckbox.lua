-- ACheckBox application source code

function setup_uicheckbox( layout )
    local dest = layout:SearchAWidgetClass( "TBButton" )
    for i, awid in ipairs(dest) do
        SubscribeToEvent(awid, "WidgetEvent", "HandleUicheckboxEvent")
    end

    local demochk = layout:GetWidget ("democheck")
    if (demochk ~= nil) then
        local d2 = tolua.cast(demochk, "AWidget")
        SubscribeToEvent(d2, "WidgetEvent", "HandleUicheckboxEvent")
    end
end

function HandleUicheckboxEvent(eventType, eventData)
    local widget = eventData["Target"]:GetPtr("AWidget")
    if ( widget == nil) then
        return;
    end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if widget:GetId() == "uicheckboxcode" then
            AppLog( "ACheckBox support : " .. widget:GetId() .. " was pressed " )
            ViewCode ( "LuaScripts/code_acheckbox.lua", widget:GetParent() )
        end
        if widget:GetId() ==  "uicheckboxlayout" then
            AppLog( "ACheckBox support : " .. widget:GetId() .. " was pressed ")
            ViewCode ( "Scenes/layout_acheckbox.ui.txt", widget:GetParent() )
        end
        if widget:GetId() == "democheck" then
            AppLog( "ACheckBox event : " .. widget:GetId() .. " was pressed, state = " .. widget:GetValue())
        end
        if widget:GetId() ==  "checkset" then
            local demochk = widget:FindWidget ("democheck")
            if demochk ~= nil then
                demochk:SetValue (1)
                AppLog( "ACheckBox action : " .. widget:GetId() .. " was pressed, set state to 1" )
            end
        end
        if widget:GetId() == "checkunset" then
            local demochk = widget:FindWidget ("democheck")
            if demochk ~= nil then
                demochk:SetValue (0)
                AppLog( "ACheckBox action : " .. widget:GetId() .. " was pressed, set state to 0" )
            end
        end
    end
end

