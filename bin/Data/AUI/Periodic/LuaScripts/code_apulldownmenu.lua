-- APulldownMenu application source code


function setup_uipulldownmenu( layout )
    local dest = layout:SearchAWidgetClass( "TBButton" )
    for i, awid in ipairs(dest) do
        SubscribeToEvent(awid, "WidgetEvent", "HandleUipulldownmenuEvent")
    end

    local dest1 = layout:SearchAWidgetClass( "TBPulldownMenu" )
    for i, apul in ipairs(dest1) do
        SubscribeToEvent(apul, "WidgetEvent", "HandleUipulldownmenuEvent")
    end
end

function HandleUipulldownmenuEvent( eventType, eventData)
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
        return
    end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if widget:GetId() == "uipulldownmenucode" then
            AppLog( "APulldownMenu support : " .. widget:GetId() .. " was pressed " )
            ViewCode ( "LuaScripts/code_apulldownmenu.lua", widget:GetParent() )
        end
        if widget:GetId() ==  "uipulldownmenulayout" then
            AppLog( "APulldownMenu support : " .. widget:GetId() .. " was pressed ")
            ViewCode ( "Scenes/layout_apulldownmenu.ui.txt", widget:GetParent() )
        end
    elseif eventData["Type"]:GetInt() == UI_EVENT_TYPE_CHANGED then
        if widget:GetId() == "FileMenu" then
            local pdm = tolua.cast(widget, "APulldownMenu") -- HELP No conversion from 'AWidget' to 'APulldownMenu'
            if pdm ~= nil then
                AppLog( "APulldownMenu event : " .. widget:GetId() .. " selected entry = " .. pdm:GetSelectedId())
            end
        end
        if widget:GetId() == "EditMenu" then
            local pdm = tolua.cast(widget, "APulldownMenu")
            if pdm ~= nil then
                AppLog( "APulldownMenu event : " .. widget:GetId() .. " selected entry = " .. pdm:GetSelectedId())
            end
        end
        if widget:GetId() == "ViewMenu" then
            local pdm = tolua.cast(widget, "APulldownMenu")
            if pdm ~= nil then
                AppLog( "APulldownMenu event : " .. widget:GetId() .. " selected entry = " ..  pdm:GetSelectedId())
            end
        end
        if widget:GetId() == "HelpMenu" then
            local pdm = tolua.cast(widget, "APulldownMenu")
            if pdm ~= nil then
               AppLog( "APulldownMenu event : " .. widget:GetId() .. " selected entry = " .. pdm:GetSelectedId())
            end
        end
    end
end

