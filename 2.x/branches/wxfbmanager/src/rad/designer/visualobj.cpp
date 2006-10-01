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

#include "visualobj.h"
#include "visualeditor.h"

#include "utils/typeconv.h"
#include "utils/debug.h"
#include "rad/genericpanel.h"

#include <wx/wxFlatNotebook/wxFlatNotebook.h>
#include <wx/notebook.h>
#include <wx/listbook.h>
#include <wx/choicebk.h>
#include <wx/wxscintilla.h>

#include <rad/appdata.h>

using namespace TypeConv;

///////////////////////////////////////////////////////////////////////////////

BEGIN_EVENT_TABLE( VObjEvtHandler, wxEvtHandler )
	EVT_LEFT_DOWN( VObjEvtHandler::OnLeftClick )
	EVT_PAINT( VObjEvtHandler::OnPaint )
	EVT_SET_CURSOR( VObjEvtHandler::OnSetCursor )
END_EVENT_TABLE()

VObjEvtHandler::VObjEvtHandler(wxWindow *win, shared_ptr<ObjectBase> obj)
{
	m_window = win;
	m_object = obj;
};

void VObjEvtHandler::OnLeftClick(wxMouseEvent &event)
{
	shared_ptr<ObjectBase> obj = m_object.lock();

	if (obj)
	{
		if (AppData()->GetSelectedObject() != obj)
			AppData()->SelectObject(obj);
		//else
		//	event.Skip();
	}


	event.Skip();
	m_window->ClientToScreen(&event.m_x, &event.m_y);
	m_window->GetParent()->ScreenToClient(&event.m_x, &event.m_y);
	::wxPostEvent(m_window->GetParent(), event);
}


void VObjEvtHandler::OnPaint(wxPaintEvent &event)
{
	shared_ptr<ObjectBase> wo = shared_dynamic_cast<ObjectBase>(m_object.lock());
	if (wo->IsContainer())
	{
		wxWindow *aux = m_window;
		while (!aux->IsKindOf(CLASSINFO(GridPanel))) aux = aux->GetParent();
		GridPanel *gp = (GridPanel*) aux;
		if (gp->GetActivePanel() == m_window)
		{
			wxPaintDC dc(m_window);
			gp->HighlightSelection(dc);
		}
	}
	event.Skip();
}

void VObjEvtHandler::OnSetCursor(wxSetCursorEvent &event)
{
	wxCoord x = event.GetX(), y = event.GetY();
	m_window->ClientToScreen(&x, &y);
	m_window->GetParent()->ScreenToClient(&x, &y);
	wxSetCursorEvent sce(x, y);
	::wxPostEvent(m_window->GetParent(), sce);
}

//////////////////////////////////////
// Object Tree for notebook objects:
//
//  notebook
//      |
//    notebookpage (item)
//          |
//       container
//////////////////////////////////////

void VObjEvtHandler::OnNotebookPageChanged(wxNotebookEvent &event)
{
	//OnBookPageChanged( shared_ptr<ObjectBase>(m_object), event.GetSelection() );
	//event.Skip();
}
void VObjEvtHandler::OnFlatNotebookPageChanged(wxFlatNotebookEvent &event)
{
	OnBookPageChanged( shared_ptr<ObjectBase>(m_object), event.GetSelection() );
	event.Skip();
}
void VObjEvtHandler::OnListbookPageChanged(wxListbookEvent &event)
{
	OnBookPageChanged( shared_ptr<ObjectBase>(m_object), event.GetSelection() );
	event.Skip();
}

void VObjEvtHandler::OnChoicebookPageChanged( wxChoicebookEvent& event )
{
	OnBookPageChanged( shared_ptr<ObjectBase>(m_object), event.GetSelection() );
	event.Skip();
}

void VObjEvtHandler::OnBookPageChanged( shared_ptr<ObjectBase> obj, int selPage )
{
	if (selPage >= 0)
	{
		for (unsigned int i=0; i<obj->GetChildCount(); i++)
		{
			shared_ptr<ObjectBase> child = obj->GetChild(i);
			shared_ptr<Property> propSelect = child->GetProperty(wxT("select"));
			if (propSelect)
			{
				// we can't use DataObservable::ModifyProperty because
				// it will regenerate the gui, so these modifications won't be
				// undoable
				if ((int)i == selPage && !propSelect->GetValueAsInteger())
				{
					propSelect->SetValue( wxT("1") );
				}
				else if ((int)i != selPage && propSelect->GetValueAsInteger())
				{
					propSelect->SetValue( wxT("0") );
				}
			}
		}
	}
}

void VObjEvtHandler::OnMarginClick ( wxScintillaEvent& event )
{
	wxScintilla* scintilla = wxDynamicCast( m_window, wxScintilla );
	if ( scintilla != NULL )
	{
		if ( event.GetMargin() == 1 )
		{
			int lineClick = scintilla->LineFromPosition( event.GetPosition() );
			int levelClick = scintilla->GetFoldLevel( lineClick );
			if ( ( levelClick & wxSCI_FOLDLEVELHEADERFLAG ) > 0 )
			{
				scintilla->ToggleFold( lineClick );
			}
		}
	}
	event.Skip();
}
