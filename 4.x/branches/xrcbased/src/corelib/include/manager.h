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

#define wxFB_XRC_DIR            wxStandardPaths::Get().GetResourcesDir().BeforeLast('/') + wxFILE_SEP_PATH + wxT("wxformbuilder") + wxFILE_SEP_PATH + wxT("xrc") + wxFILE_SEP_PATH

#define wxFB_ABOUT              wxFB_XRC_DIR + wxT("gui/about.xrc")
#define wxFB_DEFAULTS           wxFB_XRC_DIR + wxT("gui/default.xrc")
#define wxFB_DEFAULT_PROJECT    wxFB_XRC_DIR + wxT("gui/project.xrc")
#define wxFB_EDITOR             wxFB_XRC_DIR + wxT("gui/editor.xrc")
#define wxFB_MAINFRAME          wxFB_XRC_DIR + wxT("gui/mainframe.xrc")
#define wxFB_MAINMENU           wxFB_XRC_DIR + wxT("gui/mainmenu.xrc")
#define wxFB_OBJECT_INSPECTOR   wxFB_XRC_DIR + wxT("gui/objinsp.xrc")
#define wxFB_OBJECT_TREE        wxFB_XRC_DIR + wxT("gui/objtree.xrc")
#define wxFB_OBJECT_PALETTE     wxFB_XRC_DIR + wxT("gui/palette.xrc")
#define wxFB_TOOLBAR            wxFB_XRC_DIR + wxT("gui/toolbar.xrc")
#define wxFB_LOGO               wxFB_XRC_DIR + wxT("gui/images/logo.png")

#define wxFB_WND                wxFB_XRC_DIR + wxT("classes/window.xrc")
#define wxFB_WND_TOPLEVEL       wxFB_XRC_DIR + wxT("classes/toplevel.xrc")

#ifdef __WXMSW__
    #define wxFB_PLUGINS_DIR    wxStandardPaths::Get().GetResourcesDir().BeforeLast('/') + wxFILE_SEP_PATH + wxT("xrc/plugins") + wxFILE_SEP_PATH
#else
    #define wxFB_PLUGINS_DIR    wxStandardPaths::Get().GetResourcesDir().BeforeLast('/') + wxFILE_SEP_PATH + wxT("wxformbuilder/xrc/plugins") + wxFILE_SEP_PATH
#endif

#include "defs.h"

#include "handlers/mainframe.h"
#include "handlers/xh_propgrid.h"
#include "handlers/xh_stc.h"

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

class WXDLLIMPEXP_WXFBCORE wxFBResource : public wxXmlResource
{
public:
    // GUI staff
    wxDialog                *GetAboutDialog     ( wxWindow *parent = NULL );
    wxFrame                 *GetMainFrame       ( wxWindow *parent = NULL, bool aui = false );
    wxMenuBar               *GetMainMenu        ( wxWindow *parent = NULL );
    wxNotebook              *GetEditor          ( wxWindow *parent = NULL );
    wxNotebook              *GetObjectInspector ( wxWindow *parent = NULL );
    wxNotebook              *GetObjectPalette   ( wxWindow *parent = NULL );
    wxTreeCtrl              *GetObjectTree      ( wxWindow *parent = NULL );
    wxToolBar               *GetToolBar         ( wxWindow *parent = NULL );

    wxPropertyGridManager   *GetPGManagerProperties()   { return m_pgProps; }
    wxPropertyGridManager   *GetPGManagerEvents()       { return m_pgEvents; }

    wxPropertyGridXmlHandler *GetPGXmlHandler()         { return m_pgXrcHandler; }

    // App stuff
    void NewProject();
    void LoadPlugins();
    void LoadTemplates();
    bool CheckCtrlTemplate( const wxString& file );

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
