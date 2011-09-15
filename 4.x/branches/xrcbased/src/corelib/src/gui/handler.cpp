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
 * @file    handler.cpp
 * @author  Andrea Zanellato (zanellato.andrea@gmail.com)
 * @date    2011/09/13
 * @version 0.0.1
 */
#include "gui/handler.h"
#include "manager.h"

#include <wx/dialog.h>
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

void wxFBFrameHandler::OnClose( wxCloseEvent & )
{
    m_frame->Destroy(); //TODO
}

void wxFBFrameHandler::OnIdle( wxIdleEvent & )
{
    m_leftSplitter->SetSashPosition( 150 );
    m_rightSplitter->SetSashPosition( 330 );

    m_frame->Disconnect( wxEVT_IDLE, wxIdleEventHandler( wxFBFrameHandler::OnIdle ), NULL, this );
}

void wxFBFrameHandler::OnNewProject( wxCommandEvent & )
{
    wxFBResource::Get()->NewProject(); //TODO
}
