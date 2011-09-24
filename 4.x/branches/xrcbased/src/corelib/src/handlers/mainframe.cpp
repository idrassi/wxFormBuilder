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
    @file    mainframe.cpp
    @author  Andrea Zanellato (zanellato.andrea@gmail.com)
    @date    2011/09/13
    @version 0.0.1
 */
#include "handlers/mainframe.h"
#include "manager.h"
#include "xrcconfig.h"

#include <wx/dialog.h>
#include <wx/stdpaths.h>
#include <wx/xrc/xmlres.h>

wxFBFrameHandler::wxFBFrameHandler( wxFrame *owner, wxSplitterWindow *leftSplitter, wxSplitterWindow *rightSplitter )
{
    m_frame         = owner;
    m_leftSplitter  = leftSplitter;
    m_rightSplitter = rightSplitter;
}

void wxFBFrameHandler::OnAbout( wxCommandEvent &event )
{
    wxDialog *dlg = wxFBResource::Get()->GetAboutDialog( m_frame );
    if ( dlg )
    {
        dlg->ShowModal();
        dlg->Destroy();
    }
}

void wxFBFrameHandler::OnExit( wxCommandEvent & )
{
    m_frame->Close();
}

void wxFBFrameHandler::OnClose( wxCloseEvent &event )
{
    if ( !SaveWarning() ) return;

    SaveLayout();

    XRCConfig::Get()->Free();

    event.Skip();
}

void wxFBFrameHandler::OnIdle( wxIdleEvent & )
{
    m_leftSplitter->SetSashPosition( 150 );
    m_rightSplitter->SetSashPosition( 330 );

    m_frame->Unbind( wxEVT_IDLE, &wxFBFrameHandler::OnIdle, this );
}

void wxFBFrameHandler::OnNewProject( wxCommandEvent & )
{
    wxFBResource::Get()->NewProject(); //TODO
}

void wxFBFrameHandler::OnToolClicked( wxCommandEvent &event )
{
    wxToolBar *tb = wxDynamicCast( event.GetEventObject(), wxToolBar );

    if ( tb )
    {
        wxWindowID toolId = event.GetId();
        wxString   clsNme = tb->GetToolShortHelp( toolId );
        wxLogDebug( clsNme ); //TODO
    }
}

void wxFBFrameHandler::SaveLayout()
{
    bool       isIconized  = m_frame->IsIconized();
    bool       isMaximized = m_frame->IsMaximized();
    wxString   fileName    = "wxFormBuilder.xrc";
    XRCConfig *xrcConfig   = XRCConfig::Get();

    if ( !wxFileExists( wxStandardPaths::Get().GetUserConfigDir() + wxFILE_SEP_PATH + fileName ) )
    {
        xrcConfig->Initialize();
        if ( !xrcConfig->AddObjectRef("MainFrame", "MainFrameState") ) return;
    }
    else if ( !xrcConfig->Load( fileName ) )
    {
        return;
    }

    if ( !isMaximized && !isIconized )
    {
        xrcConfig->AddProperty("MainFrameState", "pos",  wxString::Format( "%i,%i",
                                m_frame->GetPosition().x, m_frame->GetPosition().y ) );

        xrcConfig->AddProperty("MainFrameState", "size", wxString::Format("%i,%i",
                                m_frame->GetSize().GetWidth(), m_frame->GetSize().GetHeight() ) );
    }

    xrcConfig->AddProperty("MainFrameState", "centered", "0" );
    xrcConfig->AddProperty("MainFrameState", "maximized", isMaximized ? "1" : "0" );
    xrcConfig->AddProperty("MainFrameState", "iconized",  isIconized  ? "1" : "0" );
    xrcConfig->Save( fileName );
}

bool wxFBFrameHandler::SaveWarning()
{
    int result = wxYES;

    // TODO: Check for modified project

    return ( result != wxCANCEL );
}
