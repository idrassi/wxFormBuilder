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

#include "bitmaps.h"
#include "icons/open22.xpm"
#include "icons/save22.xpm"
#include "icons/new22.xpm"
#include "icons/unknown.xpm"



wxBitmap AppBitmaps::GetBitmap(wxString iconname)
{
/*  if (iconname == wxT("wxTextCtrl"))
    return wxBitmap(text_ctrl_xpm);
  else if (iconname == wxT("wxStaticText"))
    return wxBitmap(static_text_xpm);
  else if (iconname == wxT("wxButton"))
    return wxBitmap(button_xpm);
  else if (iconname == wxT("wxPanel") || iconname == wxT("Panel"))
    return wxBitmap(panel_xpm);
  else if (iconname == wxT("wxBoxSizer") || iconname == wxT("wxStaticBoxSizer"))
    return wxBitmap(sizer_xpm);
  else if (iconname == wxT("wxGridSizer") || iconname == wxT("wxFlexGridSizer"))
    return wxBitmap(grid_sizer_xpm);
  else if (iconname == wxT("Frame"))
    return wxBitmap(frame_xpm);
  else if (iconname == wxT("Dialog"))
    return wxBitmap(dialog_xpm);
  else if (iconname == wxT("spacer"))
    return wxBitmap(spacer_xpm);  
  else*/
  if (iconname == wxT("open"))
    return wxBitmap(open_xpm);  
  else if (iconname == wxT("save"))
    return wxBitmap(save_xpm);     
  else if (iconname == wxT("new"))
    return wxBitmap(new_xpm);     

    
  return wxBitmap(unknown_xpm);
}
