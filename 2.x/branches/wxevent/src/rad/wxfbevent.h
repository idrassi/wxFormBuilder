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

#ifndef __WXFBEVENT__
#define __WXFBEVENT__

#include <wx/event.h>

#include "model/objectbase.h"
#include "model/database.h"

DECLARE_EVENT_TYPE( wxEVT_FB_OBJECT_CREATED, -1 )

class wxfbEvent : public wxEvent
{
	public:
		wxfbEvent( wxEventType commandType = wxEVT_NULL );
		virtual ~wxfbEvent();

		shared_ptr< ObjectBase > m_object;
		shared_ptr< Property > m_property;

		// required for sending with wxPostEvent()
		wxEvent* Clone() const;

	protected:
	private:
};

typedef void (wxEvtHandler::*wxfbEventFunction)(wxfbEvent&);

#define EVT_FB_OBJECT_CREATED(fn) \
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_FB_OBJECT_CREATED, -1, -1, \
    (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) (wxNotifyEventFunction) \
    wxStaticCastEvent( wxfbEventFunction, & fn ), (wxObject *) NULL ),

#endif // __WXFBEVENT__
