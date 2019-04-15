// launcher example
// configuration using AUI

const uint prgNum = 39;
Array<String>prgFlags; // list of spawn flags
Array<String>prgArguments; // list of spawn arguments
Array<String>prgChecks; // list of checkbox states

// fill in the box with current settings
void PresetConfiguration( AWindow @win )
{
    for ( uint nn = 0; nn<prgNum; nn++)    // fill the box, feel the joy.
    {
       String cname = "pac" + String (nn); 
       AWidget @acheck = win.GetWidget(cname);
       if ( acheck !is null )
       {
            acheck.SetValue( prgChecks[nn].ToInt());
            SubscribeToEvent(acheck, "WidgetEvent", "HandleCheckEvent");
        }

        String ename = "pae" + String (nn); 
        AWidget @aedit = win.GetWidget(ename);
        if ( aedit !is null )
        {
            aedit.SetText( prgArguments[nn] );
        }
    }
}

void CreateArgDatabase()
{
    prgFlags.Resize(prgNum); // list of spawn flags
    prgArguments.Resize(prgNum); // list of spawn arguments
    prgChecks.Resize(prgNum); // list of checkbox states
   
    prgArguments.Insert( 0, "Launcher" );
    prgFlags.Insert( 0, "" );
    prgChecks.Insert( 0, "0" );
    for ( uint nn = 1; nn<prgNum; nn++)
    {
       prgArguments.Insert( nn, "" );
       prgChecks.Insert( nn, "0" );
    }
    prgFlags.Insert( 1, "-x" );  prgFlags.Insert( 2, "-y" );  prgFlags.Insert( 3, "-m" );
    prgFlags.Insert( 4, "-v" );  prgFlags.Insert( 5, "-t" );  prgFlags.Insert( 6, "-w" );
    prgFlags.Insert( 7, "-s" );  prgFlags.Insert( 8, "-q" );  prgFlags.Insert( 9, "-b" );
    prgFlags.Insert( 10, "-r" );  prgFlags.Insert( 11, "-pp" );  prgFlags.Insert( 12, "-p" );
    prgFlags.Insert( 13, "-pf" );  prgFlags.Insert( 14, "-ap" );  prgFlags.Insert( 15, "-log" );
    prgFlags.Insert( 16, "-ds" );  prgFlags.Insert( 17, "-mq" );  prgFlags.Insert( 18, "-tq" );
    prgFlags.Insert( 19, "-tf" );  prgFlags.Insert( 20, "-af" );  prgFlags.Insert( 21, "-gl2" );
    prgFlags.Insert( 22, "-flushgpu" );  prgFlags.Insert( 23, "-borderless" );  prgFlags.Insert( 24, "-lowdpi" );
    prgFlags.Insert( 25, "-headless" );  prgFlags.Insert( 26, "-landscape" );  prgFlags.Insert( 27, "-portrait" );
    prgFlags.Insert( 28, "-monitor" );  prgFlags.Insert( 29, "-hz" );  prgFlags.Insert( 30, "-prepass" );
    prgFlags.Insert( 31, "-renderpath" );  prgFlags.Insert( 32, "-lqshadows" );  prgFlags.Insert( 33, "-noshadows" );
    prgFlags.Insert( 34, "-nolimit" );  prgFlags.Insert( 35, "-nothreads" );  prgFlags.Insert( 36, "-nosound" );
    prgFlags.Insert( 37, "-noip" );  prgFlags.Insert( 38, "-touch" );
}

void GenerateExecArgs()
{
    String simp = " ";
    for (uint nn=1; nn<prgNum; nn++ )
    {
         if ( prgChecks[nn] == 1 ) 
         {
             simp = simp + prgFlags[nn] + " " ;
             if ( nn == 11 || nn== 12 || nn == 13 || nn == 14 || nn == 16 || nn == 31 ) // quote these
                simp = simp + "\"" + prgArguments[nn] + "\" ";
             else simp = simp + prgArguments[nn] + " ";
         }
    }
    execargs = simp;
}

void HandleCheckEvent(StringHash eventType, VariantMap& eventData)
{
    AWidget @widget = eventData["Target"].GetPtr();
    if ( widget is null ) return;
    if (eventData["Type"] == UI_EVENT_TYPE_CLICK)
    {
        String count = widget.GetId().Substring(3);
        prgChecks[count.ToInt()] = String (widget.GetValue());
        String ename = "pae" + count; 
        AWidget @aedit = widget.FindWidget(ename);
        if ( aedit !is null )
            prgArguments[count.ToInt()] = aedit.GetText();

        WriteConfiguration(); // hackyish
        
        GenerateExecArgs();
    }
}

void ReadConfiguration()
{
    String configFilename = localVars["SettingsPath"].GetString() + "settings.txt";
    uint count = 0;
    if ( fileSystem.FileExists(configFilename) )
    {
        File file( configFilename, FILE_READ);
        if ( file.open )
        {
            while (!file.eof)
            {
                String line = file.ReadLine().Trimmed();
                if (line.StartsWith("0") ) prgChecks[count] = "0";
                else  prgChecks[count] = "1";
                if (line.length > 1) prgArguments[count] = line.Substring(1);
                else prgArguments[count].Clear();
                count++;
            }
            file.Close();
        }
    }
    else // file not created or read-only file system, so make some defaults
    {
        prgChecks[12] = "1";
        prgArguments[12] = "Data;CoreData;Data/AUI;Data/AUI/Periodic";
        prgChecks[6] = "1";
        prgChecks[7] = "1";
    }
    
    GenerateExecArgs();
}

void WriteConfiguration()
{
    String configFilename = localVars["SettingsPath"].GetString() + "settings.txt";
    uint count = 0;
    File file( configFilename, FILE_WRITE);
    if (file.open)
    {
        for (uint nn=0; nn<prgNum; nn++ )
        {
            file.WriteLine( prgChecks[nn] + prgArguments[nn] );
        }
        file.Close();
    }
}
