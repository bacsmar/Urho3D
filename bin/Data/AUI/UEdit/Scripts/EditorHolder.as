// uEdit-lite a (real) simple text editor, using AUI
// EditorHolder class
// JimMarlowe
// MIT License

class EditorHolder
{
    String FullPath;  // pathname of the file
    String FileName;  // filename without path
    AWidget @TabWin;  // tab for the file
    AEditField @Editor; // editor
    bool changed;  // has the file been changed
    uint original; // original stringhash
    uint lastlen;  // incremental file/string len

    private String prospectPath;  //save as conflict
    private AWidget @tbUndoWidget;
    private AWidget @tbRedoWidget;
    private AWidget @tbSaveWidget;
    private APulldownMenu @pullfile;
    private APulldownMenu @pulledit;

    EditorHolder()
    {
        TabWin = null;
        Editor = null;
        changed = false;
        original = 0;
        lastlen = 0;
        tbUndoWidget = null;
        tbRedoWidget = null;
        tbSaveWidget = null;
    }

    String GetDisplayName() // for the tab display
    {
        if ( changed ) return "*" + FileName;
        return FileName;
    }

    void CreateEditorWidgets ( ATabContainer @tcx, String fullpathname )
    {
        FullPath = GetNativePath(fullpathname);

        if (fullpathname.Compare("") == 0 )
        {
            FileName = "NewDocument.txt";
        }
        else
            FileName = GetFileNameAndExtension(FullPath);

        ALayout @lo = ALayout();
        lo.SetLayoutConfig ( "YAGAC" );
        AEditField @myeditfield = AEditField();
        Editor = myeditfield;
        myeditfield.SetId ("Document-Editor");
        myeditfield.SetGravity( UI_GRAVITY_ALL);
        myeditfield.SetMultiline(true);
        if ( settings.selectEditorSkin > 0 )
            myeditfield.SetSkinBg( skinnames[settings.selectEditorSkin] );  // this can change the editor independent of theme
        AFontDescription @myfont = AFontDescription(); 
        myfont.SetSize( fontsz[settings.selectFontSize].ToInt());
        myfont.SetId( fontnames[settings.selectFontName]);
        myeditfield.SetFontDescription (myfont);
        lo.AddChild (myeditfield);
        tcx.AddTabPageWidget(FileName, lo);
        TabWin = tcx.GetPageTab( tcx.GetNumPages() -1 );

        if ( fullpathname.Compare("") != 0 )
        {
            TabWin.SetTooltip(FullPath);
            ReadTheFile();
        }
        changed = false;
        SubscribeToEvent(Editor, "WidgetEvent", "HandleLocalEditorEvent" );

        AWidget @xtb1 = tcx.FindWidget("undotb");
        AWidget @xtb2 = tcx.FindWidget("redotb");
        AWidget @xtb3 = tcx.FindWidget("savetb");
        RegisterToolbarWidgets ( xtb1, xtb2, xtb3 );

        APulldownMenu @xmb1 = cast<AButton@>(tcx.FindWidget("FileMenu"));
        APulldownMenu @xmb2 = cast<AButton@>(tcx.FindWidget("EditMenu"));
        RegisterMenubarWidgets ( xmb1, xmb2 );
    }

    void HandleLocalEditorEvent(StringHash eventType, VariantMap& eventData)
    {
        AWidget @widget = eventData["Target"].GetPtr();
        if ( widget is null ) return;

        if ( eventData["Type"].GetInt() == UI_EVENT_TYPE_KEY_UP )
            PerKeyStroke();
    }

    void RegisterToolbarWidgets ( AWidget @undow, AWidget @redow, AWidget @savew )
    {
        tbUndoWidget = undow;
        tbRedoWidget = redow;
        tbSaveWidget = savew;
        if ( Editor !is null )
        {
            FixUndoButton(Editor.CanUndo());
            FixRedoButton(Editor.CanRedo());
            FixSaveButton(changed);
        }
    }

    void RegisterMenubarWidgets ( APulldownMenu @m1, APulldownMenu @m2 )
    {
        pullfile = m1;
        pulledit = m2;
        if ( Editor !is null )
        {
            FixUndoButton(Editor.CanUndo());
            FixRedoButton(Editor.CanRedo());
            FixSaveButton(changed);
            if (pullfile !is null )
            {
                pullfile.SetMenuItemState(4, 1); // turn on save as
                pullfile.SetMenuItemState(6, 1); // turn on close
            }
        }
    }

    void MadeActive()
    {
        FixUndoButton(Editor.CanUndo());
        FixRedoButton(Editor.CanRedo());
        FixSaveButton(changed);
    }

    void ReadTheFile()
    {
        if ( FullPath.Compare("") != 0 )
        {
            File @filex = File();
            filex.Open(FullPath, FILE_READ);
            if ( filex.open )
            {
                String textx = filex.ReadString();
                Editor.SetText(textx);
                lastlen = textx.length;
                StringHash Orig (textx);
                original = Orig.value;
                filex.Close();
            }
        }
    }

    void SaveTheFile()
    {
        if ( FullPath.Compare("") != 0 )
        {
            File @file = File();
            file.Open(FullPath, FILE_WRITE);
            if ( file !is null && file.open)
            {
                String mystr = Editor.GetText();
                if ( file.WriteString( mystr))
                {
                    lastlen = mystr.length;
                    StringHash Orig(mystr);
                    original = Orig.value;
                    changed = false;
                    FixSaveButton(changed);
                }
                file.Close();
            }
        }
        else  // its a "new" file and needs to select a file+path
        {
            AFinderWindow @winnu = AFinderWindow( aui.GetFocusedView(), "NewDoc" );
            SubscribeToEvent(winnu, "AFinderComplete", "HandleNewDocEvent" );
            winnu.FindFile("Save New File", "", 1, 0, 0);
        }
    }

    void HandleNewDocEvent(StringHash eventType, VariantMap& eventData)
    {
        if ( eventData["Reason"].GetString() == "CANCEL" ) return; // they bailed

        if (activeEditor !is null )
        {
            SaveTheFileAs(eventData["Selected"].GetString());
        }
    }

    void SaveTheFileAs( String newfilename )
    {
        if ( newfilename.Compare("") != 0 )
        {
            if ( fileSystem.FileExists(newfilename)  )
            {
                prospectPath = newfilename;
                AMessageWindow @mess6 = AMessageWindow(  aui.GetFocusedView(), "savebeforeclose");
                SubscribeToEvent(mess6, "WidgetEvent", "HandleSaveOverEvent" );
                mess6.Show( "SaveAs File", "The requested file already exists. Do you want to overwrite it?",
                            UI_MESSAGEWINDOW_SETTINGS_YES_NO, true, 0, 0);
            }
            else
            {
                FullPath = GetNativePath(newfilename);  // saveas rebrands the file
                SaveTheFile();
                TabWin.SetTooltip(FullPath);
                FileName = GetFileNameAndExtension(FullPath);
                FixSaveButton( changed );
            }
        }
    }

    void HandleSaveOverEvent(StringHash eventType, VariantMap& eventData)
    {
        String refid = eventData["RefID"].GetString();
        AWidget @widget = eventData["Target"].GetPtr();
        if ( widget is null ) return;
        if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
        {
            if (refid == "TBMessageWindow.yes" )
            {
                FullPath = GetNativePath(prospectPath);
                SaveTheFile();
                TabWin.SetTooltip(FullPath);
                FileName = GetFileNameAndExtension(FullPath);
                FixSaveButton( changed );
                prospectPath.Clear();
            }
            if (refid == "TBMessageWindow.no" )
            {
            }
        }
    }

    void FixUndoButton( bool value)
    {
        if (tbUndoWidget !is null)
        {
            if ( value == true ) tbUndoWidget.SetState(UI_WIDGET_STATE_DISABLED, false );
            else tbUndoWidget.SetState(UI_WIDGET_STATE_DISABLED, true );
        }
        if ( pulledit !is null )
        {
            if ( value ) pulledit.SetMenuItemState(0, 1);
            else pulledit.SetMenuItemState(0, 0);
        }
    }

    void FixRedoButton( bool value )
    {
        if ( tbRedoWidget !is null)
        {
            if ( value == true ) tbRedoWidget.SetState(UI_WIDGET_STATE_DISABLED, false );
            else tbRedoWidget.SetState(UI_WIDGET_STATE_DISABLED, true );
        }
        if ( pulledit !is null )
        {
            if ( value ) pulledit.SetMenuItemState(1, 1);
            else pulledit.SetMenuItemState(1, 0);
        }
    }

    void FixSaveButton( bool value )
    {
        if ( tbSaveWidget !is null)
        {
            if ( value == true )
            {
                tbSaveWidget.SetState(UI_WIDGET_STATE_DISABLED, false );
                TabWin.SetText ( GetDisplayName() );
            }
            else
            {
                tbSaveWidget.SetState(UI_WIDGET_STATE_DISABLED, true );
                TabWin.SetText ( GetDisplayName() );
            }
        }
        if ( pullfile !is null )
        {
            if ( value ) pullfile.SetMenuItemState(3, 1);
            else pullfile.SetMenuItemState(3, 0);
            pullfile.SetMenuItemState(6, 1);
        }
    }

    void EditorUndo()
    {
        Editor.Undo();

        FixUndoButton(Editor.CanUndo());
        FixRedoButton(Editor.CanRedo());

        lastlen = Editor.GetText().length;
        StringHash UndoVal(Editor.GetText());
        if ( original != UndoVal.value ) changed = true;
        else changed = false;
        FixSaveButton(changed);
    }

    void EditorRedo()
    {
        Editor.Redo();

        FixRedoButton(Editor.CanRedo());
        FixUndoButton(Editor.CanUndo());
        lastlen = Editor.GetText().length;
        StringHash RedoVal(Editor.GetText());
        if ( original != RedoVal.value ) changed = true;
        else changed = false;
        FixSaveButton( changed );
    }

    void PerKeyStroke()
    {
        FixRedoButton(Editor.CanRedo());
        FixUndoButton(Editor.CanUndo());
        if ( lastlen != Editor.GetText().length )  // cheap test for change
        {
            lastlen = Editor.GetText().length;
            StringHash PerKeyVal(Editor.GetText());
            if ( original != PerKeyVal.value ) changed = true;
            else changed = false;
            FixSaveButton(changed);
        }
    }

};
