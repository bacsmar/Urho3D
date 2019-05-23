-- AEditField application source code

function setup_uieditfield( layout )
    local dest = layout:SearchAWidgetClass( "TBButton" )
    for i, awid in ipairs(dest) do
        SubscribeToEvent(awid, "WidgetEvent", "HandleUieditfieldEvent")
    end

    local ed1 = layout:GetWidget ("editfieldsingle")
    if ed1 ~= nil then
        local d1 = tolua.cast(ed1, "AWidget")
        SubscribeToEvent(d1, "WidgetEvent", "HandleUieditfieldEvent")
    end
    local ed2 = layout:GetWidget ("editfieldmulti")
    if ed2 ~= nil then
        local d2 = tolua.cast(ed2, "AWidget")
        SubscribeToEvent(d2, "WidgetEvent", "HandleUieditfieldEvent")
    end
end

function HandleUieditfieldEvent( eventType, eventData )
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
        return;
    end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if widget:GetId() == "uieditfieldcode" then
            AppLog( "AEditField support : " .. widget:GetId() .. " was pressed " )
            ViewCode ( "LuaScripts/code_aeditfield.lua", widget:GetParent())
        end
        if widget:GetId() ==  "uieditfieldlayout" then
            AppLog( "AEditField support : " .. widget:GetId() .. " was pressed ")
            ViewCode ( "Scenes/layout_aeditfield.ui.txt", widget:GetParent())
        end
        if widget:GetId() == "editfieldadd" then
            AppLog( "AEditField action : " .. widget:GetId() .. " was pressed ")
            local ef1 = widget:FindWidget("editfieldmulti")
            if ef1 ~= nil then
                local ef2 = tolua.cast(ef1, "AEditField")
                local filex = cache:GetFile("Scenes/layout_aeditfield.ui.txt")
                local textx = filex:ReadString()
                filex:Close()
                ef2:SetText(textx)
            end
        end
        if widget:GetId() ==  "editfieldclr" then
            AppLog( "AEditField action : " .. widget:GetId() .. " was pressed ")
            local ef1 = widget:FindWidget("editfieldmulti")
            if ef1 ~= nil then
                local ef2 = tolua.cast(ef1, "AEditField")
                ef2:SetText("")
            end
        end
    else
        if widget:GetId() == "editfieldsingle" then
           AppLog( "AEditField event : " .. widget:GetId() .. " text = `" .. widget:GetText())
        end
        if widget:GetId() ==  "editfieldmulti" then
            AppLog( "AEditField event : " .. widget:GetId() .. " text = `" .. widget:GetText())
        end
    end
end

