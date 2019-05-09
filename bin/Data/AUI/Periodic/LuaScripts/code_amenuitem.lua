-- AMenuItem and AMenuItemSource application source code

-- a global, persist this way, wouldnt do it thru a SetGlobalVar
mgmis = nil

function setup_uimenuitem( layout )
    local dest = layout:SearchAWidgetClass( "TBButton" )
    for i, awid in ipairs(dest) do
        SubscribeToEvent(awid, "WidgetEvent", "HandleUimenuitemEvent")
	end

    mis = AMenuItemSource:new()
    mis:AddItem( AMenuItem:new( "ASelectItem1", "item1" ) )
    mis:AddItem( AMenuItem:new( "ASelectItem2", "item2", "Ctrl+X" ) )
    mis:AddItem( AMenuItem:new( "ASelectItem3", "item3", "Ctrl+D", "DuckButton" ) )
    mis:AddItem( AMenuItem:new( "ASelectItem4", "item4", "Ctrl+A", "LogoAtomic" ) )

 	mgmis = mis

end

function HandleUimenuitemEvent( eventType,  eventData)
    local refid = eventData["RefID"]:GetString()
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
 		return
	end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if widget:GetId() == "uimenuitemcode" then
            AppLog( "AMenuItem support : " .. widget:GetId() .. " was pressed " )
            ViewCode ( "LuaScripts/code_amenuitem.lua", widget:GetParent())
        end
        if widget:GetId() ==  "uimenuitemlayout" then
            AppLog( "AMenuItem support : " .. widget:GetId() .. " was pressed ")
            ViewCode ( "Scenes/layout_amenuitem.ui.txt", widget:GetParent())
        end

        if widget:GetId() ==  "uimenuitempush" then
			if mgmis ~= nil then
            	local mymenuwindow = AMenuWindow:new( widget, "MenuItemDemo")
           	 	SubscribeToEvent(mymenuwindow, "WidgetEvent", "HandleUimenuitemEvent" )
            	local xx = widget:GetX() + (widget:GetWidth()/2)
            	local yy = widget:GetY() + (widget:GetHeight()/2)
           	 	mymenuwindow:ShowMenu(mgmis, xx, yy)
			end
        end

        if widget:GetId() ==  "MenuItemDemo" then
            AppLog( "AMenuItem event : " .. widget:GetId() .. " and " .. refid .. " was selected ")
        end

        if widget:GetId() ==  "uimi1" then
            AppLog( "AMenuItem action : " .. widget:GetId() .. " was pressed ")
			if mgmis ~= nil then
            	mgmis:AddItem( AMenuItem:new( "New AMenuItem", "newitem") )
			end
        end
        if widget:GetId() ==  "uimi2" then
            AppLog( "AMenuItem action : " .. widget:GetId() .. " was pressed ")
			if mgmis ~= nil then
            	mgmis:AddItem( AMenuItem:new( "Newer AMenuItem", "neweritem" ) )
			end
        end
        if widget:GetId() ==  "uimi3" then
            AppLog( "AMenuItem action : " .. widget:GetId() .. " was pressed ")
			if mgmis ~= nil then
            	mgmis:AddItem( AMenuItem:new( "A Duck", "aduck", "", "DuckButton" ) )
			end
        end
        if widget:GetId() ==  "uimi4" then
            AppLog( "AMenuItem action : " .. widget:GetId() .. " was pressed ")
			if mgmis ~= nil then
            	mgmis:AddItem( AMenuItem:new( "Atomic!", "atomic", "", "LogoAtomic") )
			end
        end
        if widget:GetId() ==  "uimi5" then
            AppLog( "AMenuItem action : " .. widget:GetId() .. " was pressed ")
			if mgmis ~= nil then
           		mgmis:Clear()
			end
        end
    end
end

