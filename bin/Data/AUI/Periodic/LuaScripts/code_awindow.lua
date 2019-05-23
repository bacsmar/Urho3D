-- AWindow application source code


function setup_uiwindow( layout, uiview )
    local dest = layout:SearchAWidgetClass( "TBButton" )
    for i, awid in ipairs(dest) do
        SubscribeToEvent(awid, "WidgetEvent", "HandleUiwindowEvent")
    end
end

function HandleUiwindowEvent(eventType, eventData)
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
        return
    end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if widget:GetId() == "uiwindowcode" then
            AppLog( "AWindow support : " .. widget:GetId() .. " was pressed " )
            ViewCode ( "LuaScripts/code_awindow.lua", widget:GetParent())
        end
        if widget:GetId() ==  "uiwindowlayout" then
            AppLog( "AWindow support : " .. widget:GetId() .. " was pressed ")
            ViewCode ( "Scenes/layout_awindow.ui.txt", widget:GetParent())
        end

        if widget:GetId() == "windowdemo" then
            AppLog( "AWindow action : " .. widget:GetId() .. " was pressed " )
            local win1 = AWindow:new()
            win1:SetSettings ( UI_WINDOW_SETTINGS_DEFAULT )
            win1:SetText("AWindow demo (a login dialog)")
            win1:Load("Scenes/login_dialog.ui.txt")
            win1:ResizeToFitContent()
            uiview:AddChild(win1)
            win1:Center()
            local login = win1:GetWidget("login")
            SubscribeToEvent(login, "WidgetEvent", "HandleUiwindowEvent" )
            local cancel = win1:GetWidget("cancel")
            SubscribeToEvent(cancel, "WidgetEvent", "HandleUiwindowEvent" )
        end
        if widget:GetId() == "login" then
            AppLog( "AWindow action : " .. widget:GetId() .. " was pressed " )
            local mywin = FindTheWindowParent(widget)
            if mywin ~= nil then
                local w1 = tolua.cast( mywin, "AWindow")
                if w1 ~= nil then
                    mywin:Close()
                end
            end
        end
        if widget:GetId() == "cancel" then
            AppLog( "AWindow action : " .. widget:GetId() .. " was pressed " )
            local mywindow = FindTheWindowParent(widget)
            if mywindow ~= nil then
                local w1 = tolua.cast( mywindow, "AWindow")
                if w1 ~= nil then
                    w1:Close()
                end
            end
        end
        if widget:GetId() == "windowdemo1" then
            AppLog( "AWindow action : " .. widget:GetId() .. " was pressed " )
            local win2 = AWindow:new()
            win2:SetSettings ( UI_WINDOW_SETTINGS_DEFAULT )
            win2:SetText("AWindow demo (a table)" )
            win2:Load("Scenes/sheet.ui.txt")
            win2:ResizeToFitContent()
            uiview:AddChild(win2)
            win2:Center()
        end
        if widget:GetId() == "windowdemo2" then
            AppLog( "AWindow action : " .. widget:GetId() .. " was pressed " )
            local win3 = AWindow:new()
            win3:SetAxis(UI_AXIS_X)
            win3:SetSettings ( UI_WINDOW_SETTINGS_DEFAULT )
            win3:SetText(" ")
            win3:Load("Scenes/sheet.ui.txt")
            win3:ResizeToFitContent()
            uiview:AddChild(win3)
            win3:Center()
        end
        if widget:GetId() == "windowdemo3" then
            AppLog( "AWindow action : " .. widget:GetId() .. " was pressed " )
            local win4 = AWindow:new()
            win4:SetSettings ( UI_WINDOW_SETTINGS_DEFAULT )
            win4:SetId ("WinCloseOverride" )
            win4:SetText("AWindow with Close Override action" )
            win4:Load("Scenes/sheet.ui.txt")
            win4:SetCloseDelegate(true)
            SubscribeToEvent(win4, "AWidgetEditCanceled", "HandleCloseOverrideEvent")
            win4:ResizeToFitContent()
            uiview:AddChild(win4)
            win4:Center()
        end
    end
end

function HandleCloseOverrideEvent(eventType, eventData)
    local widget = eventData["Widget"]:GetPtr("AWidget")
    if widget == nil then
        return
    end
    local mess4 = AMessageWindow:new( uiview, "mymess4")
    SubscribeToEvent(mess4, "WidgetEvent", "HandleCloseYesNoEvent" )
    mess4:Show( "Close Window Request", "Do you really want to close this window?", UI_MESSAGEWINDOW_SETTINGS_YES_NO, false, 0, 0)
end

function HandleCloseYesNoEvent(eventType, eventData)
    local refid = eventData["RefID"]:GetString()
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
        return
    end

    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if refid == "TBMessageWindow.yes" then
            local mywin = widget:FindWidget("WinCloseOverride")
            if mywin ~= nil then
                local wcx = tolua.cast(mywin, "AWindow" )
                if wcx ~= nil then
                    wcx:Close()
                end
            end
        end
        if refid == "TBMessageWindow.no" then
        end
    end
end

