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

#include "xrcfilter.h"
#include "utils/typeconv.h"
#include "utils/debug.h"
#include "tinyxml.h"
#include <wx/filename.h>
#include <wx/wfstream.h>
#include <wx/txtstrm.h>

TiXmlElement* XrcFilter::GetXrcClassInfo(const string &classname)
{
  TiXmlElement *result = NULL;
  TiXmlElement *root = m_xrcDb.FirstChildElement("xrc");
  if (root)
  {
    result = root->FirstChildElement("object");
    while (result && result->Attribute("class") != classname)
      result = result->NextSiblingElement("object");
  }
  
  return result;
}

TiXmlElement* XrcFilter::GetElement(const PObjectBase obj)
{
  TiXmlElement *element = new TiXmlElement("object"); 
  TiXmlElement *xrcInfo = GetXrcClassInfo(GetClassName(obj));
  
  if (xrcInfo)
  {
    element->SetAttribute("class", GetClassName(obj));

    // enlazamos los atributos
    TiXmlElement *attr = xrcInfo->FirstChildElement("attribute");
    while (attr)
    {
      string attrName = attr->Attribute("name");
      string propName = (attr->Attribute("property") ?
                         attr->Attribute("property") : attrName);
      element->SetAttribute(attrName, _STDSTR(obj->GetPropertyAsString(_WXSTR(propName))));
      attr = attr->NextSiblingElement("attribute");
    }
    
    // enlazamos los sub-elementos

    // FIXME! no todos los objetos xrc heredan de wxWindow...
    if (obj->GetObjectType() == T_WIDGET)
      LinkValues(element,GetXrcClassInfo("wxWindow"),obj);
          
    LinkValues(element,xrcInfo,obj); // los propios del objeto
  }
  else
  {
    // clase no soportada por XRC.
    element->SetAttribute("class", "unknown");
  }
  
  for (unsigned int i = 0; i < obj->GetChildCount(); i++)
      element->LinkEndChild(GetElement(obj->GetChild(i)));

  return element;
}

void XrcFilter::LinkValues(TiXmlElement *element, TiXmlElement *xrcInfo,
  const PObjectBase obj)
{
  TiXmlElement *attr = xrcInfo->FirstChildElement("element");
  while (attr)
  {
    // los subelementos se corresponden con la propiedad cuyo nombre
    // viene dado en el atributo "property" o en su defecto por "name"
    PProperty prop = (attr->Attribute("property")  ?
      obj->GetProperty(attr->Attribute("property")) :
      obj->GetProperty(attr->Attribute("name")));
    
    if (prop && prop->GetValue() != "")
    {  
      TiXmlElement *propElement = new TiXmlElement(attr->Attribute("name"));
      LinkValue(prop,propElement);
      element->LinkEndChild(propElement);
    }
    
    attr = attr->NextSiblingElement("element");
  }
}
/*
bool XrcFilter::IsSupported(const string& className)
{
  return (GetXrcClassInfo(className) != NULL);
}*/

string XrcFilter::GetClassName(const PObjectBase obj)
{
  string className = obj->GetObjectInfo()->GetClassName();
  
  if (className == "Panel" || className == "Dialog" || className == "Frame")
      className = "wx" + className;

  return className;
}

void XrcFilter::LinkValue(const PProperty prop, TiXmlElement *propElement)
{
    wxColour colour;
    string value = prop->GetValue();
    if (prop->GetType() == PT_WXCOLOUR)
    {
        colour = prop->GetValueAsColour();
        value = _STDSTR(wxString::Format(_T("#%02x%02x%02x"), 
            colour.Red(), colour.Green(), colour.Blue()));
    }
    if (prop->GetType() == PT_WXFONT)
        LinkFont(prop->GetValueAsFont(), propElement);    
    else
        propElement->LinkEndChild(new TiXmlText(value));
}

void XrcFilter::LinkFont(const wxFont &font, TiXmlElement *propElement)
{
    wxString aux;
    TiXmlElement *element = new TiXmlElement("size");
    aux.Printf(_T("%d"), font.GetPointSize());
    element->LinkEndChild(new TiXmlText(_STDSTR(aux)));
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
    element->LinkEndChild(new TiXmlText(_STDSTR(font.GetFaceName())));
    propElement->LinkEndChild(element);
}

///////////////////////////////////////////////////////////////////////////////

XrcFilter::XrcFilter()
{
  assert (m_xrcDb.LoadFile("./xml/xrc.xml"));
}

TiXmlDocument *XrcFilter::GetXrcDocument (PObjectBase project)
{
  TiXmlDocument *doc = new TiXmlDocument();
  
  TiXmlElement *element = new TiXmlElement("resource");
  element->SetAttribute("xmlns", "http://www.wxwindows.org/wxxrc");
  element->SetAttribute("version", "2.3.0.1");
  
  for (unsigned int i=0; i<project->GetChildCount(); i++)
      element->LinkEndChild(GetElement(project->GetChild(i)));
  
  doc->LinkEndChild(element);

  return doc;  
}

