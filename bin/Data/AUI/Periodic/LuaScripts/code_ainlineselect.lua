-- AInlineSelect application source code


function setup_uiinlineselect( layout )
    local dest = layout:SearchAWidgetClass( "TBButton" )
    for i, awid in ipairs(dest) do  -- set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(awid, "WidgetEvent", "HandleUiinlineselectEvent")
    end
    local sld1 = layout:GetWidget ("ilsstep")
    if sld1 ~= nil then
        local d1 = tolua.cast(sld1, "AWidget")
        SubscribeToEvent(d1, "WidgetEvent", "HandleUiinlineselectEvent" )
    end
    local sld2 = layout:GetWidget ("inlineselectdemo")
    if sld2 ~= nil then
        local d2 = tolua.cast(sld2, "AWidget")
        SubscribeToEvent(d2, "WidgetEvent", "HandleUiinlineselectEvent" )
    end
end

function HandleUiinlineselectEvent(eventType, eventData)
    local widget = eventData["Target"]:GetPtr("AWidget");
    if widget == nil then
        return;
    end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if widget:GetId() == "uiinlineselectcode" then
            AppLog( "AInlineSelect support : " .. widget:GetId() .. " was pressed " )
            ViewCode ( "LuaScripts/code_ainlineselect.lua", widget:GetParent())
        end
        if widget:GetId() ==  "uiinlineselectlayout" then
            AppLog( "AInlineSelect support : " .. widget:GetId() .. " was pressed ")
            ViewCode ( "Scenes/layout_ainlineselect.ui.txt", widget:GetParent())
        end
    elseif eventData["Type"]:GetInt() == UI_EVENT_TYPE_CHANGED then
        if widget:GetId() == "inlineselectdemo" then
            local ils = tolua.cast(widget, "AInlineSelect")
            if ils ~= nil then
                AppLog( "AInlineSelect event : " .. widget:GetId() .. " changed value to " .. ils:GetValue())
            end
        end
        if widget:GetId() == "ilsstep" then
            local steps = tolua.cast(widget, "ASlider")
            if steps ~= nil then
                local ils1 = widget:FindWidget("inlineselectdemo")
                if ils1 ~= nil then
                    local ils = tolua.cast(ils1, "AInlineSelect")
                    ils:SetStepSize (steps:GetValue())
                end
                AppLog( "AInlineSelect event : " .. widget:GetId() .. " step size changed to " .. steps:GetValue())
            end
        end
    end
end

