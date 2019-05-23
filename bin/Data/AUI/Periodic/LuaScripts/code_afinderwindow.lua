-- AFinderWindow application source code

function setup_uifinderwindow( layout, uiview )
    local dest = layout:SearchAWidgetClass( "TBButton" )
    for i, awid in ipairs(dest) do
        SubscribeToEvent(awid, "WidgetEvent", "HandleUifinderwindowEvent")
    end
end

function HandleFinderCompleteEvent( eventType, eventData )
    AppLog( "AFinderWindow event : the window " .. eventData["Title"]:GetString()
            .. " file was " .. eventData["Selected"]:GetString()
            .. ", the button pressed was " .. eventData["Reason"]:GetString())
end

function HandleUifinderwindowEvent( eventType, eventData )
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
        return;
    end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if (widget:GetId() == "uifinderwindowcode" ) then
            AppLog( "AFinderWindow support : " .. widget:GetId() .. " was pressed " );
            ViewCode ( "LuaScripts/code_afinderwindow.lua", widget:GetParent() )
        end
        if (widget:GetId() ==  "uifinderwindowlayout" ) then
            AppLog( "AFinderWindow support : " .. widget:GetId() .. " was pressed ")
            ViewCode ( "Scenes/layout_afinderwindow.ui.txt", widget:GetParent())
        end

        if widget:GetId() == "filefinder" then
            AppLog( "AFinderWindow action : " .. widget:GetId() .. " was pressed ")
            winf = AFinderWindow:new(uiview, widget:GetId())
            SubscribeToEvent(winf, "AFinderComplete", "HandleFinderCompleteEvent" )
            winf:FindFile("Find a File", "", 0, 0, 0)
        end
        if widget:GetId() ==  "folderfinder" then
            AppLog( "AFinderWindow action : " .. widget:GetId() .. " was pressed ")
            windowd = AFinderWindow:new(uiview, widget:GetId())
            SubscribeToEvent(windowd, "AFinderComplete", "HandleFinderCompleteEvent" )
            windowd:FindPath("Find a Folder", "", 0, 0, 0)
        end
    end
end

