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

#include "model/types.h"
#include <wx/tokenzr.h>
#include "utils/stringutils.h"
#include "utils/debug.h"

IntList::IntList(string value)
{
  SetList(value);
}

void IntList::DeleteList()
{
  m_ints.erase(m_ints.begin(), m_ints.end());
}

void IntList::SetList(string str)
{
  wxString wxstr(str.c_str(),wxConvUTF8);
  DeleteList();
  wxStringTokenizer tkz(wxstr, wxT(","));
  while (tkz.HasMoreTokens())
  {
    long value;
    wxString token;
    token = tkz.GetNextToken();
    token.Trim(true);
    token.Trim(false);
    
    if (token.ToLong(&value))
      Add((int)value);
  }
}

string IntList::ToString()
{
  string result;
  
  for (unsigned int i=0; i< m_ints.size() ; i++)
  {
    result = result + StringUtils::IntToStr(m_ints[i]);
  }
  
  return result;
}
