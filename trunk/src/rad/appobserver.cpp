///////////////////////////////////////////////////////////////////////////////
//
// wxFormBuilder - A Visual Dialog Editor for wxWidgets.
// Copyright (C) 2005 Jos� Antonio Hurtado
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
// Written by Jos� Antonio Hurtado - joseantonio.hurtado@hispalinux.es
//
///////////////////////////////////////////////////////////////////////////////

#include "appobserver.h"

// !!! Hay un bug !!!!
// Cuando se cierra la aplicaci�n y durante el cierre se llamada a alguna
// funci�n que vaya a realizar una notificaci�n, es posible que alg�n
// observador ya se haya eliminado generando un acceso no v�lido


void DataObservable::AddDataObserver(DataObserver *o)
{
  m_observers.push_back(o);
  o->SetData(this);
}

void DataObservable::RemoveDataObserver(DataObserver *o)
{
  ObserverVector::iterator it = m_observers.begin();

  while (it != m_observers.end() && *it != o)
    it++;
    
  if (it != m_observers.end())
    m_observers.erase(it);
}

void DataObservable::NotifyProjectLoaded()
{
  if (!m_lock)
  {
    m_lock = true;
    ObserverVector::iterator it;
    for (it = m_observers.begin(); it != m_observers.end(); it++)
      (*it)->ProjectLoaded();
    m_lock = false;
  }
}

void DataObservable::NotifyProjectSaved()
{
  if (!m_lock)
  {
    m_lock = true;
    ObserverVector::iterator it;
    for (it = m_observers.begin(); it != m_observers.end(); it++)
      (*it)->ProjectSaved();
    m_lock = false;
  }      
}

void DataObservable::NotifyObjectSelected(PObjectBase obj)
{
  if (!m_lock)
  {
    m_lock = true;
    ObserverVector::iterator it;
    for (it = m_observers.begin(); it != m_observers.end(); it++)
      (*it)->ObjectSelected(obj);
    m_lock = false;
  }
}

void DataObservable::NotifyObjectCreated(PObjectBase obj)
{
  if (!m_lock)
  {
    m_lock = true;
    ObserverVector::iterator it;
    for (it = m_observers.begin(); it != m_observers.end(); it++)
      (*it)->ObjectCreated(obj);
    m_lock = false;
  }
}

void DataObservable::NotifyObjectRemoved(PObjectBase obj)
{
  if (!m_lock)
  {
    m_lock = true;
    ObserverVector::iterator it;
    for (it = m_observers.begin(); it != m_observers.end(); it++)
      (*it)->ObjectRemoved(obj);
    m_lock = false;
  }      
}

void DataObservable::NotifyPropertyModified(PProperty prop)
{
  if (!m_lock)
  {
    m_lock = true;
    ObserverVector::iterator it;
    for (it = m_observers.begin(); it != m_observers.end(); it++)
      (*it)->PropertyModified(prop);
    m_lock = false;
  }
}

void DataObservable::NotifyCodeGeneration()
{
  if (!m_lock)
  {
    m_lock = true;
    ObserverVector::iterator it;
    for (it = m_observers.begin(); it != m_observers.end(); it++)
      (*it)->CodeGeneration();
    m_lock = false;
  }
}

void DataObservable::NotifyProjectRefresh()
{
  if (!m_lock)
  {
    m_lock = true;
    ObserverVector::iterator it;
    for (it = m_observers.begin(); it != m_observers.end(); it++)
      (*it)->ProjectRefresh();
    m_lock = false;
  }
}
