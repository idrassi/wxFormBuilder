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

#include "appobserver.h"
#include "wxfbevent.h"

#include <set>

// !!! Hay un bug !!!!
// Cuando se cierra la aplicación y durante el cierre se llamada a alguna
// función que vaya a realizar una notificación, es posible que algún
// observador ya se haya eliminado generando un acceso no válido

void DataObservable::AddHandler( wxEvtHandler* handler )
{
	m_handlers.push_back( handler );
}

void DataObservable::RemoveHandler( wxEvtHandler* handler )
{
	for ( HandlerVector::iterator it = m_handlers.begin(); it != m_handlers.end(); ++it )
	{
		if ( *it == handler )
		{
			m_handlers.erase( it );
			break;
		}
	}
}

void DataObservable::NotifyEvent( wxFBEvent& event )
{
  static int count = 0;
  static std::set< wxFBEvent* > eventQueue;

  if (count == 0)
  {
	  count++;
	  std::vector< wxEvtHandler* >::iterator handler;
	  for ( handler = m_handlers.begin(); handler != m_handlers.end(); handler++ )
	    (*handler)->ProcessEvent( event );

	  count--;
  }
  else
  {
  	eventQueue.insert( &event );
    wxLogMessage( wxT("Queued event: %s"), event.GetEventName().c_str() );
  }

  // Copy queue
  std::set< wxFBEvent* > queueInProcess = eventQueue;
  eventQueue.clear();

  // Process queue
  std::set< wxFBEvent* >::iterator queuedEvent;
  for ( queuedEvent = queueInProcess.begin(); queuedEvent != queueInProcess.end(); ++queuedEvent )
  {
  	wxFBEvent* temp = *queuedEvent;
	  NotifyEvent( *temp );
  }
}

void DataObservable::NotifyProjectLoaded()
{
  wxFBEvent event( wxEVT_FB_PROJECT_LOADED );
  NotifyEvent( event );
}

void DataObservable::NotifyProjectSaved()
{
  wxFBEvent event( wxEVT_FB_PROJECT_SAVED );
  NotifyEvent( event );
}

void DataObservable::NotifyObjectSelected(shared_ptr<ObjectBase> obj)
{
  wxFBObjectEvent event( wxEVT_FB_OBJECT_SELECTED, obj);
  NotifyEvent( event );
}

void DataObservable::NotifyObjectCreated(shared_ptr<ObjectBase> obj)
{
  wxFBObjectEvent event( wxEVT_FB_OBJECT_CREATED, obj);
  NotifyEvent( event );
}

void DataObservable::NotifyObjectRemoved(shared_ptr<ObjectBase> obj)
{
  wxFBObjectEvent event( wxEVT_FB_OBJECT_REMOVED, obj);
  NotifyEvent( event );
}

void DataObservable::NotifyPropertyModified(shared_ptr<Property> prop)
{
  wxFBPropertyEvent event( wxEVT_FB_PROPERTY_MODIFIED, prop);
  NotifyEvent( event );
}

void DataObservable::NotifyCodeGeneration( bool panelOnly )
{
  wxFBEvent event( wxEVT_FB_CODE_GENERATION );

  // Using the previously unused Id field in the event to carry a boolean
  event.SetId( ( panelOnly ? 1 : 0 ) );

  NotifyEvent( event );
}

void DataObservable::NotifyProjectRefresh()
{
  wxFBEvent event( wxEVT_FB_PROJECT_REFRESH, -1 );
  NotifyEvent( event );
}
