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
// Written by José Antonio Hurtado - joseantonio.hurtado@hispalinux.es
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __TYPES__
#define __TYPES__

#include <vector>
#include <string>
#include "wx/wx.h"

using namespace std;

typedef enum
{
  T_ERROR,
  T_PROJECT,
  T_FORM,
  T_INTERFACE,
  T_COMPONENT,
  T_WIDGET,    
  T_SIZER,
  T_SIZERITEM,
  T_SPACER,
  T_BITMAP,
  T_CONTAINER,
  T_NOTEBOOK,    // de momento lo trataremos como un tipo especial
  T_NOTEBOOK_PAGE,
  T_MENUBAR,
  T_MENU,
  T_MENUITEM
} ObjectType;


/**
 * Tipos de propiedades.
 */
typedef enum
{
  PT_ERROR,
  PT_BOOL,
  PT_TEXT,
  PT_INTEGER, 
  PT_BITLIST,
  PT_INTLIST,
  PT_OPTION,
  PT_MACRO,
  PT_WXSTRING,
  PT_WXPOINT,
  PT_WXSIZE,
  PT_WXFONT,
  PT_WXCOLOUR,
  PT_PATH,
  PT_BITMAP
} PropertyType;
/*  
typedef enum
{
  W_NO_WIDGET,
  W_GENERIC,    // para el caso de que nuestro widget no esté incluido
  W_BUTTON,
  W_COMBO_BOX,
  W_TEXT_CTRL,
  W_STATIC_TEXT,
  W_PANEL,
  W_BOX_SIZER,
  W_GRID_SIZER,
  W_FLEX_GRID_SIZER,
  W_CHECK_BOX,
  W_SPACER,
  W_SIZERITEM,
  W_GRID,
  W_STATIC_BITMAP
  //W_PLUGIN
} WidgetType;
*/
/**
 * Lista de enteros.
 */
class IntList
{
  private:
    typedef vector<int> IntVector;
    IntVector m_ints;
    
  public:
   IntList() {};
   IntList(string value);
   
   unsigned int GetSize() { return m_ints.size(); };
   int GetValue(unsigned int idx) { return m_ints[idx]; };
   void Add(int value) { m_ints.push_back(value); };
   void DeleteList();
   void SetList(string str);
   string ToString();
};


#endif // __TYPES__
