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
 * @file xrcfilter.h
 * @author 
 * @date 
 * @brief 
 */
 
#ifndef __XRCFILTER_H__
#define __XRCFILTER_H__

#include "model/database.h"
#include "utils/wxfbdefs.h"

#include <ticpp.h>

/**
 * @class XrcLoader
 * XRC files import filter.
 */
class XrcLoader
{
private:
	/** @todo Description needed. */
	PObjectDatabase m_objDb;

	/**
	 * @todo Description needed.
	 * @param xrcObj 
	 * @param parent 
	 */
	PObjectBase GetObject(ticpp::Element *xrcObj, PObjectBase parent );

public:
	/**
	 * @todo Description needed.
	 * @param db 
	 */
	void SetObjectDatabase( PObjectDatabase db ) { m_objDb = db; }

	/**
	 * Creates the associated object tree.
	 * @param xrcDoc XML tree in XRC format.
	 */
	PObjectBase GetProject( ticpp::Document* xrcDoc );
};

#endif //__XRCFILTER_H__
