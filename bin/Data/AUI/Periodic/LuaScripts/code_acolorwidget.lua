-- AColorWidget application source code

function setup_uicolorwidget( layout )
    local dest = layout:SearchAWidgetClass( "TBButton" )
    for i, awid in ipairs(dest) do
        SubscribeToEvent(awid, "WidgetEvent", "HandleUicolorwidgetEvent")
	end
end

function HandleUicolorwidgetEvent( eventType, eventData )
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
 		return;
	end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if widget:GetId() == "uicolorwidgetcode" then
            AppLog( "AColorWidget support : " .. widget:GetId() .. " was pressed " )
            ViewCode ( "LuaScripts/code_acolorwidget.lua", widget:GetParent())
        end
        if widget:GetId() == "uicolorwidgetlayout" then
            AppLog( "AColorWidget support : " .. widget:GetId() .. " was pressed ")
            ViewCode ( "Scenes/layout_acolorwidget.ui.txt", widget:GetParent())
        end
        if widget:GetId() == "uicolorwidgetred" then
            AppLog( "AColorWidget action : " .. widget:GetId() .. " was pressed ")
            local clw = widget:FindWidget("colorwidgetdemo")
            if clw ~= nil then
            	local cw1 = tolua.cast(clw, "AColorWidget")
                cw1:SetColorString("#FF1111")
			end
        end
        if widget:GetId() == "uicolorwidgetgreen" then
            AppLog( "AColorWidget action : " .. widget:GetId() .. " was pressed ")
            local clw = widget:FindWidget("colorwidgetdemo")
            if clw ~= nil then
            	local cw1 = tolua.cast(clw, "AColorWidget")
                cw1:SetColorString("#11FF11")
			end
        end
        if widget:GetId() == "uicolorwidgetblue" then
            AppLog( "AColorWidget action : " .. widget:GetId() .. " was pressed ")
            local clw = widget:FindWidget("colorwidgetdemo")
            if clw ~= nil then
            	local cw1 = tolua.cast(clw, "AColorWidget")
                cw1:SetColorString("#1111FF")
			end
        end
    end
end

