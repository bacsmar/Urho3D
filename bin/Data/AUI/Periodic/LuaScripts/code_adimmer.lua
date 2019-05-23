-- ADimmer application source code


function setup_uidimmer( layout )
    local dest = layout:SearchAWidgetClass( "TBButton" )
    for i, awid in ipairs(dest) do
        SubscribeToEvent(awid, "WidgetEvent", "HandleUidimmerEvent")
    end
end

function HandleUidimmerEvent(eventType, eventData)
    local refid = eventData["RefID"]:GetString()
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
        return
    end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if widget:GetId() == "uidimmercode" then
            AppLog( "ADimmer support : " .. widget:GetId() .. " was pressed " )
            ViewCode ( "LuaScripts/code_adimmer.lua", widget:GetParent())
        end
        if widget:GetId() ==  "uidimmerlayout" then
            AppLog( "ADimmer support : " .. widget:GetId() .. " was pressed ")
            ViewCode ( "Scenes/layout_adimmer.ui.txt", widget:GetParent())
        end
        if widget:GetId() == "modalfinder" then
            AppLog( "ADimmer action : " .. widget:GetId() .. " was pressed ")
            local windowp = APromptWindow:new( uiview, widget:GetId())
            windowp:Show( "Modal Prompt", "Modal Selection in window", "preset value", 1, 0, 0)
        end
        if widget:GetId() == "modalok" then
            AppLog( "ADimmer support : " .. widget:GetId() .. " was pressed ")
            local mess2 = AMessageWindow:new( uiview, "mymess2")
            mess2:Show("MessageWindow - OK", "Modal MessageWindow - OK button", UI_MESSAGEWINDOW_SETTINGS_OK, true, 0, 0)
        end
        if widget:GetId() == "modalokcancel" then
            AppLog( "ADimmer support : " .. widget:GetId() .. " was pressed ")
            local mess3 = AMessageWindow:new(uiview, "mymess3")
            SubscribeToEvent(mess3, "WidgetEvent", "HandleUimessagewindowEvent" )
            mess3:Show("MessageWindow - OK CANCEL", "Modal MessageWindow - OK CANCEL buttons", UI_MESSAGEWINDOW_SETTINGS_OK_CANCEL, true, 0, 0)
        end
        if widget:GetId() == "modalyesno" then
            AppLog( "ADimmer support : " .. widget:GetId() .. " was pressed ")
            local mess4 = AMessageWindow:new( uiview, "mymess4")
            mess4:Show( "MessageWindow - YES NO", "Modal MessageWindow - YES NO buttons", UI_MESSAGEWINDOW_SETTINGS_YES_NO, true, 0, 0)
        end

        if widget:GetId() == "modalfilefinder" then
            AppLog( "ADimmer action : " .. widget:GetId() .. " was pressed ")
            winf = AFinderWindow:new(uiview, widget:GetId())
            winf:FindFile("Find a File", "", 1, 0, 0)
        end
        if widget:GetId() ==  "modalfolderfinder" then
            AppLog( "ADimmer action : " .. widget:GetId() .. " was pressed ")
            windowd = AFinderWindow:new(uiview, widget:GetId())
            windowd:FindPath("Find a Folder", "", 1, 0, 0)
        end
    else
        AppLog( "ADimmer event : " .. widget:GetId() .. " event type = " .. eventData["Type"]:GetInt() )
   end
end

