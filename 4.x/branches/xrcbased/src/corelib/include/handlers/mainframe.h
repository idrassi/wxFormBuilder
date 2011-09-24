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
 * @file    mainframe.h
 * @author  Andrea Zanellato (zanellato.andrea@gmail.com)
 * @date    2011/09/13
 * @version 0.0.1
 */
#ifndef __WXFB_MAINFRAME_H__
#define __WXFB_MAINFRAME_H__

#include <wx/event.h>
#include <wx/frame.h>
#include <wx/splitter.h>

class wxFBFrameHandler
{
public:
    wxFBFrameHandler( wxFrame *owner, wxSplitterWindow *leftSplitter  = NULL,
                                      wxSplitterWindow *rightSplitter = NULL );
    // MainFrame
    void OnClose( wxCloseEvent &event );
    void OnIdle( wxIdleEvent & );

    void SaveLayout();
    bool SaveWarning();

    // MainMenu and ToolBar
    void OnAbout( wxCommandEvent &event );
    void OnExit( wxCommandEvent & );
    void OnNewProject( wxCommandEvent & );

    // ObjectPalette
    void OnToolClicked( wxCommandEvent &event );

private:
    wxFrame          *m_frame;
    wxSplitterWindow *m_leftSplitter, *m_rightSplitter;
};

#endif //__WXFB_MAINFRAME_H__
