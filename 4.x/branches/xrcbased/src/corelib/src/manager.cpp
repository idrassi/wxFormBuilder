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

#include <wx/image.h>
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
            paltPanel->GetSizer()->Add( paltBook, 1, wxEXPAND );
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

/*
    wxXmlDocument defPrj;
    if ( !defPrj.Load( wxFB_DEFAULT_PROJECT ) ) return;

    if ( m_objInsp && m_pgProps )
    {
        wxPropertyGridPage *page = m_pgProps->GetPage( 0 );
        if ( page )
        {
            LoadObject( m_objInsp, wxT("Project"), wxT("wxPropertyCategory") )
            wxPropertyCategory *cat = wxDynamicCast( LoadObject( m_pgProps, wxT("Project"), wxT("wxPropertyCategory") ), wxPropertyCategory );
            if ( cat )
            {
                m_pgXrcHandler->InitPopulator();
                m_pgXrcHandler->PopulatePage( m_pgProps->GetState() );
                m_pgXrcHandler->DonePopulator();
            }
        }
    }

//---------------------------------------------------------------------------------------------
            wxXmlNode *propNode = defPrj.GetRoot()->GetChildren();

            wxString propClass, propLabel, propName, propValue, emptyString, propData;
            wxPGChoices *pChoices = NULL;

            while ( propNode )
            {
                
                name = propNode->GetName();

                if ( name == wxT("property") )
                {
                    propClass = wxXML_GetAttribute( propNode, wxT("class"), emptyString );

                    wxXmlNode *dataNode = propNode->GetChildren();
                    propData = propNode->GetName();

                    while ( dataNode )
                    {
                        if ( propData == wxT("label") )
                        {
                            propValue = dataNode->GetContent();
                        }
                        else if ( propData == wxT("name") )
                        {
                            propName = dataNode->GetContent();
                        }
                        else if ( propData == wxT("name") )
                        {
                            propName = dataNode->GetContent();
                        }
                    }

                    wxPGProperty *prop = wxPropertyGridPopulator::Add( propClass, propLabel, propName,
                                                                                  propValue, pChoices );
                    page->Append( prop );
                }

                propNode = propNode->GetNext();
            }
//-----------------------------------------------------------------------------------------------------
    //m_project = wxDynamicCast( LoadObject( NULL, wxT("DefaultProject"), wxT("Project") ), Project );

    wxXmlDocument defPrj, newPrj;
    if ( !defPrj.Load( wxFB_DEFAULT_PROJECT ) ) return;

    newPrj = wxXmlDocument( defPrj );

    wxXmlNode *prjCatNode = newPrj.GetRoot()->GetChildren()->GetChildren();
    newPrj.GetRoot()->GetChildren()->RemoveChild( prjCatNode );
    wxXmlNode *pgPageNode = FindResource( wxT("ObjInspPropsPGMan"), wxT("wxPropertyGridManager"), true )->GetChildren()->GetNext();

    if ( pgPageNode && prjCatNode )
    {
        wxPropertyGridManager *pg = wxDynamicCast( wxWindow::FindWindowById( XRCID("ObjInspPropsPGMan") ), wxPropertyGridManager );

        pgPageNode->InsertChildAfter( prjCatNode, pgPageNode->GetChildren() );

        newPrj.SetRoot( pgPageNode );
        newPrj.Save( wxFB_XRC_DIR + wxFILE_SEP_PATH + wxT("test.xrc") );
    }
*/
}

wxFBResource *wxFBResource::ms_instance = NULL;

wxFBResource *wxFBResource::Get()
{
    if ( !ms_instance )
        ms_instance = new wxFBResource;

    return ms_instance;
}
