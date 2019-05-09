-- AMessageWindow application source code


function setup_uimessagewindow( layout )
    local dest = layout:SearchAWidgetClass( "TBButton" )
    for i, awid in ipairs(dest) do
        SubscribeToEvent(awid, "WidgetEvent", "HandleUimessagewindowEvent")
	end
end

function HandleUimessagewindowEvent(eventType, eventData)
    local refid = eventData["RefID"]:GetString()
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
 		return
	end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if widget:GetId() == "uimessagewindowcode" then
            AppLog( "AMessageWindow support : " .. widget:GetId() .. " was pressed " )
            ViewCode ( "LuaScripts/code_amessagewindow.lua", widget:GetParent())
        end
        if widget:GetId() ==  "uimessagewindowlayout" then
            AppLog( "AMessageWindow support : " .. widget:GetId() .. " was pressed ")
            ViewCode ( "Scenes/layout_amessagewindow.ui.txt", widget:GetParent())
        end
        if widget:GetId() == "msgnone" then
            AppLog( "AMessageWindow support : " .. widget:GetId() .. " was pressed ")
            local mess1 = AMessageWindow:new( uiview, "mymess1" )
            mess1:Show("MessageWindow - NONE", "this is a MessageWindow - None button", UI_MESSAGEWINDOW_SETTINGS_NONE, false, 0, 0)
        end
        if widget:GetId() == "msgok" then
            AppLog( "AMessageWindow support : " .. widget:GetId() .. " was pressed ")
            local mess2 = AMessageWindow:new( uiview, "mymess2")
            SubscribeToEvent(mess2, "WidgetEvent", "HandleUimessagewindowEvent" )
            mess2:Show("MessageWindow - OK", "this is a MessageWindow - OK button", UI_MESSAGEWINDOW_SETTINGS_OK, false, 0, 0)
        end
        if widget:GetId() == "msgkcancel" then
            AppLog( "AMessageWindow support : " .. widget:GetId() .. " was pressed ")
            local mess3 = AMessageWindow:new(uiview, "mymess3")
            SubscribeToEvent(mess3, "WidgetEvent", "HandleUimessagewindowEvent" )
            mess3:Show("MessageWindow - OK CANCEL", "this is a MessageWindow - OK CANCEL buttons", UI_MESSAGEWINDOW_SETTINGS_OK_CANCEL, false, 0, 0)
        end
        if widget:GetId() == "msgyesno" then
            AppLog( "AMessageWindow support : " .. widget:GetId() .. " was pressed ")
            local mess4 = AMessageWindow:new( uiview, "mymess4")
            SubscribeToEvent(mess4, "WidgetEvent", "HandleUimessagewindowEvent" )
            mess4:Show( "MessageWindow - YES NO", "this is a MessageWindow - YES NO buttons", UI_MESSAGEWINDOW_SETTINGS_YES_NO, false, 0, 0)
        end
        if refid == "TBMessageWindow.ok" then
            AppLog( "AMessageWindow event : " .. refid .. " closed the AMessageWindow")
        end
        if refid == "TBMessageWindow.cancel" then
            AppLog( "AMessageWindow event : " .. refid .. " closed the AMessageWindow")
        end
        if refid == "TBMessageWindow.yes" then
            AppLog( "AMessageWindow event : " .. refid .. " closed the AMessageWindow")
        end
        if refid == "TBMessageWindow.no" then
            AppLog( "AMessageWindow event : " .. refid .. " closed the AMessageWindow")
        end
    else
        AppLog( "AMessageWindow event : " .. widget:GetId() .. " event type = " .. eventData["Type"]:GetInt() )
   end
end

