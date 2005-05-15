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

#include "xrcconv.h"

ObjectToXrcFilter::ObjectToXrcFilter(IObject *obj, const wxString &classname,
                                     const wxString &objname,
                                     const wxString &base)
{
  m_obj = obj;
  m_xrcObj = new TiXmlElement("object");
  
  m_xrcObj->SetAttribute("class",classname.mb_str());

  if (objname != wxT(""))
    m_xrcObj->SetAttribute("name",objname.mb_str());

  if (base != wxT(""))
    m_xrcObj->SetAttribute("base",base.mb_str());
}
                                    
ObjectToXrcFilter::~ObjectToXrcFilter()
{
  delete m_xrcObj;
}
  
void ObjectToXrcFilter::AddProperty(const wxString &objPropName,
                                    const wxString &xrcPropName,
                                    const int &propType)
{
  TiXmlElement *propElement = new TiXmlElement(xrcPropName.mb_str());
  
  switch (propType)
  {
    case XRC_TYPE_SIZE: 
    case XRC_TYPE_POINT:
    case XRC_TYPE_BITLIST:
    case XRC_TYPE_TEXT:
      LinkText(m_obj->GetPropertyAsString(objPropName), propElement);
      break;

    case XRC_TYPE_BOOL:      
    case XRC_TYPE_INTEGER:
      LinkInteger(m_obj->GetPropertyAsInteger(objPropName), propElement);
      break;
      
    case XRC_TYPE_COLOUR:
      LinkColour(m_obj->GetPropertyAsColour(objPropName), propElement);
      break;
      
    case XRC_TYPE_FONT:
      LinkFont(m_obj->GetPropertyAsFont(objPropName), propElement);
      break;
  }
  
  m_xrcObj->LinkEndChild(propElement);
}

void ObjectToXrcFilter::AddPropertyValue (const wxString &xrcPropName,
                                          const wxString &xrcPropValue)
{
  TiXmlElement *propElement = new TiXmlElement(xrcPropName.mb_str());
  LinkText(m_obj->GetPropertyAsString(xrcPropName), propElement);
  m_xrcObj->LinkEndChild(propElement);  
}
                     
TiXmlElement* ObjectToXrcFilter::GetXrcObject()
{
  return (m_xrcObj->Clone())->ToElement();
}

void ObjectToXrcFilter::LinkText(const wxString &text,TiXmlElement *propElement)
{
  propElement->LinkEndChild(new TiXmlText(text.mb_str()));
}

void ObjectToXrcFilter::LinkInteger(const int &integer, TiXmlElement *propElement)
{
  wxString text = wxString::Format(wxT("%d"),integer);
  propElement->LinkEndChild(new TiXmlText(text.mb_str()));
}


void ObjectToXrcFilter::LinkColour(const wxColour &colour,
                                   TiXmlElement *propElement)
{
  
  wxString value = wxString::Format(_T("#%02x%02x%02x"),
                     colour.Red(), colour.Green(), colour.Blue());
  
  propElement->LinkEndChild(new TiXmlText(value.mb_str()));  
}

void ObjectToXrcFilter::LinkFont(const wxFont &font, TiXmlElement *propElement)
{
  wxString aux;
  TiXmlElement *element = new TiXmlElement("size");
  aux.Printf(_T("%d"), font.GetPointSize());
  element->LinkEndChild(new TiXmlText(aux.mb_str()));
  propElement->LinkEndChild(element);
  
  element = new TiXmlElement("family");
  switch (font.GetFamily())
  {
      case wxDECORATIVE:
          element->LinkEndChild(new TiXmlText("decorative"));
          break;
      case wxROMAN:
          element->LinkEndChild(new TiXmlText("roman"));
          break;
      case wxSWISS:
          element->LinkEndChild(new TiXmlText("swiss"));
          break;
      case wxMODERN:
          element->LinkEndChild(new TiXmlText("modern"));
          break;
      default:
          element->LinkEndChild(new TiXmlText("default"));
          break;
  }
  propElement->LinkEndChild(element);
  
  element = new TiXmlElement("style");
  switch (font.GetStyle())
  {
      case wxSLANT:
          element->LinkEndChild(new TiXmlText("slant"));
          break;
      case wxITALIC:
          element->LinkEndChild(new TiXmlText("italic"));
          break;
      default:
          element->LinkEndChild(new TiXmlText("normal"));
          break;
  }
  propElement->LinkEndChild(element);
  
  element = new TiXmlElement("weight");
  switch (font.GetWeight())
  {
      case wxLIGHT:
          element->LinkEndChild(new TiXmlText("light"));
          break;
      case wxBOLD:
          element->LinkEndChild(new TiXmlText("bold"));
          break;
      default:
          element->LinkEndChild(new TiXmlText("normal"));
          break;
  }
  propElement->LinkEndChild(element);
  
  element = new TiXmlElement("underlined");
  element->LinkEndChild(new TiXmlText(font.GetUnderlined() ? "1" : "0"));
  propElement->LinkEndChild(element);
  
  element = new TiXmlElement("face");
  element->LinkEndChild(new TiXmlText(font.GetFaceName().mb_str()));
  propElement->LinkEndChild(element);
} 
