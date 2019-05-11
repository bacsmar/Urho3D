-- ASelectItem and ASelectItemSource application source code


function setup_uiselectitem( layout )
    local dest = layout:SearchAWidgetClass( "TBButton" )
    for i, awid in ipairs(dest) do
        SubscribeToEvent(awid, "WidgetEvent", "HandleUiselectitemEvent")
	end

    local mylist = ASelectList:new()
    mylist:SetId( "ASelectItemList")
    local lpx = ALayoutParams:new()
    lpx:SetWidth (200)
    lpx:SetHeight(256)
    lpx:SetMinWidth(200)
    lpx:SetMinHeight(256)
    lpx:SetMaxWidth (200)
    lpx:SetMaxHeight(256)
    mylist:SetLayoutParams(lpx)
    local lower = layout:GetWidget("selectitemlower")
    local mysvc = layout:GetWidget("selectitemlayout")
    mysvc:AddChildBefore(mylist, lower)
    SubscribeToEvent(mylist, "WidgetEvent", "HandleUiselectitemEvent" )

    local sis = ASelectItemSource:new()
    sis:AddItem( ASelectItem:new( "ASelectItem1", "sitem1", "" ) )
    sis:AddItem( ASelectItem:new( "ASelectItem2", "sitem2", "" ) )
    sis:AddItem( ASelectItem:new( "ASelectItem3", "sitem3", "DuckButton" ) )
    sis:AddItem( ASelectItem:new( "ASelectItem4", "sitem4", "LogoAtomic" ) )
    mylist:SetSource(sis)
    SetGlobalVar( "selectitemptr", Variant(sis) )  -- make a global reference:
end

function HandleUiselectitemEvent(eventType, eventData)
    local refid = eventData["RefID"]:GetString()
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
 		return
	end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if widget:GetId() == "uiselectitemcode" then
            AppLog( "ASelectItem support : " .. widget:GetId() .. " was pressed " )
            ViewCode ( "LuaScripts/code_aselectitem.lua", widget:GetParent())
        end
        if widget:GetId() ==  "uiselectitemlayout" then
            AppLog( "ASelectItem support : " .. widget:GetId() .. " was pressed ")
            ViewCode ( "Scenes/layout_aselectitem.ui.txt", widget:GetParent())
        end

        if widget:GetId() ==  "ASelectItemList" then
            AppLog( "ASelectItem event : " .. widget:GetId() .. " and " .. refid .. " was selected ")
        end

        if widget:GetId() ==  "uisi1" then
            AppLog( "ASelectItem action : " .. widget:GetId() .. " was pressed ")
            local gsis = GetGlobalVar("selectitemptr"):GetPtr("ASelectItemSource")
            local slist = widget:FindWidget("ASelectItemList")
			if slist ~= nil then
				local s1 = tolua.cast(slist, "ASelectList" )
				if s1 ~= nil then
            		gsis:AddItem( ASelectItem:new( "New ASelectItem", "newitemx", "") )
            		s1:SetSource(gsis)
				end
			end
        end
        if widget:GetId() ==  "uisi2" then
            AppLog( "ASelectItem action : " .. widget:GetId() .. " was pressed ")
            local gsis = GetGlobalVar("selectitemptr"):GetPtr("ASelectItemSource")
            local slist = widget:FindWidget("ASelectItemList") 
			if slist ~= nil then
				local s1 = tolua.cast(slist, "ASelectList" )
				if s1 ~= nil then
            		gsis:AddItem( ASelectItem:new( "Newer ASelectItem", "eritem", "" ) )
            		s1:SetSource(gsis)
				end
			end
        end
        if widget:GetId() ==  "uisi3" then
            AppLog( "ASelectItem action : " .. widget:GetId() .. " was pressed ")
            local gsis = GetGlobalVar("selectitemptr"):GetPtr("ASelectItemSource")
            local slist = widget:FindWidget("ASelectItemList")
			if slist ~= nil then
				local s1 = tolua.cast(slist, "ASelectList" )
				if s1 ~= nil then
            		gsis:AddItem( ASelectItem:new( "A Duck", "aduck", "DuckButton" ) )
            		s1:SetSource(gsis)
				end
			end
        end
        if widget:GetId() ==  "uisi4" then
            AppLog( "ASelectItem action : " .. widget:GetId() .. " was pressed ")
            local gsis = GetGlobalVar("selectitemptr"):GetPtr("ASelectItemSource")
            local slist = widget:FindWidget("ASelectItemList")
			if slist ~= nil then
				local s1 = tolua.cast(slist, "ASelectList" )
				if s1 ~= nil then
            		gsis:AddItem( ASelectItem:new( "Atomic!", "atomic", "LogoAtomic" ) )
            		s1:SetSource(gsis)
				end
			end
        end
        if widget:GetId() ==  "uisi5" then
            AppLog( "ASelectItem action : " .. widget:GetId() .. " was pressed ")
            local gsis = GetGlobalVar("selectitemptr"):GetPtr("ASelectItemSource")
            local slist = widget:FindWidget("ASelectItemList")
			if slist ~= nil then
				local s1 = tolua.cast(slist, "ASelectList" )
				if s1 ~= nil then
            		gsis:Clear()
            		s1:SetSource(gsis)
				end
			end
        end
    end
end

