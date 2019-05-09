-- handle the periodic table jumps

function setup_table(mylayout) 
    local pgtable = mylayout:GetWidget( "pagetable")
    dest = pgtable:SearchAWidgetClass( "TBButton" )
    for i, awid in ipairs(dest) do
        SubscribeToEvent(awid, "WidgetEvent", "HandleTableEvent")
	end
end

function HandleTableEvent(eventType, eventData)

--    URHO3D_PARAM(P_HANDLER, Handler)           -- AWidget pointer of widget's OnEvent we are in
--    URHO3D_PARAM(P_TARGET, Target)             -- AWidget pointer
--    URHO3D_PARAM(P_TYPE, Type)                 -- enum UI_EVENT_TYPE
--    URHO3D_PARAM(P_X, X)                       -- int
--    URHO3D_PARAM(P_Y, Y)                       -- int
--    URHO3D_PARAM(P_DELTAX, DeltaX)             -- int
--    URHO3D_PARAM(P_DELTAY, DeltaY)             -- int
--    URHO3D_PARAM(P_COUNT, Count)               -- int
--    URHO3D_PARAM(P_KEY, Key)                   -- int
--    URHO3D_PARAM(P_SPECIALKEY, SpecialKey)     -- enum SPECIAL_KEY
--    URHO3D_PARAM(P_MODIFIERKEYS, ModifierKeys) -- enum MODIFIER_KEYS
--    URHO3D_PARAM(P_REFID, RefID)               -- string (TBID)
--    URHO3D_PARAM(P_TOUCH, Touch)               -- bool
-- EventHandled can be set by event receivers to stop event bubble
--    URHO3D_PARAM(P_HANDLED, Handled)               -- [OUT] -> bool

    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
		return
	end
    if (eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK) then
	   	local maintb = tolua.cast(uiview:FindWidget("maintabs"), "ATabContainer")
    	local acttb = tolua.cast(uiview:FindWidget("primarytabs"), "ATabContainer")
    	local semitb = tolua.cast(uiview:FindWidget("moretabs"), "ATabContainer")
    	local viewtb = tolua.cast(uiview:FindWidget("supporttabs"), "ATabContainer")
    	local supporttb = tolua.cast(uiview:FindWidget("atomictabs"), "ATabContainer")

        if widget:GetId() ==  "A1" then
            maintb:SetCurrentPage(1)
            acttb:SetCurrentPage(0)
        end
        if widget:GetId() ==  "A2" then
            maintb:SetCurrentPage(1)
            acttb:SetCurrentPage(1)
        end
        if widget:GetId() ==  "A3" then
            maintb:SetCurrentPage(1)
            acttb:SetCurrentPage(2)
        end
        if widget:GetId() ==  "A4" then
            maintb:SetCurrentPage(1)
            acttb:SetCurrentPage(3)
        end
        if widget:GetId() ==  "A5" then
            maintb:SetCurrentPage(1)
            acttb:SetCurrentPage(4)
        end
        if widget:GetId() ==  "A6" then
            maintb:SetCurrentPage(1)
            acttb:SetCurrentPage(5)
        end
        if widget:GetId() ==  "A7" then
            maintb:SetCurrentPage(1)
            acttb:SetCurrentPage(6)
        end
        if widget:GetId() ==  "A8" then
            maintb:SetCurrentPage(1)
            acttb:SetCurrentPage(7)
        end
        if widget:GetId() ==  "A9" then
            maintb:SetCurrentPage(1)
            acttb:SetCurrentPage(8)
        end

        if widget:GetId() ==  "B1" then
            maintb:SetCurrentPage(2)
            semitb:SetCurrentPage(0)
        end
        if widget:GetId() ==  "B2" then
            maintb:SetCurrentPage(2)
            semitb:SetCurrentPage(1)
        end
        if widget:GetId() ==  "B3" then
            maintb:SetCurrentPage(2)
            semitb:SetCurrentPage(2)
        end
        if widget:GetId() ==  "B4" then
            maintb:SetCurrentPage(2)
            semitb:SetCurrentPage(3)
        end
        if widget:GetId() ==  "B5" then
            maintb:SetCurrentPage(2)
            semitb:SetCurrentPage(4)
        end
        if widget:GetId() ==  "B6" then
            maintb:SetCurrentPage(2)
            semitb:SetCurrentPage(5)
        end
        if widget:GetId() ==  "B7" then
            maintb:SetCurrentPage(2)
            semitb:SetCurrentPage(6)
        end
        if widget:GetId() ==  "B8" then
            maintb:SetCurrentPage(2)
            semitb:SetCurrentPage(7)
        end
        if widget:GetId() ==  "B9" then
            maintb:SetCurrentPage(2)
            semitb:SetCurrentPage(8)
        end

        if widget:GetId() ==  "C1" then
            maintb:SetCurrentPage(3)
            viewtb:SetCurrentPage(0)
        end
        if widget:GetId() ==  "C2" then
            maintb:SetCurrentPage(3)
            viewtb:SetCurrentPage(1)
        end
        if widget:GetId() ==  "C3" then
            maintb:SetCurrentPage(3)
            viewtb:SetCurrentPage(2)
        end
        if widget:GetId() ==  "C4" then
            maintb:SetCurrentPage(3)
            viewtb:SetCurrentPage(3)
        end
        if widget:GetId() ==  "C5" then
            maintb:SetCurrentPage(3)
            viewtb:SetCurrentPage(4)
        end
        if widget:GetId() ==  "C6" then
            maintb:SetCurrentPage(3)
            viewtb:SetCurrentPage(5)
        end
        if widget:GetId() ==  "C7" then
            maintb:SetCurrentPage(3)
            viewtb:SetCurrentPage(6)
        end
        if widget:GetId() ==  "C8" then
            maintb:SetCurrentPage(3)
            viewtb:SetCurrentPage(7)
        end
        if widget:GetId() ==  "C9" then
            maintb:SetCurrentPage(3)
            viewtb:SetCurrentPage(8)
        end

        if widget:GetId() ==  "D1" then
            maintb:SetCurrentPage(4)
            supporttb:SetCurrentPage(0)
        end
        if widget:GetId() ==  "D2" then
            maintb:SetCurrentPage(4)
            supporttb:SetCurrentPage(1)
        end
        if widget:GetId() ==  "D3" then
            maintb:SetCurrentPage(4)
            supporttb:SetCurrentPage(2)
        end
        if widget:GetId() ==  "D4" then
            maintb:SetCurrentPage(4)
            supporttb:SetCurrentPage(3)
        end
        if widget:GetId() ==  "D5" then
            maintb:SetCurrentPage(4)
            supporttb:SetCurrentPage(4)
        end
        if widget:GetId() ==  "D6" then
            maintb:SetCurrentPage(4)
            supporttb:SetCurrentPage(5)
        end
        if widget:GetId() ==  "D7" then
            maintb:SetCurrentPage(4)
            supporttb:SetCurrentPage(6)
        end
        if widget:GetId() ==  "D8" then
            maintb:SetCurrentPage(4)
            supporttb:SetCurrentPage(7)
        end
        if widget:GetId() ==  "D9" then
            maintb:SetCurrentPage(4)
            supporttb:SetCurrentPage(8)
        end
    end
end

