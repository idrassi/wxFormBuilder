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
// Generación de código XRC
// Juan Antonio Ortega (jortegalalmolda@gmail.com)

#include "xrccg.h"
#include "utils/typeconv.h"
#include "tinyxml.h"
#include <wx/filename.h>
#include <wx/wfstream.h>
#include <wx/txtstrm.h>

class XrcDocument : public TiXmlDocument {
public:
    XrcDocument() : TiXmlDocument() {};
    void Dump(PCodeWriter cw)
    {
        stringbuf sb;
        ostream os(&sb);
        StreamOut(&os);
        cw->Write(sb.str());
    }
};

TiXmlElement* XrcCodeGenerator::GetElement(const PObjectBase obj)
{
    TiXmlElement *element = new TiXmlElement("object"); 
    element->SetAttribute("class", GetClassName(obj));
    
    // (!) según la especificacion XRC, name contiene el id del objeto y ademas
    //     es opcional
    if (obj->GetProperty("id"))
      element->SetAttribute("name", _STDSTR(obj->GetPropertyAsString(_T("id"))));
      
    for (unsigned int i = 0; i < obj->GetPropertyCount(); i++)
    {
        PProperty prop = obj->GetProperty(i);
        if (IsHidden(prop)) continue;
        TiXmlElement *propElement = new TiXmlElement(prop->GetName());
        LinkValue(prop, propElement);
        element->LinkEndChild(propElement);
    }
    for (unsigned int i = 0; i < obj->GetChildCount(); i++)
    {
        element->LinkEndChild(GetElement(obj->GetChild(i)));
    }
    return element;
}

bool XrcCodeGenerator::IsSupported(const string& className){
    return className == "sizeritem" ||
           className == "wxBoxSizer" ||
           className == "wxStaticBoxSizer" ||
           className == "wxGridSizer" ||
           className == "wxFlexGridSizer" ||
           className == "wxBitmapButton" ||
           className == "wxButton" ||
           className == "wxCalendarCtrl" ||
           className == "wxCheckBox" ||
           className == "wxCheckList" ||
           className == "wxChoice" ||
           className == "wxComboBox" ||
           className == "wxDialog" ||
           className == "wxFrame" ||
           className == "wxGauge" ||
           className == "wxGenericDirCtrl" ||
           className == "wxHtmlWindow" ||
           className == "wxListBox" ||
           className == "wxListCtrl" ||
           className == "wxMenuBar" ||
           className == "wxMenu" ||
           className == "wxMenuItem" ||
           className == "wxNotebook" ||
           className == "notebookpage" ||
           className == "wxPanel" ||
           className == "wxRadioButton" ||
           className == "wxRadioBox" ||
           className == "wxScrollBar" ||
           className == "wxScrolledWindow" ||
           className == "wxSlider" ||
           className == "wxSpinButton" ||
           className == "wxSpinCtrl" ||
           className == "wxStaticBitmap" ||
           className == "wxStaticBox" ||
           className == "wxStaticLine" ||
           className == "wxStaticText" ||
           className == "wxTextCtrl" ||
           className == "wxToolBar" ||
           className == "tool" ||
           className == "separator" ||
           className == "wxTreeCtrl"; 
}

string XrcCodeGenerator::GetClassName(const PObjectBase obj)
{
    string className = obj->GetObjectInfo()->GetClassName();;
    
    if (className == "Panel" || className == "Dialog" || className == "Frame")
        className = "wx" + className;
 
    if (IsSupported(className))
        return className;
    else
        return "unknown";
}

void XrcCodeGenerator::LinkValue(const PProperty prop, TiXmlElement *propElement)
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

void XrcCodeGenerator::LinkFont(const wxFont &font, TiXmlElement *propElement)
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

bool XrcCodeGenerator::IsHidden(const PProperty prop)
{
    PPropertyInfo propInfo = prop->GetPropertyInfo();
    if (propInfo->IsHidden()) return true;
    
    switch (prop->GetType())
    {
        case PT_WXPOINT:
            return prop->GetValueAsPoint() == wxDefaultPosition;
        case PT_WXSIZE:
            return prop->GetValueAsSize() == wxDefaultSize;
        default:
            return prop->GetValue().empty();
    }
}

bool XrcCodeGenerator::GenerateCode(PObjectBase project)
{    
    m_cw->Clear();
    
    XrcDocument *doc = new XrcDocument();
    
    TiXmlElement *element = new TiXmlElement("resource");
    element->SetAttribute("xmlns", "http://www.wxwindows.org/wxxrc");
    element->SetAttribute("version", "2.3.0.1");
    
    for (unsigned int i=0; i<project->GetChildCount(); i++)
        element->LinkEndChild(GetElement(project->GetChild(i)));
    
    doc->LinkEndChild(element);

    //doc->Dump(m_cw); No inserta ni \t ni \n
    string tmpFileName = _STDSTR(wxFileName::CreateTempFileName(_T("wxfb")));    
    doc->SaveFile(tmpFileName);
    delete doc;

    {
        wxString line;
        wxFileInputStream input(_WXSTR(tmpFileName));
        wxTextInputStream text(input);
    
        while (!input.Eof())
            m_cw->WriteLn(_STDSTR(text.ReadLine()));
    }
    ::wxRemoveFile(_WXSTR(tmpFileName));
    
    return true;
}
