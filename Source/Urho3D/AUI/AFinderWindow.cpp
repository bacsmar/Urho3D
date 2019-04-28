//
// Copyright (c) 2014-2017, THUNDERBEAST GAMES LLC All rights reserved
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include <TurboBadger/tb_widgets.h>
#include <TurboBadger/tb_widgets_common.h>

#include "../Precompiled.h"
#include "../IO/FileSystem.h"
#include "../IO/Log.h"
#include "../IO/File.h"

#include "../AUI/AUI.h"
#include "../AUI/AEvents.h"
#include "../AUI/AWindow.h"
#include "../AUI/AEditField.h"
#include "../AUI/ASelectList.h"
#include "../AUI/APromptWindow.h"
#include "../AUI/AFinderWindow.h"
#include "../AUI/ASelectItem.h"
#include "../AUI/AMenuWindow.h"

#ifdef URHO3D_ANGELSCRIPT
#include "../Core/Context.h"
#include "../Scene/Serializable.h"
extern const char* AUI_CATEGORY;  /// for angelscript binding
#endif

using namespace tb;

namespace Urho3D
{

/// finder window
AFinderWindow::AFinderWindow(Context* context, AWidget* target, const String& id, bool createWidget) : AWindow(context, false),
    finderMode_(0),
    bookmarksDirty_(0)
{
    if (createWidget)
    {
        widget_ = new TBFinderWindow(target ? target->GetInternalWidget() : 0, TBIDC(id.CString()));
        widget_->SetDelegate(this);
        GetSubsystem<AUI>()->WrapWidget(this, widget_);
    }
}

AFinderWindow::~AFinderWindow()
{
    SaveBookmarks();
    
    if ( !newFolderPtr_.Expired())
        newFolderPtr_->UnsubscribeFromAllEvents();
    if ( !newBookmarkPtr_.Expired() )
       newBookmarkPtr_->UnsubscribeFromAllEvents();

}

void AFinderWindow::FindFile(const String& title, const String& preset, int dimmer, int width, int height)
{
    if (!widget_)
        return;

    if ( ((TBFinderWindow*)widget_)->Show(title.CString(), preset.CString(), dimmer, width, height) )
    {
        CreateBookmarks();
        PresetCurrentPath(preset);
        UpdateUiPath();
        UpdateUiList();
        UpdateUiResult();
    }
}

void AFinderWindow::FindPath(const String& title, const String& preset, int dimmer, int width, int height)
{
    if (!widget_)
        return;

    finderMode_ = 1;
    
    if ( ((TBFinderWindow*)widget_)->Show(title.CString(), preset.CString(), dimmer, width, height) )
    {
        AWidget *reswid = GetResultWidget();
        if (reswid) reswid->SetVisibility( UI_WIDGET_VISIBILITY_INVISIBLE );
        CreateBookmarks();
        PresetCurrentPath(preset);
        UpdateUiPath();
        UpdateUiList();
        UpdateUiResult();
    }
}

bool AFinderWindow::OnEvent(const tb::TBWidgetEvent &ev)
{

    if ( ev.type == EVENT_TYPE_CHANGED && ev.target && ((uint32)ev.target->GetID()) == UIFINDEREDITPATHID ) 
    {
        FileSystem* filesystem = GetSubsystem<FileSystem>();
        AWidget *pathwidget = GetPathWidget();  // paste or type in currentpath widget
        if(pathwidget)
        {
            if ( filesystem->DirExists (pathwidget->GetText())) 
            {
                if ( pathwidget->GetText() != currentPath_ ) 
                {
                    resultPath_ = "";
                    SetCurrentPath (pathwidget->GetText());
                    UpdateUiList();
                    UpdateUiResult();
                }
            }
        }
        return true;
    }

   if ( ev.type == EVENT_TYPE_POINTER_UP && ev.target && ((uint32)ev.target->GetID()) == UIFINDERUPBUTTONID ) // go up
    {
        GoFolderUp();
        return true;
    }

    if ( ev.type == EVENT_TYPE_POINTER_UP && ev.target && ((uint32)ev.target->GetID()) == UIFINDERBOOKBUTTONID ) // add bookmark request
    {
        // this check is necessary because you can kill the bookmark window with the "X" and
        // this kills the AUI* but not the newBookmarkPtr to it, and it doesnt get cleaned up properly.
        if ( newBookmarkPtr_.NotNull() )
        {
            newBookmarkPtr_->UnsubscribeFromAllEvents();
            newBookmarkPtr_.Reset();
        }
        newBookmarkPtr_ = new APromptWindow(context_, this, "createbookmark",  true);
        SubscribeToEvent(newBookmarkPtr_, E_APROMPTCOMPLETE, URHO3D_HANDLER(AFinderWindow, HandleCreateBookmark ));

        String prospect = "";
        char delim = '/';
        Vector <String> tokens = currentPath_.Split(delim, false);
        prospect = tokens[ tokens.Size()-1 ]; // get the last folder name as preset
    
        newBookmarkPtr_->Show("Create New Bookmark", "Enter a name for the new bookmark", prospect );
        return true;
    }

    if ( ev.type == EVENT_TYPE_POINTER_UP && ev.target && ((uint32)ev.target->GetID()) == UIFINDERFOLDERBUTTONID ) // add folder request
    {
        if (newFolderPtr_.NotNull())
        {
            newFolderPtr_->UnsubscribeFromAllEvents();
            newFolderPtr_.Reset();
        }
        newFolderPtr_ = new APromptWindow(context_, this, "createfolder",  true);
        SubscribeToEvent(newFolderPtr_, E_APROMPTCOMPLETE, URHO3D_HANDLER(AFinderWindow, HandleCreateFolder));
        newFolderPtr_->Show("Create new folder", "Enter a name for the new folder", "" );
        return true;
    }

    if ( ev.type == EVENT_TYPE_CLICK && ev.target && ((uint32)ev.target->GetID()) == 5 ) // clicked in bookmarks
    {
        ASelectList *bklist = static_cast<ASelectList *>(GetBookmarksWidget());
        int selected = bklist->GetValue();
        if ( selected >= 0 )
        {
            resultPath_ = "";  // were going back, give up file.
            SetCurrentPath ( bookmarkPaths_[selected]);
            UpdateUiPath();
            UpdateUiList();
            UpdateUiResult();
            bklist->SetValue(-1); // clear the select visuals
        }
        return true;
    }
    
    if ( ev.type == EVENT_TYPE_CUSTOM && ev.target && ((uint32)ev.target->GetID()) == UIFINDERBOOKLISTID ) // bookmarks TB context menu result
    {
        AUI* ui = GetSubsystem<AUI>();
        if ( ev.special_key == tb::TB_KEY_DELETE ) // we wanna delete something
        {
            String myid;
            ui->GetTBIDString(ev.target?((uint32)ev.target->GetID()) : 0, myid);
            ASelectList *bklist = static_cast<ASelectList *>(GetBookmarksWidget());
            if (bklist)
            {
                int myindex = bklist->FindId ( (uint32)ev.ref_id );
                if ( myindex >= 0 )
                {
                    DeleteBookmark(myindex);
                }
            }
        }
        return true;
    }

    if ( ev.type == EVENT_TYPE_CLICK && ev.target && ((uint32)ev.target->GetID()) == UIFINDERFILELISTID ) // clicked dirfiles list
    {
        ASelectList *filelist = static_cast<ASelectList *>(GetFilesWidget());
        ComposePath( filelist->GetSelectedItemString() );
        return true;
    }

    if ( ev.type == EVENT_TYPE_CLICK && (ev.ref_id ==  UIFINDEROKBUTTONID|| ev.ref_id == UIFINDERCANCELBUTTONID ) ) // clicked ok or cancel button
    {
        AUI* ui = GetSubsystem<AUI>();
        VariantMap eventData;

        String title = "FinderWindow";
        TBStr tbtext;
        if(  widget_ && (TBWindow*)widget_->GetText(tbtext) )
            title = tbtext.CStr();

        eventData[AFinderComplete::P_TITLE] = title;
        eventData[AFinderComplete::P_SELECTED] = "";
        eventData[AFinderComplete::P_REASON] = "CANCEL";

        if (ev.ref_id == UIFINDEROKBUTTONID) // ok button was pressed, otherwise it was cancel button
        {
            eventData[AFinderComplete::P_REASON] = "OK";
            if ( finderMode_ == 0 ) // finding a file
            {   // get from widget, in case the user had been typing.
                AWidget *ewidget = GetResultWidget(); 
                if( ewidget) eventData[AFinderComplete::P_SELECTED] = ewidget->GetText();
            }
            else  // finding a folder
            {
                AWidget *cwidget = GetPathWidget();
                if( cwidget) eventData[AFinderComplete::P_SELECTED] = cwidget->GetText();
            }
        }

        ConvertEvent(this, ui->WrapWidget(ev.target), ev, eventData);
        SendEvent(E_AFINDERCOMPLETE, eventData);

        if (eventData[WidgetEvent::P_HANDLED].GetBool())
           return true;
    }

    return AWindow::OnEvent(ev);
}

void AFinderWindow::HandleCreateBookmark(StringHash eventType, VariantMap& eventData)
{
    const String& Title = eventData["Title"].GetString();
    const String& Reason = eventData["Reason"].GetString();
    const String& Selected = eventData["Selected"].GetString();

    if( Reason == "OK" )
        CreateBookmark( Selected, currentPath_ );
    if (newBookmarkPtr_)
    {
        newBookmarkPtr_->UnsubscribeFromAllEvents();
        newBookmarkPtr_.Reset();
    }
}

void AFinderWindow::HandleCreateFolder(StringHash eventType, VariantMap& eventData)
{
    const String& Title = eventData["Title"].GetString();
    const String& Reason = eventData["Reason"].GetString();
    const String& Selected = eventData["Selected"].GetString();

    if( Reason == "OK" )
        CreateFolder(Selected); 
    if (newFolderPtr_)
    {
         newFolderPtr_->UnsubscribeFromAllEvents();
         newFolderPtr_.Reset();
    }
}

AWidget* AFinderWindow::GetWindowWidget()
{
    if (!widget_)
        return 0;
    AUI* ui = GetSubsystem<AUI>();
    return ui->WrapWidget(widget_);
}

AWidget* AFinderWindow::GetPathWidget()
{
    if (!widget_)
        return 0;
    TBWidget* child = (TBWidget*) widget_->GetWidgetByIDAndType<TBEditField>(UIFINDEREDITPATHID);
    if (!child)
        return 0;
    AUI* ui = GetSubsystem<AUI>();
    return ui->WrapWidget(child);
}

AWidget* AFinderWindow::GetResultWidget()
{
    if (!widget_)
        return 0;
    TBWidget* child = (TBWidget*)widget_->GetWidgetByIDAndType<TBEditField>(UIFINDEREDITFILEID);
    if (!child)
        return 0;
    AUI* ui = GetSubsystem<AUI>();
    return ui->WrapWidget(child);
}

AWidget* AFinderWindow::GetBookmarksWidget()
{
    if (!widget_)
        return 0;
    TBWidget* child = (TBWidget*)widget_->GetWidgetByIDAndType<TBSelectList>(UIFINDERBOOKLISTID);
    if (!child)
        return 0;
    AUI* ui = GetSubsystem<AUI>();
    return ui->WrapWidget(child);
}

AWidget* AFinderWindow::GetFilesWidget()
{
    if (!widget_)
        return 0;
    TBWidget* child = (TBWidget*)widget_->GetWidgetByIDAndType<TBSelectList>(UIFINDERFILELISTID);
    if (!child)
        return 0;
    AUI* ui = GetSubsystem<AUI>();
    return ui->WrapWidget(child);
}

// where the finder starts
void AFinderWindow::PresetCurrentPath( const String& preset ) 
{
    FileSystem* filesystem = GetSubsystem<FileSystem>();
    if ( !preset.Empty() && filesystem->DirExists (preset) )
        SetCurrentPath (preset);
    else
        SetCurrentPath ( filesystem->GetUserDocumentsDir() );
}

// set the current path value
void AFinderWindow::SetCurrentPath( const String& string ) 
{ 
    currentPath_ = string;
}

//using the list, jam things together, we'll either get another path or a file.
void AFinderWindow::ComposePath (const String& string )
{
    String prospect = currentPath_ + string;

    FileSystem* filesystem = GetSubsystem<FileSystem>();
 
    if ( !filesystem->FileExists ( prospect ) )  // its a dir, feel the joy
    {
        SetCurrentPath( prospect + "/" );  // add the trailing slash, OR ELSE
        UpdateUiPath();
        UpdateUiList();
        UpdateUiResult();
    }
    else  // its a file
    {
        resultPath_ = prospect;
        UpdateUiResult();
    }
}

// create the list of bookmarks ... can be different per platform
void AFinderWindow::CreateBookmarks()
{
    FileSystem* filesystem = GetSubsystem<FileSystem>();
    String basepath = filesystem->GetUserDocumentsDir();
    ASelectList *bklist = static_cast<ASelectList *>(GetBookmarksWidget());
    
#if defined(__linux__) 
    if ( filesystem->DirExists ( basepath )) CreateBookmark ( "Home", basepath );
    if ( filesystem->DirExists ( basepath + "Documents")) CreateBookmark ( "Documents", basepath + "Documents/" );
    if ( filesystem->DirExists ( basepath + "Music")) CreateBookmark ( "Music", basepath + "Music/" );
    if ( filesystem->DirExists ( basepath + "Pictures" )) CreateBookmark ( "Pictures", basepath + "Pictures/" );
    if ( filesystem->DirExists ( basepath + "Videos" )) CreateBookmark ( "Videos", basepath + "Videos/" );
    if ( filesystem->DirExists ( basepath + "Downloads")) CreateBookmark ( "Downloads", basepath + "Downloads/" );
#elif defined(_WIN32)
    if ( filesystem->DirExists ( basepath )) CreateBookmark ( "Home", basepath );
    if ( filesystem->DirExists ( basepath + "Desktop")) CreateBookmark ( "Desktop", basepath + "Desktop/" );
    if ( filesystem->DirExists ( basepath + "Documents")) CreateBookmark ( "Documents", basepath + "Documents/" );
    if ( filesystem->DirExists ( basepath + "Downloads")) CreateBookmark ( "Downloads", basepath + "Downloads/" );
    if ( filesystem->DirExists ( basepath + "Music")) CreateBookmark ( "Music", basepath + "Music/" );
    if ( filesystem->DirExists ( basepath + "Pictures" )) CreateBookmark ( "Pictures", basepath + "Pictures/" );
    if ( filesystem->DirExists ( basepath + "Videos" )) CreateBookmark ( "Videos", basepath + "Videos/" );
#elif defined(__APPLE__)
    if ( filesystem->DirExists ( basepath )) CreateBookmark ( "Home", basepath );
    if ( filesystem->DirExists ( basepath + "Documents")) CreateBookmark ( "Documents", basepath + "Documents/" );
    if ( filesystem->DirExists ( basepath + "Downloads")) CreateBookmark ( "Downloads", basepath + "Downloads/" );
    if ( filesystem->DirExists ( basepath + "Public")) CreateBookmark ( "Public", basepath + "Public/" );
#else  // android, ios, web?
    if ( filesystem->DirExists ( basepath )) CreateBookmark ( "Home", basepath );
#endif
    CreateBookmark ( "-", basepath );  // create separator!
    LoadBookmarks();
    bklist->SetValue(-1); // fix the selection and scrolling

}

// go up tree 1 folder
void AFinderWindow::GoFolderUp()
{
    String prospect = "";
    char delim = '/';
    Vector <String> tokens = currentPath_.Split(delim, false);
 
    if ( tokens.Size() == 0 ) // were at the top
        prospect = "/";
    else
    {
        int nn = 0;
        for ( nn=0; nn<tokens.Size()-1; nn++ )
        {
            prospect += delim;
            prospect += tokens[nn];
        }
        prospect += delim;
    }

    if ( prospect != currentPath_ ) 
    {
        resultPath_ = "";
        SetCurrentPath (prospect);
        UpdateUiPath();
        UpdateUiList();
        UpdateUiResult();
    }
}

// move current path to widget
void AFinderWindow::UpdateUiPath ()
{
    AWidget *pathwidget = GetPathWidget();
    if(pathwidget)
    {
        if ( pathwidget->GetText() != currentPath_ )
            pathwidget->SetText(currentPath_);
    }
}

// move result path to widget
void AFinderWindow::UpdateUiResult ()
{
    AWidget *resultwidget = GetResultWidget();
    if( resultwidget)
    {
        if ( resultwidget->GetText() != resultPath_ )
            resultwidget->SetText(resultPath_);
    }
}

#include "Container/Sort.h"

// a very local compare function
bool CompareStrs(const String& a, const String &b)  
{
    return a < b;
}

// move folder contents into list
void AFinderWindow::UpdateUiList()
{
    FileSystem* filesystem = GetSubsystem<FileSystem>();
    ASelectList *filelist = static_cast<ASelectList *>(GetFilesWidget());
    ASelectItemSource *fileSource = new ASelectItemSource(context_);
    
    if ( filesystem->DirExists (currentPath_ ) )
    { 
        Vector <String> mydirs;
        int nn = 0;
        filesystem->ScanDir (mydirs,currentPath_, "*", SCAN_DIRS, false );
        Sort(mydirs.Begin(), mydirs.End(), CompareStrs); // sort them
        for ( nn=0; nn<mydirs.Size(); nn++ ) 
        {
            if ( mydirs[nn] == "." ) continue;  
            if ( mydirs[nn] == ".." ) continue;
            String idz = "DIR"+ String(nn);
            fileSource->AddItem( new ASelectItem(context_, mydirs[nn], idz, "FolderIcon" ));
        }
        Vector <String> myfiles;
        filesystem->ScanDir (myfiles, currentPath_, "*", SCAN_FILES, false );
        Sort(myfiles.Begin(), myfiles.End(), CompareStrs);
        for ( nn=0; nn<myfiles.Size(); nn++ ) 
        {
            String idz = "FIL"+ String(nn);
            fileSource->AddItem(new ASelectItem( context_, myfiles[nn], idz));
        }
    }
    filelist->SetValue(-1);
    filelist->SetSource(fileSource);
}

// utility to add a folder in current path
void AFinderWindow::CreateFolder( const String& string )
{
    FileSystem* filesystem = GetSubsystem<FileSystem>();
    if ( filesystem->CreateDir( currentPath_ + string ) )
    {
        UpdateUiList();
    }
}

// utility to add a bookmark from the current path
void AFinderWindow::CreateBookmark ( const String& bkname, const String&  bkpath ) 
{
    ASelectList *bklist = static_cast<ASelectList *>(GetBookmarksWidget());
    if (bklist ) 
    {
        int inspos = bklist->GetNumItems();
        if ( inspos < 0 ) inspos = 0;
        String idz = "BKM" + String(inspos);
        if ( bklist->AddItem ( inspos, bkname, idz ) )
        {
            bookmarks_.Push(bkname);
            bookmarkPaths_.Push (bkpath);
            bookmarksDirty_ = 1;
        }
    }
}

// removes a bookmark based upon its index in the bookmark list
void AFinderWindow::DeleteBookmark ( int bkindex )
{
    ASelectList *bklist = static_cast<ASelectList *>(GetBookmarksWidget());
    if (bklist && bkindex >= 0) 
    {
        bklist->DeleteItem(bkindex);
        bookmarks_.Erase(bkindex,1);
        bookmarkPaths_.Erase(bkindex,1);
        resultPath_ = "";
        SetCurrentPath (bookmarkPaths_[0]);
        UpdateUiPath();
        UpdateUiList();
        UpdateUiResult();
        bklist->SetValue(-1);
        bookmarksDirty_ = 1;
    }
}

void AFinderWindow::LoadBookmarks()
{
    FileSystem* filesystem = GetSubsystem<FileSystem>();
    String bkdata = "";
    String bkpath = "";
    
#if defined(__ANDROID__) || defined(IOS)  || defined(TVOS)
    bkpath = filesystem->GetUserDocumentsDir(); // somewhere writable on mobile
#else
    bkpath = filesystem->GetAppPreferencesDir("urho3d", "Bookmarks"); // desktop systems
#endif
    
    bkpath += "/Bookmarks.txt";
    if ( filesystem->FileExists ( bkpath ) )
    {
        File *fp = new File (context_, bkpath, FILE_READ);
        if(fp->IsOpen())
        {
            /// ATOMIC ReadText missing
            fp->ReadText(bkdata);
            fp->Close();
        }
    }
    char delim = '\n';
    Vector <String> tokens = bkdata.Split(delim, false);
    int nn=0;
    for ( nn=0; nn< tokens.Size(); nn+=2)
    {
        CreateBookmark ( tokens[nn], tokens[nn+1] );
    }
    bookmarksDirty_ = 0;

}

void AFinderWindow::SaveBookmarks()
{
    if ( bookmarksDirty_ > 0 )
    {
        FileSystem* filesystem = GetSubsystem<FileSystem>();
        String bkpath = "";

#if defined(__ANDROID__) || defined(IOS)  || defined(TVOS)
        bkpath = filesystem->GetUserDocumentsDir();
#else
        bkpath = filesystem->GetAppPreferencesDir("urho3d", "Bookmarks");
#endif

        bkpath += "/Bookmarks.txt";
        String bkdata = "";
        int nn=0, sep=-1;
        for ( nn = 0; nn<bookmarks_.Size(); nn++)
        {
            if ( sep > 0 )
            {
                bkdata += bookmarks_[nn];
                bkdata += "\n";
                bkdata += bookmarkPaths_[nn];
                bkdata += "\n";
            }
            if ( bookmarks_[nn] == "-" ) 
                sep = nn;
        }
        File *fp = new File (context_, bkpath, FILE_WRITE);
        if(fp->IsOpen())
        {
            fp->Write ((const void *)bkdata.CString(), bkdata.Length() );
            fp->Close();
        }
    }
}

#ifdef URHO3D_ANGELSCRIPT
/// Angelscript Register object factory. (semi-manditory)
void AFinderWindow::RegisterObject(Context* context)
{
    context->RegisterFactory<AFinderWindow>(AUI_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(AWindow);
}
#endif

}
