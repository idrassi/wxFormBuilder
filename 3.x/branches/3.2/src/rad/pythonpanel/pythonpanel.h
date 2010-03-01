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
// Python code generation writen by
//   Michal Bližňak - michal.bliznak@gmail.com
//
///////////////////////////////////////////////////////////////////////////////

/**
@file
@author Michal Bližňák - michal.bliznak@gmail.com
@note
*/

#ifndef __PYTHON_PANEL__
#define __PYTHON_PANEL__

#include <wx/panel.h>
#include <wx/stc/stc.h>
#include "utils/wxfbdefs.h"

class CodeEditor;

class wxFindDialogEvent;

class wxFBEvent;
class wxFBPropertyEvent;
class wxFBObjectEvent;
class wxFBEventHandlerEvent;

class PythonPanel : public wxPanel
{
private:
	CodeEditor* m_pythonPanel;
	PTCCodeWriter m_pythonCW;

	void InitStyledTextCtrl( wxStyledTextCtrl* stc );

public:
	PythonPanel( wxWindow *parent, int id );
	~PythonPanel();

	void OnPropertyModified( wxFBPropertyEvent& event );
	void OnProjectRefresh( wxFBEvent& event );
	void OnCodeGeneration( wxFBEvent& event );
	void OnObjectChange( wxFBObjectEvent& event );
	void OnEventHandlerModified( wxFBEventHandlerEvent& event );

	void OnFind( wxFindDialogEvent& event );

	DECLARE_EVENT_TABLE()
};

#endif //__PYTHON_PANEL__
