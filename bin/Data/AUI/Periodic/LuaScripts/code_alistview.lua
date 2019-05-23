-- AListView application source code

local wcount = 0

function PrintPretty( alv, me, recenthandle )

    wcount = wcount + 1

    local wname = "Widget[" .. wcount .. "]" .. me:GetClassName() .. " " .. me:GetText()
    local iconx = ""
    if  me:GetClassName() == "TBButton" then
        iconx = "ButtonIcon"
    end
    if me:GetClassName() == "TBLayout" then
        iconx = "LayoutIcon"
    end
    if me:GetClassName() == "TBTextField" then
        iconx = "TextFieldIcon"
    end

    local nxt = alv:AddChildItem(recenthandle, wname, iconx, "widget" .. me:GetId())

    local num = me:numChildren()
    local ii = 0
    while (ii < num ) do 
        local child = me:GetChildFromIndex(ii);
        PrintPretty( alv, child, nxt );
        ii = ii + 1
    end
end

function setup_uilistview( layout)
    dest = layout:SearchAWidgetClass( "TBButton" )
    for i, awid in ipairs(dest) do 
        SubscribeToEvent(awid, "WidgetEvent", "HandleUilistviewEvent")
    end

    local mylistview = AListView:new()  -- make a scene:::view
    mylistview:SetId( "AListViewDemo") -- tag it, in case we want to get it again later
    SubscribeToEvent( mylistview, "WidgetEvent", "HandleUilistviewEvent")

    -- fill the listview, feel the joy
    local roothandle = mylistview:AddRootItem("Widgets", "LogoAtomic", "root_")
    PrintPretty( mylistview, uiview, roothandle )

    local lpx = ALayoutParams:new()
    lpx:SetWidth (600)
    lpx:SetHeight(320)
    lpx:SetMinWidth(600)
    lpx:SetMinHeight(320)
    lpx:SetMaxWidth (600)
    lpx:SetMaxHeight(320)
    mylistview:SetLayoutParams(lpx)

    local lower = layout:GetWidget("uilistviewlower")
    local mysvc = layout:GetWidget("listviewcontainer")
    mysvc:AddChildBefore(mylistview, lower)
end

function HandleUilistviewEvent( eventType, eventData)
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
        return
    end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if widget:GetId() == "uilistviewcode" then
            AppLog( "AListView support : " .. widget:GetId() .. " was pressed " )
            ViewCode ( "LuaScripts/code_alistview.lua", widget:GetParent())
        end
        if widget:GetId() ==  "uilistviewlayout" then
            AppLog( "AListView support : " .. widget:GetId() .. " was pressed ")
            ViewCode ( "Scenes/layout_alistview.ui.txt", widget:GetParent())
        end
    end
    if widget:GetId() == "AListViewDemo" then
       AppLog( "AListView event : " .. widget:GetId() .. " got event= ".. eventData["Type"]:GetInt())
   end
end

