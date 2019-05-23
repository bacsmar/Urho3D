-- AWidget application source code


function setup_uiwidget( layout )
    local dest = layout:SearchAWidgetClass( "TBButton" )
    for i, awid in ipairs(dest) do 
        SubscribeToEvent(awid, "WidgetEvent", "HandleUiwidgetEvent")
    end
end

function HandleUiwidgetEvent(eventType, eventData)
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
        return
    end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if widget:GetId() == "uiwidgetcode" then
            AppLog( "AWidget support : " .. widget:GetId() .. " was pressed " )
            ViewCode ( "LuaScripts/code_awidget.lua", widget:GetParent())
        end
        if widget:GetId() ==  "uiwidgetlayout" then
            AppLog( "AWidget support : " .. widget:GetId() .. " was pressed ")
            ViewCode ( "Scenes/layout_awidget.ui.txt", widget:GetParent())
        end
    end
end

