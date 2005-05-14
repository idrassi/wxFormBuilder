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
// Generaci�n de c�digo XRC
// Juan Antonio Ortega (jortegalalmolda@gmail.com)

#include "xrccg.h"
#include "utils/typeconv.h"
#include "utils/debug.h"
#include "tinyxml.h"
#include <wx/filename.h>
#include <wx/wfstream.h>
#include <wx/txtstrm.h>

#include "model/xrcfilter.h"
/*
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
};*/


///////////////////////////////////////////////////////////////////////////////
/*
bool XrcCodeGenerator::GenerateCode(PObjectBase project)
{
  m_cw->Clear();

  // CodeWriter no permite la insercci�n de texto con formato (\n y \t),
  // por este motivo no funciona esto
  //
  // doc->Dump(m_cw); No inserta ni \t ni \n
  //
  // La soluci�n que se ha dado es volcarlo a un fichero temporal y luego
  // escribirlo l�nea a l�nea.
  
  XrcFilter xrc;
  TiXmlDocument *doc = xrc.GetXrcDocument(project);

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
*/

bool XrcCodeGenerator::GenerateCode(PObjectBase project)
{
  m_cw->Clear();

  TiXmlDocument *doc = new TiXmlDocument();
  
  TiXmlElement *element = new TiXmlElement("resource");
  element->SetAttribute("xmlns", "http://www.wxwindows.org/wxxrc");
  element->SetAttribute("version", "2.3.0.1");
  /*
  for (unsigned int i=0; i<project->GetChildCount(); i++)
  {
    TiXmlElement *child = GetElement(project->GetChild(i));
    if (child)
      element->LinkEndChild(child);
  }*/
  
  TiXmlElement *child = GetElement(project->GetChild(0));
  if (child)
    element->LinkEndChild(child);
  
  doc->LinkEndChild(element);

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


TiXmlElement* XrcCodeGenerator::GetElement(PObjectBase obj)
{
  TiXmlElement *element = NULL;
  
  IComponent *comp = obj->GetObjectInfo()->GetComponent();  
  if (comp)
    element = comp->ObjectToXrcElement(obj.get());
    
  if (element)
  {
    for (unsigned int i=0; i<obj->GetChildCount(); i++)
      element->LinkEndChild(GetElement(obj->GetChild(i)));
  }
  
  return element;
}

