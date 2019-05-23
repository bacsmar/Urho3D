-- ALayout application source code

function setup_uilayout( layout, uiview )
    local dest = layout:SearchAWidgetClass( "TBButton" )
    for i, awid in ipairs(dest) do 
        SubscribeToEvent(awid, "WidgetEvent", "HandleUilayoutEvent")
    end

   local mycw = layout:GetWidget("uilayoutcontainer") -- get the container layout
   local myc = tolua.cast(mycw, "ALayout")

   local tf0 = AButton:new()  -- the layout-o-matic spawner
    tf0:SetText( "LAYOUT-O-MATIC")
    tf0:SetId( "go_layout_config")
    local lo0 = ALayout:new()
    lo0:SetId( "target_layout")
    lo0:SetLayoutConfig ( "-----" )
    lo0:Load("Scenes/simp_button.ui.txt")
    lo0:AddChildBefore(tf0, lo0:GetFirstChild())
    myc:AddChild(lo0)  -- drop it in
    SubscribeToEvent(tf0, "WidgetEvent", "HandleUilayoutEvent" )

    local tf1 = ATextField:new()
    tf1:SetText( "layout config XACAC")
    local lo1 = ALayout:new()
    lo1:SetLayoutConfig ( "XACAC" )
    lo1:Load("Scenes/simp_button.ui.txt")
    lo1:AddChildBefore(tf1, lo1:GetFirstChild())
    myc:AddChild(lo1)

    local tf2 = ATextField:new()
    tf2:SetText( "layout config XGCAC")
    local lo2 = ALayout:new()
    lo2:SetLayoutConfig ( "XGCAC" )
    lo2:Load("Scenes/simp_button.ui.txt")
    lo2:AddChildBefore(tf2, lo2:GetFirstChild())
    myc:AddChild(lo2)

    local tf3 =  ATextField:new()
    tf3:SetText( "layout config XPCAC")
    local lo3 = ALayout:new()
    lo3:SetLayoutConfig ( "XPCAC" )
    lo3:Load("Scenes/simp_button.ui.txt")
    lo3:AddChildBefore(tf3, lo3:GetFirstChild())
    myc:AddChild(lo3)

    local tf4 = ATextField:new()
    tf4:SetText( "layout config XACGC")
    local lo4 = ALayout:new()
    lo4:SetLayoutConfig ( "XACGC" )
    lo4:Load("Scenes/simp_button.ui.txt")
    lo4:AddChildBefore(tf4, lo4:GetFirstChild())
    myc:AddChild(lo4)

    local tf5 =  ATextField:new()
    tf5:SetText( "layout config XGRGC")
    local lo5 = ALayout:new()
    lo5:SetLayoutConfig ( "XGRGC" )
    lo5:Load("Scenes/simp_button.ui.txt")
    lo5:AddChildBefore(tf5, lo5:GetFirstChild())
    myc:AddChild(lo5)

    local tf6 = ATextField:new()
    tf6:SetText( "layout config XPLGC")
    local lo6 = ALayout:new()
    lo6:SetLayoutConfig ( "XPLGC" )
    lo6:Load("Scenes/simp_button.ui.txt")
    lo6:AddChildBefore(tf6, lo6:GetFirstChild())
    myc:AddChild(lo6)

    local tf7 = ATextField:new()
    tf7:SetText( "layout config XACPC")
    local lo7 = ALayout:new()
    lo7:SetLayoutConfig ( "XACPC" )
    lo7:Load("Scenes/simp_button.ui.txt")
    lo7:AddChildBefore(tf7, lo7:GetFirstChild())
    myc:AddChild(lo7)

    local tf8 =  ATextField:new()
    tf8:SetText( "layout config XGLPL")
    local lo8 =  ALayout:new()
    lo8:SetLayoutConfig ( "XGLPL" )
    lo8:Load("Scenes/simp_button.ui.txt")
    lo8:AddChildBefore(tf8, lo8:GetFirstChild())
    myc:AddChild(lo8)

    local tf9 =  ATextField:new()
    tf9:SetText( "layout config XPCPR")
    local lo9 =  ALayout:new()
    lo9:SetLayoutConfig ( "XPCPR" )
    lo9:Load("Scenes/simp_button.ui.txt")
    lo9:AddChildBefore(tf9, lo9:GetFirstChild())
    myc:AddChild(lo9)

   SetGlobalVar("layoutomaticstr", Variant("XGCPC") ) -- LAYOUT-O-MATIC string, cheating, using a globalvar

end

function HandleUilayoutEvent(eventType, eventData)
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
        return
    end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if widget:GetId() == "go_layout_config" then -- its LAYOUT-O-MATIC time:
            AppLog( "ALayout action : " .. widget:GetId() .. " was pressed, its LAYOUT-O-MATIC time")
            local win = AWindow:new()
            win:SetSettings ( UI_WINDOW_SETTINGS_DEFAULT )
            win:SetText( "LAYOUT-O-MATIC(tm)")
            win:Load("Scenes/view_layout.ui.txt")
            win:ResizeToFitContent()
            uiview:AddChild(win)
            local okbutt = win:GetWidget("ok")
            SubscribeToEvent(okbutt, "WidgetEvent", "HandleUilayoutEvent" )
            local dest = win:SearchAWidgetClass( "TBRadioButton" )
            for i, awid in ipairs(dest) do  -- set bulk event handlers on all buttons -- boom!
                SubscribeToEvent(awid, "WidgetEvent", "HandleUilayoutEvent")
            end
        end
        if widget:GetId() ==  "ok" then
            local mywindow = FindTheWindowParent(widget)
            if mywindow ~= nil then
                local w1 = tolua.cast( mywindow, "AWindow")
                w1:Close()
            end
        end
        if widget:GetId() ==  "set_ax" then
            local targetl = widget:FindWidget("target_layout") -- who to operate on:
            if targetl ~= nil then 
                local t1 = tolua.cast( targetl, "ALayout")
                local b1 = tolua.cast( widget, "ARadioButton") -- who we are
                if t1 ~= nil and b1 ~= nil then
                    if b1:GetValue() == 1 then
                        local current = GetGlobalVar("layoutomaticstr"):GetString() -- strings are immutable in lua.
                        local c1 = 'X' -- current[0] = 'X' -- current:Replace (0, 1, "X")
                        local c2 = current:sub (2,2)
                        local c3 = current:sub (3,3)
                        local c4 = current:sub (4,4)
                        local c5 = current:sub (5,5)
                        t1:SetLayoutConfig( c1 .. c2 .. c3 .. c4 .. c5 )
                        SetGlobalVar("layoutomaticstr", Variant(c1 .. c2 .. c3 .. c4 .. c5) )
                    end
                end
            end
        end
        if widget:GetId() == "set_ay" then
            local targetl = widget:FindWidget("target_layout")
            if targetl ~= nil then 
                local t1 = tolua.cast( targetl, "ALayout")
                local b1 = tolua.cast( widget, "ARadioButton")
                if t1 ~= nil and b1 ~= nil then
                    if b1:GetValue() == 1 then
                        local current = GetGlobalVar("layoutomaticstr"):GetString()
                        local c1 = 'Y'
                        local c2 = current:sub (2,2)
                        local c3 = current:sub (3,3)
                        local c4 = current:sub (4,4)
                        local c5 = current:sub (5,5)
                        t1:SetLayoutConfig( c1 .. c2 .. c3 .. c4 .. c5 )
                        SetGlobalVar("layoutomaticstr", Variant(c1 .. c2 .. c3 .. c4 .. c5) )
                    end
                end
            end
        end
        if widget:GetId() == "set_sza" then
            local targetl = widget:FindWidget("target_layout")
            if targetl ~= nil then 
                local t1 = tolua.cast( targetl, "ALayout")
                local b1 = tolua.cast( widget, "ARadioButton")
                if t1 ~= nil and b1 ~= nil then
                    if b1:GetValue() == 1 then
                        local current = GetGlobalVar("layoutomaticstr"):GetString()
                        local c1 = current:sub (1,1)
                        local c2 = 'A'
                        local c3 = current:sub (3,3)
                        local c4 = current:sub (4,4)
                        local c5 = current:sub (5,5)
                        t1:SetLayoutConfig( c1 .. c2 .. c3 .. c4 .. c5 )
                        SetGlobalVar("layoutomaticstr", Variant(c1 .. c2 .. c3 .. c4 .. c5) )
                    end
                end
            end
        end
        if widget:GetId() == "set_szg" then
            local targetl = widget:FindWidget("target_layout")
            if targetl ~= nil then 
                local t1 = tolua.cast( targetl, "ALayout")
                local b1 = tolua.cast( widget, "ARadioButton")
                if t1 ~= nil and b1 ~= nil then
                    if b1:GetValue() == 1 then
                        local current = GetGlobalVar("layoutomaticstr"):GetString()
                        local c1 = current:sub (1,1)
                        local c2 = 'G'
                        local c3 = current:sub (3,3)
                        local c4 = current:sub (4,4)
                        local c5 = current:sub (5,5)
                        t1:SetLayoutConfig( c1 .. c2 .. c3 .. c4 .. c5 )
                        SetGlobalVar("layoutomaticstr", Variant(c1 .. c2 .. c3 .. c4 .. c5) )
                    end
                end
            end
        end
        if widget:GetId() == "set_szp" then
            local targetl = widget:FindWidget("target_layout") -- who to operate on:
            if targetl ~= nil then 
                local t1 = tolua.cast( targetl, "ALayout")
                local b1 = tolua.cast( widget, "ARadioButton") -- who we are
                if t1 ~= nil and b1 ~= nil then
                    if b1:GetValue() == 1 then
                        local current = GetGlobalVar("layoutomaticstr"):GetString()
                        local c1 = current:sub (1,1)
                        local c2 = 'P'
                        local c3 = current:sub (3,3)
                        local c4 = current:sub (4,4)
                        local c5 = current:sub (5,5)
                        t1:SetLayoutConfig( c1 .. c2 .. c3 .. c4 .. c5 )
                        SetGlobalVar("layoutomaticstr", Variant(c1 .. c2 .. c3 .. c4 .. c5) )
                    end
                end
            end
        end

        if widget:GetId() == "set_posc" then
            local targetl = widget:FindWidget("target_layout") -- who to operate on:
            if targetl ~= nil then 
                local t1 = tolua.cast( targetl, "ALayout")
                local b1 = tolua.cast( widget, "ARadioButton") -- who we are
                if t1 ~= nil and b1 ~= nil then
                    if b1:GetValue() == 1 then
                        local current = GetGlobalVar("layoutomaticstr"):GetString()
                        local c1 = current:sub (1,1)
                        local c2 = current:sub (2,2)
                        local c3 = 'C'
                        local c4 = current:sub (4,4)
                        local c5 = current:sub (5,5)
                        t1:SetLayoutConfig( c1 .. c2 .. c3 .. c4 .. c5 )
                        SetGlobalVar("layoutomaticstr", Variant(c1 .. c2 .. c3 .. c4 .. c5) )
                    end
                end
            end
        end
        if widget:GetId() == "set_posg" then
            local targetl = widget:FindWidget("target_layout") -- who to operate on:
            if targetl ~= nil then 
                local t1 = tolua.cast( targetl, "ALayout")
                local b1 = tolua.cast( widget, "ARadioButton") -- who we are
                if t1 ~= nil and b1 ~= nil then
                    if b1:GetValue() == 1 then
                        local current = GetGlobalVar("layoutomaticstr"):GetString()
                        local c1 = current:sub (1,1)
                        local c2 = current:sub (2,2)
                        local c3 = 'G'
                        local c4 = current:sub (4,4)
                        local c5 = current:sub (5,5)
                        t1:SetLayoutConfig( c1 .. c2 .. c3 .. c4 .. c5 )
                        SetGlobalVar("layoutomaticstr", Variant(c1 .. c2 .. c3 .. c4 .. c5) )
                    end
                end
            end
        end
        if widget:GetId() == "set_posl" then
            local targetl = widget:FindWidget("target_layout") -- who to operate on:
            if targetl ~= nil then 
                local t1 = tolua.cast( targetl, "ALayout")
                local b1 = tolua.cast( widget, "ARadioButton") -- who we are
                if t1 ~= nil and b1 ~= nil then
                    if b1:GetValue() == 1 then
                        local current = GetGlobalVar("layoutomaticstr"):GetString()
                        local c1 = current:sub (1,1)
                        local c2 = current:sub (2,2)
                        local c3 = 'L'
                        local c4 = current:sub (4,4)
                        local c5 = current:sub (5,5)
                        t1:SetLayoutConfig( c1 .. c2 .. c3 .. c4 .. c5 )
                        SetGlobalVar("layoutomaticstr", Variant(c1 .. c2 .. c3 .. c4 .. c5) )
                    end
                end
            end
        end
        if widget:GetId() == "set_posr" then
            local targetl = widget:FindWidget("target_layout") -- who to operate on:
            if targetl ~= nil then 
                local t1 = tolua.cast( targetl, "ALayout")
                local b1 = tolua.cast( widget, "ARadioButton") -- who we are
                if t1 ~= nil and b1 ~= nil then
                    if b1:GetValue() == 1 then
                        local current = GetGlobalVar("layoutomaticstr"):GetString()
                        local c1 = current:sub (1,1)
                        local c2 = current:sub (2,2)
                        local c3 = 'R'
                        local c4 = current:sub (4,4)
                        local c5 = current:sub (5,5)
                        t1:SetLayoutConfig( c1 .. c2 .. c3 .. c4 .. c5 )
                        SetGlobalVar("layoutomaticstr", Variant(c1 .. c2 .. c3 .. c4 .. c5) )
                    end
                end
            end
        end

        if widget:GetId() == "set_dista" then
            local targetl = widget:FindWidget("target_layout") -- who to operate on:
            if targetl ~= nil then 
                local t1 = tolua.cast( targetl, "ALayout")
                local b1 = tolua.cast( widget, "ARadioButton") -- who we are
                if t1 ~= nil and b1 ~= nil then
                    if b1:GetValue() == 1 then
                        local current = GetGlobalVar("layoutomaticstr"):GetString()
                        local c1 = current:sub (1,1)
                        local c2 = current:sub (2,2)
                        local c3 = current:sub (3,3)
                        local c4 = 'A'
                        local c5 = current:sub (5,5)
                        t1:SetLayoutConfig( c1 .. c2 .. c3 .. c4 .. c5 )
                        SetGlobalVar("layoutomaticstr", Variant(c1 .. c2 .. c3 .. c4 .. c5) )
                    end
                end
            end
        end
        if widget:GetId() ==  "set_distg" then
            local targetl = widget:FindWidget("target_layout") -- who to operate on:
            if targetl ~= nil then 
                local t1 = tolua.cast( targetl, "ALayout")
                local b1 = tolua.cast( widget, "ARadioButton") -- who we are
                if t1 ~= nil and b1 ~= nil then
                    if b1:GetValue() == 1 then
                        local current = GetGlobalVar("layoutomaticstr"):GetString()
                        local c1 = current:sub (1,1)
                        local c2 = current:sub (2,2)
                        local c3 = current:sub (3,3)
                        local c4 = 'G'
                        local c5 = current:sub (5,5)
                        t1:SetLayoutConfig( c1 .. c2 .. c3 .. c4 .. c5 )
                        SetGlobalVar("layoutomaticstr", Variant(c1 .. c2 .. c3 .. c4 .. c5) )
                    end
                end
            end
        end
        if widget:GetId() ==  "set_distp" then
            local targetl = widget:FindWidget("target_layout") -- who to operate on:
            if targetl ~= nil then 
                local t1 = tolua.cast( targetl, "ALayout")
                local b1 = tolua.cast( widget, "ARadioButton") -- who we are
                if t1 ~= nil and b1 ~= nil then
                    if b1:GetValue() == 1 then
                        local current = GetGlobalVar("layoutomaticstr"):GetString()
                        local c1 = current:sub (1,1)
                        local c2 = current:sub (2,2)
                        local c3 = current:sub (3,3)
                        local c4 = 'P'
                        local c5 = current:sub (5,5)
                        t1:SetLayoutConfig( c1 .. c2 .. c3 .. c4 .. c5 )
                        SetGlobalVar("layoutomaticstr", Variant(c1 .. c2 .. c3 .. c4 .. c5) )
                    end
                end
            end
        end

        if widget:GetId() == "set_dpc" then
            local targetl = widget:FindWidget("target_layout") -- who to operate on:
            if targetl ~= nil then 
                local t1 = tolua.cast( targetl, "ALayout")
                local b1 = tolua.cast( widget, "ARadioButton") -- who we are
                if t1 ~= nil and b1 ~= nil then
                    if b1:GetValue() == 1 then
                        local current = GetGlobalVar("layoutomaticstr"):GetString()
                        local c1 = current:sub (1,1)
                        local c2 = current:sub (2,2)
                        local c3 = current:sub (3,3)
                        local c4 = current:sub (4,4)
                        local c5 = 'C'
                        t1:SetLayoutConfig( c1 .. c2 .. c3 .. c4 .. c5 )
                        SetGlobalVar("layoutomaticstr", Variant(c1 .. c2 .. c3 .. c4 .. c5) )
                    end
                end
            end
        end
        if widget:GetId() ==  "set_dpl" then
            local targetl = widget:FindWidget("target_layout") -- who to operate on:
            if targetl ~= nil then 
                local t1 = tolua.cast( targetl, "ALayout")
                local b1 = tolua.cast( widget, "ARadioButton") -- who we are
                if t1 ~= nil and b1 ~= nil then
                    if b1:GetValue() == 1 then
                        local current = GetGlobalVar("layoutomaticstr"):GetString()
                        local c1 = current:sub (1,1)
                        local c2 = current:sub (2,2)
                        local c3 = current:sub (3,3)
                        local c4 = current:sub (4,4)
                        local c5 = 'L'
                        t1:SetLayoutConfig( c1 .. c2 .. c3 .. c4 .. c5 )
                        SetGlobalVar("layoutomaticstr", Variant(c1 .. c2 .. c3 .. c4 .. c5) )
                    end
                end
            end
        end
        if widget:GetId() ==  "set_dpr" then
            local targetl = widget:FindWidget("target_layout") -- who to operate on:
            if targetl ~= nil then 
                local t1 = tolua.cast( targetl, "ALayout")
                local b1 = tolua.cast( widget, "ARadioButton") -- who we are
                if t1 ~= nil and b1 ~= nil then
                    if b1:GetValue() == 1 then
                        local current = GetGlobalVar("layoutomaticstr"):GetString()
                        local c1 = current:sub (1,1)
                        local c2 = current:sub (2,2)
                        local c3 = current:sub (3,3)
                        local c4 = current:sub (4,4)
                        local c5 = 'R'
                        t1:SetLayoutConfig( c1 .. c2 .. c3 .. c4 .. c5 )
                        SetGlobalVar("layoutomaticstr", Variant(c1 .. c2 .. c3 .. c4 .. c5) )
                    end
                end
            end
        end
    end
end

