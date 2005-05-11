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

#include "objinspect2.h"
#include <wx/propgrid/advprops.h>
#include "model/objectbase.h"
#include "utils/debug.h"


ObjectInspector::ObjectInspector(wxWindow *parent, int id)
  : wxPanel(parent,id)
{
  m_currentSel = PObjectBase();
  wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
  m_pg = new wxPropertyGrid(this, -1);
  topSizer->Add(m_pg, 1, wxALL | wxEXPAND, 0);
  SetSizer(topSizer);
}



void ObjectInspector::Create()
{
  PObjectBase sel_obj = GetData()->GetSelectedObject();
  if (sel_obj && sel_obj != m_currentSel)
  {
    #ifdef __WX24__ 
    Freeze();    // No va en wxWidgets 2.5.4
    #endif
    
    m_currentSel = sel_obj;
    
    /*wxString pageName;
    
    if (GetChildren().GetCount() > 0)
      pageName = m_notebook->GetPageText(m_notebook->GetSelection());
   
    DestroyChildren();*/
        
    m_pg->Clear();
    m_map.erase(m_map.begin(),m_map.end());
    
    PObjectInfo obj_desc = sel_obj->GetObjectInfo();
    if (obj_desc)
    {
      #ifndef __WX24__
      Freeze();
      #endif 
      
      PropertyMap map, dummy;
      /*wxBoxSizer *top_sizer = new wxBoxSizer(wxVERTICAL);
      m_notebook = new wxNotebook(this, -1, wxDefaultPosition, wxDefaultSize, 0);*/
      
      // Creamos los panales con las propiedades del objeto organizados por
      // "clases"
      CreateCategory(wxString(obj_desc->GetClassName().c_str(),wxConvUTF8), sel_obj,obj_desc,map);
      //top_sizer->Add(m_notebook, 1, wxEXPAND, 0);

      for (unsigned int i=0; i<obj_desc->GetBaseClassCount() ; i++)
      {
        PObjectInfo info_base = obj_desc->GetBaseClass(i);
        CreateCategory(wxString(info_base->GetClassName().c_str(),wxConvUTF8), sel_obj,info_base,map);
      }  

      // Añadimos el panel "layout" si el objeto está contenido en un sizer
      PObjectBase layout;
      layout = sel_obj->GetLayout();  
      if (layout)
      {
        Debug::Print("[ObjectInspector::Update] Has layout properties");
        CreateCategory(wxT("Layout"), layout ,layout->GetObjectInfo(),dummy);
      }
      
      // Añadirmos el panel "Notebook Page" si el objeto está contenido
      // en un Notebook (no me gusta)
      if (sel_obj->GetParent() && sel_obj->GetParent()->GetObjectType()==T_NOTEBOOK_PAGE)
      {
        CreateCategory(wxT("Page"), sel_obj->GetParent(),
          sel_obj->GetParent()->GetObjectInfo(),dummy);
      }
      
      // vamos a intentar seleccionar la misma página que había seleccionada
      /*if (pageName != wxT("") && GetChildren().GetCount() > 0)
      {
        int page = -1;
        int i=0;

        while (page < 0 && i < m_notebook->GetPageCount())
        {
          if (m_notebook->GetPageText(i) == pageName)
            page = i;
          else 
            i++;
        }
        
        if (page >= 0)
          m_notebook->SetSelection(page);
        
      }*/
        
      #ifndef __WX24__
      Thaw();
      #endif
      //SetSizer(top_sizer);
      //Layout();
    }
    #ifdef __WX24__
    Thaw();
    #endif
  }
}

wxPGProperty* ObjectInspector::GetProperty(PProperty prop)
{
  wxPGProperty *result;
  PropertyType type = prop->GetType();
  wxString name = _WXSTR(prop->GetName());
  
  if (type == PT_TEXT || type == PT_MACRO || type == PT_WXSTRING)
    result = wxStringProperty(name, wxPG_LABEL, prop->GetValueAsString());

  else if (type == PT_BOOL)
  {
    wxString valStr(prop->GetValue().c_str(),wxConvUTF8);
    result = wxBoolProperty(name, wxPG_LABEL, valStr == wxT("1"));
  }  
  else if (type == PT_BITLIST)
  {
    PPropertyInfo prop_desc = prop->GetPropertyInfo();
    POptionList opt_list = prop_desc->GetOptionList();
  
    assert(opt_list && opt_list->GetOptionCount() > 0);
    
    wxPGConstants constants;
    for (unsigned int i=0; i<opt_list->GetOptionCount() ;i++)
      constants.Add(wxString(opt_list->GetOption(i).c_str(),wxConvUTF8), i);
      
    result = wxFlagsProperty(name, wxPG_LABEL, constants);
    
  }
  else if (type == PT_INTLIST)
    result = wxStringProperty(name);

  else if (type == PT_OPTION)
  {
    PPropertyInfo prop_desc = prop->GetPropertyInfo();
    POptionList opt_list = prop_desc->GetOptionList();
  
    assert(opt_list && opt_list->GetOptionCount() > 0);
    
    wxPGConstants constants;
    for (unsigned int i=0; i<opt_list->GetOptionCount() ;i++)
      constants.Add(wxString(opt_list->GetOption(i).c_str(),wxConvUTF8), i);
      
    result = wxEnumProperty(name, wxPG_LABEL, constants);
  }

  else if (type == PT_WXPOINT)
    result = wxStringProperty(name);

  else if (type == PT_WXSIZE)
    result = wxStringProperty(name);
  
  else if (type == PT_WXFONT)
    result = wxStringProperty(name);

  else if (type == PT_WXCOLOUR)
  {
    result = wxColourProperty(name, wxPG_LABEL, prop->GetValueAsColour());
  }
  else if (type == PT_PATH)
    result = wxStringProperty(name);
  
  else if (type == PT_BITMAP)
    result = wxStringProperty(name);
    
  return result;
}

void ObjectInspector::CreateCategory(const wxString& name, PObjectBase obj, PObjectInfo obj_info,PropertyMap &map)
{
  m_pg->AppendCategory(name);
  unsigned int prop_count = obj_info->GetPropertyCount();
  
  if (prop_count > 0)
  {
    wxFlexGridSizer* sizer = new wxFlexGridSizer(prop_count, 2, 0, 0);
    for (unsigned int i=0; i<prop_count ; i++)
    {
      PPropertyInfo prop_desc = obj_info->GetPropertyInfo(i);
      PProperty     prop      = obj->GetProperty(prop_desc->GetName());
      wxWindow *prop_editor = NULL;
      
      assert(prop_desc && prop);

      wxString prop_name(prop_desc->GetName().c_str(),wxConvUTF8);
      Debug::Print("[ObjectInspector::CreatePropertyPanel] Creating Property Editor");
      // no queremos duplicar propiedades heredadas
      if (map.find(prop_desc->GetName()) == map.end())
      {
        //wxStaticText *text = new wxStaticText(panel, -1, prop_name);
        //sizer->Add(text,  0, wxALL|wxADJUST_MINSIZE, 5);

        m_pg->Append(GetProperty(prop));
        
        /*if (prop_editor)
          m_map.insert(ObjInspectorMap::value_type(prop,
                              dynamic_cast<PropertyEditor *>(prop_editor)));*/

        
        /*if (!prop_editor)
          sizer->Add(20,20,0, wxALL| wxEXPAND | wxADJUST_MINSIZE, 5);
        else
          sizer->Add(prop_editor,  0, wxALL| wxEXPAND | wxADJUST_MINSIZE, 5);*/
          
        map.insert(PropertyMap::value_type(prop_desc->GetName(),prop));
      }  
    }
    //sizer->AddGrowableCol(1);
    //panel->SetAutoLayout(true);
    //panel->SetSizer(sizer);
  //        sizer->SetSizeHints(panel);
    //panel->SetScrollRate(10, 10);
    //panel->Fit();
  }  
  //m_notebook->AddPage(panel, name);
                
}  


///////////////////////////////////////////////////////////////////////////////

void ObjectInspector::ProjectLoaded()
{
}

void ObjectInspector::ProjectSaved()
{
}

void ObjectInspector::ObjectSelected(PObjectBase obj)
{
  Create();
}

void ObjectInspector::ObjectCreated(PObjectBase obj)
{
}

void ObjectInspector::ObjectRemoved(PObjectBase obj)
{
}

void ObjectInspector::PropertyModified(PProperty prop)
{
  /*ObjInspectorMap::iterator it = m_map.find(prop);
  
  if (it != m_map.end())
    (it->second)->RetrieveValue();*/
}
