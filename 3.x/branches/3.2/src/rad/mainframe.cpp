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

#include <wx/config.h>
#include <wx/filename.h>
#include <wx/stc/stc.h>

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
#include "wxfbpalette.h"
#include "rad/designer/visualeditor.h"
#include "settingspanel.h"

#include "model/xrcfilter.h"
#include "rad/about.h"
#include "rad/wxfbevent.h"
#include "wxfbmanager.h"
#include "utils/wxfbexception.h"
#include "utils/stringutils.h"
#include "utils/wxfbdefs.h"

#include "rad/appdata.h"
#include "model/objectbase.h"

#define ID_SAVE_PRJ      102
#define ID_OPEN_PRJ      103
#define ID_NEW_PRJ       104
#define ID_GENERATE_CODE 105
#define ID_IMPORT_XRC    106
#define ID_UNDO          107
#define ID_REDO          108
#define ID_SAVE_AS_PRJ   109
#define ID_CUT           110
#define ID_DELETE        111
#define ID_COPY          112
#define ID_PASTE         113
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

// The preference dialog must use wxID_PREFERENCES for wxMAC
//#define ID_SETTINGS_GLOBAL 138	// For the future preference dialogs
#define ID_SETTINGS_PROJ   139	// For the future preference dialogs

#define ID_FIND 142

#define ID_CLIPBOARD_COPY 143
#define ID_CLIPBOARD_PASTE 144

#define STATUS_FIELD_OBJECT 2
#define STATUS_FIELD_PATH 1

BEGIN_EVENT_TABLE( MainFrame, wxFrame )
EVT_MENU( ID_NEW_PRJ, MainFrame::OnNewProject )
EVT_MENU( ID_SAVE_PRJ, MainFrame::OnSaveProject )
EVT_MENU( ID_SAVE_AS_PRJ, MainFrame::OnSaveAsProject )
EVT_MENU( ID_OPEN_PRJ, MainFrame::OnOpenProject )
EVT_MENU( wxID_ABOUT, MainFrame::OnAbout )
EVT_MENU( wxID_EXIT, MainFrame::OnExit )
EVT_MENU( ID_IMPORT_XRC, MainFrame::OnImportXrc )
EVT_MENU( ID_GENERATE_CODE, MainFrame::OnGenerateCode )
EVT_MENU( ID_UNDO, MainFrame::OnUndo )
EVT_MENU( ID_REDO, MainFrame::OnRedo )
EVT_MENU( ID_DELETE, MainFrame::OnDelete )
EVT_MENU( ID_CUT, MainFrame::OnCut )
EVT_MENU( ID_COPY, MainFrame::OnCopy )
EVT_MENU( ID_PASTE, MainFrame::OnPaste )
EVT_MENU( ID_EXPAND, MainFrame::OnToggleExpand )
EVT_MENU( ID_STRETCH, MainFrame::OnToggleStretch )
EVT_MENU( ID_MOVE_UP, MainFrame::OnMoveUp )
EVT_MENU( ID_MOVE_DOWN, MainFrame::OnMoveDown )
EVT_MENU( ID_MOVE_LEFT, MainFrame::OnMoveLeft )
EVT_MENU( ID_MOVE_RIGHT, MainFrame::OnMoveRight )
EVT_MENU( ID_RECENT_0, MainFrame::OnOpenRecent )
EVT_MENU( ID_RECENT_1, MainFrame::OnOpenRecent )
EVT_MENU( ID_RECENT_2, MainFrame::OnOpenRecent )
EVT_MENU( ID_RECENT_3, MainFrame::OnOpenRecent )
EVT_MENU( ID_ALIGN_RIGHT, MainFrame::OnChangeAlignment )
EVT_MENU( ID_ALIGN_LEFT, MainFrame::OnChangeAlignment )
EVT_MENU( ID_ALIGN_CENTER_H, MainFrame::OnChangeAlignment )
EVT_MENU( ID_ALIGN_TOP, MainFrame::OnChangeAlignment )
EVT_MENU( ID_ALIGN_BOTTOM, MainFrame::OnChangeAlignment )
EVT_MENU( ID_ALIGN_CENTER_V, MainFrame::OnChangeAlignment )
EVT_MENU_RANGE( ID_BORDER_LEFT, ID_BORDER_BOTTOM, MainFrame::OnChangeBorder )
EVT_MENU( ID_PREVIEW_XRC, MainFrame::OnXrcPreview )
EVT_MENU( ID_GEN_INHERIT_CLS, MainFrame::OnGenInhertedClass )
EVT_MENU( ID_CLIPBOARD_COPY, MainFrame::OnClipboardCopy )
EVT_MENU( ID_CLIPBOARD_PASTE, MainFrame::OnClipboardPaste )
EVT_UPDATE_UI( ID_CLIPBOARD_PASTE, MainFrame::OnClipboardPasteUpdateUI )
EVT_MENU( ID_AUI_SETTINGS, MainFrame::OnAuiSettings )
EVT_CLOSE( MainFrame::OnClose )

EVT_FB_CODE_GENERATION( MainFrame::OnCodeGeneration )
EVT_FB_OBJECT_CREATED( MainFrame::OnObjectCreated )
EVT_FB_OBJECT_REMOVED( MainFrame::OnObjectRemoved )
EVT_FB_OBJECT_EXPANDED( MainFrame::OnObjectExpanded )
EVT_FB_OBJECT_SELECTED( MainFrame::OnObjectSelected )
EVT_FB_PROJECT_LOADED( MainFrame::OnProjectLoaded )
EVT_FB_PROJECT_REFRESH( MainFrame::OnProjectRefresh )
EVT_FB_PROJECT_SAVED( MainFrame::OnProjectSaved )
EVT_FB_PROPERTY_MODIFIED( MainFrame::OnPropertyModified )
EVT_FB_EVENT_HANDLER_MODIFIED( MainFrame::OnEventHandlerModified )

EVT_MENU( ID_FIND, MainFrame::OnFindDialog )
EVT_FIND( wxID_ANY, MainFrame::OnFind )
EVT_FIND_NEXT( wxID_ANY, MainFrame::OnFind )
EVT_FIND_CLOSE( wxID_ANY, MainFrame::OnFindClose )

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
				propgrid->GetEventHandler()->ProcessEvent( focusEvent );
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
m_style( style ),
m_page_selection( 0 ),
m_findData( wxFR_DOWN ),
m_findDialog( NULL )
{
	/////////////////////////////////////////////////////////////////////////////
	// Setup frame icons, title bar, status bar, menubar and toolbar
	/////////////////////////////////////////////////////////////////////////////
	wxIconBundle bundle;
	wxIcon ico16;
	ico16.CopyFromBitmap( AppBitmaps::GetBitmap( wxT( "app16" ), 16 ) );
	bundle.AddIcon( ico16 );

	wxIcon ico32;
	ico32.CopyFromBitmap( AppBitmaps::GetBitmap( wxT( "app32" ), 32 ) );
	bundle.AddIcon( ico32 );

	SetIcons( bundle );

	SetTitle( wxT( "wxFormBuilder" ) );

	SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNFACE ) );

	SetMenuBar( CreateFBMenuBar() );
	CreateStatusBar( 3 );
	SetStatusBarPane( 0 );
	int widths[3] = { -1, -1, 300 };
	SetStatusWidths( sizeof( widths ) / sizeof( int ), widths );
//	CreateFBToolBar();

	/////////////////////////////////////////////////////////////////////////////
	// Create the gui
	/////////////////////////////////////////////////////////////////////////////

	wxWindow *objectTree      = CreateObjectTree(this);
	wxWindow *objectInspector = CreateObjectInspector(this);
	wxWindow *palette         = CreateComponentPalette(this);
	wxWindow *designer        = CreateDesignerWindow(this);


	m_mgr.SetManagedWindow(this);
	
	wxAuiToolBar* mainbar = CreateFBAuiToolBar();

	// TODO: Remove ICON_SIZE and TOOL_SIZE, use stock icons and add a function to resize bundled icons with system icons sizes

	m_mgr.AddPane(mainbar, wxAuiPaneInfo().
								Name(_("mainbar")).Caption(_("Toolbar")).
								ToolbarPane().Top().
								Direction(1).Layer(10).
								BestSize(750, 33).
								LeftDockable(false).RightDockable(false).
								CloseButton(false));

	m_mgr.AddPane(objectTree, wxAuiPaneInfo().
								Name(wxT("tree")).Caption(wxT("Object Tree")).
								Direction(4).Layer(1).			// Left().
								MinSize(210, 60).
								FloatingSize(210, 420).
								CloseButton(false));

	m_mgr.AddPane(objectInspector, wxAuiPaneInfo().
								Name(wxT("inspector")).Caption(wxT("Object Properties")).
								Direction(2).Layer(1).			// Right().
								MinSize(240, 300).
								FloatingSize(270, 420).
								CloseButton(false));

	m_mgr.AddPane(designer, wxAuiPaneInfo().
								Name(wxT("editor")).Caption(wxT("Editor")).
								Direction(5).Layer(0).			// Center().
								CloseButton(false));

	m_mgr.AddPane(palette, wxAuiPaneInfo().
								Name(wxT("palette")).Caption(wxT("Component Palette")).
								Direction(1).Layer(0).Row(1).	// Top().
								MinSize(-1, 72).
								MaxSize(-1, 72).
								FloatingSize(609, 120).
								RightDockable(false).LeftDockable(false).
								CloseButton(false));

    m_mgr.AddPane(new AuiSettingsPanel( this, this ), wxAuiPaneInfo().
								Name(wxT("settings")).Caption( _("Dock Manager Settings") ).
								Dockable(false).
								Float().
								Hide());

	m_mgr.SetFlags(wxAUI_MGR_DEFAULT | wxAUI_MGR_ALLOW_ACTIVE_PANE | wxAUI_MGR_TRANSPARENT_DRAG);

	m_mgr.Update();

	wxConfigBase *config = wxConfigBase::Get();

	wxString Perspective;
	if ( config->Read( wxT("/mainframe/aui/perspective"), &Perspective ) )
		m_mgr.LoadPerspective(Perspective);

	RestorePosition( wxT( "mainframe" ) );
	Layout();

	// Init. m_cpp and m_xrc first
	m_cpp = NULL;
	m_xrc = NULL;
	m_python = NULL;

	AppData()->AddHandler( this->GetEventHandler() );

	wxTheApp->SetTopWindow( this );

	m_focusKillEvtHandler = new FocusKillerEvtHandler;
	PushEventHandler( m_focusKillEvtHandler );

	// So we don't respond to a AuiNoteBookPageChanged event during construction
	m_notebook->Connect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED, wxAuiNotebookEventHandler( MainFrame::OnAuiNotebookPageChanged ), 0, this );
	m_notebook->Connect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGING, wxAuiNotebookEventHandler( MainFrame::OnAuiNotebookPageChanged ), 0, this );
};


MainFrame::~MainFrame()
{
	m_notebook->Disconnect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED, wxAuiNotebookEventHandler( MainFrame::OnAuiNotebookPageChanged ), 0, this );
	m_notebook->Disconnect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGING, wxAuiNotebookEventHandler( MainFrame::OnAuiNotebookPageChanged ), 0, this );

#ifdef __WXMAC__
    // work around problem on wxMac
// TODO: Mac still need this?
	m_mgr.Detach( m_notebook )
    m_notebook->Destroy();
#endif

	m_mgr.UnInit();

	// the focus killer event handler
	RemoveEventHandler( m_focusKillEvtHandler );
	delete m_focusKillEvtHandler;

	AppData()->RemoveHandler( this->GetEventHandler() );
	delete m_findDialog;
}

void MainFrame::RestorePosition( const wxString &name )
{
	m_currentDir = wxT( "./projects" );

	wxConfigBase *config = wxConfigBase::Get();
	config->SetPath( name );

	bool maximized;
	config->Read( wxT( "IsMaximized" ), &maximized, true );

	if ( maximized )
	{
		Maximize( maximized );
	}
	else
	{
		bool iconized;
		config->Read( wxT( "IsIconized" ), &iconized, false );

		if ( iconized )
		{
			Iconize( iconized );
		}
	}

	config->Read( wxT( "CurrentDirectory" ), &m_currentDir );

	config->Read( wxT( "RecentFile0" ), &m_recentProjects[0] );
	config->Read( wxT( "RecentFile1" ), &m_recentProjects[1] );
	config->Read( wxT( "RecentFile2" ), &m_recentProjects[2] );
	config->Read( wxT( "RecentFile3" ), &m_recentProjects[3] );

	config->SetPath( wxT( ".." ) );
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
		config->Write( wxT( "PosX" ), isIconized ? -1 : GetPosition().x );
		config->Write( wxT( "PosY" ), isIconized ? -1 : GetPosition().y );
		config->Write( wxT( "SizeW" ), isIconized ? -1 : GetSize().GetWidth() );
		config->Write( wxT( "SizeH" ), isIconized ? -1 : GetSize().GetHeight() );
	}

	config->Write( wxT( "IsMaximized" ), isMaximized );

	config->Write( wxT( "IsIconized" ), isIconized );
	config->Write( wxT( "CurrentDirectory" ), m_currentDir );

	config->Write( wxT( "RecentFile0" ), m_recentProjects[0] );
	config->Write( wxT( "RecentFile1" ), m_recentProjects[1] );
	config->Write( wxT( "RecentFile2" ), m_recentProjects[2] );
	config->Write( wxT( "RecentFile3" ), m_recentProjects[3] );

	config->SetPath( wxT( ".." ) );
	config->Write( wxT("/mainframe/editor/notebook_style"), m_notebook->GetWindowStyleFlag() );

	wxString Perspective = m_mgr.SavePerspective();
	config->Write( wxT("/mainframe/aui/perspective"), Perspective );
}

void MainFrame::OnSaveProject( wxCommandEvent &event )

{
	wxString filename = AppData()->GetProjectFileName();

	if ( filename == wxT( "" ) )
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
	wxFileDialog *dialog = new wxFileDialog( this, wxT( "Save Project" ), m_currentDir,
	                       wxT( "" ), wxT( "wxFormBuilder Project File (*.fbp)|*.fbp|All files (*.*)|*.*" ), wxFD_SAVE );

	if ( dialog->ShowModal() == wxID_OK )
	{
		m_currentDir = dialog->GetDirectory();
		wxString filename = dialog->GetPath();

		// Add the default extension if none was chosen
		wxFileName file( filename );

		if ( !file.HasExt() )
		{
			file.SetExt( wxT( "fbp" ) );
			filename = file.GetFullPath();
		}

		// Check the file whether exists or not
		if ( file.FileExists() == true )
		{
		    wxMessageDialog msg_box( this, wxT("The file already exists. Do you want to replace it?"), wxT("Overwrite the file"), wxYES_NO|wxICON_INFORMATION|wxNO_DEFAULT );
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

	wxFileDialog *dialog = new wxFileDialog( this, wxT( "Open Project" ), m_currentDir,
	                       wxT( "" ), wxT( "wxFormBuilder Project File (*.fbp)|*.fbp|All files (*.*)|*.*" ), wxFD_OPEN );

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
        if(wxMessageBox(wxString::Format(wxT("The project file '%s' doesn't exist. Would you like to remove it from the recent files list?"), filename.GetName().GetData()), wxT("Open recent project"), wxICON_WARNING | wxYES_NO) == wxYES)
        {
            m_recentProjects[i] = wxT("");
            UpdateRecentProjects();
        }
    }
}

void MainFrame::OnImportXrc( wxCommandEvent &)
{
	wxFileDialog *dialog = new wxFileDialog( this, wxT( "Import XRC file" ), m_currentDir,
	                       wxT( "example.xrc" ), wxT( "*.xrc" ), wxFD_OPEN );

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
				wxLogError( wxT( "Error while loading XRC" ) );
			}
		}
		catch ( wxFBException& ex )
		{
			wxLogError( _( "Error Loading XRC: %s" ), ex.what() );
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

	SavePosition( wxT( "mainframe" ) );
 
	event.Skip();
}

void MainFrame::OnProjectLoaded( wxFBEvent& )
{
	GetStatusBar()->SetStatusText( wxT( "Project Loaded!" ) );
	PObjectBase project = AppData()->GetProjectData();

	if ( project )
	{
		wxString objDetails = wxString::Format( wxT( "Name: %s | Class: %s" ), project->GetPropertyAsString( wxT( "name" ) ).c_str(), project->GetClassName().c_str() );
		GetStatusBar()->SetStatusText( objDetails, STATUS_FIELD_OBJECT );
	}

	UpdateFrame();
}

void MainFrame::OnProjectSaved( wxFBEvent& )
{
	GetStatusBar()->SetStatusText( wxT( "Project Saved!" ) );
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

	wxString name;
	PProperty prop( obj->GetProperty( wxT( "name" ) ) );

	if ( prop )
		name = prop->GetValueAsString();
	else
		name = wxT( "\"Unknown\"" );

	//GetStatusBar()->SetStatusText( wxT( "Object " ) + name + wxT( " Selected!" ) );

	wxString objDetails = wxString::Format( wxT( "Name: %s | Class: %s" ), name.c_str(), obj->GetClassName().c_str() );

	GetStatusBar()->SetStatusText( objDetails, STATUS_FIELD_OBJECT );

	UpdateFrame();
}

void MainFrame::OnObjectCreated( wxFBObjectEvent& event )
{
	wxString message;

	Debug::Print(wxT("MainFrame::OnObjectCreated"));

	if ( event.GetFBObject() )
	{
		message.Printf( wxT( "Object '%s' of class '%s' created." ),
		                event.GetFBObject()->GetPropertyAsString( wxT( "name" ) ).c_str(),
		                event.GetFBObject()->GetClassName().c_str() );
	}
	else
	{
		message = wxT( "Impossible to create the object. Did you forget to add a sizer/parent object?" );
		wxMessageBox( message, wxT("wxFormBuilder"), wxICON_WARNING | wxOK );
	}

	GetStatusBar()->SetStatusText( message );

	UpdateFrame();
}

void MainFrame::OnObjectRemoved( wxFBObjectEvent& event )
{
	wxString message;
	message.Printf( wxT( "Object '%s' removed." ),
	                event.GetFBObject()->GetPropertyAsString( wxT( "name" ) ).c_str() );
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
			if ( 0 == prop->GetName().CmpNoCase( wxT( "name" ) ) )
			{
				wxString oldDetails = GetStatusBar()->GetStatusText( STATUS_FIELD_OBJECT );
				wxString newDetails;
				size_t pipeIdx = oldDetails.find( wxT( "|" ) );

				if ( pipeIdx != oldDetails.npos )
				{
					newDetails.Printf( wxT( "Name: %s %s" ), prop->GetValueAsString().c_str(), oldDetails.substr( pipeIdx ).c_str() );
					GetStatusBar()->SetStatusText( newDetails, STATUS_FIELD_OBJECT );
				}
			}

			GetStatusBar()->SetStatusText( wxT( "Property Modified!" ) );
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
	message.Printf( wxT( "Event handler '%s' of object '%s' modified." ),
	                event.GetFBEventHandler()->GetName().c_str(),
	                event.GetFBEventHandler()->GetObject()->GetPropertyAsString( wxT( "name" ) ).c_str() );

	GetStatusBar()->SetStatusText( message );
	UpdateFrame();
}

void MainFrame::OnCodeGeneration( wxFBEvent& event )
{
	// Using the previously unused Id field in the event to carry a boolean
	bool panelOnly = ( event.GetId() != 0 );

	if ( panelOnly )
	{
		GetStatusBar()->SetStatusText( wxT( "Code Generated!" ) );
	}
}

void MainFrame::OnProjectRefresh( wxFBEvent& )
{
	PObjectBase project = AppData()->GetProjectData();

	if ( project )
	{
		wxString objDetails = wxString::Format( wxT( "Name: %s | Class: %s" ), project->GetPropertyAsString( wxT( "name" ) ).c_str(), project->GetClassName().c_str() );
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
	wxAuiToolBar* mainbar = this->GetToolBar();
	wxMenu* menuEdit = GetMenuBar()->GetMenu( GetMenuBar()->FindMenu( wxT( "Edit" ) ) );

	// Enable the layout tools if there are layout settings, else disable the tools
	menuEdit->Enable( ID_EXPAND, gotLayoutSettings );
	mainbar->EnableTool( ID_EXPAND, gotLayoutSettings );
	menuEdit->Enable( ID_STRETCH, option >= 0 );
	mainbar->EnableTool( ID_STRETCH, option >= 0 );

	bool enableHorizontalTools = ( orient != wxHORIZONTAL ) && gotLayoutSettings;
	menuEdit->Enable( ID_ALIGN_LEFT, enableHorizontalTools );
	mainbar->EnableTool( ID_ALIGN_LEFT, enableHorizontalTools );
	menuEdit->Enable( ID_ALIGN_CENTER_H, enableHorizontalTools );
	mainbar->EnableTool( ID_ALIGN_CENTER_H, enableHorizontalTools );
	menuEdit->Enable( ID_ALIGN_RIGHT, enableHorizontalTools );
	mainbar->EnableTool( ID_ALIGN_RIGHT, enableHorizontalTools );

	bool enableVerticalTools = ( orient != wxVERTICAL ) && gotLayoutSettings;
	menuEdit->Enable( ID_ALIGN_TOP, enableVerticalTools );
	mainbar->EnableTool( ID_ALIGN_TOP, enableVerticalTools );
	menuEdit->Enable( ID_ALIGN_CENTER_V, enableVerticalTools );
	mainbar->EnableTool( ID_ALIGN_CENTER_V, enableVerticalTools );
	menuEdit->Enable( ID_ALIGN_BOTTOM, enableVerticalTools );
	mainbar->EnableTool( ID_ALIGN_BOTTOM, enableVerticalTools );

	mainbar->EnableTool( ID_BORDER_TOP, gotLayoutSettings );
	mainbar->EnableTool( ID_BORDER_RIGHT, gotLayoutSettings );
	mainbar->EnableTool( ID_BORDER_LEFT, gotLayoutSettings );
	mainbar->EnableTool( ID_BORDER_BOTTOM, gotLayoutSettings );

	// Toggle the toolbar buttons according to the properties, if there are layout settings
	mainbar->ToggleTool( ID_EXPAND,         ( ( flag & wxEXPAND ) != 0 ) && gotLayoutSettings );
	mainbar->ToggleTool( ID_STRETCH,        ( option > 0 ) && gotLayoutSettings );
	mainbar->ToggleTool( ID_ALIGN_LEFT,     !( ( flag & ( wxALIGN_RIGHT | wxALIGN_CENTER_HORIZONTAL ) ) != 0 ) && enableHorizontalTools );
	mainbar->ToggleTool( ID_ALIGN_CENTER_H, ( ( flag & wxALIGN_CENTER_HORIZONTAL ) != 0 ) && enableHorizontalTools );
	mainbar->ToggleTool( ID_ALIGN_RIGHT,    ( ( flag & wxALIGN_RIGHT ) != 0 ) && enableHorizontalTools );
	mainbar->ToggleTool( ID_ALIGN_TOP,      !( ( flag & ( wxALIGN_BOTTOM | wxALIGN_CENTER_VERTICAL ) ) != 0 ) && enableVerticalTools );
	mainbar->ToggleTool( ID_ALIGN_CENTER_V, ( ( flag & wxALIGN_CENTER_VERTICAL ) != 0 ) && enableVerticalTools );
	mainbar->ToggleTool( ID_ALIGN_BOTTOM,   ( ( flag & wxALIGN_BOTTOM ) != 0 ) && enableVerticalTools );

	mainbar->ToggleTool( ID_BORDER_TOP,      ( ( flag & wxTOP ) != 0 ) && gotLayoutSettings );
	mainbar->ToggleTool( ID_BORDER_RIGHT,    ( ( flag & wxRIGHT ) != 0 ) && gotLayoutSettings );
	mainbar->ToggleTool( ID_BORDER_LEFT,     ( ( flag & wxLEFT ) != 0 ) && gotLayoutSettings );
	mainbar->ToggleTool( ID_BORDER_BOTTOM,   ( ( flag & wxBOTTOM ) != 0 ) && gotLayoutSettings );

	m_mgr.Update();
}

void MainFrame::UpdateFrame()
{
	// Build the title
	wxString filename = AppData()->GetProjectFileName();
	wxString file;

	if ( filename.empty() )
	{
		file = wxT("untitled");
	}
	else
	{
		wxFileName fn( filename );
		file = fn.GetName();
	}

	SetTitle( wxString::Format( wxT("%s%s - wxFormBuilder v3.1 - Beta"), AppData()->IsModified() ? wxT("*") : wxT(""), file.c_str() ) );
	GetStatusBar()->SetStatusText( filename, STATUS_FIELD_PATH );

	// Enable/Disable toolbar and menu entries
	wxMenu* menuEdit = GetMenuBar()->GetMenu( GetMenuBar()->FindMenu( wxT( "Edit" ) ) );

	bool redo = AppData()->CanRedo();
	menuEdit->Enable( ID_REDO, redo );
	mainbar->EnableTool( ID_REDO, redo );

	bool undo = AppData()->CanUndo();
	menuEdit->Enable( ID_UNDO, undo );
	mainbar->EnableTool( ID_UNDO, undo );

	bool copy = AppData()->CanCopyObject();
	bool isEditor = ( _("Designer") != m_notebook->GetPageText( m_notebook->GetSelection() ) );
	menuEdit->Enable( ID_FIND, isEditor );

	menuEdit->Enable( ID_CLIPBOARD_COPY, copy );

	menuEdit->Enable( ID_COPY, copy || isEditor );
	mainbar->EnableTool( ID_COPY, copy || isEditor );

	menuEdit->Enable( ID_CUT, copy );
	mainbar->EnableTool( ID_CUT, copy );

	menuEdit->Enable( ID_DELETE, copy );
	mainbar->EnableTool( ID_DELETE, copy );

	menuEdit->Enable( ID_MOVE_UP, copy );
	menuEdit->Enable( ID_MOVE_DOWN, copy );
	menuEdit->Enable( ID_MOVE_LEFT, copy );
	menuEdit->Enable( ID_MOVE_RIGHT, copy );

	bool paste = AppData()->CanPasteObject();
	menuEdit->Enable( ID_PASTE, paste );
	mainbar->EnableTool( ID_PASTE, paste );

	menuEdit->Enable( ID_CLIPBOARD_PASTE, AppData()->CanPasteObjectFromClipboard() );

	UpdateLayoutTools();
}

void MainFrame::UpdateRecentProjects()
{
	int i, fi;
	wxMenu *menuFile = GetMenuBar()->GetMenu( GetMenuBar()->FindMenu( wxT( "File" ) ) );

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
		menuFile->Append( ID_RECENT_0 + i, m_recentProjects[i], wxT( "" ) );
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

	if ( focusedWindow != NULL && focusedWindow->IsKindOf( CLASSINFO( wxStyledTextCtrl ) ) )
		( ( wxStyledTextCtrl* )focusedWindow )->Copy();
	else
	{
		AppData()->CopyObject( AppData()->GetSelectedObject() );
		UpdateFrame();
	}
}

void MainFrame::OnCut ( wxCommandEvent &)
{
	wxWindow *focusedWindow = wxWindow::FindFocus();

	if ( focusedWindow != NULL && focusedWindow->IsKindOf( CLASSINFO( wxStyledTextCtrl ) ) )
		( ( wxStyledTextCtrl* )focusedWindow )->Cut();
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

	if ( focusedWindow != NULL && focusedWindow->IsKindOf( CLASSINFO( wxStyledTextCtrl ) ) )
		( ( wxStyledTextCtrl* )focusedWindow )->Paste();
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

	wxAuiPaneInfoArray& all_panes = m_mgr.GetAllPanes();
	for ( int i = 0, count = all_panes.GetCount(); i < count; ++i )
	{
		wxAuiPaneInfo info = all_panes.Item( i );
	}

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
	if ( project->IsNull( _("file") ) )
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
	
	wxMessageBox( wxString::Format( wxT( "Class(es) generated to \'%s\'." ), filePath.c_str() ), wxT("wxFormBuilder") );
}

bool MainFrame::SaveWarning()
{
	int result = wxYES;

	if ( AppData()->IsModified() )
	{
		result = ::wxMessageBox( wxT( "Current project file has been modified...\n" )
		                         wxT( "Do you want to save the changes?" ),
		                         wxT( "Save project" ),
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

void MainFrame::OnAuiNotebookPageChanged( wxAuiNotebookEvent& event )
{
	UpdateFrame(); // TODO: before GenerateCode?
	AppData()->GenerateCode( true );
	event.Skip();
}

void MainFrame::OnFindDialog( wxCommandEvent& )
{
	if ( NULL == m_findDialog )
	{
		m_findDialog = new wxFindReplaceDialog( this, &m_findData, wxT("Find") );
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
	for ( unsigned int page = 0; page < m_notebook->GetPageCount(); ++page )
	{
		event.StopPropagation();
		event.SetClientData( m_findDialog );
		m_notebook->GetPage( page )->GetEventHandler()->ProcessEvent( event );
	}
}

/////////////////////////////////////////////////////////////////////////////

wxMenuBar * MainFrame::CreateFBMenuBar()
{
	wxMenu *menuFile = new wxMenu;
	menuFile->Append( ID_NEW_PRJ, wxT( "&New Project\tCtrl+N" ), wxT( "Create an empty project" ) );
	menuFile->Append( ID_OPEN_PRJ, wxT( "&Open...\tCtrl+O" ), wxT( "Open a project" ) );

	menuFile->Append( ID_SAVE_PRJ,          wxT( "&Save\tCtrl+S" ), wxT( "Save current project" ) );
	menuFile->Append( ID_SAVE_AS_PRJ, wxT( "Save &As...\tCtrl-Shift+S" ), wxT( "Save current project as..." ) );
	menuFile->AppendSeparator();
	menuFile->Append( ID_IMPORT_XRC, wxT( "&Import XRC..." ), wxT( "Import XRC file" ) );
	menuFile->AppendSeparator();
	menuFile->Append( ID_GENERATE_CODE, wxT( "&Generate Code\tF8" ), wxT( "Generate Code" ) );
	menuFile->AppendSeparator();
	menuFile->Append( wxID_EXIT, wxT( "E&xit\tAlt-F4" ), wxT( "Quit wxFormBuilder" ) );

	wxMenu *menuEdit = new wxMenu;
	menuEdit->Append( ID_UNDO, wxT( "&Undo \tCtrl+Z" ), wxT( "Undo changes" ) );
	menuEdit->Append( ID_REDO, wxT( "&Redo \tCtrl+Y" ), wxT( "Redo changes" ) );
	menuEdit->AppendSeparator();
	menuEdit->Append( ID_COPY, wxT( "&Copy \tCtrl+C" ), wxT( "Copy selected object" ) );
	menuEdit->Append( ID_CUT, wxT( "Cut \tCtrl+X" ), wxT( "Cut selected object" ) );
	menuEdit->Append( ID_PASTE, wxT( "&Paste \tCtrl+V" ), wxT( "Paste on selected object" ) );
	menuEdit->Append( ID_DELETE, wxT( "&Delete \tCtrl+D" ), wxT( "Delete selected object" ) );
	menuEdit->AppendSeparator();
	menuEdit->Append( ID_CLIPBOARD_COPY, wxT("Copy Object To Clipboard\tCtrl+Shift+C"), wxT("Copy Object to Clipboard") );
	menuEdit->Append( ID_CLIPBOARD_PASTE, wxT("Paste Object From Clipboard\tCtrl+Shift+V"), wxT("Paste Object from Clipboard") );
	menuEdit->AppendSeparator();
	menuEdit->Append( ID_EXPAND, wxT( "Toggle &Expand\tAlt+W" ), wxT( "Toggle wxEXPAND flag of sizeritem properties" ) );
	menuEdit->Append( ID_STRETCH, wxT( "Toggle &Stretch\tAlt+S" ), wxT( "Toggle option property of sizeritem properties" ) );
	menuEdit->Append( ID_MOVE_UP, wxT( "Move Up\tAlt+Up" ), wxT( "Move Up selected object" ) );
	menuEdit->Append( ID_MOVE_DOWN, wxT( "Move Down\tAlt+Down" ), wxT( "Move Down selected object" ) );
	menuEdit->Append( ID_MOVE_LEFT, wxT( "Move Left\tAlt+Left" ), wxT( "Move Left selected object" ) );
	menuEdit->Append( ID_MOVE_RIGHT, wxT( "Move Right\tAlt+Right" ), wxT( "Move Right selected object" ) );
	menuEdit->AppendSeparator();
	menuEdit->Append( ID_FIND, wxT( "&Find\tCtrl+F" ), wxT( "Find text in the active code viewer" ) );
	menuEdit->AppendSeparator();
	menuEdit->Append( ID_ALIGN_LEFT,     wxT( "&Align &Left\tAlt+Shift+Left" ),           wxT( "Align item to the left" ) );
	menuEdit->Append( ID_ALIGN_CENTER_H, wxT( "&Align Center &Horizontal\tAlt+Shift+H" ), wxT( "Align item to the center horizontally" ) );
	menuEdit->Append( ID_ALIGN_RIGHT,    wxT( "&Align &Right\tAlt+Shift+Right" ),         wxT( "Align item to the right" ) );
	menuEdit->Append( ID_ALIGN_TOP,      wxT( "&Align &Top\tAlt+Shift+Up" ),              wxT( "Align item to the top" ) );
	menuEdit->Append( ID_ALIGN_CENTER_V, wxT( "&Align Center &Vertical\tAlt+Shift+V" ),   wxT( "Align item to the center vertically" ) );
	menuEdit->Append( ID_ALIGN_BOTTOM,   wxT( "&Align &Bottom\tAlt+Shift+Down" ),         wxT( "Align item to the bottom" ) );

	wxMenu *menuView = new wxMenu;
	menuView->Append( ID_PREVIEW_XRC, wxT( "&XRC Window\tF5" ), wxT( "Show a preview of the XRC window" ) );

	wxMenu *menuTools = new wxMenu;
	menuTools->Append( ID_GEN_INHERIT_CLS, wxT( "&Generate Inherited Class\tF6" ), wxT( "Creates the needed files and class for proper inheritance of your designed GUI" ) );

	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append( wxID_ABOUT, wxT( "&About...\tF1" ), wxT( "Show about dialog" ) );


	// now append the freshly created menu to the menu bar...
	wxMenuBar *menuBar = new wxMenuBar();
	menuBar->Append( menuFile, wxT( "&File" ) );
	menuBar->Append( menuEdit, wxT( "&Edit" ) );
	menuBar->Append( menuView, wxT( "&View" ) );
	menuBar->Append( menuTools, wxT( "&Tools" ) );
	menuBar->Append( menuHelp, wxT( "&Help" ) );

	return menuBar;
}

wxAuiToolBar * MainFrame::CreateFBAuiToolBar()
{
	wxAuiToolBarItemArray prepend_items;
	wxAuiToolBarItemArray append_items;
	wxAuiToolBarItem item;

	item.SetKind( wxITEM_NORMAL );
	item.SetId( ID_AUI_SETTINGS );
	item.SetLabel( _("Customize...") );
	item.SetBitmap( AppBitmaps::GetBitmap( wxT( "generate" ), 16 ) );
	append_items.Add( item );

	mainbar = new wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_OVERFLOW);
	mainbar->SetToolBitmapSize( wxSize( TOOL_SIZE, TOOL_SIZE ) );
	mainbar->AddTool( ID_NEW_PRJ, _( "New Project" ), AppBitmaps::GetBitmap( wxT( "new" ), TOOL_SIZE ), wxNullBitmap, wxITEM_NORMAL, _( "New Project (Ctrl+N)" ), _( "Start a new project." ), NULL );
	mainbar->AddTool( ID_OPEN_PRJ, _( "Open Project" ), AppBitmaps::GetBitmap( wxT( "open" ), TOOL_SIZE ), wxNullBitmap, wxITEM_NORMAL, _( "Open Project (Ctrl+O)" ), _( "Open an existing project." ), NULL );
	mainbar->AddTool( ID_SAVE_PRJ, _( "Save Project" ), AppBitmaps::GetBitmap( wxT( "save" ), TOOL_SIZE ), wxNullBitmap, wxITEM_NORMAL, _( "Save Project (Ctrl+S)" ), _( "Save the current project." ), NULL );
	mainbar->AddSeparator();
	mainbar->AddTool( ID_UNDO, _( "Undo" ), AppBitmaps::GetBitmap( wxT( "undo" ), TOOL_SIZE ), wxNullBitmap, wxITEM_NORMAL, _( "Undo (Ctrl+Z)" ), _( "Undo the last action." ), NULL );
	mainbar->AddTool( ID_REDO, _( "Redo" ), AppBitmaps::GetBitmap( wxT( "redo" ), TOOL_SIZE ), wxNullBitmap, wxITEM_NORMAL, _( "Redo (Ctrl+Y)" ), _( "Redo the last action that was undone." ), NULL );
	mainbar->AddSeparator();
	mainbar->AddTool( ID_CUT, _( "Cut" ), AppBitmaps::GetBitmap( wxT( "cut" ), TOOL_SIZE ), wxNullBitmap, wxITEM_NORMAL, _( "Cut (Ctrl+X)" ), _( "Remove the selected object and place it on the clipboard." ), NULL );
	mainbar->AddTool( ID_COPY, _( "Copy" ), AppBitmaps::GetBitmap( wxT( "copy" ), TOOL_SIZE ), wxNullBitmap, wxITEM_NORMAL, _( "Copy (Ctrl+C)" ), _( "Copy the selected object to the clipboard." ), NULL );
	mainbar->AddTool( ID_PASTE, _( "Paste" ), AppBitmaps::GetBitmap( wxT( "paste" ), TOOL_SIZE ), wxNullBitmap, wxITEM_NORMAL, _( "Paste (Ctrl+V)" ), _( "Insert an object from the clipboard." ), NULL );
	mainbar->AddTool( ID_DELETE, _( "Delete" ), AppBitmaps::GetBitmap( wxT( "delete" ), TOOL_SIZE ), wxNullBitmap, wxITEM_NORMAL, _( "Delete (Ctrl+D)" ), _( "Remove the selected object." ), NULL );
	mainbar->AddSeparator();
	mainbar->AddTool( ID_GENERATE_CODE, _( "Generate Code" ), AppBitmaps::GetBitmap( wxT( "generate" ), TOOL_SIZE ), wxNullBitmap, wxITEM_NORMAL, _( "Generate Code (F8)" ), _( "Create code from the current project." ), NULL );
	mainbar->AddSeparator();
	mainbar->AddTool( ID_ALIGN_LEFT, wxEmptyString, AppBitmaps::GetBitmap( wxT( "lalign" ), TOOL_SIZE ), wxNullBitmap, wxITEM_CHECK, _( "Align Left" ), _( "The item will be aligned to the left of the space alotted to it by the sizer." ), NULL );
	mainbar->AddTool( ID_ALIGN_CENTER_H, wxEmptyString, AppBitmaps::GetBitmap( wxT( "chalign" ), TOOL_SIZE ), wxNullBitmap, wxITEM_CHECK, _( "Align Center Horizontally" ), _( "The item will be centered horizontally in the space alotted to it by the sizer." ), NULL );
	mainbar->AddTool( ID_ALIGN_RIGHT, wxEmptyString, AppBitmaps::GetBitmap( wxT( "ralign" ), TOOL_SIZE ), wxNullBitmap, wxITEM_CHECK, _( "Align Right" ), _( "The item will be aligned to the right of the space alotted to it by the sizer." ), NULL );
	mainbar->AddSeparator();
	mainbar->AddTool( ID_ALIGN_TOP, wxEmptyString, AppBitmaps::GetBitmap( wxT( "talign" ), TOOL_SIZE ), wxNullBitmap, wxITEM_CHECK, _( "Align Top" ), _( "The item will be aligned to the top of the space alotted to it by the sizer." ), NULL );
	mainbar->AddTool( ID_ALIGN_CENTER_V, wxEmptyString, AppBitmaps::GetBitmap( wxT( "cvalign" ), TOOL_SIZE ), wxNullBitmap, wxITEM_CHECK, _( "Align Center Vertically" ), _( "The item will be centered vertically within space alotted to it by the sizer." ), NULL );
	mainbar->AddTool( ID_ALIGN_BOTTOM, wxEmptyString, AppBitmaps::GetBitmap( wxT( "balign" ), TOOL_SIZE ), wxNullBitmap, wxITEM_CHECK, _( "Align Bottom" ), _( "The item will be aligned to the bottom of the space alotted to it by the sizer." ), NULL );
	mainbar->AddSeparator();
	mainbar->AddTool( ID_EXPAND, wxEmptyString, AppBitmaps::GetBitmap( wxT( "expand" ), TOOL_SIZE ), wxNullBitmap, wxITEM_CHECK, _( "Expand (Alt+W)" ), _( "The item will be expanded to fill the space assigned to the item." ), NULL );
	mainbar->AddTool( ID_STRETCH, wxEmptyString, AppBitmaps::GetBitmap( wxT( "stretch" ), TOOL_SIZE ), wxNullBitmap, wxITEM_CHECK, _( "Stretch (Alt+S)" ), _( "The item will grow and shrink with the sizer." ), NULL );
	mainbar->AddSeparator();
	mainbar->AddTool( ID_BORDER_LEFT, wxEmptyString, AppBitmaps::GetBitmap( wxT( "left" ), TOOL_SIZE ), wxNullBitmap, wxITEM_CHECK, _( "Left Border" ), _( "A border will be added on the left side of the item." ), NULL );
	mainbar->AddTool( ID_BORDER_RIGHT, wxEmptyString, AppBitmaps::GetBitmap( wxT( "right" ), TOOL_SIZE ), wxNullBitmap, wxITEM_CHECK, _( "Right Border" ), _( "A border will be  added on the right side of the item." ), NULL );
	mainbar->AddTool( ID_BORDER_TOP, wxEmptyString, AppBitmaps::GetBitmap( wxT( "top" ), TOOL_SIZE ), wxNullBitmap, wxITEM_CHECK, _( "Top Border" ), _( "A border will be  added on the top of the item." ), NULL );
	mainbar->AddTool( ID_BORDER_BOTTOM, wxEmptyString, AppBitmaps::GetBitmap( wxT( "bottom" ), TOOL_SIZE ), wxNullBitmap, wxITEM_CHECK, _( "Bottom Border" ), _( "A border will be  added on the bottom of the item." ), NULL );
	mainbar->SetCustomOverflowItems( prepend_items, append_items );
	mainbar->Realize();

	return mainbar;
}

wxWindow * MainFrame::CreateDesignerWindow( wxWindow *parent )
{
	long nbStyle = 0;
	wxConfigBase* config = wxConfigBase::Get();
	config->Read( wxT("/mainframe/editor/notebook_style"), &nbStyle, wxAUI_NB_TAB_MOVE | wxAUI_NB_WINDOWLIST_BUTTON | wxAUI_NB_SCROLL_BUTTONS | wxAUI_NB_TOP );

	m_notebook = new wxAuiNotebook( parent, ID_EDITOR_FNB, wxDefaultPosition, wxDefaultSize, nbStyle );

	m_visualEdit = new VisualEditor( m_notebook );
	AppData()->GetManager()->SetVisualEditor( m_visualEdit );

	m_notebook->AddPage( m_visualEdit, wxT( "Designer" ), false, AppBitmaps::GetBitmap( wxT( "designer" ), 16 ) );

	m_cpp = new CppPanel( m_notebook, -1 );
	m_notebook->AddPage( m_cpp, wxT( "C++" ), false, AppBitmaps::GetBitmap( wxT( "c++" ), 16 ) );

	m_python = new PythonPanel( m_notebook, -1 );
	m_notebook->AddPage( m_python, wxT( "Python" ), false, AppBitmaps::GetBitmap( wxT( "c++" ), 16 ) );

	m_xrc = new XrcPanel( m_notebook, -1 );
	m_notebook->AddPage( m_xrc, wxT( "XRC" ), false, AppBitmaps::GetBitmap( wxT( "xrc" ), 16 ) );

	return m_notebook;
}

wxWindow * MainFrame::CreateComponentPalette ( wxWindow *parent )
{
	// la paleta de componentes, no es un observador propiamente dicho, ya
	// que no responde ante los eventos de la aplicación
	m_palette = new wxFbPalette( parent, -1 );
	m_palette->Create();
	m_palette->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DFACE ) );

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
	// TODO: make object inspector style selectable.
//	int style = ( m_style == wxFB_CLASSIC_GUI ? wxFB_OI_MULTIPAGE_STYLE : wxFB_OI_SINGLE_PAGE_STYLE );
	int style = wxFB_OI_SINGLE_PAGE_STYLE;
	m_objInsp = new ObjectInspector( parent, -1, style );

	return m_objInsp;
}

void MainFrame::OnAuiSettings(wxCommandEvent& WXUNUSED(evt))
{
    // show the settings pane, and float it
    wxAuiPaneInfo& floating_pane = m_mgr.GetPane( _("settings") ).Float().Show();

    if (floating_pane.floating_pos == wxDefaultPosition)
        floating_pane.FloatingPosition(GetStartPosition());

    m_mgr.Update();
}

wxAuiDockArt* MainFrame::GetDockArt()
{
    return m_mgr.GetArtProvider();
}

void MainFrame::DoUpdate()
{
    m_mgr.Update();
}

wxPoint MainFrame::GetStartPosition()
{
    static int x = 0;
    x += 20;
    wxPoint pt = ClientToScreen(wxPoint(0,0));
    return wxPoint(pt.x + x, pt.y + x);
}
