-- ASelectList application source code

function setup_uiselectlist( layout )
    local dest = layout:SearchAWidgetClass( "TBButton" )
    for i, awid in ipairs(dest) do 
        SubscribeToEvent(awid, "WidgetEvent", "HandleUiselectlistEvent")
	end

    local slist = layout:GetWidget ("ASelectListDemo")
    if slist ~= nil then
        SubscribeToEvent(slist, "WidgetEvent", "HandleUiselectlistEvent" )
	end
end

function HandleUiselectlistEvent(eventType, eventData)
    local refid = eventData["RefID"]:GetString()
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
 		return
	end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if widget:GetId() == "uiselectlistcode" then
            AppLog( "ASelectList support : " .. widget:GetId() .. " was pressed " )
            ViewCode ( "LuaScripts/code_aselectlist.lua", widget:GetParent())
        end
        if widget:GetId() ==  "uiselectlistlayout" then
            AppLog( "ASelectList support : " .. widget:GetId() .. " was pressed ")
            ViewCode ( "Scenes/layout_aselectlist.ui.txt", widget:GetParent())
        end

        if widget:GetId() ==  "ASelectListDemo" then
            AppLog( "ASelectList event : " .. widget:GetId() .. " and " .. refid .. " was selected ")
        end

        if widget:GetId() ==  "selectlistadd" then
            AppLog( "ASelectList action : " .. widget:GetId() .. " was pressed ")
            local slist = widget:FindWidget("ASelectListDemo")
			if slist ~= nil then
				local s1 = tolua.cast(slist, "ASelectList" )
				if s1 ~= nil then
            		s1:AddItem( s1:GetNumItems(), "New Entry", "newentry" .. s1:GetNumItems())
				end
			end
        end
        if widget:GetId() ==  "selectlistdel" then
            AppLog( "ASelectList action : " .. widget:GetId() .. " was pressed ")
            local slist = widget:FindWidget("ASelectListDemo") 
			if slist ~= nil then
				local s1 = tolua.cast(slist, "ASelectList" )
				if s1 ~= nil then
            		-- Float value truncated in implicit conversion to integer
            		local si = math.floor(s1:GetValue()) -- this is the selected index
            		s1:DeleteItem(si)
				end
			end
        end
        if widget:GetId() ==  "selectlistdelall" then
            AppLog( "ASelectList action : " .. widget:GetId() .. " was pressed ")
            local slist = widget:FindWidget("ASelectListDemo")
			if slist ~= nil then			
				local s1 = tolua.cast(slist, "ASelectList" )
				if s1 ~= nil then
					s1:DeleteAllItems()
				end
			end
        end
        if widget:GetId() ==  "selectlistnew" then
            AppLog( "ASelectList action : " .. widget:GetId() .. " was pressed ")
            local slist = widget:FindWidget("ASelectListDemo") 
			if slist ~= nil then			
				local s1 = tolua.cast(slist, "ASelectList" )
				if s1 ~= nil then
            		local sis1 = ASelectItemSource:new()
            		sis1:AddItem( ASelectItem:new( "list 1","list1", "LogoAtomic" ))
            		sis1:AddItem( ASelectItem:new( "list 2","list2", "" ))
            		sis1:AddItem( ASelectItem:new( "list 3","list3", "" ))
            		sis1:AddItem( ASelectItem:new( "list 4","list4", "" ))
            		sis1:AddItem( ASelectItem:new( "list 5","list5", "" ))
            		sis1:AddItem( ASelectItem:new( "list 6","list6", "" ))
            		s1:SetSource(sis1)
				end
			end
        end
    end
end

