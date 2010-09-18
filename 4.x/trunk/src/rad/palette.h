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
 * @file palette.h
 * @author 
 * @date 
 * @brief 
 */
#ifndef __PALETTE__
#define __PALETTE__

#include "model/database.h"
#include "utils/wxfbdefs.h"

#include <wx/vector.h>
#include <wx/aui/aui.h>

/** Defines a wxVector that contains toolbars to show component packages. */
typedef wxVector< wxAuiToolBar* > ToolbarVector;

/** 
 * @class Palette
 * @brief Component packages panel
 */
class Palette : public wxPanel
{
private:
	ToolbarVector 		m_tv; 		/**< Toolbars associated to loaded packages. */
	wxAuiNotebook* 		m_notebook; /**< Notebook used to store toolbar vector. */

	/** Populates components palette toolbar loading specified package. */
	void PopulateToolbar( PObjectPackage pkg, wxAuiToolBar* toolbar );

	DECLARE_EVENT_TABLE()

public:
	/** Constructor. */
	Palette( wxWindow* parent, int id );
	/**
	 * Destructor.
	 * @todo This crashes on exit when notebook have no pages
	 */
	~Palette();

	/** Creates the components palette */
	void Create();

	/** Toolbar's button click event */
	void OnButtonClick( wxCommandEvent &event );
};

#endif //__PALETTE__
