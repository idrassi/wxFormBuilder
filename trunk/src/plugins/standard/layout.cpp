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

#include "../component.h"
#include "../plugin.h"

#ifdef __WX24__
  #define wxFIXED_MINSIZE wxADJUST_MINSIZE  
#endif

class BoxSizerComponent : public ComponentBase
{
 public:
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    return new wxBoxSizer(obj->GetPropertyAsInteger(_("orient")));
  }
};

class StaticBoxSizerComponent : public ComponentBase
{
 public:
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    wxStaticBox* box = new wxStaticBox((wxWindow *)parent, -1,
      obj->GetPropertyAsString(_("label")));
    
    wxStaticBoxSizer* sizer = new wxStaticBoxSizer(box,
      obj->GetPropertyAsInteger(_("orient")));
     
    return sizer;
  }  
};

class GridSizerComponent : public ComponentBase
{
 public:
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    return new wxGridSizer(
      obj->GetPropertyAsInteger(_("rows")),
      obj->GetPropertyAsInteger(_("cols")),
      obj->GetPropertyAsInteger(_("vgap")),
      obj->GetPropertyAsInteger(_("hgap")));
  }
};

class FlexGridSizerComponent : public ComponentBase
{
 public:
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    wxFlexGridSizer *sizer = new wxFlexGridSizer(
      obj->GetPropertyAsInteger(_("rows")),
      obj->GetPropertyAsInteger(_("cols")),
      obj->GetPropertyAsInteger(_("vgap")),
      obj->GetPropertyAsInteger(_("hgap")));

    wxArrayInt gcols, grows;
    gcols = obj->GetPropertyAsIntegerArray(_("growablecols"));
    grows = obj->GetPropertyAsIntegerArray(_("growablerows"));
   
    unsigned int i;
    for (i=0; i < gcols.GetCount() ; i++)
      sizer->AddGrowableCol(gcols[i]);

    for (i=0; i < grows.GetCount() ; i++)
      sizer->AddGrowableRow(grows[i]);  
  }
};



///////////////////////////////////////////////////////////////////////////////

BEGIN_LIBRARY()
  COMPONENT("wxBoxSizer",BoxSizerComponent)
  COMPONENT("wxStaticBoxSizer",StaticBoxSizerComponent)
  COMPONENT("wxGridSizer",GridSizerComponent)
  COMPONENT("wxFlexGridSizer",FlexGridSizerComponent)

  // wxBoxSizer
  MACRO(wxHORIZONTAL)
  MACRO(wxVERTICAL) 

  // Add
  MACRO(wxALL)
  MACRO(wxLEFT)
  MACRO(wxRIGHT)
  MACRO(wxTOP)
  MACRO(wxBOTTOM)
  MACRO(wxEXPAND)
  MACRO(wxALIGN_BOTTOM)
  MACRO(wxALIGN_CENTER_HORIZONTAL)
  MACRO(wxALIGN_CENTER_VERTICAL)
  MACRO(wxSHAPED)
  MACRO(wxADJUST_MINSIZE)
  MACRO(wxFIXED_MINSIZE)
END_LIBRARY()

