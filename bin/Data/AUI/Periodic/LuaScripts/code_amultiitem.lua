-- AMultiItem and AMultiItemSource application source code

-- a global, persist this way, wouldnt do it thru a SetGlobalVar
mmmis = nil

function setup_uimultiitem( layout )
    local dest = layout:SearchAWidgetClass( "TBButton" )
    for i, awid in ipairs(dest) do
        SubscribeToEvent(awid, "WidgetEvent", "HandleUimultiitemEvent")
	end

    local mylist = ASelectList:new() -- uses a regular ASelectList to hold the multilist items
    mylist:SetId("AMultiItemList")   -- tag it, in case we want to get it again later
    local lpx = ALayoutParams:new()
    lpx:SetWidth (200)
    lpx:SetHeight(256)
    lpx:SetMinWidth(200)
    lpx:SetMinHeight(256)
    lpx:SetMaxWidth (200)
    lpx:SetMaxHeight(256)
    mylist:SetLayoutParams(lpx)
    mylist:SetLayoutParams(lpx)
    local lower = layout:GetWidget("multiitemlower")
    local mysvc = layout:GetWidget("multiitemlayout")
    mysvc:AddChildBefore(mylist, lower)
    SubscribeToEvent(mylist, "WidgetEvent", "HandleUimultiitemEvent" )

    local xis = AMultiItemSource:new()
    local mi1 = AMultiItem:new( "sitem1", "TEXT", "AMultiItem1", 88, 0 )
    mi1:AddColumn ( "TEXT", "Col2", 44 )
    mi1:AddColumn ( "TEXT", "Col3", 44 )
    xis:AddItem(mi1)
    local mi2 = AMultiItem:new( "sitem2", "TEXT", "AMultiItem2",  88, 0 )
    mi2:AddColumn ( "TEXT", "Col4", 44 )
    mi2:AddColumn ( "TEXT", "Col5", 44 )
    xis:AddItem(mi2)
    local mi3 = AMultiItem:new( "sitem3", "TEXT", "AMultiItem3",  88, 0 )
    mi3:AddColumn ( "TEXT", "Col6", 44 )
    mi3:AddColumn ( "TEXT", "Col7", 44 )
    xis:AddItem(mi3)
    local mi4 = AMultiItem:new( "sitem4", "TEXT", "AMultiItem4",  88, 0 )
    mi4:AddColumn ( "TEXT", "Col8", 44 )
    mi4:AddColumn ( "TEXT", "FAIL", 44 )
    xis:AddItem(mi4)

    mylist:SetSource(xis)

	mmmis = xis
end

function HandleUimultiitemEvent( eventType, eventData)
    local refid = eventData["RefID"]:GetString()
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
 		return
	end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if widget:GetId() == "uimultiitemcode" then
            AppLog( "AMultiItem support : " .. widget:GetId() .. " was pressed " )
            ViewCode ( "LuaScripts/code_amultiitem.lua", widget:GetParent())
        end
        if widget:GetId() == "uimultiitemlayout" then
            AppLog( "ASelectItem support : " .. widget:GetId() .. " was pressed ")
            ViewCode ( "Scenes/layout_amultiitem.ui.txt", widget:GetParent())
        end
        if widget:GetId() ==  "AMultiItemList" then
            AppLog( "AMultiItemList event : " .. widget:GetId() .. " and " .. refid .. " was selected ")
        end
        if widget:GetId() ==  "uimi1" then
            AppLog( "AMultiItem1 action : " .. widget:GetId() .. " was pressed ")
            local slist = widget:FindWidget("AMultiItemList")
            if slist ~= nil then
				local sl2 = tolua.cast(slist, "ASelectList")
                if mmmis ~= nil then
                    local mi1 = AMultiItem:new( "sitem1", "TEXT", " MultiItem", 88, 0 )
                    mi1:AddColumn ( "TEXT", "Col2", 44 )
                    mi1:AddColumn ( "TEXT", "Col3", 44 )
                    mmmis:AddItem(mi1)
                    sl2:SetSource(mmmis)
                end
            end
        end
        if widget:GetId() ==  "uimi2" then
            AppLog( "AMultiItem action : " .. widget:GetId() .. " was pressed")
            local slist = widget:FindWidget("AMultiItemList")
            if slist ~= nil then
				local sl2 = tolua.cast(slist, "ASelectList")
                if mmmis ~= nil then
            		local mi2 = AMultiItem:new( "sitem2", "TEXT", "Another Item",  88, 0 )
            		mi2:AddColumn ( "COLOR", "#3333FF", 44 )
            		mi2:AddColumn ( "TEXT", "Col5", 44 )
            		mmmis:AddItem(mi2)
            		sl2:SetSource(mmmis)
				end
			end
        end
        if widget:GetId() ==  "uimi3" then
            AppLog( "AMultiItem action : " .. widget:GetId() .. " was pressed ")
            local slist = widget:FindWidget("AMultiItemList")
            if slist ~= nil then
				local sl2 = tolua.cast(slist, "ASelectList")
                if mmmis ~= nil then
             		local mi3 = AMultiItem( "Duck", "ICON", "DuckButton", 88, 0 )
            		mi3:AddColumn ( "TEXT", "Col6", 44 )
            		mi3:AddColumn ( "TEXT", "Col7", 44 )
            		mmmis:AddItem(mi3)
            		sl2:SetSource(mmmis)
				end
			end
        end
        if widget:GetId() ==  "uimi4" then
            AppLog( "AMultiItem action : " .. widget:GetId() .. " was pressed ")
            local slist = widget:FindWidget("AMultiItemList")
            if slist ~= nil then
				local sl2 = tolua.cast(slist, "ASelectList")
                if mmmis ~= nil then
            		local mi4 = AMultiItem:new( "Atomic", "ICON", "LogoAtomic", 88,0 )
            		mi4:AddColumn ( "TEXT", "Col8", 44 )
            		mi4:AddColumn ( "TEXT", "Col9", 44 )
            		mmmis:AddItem(mi4)
            		sl2:SetSource(mmmis)
				end
			end
        end
        if widget:GetId() ==  "uimi5" then
            AppLog( "AMultiItem action : " .. widget:GetId() .. " was pressed ")
            local slist = widget:FindWidget("AMultiItemList")
            if slist ~= nil then
				local sl2 = tolua.cast(slist, "ASelectList")
                if mmmis ~= nil then
             		mmmis:Clear()
            		sl2:SetSource(mmmis)
				end
			end
        end
    end
end

