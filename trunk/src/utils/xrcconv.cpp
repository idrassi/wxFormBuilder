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

#include "xrcconv.h"

#include <string>
#include <sstream>
using namespace std;

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
  LinkText(xrcPropValue, propElement);
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

void ObjectToXrcFilter::AddWindowProperties()
{
  // falta exstyle
  if (!m_obj->IsNull(_("size")))
    AddProperty(_("size"), _("size"), XRC_TYPE_SIZE);
    
  if (!m_obj->IsNull(_("bg")))  
    AddProperty(_("bg"), _("bg"), XRC_TYPE_COLOUR);
  
  if (!m_obj->IsNull(_("fg")))  
    AddProperty(_("fg"), _("fg"), XRC_TYPE_COLOUR);  

  if (!m_obj->IsNull(_("enabled")))
    AddPropertyValue(_("enabled"),_("1"));
  
  if (!m_obj->IsNull(_("focused")))  
    AddPropertyValue(_("focused"),_("0"));
  
  if (!m_obj->IsNull(_("hidden")))
    AddPropertyValue(_("hidden"),_("0"));  
  
  if (!m_obj->IsNull(_("font")))
    AddProperty(_("font"), _("font"), XRC_TYPE_FONT);  
};

///////////////////////////////////////////////////////////////////////////////

XrcToXfbFilter::XrcToXfbFilter(TiXmlElement *obj, const wxString &classname,
                                                  const wxString &objname)
{
  m_xrcObj = obj;
  m_xfbObj = new TiXmlElement("object");
  
  if (obj->Attribute("class"))
    m_xfbObj->SetAttribute("class",obj->Attribute("class"));

  if (objname != wxT(""))
    AddProperty(wxT("name"), objname, XRC_TYPE_TEXT);
}

XrcToXfbFilter::XrcToXfbFilter(TiXmlElement *obj, const wxString &classname)                                             
{
  m_xrcObj = obj;
  m_xfbObj = new TiXmlElement("object");
  
  m_xfbObj->SetAttribute("class",classname.mb_str());
    
  if (obj->Attribute("name"))
  {
    wxString objname(obj->Attribute("name"),wxConvUTF8);
    AddProperty(wxT("name"), objname, XRC_TYPE_TEXT);
  }
}
                                    
XrcToXfbFilter::~XrcToXfbFilter()
{
  delete m_xfbObj;
}


TiXmlElement* XrcToXfbFilter::GetXrcProperty(const wxString &name)
{
  return m_xrcObj->FirstChildElement(name.mb_str());
}
  
void XrcToXfbFilter::AddProperty(const wxString &xrcPropName,
                                 const wxString &xfbPropName,
                                 const int &propType)
{
  TiXmlElement *propElement = new TiXmlElement("property");
  propElement->SetAttribute("name",xfbPropName.mb_str());
  
  switch (propType)
  {
    case XRC_TYPE_SIZE: 
    case XRC_TYPE_POINT:
    case XRC_TYPE_BITLIST:
    case XRC_TYPE_TEXT:
    case XRC_TYPE_BOOL:      
    case XRC_TYPE_INTEGER:
      ImportTextProperty(xrcPropName, propElement);
      break;

    case XRC_TYPE_COLOUR:
      ImportColourProperty(xrcPropName, propElement);
      break;
      
    case XRC_TYPE_FONT:
      ImportFontProperty(xrcPropName, propElement);
      break;
  }
  
  m_xfbObj->LinkEndChild(propElement);
}

void XrcToXfbFilter::AddPropertyValue (const wxString &xfbPropName,
                                       const wxString &xfbPropValue)
{
  TiXmlElement *propElement = new TiXmlElement("property");
  propElement->SetAttribute("name",xfbPropName.mb_str());
  
  TiXmlText *propValue = new TiXmlText(xfbPropValue.mb_str());
  
  propElement->LinkEndChild(propValue);
  m_xfbObj->LinkEndChild(propElement);  
}
                     
TiXmlElement* XrcToXfbFilter::GetXfbObject()
{
  return (m_xfbObj->Clone())->ToElement();
}

//-----------------------------

void XrcToXfbFilter::ImportTextProperty(const wxString &xrcPropName,
                                        TiXmlElement *property)
{
  TiXmlElement *xrcProperty = m_xrcObj->FirstChildElement(xrcPropName.mb_str());
  if (xrcProperty)
  {
    TiXmlNode *textElement = xrcProperty->FirstChild();
    if (textElement && textElement->ToText())
      property->LinkEndChild(textElement->Clone());
  }
}

void XrcToXfbFilter::ImportFontProperty(const wxString &xrcPropName,
                                        TiXmlElement *property)
{
  TiXmlElement *xrcProperty = m_xrcObj->FirstChildElement(xrcPropName.mb_str());
  if (!xrcProperty)
    return;
  
  TiXmlElement *element;
  TiXmlNode *xmlValue;
  wxFont font;
  
  // el tama�o
  element = xrcProperty->FirstChildElement("size");
  if (element)
  {
    wxString size_str;
    xmlValue = element->FirstChild();
    if (xmlValue && xmlValue->ToText())
      size_str = wxString(xmlValue->ToText()->Value(),wxConvUTF8);
      
    long size;
    if (size_str.ToLong(&size))
      font.SetPointSize(size);
  }

  // la familia
  element = xrcProperty->FirstChildElement("family");
  if (element)
  {
    wxString family_str;
    xmlValue = element->FirstChild();
    if (xmlValue && xmlValue->ToText())
      family_str = wxString(xmlValue->ToText()->Value(),wxConvUTF8);
      
    if (family_str == _("decorative"))
      font.SetFamily(wxDECORATIVE);
    else if (family_str == _("roman"))
      font.SetFamily(wxROMAN);
    else if (family_str == _("swiss"))
      font.SetFamily(wxSWISS);
    else if (family_str == _("modern"))
      font.SetFamily(wxMODERN);
    else //if (family_str == "default")
      font.SetFamily(wxDEFAULT);
  }
  
  // el estilo
  element = xrcProperty->FirstChildElement("style");
  if (element)
  {
    wxString style_str;
    xmlValue = element->FirstChild();
    if (xmlValue && xmlValue->ToText())
      style_str = wxString(xmlValue->ToText()->Value(),wxConvUTF8);
      
    if (style_str == _("slant"))
      font.SetStyle(wxSLANT);
    else if (style_str == _("italic"))
      font.SetStyle(wxITALIC);
    else //if (style_str == "normal")
      font.SetStyle(wxNORMAL);
  }    
  
  
  // grosor
  element = xrcProperty->FirstChildElement("weight");
  if (element)
  {
    wxString weight_str;
    xmlValue = element->FirstChild();
    if (xmlValue && xmlValue->ToText())
      weight_str = wxString(xmlValue->ToText()->Value(),wxConvUTF8);
      
    if (weight_str == _("light"))
      font.SetWeight(wxLIGHT);
    else if (weight_str == _("bold"))
      font.SetWeight(wxBOLD);
    else //if (sweight_str == "normal")
      font.SetWeight(wxNORMAL);
  }    
  
  // subrayado
  element = xrcProperty->FirstChildElement("underlined");
  if (element)
  {
    wxString underlined_str;
    xmlValue = element->FirstChild();
    if (xmlValue && xmlValue->ToText())
      underlined_str = wxString(xmlValue->ToText()->Value(),wxConvUTF8);
      
    if (underlined_str == _("1"))
      font.SetUnderlined(TRUE);
    else
      font.SetUnderlined(FALSE);
  }
  
  // tipo de letra
  element = xrcProperty->FirstChildElement("face");
  if (element)
  {
    wxString face;
    xmlValue = element->FirstChild();
    if (xmlValue && xmlValue->ToText())
      face = wxString(xmlValue->ToText()->Value(),wxConvUTF8);
      
    font.SetFaceName(face);
  }
  
  // Ya tenemos el tipo de letra, s�lo nos queda pasarlo a formato wxFB
  wxString font_str =
    wxString::Format(wxT("%s,%d,%d,%d"),font.GetFaceName().c_str(), font.GetStyle(),
                                       font.GetWeight(), font.GetPointSize());
  property->LinkEndChild(new TiXmlText(font_str.mb_str()));
  
}                                        
                                        
void XrcToXfbFilter::ImportColourProperty(const wxString &xrcPropName,
                                        TiXmlElement *property)
{
  TiXmlElement *xrcProperty = m_xrcObj->FirstChildElement(xrcPropName.mb_str());
  if (!xrcProperty)
    return;
  
  TiXmlNode *xmlValue = xrcProperty->FirstChild();
  if (xmlValue && xmlValue->ToText())
  {
    string value = xmlValue->ToText()->Value();
    
    // convertimos el formato "#rrggbb" a "rrr,ggg,bbb"
    string hexColour = "0x" + value.substr(1,2) + " 0x" + value.substr(3,2) +
                       " 0x" + value.substr(5,2);
    istringstream strIn;
    ostringstream strOut;
    unsigned int red,green,blue;
    
    strIn.str(hexColour);
    strIn >> hex;
    
    strIn >> red;
    strIn >> green;
    strIn >> blue;
    
    strOut << red << "," << green << "," << blue;
    
    property->LinkEndChild(new TiXmlText(strOut.str()));
  }
}                                        
                                        


void XrcToXfbFilter::AddWindowProperties()
{
  // falta exstyle
  AddProperty(_("size"), _("size"), XRC_TYPE_SIZE);
  AddProperty(_("bg"), _("bg"), XRC_TYPE_COLOUR);
  AddProperty(_("fg"), _("fg"), XRC_TYPE_COLOUR);  
  AddProperty(_("font"), _("font"), XRC_TYPE_FONT);  
};
