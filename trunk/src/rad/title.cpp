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

#include "title.h"
/*
BEGIN_EVENT_TABLE(Title,wxPanel)
//  EVT_
END_EVENT_TABLE()
  */
Title::Title(wxWindow *parent,const wxString &title) : wxPanel(parent,-1)
{
  wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
  
  wxStaticText *text = new wxStaticText(this,-1,title);//,wxDefaultPosition,wxDefaultSize,wxSIMPLE_BORDER);
  SetBackgroundColour(wxColour(100,100,100));
  text->SetBackgroundColour(wxColour(100,100,100));
  text->SetForegroundColour(*wxWHITE);
  text->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, 0, wxT("")));

  sizer->Add(text,0,0,0);
  SetSizer(sizer);
  Fit();
}

