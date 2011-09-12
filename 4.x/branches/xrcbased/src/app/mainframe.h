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
 * @date    2011/09/07
 * @version 0.0.1
 */
#ifndef __WXFB_MAINFRAME_H__
#define __WXFB_MAINFRAME_H__

#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/splitter.h>

//#include <wx/propgrid/propgrid.h>

class MainFrame : public wxFrame
{
public:
    MainFrame( wxWindow *parent = ( wxWindow * )NULL );

private:
    // Used to correctly restore splitter position
    void OnAbout( wxCommandEvent& );
    void OnExit( wxCommandEvent& );
    void OnClose( wxCloseEvent& );
    void OnIdle( wxIdleEvent& );
//  void OnSplitterChanged( wxSplitterEvent &event );

    wxMenuBar        *m_menuBar;
/*
    wxPropertyGrid *m_pg;
    wxPropertyGrid *m_eg;
*/
    wxSplitterWindow *m_leftSplitter;
    wxSplitterWindow *m_rightSplitter;
    int               m_leftSplitterWidth;
    int               m_rightSplitterWidth;
};

#endif //__WXFB_MAINFRAME_H__
