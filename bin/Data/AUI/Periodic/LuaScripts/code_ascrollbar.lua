-- AScrollBar application source code

function setup_uiscrollbar( layout )
    local dest = layout:SearchAWidgetClass( "TBButton" )
    for i, awid in ipairs(dest) do  -- set bulk event handlers on all buttons -- boom!
        SubscribeToEvent(awid, "WidgetEvent", "HandleUiscrollbarEvent")
	end

    local sc1 = layout:GetWidget ("scrollbardemo")
    if sc1 ~= nil then
        SubscribeToEvent(sc1, "WidgetEvent", "HandleUiscrollbarEvent" )
	end
end

function HandleUiscrollbarEvent( eventType, eventData)
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
 		return
	end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if widget:GetId() == "uiscrollbarcode" then
            AppLog( "AScrollBar support : " .. widget:GetId() .. " was pressed " )
            ViewCode ( "LuaScripts/code_ascrollbar.lua", widget:GetParent())
        end
        if widget:GetId() ==  "uiscrollbarlayout" then
            AppLog( "AScrollBar support : " .. widget:GetId() .. " was pressed ")
            ViewCode ( "Scenes/layout_ascrollbar.ui.txt", widget:GetParent())
        end
    elseif eventData["Type"]:GetInt() == UI_EVENT_TYPE_CHANGED then
        if widget:GetId() == "scrollbardemo" then
            AppLog( "AScrollBar action : " .. widget:GetId() .. " changed value to " .. widget:GetValue())
        end
	else
       	AppLog( "HandleUiscrollbarEvent " .. widget:GetId() .. " got event " .. eventData["Type"]:GetInt())
     end
end

