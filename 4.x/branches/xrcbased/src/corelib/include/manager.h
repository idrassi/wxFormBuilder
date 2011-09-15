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
 * @file    manager.h
 * @author  Andrea Zanellato (zanellato.andrea@gmail.com)
 * @date    2011/09/07
 * @version 0.0.1
 */
#ifndef __WXFB_RESMANAGER_H__
#define __WXFB_RESMANAGER_H__

#define wxFB_XRC_DIR            wxStandardPaths::Get().GetResourcesDir().BeforeLast('/') + wxFILE_SEP_PATH + wxT("wxformbuilder") + wxFILE_SEP_PATH + wxT("xrc")
#define wxFB_ABOUT              wxFB_XRC_DIR + wxFILE_SEP_PATH + wxT("about.xrc")
#define wxFB_DEFAULTS           wxFB_XRC_DIR + wxFILE_SEP_PATH + wxT("default.xrc")
#define wxFB_DEFAULT_PROJECT    wxFB_XRC_DIR + wxFILE_SEP_PATH + wxT("project.xrc")
#define wxFB_EDITOR             wxFB_XRC_DIR + wxFILE_SEP_PATH + wxT("editor.xrc")
#define wxFB_MAINFRAME          wxFB_XRC_DIR + wxFILE_SEP_PATH + wxT("mainframe.xrc")
#define wxFB_MAINMENU           wxFB_XRC_DIR + wxFILE_SEP_PATH + wxT("mainmenu.xrc")
#define wxFB_OBJECT_INSPECTOR   wxFB_XRC_DIR + wxFILE_SEP_PATH + wxT("objinsp.xrc")
#define wxFB_OBJECT_TREE        wxFB_XRC_DIR + wxFILE_SEP_PATH + wxT("objtree.xrc")
#define wxFB_OBJECT_PALETTE     wxFB_XRC_DIR + wxFILE_SEP_PATH + wxT("palette.xrc")
#define wxFB_TOOLBAR            wxFB_XRC_DIR + wxFILE_SEP_PATH + wxT("toolbar.xrc")
#define wxFB_LOGO               wxFB_XRC_DIR + wxFILE_SEP_PATH + wxT("images/logo.png")

#include "defs.h"
#include "gui/handler.h"
//#include "gui/mainframe.h"

//#include "project.h"

#include <wx/dialog.h>
#include <wx/frame.h>
#include <wx/imaglist.h>
#include <wx/menu.h>
#include <wx/notebook.h>
#include <wx/panel.h>
#include <wx/splitter.h>
#include <wx/toolbar.h>
#include <wx/treectrl.h>
#include <wx/xrc/xmlres.h>

#include <handlers/xh_propgrid.h>
#include <wx/propgrid/manager.h>

class WXDLLIMPEXP_WXFBCORE wxFBResource : public wxXmlResource
{
public:
    wxDialog   *GetAboutDialog( wxWindow *parent = NULL );
    wxFrame    *GetMainFrame( wxWindow *parent = NULL, bool aui = false );
    wxMenuBar  *GetMainMenu( wxWindow *parent = NULL );
    wxNotebook *GetEditor( wxWindow *parent = NULL );
    wxNotebook *GetObjectInspector( wxWindow *parent = NULL );
    wxNotebook *GetObjectPalette( wxWindow *parent = NULL );
    wxTreeCtrl *GetObjectTree( wxWindow *parent = NULL );
    wxToolBar  *GetToolBar( wxWindow *parent = NULL );

    wxPropertyGridManager *GetPGManagerProperties() { return m_pgProps; }
    wxPropertyGridManager *GetPGManagerEvents() { return m_pgEvents; }

    wxPropertyGridXmlHandler *GetPGXmlHandler() { return m_pgXrcHandler; }

    void NewProject();

    static wxFBResource *Get();

protected:
    wxFBResource();
    virtual ~wxFBResource();

private:
//  Project    *m_project;

    wxFrame     *m_frame;
    wxImageList *m_objInspImages;
    wxMenuBar   *m_menuBar;
    wxToolBar   *m_toolBar;
    wxNotebook  *m_editor;
    wxNotebook  *m_objInsp;
    wxNotebook  *m_objPalette;
    wxTreeCtrl  *m_objTree;

    wxPropertyGridXmlHandler *m_pgXrcHandler;

    wxPropertyGridManager *m_pgProps;
    wxPropertyGridManager *m_pgEvents;

    bool m_bUsingAUI;

    wxFBFrameHandler *m_handler;

    static wxFBResource *ms_instance;
};

#endif //__WXFB_RESMANAGER_H__
