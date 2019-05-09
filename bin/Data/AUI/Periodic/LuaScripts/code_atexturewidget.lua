-- ATextureWidget application source code


function setup_uitexturewidget( layout )
    local dest = layout:SearchAWidgetClass( "TBButton" )
    for i, awid in ipairs(dest) do
        SubscribeToEvent(awid, "WidgetEvent", "HandleUitexturewidgetEvent")
	end

    local mytexturewidget = ATextureWidget:new()
    mytexturewidget:SetId( "ATextureWidgetDemo")
    if mytexturewidget ~= nil then
        local mytex = Texture2D:new()
        if mytex ~= nil then
            mytex = cache:GetResource("Texture2D", "Textures/planet.jpg")
            mytexturewidget:SetTexture(mytex)
        end
    end
    SubscribeToEvent(mytexturewidget, "WidgetEvent", "HandleUitexturewidgetEvent" )
    local lpx = ALayoutParams:new()
    lpx:SetWidth (256)
    lpx:SetHeight(256)
    lpx:SetMinWidth(256)
    lpx:SetMinHeight(256)
    lpx:SetMaxWidth (256)
    lpx:SetMaxHeight(256)
    mytexturewidget:SetLayoutParams(lpx)
    local lower = layout:GetWidget("uitexturewidgetlower")
    local mysvc = layout:GetWidget("uitwcontainer")
    mysvc:AddChildBefore( mytexturewidget, lower)

    local lo1 = ALayout:new()
    mysvc:AddChildBefore(lo1, lower)

    local b1 = AButton:new()
    b1:SetId( "uitexturewidgetch1")
    b1:SetText("Change texture to  build")
    lo1:AddChild(b1)
    SubscribeToEvent(b1, "WidgetEvent", "HandleUitexturewidgetEvent" )
    local b2 = AButton:new()
    b2:SetId( "uitexturewidgetch2")
    b2:SetText("Change texture to colorwheel")
    lo1:AddChild(b2)
    SubscribeToEvent(b2, "WidgetEvent", "HandleUitexturewidgetEvent" )
    local b3 = AButton:new()
    b3:SetId( "uitexturewidgetch3")
    b3:SetText("Change texture to planet")
    lo1:AddChild(b3)
    SubscribeToEvent(b3, "WidgetEvent", "HandleUitexturewidgetEvent" )
    
end

function HandleUitexturewidgetEvent(eventType, eventData)
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
 		return
	end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if widget:GetId() == "uitexturewidgetcode" then
            AppLog( "ATextureWidget support : " .. widget:GetId() .. " was pressed " )
            ViewCode ( "LuaScripts/code_atexturewidget.lua", widget:GetParent())
        end
        if widget:GetId() ==  "uitexturewidgetlayout" then
            AppLog( "ATextureWidget support : " .. widget:GetId() .. " was pressed ")
            ViewCode ( "Scenes/layout_atexturewidget.ui.txt", widget:GetParent())
        end

        if widget:GetId() ==  "uitexturewidgetch1" then
            AppLog( "ATextureWidget support : " .. widget:GetId() .. " was pressed ")
            local twraw = widget:FindWidget("ATextureWidgetDemo")
			if twraw ~= nil then
				local tw = tolua.cast(twraw, "ATextureWidget" )
				if tw ~= nil then
		            tw:SetTexture( cache:GetResource("Texture2D","Textures/newbuilddetected_header.jpg") )
				end
			end
        end
        if widget:GetId() ==  "uitexturewidgetch2" then
            AppLog( "ATextureWidget support : " .. widget:GetId() .. " was pressed ")
            local twraw = widget:FindWidget("ATextureWidgetDemo")
			if twraw ~= nil then
				local tw = tolua.cast(twraw, "ATextureWidget" )
				if tw ~= nil then
            		tw:SetTexture( cache:GetResource( "Texture2D", "Textures/HSV21.png") )
				end
			end
        end
        if widget:GetId() ==  "uitexturewidgetch3" then
            AppLog( "ATextureWidget support : " .. widget:GetId() .. " was pressed ")
            local twraw = widget:FindWidget("ATextureWidgetDemo")
			if twraw ~= nil then
				local tw = tolua.cast(twraw, "ATextureWidget" )
				if tw ~= nil then
            		tw:SetTexture( cache:GetResource( "Texture2D", "Textures/planet.jpg") )
				end
			end
        end
    end
end

