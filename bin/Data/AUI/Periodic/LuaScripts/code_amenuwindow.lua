-- AMenuWindow application source code


function setup_uimenuwindow( layout )
    local dest = layout:SearchAWidgetClass( "TBButton" )
    for i, awid in ipairs(dest) do
        SubscribeToEvent(awid, "WidgetEvent", "HandleUimenuwindowEvent")
	end
end

function HandleUimenuwindowEvent(eventType, eventData)
    local refid = eventData["RefID"]:GetString()
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
 		return
	end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if widget:GetId() == "uimenuwindowcode" then
            AppLog( "AMenuWindow support : " .. widget:GetId() .. " was pressed " )
            ViewCode ( "LuaScripts/code_amenuwindow.lua", widget:GetParent())
        end
        if widget:GetId() == "uimenuwindowlayout" then
            AppLog( "AMenuWindow support : " .. widget:GetId() .. " was pressed ")
            ViewCode ( "Scenes/layout_amenuwindow.ui.txt", widget:GetParent())
        end
        if widget:GetId() ==  "uimenuwindowpush" then
            AppLog( "AMenuWindow action : " .. widget:GetId() .. " was pressed " )
            local mymenuwindow = AMenuWindow:new( widget, "MenuWindowDemo")
            local mis =  AMenuItemSource:new()
            mis:AddItem( AMenuItem:new( "ASelectItem1", "item1", "", "" ) )
            mis:AddItem( AMenuItem:new( "ASelectItem2", "item2", "Ctrl+C", "" ) )
            mis:AddItem( AMenuItem:new( "ASelectItem3", "item3", "Ctrl+A", "DuckButton" ) )
            mis:AddItem( AMenuItem:new( "ASelectItem4", "item4", "Ctrl+O", "LogoAtomic" ) )
            local xx = widget:GetX() + (widget:GetWidth()/2)
            local yy = widget:GetY() + (widget:GetHeight()/2)
            SubscribeToEvent(mymenuwindow, "WidgetEvent", "HandleUimenuwindowEvent" )
            mymenuwindow:ShowMenu(mis, xx, yy)
        end

        if widget:GetId() ==  "MenuWindowDemo" then
            AppLog( "AMenuWindow event : " .. widget:GetId() .. " and " .. refid .. " was selected ")
        end
    else
        if widget:GetId() ==  "MenuWindowDemo" then
            AppLog( "AMenuWindow event : " .. widget:GetId() ..  " refid=" .. refid )
        end
    end
end

