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
// Written by
//   Jos� Antonio Hurtado - joseantonio.hurtado@gmail.com
//   Juan Antonio Ortega  - jortegalalmolda@gmail.com
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __TYPE_UTILS__
#define __TYPE_UTILS__

#include "wx/wx.h"
#include <string>
#include <vector>
#include <map>
#include "model/types.h"


using namespace std;

// macros para la conversi�n entre wxString <-> std::string
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
  
  wxBitmap StringToBitmap(const wxString &filename);

  wxFont StringToFont (const wxString &str);
  wxString FontToString (const wxFont &font);
  
  wxColour StringToColour(const wxString &str);
  wxString ColourToString(const wxColour &colour);
  
  bool StringToBool(const wxString &str);
  wxString BoolToString(bool val);
  
  wxArrayString StringToArrayString(const wxString &str);
  wxString ArrayStringToString(const wxArrayString &arrayStr);
  
  wxString ReplaceSynonymous(const wxString &bitlist);
  
  // Obtiene la ruta absoluta de un archivo
  wxString MakeAbsolutePath(const wxString &filename, const wxString &basePath);
  
  // Obtiene la ruta relativa de un archivo
  wxString MakeRelativePath(const wxString &filename, const wxString &basePath);
};


// No me gusta nada tener que usar variables globales o singletons
// pero hasta no dar con otro dise�o m�s elegante seguiremos con este...
// TO-DO: incluirlo en GlobalApplicationData
class MacroDictionary;
typedef MacroDictionary* PMacroDictionary;

class MacroDictionary
{
 private:
  typedef map<string,int> MacroMap;
  static PMacroDictionary s_instance;
  
  typedef map<string,string> SynMap;

  MacroMap m_map;
  SynMap m_synMap;
  
  MacroDictionary(); 
  
 public:
  static PMacroDictionary GetInstance();
  bool SearchMacro(string name, int *result);
  void AddMacro(string name, int value);
  void AddSynonymous(string synName, string name);
  bool SearchSynonymous(string synName, string& result);
};

#endif //__TYPE_UTILS__

