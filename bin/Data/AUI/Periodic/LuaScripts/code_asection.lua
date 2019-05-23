-- ASection application source code

function setup_uisection( layout )
    local dest = layout:SearchAWidgetClass( "TBButton" )
    for i, awid in ipairs(dest) do 
        SubscribeToEvent(awid, "WidgetEvent", "HandleUisectionEvent")
    end
    local sec1 = layout:GetWidget("ASectionDemo")
    if sec1 ~= nil then
       SubscribeToEvent(sec1, "WidgetEvent", "HandleUisectionEvent" )
    end
    local sec2 = layout:GetWidget("ASection2Demo")
    if sec2 ~= nil then
        SubscribeToEvent(sec2, "WidgetEvent", "HandleUisectionEvent" )
    end
end

function HandleUisectionEvent(eventType, eventData)
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
        return
    end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if widget:GetId() == "uisectioncode" then
            AppLog( "ASection support : " .. widget:GetId() .. " was pressed " )
            ViewCode ( "LuaScripts/code_asection.lua", widget:GetParent())
        end
        if widget:GetId() ==  "uisectionlayout" then
            AppLog( "ASection support : " .. widget:GetId() .. " was pressed ")
            ViewCode ( "Scenes/layout_asection.ui.txt", widget:GetParent())
        end
    elseif eventData["Type"]:GetInt() == UI_EVENT_TYPE_CHANGED then
        local demo1 = widget:FindWidget("ASectionDemo") -- event comes in on child widget!
        if demo1:IsAncestorOf(widget) then
            AppLog( "ASection event : " ..  demo1:GetId() .. " changed to value = " .. demo1:GetValue())
        end
        local demo2 = widget:FindWidget("ASection2Demo")
        if demo2:IsAncestorOf(widget) then
            AppLog( "ASection event : " ..  demo2:GetId() .. " changed to value = " .. demo2:GetValue())
        end
    end
end

