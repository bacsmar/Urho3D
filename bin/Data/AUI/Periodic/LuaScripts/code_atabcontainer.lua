-- ATabContainer application source code


function setup_uitabcontainer( layout )
    local dest = layout:SearchAWidgetClass( "TBButton" )
    for i, awid in ipairs(dest) do
        SubscribeToEvent(awid, "WidgetEvent", "HandleUitabcontainerEvent")
    end
    local tcxraw = layout:GetWidget("ATabContainerDemo") 
    SubscribeToEvent(tcxraw, "WidgetEvent", "HandleAllTabcontainerEvent" )
    if tcxraw ~= nil then
        local tcx = tolua.cast(tcxraw, "ATabContainer" )
        if tcx ~= nil then
            tcx:SetCurrentPage(0)  -- fix or it looks like crap
        end
    end
end

function HandleAllTabcontainerEvent(eventType, eventData)
    local refid = eventData["RefID"]:GetString()
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
        return
    end

    local demo = widget:FindWidget("ATabContainerDemo") -- find our specific widget
    if widget ~= demo then
        return -- if its not ours, bail
    end

    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_TAB_CHANGED then
        if widget:GetId() ==  "ATabContainerDemo" then
          local tcx = tolua.cast( widget, "ATabContainer")  -- check the focus & stuff, or it gets a little spammy
            if tcx ~= nil and tcx:GetState(UI_WIDGET_STATE_FOCUSED) == true then
                AppLog( "ATabContainer event : " .. widget:GetId() .. " UI_EVENT_TYPE_TAB_CHANGED to " ..  tcx:GetCurrentPage() .. " id: " .. tcx:GetCurrentPageWidget():GetId() )
            end
        end
    end
end


function HandleUitabcontainerEvent( eventType, eventData)
    local refid = eventData["RefID"]:GetString()
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
        return
    end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if widget:GetId() == "uitabcontainercode" then
            AppLog( "ATabContainer support : " .. widget:GetId() .. " was pressed " )
            ViewCode ( "LuaScripts/code_atabcontainer.lua", widget:GetParent())
        end
        if widget:GetId() ==  "uitabcontainerlayout" then
            AppLog( "ATabContainer support : " .. widget:GetId() .. " was pressed ")
            ViewCode ( "Scenes/layout_atabcontainer.ui.txt", widget:GetParent())
        end

        if widget:GetId() ==  "uitabcontainerremove" then
            AppLog( "ATabContainer action : " .. widget:GetId() .. " was pressed ")
            local tcxraw = widget:FindWidget("ATabContainerDemo")
            if tcxraw ~= nil then
                local tcx = tolua.cast(tcxraw, "ATabContainer" )
                if tcx ~= nil then
                    local current = tcx:GetCurrentPage()
                    tcx:DeletePage(current)
                end
            end
        end
        if widget:GetId() ==  "uitabcontaineradd" then
            AppLog( "ATabContainer action : " .. widget:GetId() .. " was pressed ")
            local tcxraw = widget:FindWidget("ATabContainerDemo")
            if tcxraw ~= nil then
                local tcx = tolua.cast(tcxraw, "ATabContainer" )
                if tcx ~= nil then
                    tcx:AddTabPageFile("New File", "Scenes/sheet.ui.txt" )
                end
            end
        end
        if widget:GetId() ==  "uitabcontainermake" then
            AppLog( "ATabContainer action : " .. widget:GetId() .. " was pressed ")
            local tcxraw = widget:FindWidget("ATabContainerDemo")
            if tcxraw ~= nil then
                local tcx = tolua.cast(tcxraw, "ATabContainer" )
                if tcx ~= nil then
                    local lo = ALayout:new()
                    lo:SetLayoutConfig ( "YAGAC" )  -- YACAC!
                    local myeditfield = AEditField:new()
                    myeditfield:SetGravity( UI_GRAVITY_ALL)
                    myeditfield:SetMultiline(true)
                    local filex = cache:GetFile("LuaScripts/code_atabcontainer.lua")
                    local textx = filex:ReadString()
                    filex:Close()
                    myeditfield:SetText(textx)
                    local myfont = AFontDescription:new() -- put in a coder font
                    myfont:SetSize(16)
                    myfont:SetId("Vera")
                    myeditfield:SetFontDescription (myfont)
                    lo:AddChild (myeditfield)
                    tcx:AddTabPageWidget("New Code", lo)
                end
            end
        end
        if widget:GetId() ==  "uitabcontainerundock" then
            AppLog( "ATabContainer action : " .. widget:GetId() .. " was pressed ")
            local tcxraw = widget:FindWidget("ATabContainerDemo")
            if tcxraw ~= nil then
                local tcx = tolua.cast(tcxraw, "ATabContainer" )
                if tcx ~= nil then
                    local current = tcx:GetCurrentPage()
                    tcx:UndockPage(current)
                end
            end
        end
        if widget:GetId() == "uitabcontainerredock" then
            AppLog( "ATabContainer action : " .. widget:GetId() .. " was pressed ")
            local tcxraw = widget:FindWidget("ATabContainerDemo")
            if tcxraw ~= nil then
                local tcx = tolua.cast(tcxraw, "ATabContainer" )
                if tcx ~= nil then
                    if tcx:DockWindow ( "tab1" ) == false then
                        if tcx:DockWindow ( "tab2" ) == false  then
                            if tcx:DockWindow ( "tab3" ) == false  then
                                if tcx:DockWindow ( "New File" ) == false  then
                                    if tcx:DockWindow ( "New Code" )== false  then
                                        AppLog( "ATabContainer action : no more windows to dock:")
                                    end
                                end
                            end
                        end
                    end
                end
            end
        end
    end
end

