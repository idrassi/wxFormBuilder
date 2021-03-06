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
// Written by
//   Jos� Antonio Hurtado - joseantonio.hurtado@gmail.com
//   Juan Antonio Ortega  - jortegalalmolda@gmail.com
//
///////////////////////////////////////////////////////////////////////////////

#include "xrcfilter.h"
#include "utils/typeconv.h"
#include "utils/debug.h"
#include "tinyxml.h"
#include <wx/filename.h>
#include <wx/wfstream.h>
#include <wx/txtstrm.h>
#include <sstream>

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
  TiXmlElement *xrcInfo = GetXrcClassInfo(GetXrcClassName(obj));

  if (xrcInfo)
  {
    element->SetAttribute("class", GetXrcClassName(obj));

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
    string typeName = obj->GetObjectTypeName();
    if ( typeName == "container" || typeName == "widget" || typeName == "form" || typeName == "statusbar")
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
    ///************************************************************************
    else if (!prop && xrcInfo->Attribute("class") == string("spacer") &&
                      attr->Attribute("name")== string("size") )
    {
      // S� que esto duele a la vista, pero no hay otra... el objeto de tipo
      // "spacer" est� especificado de una forma que no concuerda con el resto
      // de objetos.
      // Me refiero a las propiedades width y height, las cuales est�n mapeadas
      // como una propiedad wxSize (llamada "size") en XRC, mientras que en la
      // interfaz wxSizer son dos propiedades de tipo "int" separadas.
      int width = obj->GetPropertyAsInteger(_T("width"));
      int height = obj->GetPropertyAsInteger(_T("height"));

      TiXmlElement *propElement = new TiXmlElement("size");

      string sizeValue = _STDSTR(TypeConv::SizeToString(wxSize(width,height)));
      propElement->LinkEndChild(new TiXmlText(sizeValue));
      element->LinkEndChild(propElement);
    }
    ///************************************************************************

    attr = attr->NextSiblingElement("element");
  }
}
/*
bool XrcFilter::IsSupported(const string& className)
{
  return (GetXrcClassInfo(className) != NULL);
}*/

string XrcFilter::GetXrcClassName(const PObjectBase obj)
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



void XrcFilter::ImportXrcProperty(TiXmlElement *xrcProperty, PProperty property)
{
  if (!xrcProperty)
    return;

  if (property->GetType() == PT_WXCOLOUR)
  {
    ImportColour(xrcProperty, property);
  }
  else if (property->GetType() == PT_WXFONT)
  {
    ImportFont(xrcProperty, property);
  }
  else // es texto equivalente
  {
    TiXmlNode *xmlValue = xrcProperty->FirstChild();
    if (xmlValue && xmlValue->ToText())
    {
      string value = xmlValue->ToText()->Value();
      property->SetValue(value);
    }
  }
}

void XrcFilter::ImportColour(TiXmlElement *xrcProperty, PProperty property)
{
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
    property->SetValue(strOut.str());
  }
}

void XrcFilter::ImportFont(TiXmlElement *xrcProperty, PProperty property)
{
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
      size_str = _WXSTR(xmlValue->ToText()->Value());

    long size;
    if (size_str.ToLong(&size))
      font.SetPointSize(size);
  }

  // la familia
  element = xrcProperty->FirstChildElement("family");
  if (element)
  {
    string family_str;
    xmlValue = element->FirstChild();
    if (xmlValue && xmlValue->ToText())
      family_str = xmlValue->ToText()->Value();

    if (family_str == "decorative")
      font.SetFamily(wxDECORATIVE);
    else if (family_str == "roman")
      font.SetFamily(wxROMAN);
    else if (family_str == "swiss")
      font.SetFamily(wxSWISS);
    else if (family_str == "modern")
      font.SetFamily(wxMODERN);
    else //if (family_str == "default")
      font.SetFamily(wxDEFAULT);
  }

  // el estilo
  element = xrcProperty->FirstChildElement("style");
  if (element)
  {
    string style_str;
    xmlValue = element->FirstChild();
    if (xmlValue && xmlValue->ToText())
      style_str = xmlValue->ToText()->Value();

    if (style_str == "slant")
      font.SetStyle(wxSLANT);
    else if (style_str == "italic")
      font.SetStyle(wxITALIC);
    else //if (style_str == "normal")
      font.SetStyle(wxNORMAL);
  }


  // grosor
  element = xrcProperty->FirstChildElement("weight");
  if (element)
  {
    string weight_str;
    xmlValue = element->FirstChild();
    if (xmlValue && xmlValue->ToText())
      weight_str = xmlValue->ToText()->Value();

    if (weight_str == "light")
      font.SetWeight(wxLIGHT);
    else if (weight_str == "bold")
      font.SetWeight(wxBOLD);
    else //if (sweight_str == "normal")
      font.SetWeight(wxNORMAL);
  }

  // subrayado
  element = xrcProperty->FirstChildElement("underlined");
  if (element)
  {
    string underlined_str;
    xmlValue = element->FirstChild();
    if (xmlValue && xmlValue->ToText())
      underlined_str = xmlValue->ToText()->Value();

    if (underlined_str == "1")
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
      face = _WXSTR(xmlValue->ToText()->Value());

    font.SetFaceName(face);
  }

  property->SetValue(font);
}

void XrcFilter::ImportXrcElements(TiXmlElement *xrcObj, TiXmlElement *xrcInfo,
                                  PObjectBase obj)
{
  TiXmlElement *element = xrcInfo->FirstChildElement("element");
  while (element)
  {
    string propName = ( element->Attribute("property") ?
                        element->Attribute("property") : element->Attribute("name"));

    PProperty property = obj->GetProperty(propName);

    if (property)
      ImportXrcProperty(xrcObj->FirstChildElement(element->Attribute("name")),property);

    else if (!property && xrcInfo->Attribute("class") == string("spacer") &&
                          element->Attribute("name") == string("size"))
    {
      ///***********************************************************************
      // Vale la misma nota que LinkValues :-(
      string str_size;
      TiXmlElement* xrcProperty = xrcObj->FirstChildElement("size");

      assert(xrcProperty);

      TiXmlNode *xmlValue = xrcProperty->FirstChild();
      if (xmlValue && xmlValue->ToText())
      {
        str_size = xmlValue->ToText()->Value();

        PProperty propWidth = obj->GetProperty("width");
        PProperty propHeight = obj->GetProperty("height");
        assert (propWidth && propHeight);

        wxSize size = TypeConv::StringToSize(_WXSTR(str_size));
        propWidth->SetValue(size.GetWidth());
        propHeight->SetValue(size.GetHeight());
      }
      ///***********************************************************************
    }

    element = element->NextSiblingElement("element");
  }
}

void XrcFilter::ImportXrcProperties(TiXmlElement *xrcObj, PObjectBase obj)
{
  assert(xrcObj->Attribute("class"));
  TiXmlElement *xrcInfo = GetXrcClassInfo(xrcObj->Attribute("class"));
  assert(xrcInfo);


  // comenzamos por los atributos
  TiXmlElement *attr = xrcInfo->FirstChildElement("attribute");
  while (attr)
  {
    string propName = ( attr->Attribute("property") ?
                        attr->Attribute("property") : attr->Attribute("name"));

    PProperty property = obj->GetProperty(propName);

    // los atributos siempre son texto
    if (property && xrcObj->Attribute(attr->Attribute("name")))
      property->SetValue(string(xrcObj->Attribute(attr->Attribute("name"))));

    attr = attr->NextSiblingElement("attribute");
  }

  // y seguimos por los sub-elementos
  ImportXrcElements(xrcObj,xrcInfo,obj);

  // si es un widget o un form importamos los subelementos comunes
  string typeName = obj->GetObjectTypeName();
  if ( typeName == "container" || typeName == "widget" || typeName == "form" || typeName == "statusbar")
    ImportXrcElements(xrcObj,GetXrcClassInfo("wxWindow"),obj);
}

PObjectBase XrcFilter::GetObject(TiXmlElement *xrcObj, PObjectBase parent,
                                 bool is_form)
{
  // La estrategia ser� construir el objeto a partir del nombre
  // para posteriormente modificar las propiedades.
  // Con el atributo is_form intentaremos arreglar el problema del conflicto
  // de nombres (wxPanel como form o como widget).

  string className = xrcObj->Attribute("class");

  if (is_form)
  {
    // hay que quitarle el "wx" del principio
    className = className.substr(2,className.size() - 2);
  }

  Debug::Print("[XrcFilter::GetObject] importing %s",className.c_str());

  PObjectBase obj = m_objDb->CreateObject(className,parent);

  if (obj)
  {
    // ahora hay que importar todas las propiedades del objeto xrc
    ImportXrcProperties(xrcObj,obj);

    TiXmlElement *element = xrcObj->FirstChildElement("object");
    while (element)
    {
      PObjectBase child = GetObject(element,obj);
      element = element->NextSiblingElement("object");
    }
  }
  else
    Debug::Print("[XrcFilter::GetObject] Error!! importing %s",className.c_str());
  return obj;
};
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

PObjectBase XrcFilter::GetProject(TiXmlDocument *xrcDoc)
{
  assert(m_objDb);
  Debug::Print("[XrcFilter::GetProject]");

  PObjectBase project(m_objDb->CreateObject("Project"));


  TiXmlElement *root = xrcDoc->FirstChildElement("resource");
  TiXmlElement *element = root->FirstChildElement("object");
  while (element)
  {
    PObjectBase obj = GetObject(element,project,true);
    element = element->NextSiblingElement("object");
  }

  return project;
}


///////////////////////////////////////////////////////////////////////////////

PObjectBase XrcLoader::GetProject(TiXmlDocument *xrcDoc)
{
  assert(m_objDb);
  Debug::Print("[XrcFilter::GetProject]");

  PObjectBase project(m_objDb->CreateObject("Project"));


  TiXmlElement *root = xrcDoc->FirstChildElement("resource");
  TiXmlElement *element = root->FirstChildElement("object");
  while (element)
  {
    PObjectBase obj = GetObject(element,project);
    element = element->NextSiblingElement("object");
  }

  return project;
}

PObjectBase XrcLoader::GetObject(TiXmlElement *xrcObj, PObjectBase parent)
{
  // La estrategia ser� construir el objeto a partir del nombre
  // para posteriormente modificar las propiedades.

  string className = xrcObj->Attribute("class");
  if (parent->GetObjectTypeName() == "project")
  {
    // hay que quitarle el "wx" del principio
    // esto es un apa�o que a�n no se como arreglarlo porque "wxPanel" es llamada
    // como "Panel" para distinguirlo de un "form" y un "container"
    className = className.substr(2,className.size() - 2);
  }

  // Well, this is not nice. wxMenu class name is ambiguous, so we'll get the
  // correct class by the context. If the parent of a wxMenu is another wxMenu
  // then the class name will be "submenu"
  else if (className == "wxMenu" &&
    (parent->GetClassName() == "wxMenu" || parent->GetClassName() == "submenu"))
    className = "submenu";

  PObjectBase object;
  PObjectInfo objInfo = m_objDb->GetObjectInfo(className);
  if (objInfo)
  {
    IComponent *comp = objInfo->GetComponent();
    if (comp)
    {
      TiXmlElement *fbObj = comp->ImportFromXrc(xrcObj);
      if (fbObj)
      {
      	object = m_objDb->CreateObject(fbObj,parent);

      	// Es posible que sea haya creado el objeto, creando un item
        // previamente (ocurren en el caso de wxSplitterWindow). Por tanto,
        // hay que asegurarse de que el objeto apuntado por "object" no sea
        // el item.
      	if (object && object->GetClassName() != className && object->GetChildCount()>0)
      	  object = object->GetChild(0);

        if (object)
        {
          // recursivamente importamos los objetos que est�n por debajo
          TiXmlElement *element = xrcObj->FirstChildElement("object");
          while (element)
          {
            GetObject(element,object);
            element = element->NextSiblingElement("object");
          }
        }
      }
    }
  }
  else
  {
    // es una clase desconocida, vamos a crear un wxPanel porque de lo
    // contrario es muy posible que se produzca un fallo debido a que
    // haya un sizeritem sin objeto incluido �l.
    object = m_objDb->CreateObject("wxPanel",parent);
    if (object)
    {
      parent->AddChild(object);
      object->SetParent(parent);
    }
    else
    {
      wxString msg(wxString::Format(
        wxT("Can't create unknown object (wxPanel) as child of \"%s:%s\""),
        parent->GetPropertyAsString(_T("name")).c_str(), parent->GetClassName().c_str()));

      wxLogError(msg);
    }
  }

  return object;
}
