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

#include "typeconv.h"
#include <wx/tokenzr.h>
#include "utils/stringutils.h"
#include "utils/debug.h"
#include "icons/unknown.xpm"
 
////////////////////////////////////

using namespace TypeConv;

wxString TypeConv::_StringToWxString(const string &str)
{
  wxString newstr(str.c_str(),wxConvUTF8);
  return newstr;
}
  
string TypeConv::_WxStringToString(const wxString &str)
{
  string newstr(str.mb_str());
  return newstr;
}  

bool TypeConv::StringToPoint(const wxString &val, wxPoint *point)
{
  wxPoint result;
  
  bool error = false;
  wxString str_x,str_y;
  long val_x = -1, val_y = -1;

  
  Debug::Print("[wxPointEditor::ParseValue] Parsing value %s",val.c_str());
  
  if (val != wxT(""))
  {
    wxStringTokenizer tkz(val, wxT(","));
    if (tkz.HasMoreTokens())
    {
      str_x = tkz.GetNextToken();
      str_x.Trim(true);
      str_x.Trim(false);
      Debug::Print("[wxPointEditor::ParseValue] Parse %s", str_x.c_str());
      if (tkz.HasMoreTokens())
      {
        str_y = tkz.GetNextToken();
        str_y.Trim(true);
        str_y.Trim(false);
        Debug::Print("[wxPointEditor::ParseValue] Parse %s", str_y.c_str());
      }  
      else
        error = true;
    }
    else
      error = true;

    if (!error)
      error = !str_x.ToLong(&val_x);
  
    if (!error)
      error = !str_y.ToLong(&val_y);
  
    if (!error)
      result = wxPoint(val_x,val_y);
  }
  else 
    result = wxDefaultPosition;

  if (error)
    result = wxDefaultPosition;
    
  point->x = result.x;
  point->y = result.y;
    
  return !error;
}

wxPoint TypeConv::StringToPoint (const wxString &val)
{
  wxPoint result;
  StringToPoint (val,&result);
  return result;
}  

wxSize TypeConv::StringToSize (const wxString &val)
{
  wxPoint point = StringToPoint(val);
  return wxSize(point.x, point.y);
}  

int TypeConv::BitlistToInt (const wxString &str)
{
  int result = 0;
  wxStringTokenizer tkz(str, wxT("|"));
  while (tkz.HasMoreTokens())
  {
    wxString token;
    token = tkz.GetNextToken();
    token.Trim(true);
    token.Trim(false);
    
    result |= GetMacroValue(token);
  }
  
  return result;
}  

wxString TypeConv::PointToString(const wxPoint &point)
{
  wxString value = wxString::Format(wxT("%d,%d"),point.x,point.y);
  return value;
}  

wxString TypeConv::SizeToString(const wxSize &size)
{
  wxString value = wxString::Format(wxT("%d,%d"),size.GetWidth(), size.GetHeight());
  return value;
}

int TypeConv::GetMacroValue(const wxString &str)
{
  int value = 0;
  
  PMacroDictionary dic = MacroDictionary::GetInstance();
  dic->SearchMacro(_STDSTR(str),&value);

  return value;
}  

int TypeConv::StringToInt(const wxString &str)
{
  long l = 0;
  str.ToLong(&l);
  
  return (int)l;
}  




wxFont TypeConv::StringToFont (const wxString &str)
{
  // los tipos de letra tienen el siguiente formato
  // face name, style, weight, point size
  wxStringTokenizer tkz(str,wxT(","));

  wxString face_name;
  int style = wxNORMAL, weight = wxNORMAL, size = 12;

  bool set_face_name, set_style, set_weight, set_size;

  set_face_name = set_style = set_weight = set_size = false;  
  
  if (tkz.HasMoreTokens())
  {
    face_name = tkz.GetNextToken();
    face_name.Trim(true);
    face_name.Trim(false);
    set_face_name = true;
  }

  if (tkz.HasMoreTokens())
  {
    long l_style;
    wxString s_style = tkz.GetNextToken();
    if (s_style.ToLong(&l_style))
    {
      style = (int)l_style;
      set_style = true;
    }
  }

  if (tkz.HasMoreTokens())
  {
    long l_weight;
    wxString s_weight = tkz.GetNextToken();
    if (s_weight.ToLong(&l_weight))
    {
      weight = (int)l_weight;
      set_weight = true;
    }
  }

  if (tkz.HasMoreTokens())
  {
    long l_size;
    wxString s_size = tkz.GetNextToken();
    if (s_size.ToLong(&l_size))
    {
      size = (int)l_size;
      set_size = true;
    }
  }

  wxFont font;

  if (set_face_name)
    font.SetFaceName(face_name);

  if (set_style)  
    font.SetStyle(style);

  if (set_weight)  
    font.SetWeight(weight);

  if (set_size)
    font.SetPointSize(size);

  return font;

}

wxString TypeConv::FontToString (const wxFont &font)
{
  wxString str =
    wxString::Format(wxT("%s,%d,%d,%d"),font.GetFaceName().c_str(), font.GetStyle(),
                                       font.GetWeight(), font.GetPointSize());

  return str;                                                                               
}

wxBitmap TypeConv::StringToBitmap(const wxString &str)
{
  if (::wxFileExists(str))
  {
    wxBitmap bitmap(str,wxBITMAP_TYPE_ANY);
    if (bitmap.Ok())
      return bitmap;
  }

  return wxBitmap(unknown_xpm);
}

wxColour TypeConv::StringToColour(const wxString &str)
{
  wxStringTokenizer tkz(str,wxT(","));
  unsigned char red,green,blue;
  
  red = green = blue = 0;
  
//  bool set_red, set_green, set_blue;
  
//  set_red = set_green = set_blue = false;
  
  if (tkz.HasMoreTokens())
  {
    wxString s_red = tkz.GetNextToken();
    long l_red;
    
    if (s_red.ToLong(&l_red) && (l_red >= 0 && l_red <= 255))
    {
      red = (int)l_red;
//      set_size = true;
    }
  }

  if (tkz.HasMoreTokens())
  {
    wxString s_green = tkz.GetNextToken();
    long l_green;
    
    if (s_green.ToLong(&l_green) && (l_green >= 0 && l_green <= 255))
    {
      green = (int)l_green;
//      set_size = true;
    }
  }

  if (tkz.HasMoreTokens())
  {
    wxString s_blue = tkz.GetNextToken();
    long l_blue;
    
    if (s_blue.ToLong(&l_blue) && (l_blue >= 0 && l_blue <= 255))
    {
      blue = (int)l_blue;
//      set_size = true;
    }
  }
  

  return wxColour(red,green,blue);
}

wxString TypeConv::ColourToString(const wxColour &colour)
{
  return wxString::Format(wxT("%d,%d,%d"),colour.Red(),colour.Green(),colour.Blue());
}

bool TypeConv::StringToBool(const wxString &str)
{
  bool result;
  if (str == wxT("1"))
    result = true;
  else
    result = false;
  return result;
}

wxString TypeConv::BoolToString(bool val)
{
  wxString result;
  
  if (val)
    result = wxT("1");
  else
    result = wxT("0");

  return result;
}

bool TypeConv::FlagSet  (const wxString &flag, const wxString &currentValue)
{
  bool set = false;
  wxStringTokenizer tkz(currentValue, wxT("|"));
  while (!set && tkz.HasMoreTokens())
  {
    wxString token;
    token = tkz.GetNextToken();
    token.Trim(true);
    token.Trim(false);
    
    if (token == flag)
      set = true;
  }
  
  return set;
}

wxString TypeConv::ClearFlag(const wxString &flag, const wxString &currentValue)
{
  wxString result;
  wxStringTokenizer tkz(currentValue, wxT("|"));
  while (tkz.HasMoreTokens())
  {
    wxString token;
    token = tkz.GetNextToken();
    token.Trim(true);
    token.Trim(false);
    
    if (token != flag)
    {
      if (result != wxT(""))
        result = result + wxT('|');
        
      result = result + token;
    }
  }
  
  return result;
}

wxString TypeConv::SetFlag  (const wxString &flag, const wxString &currentValue)
{
  bool found = false;
  wxString result = currentValue;
  wxStringTokenizer tkz(currentValue, wxT("|"));
  while (tkz.HasMoreTokens())
  {
    wxString token;
    token = tkz.GetNextToken();
    token.Trim(true);
    token.Trim(false);
    
    if (token == flag)
      found = true;
  }
  
  if (!found)
  {
    if (result != wxT(""))
      result = result + wxT('|');
        
    result = result + flag;
  }
  return result;
}

// la representación de un array de cadenas será:
// 'string1' 'string2' 'string3'
// el caracter (') se representa dentro de una cadena como ('')
// 'string''1'''
wxArrayString TypeConv::StringToArrayString(const wxString &str)
{
  int i=0, size = str.Length(), state = 0;
  wxArrayString result;
  wxString substr;
  while (i < size)
  {
    wxChar c = str[i];
    switch (state)
    {
      case 0: // esperando (') de comienzo de cadena
        if (c == wxT('\''))
          state = 1;
        break;
      case 1: // guardando cadena
        if (c == wxT('\''))
        {
          if (i+1 < size && str[i+1] == wxT('\''))
          {
            substr = substr + wxT('\'');  // sustitución ('') por (') y seguimos
            i++;
          }
          else
          {
            result.Add(substr); // fin de cadena
            substr.Clear();
            state = 0;
          }
        }
        else
          substr = substr + c; // seguimos guardado la cadena
        
        break;
    }
    i++;
  }
  
  return result;
}

wxString TypeConv::ArrayStringToString(const wxArrayString &arrayStr)
{
  wxString result;
  wxString substr;
  int i, size= arrayStr.Count();
  
  if (size > 0)
    result = wxT('\'') + arrayStr[0] + wxT('\'');
  
  for (i=1 ; i < size ; i++)
    result = result +  wxT(" '") + arrayStr[i] + wxT('\'');
  
  return result;
}

wxString TypeConv::ReplaceSynonymous(const wxString &bitlist)
{
  wxMessageBox("Antes: "+bitlist);
  wxString result;
  string translation;
  wxStringTokenizer tkz(bitlist, wxT("|"));
  while (tkz.HasMoreTokens())
  {
    wxString token;
    token = tkz.GetNextToken();
    token.Trim(true);
    token.Trim(false);
    
    if (result != wxT(""))
        result = result + wxT('|');
    
    if (MacroDictionary::GetInstance()->SearchSynonymous(_STDSTR(token), translation))  
      result += _WXSTR(translation);
    else
      result += token;

  }
  wxMessageBox("Después: "+result);
  return result;
}


///////////////////////////////////////////////////////////////////////////////

PMacroDictionary MacroDictionary::s_instance = NULL;

PMacroDictionary MacroDictionary::GetInstance()
{
  if (!s_instance)
  {
    s_instance = new MacroDictionary();
  }
  
  return s_instance;
}

bool MacroDictionary::SearchMacro(string name, int *result)
{
  bool found = false;
  MacroMap::iterator it = m_map.find(name);
  if (it != m_map.end())
  {
    found = true;
    *result = it->second;
  }
  
  return found;
}

bool MacroDictionary::SearchSynonymous(string synName, string& result)
{
  bool found = false;
  SynMap::iterator it = m_synMap.find(synName);
  if (it != m_synMap.end())
  {
    found = true;
    result = it->second;
  }
  
  return found;
}

#define MACRO(x) m_map.insert(MacroMap::value_type(#x,x))
#define MACRO2(x,y) m_map.insert(MacroMap::value_type(#x,y))

void MacroDictionary::AddMacro(string name, int value)
{
  m_map.insert(MacroMap::value_type(name,value));
}

void MacroDictionary::AddSynonymous(string synName, string name)
{
  m_synMap.insert(SynMap::value_type(synName, name));
}

MacroDictionary::MacroDictionary()
{
  // Las macros serán incluidas en las bibliotecas de componentes... 
  // Sizers macros
}

