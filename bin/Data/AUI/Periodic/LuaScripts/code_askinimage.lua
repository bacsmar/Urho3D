-- ASkinImage application source code

function setup_uiskinimage( layout )
    local dest = layout:SearchAWidgetClass( "TBButton" )
    for i, awid in ipairs(dest) do
        SubscribeToEvent(awid, "WidgetEvent", "HandleUiskinimageEvent")
    end
end

function HandleUiskinimageEvent(eventType, eventData)
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
        return
    end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if widget:GetId() == "uiskinimagecode" then
            AppLog( "ASkinImage support : " .. widget:GetId() .. " was pressed " )
            ViewCode ( "LuaScripts/code_askinimage.lua", widget:GetParent())
        end
        if widget:GetId() ==  "uiskinimagelayout" then
            AppLog( "ASkinImage support : " .. widget:GetId() .. " was pressed ")
            ViewCode ( "Scenes/layout_askinimage.ui.txt", widget:GetParent())
        end
    end
end

