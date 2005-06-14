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
#include "model/objectbase.h"
#include "utils/debug.h"
#include "utils/typeconv.h"
#include "wx/tokenzr.h"

// -----------------------------------------------------------------------
// wxSizeProperty
// -----------------------------------------------------------------------

WX_PG_IMPLEMENT_VALUE_TYPE_VOIDP(wxSize,wxSizeProperty,wxSize(0,0))

class wxSizePropertyClass : public wxPGPropertyWithChildren
{
    WX_PG_DECLARE_PROPERTY_CLASS()
public:

    wxSizePropertyClass ( const wxString& label, const wxString& name,
        const wxSize& value );
    virtual ~wxSizePropertyClass ();

    WX_PG_DECLARE_PARENTAL_TYPE_METHODS()
    WX_PG_DECLARE_PARENTAL_METHODS()

protected:
    wxSize                  m_value;
};

WX_PG_IMPLEMENT_PROPERTY_CLASS(wxSizeProperty,wxSize,const wxSize&,TextCtrl)

wxSizePropertyClass::wxSizePropertyClass ( const wxString& label, const wxString& name,
    const wxSize& value) : wxPGPropertyWithChildren(label,name)
{
    wxPG_INIT_REQUIRED_TYPE(wxSize)
    DoSetValue((void*)&value);
    AddChild( wxIntProperty(wxT("Width"),wxPG_LABEL,value.x) );
    AddChild( wxIntProperty(wxT("Height"),wxPG_LABEL,value.y) );
}

wxSizePropertyClass::~wxSizePropertyClass () { }

void wxSizePropertyClass::DoSetValue ( wxPGVariant value )
{
    wxSize* pObj = (wxSize*)wxPGVariantToVoidPtr(value);
    m_value = *pObj;
    RefreshChildren();
}

wxPGVariant wxSizePropertyClass::DoGetValue () const
{
    return wxPGVariant((void*)&m_value);
}

void wxSizePropertyClass::RefreshChildren()
{
    if ( !GetCount() ) return;
    Item(0)->DoSetValue( (long)m_value.x );
    Item(1)->DoSetValue( (long)m_value.y );
}

void wxSizePropertyClass::ChildChanged ( wxPGProperty* p )
{
    switch ( p->GetIndexInParent() )
    {
        case 0: m_value.x = p->DoGetValue().GetLong(); break;
        case 1: m_value.y = p->DoGetValue().GetLong(); break;
    }
}

// -----------------------------------------------------------------------
// wxPointProperty
// -----------------------------------------------------------------------

WX_PG_IMPLEMENT_VALUE_TYPE_VOIDP(wxPoint,wxPointProperty,wxPoint(0,0))

class wxPointPropertyClass : public wxPGPropertyWithChildren
{
    WX_PG_DECLARE_PROPERTY_CLASS()
public:

    wxPointPropertyClass( const wxString& label, const wxString& name,
        const wxPoint& value );
    virtual ~wxPointPropertyClass ();

    WX_PG_DECLARE_PARENTAL_TYPE_METHODS()
    WX_PG_DECLARE_PARENTAL_METHODS()

protected:
    wxPoint                  m_value;
};

WX_PG_IMPLEMENT_PROPERTY_CLASS(wxPointProperty,wxPoint,const wxPoint&,TextCtrl)

wxPointPropertyClass::wxPointPropertyClass ( const wxString& label, const wxString& name,
    const wxPoint& value) : wxPGPropertyWithChildren(label,name)
{
    wxPG_INIT_REQUIRED_TYPE(wxPoint)
    DoSetValue((void*)&value);
    AddChild( wxIntProperty(wxT("X"),wxPG_LABEL,value.x) );
    AddChild( wxIntProperty(wxT("Y"),wxPG_LABEL,value.y) );
}

wxPointPropertyClass::~wxPointPropertyClass () { }

void wxPointPropertyClass::DoSetValue ( wxPGVariant value )
{
    wxPoint* pObj = (wxPoint*)wxPGVariantToVoidPtr(value);
    m_value = *pObj;
    RefreshChildren();
}

wxPGVariant wxPointPropertyClass::DoGetValue () const
{
    return wxPGVariant((void*)&m_value);
}

void wxPointPropertyClass::RefreshChildren()
{
    if ( !GetCount() ) return;
    Item(0)->DoSetValue( m_value.x );
    Item(1)->DoSetValue( m_value.y );
}

void wxPointPropertyClass::ChildChanged ( wxPGProperty* p )
{
    switch ( p->GetIndexInParent() )
    {
        case 0: m_value.x = p->DoGetValue().GetLong(); break;
        case 1: m_value.y = p->DoGetValue().GetLong(); break;
    }
}

// -----------------------------------------------------------------------
// wxMyColourProperty
// -----------------------------------------------------------------------

// Colour labels. Last (before NULL, if any) must be Custom.
static const wxChar* mycolprop_labels[] = {
    wxT("Default"),
    wxT("Black"),
    wxT("Maroon"),
    wxT("Navy"),
    wxT("Purple"),
    wxT("Teal"),
    wxT("Gray"),
    wxT("Green"),
    wxT("Olive"),
    wxT("Brown"),
    wxT("Blue"),
    wxT("Fuchsia"),
    wxT("Red"),
    wxT("Orange"),
    wxT("Silver"),
    wxT("Lime"),
    wxT("Aqua"),
    wxT("Yellow"),
    wxT("White"),
    wxT("Custom"),
    (const wxChar*) NULL
};

// Relevant colour values as unsigned longs.
static unsigned long mycolprop_colours[] = {
    wxPG_COLOUR(255,255,254),
    wxPG_COLOUR(0,0,0),
    wxPG_COLOUR(128,0,0),
    wxPG_COLOUR(0,0,128),
    wxPG_COLOUR(128,0,128),
    wxPG_COLOUR(0,128,128),
    wxPG_COLOUR(128,128,128),
    wxPG_COLOUR(0,128,0),
    wxPG_COLOUR(128,128,0),
    wxPG_COLOUR(166,124,81),
    wxPG_COLOUR(0,0,255),
    wxPG_COLOUR(255,0,255),
    wxPG_COLOUR(255,0,0),
    wxPG_COLOUR(247,148,28),
    wxPG_COLOUR(192,192,192),
    wxPG_COLOUR(0,255,0),
    wxPG_COLOUR(0,255,255),
    wxPG_COLOUR(255,255,0),
    wxPG_COLOUR(255,255,255),
    wxPG_COLOUR(0,0,0)
};


// Implement property class. Third argument is optional values array,
// but in this example we are only interested in creating a shortcut
// for user to access the colour values. Last arg is itemcount, but
// that's not necessary because our label array is NULL-terminated.
WX_PG_IMPLEMENT_CUSTOM_COLOUR_PROPERTY_USES_WXCOLOUR(fbColourProperty,
                                                     mycolprop_labels,
                                                     (long*)NULL,
                                                     mycolprop_colours,
                                                     0)

// -----------------------------------------------------------------------
// ObjectInspector
// -----------------------------------------------------------------------

BEGIN_EVENT_TABLE(ObjectInspector, wxPanel)
    EVT_PG_CHANGED(-1, ObjectInspector::OnPropertyGridChange)
END_EVENT_TABLE()

ObjectInspector::ObjectInspector(wxWindow *parent, int id)
  : wxPanel(parent,id)
{
  m_currentSel = PObjectBase();
  wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
  m_pg = new wxPropertyGrid(this, -1);
  topSizer->Add(m_pg, 1, wxALL | wxEXPAND, 0);
  SetSizer(topSizer);
}

void ObjectInspector::Create(bool force)
{
  PObjectBase sel_obj = GetData()->GetSelectedObject();
  if (sel_obj && (sel_obj != m_currentSel || force))
  {
    Freeze();
    
    m_currentSel = sel_obj;
        
    m_pg->Clear();
    m_propmap.clear();
    
    PObjectInfo obj_desc = sel_obj->GetObjectInfo();
    if (obj_desc)
    {
      
      PropertyMap map, dummy;
      
      // Creamos las categorías con las propiedades del objeto organizados por
      // "clases"
      CreateCategory(wxString(obj_desc->GetClassName().c_str(),wxConvUTF8), sel_obj,obj_desc,map);

      for (unsigned int i=0; i<obj_desc->GetBaseClassCount() ; i++)
      {
        PObjectInfo info_base = obj_desc->GetBaseClass(i);
        CreateCategory(wxString(info_base->GetClassName().c_str(),wxConvUTF8), sel_obj,info_base,map);
      }  

      /*
      // Añadimos la categoría "layout" si el objeto está contenido en un sizer
      PObjectBase layout;
      layout = sel_obj->GetLayout();  
      if (layout)
      {
        Debug::Print("[ObjectInspector::Update] Has layout properties");
        CreateCategory(wxT("Layout"), layout ,layout->GetObjectInfo(),dummy);
      }
      
      // Añadirmos la categoría "Notebook Page" si el objeto está contenido
      // en un Notebook (no me gusta)
      if (sel_obj->GetParent() && sel_obj->GetParent()->GetObjectTypeName()=="notebookpage")
      {
        CreateCategory(wxT("Page"), sel_obj->GetParent(),
          sel_obj->GetParent()->GetObjectInfo(),dummy);
      }
      */
      
      PObjectBase parent = sel_obj->GetParent();
      if (parent && parent->GetObjectInfo()->GetObjectType()->IsItem())
      {
        CreateCategory(_WXSTR(parent->GetObjectInfo()->GetClassName()), parent, parent->GetObjectInfo(),dummy);
      }
      
      // bajo wxGTK no se actualiza adecuadamente
      m_pg->Refresh();
      
    }
    Thaw();
  }
}

int ObjectInspector::StringToBits(const wxString& strVal, wxPGConstants& constants)
{
  wxStringTokenizer strTok(strVal, _T(" |"));
  int val = 0;
  while (strTok.HasMoreTokens())
  {
    wxString token = strTok.GetNextToken();
    unsigned int i = 0;
    bool done = false;
    while (i < constants.GetCount() && !done)
    {
      if (constants.GetLabel(i) == token)
      {
        val |= constants.GetValue(i);
        done = true;
      }
      i++;  
    }
  }
  return val;
}

wxPGProperty* ObjectInspector::GetProperty(PProperty prop)
{
  wxPGProperty *result;
  PropertyType type = prop->GetType();
  wxString name = _WXSTR(prop->GetName());
  
  if (type == PT_TEXT || type == PT_MACRO || type == PT_WXSTRING)
  {
    result = wxStringProperty(name, wxPG_LABEL, prop->GetValueAsString());
    result->SetAttribute(wxPG_BOOL_USE_DOUBLE_CLICK_CYCLING, true);
  }
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
    for (unsigned int i = 0; i < opt_list->GetOptionCount(); i++)
    {
      wxString item(opt_list->GetOption(i).c_str(), wxConvUTF8);
      constants.Add(item, 1 << i);
    }

    int val = StringToBits(prop->GetValueAsString(), constants);
    result = wxFlagsProperty(name, wxPG_LABEL, constants, val);
    /*if (aux != _T("0"))
        result->SetValueFromString(aux, 0);*/
  }
  else if (type == PT_INTLIST)
    result = wxStringProperty(name, wxPG_LABEL, _WXSTR(IntList(_STDSTR(prop->GetValueAsString())).ToString()));

  else if (type == PT_OPTION)
  {
    PPropertyInfo prop_desc = prop->GetPropertyInfo();
    POptionList opt_list = prop_desc->GetOptionList();
  
    assert(opt_list && opt_list->GetOptionCount() > 0);
    
    wxPGConstants constants;
    for (unsigned int i=0; i<opt_list->GetOptionCount() ;i++)
      constants.Add(wxString(opt_list->GetOption(i).c_str(),wxConvUTF8), i);
      
    result = wxEnumProperty(name, wxPG_LABEL, constants);
    result->SetValueFromString(prop->GetValueAsString(), 0);
  }

  else if (type == PT_WXPOINT)
    result = wxPointProperty(name, wxPG_LABEL, prop->GetValueAsPoint());

  else if (type == PT_WXSIZE)
    result = wxSizeProperty(name, wxPG_LABEL, prop->GetValueAsSize());
  
  else if (type == PT_WXFONT)
    result = wxFontProperty(name, wxPG_LABEL, prop->GetValueAsFont());

  else if (type == PT_WXCOLOUR)
  {
    wxColour col = prop->GetValueAsColour();
    if (prop->GetValueAsString() == _T(""))
        result = fbColourProperty(name, wxPG_LABEL, wxColour(255, 255, 254));
    else
        result = fbColourProperty(name, wxPG_LABEL, prop->GetValueAsColour());
  }

  else if (type == PT_PATH)
    result = wxDirProperty(name, wxPG_LABEL, prop->GetValueAsString());
  
  else if (type == PT_BITMAP)
    result = wxImageFileProperty(name, wxPG_LABEL, prop->GetValueAsString());
    
  else if (type == PT_XPM_BITMAP){
    result = wxImageFileProperty(name, wxPG_LABEL, prop->GetValueAsString());
    result->SetAttribute(wxPG_FILE_WILDCARD, _T("XPM files (*.xpm)|*.xpm"));
  }
  else if (type == PT_STRINGLIST)
  {
    result = wxArrayStringProperty(name, wxPG_LABEL,prop->GetValueAsArrayString());    
  }
  else // propiedad desconocida
  {
    result = wxStringProperty(name, wxPG_LABEL, prop->GetValueAsString());
    result->SetAttribute(wxPG_BOOL_USE_DOUBLE_CLICK_CYCLING, true);
    wxLogError(wxT("Property type Unknown"));
  }
    
  return result;
}

void ObjectInspector::CreateCategory(const wxString& name, PObjectBase obj, PObjectInfo obj_info,PropertyMap &map)
{
  m_pg->AppendCategory(name);
  unsigned int prop_count = obj_info->GetPropertyCount();
  
  if (prop_count > 0)
  {
    //wxFlexGridSizer* sizer = new wxFlexGridSizer(prop_count, 2, 0, 0);
    for (unsigned int i=0; i<prop_count ; i++)
    {
      PPropertyInfo prop_desc = obj_info->GetPropertyInfo(i);
      PProperty     prop      = obj->GetProperty(prop_desc->GetName());
      //wxWindow *prop_editor = NULL;
      
      assert(prop_desc && prop);

      wxString prop_name(prop_desc->GetName().c_str(),wxConvUTF8);
      Debug::Print("[ObjectInspector::CreatePropertyPanel] Creating Property Editor");
      
      // no queremos duplicar propiedades heredadas
      if (map.find(prop_desc->GetName()) == map.end())
      {
        wxPGId id = m_pg->Append(GetProperty(prop));
          
        map.insert(PropertyMap::value_type(prop_desc->GetName(),prop));
        m_propmap.insert(ObjInspectorMap::value_type(id.GetPropertyPtr(), prop));
      }  
    }

  }  
                
}  

void ObjectInspector::OnPropertyGridChange(wxPropertyGridEvent& event)
{
    ObjInspectorMap::iterator it = m_propmap.find(event.GetPropertyPtr());

    if (it != m_propmap.end())
    {
        PProperty prop = it->second;
        switch (prop->GetType())
        {
            case PT_TEXT: case PT_MACRO: case PT_WXSTRING: case PT_OPTION:
                GetData()->ModifyProperty(prop, event.GetPropertyValueAsString());
                break;
            case PT_BOOL:
                GetData()->ModifyProperty(prop, event.GetPropertyValueAsBool() ? _T("1") : _T("0"));
                break;
            case PT_BITLIST:
                {
                    wxString aux = event.GetPropertyValueAsString();
                    aux.Replace(_T(" "), _T(""));
                    aux.Replace(_T(","), _T("|"));
                    GetData()->ModifyProperty(prop, aux);
                }
                break;
            case PT_WXPOINT: case PT_WXSIZE:
                {
                    wxString aux = event.GetPropertyValueAsString();
                    aux.Replace(_T(" "), _T(""));
                    aux.Replace(_T(";"), _T(","));
                    GetData()->ModifyProperty(prop, aux);
                }
                break;
            case PT_WXFONT:
                {
                    wxFont *font = wxPGVariantToWxObjectPtr(event.GetPropertyPtr()->DoGetValue(), wxFont);
                    GetData()->ModifyProperty(prop, TypeConv::FontToString(*font));
                }
                break;
            case PT_WXCOLOUR:
                {
                    if (event.GetPropertyValueAsString() == _T("Default"))
                        GetData()->ModifyProperty(prop, _T(""));
                    else
                    {
                        wxColour *colour = wxPGVariantToWxObjectPtr(event.GetPropertyPtr()->DoGetValue(), wxColour);
                        GetData()->ModifyProperty(prop, TypeConv::ColourToString(*colour));
                    }
                }
                break;
            case PT_STRINGLIST:
                {
                  const wxArrayString &arraystr = event.GetPropertyValueAsArrayString();
                  GetData()->ModifyProperty(prop, TypeConv::ArrayStringToString(arraystr));
                }
                break;
            default:
                GetData()->ModifyProperty(prop, event.GetPropertyValueAsString());
        }
    }
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

void ObjectInspector::ProjectRefresh()
{
  Create(true);
}

void ObjectInspector::PropertyModified(PProperty prop)
{
  wxPGId pgid = m_pg->GetPropertyByLabel(_WXSTR(prop->GetName()));
  if (!pgid.IsOk()) return; // Puede que no se esté mostrando ahora esa página
  wxPGProperty *pgProp = pgid.GetPropertyPtr();

  switch (prop->GetType())
  {
    case PT_TEXT: case PT_MACRO: case PT_WXSTRING: case PT_OPTION:
        pgProp->SetValueFromString(prop->GetValueAsString(), 0);
        break;
    case PT_BOOL:
        pgProp->SetValueFromInt(prop->GetValueAsString() == _T("0") ? 0 : 1, 0);
        break;
    case PT_BITLIST:
        {
            wxString aux = prop->GetValueAsString();
            aux.Replace(_T("|"), _T(", "));
            if (aux == _T("0")) aux = _T("");
            pgProp->SetValueFromString(aux, 0);
        }
        break;
    case PT_WXPOINT:
        m_pg->SetPropertyValue(pgid, prop->GetValueAsPoint());
        break;
    case PT_WXSIZE:
        m_pg->SetPropertyValue(pgid, prop->GetValueAsSize());
        break;
    case PT_WXFONT:
        {
            wxFont val = prop->GetValueAsFont();
            pgProp->DoSetValue((void*)&val);
        }
        break;
    case PT_WXCOLOUR:
        if (prop->GetValueAsString() == wxT(""))
            pgProp->SetValueFromString(_T("Default"), 0);
        else{
            wxColour val = prop->GetValueAsColour();
            pgProp->DoSetValue((void*)&val);
        }
        break;
    case PT_STRINGLIST:
      {
        // ????
      }      
      break;
    default:
        pgProp->SetValueFromString(prop->GetValueAsString(), 0);
  }
  m_pg->Refresh();
}
