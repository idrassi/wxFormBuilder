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
 * @file    guimanager.h
 * @author  Andrea Zanellato (zanellato.andrea@gmail.com)
 * @date    2011/09/07
 * @version 0.0.1
 */
#ifndef __WXFBLIB_GUIMANAGER_H__
#define __WXFBLIB_GUIMANAGER_H__

#include "defs.h"
#include "utils/singleton.h"

#include <wx/dialog.h>
#include <wx/notebook.h>
#include <wx/panel.h>
#include <wx/toolbar.h>
#include <wx/treectrl.h>

class GUIManager : public Singleton< GUIManager >
{
public:
    wxDialog   *GetAboutDialog( wxWindow *parent );
    wxToolBar  *GetToolBar( wxWindow *parent );
    wxNotebook *GetEditor( wxWindow *parent );
    wxNotebook *GetObjectInspector( wxWindow *parent );
    wxNotebook *GetObjectPalette( wxWindow *parent );
    wxTreeCtrl *GetObjectTree( wxWindow *parent );

private:
    GUIManager();
    virtual ~GUIManager();

    wxToolBar  *m_toolBar;
    wxNotebook *m_editor;
    wxNotebook *m_objInsp;
    wxNotebook *m_objPalette;
    wxTreeCtrl *m_objTree;

    friend class Singleton< GUIManager >;
};

#endif //__WXFBLIB_GUIMANAGER_H__
