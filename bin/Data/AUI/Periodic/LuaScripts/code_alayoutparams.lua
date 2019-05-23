-- ALayoutParams application source code

function setup_uilayoutparams( layout )
    local dest = layout:SearchAWidgetClass( "TBButton" )
    for i, awid in ipairs(dest) do
        SubscribeToEvent(awid, "WidgetEvent", "HandleUilayoutparamsEvent")
    end
end

function HandleUilayoutparamsEvent(eventType, eventData)
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
        return
    end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if widget:GetId() == "uilayoutparamscode" then
            AppLog( "ALayoutParams support : " .. widget:GetId() .. " was pressed " )
            ViewCode ( "LuaScripts/code_alayoutparams.lua", widget:GetParent())
        end
        if widget:GetId() ==  "uilayoutparamslayout" then
            AppLog( "ALayoutParams support : " .. widget:GetId() .. " was pressed ")
            ViewCode ( "Scenes/layout_alayoutparams.ui.txt", widget:GetParent())
        end
    end
end

