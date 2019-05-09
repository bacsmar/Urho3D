-- UIFontdescription application source code


function setup_uifontdescription(  layout )
    local dest = layout:SearchAWidgetClass( "TBButton" )
    for i, awid in ipairs(dest) do
        SubscribeToEvent(awid, "WidgetEvent", "HandleUifontdescriptionEvent")
	end
    local sld = layout:GetWidget ("fontstep")
    if sld ~= nil then
		local d1 = tolua.cast(sld, "AWidget")
        SubscribeToEvent(d1, "WidgetEvent", "HandleUifontdescriptionEvent" )
	end
end

function HandleUifontdescriptionEvent( eventType,  eventData)
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
 		return
	end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if widget:GetId() == "uifontdescriptioncode" then
            AppLog( "UIFontdescription support : " .. widget:GetId() .. " was pressed " )
            ViewCode ( "LuaScripts/code_afontdescription.lua", widget:GetParent())
        end
        if widget:GetId() ==  "uifontdescriptionlayout" then
            AppLog( "UIFontdescription support : " .. widget:GetId() .. " was pressed ")
            ViewCode ( "Scenes/layout_afontdescription.ui.txt", widget:GetParent())
        end
    elseif eventData["Type"]:GetInt() == UI_EVENT_TYPE_CHANGED then
        if widget:GetId() == "fontstep" then
 			local uis2 = tolua.cast( widget, "ASlider")
            local mytext = widget:FindWidget("changetext")
            local myfont = AFontDescription:new()
            myfont:SetSize( math.floor(uis2:GetValue())) -- convert float to int
            myfont:SetId("Vera")
            mytext:SetFontDescription (myfont)
            mytext:SetText ( "Size " .. math.floor(uis2:GetValue()))
            AppLog( "UIFontdescription action : " .. widget:GetId() .. " step size changed to " .. math.floor(uis2:GetValue()))
        end
    end
end

