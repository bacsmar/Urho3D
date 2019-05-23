-- ARadioButton application source code


function setup_uiradiobutton( layout)
    local dest = layout:SearchAWidgetClass( "TBButton" )
    for i, awid in ipairs(dest) do
        SubscribeToEvent(awid, "WidgetEvent", "HandleUiradiobuttonEvent")
    end

    demochk = layout:GetWidget ("demoradio")
    if demochk ~= nil then
        local d2 = tolua.cast(demochk, "AWidget")
        SubscribeToEvent(d2, "WidgetEvent", "HandleUiradiobuttonEvent")
    end
end

function HandleUiradiobuttonEvent( eventType, eventData)
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
        return
    end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if widget:GetId() == "uiradiobuttoncode" then
            AppLog( "ARadioButton support : " .. widget:GetId() .. " was pressed " )
            ViewCode ( "LuaScripts/code_aradiobutton.lua", widget:GetParent())
        end
        if widget:GetId() ==  "uiradiobuttonlayout" then
            AppLog( "ARadioButton support : " .. widget:GetId() .. " was pressed ")
            ViewCode ( "Scenes/layout_aradiobutton.ui.txt", widget:GetParent())
        end
        if widget:GetId() == "demoradio" then
            AppLog( "ARadioButton event : " .. widget:GetId() .. " was pressed, state = " ..  widget:GetValue())
        end
        if widget:GetId() ==  "radioset" then
            local demochk = widget:FindWidget ("demoradio")
            if demochk ~= nil then
                demochk:SetValue (1)
                AppLog( "ARadioButton action : " .. widget:GetId() .. " was pressed, set state to 1" )
            end
        end
        if widget:GetId() ==  "radiounset" then
            local demochk = widget:FindWidget ("demoradio")
            if demochk ~= nil then
                demochk:SetValue (0)
                AppLog( "ARadioButton action : " .. widget:GetId() .. " was pressed, set state to 0" )
            end
        end
    end
end

