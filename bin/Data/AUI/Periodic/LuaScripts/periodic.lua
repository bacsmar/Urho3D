-- This script is the main entry point of the AUI example 

-- include the components
require ( "AUI/Periodic/LuaScripts/code_table")
require ( "AUI/Periodic/LuaScripts/code_abargraph" )
require ( "AUI/Periodic/LuaScripts/code_abutton")
require ( "AUI/Periodic/LuaScripts/code_acheckbox")
require ( "AUI/Periodic/LuaScripts/code_aclicklabel")
require ( "AUI/Periodic/LuaScripts/code_acolorwheel")
require ( "AUI/Periodic/LuaScripts/code_acolorwidget")
require ( "AUI/Periodic/LuaScripts/code_acontainer")
require ( "AUI/Periodic/LuaScripts/code_aeditfield")
require ( "AUI/Periodic/LuaScripts/code_afinderwindow")
require ( "AUI/Periodic/LuaScripts/code_afontdescription")
require ( "AUI/Periodic/LuaScripts/code_aimagewidget")
require ( "AUI/Periodic/LuaScripts/code_ainlineselect")
require ( "AUI/Periodic/LuaScripts/code_alayout")
require ( "AUI/Periodic/LuaScripts/code_alayoutparams")
require ( "AUI/Periodic/LuaScripts/code_amenuitem")
require ( "AUI/Periodic/LuaScripts/code_amenuwindow")
require ( "AUI/Periodic/LuaScripts/code_amessagewindow")
require ( "AUI/Periodic/LuaScripts/code_amultiitem")
require ( "AUI/Periodic/LuaScripts/code_apromptwindow")
require ( "AUI/Periodic/LuaScripts/code_apulldownmenu")
require ( "AUI/Periodic/LuaScripts/code_aradiobutton")
require ( "AUI/Periodic/LuaScripts/code_asceneview")
require ( "AUI/Periodic/LuaScripts/code_ascrollbar")
require ( "AUI/Periodic/LuaScripts/code_ascrollcontainer")
require ( "AUI/Periodic/LuaScripts/code_asection")
require ( "AUI/Periodic/LuaScripts/code_aselectdropdown")
require ( "AUI/Periodic/LuaScripts/code_aselectitem")
require ( "AUI/Periodic/LuaScripts/code_aselectlist")
require ( "AUI/Periodic/LuaScripts/code_aseparator")
require ( "AUI/Periodic/LuaScripts/code_askinimage")
require ( "AUI/Periodic/LuaScripts/code_aslider")
require ( "AUI/Periodic/LuaScripts/code_atabcontainer")
require ( "AUI/Periodic/LuaScripts/code_atextfield")
require ( "AUI/Periodic/LuaScripts/code_atexturewidget")
require ( "AUI/Periodic/LuaScripts/code_awidget")
require ( "AUI/Periodic/LuaScripts/code_awindow")
require ( "AUI/Periodic/LuaScripts/code_alistview")
require ( "AUI/Periodic/LuaScripts/code_abuttongrid")
require ( "AUI/Periodic/LuaScripts/code_adimmer")

-- "globals"
uiview = nil
uiroot = nil
logger = nil

function Start()

    -- Enable OS cursor
    input.mouseVisible = true

    -- Load scene
    local scene_ = Scene:new()
    -- Load scene content prepared in the editor (XML format): GetFile() returns an open file from the resource system
    -- which scene:LoadXML() will read
    scene_:LoadXML(cache:GetFile("Scenes/Scene.scene"))

    -- Create the Window and add it to the UI's root node
    aui:Initialize("AUI/resources/language/lng_en.tb.txt")
    aui:LoadDefaultPlayerSkin()
    aui:AddFont( "AUI/resources/default_font/vera.ttf", "Vera" )
    aui:SetDefaultFont("Vera", 12)
    uiview = AView:new()
    uiroot = aui:GetRootAWidget()

    local lo0 = ALayout:new()  -- make the host widget for all visible ui
    lo0:SetRect (uiview:GetRect()) -- size it to fill the screen area
    lo0:SetLayoutConfig( "YAGAC" )  -- all-in-one setting
    lo0:SetSkinBg ("background_solid")  -- make it look presentable:

    -- example of adding a font, it will be used later
    aui:AddFont("Textures/BrokenGlass.ttf", "BrokenGlass")

    -- set up some stuff for mobile, so we can use the same app code & layouts
    -- by lying about the device DPI. Everyone lies about DPI.
    if GetPlatform() == "Android" or GetPlatform() == "iOS" then
        aui:LoadSkin("Textures/mobile.tb.txt","")
        if graphics.width > 1200 then
            aui:SetDefaultFont("Vera", 14)
        else 
            aui:SetDefaultFont("Vera", 10)
        end
    else
        aui:LoadSkin("Textures/desktop.tb.txt","")
    end

    -- load the main UI layout
    lo0:Load("Scenes/main_layout.ui.txt") -- load the main layout
    uiview:AddChild(lo0) -- And make it show up:

    -- and get going with widget events
    logger = lo0:GetWidget("LogText")  
    local maintb = tolua.cast(lo0:GetWidget("maintabs"), "ATabContainer")
    local acttb = tolua.cast(lo0:GetWidget("primarytabs"), "ATabContainer")
    local semitb = tolua.cast(lo0:GetWidget("moretabs"), "ATabContainer")
    local viewtb = tolua.cast(lo0:GetWidget("supporttabs"), "ATabContainer")
    local supporttb = tolua.cast(lo0:GetWidget("atomictabs"), "ATabContainer")

    supporttb:SetCurrentPage(0) -- do this or else the tab contents look like crap!
    viewtb:SetCurrentPage(0) 
    semitb:SetCurrentPage(0) 
    acttb:SetCurrentPage(0)
    maintb:SetCurrentPage(0) 

    SubscribeToEvent("KeyDown","HandleKeyDown")
 
    local ea = tolua.cast(lo0:GetWidget("exitapp"), "AWidget")
    SubscribeToEvent(ea, "WidgetEvent", "HandleExitEvent")
    local lt = tolua.cast(lo0:GetWidget("liteapp"), "AWidget")
    SubscribeToEvent(lt, "WidgetEvent", "HandleExitEvent")
    local dr = tolua.cast(lo0:GetWidget("darkapp"), "AWidget")
    SubscribeToEvent(dr, "WidgetEvent", "HandleExitEvent")

    setup_table (lo0)
    setup_uibargraph( lo0:GetWidget("pageuibargraph") )
    setup_uibutton( lo0:GetWidget("pageuibutton") )
    setup_uicheckbox( lo0:GetWidget("pageuicheckbox"))
    setup_uiclicklabel( lo0:GetWidget("pageuiclicklabel") )
    setup_uicolorwheel( lo0:GetWidget("pageuicolorwheel") )
    setup_uicolorwidget( lo0:GetWidget("pageuicolorwidget") )
    setup_uicontainer( lo0:GetWidget("pageuicontainer"))
    setup_uieditfield( lo0:GetWidget("pageuieditfield") )
    setup_uifinderwindow( lo0:GetWidget("pageuifinderwindow"), uiview )
    setup_uifontdescription( lo0:GetWidget("pageuifontdescription") )
    setup_uiimagewidget( lo0:GetWidget("pageuiimagewidget") )
    setup_uiinlineselect( lo0:GetWidget("pageuiinlineselect") )
    setup_uilayoutparams( lo0:GetWidget("pageuilayoutparams") )
    setup_uilayout( lo0:GetWidget("pageuilayout"), uiview )
    setup_uimenuitem( lo0:GetWidget("pageuimenuitem") )
    setup_uimenuwindow( lo0:GetWidget("pageuimenuwindow") )
    setup_uimessagewindow( lo0:GetWidget("pageuimessagewindow") )
    setup_uimultiitem( lo0:GetWidget("pageuimultiitem") )
    setup_uipromptwindow( lo0:GetWidget("pageuipromptwindow"), uiview )
    setup_uipulldownmenu( lo0:GetWidget("pageuipulldownmenu") )
    setup_uiradiobutton( lo0:GetWidget("pageuiradiobutton") )
    setup_uisceneview( lo0:GetWidget("pageuisceneview") )
    setup_uiscrollbar( lo0:GetWidget("pageuiscrollbar") )
    setup_uiscrollcontainer( lo0:GetWidget("pageuiscrollcontainer") )
    setup_uisection( lo0:GetWidget("pageuisection") )
    setup_uiselectdropdown( lo0:GetWidget("pageuiselectdropdown") )
    setup_uiselectitem( lo0:GetWidget("pageuiselectitem") )
    setup_uiselectlist( lo0:GetWidget("pageuiselectlist") )
    setup_uiseparator( lo0:GetWidget("pageuiseparator") )
    setup_uiskinimage( lo0:GetWidget("pageuiskinimage") )
    setup_uislider( lo0:GetWidget("pageuislider") )
    setup_uitabcontainer( lo0:GetWidget("pageuitabcontainer") )
    setup_uitextfield( lo0:GetWidget("pageuitextfield") )
    setup_uitexturewidget( lo0:GetWidget("pageuitexturewidget") )
    setup_uiwindow( lo0:GetWidget("pageuiwindow"), uiview )
    setup_uiwidget( lo0:GetWidget("pageuiwidget") )
    setup_uibuttongrid( lo0:GetWidget("pageuibuttongrid") )
    setup_uidimmer( lo0:GetWidget("pageuidimmer") )
    setup_uilistview( lo0:GetWidget("pageuilistview") )
 
    AppLog ( "Ready" )

end

function HandleExitEvent( eventType, eventData)
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
        return
    end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if widget:GetId() == "exitapp" then
            engine:Exit()
        end
        if widget:GetId() == "liteapp" then
            aui:LoadSkin( "resources/default_skin_light/skin.tb.txt", "")
        end
        if widget:GetId() == "darkapp" then
            aui:LoadSkin( "resources/default_skin/skin.tb.txt", "")
        end
    end
end

function HandleKeyDown(eventType, eventData)
    if eventData["Key"]:GetInt() == KEY_ESCAPE then
        engine:Exit()
    end

end

function AppLog( logtext )
    if logger ~= nil then
        logger:SetText( logtext )
    end
end

function ViewCode ( filename, layoutParent )
    local someview = layoutParent:GetView()
    window = AWindow:new()
    if window ~= nil then
        window:SetSettings ( UI_WINDOW_SETTINGS_DEFAULT )
        window:SetText( "Code Viewer")
        window:Load("Scenes/view_code.ui.txt")
        local textx = "File Not Found:" .. filename
        local filex = cache:GetFile(filename)
        if filex ~= nil then
            textx = filex:ReadString()
            filex:Close()
        end
        coder = window:GetWidget("viewCodeText")
        if coder ~= nil then
            coder:SetText(textx)
        end
        window:ResizeToFitContent()
        local view1 = someview
        if view1 ~= nil then
            local w1 = tolua.cast(window,"AWindow")
            if w1 ~= nil then
                view1:AddChild(w1)
            end
        end
        window:Center()
        local someok = window:GetWidget("viewCodeOK")
        if someok ~= nil then
            SubscribeToEvent(someok, "WidgetEvent", "HandleViewCodeEvent")
        end
    end
end

function HandleViewCodeEvent( eventType, eventData)
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
        return
    end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        local mywindow = FindTheWindowParent(widget) 
        if mywindow ~= nil then    
            mywindow:Close()
        end
    end
end


function FindTheWindowParent( fromThisWidget )
    if fromThisWidget == nil then
        return nil
    end
    if fromThisWidget:GetClassName() == "TBWindow" or fromThisWidget:GetClassName() == "TBDockWindow" then 
        return fromThisWidget
    end
    local tbw = fromThisWidget:GetParent()
    while tbw ~= nil do
        if tbw:GetClassName() == "TBWindow" or tbw:GetClassName() == "TBDockWindow" then
            return tbw
        end
        tbw = tbw:GetParent()
    end
    return nil 
end


