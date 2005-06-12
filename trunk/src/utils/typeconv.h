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

////////////
// NOTAS:
// No me gusta nada este módulo, y tampoco, en general, el tratamiento de las
// propiedades como cadenas de caracteres.
// Sería más elegante tratar los valores como objetos TVariant, pero esta
// modificación implica refactorizar el sistema de propiedades.
// de momento se queda como está pero es algo a tener en cuenta para los
// futuros cambios...



#ifndef __TYPE_UTILS__
#define __TYPE_UTILS__

#include "wx/wx.h"
#include <string>
#include <vector>
#include <map>
#include "model/types.h"


using namespace std;

// macros para la conversión entre wxString <-> std::string
#define _WXSTR(x)  TypeConv::_StringToWxString(x) 
#define _STDSTR(x) TypeConv::_WxStringToString(x)

namespace TypeConv
{
  wxString _StringToWxString(const string &str);
  string _WxStringToString(const wxString &str);
  
  wxPoint StringToPoint (const wxString &str);
  bool    StringToPoint(const wxString &str, wxPoint *point);
  wxSize  StringToSize (const wxString &str);
  
  wxString PointToString(const wxPoint &point);
  wxString SizeToString(const wxSize &size);
  
  int     BitlistToInt (const wxString &str);
  int     GetMacroValue(const wxString &str);
  int     StringToInt (const wxString &str);
  
  bool     FlagSet  (const wxString &flag, const wxString &currentValue);
  wxString ClearFlag(const wxString &flag, const wxString &currentValue);
  wxString SetFlag  (const wxString &flag, const wxString &currentValue);
  
  wxBitmap StringToBitmap(const wxString &str);

  wxFont StringToFont (const wxString &str);
  wxString FontToString (const wxFont &font);
  
  wxColour StringToColour(const wxString &str);
  wxString ColourToString(const wxColour &colour);
  
  bool StringToBool(const wxString &str);
  wxString BoolToString(bool val);
  
  wxArrayString StringToArrayString(const wxString &str);
  wxString ArrayStringToString(const wxArrayString &arrayStr);
  
};


// No me gusta nada tener que usar variables globales o singletons
// pero hasta no dar con otro diseño más elegante seguiremos con este...
class MacroDictionary;
typedef MacroDictionary* PMacroDictionary;

class MacroDictionary
{
 private:
  typedef map<string,int> MacroMap;
  static PMacroDictionary s_instance;

  MacroMap m_map;
  
  MacroDictionary(); 
  
 public:
  static PMacroDictionary GetInstance();
  bool SearchMacro(string name, int *result);
  void AddMacro(string name, int value);
};

/**
 * Clase que encapsula el valor de una propiedad.
 *
class TVariant
{
 public:
  // Constructores abiertos
  TVariant(PropertyType type, const string &value);  
  TVariant(PropertyType type, const wxString &value);
  
  // Constructores específicos
  TVariant(const wxFont &font);
  TVariant(const wxColour &colour);
  TVariant(const wxString &wxstring);
  TVariant(const wxPoint &point);
  TVariant(const wxSize &size);
  TVariant(const bool boolean);
  
  wxFont AsFont();
  wxColour AsColour();
  wxPoint AsPoint();
  wxSize AsSize();
  bool AsBool();
  int AsInteger();

  // Efectuan una conversión en caso de no ser un tipo string,
  // este es el formato común a todos, y el que se usará para almacenar
  // el valor en una archivo
  wxString AsString();
  string AsStdString();
  
  // se admite el valor nulo
  bool IsNull();
  
 private:
  PropertyType m_type;
  
  // la representación del valor es siempre una cadena de caracteres
  string m_value;
};
*/

#endif //__TYPE_UTILS__

