// uEdit-lite a (real) simple text editor, using AUI
// globals for app
// JimMarlowe
// MIT License

AUI@ aui;  // the Atomic User Interface
VariantMap localVars; // cache for some app paths
Array<String>recentfiles; // array of recently closed files
Array<EditorHolder@> myFiles; // array of Editors
EditorHolder @activeEditor = null; // pointer to active editor
user_settings @settings = null; // user settings

// define some strings used for config, must match ui definition file
Array<String>fontnames = // string names of fonts
{
    "Vera",
    "AnonymousPro",
    "BlueHighway"
};

Array<String>fontsz =  // string names of font sizes
{
    "8",
    "10",
    "12",
    "14",
    "16",
    "18",
    "20",
    "24",
    "32",
    "40",
    "56"
};

Array<String>skinnames = // string names of skins
{
    "None",
    "lite_cell",
    "dark_cell",
    "sheet_cell"
};
