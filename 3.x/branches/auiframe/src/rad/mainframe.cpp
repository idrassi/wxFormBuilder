///////////////////////////////////////////////////////////////////////////////
//
// wxFormBuilder - A Visual Dialog Editor for wxWidgets.
// Copyright (C) 2005 José Antonio Hurtado
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
// Written by
//   José Antonio Hurtado - joseantonio.hurtado@gmail.com
//   Juan Antonio Ortega  - jortegalalmolda@gmail.com
//
///////////////////////////////////////////////////////////////////////////////
#include "mainframe.h"

#include "wx/config.h"
#include "utils/debug.h"
#include "utils/typeconv.h"
#include "rad/title.h"
#include "rad/bitmaps.h"
#include "rad/cpppanel/cpppanel.h"
#include "rad/pythonpanel/pythonpanel.h"
#include "rad/xrcpanel/xrcpanel.h"
#include "rad/geninheritclass/geninhertclass.h"
#include "inspector/objinspect.h"
#include "objecttree/objecttree.h"
#include "palette.h"
#include "rad/designer/visualeditor.h"

#ifdef WXFB_USE_AUI
//    #include "rad/aui/settingspanel.h"
#endif

#include "model/xrcfilter.h"
#include "rad/about.h"
#include "rad/prefs/prefs.h"
#include "rad/wxfbevent.h"
#include "wxfbmanager.h"
#include "utils/wxfbexception.h"
#include "utils/stringutils.h"
#include "utils/wxfbdefs.h"
#include <wx/filename.h>

#include <rad/appdata.h>
#include "model/objectbase.h"

#include <wx/wxScintilla/wxscintilla.h>

#include <wx/artprov.h>

#define ID_NEW_PRJ       104
#define ID_GENERATE_CODE 105
#define ID_IMPORT_XRC    106

#define ID_EXPAND        114
#define ID_STRETCH       115
#define ID_MOVE_UP       116
#define ID_MOVE_DOWN     117
#define ID_RECENT_0      118 // Tienen que tener ids consecutivos
#define ID_RECENT_1      119 // ID_RECENT_n+1 == ID_RECENT_n + 1
#define ID_RECENT_2      120 //
#define ID_RECENT_3      121 //
#define ID_RECENT_SEP    122

#define ID_ALIGN_LEFT     123
#define ID_ALIGN_CENTER_H 124
#define ID_ALIGN_RIGHT    125
#define ID_ALIGN_TOP      126
#define ID_ALIGN_CENTER_V 127
#define ID_ALIGN_BOTTOM   128

#define ID_BORDER_LEFT    129
#define ID_BORDER_RIGHT   130
#define ID_BORDER_TOP     131
#define ID_BORDER_BOTTOM  132
#define ID_EDITOR_FNB	  133
#define ID_MOVE_LEFT	  134
#define ID_MOVE_RIGHT     135

#define ID_PREVIEW_XRC     136
#define ID_GEN_INHERIT_CLS 137

#define ID_CLIPBOARD_COPY 143
#define ID_CLIPBOARD_PASTE 144

#define STATUS_FIELD_OBJECT 2
#define STATUS_FIELD_PATH 1

BEGIN_EVENT_TABLE( MainFrame, wxFrame )
EVT_MENU( ID_NEW_PRJ,  MainFrame::OnNewProject )
EVT_MENU( wxID_SAVE,   MainFrame::OnSaveProject )
EVT_MENU( wxID_SAVEAS, MainFrame::OnSaveAsProject )
EVT_MENU( wxID_OPEN,   MainFrame::OnOpenProject )
EVT_MENU( wxID_ABOUT,  MainFrame::OnAbout )
EVT_MENU( wxID_EXIT,   MainFrame::OnExit )

EVT_MENU( ID_IMPORT_XRC,    MainFrame::OnImportXrc )
EVT_MENU( ID_GENERATE_CODE, MainFrame::OnGenerateCode )

EVT_MENU( wxID_UNDO,   MainFrame::OnUndo )
EVT_MENU( wxID_REDO,   MainFrame::OnRedo )
EVT_MENU( wxID_DELETE, MainFrame::OnDelete )
EVT_MENU( wxID_CUT,    MainFrame::OnCut )
EVT_MENU( wxID_COPY,   MainFrame::OnCopy )
EVT_MENU( wxID_PASTE,  MainFrame::OnPaste )

EVT_MENU( ID_EXPAND,  MainFrame::OnToggleExpand )
EVT_MENU( ID_STRETCH, MainFrame::OnToggleStretch )

EVT_MENU( wxID_UP,       MainFrame::OnMoveUp )
EVT_MENU( wxID_DOWN,     MainFrame::OnMoveDown )
EVT_MENU( wxID_BACKWARD, MainFrame::OnMoveLeft )
EVT_MENU( wxID_FORWARD,  MainFrame::OnMoveRight )

EVT_MENU( ID_RECENT_0, MainFrame::OnOpenRecent )
EVT_MENU( ID_RECENT_1, MainFrame::OnOpenRecent )
EVT_MENU( ID_RECENT_2, MainFrame::OnOpenRecent )
EVT_MENU( ID_RECENT_3, MainFrame::OnOpenRecent )

EVT_MENU( ID_ALIGN_RIGHT,    MainFrame::OnChangeAlignment )
EVT_MENU( ID_ALIGN_LEFT,     MainFrame::OnChangeAlignment )
EVT_MENU( ID_ALIGN_CENTER_H, MainFrame::OnChangeAlignment )
EVT_MENU( ID_ALIGN_TOP,      MainFrame::OnChangeAlignment )
EVT_MENU( ID_ALIGN_BOTTOM,   MainFrame::OnChangeAlignment )
EVT_MENU( ID_ALIGN_CENTER_V, MainFrame::OnChangeAlignment )

EVT_MENU_RANGE( ID_BORDER_LEFT, ID_BORDER_BOTTOM, MainFrame::OnChangeBorder )

EVT_MENU( ID_PREVIEW_XRC,     MainFrame::OnXrcPreview )
EVT_MENU( ID_GEN_INHERIT_CLS, MainFrame::OnGenInhertedClass )

EVT_MENU( ID_CLIPBOARD_COPY,  MainFrame::OnClipboardCopy )
EVT_MENU( ID_CLIPBOARD_PASTE, MainFrame::OnClipboardPaste )

#ifdef WXFB_USE_AUI
//EVT_MENU( ID_AUI_SETTINGS, MainFrame::OnAuiSettings )
#endif

EVT_UPDATE_UI( ID_CLIPBOARD_PASTE, MainFrame::OnClipboardPasteUpdateUI )

EVT_CLOSE( MainFrame::OnClose )

EVT_FB_CODE_GENERATION(        MainFrame::OnCodeGeneration )
EVT_FB_OBJECT_CREATED(         MainFrame::OnObjectCreated )
EVT_FB_OBJECT_REMOVED(         MainFrame::OnObjectRemoved )
EVT_FB_OBJECT_EXPANDED(        MainFrame::OnObjectExpanded )
EVT_FB_OBJECT_SELECTED(        MainFrame::OnObjectSelected )
EVT_FB_PROJECT_LOADED(         MainFrame::OnProjectLoaded )
EVT_FB_PROJECT_REFRESH(        MainFrame::OnProjectRefresh )
EVT_FB_PROJECT_SAVED(          MainFrame::OnProjectSaved )
EVT_FB_PROPERTY_MODIFIED(      MainFrame::OnPropertyModified )
EVT_FB_EVENT_HANDLER_MODIFIED( MainFrame::OnEventHandlerModified )

EVT_MENU( wxID_FIND, MainFrame::OnFindDialog )
EVT_FIND( wxID_ANY, MainFrame::OnFind )
EVT_FIND_NEXT( wxID_ANY, MainFrame::OnFind )
EVT_FIND_CLOSE( wxID_ANY, MainFrame::OnFindClose )

EVT_MENU( wxID_PREFERENCES, MainFrame::OnPreferences )

END_EVENT_TABLE()

// Used to kill focus from propgrid when toolbar or menu items are clicked
// This forces the propgrid to save the cell being edited
class FocusKillerEvtHandler : public wxEvtHandler
{
public:
	void OnMenuEvent( wxCommandEvent& event )
	{
		// Get window with focus
		wxWindow* windowWithFocus = wxWindow::FindFocus();

		// Only send the event if the focus is on the propgrid
		while ( windowWithFocus != NULL )
		{
			wxPropertyGrid* propgrid = wxDynamicCast( windowWithFocus, wxPropertyGrid );
			if ( propgrid != NULL )
			{
				wxFocusEvent focusEvent( wxEVT_KILL_FOCUS );
				propgrid->ProcessEvent( focusEvent );
				break;
			}
			windowWithFocus = windowWithFocus->GetParent();
		}

		// Add the event to the mainframe's original handler
		// Add as pending so propgrid saves the property before the event is processed
		GetNextHandler()->AddPendingEvent( event );
	}

	DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE( FocusKillerEvtHandler, wxEvtHandler )
	EVT_MENU( wxID_ANY, FocusKillerEvtHandler::OnMenuEvent )
END_EVENT_TABLE()

MainFrame::MainFrame( wxWindow *parent, int id, int style, wxPoint pos, wxSize size )
:
wxFrame( parent, id, wxEmptyString, pos, size, wxDEFAULT_FRAME_STYLE ),
#ifndef WXFB_USE_AUI
m_leftSplitterWidth( 300 ),
m_rightSplitterWidth( -300 ),
#endif
m_style( style ),
m_page_selection( 0 ),
#ifndef WXFB_USE_AUI
m_rightSplitter_sash_pos( 300 ),
m_autoSash( false ), // autosash function is temporarily disabled due to possible bug(?) in wxMSW event system (workaround is needed)
#endif
m_findData( wxFR_DOWN ),
m_findDialog( NULL )
{
#ifndef WXFB_USE_AUI
	// initialize the splitters, wxAUI doesn't use them
	m_leftSplitter = m_rightSplitter = NULL;
#endif
	/////////////////////////////////////////////////////////////////////////////
	// Setup frame icons, title bar, status bar, menubar and toolbar
	/////////////////////////////////////////////////////////////////////////////
	wxIconBundle bundle;
	wxIcon ico16;
	ico16.CopyFromBitmap( AppBitmaps::GetBitmap( wxT("app16"), 16 ) );
	bundle.AddIcon( ico16 );

	wxIcon ico32;
	ico32.CopyFromBitmap( AppBitmaps::GetBitmap( wxT("app32"), 32 ) );
	bundle.AddIcon( ico32 );

	SetIcons( bundle );

	SetTitle( wxT("wxFormBuilder") );

	//SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNFACE ) );

	SetMenuBar( CreateFBMenuBar() );
	CreateStatusBar( 3 );
	SetStatusBarPane( 0 );
	int widths[3] = { -1, -1, 300 };
	SetStatusWidths( sizeof( widths ) / sizeof( int ), widths );
#ifndef WXFB_USE_AUI
	CreateFBToolBar();
#endif
	/////////////////////////////////////////////////////////////////////////////
	// Create the gui
	/////////////////////////////////////////////////////////////////////////////

#ifdef WXFB_USE_AUI
    m_toolbar = NULL;
	wxWindow *objectTree      = CreateObjectTree(this);
	wxWindow *objectInspector = CreateObjectInspector(this);
	wxWindow *palette         = CreateComponentPalette(this);
	wxWindow *designer        = CreateDesignerWindow(this);

	m_mgr.SetManagedWindow(this);

	m_mgr.AddPane( RecreateFBAuiToolBar(), wxAuiPaneInfo().Name(wxT("toolbar")).Caption(_("Toolbar")).
                ToolbarPane().Gripper( false ).
                Dock().Top().
                Resizable().DockFixed( true ).Movable( false ).Floatable( false ).Layer( 10 ) );

	m_mgr.AddPane( palette, wxAuiPaneInfo().Name(wxT("palette")).Caption(_("Component Palette")).
                CaptionVisible( false ).CloseButton( false ).
                MaximizeButton( false ).MinimizeButton( false ).PinButton( false ).PaneBorder( false ).Gripper( false ).
                BottomDockable( false ).TopDockable( false ).LeftDockable( false ).RightDockable( false ).
                Dock().Top().
                Resizable().DockFixed( true ).Movable( false ).Floatable( false ).
                BestSize( wxSize( -1,66 ) ) );

	m_mgr.AddPane( designer,
                wxAuiPaneInfo().Name(wxT("editor")).Caption(_("Editor")).
                CentrePane().
                CaptionVisible( false ).CloseButton( false ).
                MaximizeButton( false ).MinimizeButton( false ).PinButton( false ).PaneBorder( false ).Gripper( false ).
                BottomDockable( false ).TopDockable( false ).LeftDockable( false ).RightDockable( false ).
                Dock().Center().
                Resizable().DockFixed( true ).Movable( false ).Floatable( false ) );

	m_mgr.AddPane( objectTree,
                wxAuiPaneInfo().Name(wxT("tree")).Caption(_("Object Tree")).
                CaptionVisible( true ).CloseButton( false ).
                MaximizeButton( false ).MinimizeButton( false ).PinButton( false ).PaneBorder( true ).Gripper( false ).
                BottomDockable( false ).TopDockable( false ).LeftDockable( true ).RightDockable( true ).
                Dock().Left().
                Resizable().DockFixed( false ).Movable( true ).Floatable( true ).
                FloatingSize( wxSize( 300,400 ) ).BestSize( wxSize( 300,-1 ) ).Layer( 1 ) );

	m_mgr.AddPane(objectInspector,
                wxAuiPaneInfo().Name(wxT("inspector")).Caption(_("Object Properties")).
                CaptionVisible( true ).CloseButton( false ).
                MaximizeButton( false ).MinimizeButton( false ).PinButton( false ).PaneBorder( true ).Gripper( false ).
                BottomDockable( false ).TopDockable( false ).LeftDockable( true ).RightDockable( true ).
                Dock().Right().
                Resizable().DockFixed( false ).Movable( true ).Floatable( true ).
                FloatingSize( wxSize( 300,400 ) ).BestSize( wxSize( 300,-1 ) ).Row( 1 ).Layer( 0 ) );
/*
  m_mgr.AddPane(new AuiSettingsPanel( this, this ),
                wxAuiPaneInfo().Name(wxT("settings")).
                Caption( _("Dock Manager Settings") ).
                Dockable(false).Float().Hide());
*/
	m_mgr.Update();

  wxConfigBase *config = wxConfigBase::Get();

  wxString Perspective;
  if ( config->Read( wxT("/mainframe/aui/perspective"), &Perspective ) )
    m_mgr.LoadPerspective(Perspective);

#endif // WXFB_USE_AUI
	RestorePosition( wxT("mainframe") );
	Layout();

	// Init. m_cpp and m_xrc first
	m_cpp = NULL;
	m_xrc = NULL;
	m_python = NULL;
#ifndef WXFB_USE_AUI
	switch ( style )
	{

		case wxFB_DOCKABLE_GUI:
			// TO-DO
			CreateWideGui();

			break;

		case wxFB_CLASSIC_GUI:

			/*  //  --- Classic style Gui --
			     //
			     //  +------++-----------------------+
			     //  | Obj. ||  Palette              |
			     //  | Tree ++-----------------------+
			     //  |      ||  Editor               |
			     //  |______||                       |
			     //  |------||                       |
			     //  | Obj. ||                       |
			     //  | Insp.||                       |
			     //  |      ||                       |
			     //  |      ||                       |
			     //  +------++-----------------------+ 	*/

			CreateClassicGui();

			break;

		case wxFB_DEFAULT_GUI:

		case wxFB_WIDE_GUI:

		default:

			/*  //  --- Wide style Gui --
			      //
			      //  +------++-----------------------+
			      //  | Obj. ||  Palette              |
			      //  | Tree ++-------------++--------+
			      //  |      ||  Editor     || Obj.   |
			      //  |      ||             || Insp.  |
			      //  |      ||             ||        |
			      //  |      ||             ||        |
			      //  |      ||             ||        |
			      //  |      ||             ||        |
			      //  |      ||             ||        |
			      //  +------++-------------++--------+ 	*/

			CreateWideGui();
	}
#endif // WXFB_USE_AUI
	AppData()->AddHandler( this->GetEventHandler() );

	wxTheApp->SetTopWindow( this );

	m_focusKillEvtHandler = new FocusKillerEvtHandler;
	PushEventHandler( m_focusKillEvtHandler );

#ifdef WXFB_USE_AUI
    m_notebook->Connect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED, wxAuiNotebookEventHandler( MainFrame::OnAuiNotebookPageChanged ), 0, this );
#else
	// So splitter windows can be restored correctly
	Connect( wxEVT_IDLE, wxIdleEventHandler( MainFrame::OnIdle ) );

	// So we don't respond to a FlatNoteBookPageChanged event during construction
	m_notebook->Connect( wxEVT_COMMAND_FLATNOTEBOOK_PAGE_CHANGED, wxFlatNotebookEventHandler( MainFrame::OnFlatNotebookPageChanged ), 0, this );
#endif
};


MainFrame::~MainFrame()
{
#ifdef WXFB_USE_AUI
    m_notebook->Disconnect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED, wxAuiNotebookEventHandler( MainFrame::OnAuiNotebookPageChanged ), 0, this );
#else
	m_notebook->Disconnect( wxEVT_COMMAND_FLATNOTEBOOK_PAGE_CHANGED, wxFlatNotebookEventHandler( MainFrame::OnFlatNotebookPageChanged ), 0, this );
#endif

#ifdef __WXMAC__
    // work around problem on wxMac
    m_rightSplitter->GetWindow1()->GetSizer()->Detach(m_notebook);
    m_notebook->Destroy();
#endif

#ifdef WXFB_USE_AUI
    m_mgr.UnInit();
#endif

	// the focus killer event handler
	RemoveEventHandler( m_focusKillEvtHandler );
	delete m_focusKillEvtHandler;

	AppData()->RemoveHandler( this->GetEventHandler() );
	delete m_findDialog;
}

void MainFrame::RestorePosition( const wxString &name )
{
	m_currentDir = wxT("./projects");

	wxConfigBase *config = wxConfigBase::Get();
	config->SetPath( name );

	bool maximized;
	config->Read( wxT("IsMaximized"), &maximized, true );

	if ( maximized )
	{
		Maximize( maximized );
	}
	else
	{
		bool iconized;
		config->Read( wxT("IsIconized"), &iconized, false );

		if ( iconized )
		{
			Iconize( iconized );
		}
	}
#ifndef WXFB_USE_AUI
	config->Read( wxT("LeftSplitterWidth"), &m_leftSplitterWidth, 300 );
	config->Read( wxT("RightSplitterWidth"), &m_rightSplitterWidth, -300 );
	config->Read( wxT("AutoSash"), &m_autoSash, false ); // disabled in default due to possible bug(?) in wxMSW
#endif
	config->Read( wxT("CurrentDirectory"), &m_currentDir );

	config->Read( wxT("RecentFile0"), &m_recentProjects[0] );
	config->Read( wxT("RecentFile1"), &m_recentProjects[1] );
	config->Read( wxT("RecentFile2"), &m_recentProjects[2] );
	config->Read( wxT("RecentFile3"), &m_recentProjects[3] );

	config->SetPath( wxT("..") );
	UpdateRecentProjects();
}

void MainFrame::SavePosition( const wxString &name )
{
	m_objInsp->SavePosition();

	wxConfigBase *config = wxConfigBase::Get();
	bool isIconized = IsIconized();
	bool isMaximized = IsMaximized();

	config->SetPath( name );

	if ( !isMaximized )
	{
		config->Write( wxT("PosX"), isIconized ? -1 : GetPosition().x );
		config->Write( wxT("PosY"), isIconized ? -1 : GetPosition().y );
		config->Write( wxT("SizeW"), isIconized ? -1 : GetSize().GetWidth() );
		config->Write( wxT("SizeH"), isIconized ? -1 : GetSize().GetHeight() );
	}

	config->Write( wxT("IsMaximized"), isMaximized );

	config->Write( wxT("IsIconized"), isIconized );
	config->Write( wxT("CurrentDirectory"), m_currentDir );

	config->Write( wxT("RecentFile0"), m_recentProjects[0] );
	config->Write( wxT("RecentFile1"), m_recentProjects[1] );
	config->Write( wxT("RecentFile2"), m_recentProjects[2] );
	config->Write( wxT("RecentFile3"), m_recentProjects[3] );
#ifndef WXFB_USE_AUI
	if ( m_leftSplitter )
	{
		int leftSashWidth = m_leftSplitter->GetSashPosition();
		config->Write( wxT("LeftSplitterWidth"), leftSashWidth );
	}

	if ( m_rightSplitter )
	{
		switch ( m_style )
		{

			case wxFB_WIDE_GUI:
				{
					int rightSash = -1 * ( m_rightSplitter->GetSize().GetWidth() - m_rightSplitter->GetSashPosition() );
					config->Write( wxT("RightSplitterWidth"), rightSash );
					break;
				}

			case wxFB_CLASSIC_GUI:
				{
					int rightSash = -1 * ( m_rightSplitter->GetSize().GetHeight() - m_rightSplitter->GetSashPosition() );
					config->Write( wxT("RightSplitterWidth"), rightSash );
					break;
				}

			default:
				break;
		}
	}
#endif // WXFB_USE_AUI
	config->SetPath( wxT("..") );
#ifdef WXFB_USE_AUI
	config->Write( wxT("/mainframe/editor/auinbook_style"), m_notebook->GetWindowStyleFlag() );

    wxString Perspective = m_mgr.SavePerspective();
    config->Write( wxT("/mainframe/aui/perspective"), Perspective );
#else
	config->Write( wxT("/mainframe/editor/notebook_style"), m_notebook->GetWindowStyleFlag() );
#endif
}

void MainFrame::OnSaveProject( wxCommandEvent &event )

{
	wxString filename = AppData()->GetProjectFileName();

	if ( filename == wxT("") )
		OnSaveAsProject( event );
	else
	{
		try
		{
			AppData()->SaveProject( filename );
			InsertRecentProject( filename );
		}
		catch ( wxFBException& ex )
		{
			wxLogError( ex.what() );
		}
	}
}

void MainFrame::OnSaveAsProject( wxCommandEvent & )
{
	wxFileDialog *dialog = new wxFileDialog( this, _("Save Project"), m_currentDir,
	                       wxT(""), wxT("wxFormBuilder Project File (*.fbp)|*.fbp|") + wxString(_("All files") ) + wxT(" (*.*)|*.*"), wxFD_SAVE );

	if ( dialog->ShowModal() == wxID_OK )
	{
		m_currentDir = dialog->GetDirectory();
		wxString filename = dialog->GetPath();

		// Add the default extension if none was chosen
		wxFileName file( filename );

		if ( !file.HasExt() )
		{
			file.SetExt( wxT("fbp") );
			filename = file.GetFullPath();
		}

		// Check the file whether exists or not
		if ( file.FileExists() == true )
		{
		    wxMessageDialog msg_box( this, _("The file already exists. Do you want to replace it?"), _("Overwrite the file"), wxYES_NO|wxICON_INFORMATION|wxNO_DEFAULT );
		    if( msg_box.ShowModal() == wxID_NO )
			{
		        dialog->Destroy();
		        return;
		    }
		}

		try
		{
			AppData()->SaveProject( filename );
			InsertRecentProject( filename );
		}
		catch ( wxFBException& ex )
		{
			wxLogError( ex.what() );
		}
	};

	dialog->Destroy();
}

void MainFrame::OnOpenProject( wxCommandEvent &)
{
	if ( !SaveWarning() )
		return;

	wxFileDialog *dialog = new wxFileDialog( this, _("Open Project"), m_currentDir,
	                       wxT(""), wxT("wxFormBuilder Project File (*.fbp)|*.fbp|") + wxString(_("All files") ) + wxT(" (*.*)|*.*"), wxFD_OPEN );

	if ( dialog->ShowModal() == wxID_OK )
	{
		m_currentDir = dialog->GetDirectory();
		wxString filename = dialog->GetPath();

		if ( AppData()->LoadProject( filename ) )
			InsertRecentProject( filename );
	};

	dialog->Destroy();
}

void MainFrame::OnOpenRecent( wxCommandEvent &event )
{
    if ( !SaveWarning() )
		return;

	int i = event.GetId() - ID_RECENT_0;

	assert ( i >= 0 && i < 4 );

	wxFileName filename( m_recentProjects[i] );

    if(filename.FileExists())
    {
        if ( AppData()->LoadProject( filename.GetFullPath() ) )
        {
            m_currentDir = filename.GetPath();
            InsertRecentProject( filename.GetFullPath() );
        }
    }
    else
    {
        if(wxMessageBox(wxString::Format( _("The project file '%s' doesn't exist. Would you like to remove it from the recent files list?"), filename.GetName().GetData()), _("Open recent project"), wxICON_WARNING | wxYES_NO) == wxYES)
        {
            m_recentProjects[i] = wxT("");
            UpdateRecentProjects();
        }
    }
}

void MainFrame::OnImportXrc( wxCommandEvent &)
{
	wxFileDialog *dialog = new wxFileDialog( this, _("Import XRC file"), m_currentDir,
	                       wxT("example.xrc"), wxT("*.xrc"), wxFD_OPEN );

	if ( dialog->ShowModal() == wxID_OK )
	{
		m_currentDir = dialog->GetDirectory();

		try
		{
			ticpp::Document doc;
			XMLUtils::LoadXMLFile( doc, false, dialog->GetPath() );

			XrcLoader xrc;
			xrc.SetObjectDatabase( AppData()->GetObjectDatabase() );

			PObjectBase project = xrc.GetProject( &doc );

			if ( project )
			{
				AppData()->MergeProject( project );
			}
			else
			{
				wxLogError( _("Error while loading XRC") );
			}
		}
		catch ( wxFBException& ex )
		{
			wxLogError( _("Error Loading XRC: %s"), ex.what() );
		}
	}

	dialog->Destroy();
}


void MainFrame::OnNewProject( wxCommandEvent &)
{
	if ( !SaveWarning() )
		return;

	AppData()->NewProject();
}

void MainFrame::OnGenerateCode( wxCommandEvent &)
{
	AppData()->GenerateCode( false );
}

void MainFrame::OnAbout( wxCommandEvent &)
{
	AboutDialog *dlg = new AboutDialog( this );
	dlg->ShowModal();
	dlg->Destroy();
}

void MainFrame::OnExit( wxCommandEvent &)
{
	Close();
}

void MainFrame::OnClose( wxCloseEvent &event )
{
	if ( !SaveWarning() )
		return;

	SavePosition( wxT("mainframe") );
#ifndef WXFB_USE_AUI
    m_rightSplitter->Disconnect( wxEVT_COMMAND_SPLITTER_SASH_POS_CHANGED, wxSplitterEventHandler( MainFrame::OnSplitterChanged ) );
#endif
	event.Skip();
}

void MainFrame::OnProjectLoaded( wxFBEvent& )
{
	GetStatusBar()->SetStatusText( _("Project Loaded!") );
	PObjectBase project = AppData()->GetProjectData();

	if ( project )
	{
		wxString objDetails = wxString::Format( _("Name: %s | Class: %s"), project->GetPropertyAsString( wxT("name") ).c_str(), project->GetClassName().c_str() );
		GetStatusBar()->SetStatusText( objDetails, STATUS_FIELD_OBJECT );
	}

	UpdateFrame();
}

void MainFrame::OnProjectSaved( wxFBEvent& )
{
	GetStatusBar()->SetStatusText( _("Project Saved!") );
	UpdateFrame();
}

void MainFrame::OnObjectExpanded( wxFBObjectEvent& )
{
	UpdateFrame();
}

void MainFrame::OnObjectSelected( wxFBObjectEvent& event )
{
	PObjectBase obj = event.GetFBObject();

	Debug::Print( wxT("MainFrame::OnObjectSelected") );
#ifndef WXFB_USE_AUI
    // resize sash position if necessary
    if ( m_autoSash )
    {
		wxSize      panel_size;
		int         sash_pos;

		if ( m_style != wxFB_CLASSIC_GUI )
		{
			switch(m_page_selection)
			{
			case 1: // CPP panel
				break;

			case 2: // Python panel
			   break;

			case 3: // XRC panel
			   break;

			default:
				if ( m_visualEdit != NULL )
				{

					// If selected object is not a Frame or a Panel or a dialog, we won't
					// adjust the sash position
					if ( obj->GetObjectTypeName() == wxT("form") ||
						 obj->GetObjectTypeName() == wxT("menubar_form") ||
					     obj->GetObjectTypeName() == wxT("toolbar_form") )
					{
						sash_pos = m_rightSplitter->GetSashPosition();
						panel_size = m_visualEdit->GetVirtualSize();

						Debug::Print(wxT("MainFrame::OnObjectSelected > sash pos = %d"), sash_pos);
						Debug::Print(wxT("MainFrame::OnObjectSelected > virtual width = %d"), panel_size.GetWidth());

						if ( panel_size.GetWidth() > sash_pos )
						{
							//set the sash position
							Debug::Print(wxT("MainFrame::OnObjectSelected > set sash position"));
							m_rightSplitter_sash_pos = panel_size.GetWidth();
							m_rightSplitter->SetSashPosition(m_rightSplitter_sash_pos);
						}
					}
				}
				break;
			}
		}
    }
#endif
	wxString name;
	PProperty prop( obj->GetProperty( wxT("name") ) );

	if ( prop )
		name = prop->GetValueAsString();
	else
		name = _("\"Unknown\"");

	//GetStatusBar()->SetStatusText( _("Object ") + name + _(" Selected!") );

	wxString objDetails = wxString::Format( _("Name: %s | Class: %s"), name.c_str(), obj->GetClassName().c_str() );

	GetStatusBar()->SetStatusText( objDetails, STATUS_FIELD_OBJECT );

	UpdateFrame();
}

void MainFrame::OnObjectCreated( wxFBObjectEvent& event )
{
	wxString message;

	Debug::Print(wxT("MainFrame::OnObjectCreated"));

	if ( event.GetFBObject() )
	{
		message.Printf( _("Object '%s' of class '%s' created."),
		                event.GetFBObject()->GetPropertyAsString( wxT("name") ).c_str(),
		                event.GetFBObject()->GetClassName().c_str() );
	}
	else
	{
		message = _("Impossible to create the object. Did you forget to add a sizer/parent object or turn on/off an AUI management?");
		wxMessageBox( message, wxT("wxFormBuilder"), wxICON_WARNING | wxOK );
	}

	GetStatusBar()->SetStatusText( message );

	UpdateFrame();
}

void MainFrame::OnObjectRemoved( wxFBObjectEvent& event )
{
	wxString message;
	message.Printf( _("Object '%s' removed."),
	                event.GetFBObject()->GetPropertyAsString( wxT("name") ).c_str() );
	GetStatusBar()->SetStatusText( message );
	UpdateFrame();
}

void MainFrame::OnPropertyModified( wxFBPropertyEvent& event )
{
	PProperty prop = event.GetFBProperty();

	if ( prop )
	{
		if ( prop->GetObject() == AppData()->GetSelectedObject() )
		{
			if ( 0 == prop->GetName().CmpNoCase( wxT("name") ) )
			{
				wxString oldDetails = GetStatusBar()->GetStatusText( STATUS_FIELD_OBJECT );
				wxString newDetails;
				size_t pipeIdx = oldDetails.find( wxT("|") );

				if ( pipeIdx != oldDetails.npos )
				{
					newDetails.Printf( _("Name: %s %s"), prop->GetValueAsString().c_str(), oldDetails.substr( pipeIdx ).c_str() );
					GetStatusBar()->SetStatusText( newDetails, STATUS_FIELD_OBJECT );
				}
			}

			GetStatusBar()->SetStatusText( _("Property Modified!") );
		}

		// When you change the sizeritem properties, the object modified is not
		// the same that the selected object because is a sizeritem object.
		// It's necessary to update the frame for the toolbar buttons.
		UpdateFrame();
	}
}

void MainFrame::OnEventHandlerModified( wxFBEventHandlerEvent& event )
{
	wxString message;
	message.Printf( _("Event handler '%s' of object '%s' modified."),
	                event.GetFBEventHandler()->GetName().c_str(),
	                event.GetFBEventHandler()->GetObject()->GetPropertyAsString( wxT("name") ).c_str() );

	GetStatusBar()->SetStatusText( message );
	UpdateFrame();
}

void MainFrame::OnCodeGeneration( wxFBEvent& event )
{
	// Using the previously unused Id field in the event to carry a boolean
	bool panelOnly = ( event.GetId() != 0 );

	if ( panelOnly )
	{
		GetStatusBar()->SetStatusText( _("Code Generated!") );
	}
}

void MainFrame::OnProjectRefresh( wxFBEvent& )
{
	PObjectBase project = AppData()->GetProjectData();

	if ( project )
	{
		wxString objDetails = wxString::Format( _("Name: %s | Class: %s"), project->GetPropertyAsString( wxT("name") ).c_str(), project->GetClassName().c_str() );
		GetStatusBar()->SetStatusText( objDetails, STATUS_FIELD_OBJECT );
	}

	UpdateFrame();
}

void MainFrame::OnUndo( wxCommandEvent &)
{
	AppData()->Undo();
}

void MainFrame::OnRedo( wxCommandEvent &)
{
	AppData()->Redo();
}

void MainFrame::UpdateLayoutTools()
{
	int option = -1;
	int border = 0;
	int flag = 0;
	int orient = 0;

	bool gotLayoutSettings = AppData()->GetLayoutSettings( AppData()->GetSelectedObject(), &flag, &option, &border, &orient );
#ifdef WXFB_USE_AUI
    wxAuiToolBar* m_toolbar = this->GetToolBar();
#else
	wxToolBar* m_toolbar = GetToolBar();
#endif
	wxMenu* menuEdit = GetMenuBar()->GetMenu( GetMenuBar()->FindMenu( _("&Edit") ) );

	// Enable the layout tools if there are layout settings, else disable the tools
	menuEdit->Enable( ID_EXPAND, gotLayoutSettings );
	m_toolbar->EnableTool( ID_EXPAND, gotLayoutSettings );
	menuEdit->Enable( ID_STRETCH, option >= 0 );
	m_toolbar->EnableTool( ID_STRETCH, option >= 0 );

	bool enableHorizontalTools = ( orient != wxHORIZONTAL ) && gotLayoutSettings;
	menuEdit->Enable( ID_ALIGN_LEFT, enableHorizontalTools );
	m_toolbar->EnableTool( ID_ALIGN_LEFT, enableHorizontalTools );
	menuEdit->Enable( ID_ALIGN_CENTER_H, enableHorizontalTools );
	m_toolbar->EnableTool( ID_ALIGN_CENTER_H, enableHorizontalTools );
	menuEdit->Enable( ID_ALIGN_RIGHT, enableHorizontalTools );
	m_toolbar->EnableTool( ID_ALIGN_RIGHT, enableHorizontalTools );

	bool enableVerticalTools = ( orient != wxVERTICAL ) && gotLayoutSettings;
	menuEdit->Enable( ID_ALIGN_TOP, enableVerticalTools );
	m_toolbar->EnableTool( ID_ALIGN_TOP, enableVerticalTools );
	menuEdit->Enable( ID_ALIGN_CENTER_V, enableVerticalTools );
	m_toolbar->EnableTool( ID_ALIGN_CENTER_V, enableVerticalTools );
	menuEdit->Enable( ID_ALIGN_BOTTOM, enableVerticalTools );
	m_toolbar->EnableTool( ID_ALIGN_BOTTOM, enableVerticalTools );

	m_toolbar->EnableTool( ID_BORDER_TOP, gotLayoutSettings );
	m_toolbar->EnableTool( ID_BORDER_RIGHT, gotLayoutSettings );
	m_toolbar->EnableTool( ID_BORDER_LEFT, gotLayoutSettings );
	m_toolbar->EnableTool( ID_BORDER_BOTTOM, gotLayoutSettings );

	// Toggle the toolbar buttons according to the properties, if there are layout settings
	m_toolbar->ToggleTool( ID_EXPAND,         ( ( flag & wxEXPAND ) != 0 ) && gotLayoutSettings );
	m_toolbar->ToggleTool( ID_STRETCH,        ( option > 0 ) && gotLayoutSettings );
	m_toolbar->ToggleTool( ID_ALIGN_LEFT,     !( ( flag & ( wxALIGN_RIGHT | wxALIGN_CENTER_HORIZONTAL ) ) != 0 ) && enableHorizontalTools );
	m_toolbar->ToggleTool( ID_ALIGN_CENTER_H, ( ( flag & wxALIGN_CENTER_HORIZONTAL ) != 0 ) && enableHorizontalTools );
	m_toolbar->ToggleTool( ID_ALIGN_RIGHT,    ( ( flag & wxALIGN_RIGHT ) != 0 ) && enableHorizontalTools );
	m_toolbar->ToggleTool( ID_ALIGN_TOP,      !( ( flag & ( wxALIGN_BOTTOM | wxALIGN_CENTER_VERTICAL ) ) != 0 ) && enableVerticalTools );
	m_toolbar->ToggleTool( ID_ALIGN_CENTER_V, ( ( flag & wxALIGN_CENTER_VERTICAL ) != 0 ) && enableVerticalTools );
	m_toolbar->ToggleTool( ID_ALIGN_BOTTOM,   ( ( flag & wxALIGN_BOTTOM ) != 0 ) && enableVerticalTools );

	m_toolbar->ToggleTool( ID_BORDER_TOP,      ( ( flag & wxTOP ) != 0 ) && gotLayoutSettings );
	m_toolbar->ToggleTool( ID_BORDER_RIGHT,    ( ( flag & wxRIGHT ) != 0 ) && gotLayoutSettings );
	m_toolbar->ToggleTool( ID_BORDER_LEFT,     ( ( flag & wxLEFT ) != 0 ) && gotLayoutSettings );
	m_toolbar->ToggleTool( ID_BORDER_BOTTOM,   ( ( flag & wxBOTTOM ) != 0 ) && gotLayoutSettings );
}

void MainFrame::UpdateFrame()
{
	// Build the title
	wxString filename = AppData()->GetProjectFileName();
	wxString file;

	if ( filename.empty() )
	{
		file = _("untitled");
	}
	else
	{
		wxFileName fn( filename );
		file = fn.GetName();
	}

	SetTitle( wxString::Format( wxT("%s%s - wxFormBuilder v3.2 - beta"), AppData()->IsModified() ? wxT("*") : wxT(""), file.c_str() ) );
	GetStatusBar()->SetStatusText( filename, STATUS_FIELD_PATH );

	// Enable/Disable toolbar and menu entries
	wxMenu* menuEdit = GetMenuBar()->GetMenu( GetMenuBar()->FindMenu( _("&Edit") ) );

#ifndef WXFB_USE_AUI
	wxToolBar* m_toolbar = GetToolBar();
#endif
	bool redo = AppData()->CanRedo();
	menuEdit->Enable( wxID_REDO, redo );
	m_toolbar->EnableTool( wxID_REDO, redo );

	bool undo = AppData()->CanUndo();
	menuEdit->Enable( wxID_UNDO, undo );
	m_toolbar->EnableTool( wxID_UNDO, undo );

	bool copy = AppData()->CanCopyObject();
	bool isEditor = ( _("Designer") != m_notebook->GetPageText( m_notebook->GetSelection() ) );
	menuEdit->Enable( wxID_FIND, isEditor );

	menuEdit->Enable( ID_CLIPBOARD_COPY, copy );

	menuEdit->Enable( wxID_COPY, copy );
	m_toolbar->EnableTool( wxID_COPY, copy );

	menuEdit->Enable( wxID_CUT, copy );
	m_toolbar->EnableTool( wxID_CUT, copy );

	menuEdit->Enable( wxID_DELETE, copy );
	m_toolbar->EnableTool( wxID_DELETE, copy );

	menuEdit->Enable( wxID_UP, copy );
	menuEdit->Enable( wxID_DOWN, copy );
	menuEdit->Enable( wxID_BACKWARD, copy );
	menuEdit->Enable( wxID_FORWARD, copy );

	bool paste = AppData()->CanPasteObject();
	menuEdit->Enable( wxID_PASTE, paste );
	m_toolbar->EnableTool( wxID_PASTE, paste );

	menuEdit->Enable( ID_CLIPBOARD_PASTE, AppData()->CanPasteObjectFromClipboard() );

	UpdateLayoutTools();
}

void MainFrame::UpdateRecentProjects()
{
	int i, fi;
	wxMenu *menuFile = GetMenuBar()->GetMenu( GetMenuBar()->FindMenu( wxT("File") ) );

	// borramos los items del menu de los projectos recientes

	for ( i = 0 ; i < 4 ; i++ )
	{
		if ( menuFile->FindItem( ID_RECENT_0 + i ) )
			menuFile->Destroy( ID_RECENT_0 + i );
	}

	wxMenuItem* mruSep = menuFile->FindItemByPosition( menuFile->GetMenuItemCount() - 1 );
	if ( mruSep->IsSeparator() )
	{
	    menuFile->Destroy( mruSep );
	}

	// remove empty filenames and 'compress' the rest
    fi = 0;
	for ( i = 0 ; i < 4 ; i++ )
	{
	    if(!m_recentProjects[i].IsEmpty())
	        m_recentProjects[fi++] = m_recentProjects[i];
	}
	for ( i = fi ; i < 4 ; i++ )
        m_recentProjects[i] = wxT("");

    if ( !m_recentProjects[0].IsEmpty() )
    {
        menuFile->AppendSeparator();
    }

	// creamos los nuevos ficheros recientes
	for ( unsigned int i = 0 ; i < 4 && !m_recentProjects[i].IsEmpty() ; i++ )
		menuFile->Append( ID_RECENT_0 + i, m_recentProjects[i], wxT("") );
}

void MainFrame::InsertRecentProject( const wxString &file )
{
	bool found = false;
	int i;

	for ( i = 0; i < 4 && !found; i++ )
		found = ( file == m_recentProjects[i] );

	if ( found ) // en i-1 está la posición encontrada (0 < i < 4)
	{
		// desplazamos desde 0 hasta i-1 una posición a la derecha

		for ( i = i - 1; i > 0; i-- )
			m_recentProjects[i] = m_recentProjects[i-1];
	}
	else if ( !found )
	{
		for ( i = 3; i > 0; i-- )
			m_recentProjects[i] = m_recentProjects[i-1];
	}

	m_recentProjects[0] = file;

	UpdateRecentProjects();
}

void MainFrame::OnCopy( wxCommandEvent &)

{
	wxWindow *focusedWindow = wxWindow::FindFocus();

	if ( focusedWindow != NULL && focusedWindow->IsKindOf( CLASSINFO( wxScintilla ) ) )
		( ( wxScintilla* )focusedWindow )->Copy();
	else
	{
		AppData()->CopyObject( AppData()->GetSelectedObject() );
		UpdateFrame();
	}
}

void MainFrame::OnCut ( wxCommandEvent &)
{
	wxWindow *focusedWindow = wxWindow::FindFocus();

	if ( focusedWindow != NULL && focusedWindow->IsKindOf( CLASSINFO( wxScintilla ) ) )
		( ( wxScintilla* )focusedWindow )->Cut();
	else
	{
		AppData()->CutObject( AppData()->GetSelectedObject() );
		UpdateFrame();
	}
}

void MainFrame::OnDelete ( wxCommandEvent &)
{
	AppData()->RemoveObject( AppData()->GetSelectedObject() );
	UpdateFrame();
}

void MainFrame::OnPaste ( wxCommandEvent &)
{
	wxWindow *focusedWindow = wxWindow::FindFocus();

	if ( focusedWindow != NULL && focusedWindow->IsKindOf( CLASSINFO( wxScintilla ) ) )
		( ( wxScintilla* )focusedWindow )->Paste();
	else
	{
		AppData()->PasteObject( AppData()->GetSelectedObject() );
		UpdateFrame();
	}
}

void MainFrame::OnClipboardCopy(wxCommandEvent& )
{
	AppData()->CopyObjectToClipboard( AppData()->GetSelectedObject() );
	UpdateFrame();
}

void MainFrame::OnClipboardPaste(wxCommandEvent& )
{
	AppData()->PasteObjectFromClipboard( AppData()->GetSelectedObject() );
	UpdateFrame();
}

void MainFrame::OnClipboardPasteUpdateUI( wxUpdateUIEvent& e )
{
	e.Enable( AppData()->CanPasteObjectFromClipboard() );
}

void MainFrame::OnToggleExpand ( wxCommandEvent &)
{
	AppData()->ToggleExpandLayout( AppData()->GetSelectedObject() );
}

void MainFrame::OnToggleStretch ( wxCommandEvent &)
{
	AppData()->ToggleStretchLayout( AppData()->GetSelectedObject() );
}

void MainFrame::OnMoveUp ( wxCommandEvent &)
{
	AppData()->MovePosition( AppData()->GetSelectedObject(), false, 1 );
}

void MainFrame::OnMoveDown ( wxCommandEvent &)
{
	AppData()->MovePosition( AppData()->GetSelectedObject(), true, 1 );
}

void MainFrame::OnMoveLeft ( wxCommandEvent &)
{
	AppData()->MoveHierarchy( AppData()->GetSelectedObject(), true );
}

void MainFrame::OnMoveRight ( wxCommandEvent & )
{
	AppData()->MoveHierarchy( AppData()->GetSelectedObject(), false );
}

void MainFrame::OnChangeAlignment ( wxCommandEvent &event )
{
	int align = 0;
	bool vertical = ( event.GetId() == ID_ALIGN_TOP ||
	                  event.GetId() == ID_ALIGN_BOTTOM ||
	                  event.GetId() == ID_ALIGN_CENTER_V );

	switch ( event.GetId() )
	{

		case ID_ALIGN_RIGHT:
			align = wxALIGN_RIGHT;

			break;

		case ID_ALIGN_CENTER_H:
			align = wxALIGN_CENTER_HORIZONTAL;

			break;

		case ID_ALIGN_BOTTOM:
			align = wxALIGN_BOTTOM;

			break;

		case ID_ALIGN_CENTER_V:
			align = wxALIGN_CENTER_VERTICAL;

			break;
	}

	AppData()->ChangeAlignment( AppData()->GetSelectedObject(), align, vertical );

	UpdateLayoutTools();
}

void MainFrame::OnChangeBorder( wxCommandEvent& e )
{
	int border;

	switch ( e.GetId() )
	{
		case ID_BORDER_LEFT:
			border = wxLEFT;
			break;

		case ID_BORDER_RIGHT:
			border = wxRIGHT;
			break;

		case ID_BORDER_TOP:
			border = wxTOP;
			break;

		case ID_BORDER_BOTTOM:
			border = wxBOTTOM;
			break;

		default:
			border = 0;
			break;
	}

	AppData()->ToggleBorderFlag( AppData()->GetSelectedObject(), border );

	UpdateLayoutTools();
}

void MainFrame::OnXrcPreview( wxCommandEvent& WXUNUSED( e ) )
{
	AppData()->ShowXrcPreview();
#ifdef WXFB_USE_AUI
/* what is this for?
	wxAuiPaneInfoArray& all_panes = m_mgr.GetAllPanes();
	for ( int i = 0, count = all_panes.GetCount(); i < count; ++i )
	{
		wxAuiPaneInfo info = all_panes.Item( i );
	}
*/
#endif
}

void MainFrame::OnGenInhertedClass( wxCommandEvent& WXUNUSED( e ) )
{
	wxString filePath;
	try
	{
		// Get the output path
		filePath = AppData()->GetOutputPath();
	}
	catch ( wxFBException& ex )
	{
		wxLogWarning( ex.what() );
		return;
	}

	// Show the dialog
	PObjectBase project = AppData()->GetProjectData();
	if ( project->IsNull( wxT("file") ) )
	{
		wxLogWarning( _("You must set the \"file\" property of the project before generating inherited classes.") );
		return;
	}
	GenInheritedClassDlg dlg( this, project );

	if ( wxID_OK != dlg.ShowModal() )
	{
		return;
	}

	std::vector< GenClassDetails > selectedForms;
	dlg.GetFormsSelected( &selectedForms );

	for ( size_t i = 0; i < selectedForms.size(); ++i )
	{
		const GenClassDetails& details = selectedForms[i];

		// Create the class and files.
		AppData()->GenerateInheritedClass( details.m_form, details.m_className, filePath, details.m_fileName );
	}
	
	wxMessageBox( wxString::Format( _("Class(es) generated to \'%s\'."), filePath.c_str() ), wxT("wxFormBuilder") );
}

bool MainFrame::SaveWarning()
{
	int result = wxYES;

	if ( AppData()->IsModified() )
	{
		result = ::wxMessageBox( _("Current project file has been modified...\nDo you want to save the changes?"),
		                         _("Save project"),
		                         wxYES | wxNO | wxCANCEL,
		                         this );

		if ( result == wxYES )
		{
			wxCommandEvent dummy;
			OnSaveProject( dummy );
		}
	}

	return ( result != wxCANCEL );
}
#ifndef WXFB_USE_AUI
void MainFrame::OnFlatNotebookPageChanged( wxFlatNotebookEvent& event )
{
	UpdateFrame();

	if ( m_autoSash )
	{
		m_page_selection = event.GetSelection();
		Debug::Print(wxT("MainFrame::OnFlatNotebookPageChanged > selection = %d"), m_page_selection);

		wxSize panel_size;
		int sash_pos;

		if(m_style != wxFB_CLASSIC_GUI)
		{
			switch( m_page_selection )
			{
			case 1: // CPP panel
				if( (m_cpp != NULL) && (m_rightSplitter != NULL) )
				{
					panel_size = m_cpp->GetClientSize();
					sash_pos = m_rightSplitter->GetSashPosition();

					Debug::Print(wxT("MainFrame::OnFlatNotebookPageChanged > CPP panel: width = %d sash pos = %d"), panel_size.GetWidth(), sash_pos);

					if(panel_size.GetWidth() > sash_pos)
					{
						// set the sash position
						Debug::Print(wxT("MainFrame::OnFlatNotebookPageChanged > reset sash position"));
						m_rightSplitter->SetSashPosition(panel_size.GetWidth());
					}
				}
				break;

			case 2: // Python panel
				if( (m_python != NULL) && (m_rightSplitter != NULL) )
				{
					panel_size = m_python->GetClientSize();
					sash_pos = m_rightSplitter->GetSashPosition();

					Debug::Print(wxT("MainFrame::OnFlatNotebookPageChanged > Python panel: width = %d sash pos = %d"), panel_size.GetWidth(), sash_pos);

					if(panel_size.GetWidth() > sash_pos)
					{
						// set the sash position
						Debug::Print(wxT("MainFrame::OnFlatNotebookPageChanged > reset sash position"));
						m_rightSplitter->SetSashPosition(panel_size.GetWidth());
					}
				}
				break;

			case 3: // XRC panel
				if((m_xrc != NULL) && (m_rightSplitter != NULL))
				{
					panel_size = m_xrc->GetClientSize();
					sash_pos = m_rightSplitter->GetSashPosition();

					Debug::Print(wxT("MainFrame::OnFlatNotebookPageChanged > XRC panel: width = %d sash pos = %d"), panel_size.GetWidth(), sash_pos);

					if(panel_size.GetWidth() > sash_pos)
					{
						// set the sash position
						Debug::Print(wxT("MainFrame::OnFlatNotebookPageChanged > reset sash position"));
						m_rightSplitter->SetSashPosition(panel_size.GetWidth());
					}
				}
				break;

			default:
				if(m_visualEdit != NULL)
				{
					sash_pos = m_rightSplitter->GetSashPosition();

					if(m_rightSplitter_sash_pos < sash_pos)
					{
						//restore the sash position
						Debug::Print(wxT("MainFrame::OnFlatNotebookPageChanged > restore sash position: sash pos = %d"), m_rightSplitter_sash_pos);
						m_rightSplitter->SetSashPosition(m_rightSplitter_sash_pos);
					}
					else
					{
						// update position
						m_rightSplitter_sash_pos = sash_pos;
					}
				}
				break;
			}
		}
	}

	AppData()->GenerateCode( true );
}
#else
void MainFrame::OnAuiNotebookPageChanged( wxAuiNotebookEvent& event )
{
	AppData()->GenerateCode( true );
	UpdateFrame();
}
#endif // WXFB_USE_AUI
void MainFrame::OnFindDialog( wxCommandEvent& )
{
	if ( NULL == m_findDialog )
	{
		m_findDialog = new wxFindReplaceDialog( this, &m_findData, _("Find") );
		m_findDialog->Centre( wxCENTRE_ON_SCREEN | wxBOTH );
	}
	m_findDialog->Show( true );
}

void MainFrame::OnFindClose( wxFindDialogEvent& )
{
	m_findDialog->Destroy();
	m_findDialog = 0;
}

void MainFrame::OnFind( wxFindDialogEvent& event )
{
#ifdef WXFB_USE_AUI
	wxWindow* page = m_notebook->GetPage( m_notebook->GetSelection() );
#else
	wxWindow* page = m_notebook->GetCurrentPage();
#endif

	if( page )
	{
		event.StopPropagation();
		event.SetClientData( m_findDialog );
		page->GetEventHandler()->ProcessEvent( event );
	}
}

void MainFrame::OnPreferences( wxCommandEvent& )
{
	PrefsDialog dlg( this );
	if ( dlg.ShowModal() == wxID_OK )
	{
		
	}
}

/////////////////////////////////////////////////////////////////////////////

wxMenuBar * MainFrame::CreateFBMenuBar()
{
	wxMenu*     menuFile = new wxMenu;
	wxMenuItem* item;
	
	item = new wxMenuItem( menuFile, ID_NEW_PRJ, wxString(_("&New Project") ) + wxT('\t') + wxT("Ctrl+N"), _("Create an empty project") );
	item->SetBitmap( AppBitmaps::GetBitmap( wxT("new"), 16 ) );
	item = menuFile->Append( item );

	menuFile->Append( wxID_OPEN,   wxString(_("&Open...") )    + wxT('\t') + wxT("Ctrl+O"),       _("Open a project") );
	menuFile->Append( wxID_SAVE,   wxString(_("&Save") )       + wxT('\t') + wxT("Ctrl+S"),       _("Save current project") );
	menuFile->Append( wxID_SAVEAS, wxString(_("Save &As...") ) + wxT('\t') + wxT("Ctrl-Shift+S"), _("Save current project as...") );

	menuFile->AppendSeparator();

	item = new wxMenuItem( menuFile, ID_IMPORT_XRC, wxString(_("&Import XRC...") ), _("Import XRC file") );
	item->SetBitmap( AppBitmaps::GetBitmap( wxT("xrc"), 16 ) );
	item = menuFile->Append( item );

	item = menuFile->AppendSeparator();

	item = new wxMenuItem( menuFile, ID_GENERATE_CODE, wxString(_("&Generate Code") ) + wxT('\t') + wxT("F8"), _("Generate Code") );
	item->SetBitmap( wxArtProvider::GetBitmap( wxART_EXECUTABLE_FILE, wxART_MENU ) );
	item = menuFile->Append( item );

	menuFile->AppendSeparator();
	item = menuFile->Append( wxID_EXIT, wxString(_("E&xit") ) + wxT('\t') + wxT("Alt-F4"), _("Quit wxFormBuilder") );

	wxMenu *menuEdit = new wxMenu;
	menuEdit->Append( wxID_UNDO,   wxString(_("&Undo") )   + wxT('\t') + wxT("Ctrl+Z"), _("Undo changes") );
	menuEdit->Append( wxID_REDO,   wxString(_("&Redo") )   + wxT('\t') + wxT("Ctrl+Y"), _("Redo changes") );
	menuEdit->AppendSeparator();
	menuEdit->Append( wxID_COPY,   wxString(_("Co&py") )   + wxT('\t') + wxT("Ctrl+C"), _("Copy selected object") );
	menuEdit->Append( wxID_CUT,    wxString(_("&Cut") )    + wxT('\t') + wxT("Ctrl+X"), _("Cut selected object") );
	menuEdit->Append( wxID_PASTE,  wxString(_("Past&e") )  + wxT('\t') + wxT("Ctrl+V"), _("Paste on selected object") );
	menuEdit->Append( wxID_DELETE, wxString(_("&Delete") ) + wxT('\t') + wxT("Ctrl+D"), _("Delete selected object") );
	menuEdit->AppendSeparator();

	item = new wxMenuItem( menuEdit, ID_CLIPBOARD_COPY,  wxString(_("Copy Object To Clipboard") ) + wxT('\t') + wxT("Ctrl+Shift+C"), _("Copy Object to Clipboard") );
	item->SetBitmap( wxArtProvider::GetBitmap( wxART_COPY, wxART_MENU ) );
	item = menuEdit->Append( item );

	item = new wxMenuItem( menuEdit, ID_CLIPBOARD_PASTE, wxString(_("Paste Object From Clipboard") ) + wxT('\t') + wxT("Ctrl+Shift+V"), _("Paste Object from Clipboard") );
	item->SetBitmap( wxArtProvider::GetBitmap( wxART_PASTE, wxART_MENU ) );
	item = menuEdit->Append( item );

	menuEdit->AppendSeparator();

	item = new wxMenuItem( menuEdit, ID_EXPAND, wxString(_("Toggle E&xpand") ) + wxT('\t') + wxT("Alt+W"), _("Toggle wxEXPAND flag of sizeritem properties") );
	item->SetBitmap( AppBitmaps::GetBitmap( wxT("expand"), 16 ) );
	item = menuEdit->Append( item );

	item = new wxMenuItem( menuEdit, ID_STRETCH, wxString(_("Toggle &Stretch") ) + wxT('\t') + wxT("Alt+S"), _("Toggle option property of sizeritem properties") );
	item->SetBitmap( AppBitmaps::GetBitmap( wxT("stretch"), 16 ) );
	item = menuEdit->Append( item );

	menuEdit->Append( wxID_UP,       wxString(_("Move Up") )    + wxT('\t') + wxT("Alt+Up"),    _("Move Up selected object") );
	menuEdit->Append( wxID_DOWN,     wxString(_("Move Down") )  + wxT('\t') + wxT("Alt+Down"),  _("Move Down selected object") );
	menuEdit->Append( wxID_BACKWARD, wxString(_("Move Left") )  + wxT('\t') + wxT("Alt+Left"),  _("Move Left selected object") );
	menuEdit->Append( wxID_FORWARD,  wxString(_("Move Right") ) + wxT('\t') + wxT("Alt+Right"), _("Move Right selected object") );
	menuEdit->AppendSeparator();
	menuEdit->Append( wxID_FIND,     wxString(_("&Find") )      + wxT('\t') + wxT("Ctrl+F"),    _("Find text in the active code viewer") );
	menuEdit->AppendSeparator();

	item = new wxMenuItem( menuEdit, ID_ALIGN_LEFT, wxString(_("Align &Left") ) + wxT('\t') + wxT("Alt+Shift+Left"), _("Align item to the left") );
	item->SetBitmap( AppBitmaps::GetBitmap( wxT("lalign"), 16 ) );
	item = menuEdit->Append( item );

	item = new wxMenuItem( menuEdit, ID_ALIGN_CENTER_H, wxString(_("Align Center &Horizontal") )  + wxT('\t') + wxT("Alt+Shift+H"), _("Align item to the center horizontally") );
	item->SetBitmap( AppBitmaps::GetBitmap( wxT("lalign"), 16 ) );
	item = menuEdit->Append( item );

	item = new wxMenuItem( menuEdit, ID_ALIGN_RIGHT, wxString(_("Align Ri&ght") ) + wxT('\t') + wxT("Alt+Shift+Right"), _("Align item to the right") );
	item->SetBitmap( AppBitmaps::GetBitmap( wxT("ralign"), 16 ) );
	item = menuEdit->Append( item );

	item = new wxMenuItem( menuEdit, ID_ALIGN_TOP, wxString(_("Align &Top") ) + wxT('\t') + wxT("Alt+Shift+Up"), _("Align item to the top") );
	item->SetBitmap( AppBitmaps::GetBitmap( wxT("talign"), 16 ) );
	item = menuEdit->Append( item );

	item = new wxMenuItem( menuEdit, ID_ALIGN_CENTER_V, wxString(_("Align Center &Vertical") ) + wxT('\t') + wxT("Alt+Shift+V"), _("Align item to the center vertically") );
	item->SetBitmap( AppBitmaps::GetBitmap( wxT("cvalign"), 16 ) );
	item = menuEdit->Append( item );

	item = new wxMenuItem( menuEdit, ID_ALIGN_BOTTOM, wxString(_("Align &Bottom") ) + wxT('\t') + wxT("Alt+Shift+Down"), _("Align item to the bottom") );
	item->SetBitmap( AppBitmaps::GetBitmap( wxT("balign"), 16 ) );
	item = menuEdit->Append( item );
	menuEdit->AppendSeparator();

	menuEdit->Append( wxID_PREFERENCES, wxString(_("Prefere&nces") ) + wxT('\t') + wxT("Alt+O"), _("Change global preferences") );

	wxMenu *menuView = new wxMenu;
	item = new wxMenuItem( menuView, ID_PREVIEW_XRC, wxString(_("&XRC Window") ) + wxT('\t') + wxT("F5"), _("Show a preview of the XRC window") );
	item->SetBitmap( AppBitmaps::GetBitmap( wxT("designer"), 16 ) );
	item = menuView->Append( item );

	wxMenu *menuTools = new wxMenu;
	item = new wxMenuItem( menuTools, ID_GEN_INHERIT_CLS, wxString(_("&Generate Inherited Class") ) + wxT('\t') + wxT("F6"), _("Creates the needed files and class for proper inheritance of your designed GUI") );
	item->SetBitmap( wxArtProvider::GetBitmap( wxART_EXECUTABLE_FILE, wxART_MENU ) );
	item = menuTools->Append( item );

	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append( wxID_ABOUT, wxString(_("&About...") ) + wxT('\t') + wxT("F1"), _("Show about dialog") );

	// now append the freshly created menu to the menu bar...
	wxMenuBar *menuBar = new wxMenuBar();
	menuBar->Append( menuFile,  _("&File") );
	menuBar->Append( menuEdit,  _("&Edit") );
	menuBar->Append( menuView,  _("&View") );
	menuBar->Append( menuTools, _("&Tools") );
	menuBar->Append( menuHelp,  _("&Help") );

	return menuBar;
}
#ifdef WXFB_USE_AUI
wxAuiToolBar * MainFrame::RecreateFBAuiToolBar()
{
  if ( m_toolbar )
  {
    m_mgr.DetachPane(m_toolbar);
    m_toolbar->Destroy();
  }
/*
  wxAuiToolBarItemArray append_items;
  wxAuiToolBarItemArray prepend_items;
  wxAuiToolBarItem item;
//  wxAuiToolBarItem item_separator;
//  item_separator.SetKind( wxITEM_SEPARATOR );

  item.SetKind( wxITEM_NORMAL );
  item.SetId( ID_AUI_SETTINGS );
  item.SetLabel( _("Customize...") );
  item.SetBitmap( AppBitmaps::GetBitmap( wxT("generate"), 16 ) );
  append_items.Add( item );
*/
  m_toolbar = new wxAuiToolBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_TB_OVERFLOW );
#else
wxToolBar * MainFrame::CreateFBToolBar()
{
	wxToolBar* m_toolbar = CreateToolBar();
#endif
	m_toolbar->SetToolBitmapSize( wxSize( TOOL_SIZE, TOOL_SIZE ) );
	m_toolbar->AddTool( ID_NEW_PRJ,  _("New Project"),  AppBitmaps::GetBitmap( wxT("new"), TOOL_SIZE ), wxNullBitmap, wxITEM_NORMAL, _("New Project (Ctrl+N)"), _("Start a new project."), NULL );
	m_toolbar->AddTool( wxID_OPEN,   _("Open Project"), wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, _("Open Project (Ctrl+O)"), _("Open an existing project."), NULL );
	m_toolbar->AddTool( wxID_SAVE,   _("Save Project"), wxArtProvider::GetBitmap( wxART_FILE_SAVE, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, _("Save Project (Ctrl+S)"), _("Save the current project."), NULL );
	m_toolbar->AddSeparator();
	m_toolbar->AddTool( wxID_UNDO,   _("Undo"), wxArtProvider::GetBitmap( wxART_UNDO, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, _("Undo (Ctrl+Z)"), _("Undo the last action."), NULL );
	m_toolbar->AddTool( wxID_REDO,   _("Redo"), wxArtProvider::GetBitmap( wxART_REDO, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, _("Redo (Ctrl+Y)"), _("Redo the last action that was undone."), NULL );
	m_toolbar->AddSeparator();
	m_toolbar->AddTool( wxID_CUT,    _("Cut"),    wxArtProvider::GetBitmap( wxART_CUT, wxART_TOOLBAR ),    wxNullBitmap, wxITEM_NORMAL, _("Cut (Ctrl+X)"),    _("Remove the selected object and place it on the clipboard."), NULL );
	m_toolbar->AddTool( wxID_COPY,   _("Copy"),   wxArtProvider::GetBitmap( wxART_COPY, wxART_TOOLBAR ),   wxNullBitmap, wxITEM_NORMAL, _("Copy (Ctrl+C)"),   _("Copy the selected object to the clipboard."), NULL );
	m_toolbar->AddTool( wxID_PASTE,  _("Paste"),  wxArtProvider::GetBitmap( wxART_PASTE, wxART_TOOLBAR ),  wxNullBitmap, wxITEM_NORMAL, _("Paste (Ctrl+V)"),  _("Insert an object from the clipboard."), NULL );
	m_toolbar->AddTool( wxID_DELETE, _("Delete"), wxArtProvider::GetBitmap( wxART_DELETE, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, _("Delete (Ctrl+D)"), _("Remove the selected object."), NULL );
	m_toolbar->AddSeparator();
	m_toolbar->AddTool( ID_GENERATE_CODE, _("Generate Code"), wxArtProvider::GetBitmap( wxART_EXECUTABLE_FILE, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, _("Generate Code (F8)"), _("Create code from the current project."), NULL );
	m_toolbar->AddSeparator();
	m_toolbar->AddTool( ID_ALIGN_LEFT,     wxEmptyString, AppBitmaps::GetBitmap( wxT("lalign"),  TOOL_SIZE ), wxNullBitmap, wxITEM_CHECK, _("Align Left"),                _("The item will be aligned to the left of the space alotted to it by the sizer."), NULL );
	m_toolbar->AddTool( ID_ALIGN_CENTER_H, wxEmptyString, AppBitmaps::GetBitmap( wxT("chalign"), TOOL_SIZE ), wxNullBitmap, wxITEM_CHECK, _("Align Center Horizontally"), _("The item will be centered horizontally in the space alotted to it by the sizer."), NULL );
	m_toolbar->AddTool( ID_ALIGN_RIGHT,    wxEmptyString, AppBitmaps::GetBitmap( wxT("ralign"),  TOOL_SIZE ), wxNullBitmap, wxITEM_CHECK, _("Align Right"),               _("The item will be aligned to the right of the space alotted to it by the sizer."), NULL );
	m_toolbar->AddSeparator();
	m_toolbar->AddTool( ID_ALIGN_TOP,      wxEmptyString, AppBitmaps::GetBitmap( wxT("talign"),  TOOL_SIZE ), wxNullBitmap, wxITEM_CHECK, _("Align Top"),                 _("The item will be aligned to the top of the space alotted to it by the sizer."), NULL );
	m_toolbar->AddTool( ID_ALIGN_CENTER_V, wxEmptyString, AppBitmaps::GetBitmap( wxT("cvalign"), TOOL_SIZE ), wxNullBitmap, wxITEM_CHECK, _("Align Center Vertically"),   _("The item will be centered vertically within space alotted to it by the sizer."), NULL );
	m_toolbar->AddTool( ID_ALIGN_BOTTOM,   wxEmptyString, AppBitmaps::GetBitmap( wxT("balign"),  TOOL_SIZE ), wxNullBitmap, wxITEM_CHECK, _("Align Bottom"),              _("The item will be aligned to the bottom of the space alotted to it by the sizer."), NULL );
	m_toolbar->AddSeparator();
	m_toolbar->AddTool( ID_EXPAND,  wxEmptyString, AppBitmaps::GetBitmap( wxT("expand"),  TOOL_SIZE ), wxNullBitmap, wxITEM_CHECK, _("Expand (Alt+W)"),  _("The item will be expanded to fill the space assigned to the item."), NULL );
	m_toolbar->AddTool( ID_STRETCH, wxEmptyString, AppBitmaps::GetBitmap( wxT("stretch"), TOOL_SIZE ), wxNullBitmap, wxITEM_CHECK, _("Stretch (Alt+S)"), _("The item will grow and shrink with the sizer."), NULL );
	m_toolbar->AddSeparator();
	m_toolbar->AddTool( ID_BORDER_LEFT,   wxEmptyString, AppBitmaps::GetBitmap( wxT("left"),   TOOL_SIZE ), wxNullBitmap, wxITEM_CHECK, _("Left Border"),   _("A border will be added on the left side of the item."), NULL );
	m_toolbar->AddTool( ID_BORDER_RIGHT,  wxEmptyString, AppBitmaps::GetBitmap( wxT("right"),  TOOL_SIZE ), wxNullBitmap, wxITEM_CHECK, _("Right Border"),  _("A border will be added on the right side of the item."), NULL );
	m_toolbar->AddTool( ID_BORDER_TOP,    wxEmptyString, AppBitmaps::GetBitmap( wxT("top"),    TOOL_SIZE ), wxNullBitmap, wxITEM_CHECK, _("Top Border"),    _("A border will be added on the top of the item."), NULL );
	m_toolbar->AddTool( ID_BORDER_BOTTOM, wxEmptyString, AppBitmaps::GetBitmap( wxT("bottom"), TOOL_SIZE ), wxNullBitmap, wxITEM_CHECK, _("Bottom Border"), _("A border will be added on the bottom of the item."), NULL );
#ifdef WXFB_USE_AUI
//  m_toolbar->SetCustomOverflowItems( prepend_items, append_items );
#endif
	m_toolbar->Realize();

	return m_toolbar;
}

wxWindow * MainFrame::CreateDesignerWindow( wxWindow *parent )
{
	long editStyle;
	wxConfigBase* config = wxConfigBase::Get();

#ifdef WXFB_USE_AUI
	long cppStyle;
	config->Read( wxT("/mainframe/editor/auinbook_style"), &editStyle, wxAUI_NB_TAB_MOVE | wxAUI_NB_WINDOWLIST_BUTTON | wxAUI_NB_SCROLL_BUTTONS );
	config->Read( wxT("/mainframe/editor/cpp/auinbook_style"), &cppStyle, wxAUI_NB_WINDOWLIST_BUTTON );

	m_notebook   = new wxAuiNotebook( parent, ID_EDITOR_FNB, wxDefaultPosition, wxDefaultSize, editStyle );
	m_visualEdit = new VisualEditor( m_notebook );
	m_cpp        = new CppPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, cppStyle );
	m_python     = new PythonPanel( m_notebook, wxID_ANY );
	m_xrc        = new XrcPanel( m_notebook, wxID_ANY );

	m_notebook->AddPage( m_visualEdit, wxT("Designer"), false, AppBitmaps::GetBitmap( wxT("designer"), 16 ) );
	m_notebook->AddPage( m_cpp,        wxT("C++"),      false, AppBitmaps::GetBitmap( wxT("cpp"),      16 ) );
	m_notebook->AddPage( m_python,     wxT("Python"),   false, AppBitmaps::GetBitmap( wxT("py"),       16 ) );
	m_notebook->AddPage( m_xrc,        wxT("XRC"),      false, AppBitmaps::GetBitmap( wxT("xrc"),      16 ) );
#else
	config->Read( wxT("/mainframe/editor/notebook_style"), &editStyle, wxFNB_BOTTOM | wxFNB_NO_X_BUTTON | wxFNB_NO_NAV_BUTTONS | wxFNB_NODRAG  | wxFNB_FF2 | wxFNB_CUSTOM_DLG );

	m_notebook   = new wxFlatNotebook( parent, ID_EDITOR_FNB, wxDefaultPosition, wxDefaultSize, FNB_STYLE_OVERRIDES( editStyle ) );
	m_visualEdit = new VisualEditor( m_notebook );
	m_cpp        = new CppPanel( m_notebook, wxID_ANY );
	m_python     = new PythonPanel( m_notebook, wxID_ANY );
	m_xrc        = new XrcPanel( m_notebook, wxID_ANY );

	m_notebook->SetCustomizeOptions( wxFNB_CUSTOM_TAB_LOOK | wxFNB_CUSTOM_ORIENTATION | wxFNB_CUSTOM_LOCAL_DRAG );

	// Set notebook icons
	m_icons.Add( AppBitmaps::GetBitmap( wxT("designer"), 16 ) );
	m_icons.Add( AppBitmaps::GetBitmap( wxT("cpp"),      16 ) );
	m_icons.Add( AppBitmaps::GetBitmap( wxT("py"),       16 ) );
	m_icons.Add( AppBitmaps::GetBitmap( wxT("xrc"),      16 ) );
	m_notebook->SetImageList( &m_icons );

	m_notebook->AddPage( m_visualEdit, wxT("Designer"), false, 0 );
	m_notebook->AddPage( m_cpp,        wxT("C++"),      false, 1 );
	m_notebook->AddPage( m_python,     wxT("Python"),   false, 2 );
	m_notebook->AddPage( m_xrc,        wxT("XRC"),      false, 3 );
#endif

	AppData()->GetManager()->SetVisualEditor( m_visualEdit );

	return m_notebook;
}

wxWindow * MainFrame::CreateComponentPalette ( wxWindow *parent )
{
#ifdef WXFB_USE_AUI
	long nbStyle;
	wxConfigBase *config = wxConfigBase::Get();
	config->Read( wxT("/palette/auinbook_style"), &nbStyle, wxAUI_NB_TAB_MOVE | wxAUI_NB_WINDOWLIST_BUTTON );

	m_palette = new wxFbPalette( parent, wxID_ANY, nbStyle );
#else
	// la paleta de componentes, no es un observador propiamente dicho, ya
	// que no responde ante los eventos de la aplicación
	m_palette = new wxFbPalette( parent, -1 );
#endif
	m_palette->Create();
	//m_palette->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DFACE ) );

	return m_palette;
}

wxWindow * MainFrame::CreateObjectTree( wxWindow *parent )
{
	m_objTree = new ObjectTree( parent, -1 );
	m_objTree->Create();

	return m_objTree;
}

wxWindow * MainFrame::CreateObjectInspector( wxWindow *parent )
{
	//TO-DO: make object inspector style selectable.
	int style = ( m_style == wxFB_CLASSIC_GUI ? wxFB_OI_MULTIPAGE_STYLE : wxFB_OI_SINGLE_PAGE_STYLE );
	m_objInsp = new ObjectInspector( parent, -1, style );
	return m_objInsp;
}
#ifdef WXFB_USE_AUI
/*
void MainFrame::OnAuiSettings(wxCommandEvent& WXUNUSED(evt))
{
    // show the settings pane, and float it
    wxAuiPaneInfo& floating_pane = m_mgr.GetPane( wxT("settings") ).Float().Show();

    if (floating_pane.floating_pos == wxDefaultPosition)
        floating_pane.FloatingPosition(GetStartPosition());

    m_mgr.Update();
}
*/
wxAuiDockArt* MainFrame::GetDockArt()
{
    return m_mgr.GetArtProvider();
}

void MainFrame::DoUpdate()
{
    m_mgr.Update();
}
/*
wxPoint MainFrame::GetStartPosition()
{
    static int x = 0;
    x += 20;
    wxPoint pt = ClientToScreen(wxPoint(0,0));
    return wxPoint(pt.x + x, pt.y + x);
}*/
#else
void MainFrame::CreateWideGui()
{
	// MainFrame only contains m_leftSplitter window
	m_leftSplitter = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE );

	wxWindow *objectTree = Title::CreateTitle( CreateObjectTree( m_leftSplitter ), _("Object Tree") );

	// panel1 contains Palette and splitter2 (m_rightSplitter)
	wxPanel *panel1 = new wxPanel( m_leftSplitter, -1 );

	wxWindow *palette = Title::CreateTitle( CreateComponentPalette( panel1 ), _("Component Palette") );
	m_rightSplitter   =  new wxSplitterWindow( panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE );

	wxBoxSizer *panel1_sizer = new wxBoxSizer( wxVERTICAL );
	panel1_sizer->Add( palette, 0, wxEXPAND );
	panel1_sizer->Add( m_rightSplitter, 1, wxEXPAND );
	panel1->SetSizer( panel1_sizer );

	// splitter2 contains the editor and the object inspector
	wxWindow *designer        = Title::CreateTitle( CreateDesignerWindow( m_rightSplitter ), _("Editor") );
	wxWindow *objectInspector = Title::CreateTitle( CreateObjectInspector( m_rightSplitter ), _("Object Properties") );

	m_leftSplitter->SplitVertically( objectTree, panel1, m_leftSplitterWidth );

	// Need to update the left splitter so the right one is drawn correctly
	wxSizeEvent update( GetSize(), GetId() );
	ProcessEvent( update );
	m_leftSplitter->UpdateSize();
	m_leftSplitter->SetMinimumPaneSize( 2 );

	m_rightSplitter->SplitVertically( designer, objectInspector, m_rightSplitterWidth );
	m_rightSplitter->SetSashGravity( 1 );
	m_rightSplitter->SetMinimumPaneSize( 2 );

	m_style = wxFB_WIDE_GUI;

	SetMinSize( wxSize( 700, 380 ) );
}

void MainFrame::CreateClassicGui()
{
	// Give ID to left splitter
	//m_leftSplitter = new wxSplitterWindow( this, -1, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE );
	m_leftSplitter = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE );
	m_rightSplitter =  new wxSplitterWindow( m_leftSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE );
	wxWindow *objectTree      = Title::CreateTitle( CreateObjectTree( m_rightSplitter ), _("Object Tree") );
	wxWindow *objectInspector = Title::CreateTitle( CreateObjectInspector( m_rightSplitter ), _("Object Properties") );

	// panel1 contains palette and designer
	wxPanel *panel1 = new wxPanel( m_leftSplitter, -1 );

	wxWindow *palette = Title::CreateTitle( CreateComponentPalette( panel1 ), _("Component Palette") );
	wxWindow *designer = Title::CreateTitle( CreateDesignerWindow( panel1 ), _("Editor") );

	wxBoxSizer *panel1_sizer = new wxBoxSizer( wxVERTICAL );
	panel1_sizer->Add( palette, 0, wxEXPAND );
	panel1_sizer->Add( designer, 1, wxEXPAND );
	panel1->SetSizer( panel1_sizer );

	m_leftSplitter->SplitVertically( m_rightSplitter, panel1, m_leftSplitterWidth );

	// Need to update the left splitter so the right one is drawn correctly
	wxSizeEvent update( GetSize(), GetId() );
	ProcessEvent( update );
	m_leftSplitter->UpdateSize();

	m_rightSplitter->SplitHorizontally( objectTree, objectInspector, m_rightSplitterWidth );
	m_rightSplitter->SetMinimumPaneSize( 2 );

	SetMinSize( wxSize( 700, 465 ) );
}

void MainFrame::OnIdle( wxIdleEvent& )
{
	if ( m_leftSplitter )
	{
		m_leftSplitter->SetSashPosition( m_leftSplitterWidth );
	}

	if ( m_rightSplitter )
	{
		m_rightSplitter->SetSashPosition( m_rightSplitterWidth );
	}

	Disconnect( wxEVT_IDLE, wxIdleEventHandler( MainFrame::OnIdle ) );

	if ( m_autoSash )
	{
		// Init. m_rightSplitter_sash_pos
		m_rightSplitter_sash_pos = m_rightSplitter->GetSashPosition();
		m_rightSplitter->Connect( wxEVT_COMMAND_SPLITTER_SASH_POS_CHANGED, wxSplitterEventHandler( MainFrame::OnSplitterChanged ) );
	}
}

void MainFrame::OnSplitterChanged( wxSplitterEvent &event )
{
	Debug::Print(wxT("MainFrame::OnSplitterChanged > pos = %d"), event.GetSashPosition());

	// update position
	m_rightSplitter_sash_pos = event.GetSashPosition();
}
#endif // WXFB_USE_AUI
