-- Sound effects example
-- This sample demonstrates:
--     - Playing sound effects and music
--     - Controlling sound and music master volume

require "AUI/LuaScripts/Utilities/Sample"

local soundNames = {
    "Fist",
    "Explosion",
    "Power-up"
    }

local soundResourceNames = {
    "Sounds/PlayerFistHit.wav",
    "Sounds/BigExplosion.wav",
    "Sounds/Powerup.wav"
    }

local musicSource

function Start()
    -- Execute the common startup for samples
    SampleStart()

    -- Create a scene which will not be actually rendered, but is used to hold SoundSource components while they play sounds
    scene_ = Scene()

    -- Create music sound source
    musicSource = scene_:CreateComponent("SoundSource")
    -- Set the sound type to music so that master volume control works correctly
    musicSource.soundType = SOUND_MUSIC

    -- Enable OS cursor
    input.mouseVisible = true

    -- Create the user interface
    CreateUI()

    -- Set the mouse mode to use in the sample
    SampleInitMouseMode(MM_FREE)
end

function CreateUI()

    local uiStyle = cache:GetResource("XMLFile", "UI/DefaultStyle.xml")
    -- Set style to the UI root so that elements will inherit it
    ui.root.defaultStyle = uiStyle

    AUIInit ( "AUI/resources/default_font/vera.ttf", "Vera", 14, "AUI/Scenes/14_layout.ui.txt" )
    
    local uiview = aui:GetFocusedView()

    local button = uiview:FindWidget("fistbutton")
    SubscribeToEvent( button, "WidgetEvent", "HandlePlaySound" )
    button = uiview:FindWidget("explosionbutton")
    SubscribeToEvent( button, "WidgetEvent", "HandlePlaySound" )
    button = uiview:FindWidget("powerupbutton")
    SubscribeToEvent( button, "WidgetEvent", "HandlePlaySound" )
    button = uiview:FindWidget("playbutton")
    SubscribeToEvent( button, "WidgetEvent", "HandlePlayMusic" )
    button = uiview:FindWidget("stopbutton")
    SubscribeToEvent( button, "WidgetEvent", "HandleStopMusic" )

    local slider = uiview:FindWidget("soundvolume")
    SubscribeToEvent( slider, "WidgetEvent", "HandleSoundVolume" )
    slider = uiview:FindWidget("musicvolume")
    SubscribeToEvent( slider, "WidgetEvent", "HandleMusicVolume" )
end



function HandlePlaySound(eventType, eventData)
    local sound = nil
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
        return
    end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        if widget:GetId() == "fistbutton" then
            sound = cache:GetResource("Sound", soundResourceNames[1])
        end
        if widget:GetId() == "explosionbutton" then
            sound = cache:GetResource("Sound", soundResourceNames[2])
        end
        if widget:GetId() == "powerupbutton" then
            sound = cache:GetResource("Sound", soundResourceNames[3])
        end
    end
    if sound ~= nil then
        -- Create a SoundSource component for playing the sound. The SoundSource component plays
        -- non-positional audio, so its 3D position in the scene does not matter. For positional sounds the
        -- SoundSource3D component would be used instead
        local soundSource = scene_:CreateComponent("SoundSource")
        soundSource:SetAutoRemoveMode(REMOVE_COMPONENT)
        soundSource:Play(sound)
        -- In case we also play music, set the sound volume below maximum so that we don't clip the output
        soundSource.gain = 0.7
    end
end

function HandlePlayMusic(eventType, eventData)
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
        return
    end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        local music = cache:GetResource("Sound", "Music/Ninja Gods.ogg")
        -- Set the song to loop
        music.looped = true

        musicSource:Play(music)
    end
end

function HandleStopMusic(eventType, eventData)
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
        return
    end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CLICK then
        musicSource:Stop()
    end
end

function HandleSoundVolume(eventType, eventData)
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
        return
    end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CHANGED then
        local newVolume = widget:GetValue()
        audio:SetMasterGain(SOUND_EFFECT, newVolume)
    end
end

function HandleMusicVolume(eventType, eventData)
    local widget = eventData["Target"]:GetPtr("AWidget")
    if widget == nil then
        return
    end
    if eventData["Type"]:GetInt() == UI_EVENT_TYPE_CHANGED then
        local newVolume = widget:GetValue()
        audio:SetMasterGain(SOUND_MUSIC, newVolume)
    end
end

-- Create XML patch instructions for screen joystick layout specific to this sample app
function GetScreenJoystickPatchString()
    return
        "<patch>" ..
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button2']]\">" ..
        "        <attribute name=\"Is Visible\" value=\"false\" />" ..
        "    </add>" ..
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Hat0']]\">" ..
        "        <attribute name=\"Is Visible\" value=\"false\" />" ..
        "    </add>" ..
        "</patch>"
end
