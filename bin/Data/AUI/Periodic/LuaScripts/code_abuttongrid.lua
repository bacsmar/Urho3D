-- AButtonGrid application source code


function setup_uibuttongrid( layout)
    dest = layout:SearchAWidgetClass( "TBButton" )
    for i, awid in ipairs(dest) do 
        SubscribeToEvent(awid, "WidgetEvent", "HandleUibuttongridEvent")
    end

    local mybuttongrid = AButtonGrid:new(6,4)  -- make a scene:::view
    mybuttongrid:SetId( "AButtonGridDemo") -- tag it, in case we want to get it again later
    
    -- fill the buttongrid, feel the joy
    local row = 0
    while ( row < mybuttongrid:GetNumRows() ) do
        local col = 0
        while( col<mybuttongrid:GetNumColumns() ) do
            mybuttongrid:SetGridText (row, col, mybuttongrid:GetGridId(row, col));
            local bx = mybuttongrid:GetGridWidget( row, col );
            SubscribeToEvent(bx, "WidgetEvent", "HandleUibuttongridEvent" )
            col= col + 1
        end
        row = row + 1
    end
    
    local lpx = ALayoutParams:new()
    lpx:SetWidth (320)
    lpx:SetHeight(320)
    lpx:SetMinWidth(320)
    lpx:SetMinHeight(320)
    lpx:SetMaxWidth (320)
    lpx:SetMaxHeight(320)
    mybuttongrid:SetLayoutParams(lpx)

    local lower = layout:GetWidget("uibuttongridlower")
    local mysvc = layout:GetWidget("buttongridcontainer")
    mysvc:AddChildBefore(mybuttongrid, lower)
end

function HandleUibuttongridEvent( eventType, eventData)
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
        return
    end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if widget:GetId() == "uibuttongridcode" then
            AppLog( "AButtonGrid support : " .. widget:GetId() .. " was pressed " )
            ViewCode ( "LuaScripts/code_abuttongrid.lua", widget:GetParent())
        elseif widget:GetId() ==  "uibuttongridlayout" then
            ViewCode ( "Scenes/layout_abuttongrid.ui.txt", widget:GetParent())
        else
            AppLog( "AButtonGrid support : " .. widget:GetId() .. " was pressed ")
        end
    end
    if widget:GetId() == "AButtonGridDemo" then
       AppLog( "AButtonGrid event : " .. widget:GetId() .. " got event= ".. eventData["Type"]:GetInt())
   end
end

