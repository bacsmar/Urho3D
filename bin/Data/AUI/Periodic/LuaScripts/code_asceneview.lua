-- ASceneView application source code
-- some code from UISceneview2D sample program

-- Rotator script object class:
Rotator = ScriptObject()

function Rotator:Start()
    self.rotationSpeed = {0.0, 0.0, 0.0}
end

function Rotator:Update(timeStep)
    local x = self.rotationSpeed[1] * timeStep
    local y = self.rotationSpeed[2] * timeStep
    local z = self.rotationSpeed[3] * timeStep
    self.node:Rotate(Quaternion(x, y, z))
end

function setup_uisceneview( layout)
    dest = layout:SearchAWidgetClass( "TBButton" )
    for i, awid in ipairs(dest) do 
        SubscribeToEvent(awid, "WidgetEvent", "HandleUisceneviewEvent")
	end

    local mysceneview = ASceneView:new()  -- make a scene:::view
    mysceneview:SetId( "ASceneViewDemo") -- tag it, in case we want to get it again later
    SubscribeToEvent(mysceneview, "WidgetEvent", "HandleUisceneviewEvent" )
    
    local myscene = Scene:new()
    if myscene ~= nil then
        if myscene:LoadXML((cache:GetFile("Scenes/sceneview.scene"))) then
            local cameraNode = myscene:GetChild("Camera", true)
            local mycamera = cameraNode:GetComponent("Camera")
            local planetNode = myscene:GetChild("TheWorld", true)
            if planetNode ~= nil then -- spin-o-rama, c.... style
       			local object = planetNode:CreateScriptObject("Rotator")
        		object.rotationSpeed = {0.0, 20.0, 1.0}
            end
            mysceneview:SetView(myscene, mycamera)
            mysceneview:SetAutoUpdate(true)
        end
    end

    local lpx = ALayoutParams:new()
    lpx:SetWidth (640)
    lpx:SetHeight(320)
    lpx:SetMinWidth(640)
    lpx:SetMinHeight(320)
    lpx:SetMaxWidth (640)
    lpx:SetMaxHeight(320)
    mysceneview:SetLayoutParams(lpx)

    local lower = layout:GetWidget("uisceneviewlower")
    local mysvc = layout:GetWidget("sceneviewcontainer")
    mysvc:AddChildBefore(mysceneview, lower)
end

function HandleUisceneviewEvent( eventType, eventData)
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
 		return
	end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if widget:GetId() == "uisceneviewcode" then
            AppLog( "ASceneView support : " .. widget:GetId() .. " was pressed " )
            ViewCode ( "LuaScripts/code_asceneview.lua", widget:GetParent())
        end
        if widget:GetId() ==  "uisceneviewlayout" then
            AppLog( "ASceneView support : " .. widget:GetId() .. " was pressed ")
            ViewCode ( "Scenes/layout_asceneview.ui.txt", widget:GetParent())
        end
    end
    if widget:GetId() == "ASceneViewDemo" then
       AppLog( "ASceneView event : " .. widget:GetId() .. " got event= ".. eventData["Type"]:GetInt())
   end
end

