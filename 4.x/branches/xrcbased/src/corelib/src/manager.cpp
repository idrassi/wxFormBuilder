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
/**
 * @file    manager.cpp
 * @author  Andrea Zanellato (zanellato.andrea@gmail.com)
 * @date    2011/09/07
 * @version 0.0.1
 */
#include "manager.h"

#include <wx/dir.h>
#include <wx/image.h>
#include <wx/msgdlg.h>
#include <wx/panel.h>
#include <wx/propgrid/manager.h>
#include <wx/sizer.h>
#include <wx/stdpaths.h>
#include <wx/treectrl.h>

#include <wx/log.h>

wxFBResource::wxFBResource() : wxXmlResource( wxXRC_USE_LOCALE | wxXRC_NO_SUBCLASSING, wxEmptyString )
{
    m_bUsingAUI = false;
    m_frame     = NULL;
    m_menuBar   = NULL;
    m_toolBar   = NULL;
    m_objTree   = NULL;
    m_editor    =
    m_objInsp   =
    m_objPalette = NULL;
    m_objInspImages = NULL;
    m_pgProps = m_pgEvents = NULL;

    wxInitAllImageHandlers();
    InitAllHandlers();

    m_pgXrcHandler = new wxPropertyGridXmlHandler;

    AddHandler( m_pgXrcHandler );
    AddHandler( new wxStyledTextCtrlXmlHandler );
//    AddHandler( new wxFBProjectXmlHandler );

    if ( !Load( wxFB_ABOUT ) ) return;
    if ( !Load( wxFB_EDITOR ) ) return;
    if ( !Load( wxFB_OBJECT_INSPECTOR ) ) return;
    if ( !Load( wxFB_OBJECT_PALETTE ) ) return;
    if ( !Load( wxFB_OBJECT_TREE ) ) return;
    if ( !Load( wxFB_DEFAULT_PROJECT ) ) return;
}

wxFBResource::~wxFBResource()
{
}

wxDialog *wxFBResource::GetAboutDialog( wxWindow *parent )
{
    wxDialog *dlg = LoadDialog( parent, wxT("About") );

    return dlg;
}

wxMenuBar *wxFBResource::GetMainMenu( wxWindow *parent )
{
    if ( !m_menuBar )
    {
        Load( wxFB_MAINMENU );
        m_menuBar  = LoadMenuBar( parent, wxT("MainMenu") );
    }

    return m_menuBar;
}

wxToolBar *wxFBResource::GetToolBar( wxWindow *parent )
{
    if ( !m_toolBar )
    {
        Load( wxFB_TOOLBAR );
        m_toolBar = LoadToolBar( parent, wxT("ToolBar") );
    }

    return m_toolBar;
}

wxFrame *wxFBResource::GetMainFrame( wxWindow *parent, bool aui )
{
    // We have already required frame
    if ( (aui && m_bUsingAUI) || (!aui && !m_bUsingAUI && m_frame) )
    {
        return m_frame;
    }

    // First request
    if ( !m_frame )
    {
        if ( !Load( wxFB_MAINFRAME ) ) return NULL;

        if ( aui )
        {
/*
            AddHandler( new wxAuiXmlHandler );

            m_bUsingAUI = Load( wxFB_AUIFRAME );
            m_frame     = LoadAuiFrame( parent, wxT("AUIFrame") );
*/
        }
        else // Not using AUI
        {
            m_frame = LoadFrame( NULL, wxT("MainFrame") );

            if ( !m_frame ) return NULL;

            wxSplitterWindow *leftSplitter  = wxDynamicCast( m_frame->FindWindowById( XRCID("LeftSplitter") ), wxSplitterWindow );
            wxSplitterWindow *rightSplitter = wxDynamicCast( m_frame->FindWindowById( XRCID("RightSplitter") ), wxSplitterWindow );

            if ( !leftSplitter || !rightSplitter ) return m_frame;

            wxPanel *editPanel = wxDynamicCast( rightSplitter->FindWindowById( XRCID("EditorPanel") ), wxPanel );
            wxPanel *inspPanel = wxDynamicCast( rightSplitter->FindWindowById( XRCID("ObjInspPanel") ), wxPanel );
            wxPanel *treePanel = wxDynamicCast( leftSplitter->FindWindowById( XRCID("ObjTreePanel") ), wxPanel );
            wxPanel *paltPanel = wxDynamicCast( leftSplitter->FindWindowById( XRCID("PalettePanel") ), wxPanel );

            if( !editPanel || !inspPanel || !treePanel || !paltPanel ) return m_frame;

            wxNotebook *inspBook = GetObjectInspector( inspPanel );
            wxNotebook *paltBook = GetObjectPalette( paltPanel );
            wxTreeCtrl *treeCtrl = GetObjectTree( treePanel );
            wxNotebook *editBook = GetEditor( editPanel );

            if( !inspBook || !paltBook || !treeCtrl || !editBook ) return m_frame;

            inspPanel->GetSizer()->Add( inspBook, 1, wxEXPAND );
            paltPanel->GetSizer()->Add( paltBook, 0, wxEXPAND );
            treePanel->GetSizer()->Add( treeCtrl, 1, wxEXPAND );
            editPanel->GetSizer()->Add( editBook, 1, wxEXPAND );

            m_handler = new wxFBFrameHandler( m_frame, leftSplitter, rightSplitter );
/*
            wxPropertyGridManager *pg = wxDynamicCast( FindWindowById( XRCID("ObjectProperties") ), wxPropertyGridManager );
            wxPropertyGridManager *eg = wxDynamicCast( FindWindowById( XRCID("ObjectEvents") ), wxPropertyGridManager );
            if ( pg ) m_pg = pg->GetGrid();
            if ( eg ) m_eg = eg->GetGrid();
*/
        }

        m_frame->SetMenuBar( GetMainMenu( m_frame ) );
        m_frame->SetToolBar( GetToolBar( m_frame ) );

        m_frame->Connect( XRCID("wxID_ABOUT"), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( wxFBFrameHandler::OnAbout ),      NULL, m_handler );
        m_frame->Connect( XRCID("wxID_NEW"),   wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( wxFBFrameHandler::OnNewProject ), NULL, m_handler );
        m_frame->Connect( XRCID("wxID_EXIT"),  wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( wxFBFrameHandler::OnExit ),       NULL, m_handler );
        m_frame->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( wxFBFrameHandler::OnClose ), NULL, m_handler );
        m_frame->Connect( wxEVT_IDLE, wxIdleEventHandler( wxFBFrameHandler::OnIdle ), NULL, m_handler );
    }
    // Switch GUI
    else
    {
        if ( aui )
        {
            // TODO: reparent...
        }
        else // Not using AUI
        {
            if ( m_bUsingAUI )
            {
                // TODO: reparent...
/*
                m_mgr.UnInit();
                m_bUsingAUI = false;
*/
            }
        }
    }

    if ( wxFileName::FileExists( wxFB_LOGO ) );
    {
        wxIcon       ico16, ico32;
        wxIconBundle bundle;
        wxImage      imgLogo = wxImage( wxFB_LOGO );

        ico16.CopyFromBitmap( imgLogo.Scale( 16, 16 ) );
        bundle.AddIcon( ico16 );

        ico32.CopyFromBitmap( imgLogo.Scale( 32, 32 ) );
        bundle.AddIcon( ico32 );

        m_frame->SetIcons( bundle );
    }

    return m_frame;
}

wxNotebook *wxFBResource::GetEditor( wxWindow *parent )
{
    if ( !m_editor )
    {
        m_editor = wxDynamicCast( LoadObject( parent, wxT("Editor"), wxT("wxNotebook") ), wxNotebook );
    }

    return m_editor;
}

wxNotebook *wxFBResource::GetObjectInspector( wxWindow *parent )
{
    if ( !m_objInsp )
    {
        m_objInsp = wxDynamicCast( LoadObject( parent, wxT("ObjectInspector"), wxT("wxNotebook") ), wxNotebook );

        if ( m_objInsp )
        {
            m_pgProps  = wxDynamicCast( m_objInsp->FindWindowById( XRCID("ObjectProperties") ), wxPropertyGridManager );
            m_pgEvents = wxDynamicCast( m_objInsp->FindWindowById( XRCID("ObjectEvents") ), wxPropertyGridManager );
            m_objInspImages = m_objInsp->GetImageList();
        }
    }

    return m_objInsp;
}

wxNotebook *wxFBResource::GetObjectPalette( wxWindow *parent )
{
    if ( !m_objPalette )
    {
        m_objPalette = wxDynamicCast( LoadObject( parent, wxT("ObjectPalette"), wxT("wxNotebook") ), wxNotebook );
    }

    return m_objPalette;
}

wxTreeCtrl *wxFBResource::GetObjectTree( wxWindow *parent )
{
    if ( !m_objTree )
    {
        m_objTree = wxDynamicCast( LoadObject( parent, wxT("ObjectTree"), wxT("wxTreeCtrl") ), wxTreeCtrl );
    }

    return m_objTree;
}

void wxFBResource::NewProject()
{
    if ( m_objInsp )
    {
        wxPropertyGridManager *pg = wxDynamicCast( LoadObject( m_objInsp, wxT("DefaultProject"), wxT("wxPropertyGridManager") ), wxPropertyGridManager );

        if ( pg )
        {
            m_objInsp->RemovePage( 0 );
            m_objInsp->InsertPage( 0, pg, _("Properties"), true, 0 );
        }
    }

    if ( m_objTree )
    {
        m_objTree->DeleteAllItems();
        m_objTree->AddRoot( wxT(" : ") + wxString(_("Project") ), 0 );
    }
    LoadTemplates();
}

void wxFBResource::LoadTemplates()
{
    if ( !Load( wxFB_WND ) ) return;
    if ( !Load( wxFB_WND_TOPLEVEL ) ) return;

    if ( m_objInsp )
    {
        wxPropertyGridManager *pgp = wxDynamicCast( LoadObject( m_objInsp, wxT("WindowProperties"), wxT("wxPropertyGridManager") ), wxPropertyGridManager );

        if ( pgp )
        {
            m_objInsp->RemovePage( 0 );
            m_objInsp->InsertPage( 0, pgp, _("Properties"), true, 0 );
        }

        wxPropertyGridManager *pge = wxDynamicCast( LoadObject( m_objInsp, wxT("WindowEvents"), wxT("wxPropertyGridManager") ), wxPropertyGridManager );
        wxPropertyGridManager *pgt = wxDynamicCast( LoadObject( m_objInsp, wxT("TopLevelWindowEvents"), wxT("wxPropertyGridManager") ), wxPropertyGridManager );

        if ( pge && pgt )
        {
            wxPGVIterator       it;
            wxPropertyCategory *main = NULL;

            for ( it = pge->GetVIterator( wxPG_ITERATE_ALL ); !it.AtEnd(); it.Next() )
            {
                wxPGProperty *p            = it.GetProperty();
                wxPropertyCategory *evtCat = wxDynamicCast( p, wxPropertyCategory );

                if ( evtCat )
                {
                    if ( main )
                    {
                        main->AppendChild( new wxPropertyCategory( p->GetLabel() ) );
                    }
                    else
                    {
                        main = new wxPropertyCategory( evtCat->GetLabel() );
                        pgt->Append( main );
                    }
                }
                else
                {
                    wxStringProperty *evtProp = wxDynamicCast( p, wxStringProperty );
                    pgt->Append( new wxStringProperty( evtProp->GetLabel(), wxPG_LABEL, evtProp->GetValueAsString() ) );
                    evtProp->SetHelpString( p->GetHelpString() );
                }
            }

            m_objInsp->RemovePage( 1 );
            m_objInsp->InsertPage( 1, pgt, _("Events"), false, 1 );
        }
    }
}

void wxFBResource::LoadPlugins()
{
    // Open plugins directory for iteration
    if ( !wxDirExists( wxFB_PLUGINS_DIR ) )
    {
        wxString msg = _("Plugins directory") + wxT(" ") + wxFB_PLUGINS_DIR + wxT(" ") + _("doesn't exists!");
        wxMessageBox( msg, wxT("wxFormBuilder"), wxOK | wxICON_EXCLAMATION, NULL );
        return;
    }

    wxDir pluginsDir( wxFB_PLUGINS_DIR );
    if ( !pluginsDir.IsOpened() ) return;

    // Plugin directory (e.g.'forms')
    wxString pluginDirName;
    int      iconIndex       = -1;
    bool     moreDirectories = pluginsDir.GetFirst( &pluginDirName, wxEmptyString, wxDIR_DIRS | wxDIR_HIDDEN );

    // Iterate through plugin directories and load the package, validating each control found
    while ( moreDirectories )
    {
        // Plugin path (e.g. 'path/to/xrc/plugins/forms')
        wxString nextPluginPath = wxFB_PLUGINS_DIR + pluginDirName;

        // XRC icons directory (e.g. 'path/to/xrc/plugins/forms/icons')
        wxString nextPluginIconPath = nextPluginPath + wxFILE_SEP_PATH + wxT("icons");

        // Be sure all required directories exists
        if ( wxDirExists( nextPluginIconPath ) )
        {
            wxDir pluginDir( nextPluginPath );
            if ( pluginDir.IsOpened() )
            {
                // Be sure we have a palette imagelist
                wxImageList *imgList = m_objPalette->GetImageList();
                if ( !imgList )
                {
                    imgList = new wxImageList( 16, 16 );
                    m_objPalette->SetImageList( imgList );
                }

                // We can add a page in palette notebook, even if no xrc validated
                wxString   plugBmpPath = nextPluginIconPath + wxFILE_SEP_PATH + pluginDirName + wxT(".png");
                wxString   packageName = pluginDirName.Capitalize();
                wxToolBar *pluginBar   = new wxToolBar( m_objPalette, XRCID( packageName ), wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL );

                // The plugin icon is mandatory...
                if ( wxFileExists( plugBmpPath ) )
                {
                    wxBitmap pluginBmp = wxBitmap( plugBmpPath, wxBITMAP_TYPE_PNG );
                    wxImage  pluginImg = pluginBmp.ConvertToImage().Scale( 16, 16 );

                    iconIndex++;
                    imgList->Add( pluginImg );

                    m_objPalette->AddPage( pluginBar, packageName, false, iconIndex );

                    // XRC file to check (e.g.'frame.xrc')
                    wxString xrcCtrlTemplate;
                    bool     moreXrcFiles = pluginDir.GetFirst( &xrcCtrlTemplate, wxT("*.xrc"),
                                                                    wxDIR_FILES | wxDIR_HIDDEN );
                    // Iterate through .xrc files in the xrc directory
                    while ( moreXrcFiles )
                    {
                        wxFileName nextXrcFile( xrcCtrlTemplate );
                        if ( !nextXrcFile.IsAbsolute() )
                        {
                            nextXrcFile.MakeAbsolute();
                        }

                        // Validate control template and, if ok, add it to the palette
                        if ( CheckCtrlTemplate( nextXrcFile.GetFullPath() ) );
                        {
                            wxString ctrlBmpPath = nextPluginIconPath + wxFILE_SEP_PATH + nextXrcFile.GetName() + wxT(".png");

                            if ( wxFileExists( ctrlBmpPath ) )
                            {
                                wxBitmap ctrlBmp = wxBitmap( ctrlBmpPath, wxBITMAP_TYPE_PNG );
                                wxImage  ctrlImg = ctrlBmp.ConvertToImage().Scale( 22, 22 );

                                // TODO: temporary name
                                wxString label = wxT("wx") + nextXrcFile.GetName().Capitalize();

                                pluginBar->AddTool( XRCID( xrcCtrlTemplate ), label, ctrlImg, wxNullBitmap, wxITEM_NORMAL, label );
                            }
                        }
                        moreXrcFiles = pluginDir.GetNext( &xrcCtrlTemplate );
                    }
                    pluginBar->Realize();
                }
            }
        }

        moreDirectories = pluginsDir.GetNext( &pluginDirName );
    }
}

bool wxFBResource::CheckCtrlTemplate( const wxString& file )
{
//  wxLogDebug( wxT("file path:%s"), file );
//  wxLogDebug( wxT("icon path:%s"), iconPath );
    return true;
}

wxFBResource *wxFBResource::ms_instance = NULL;

wxFBResource *wxFBResource::Get()
{
    if ( !ms_instance )
        ms_instance = new wxFBResource;

    return ms_instance;
}
