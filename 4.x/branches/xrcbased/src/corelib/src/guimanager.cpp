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
 * @file    guimanager.cpp
 * @author  Andrea Zanellato (zanellato.andrea@gmail.com)
 * @date    2011/09/07
 * @version 0.0.1
 */
#include "guimanager.h"

#include <wx/xrc/xmlres.h>
#include <wx/propgrid/xh_propgrid.h>

GUIManager::GUIManager()
{
    wxXmlResource::Get()->AddHandler( new wxPropertyGridXmlHandler );

    wxXmlResource::Get()->Load( wxT("./../xrc/about.xrc") );
    wxXmlResource::Get()->Load( wxT("./../xrc/editor.xrc") );
    wxXmlResource::Get()->Load( wxT("./../xrc/toolbar.xrc") );
    wxXmlResource::Get()->Load( wxT("./../xrc/objinsp.xrc") );
    wxXmlResource::Get()->Load( wxT("./../xrc/objtree.xrc") );
    wxXmlResource::Get()->Load( wxT("./../xrc/palette.xrc") );

    m_toolBar    = NULL;
    m_editor     = NULL;
    m_objInsp    = NULL;
    m_objPalette = NULL;
    m_objTree    = NULL;
}

GUIManager::~GUIManager()
{
    
}

wxToolBar *GUIManager::GetToolBar( wxWindow *parent )
{
    if ( !m_toolBar )
        m_toolBar = wxXmlResource::Get()->LoadToolBar( parent, wxT("toolbar") );

    return m_toolBar;
}

wxNotebook *GUIManager::GetEditor( wxWindow *parent )
{
    if ( !m_editor )
        m_editor = wxDynamicCast( wxXmlResource::Get()->LoadObject( parent, wxT("Editor"), wxT("wxNotebook") ), wxNotebook );

    return m_editor;
}

wxNotebook *GUIManager::GetObjectInspector( wxWindow *parent )
{
    if ( !m_objInsp )
        m_objInsp = wxDynamicCast( wxXmlResource::Get()->LoadObject( parent, wxT("ObjectInspector"), wxT("wxNotebook") ), wxNotebook );

    return m_objInsp;
}

wxNotebook *GUIManager::GetObjectPalette( wxWindow *parent )
{
    if ( !m_objPalette )
        m_objPalette = wxDynamicCast( wxXmlResource::Get()->LoadObject( parent, wxT("ObjectPalette"), wxT("wxNotebook") ), wxNotebook );

    return m_objPalette;
}

wxTreeCtrl *GUIManager::GetObjectTree( wxWindow *parent )
{
    if ( !m_objTree )
        m_objTree = wxDynamicCast( wxXmlResource::Get()->LoadObject( parent, wxT("ObjectTree"), wxT("wxTreeCtrl") ), wxTreeCtrl );

    return m_objTree;
}

wxDialog *GUIManager::GetAboutDialog( wxWindow *parent )
{
    wxDialog *dlg = wxXmlResource::Get()->LoadDialog( parent, wxT("about") );

    return dlg;
}
