-- AImageWidget application source code


function setup_uiimagewidget( layout )
    local dest = layout:SearchAWidgetClass( "TBButton" )
    for i, awid in ipairs(dest) do
        SubscribeToEvent(awid, "WidgetEvent", "HandleUiimagewidgetEvent")
	end
end

function HandleUiimagewidgetEvent(eventType, eventData)
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
 		return;
	end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if widget:GetId() == "uiimagewidgetcode" then
            AppLog( "AImageWidget support : " .. widget:GetId() .. " was pressed " )
            ViewCode ( "LuaScripts/code_aimagewidget.lua", widget:GetParent())
        end
        if widget:GetId() ==  "uiimagewidgetlayout" then
            AppLog( "AImageWidget support : " .. widget:GetId() .. " was pressed ")
            ViewCode ( "Scenes/layout_aimagewidget.ui.txt", widget:GetParent())
        end

        if widget:GetId() ==  "imagecolor" then
            AppLog( "AImageWidget action : " .. widget:GetId() .. " was pressed ")
            local img1 = widget:FindWidget("imagewidgetdemo")
			if img1 ~= nil then 
 				local i2 = tolua.cast( img1, "AImageWidget")
            	i2:SetImage("Textures/HSV21.png")
			end
        end
        if widget:GetId() ==  "imagenewbuild" then
            AppLog( "AImageWidget action : " .. widget:GetId() .. " was pressed ")
            local img1 = widget:FindWidget("imagewidgetdemo")
			if img1 ~= nil then
 				local i2 = tolua.cast( img1, "AImageWidget")
           		i2:SetImage("Textures/newbuilddetected_header.jpg")
			end
        end
    end
end

