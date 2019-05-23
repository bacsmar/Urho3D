-- APromptWindow application source code


function setup_uipromptwindow( layout, uiview )
    local dest = layout:SearchAWidgetClass( "TBButton" )
    for i, awid in ipairs(dest) do
        SubscribeToEvent(awid, "WidgetEvent", "HandleUipromptwindowEvent")
    end
end

function HandlePromptCompleteEvent(eventType, eventData)
    AppLog( "APromptWindow event : the window " .. eventData["Title"]:GetString()
            .. " file was " .. eventData["Selected"]:GetString()
            .. ", the button pressed was " .. eventData["Reason"]:GetString())
end

function HandleUipromptwindowEvent( eventType, eventData)
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
        return
    end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if widget:GetId() == "uipromptwindowcode" then
            AppLog( "APromptWindow support : " .. widget:GetId() .. " was pressed " )
            ViewCode ( "LuaScripts/code_apromptwindow.lua", widget:GetParent())
        end
        if widget:GetId() ==  "uipromptwindowlayout" then
            AppLog( "APromptWindow support : " .. widget:GetId() .. " was pressed ")
            ViewCode ( "Scenes/layout_apromptwindow.ui.txt", widget:GetParent())
        end
        if widget:GetId() == "stringfinder" then
            AppLog( "APromptWindow action : " .. widget:GetId() .. " was pressed ")
            local windowp = APromptWindow:new( uiview, widget:GetId())
            SubscribeToEvent(windowp, "APromptComplete", "HandlePromptCompleteEvent")
            windowp:Show( "WindowTitle", "Message in window", "preset value", 0, 0, 0)
        end
    end
end

