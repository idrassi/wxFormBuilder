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
#include "guimanager.h"

#include <wx/dialog.h>
#include <wx/image.h>
#include <wx/notebook.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/treectrl.h>

//#include <wx/propgrid/manager.h>
#include <wx/xrc/xmlres.h>

MainFrame::MainFrame( wxWindow *parent )
{
    // initialize the splitters, wxAUI doesn't use them
    m_leftSplitter = m_rightSplitter = NULL;
//  m_pg = m_eg = NULL;

    // Load XRC GUI resources
    wxXmlResource::Get()->LoadFrame( this, parent, wxT("MainFrame") );
    m_menuBar = wxXmlResource::Get()->LoadMenuBar( this, wxT("MainMenu") );

    wxToolBar *tb = GUIManager::Get()->GetToolBar( this );
    if ( tb ) SetToolBar( tb );

    wxTreeCtrl *objTree  = NULL;
    wxPanel    *pnlHolder = NULL;
    wxNotebook *book;

    pnlHolder = wxDynamicCast( FindWindowById( XRCID("EditorPanel") ), wxPanel );
    if ( pnlHolder )
    {
        book = GUIManager::Get()->GetEditor( pnlHolder );
        if ( book )
        {
            pnlHolder->GetSizer()->Add( book, 1, wxEXPAND );
        }
    }

    pnlHolder = wxDynamicCast( FindWindowById( XRCID("ObjInspPanel") ), wxPanel );
    if ( pnlHolder )
    {
        book = GUIManager::Get()->GetObjectInspector( pnlHolder );
        if ( book )
        {
            pnlHolder->GetSizer()->Add( book, 1, wxEXPAND );
        }
/*
        wxPropertyGridManager *pg = wxDynamicCast( FindWindowById( XRCID("ObjInspPropsPGMan") ), wxPropertyGridManager );
        wxPropertyGridManager *eg = wxDynamicCast( FindWindowById( XRCID("ObjInspEventsPGMan") ), wxPropertyGridManager );
        if ( pg ) m_pg = pg->GetGrid();
        if ( eg ) m_eg = eg->GetGrid();
*/
    }

    pnlHolder = wxDynamicCast( FindWindowById( XRCID("ObjTreePanel") ), wxPanel );
    if ( pnlHolder )
    {
        objTree = GUIManager::Get()->GetObjectTree( pnlHolder );
        if ( objTree )
        {
            pnlHolder->GetSizer()->Add( objTree, 1, wxEXPAND );
        }
    }

    pnlHolder = wxDynamicCast( FindWindowById( XRCID("PalettePanel") ), wxPanel );
    if ( pnlHolder )
    {
        book = GUIManager::Get()->GetObjectPalette( pnlHolder );
        if ( book )
        {
            pnlHolder->GetSizer()->Add( book, 1, wxEXPAND );
        }
    }

    m_leftSplitter  = wxDynamicCast( FindWindowById( XRCID("LeftSplitter") ), wxSplitterWindow );
    m_rightSplitter = wxDynamicCast( FindWindowById( XRCID("RightSplitter") ), wxSplitterWindow );

    // So splitter windows can be restored correctly
    if ( m_leftSplitter && m_rightSplitter )
    {
        m_leftSplitterWidth  = 180;
        m_rightSplitterWidth = 270;
        Connect( wxEVT_IDLE, wxIdleEventHandler( MainFrame::OnIdle ) );
    }

    Connect( XRCID("wxID_ABOUT"), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame::OnAbout ) );
    Connect( XRCID("wxID_EXIT"), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame::OnExit ) );
    Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrame::OnClose ) );
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
/*
    if ( m_pg ) m_pg->FitColumns();
    if ( m_eg ) m_eg->FitColumns();
*/
    Disconnect( wxEVT_IDLE, wxIdleEventHandler( MainFrame::OnIdle ) );
//  m_rightSplitter->Connect( wxEVT_COMMAND_SPLITTER_SASH_POS_CHANGED, wxSplitterEventHandler( MainFrame::OnSplitterChanged ) );
}
/*
void MainFrame::OnSplitterChanged( wxSplitterEvent &event )
{
    
}
*/
void MainFrame::OnAbout( wxCommandEvent &)
{
    wxDialog *dlg = GUIManager::Get()->GetAboutDialog( this );
    if ( dlg )
        dlg->ShowModal();

    dlg->Destroy();
}

void MainFrame::OnExit( wxCommandEvent &)
{
    Close();
}

void MainFrame::OnClose( wxCloseEvent &)
{
    Destroy(); //TODO
}
