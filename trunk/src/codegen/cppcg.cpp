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

#include "cppcg.h"
#include "utils/typeconv.h"
#include <wx/filename.h>

#define FIRST_ID 1000

CppTemplateParser::CppTemplateParser(PObjectBase obj, string _template)
  : TemplateParser(obj,_template)
{
}
string CppTemplateParser::RootWxParentToCode()
{
  return "this";
}

PTemplateParser CppTemplateParser::CreateParser(PObjectBase obj, string _template)
{
  PTemplateParser newparser(new CppTemplateParser(obj,_template));
  return newparser;
}


/**
 * Convierte el valor de una propiedad a c�digo C++.
 */
//string CppTemplateParser::PropertyToCode(PProperty property)
string CppTemplateParser::ValueToCode(PropertyType type, string value)
{
  //PropertyType type = property->GetType();
  //string value = property->GetValue();
  
  string result;
  
  switch (type)
  {
    case PT_WXSTRING:
    // TO-DO's
    // Las cadenas de caracteres (wxString) hay que pasarlas a cadenas tipo "C"
    // "Hola" -> wxT("\"Hola\"")
      result = "wxT(\"" + CppCodeGenerator::ConvertCppString(value) + "\")"; 
      break;
    case PT_MACRO:
    case PT_TEXT:
    case PT_OPTION:
      result = value;
      break;
    case PT_BITLIST:
      if (value == "")
        result = "0";
      else
        result = value;
      break;
    case PT_WXPOINT:
      if (value == "")
        result = "wxDefaultPosition";
      else
        result = "wxPoint(" + value + ")";
      break;
    case PT_WXSIZE:
      if (value == "")
        result = "wxDefaultSize";
      else
        result = "wxSize(" + value + ")";
      break;
    case PT_BOOL:
      if (value == "0")
        result = "false";
      else
        result = "true";
      break;
    case PT_WXFONT:
      if (value != "")
      {
        wxFont font = 
          TypeConv::StringToFont(wxString(value.c_str(),wxConvUTF8));
        
        wxString underlined(wxT("false"));
        if (font.GetUnderlined())
          underlined = wxT("true");
 
        wxString font_str = wxString::Format(wxT("wxFont(%d,%d,%d,%d,%s,wxT(\"%s\"))"),
                             font.GetPointSize(),
                             font.GetFamily(),
                             font.GetStyle(),
                             font.GetWeight(),
                             underlined.c_str(),
                             font.GetFaceName().c_str());
        result = string(font_str.mb_str());
      }
      else
        result = "wxFont()";
      break;  
    case PT_WXCOLOUR:
      if (value != "") 
      {
        wxColour colour = 
          TypeConv::StringToColour(wxString(value.c_str(),wxConvUTF8));
          
        wxString col_str = wxString::Format(wxT("wxColour(%d,%d,%d)"),
                             colour.Red(),colour.Green(),colour.Blue());
        result = string(col_str.mb_str());
        
      }
      else 
          result = "wxColour()";
       
      break;  
      
    case PT_BITMAP:
      result = "wxBitmap(wxT(\"" + CppCodeGenerator::ConvertCppString(value)
                       + "\"), wxBITMAP_TYPE_ANY)";
      break;
      
    case PT_XPM_BITMAP:
      // A diferencia de PT_BITMAP, estos bitmaps se compilan dentro del
      // m�dulo cpp, por lo que el programa ejecutable no requerir� dicho
      // fichero.     
      result = "wxBitmap(" + CppCodeGenerator::ConvertXpmName(value) + ")";
      
      //result = "wxBitmap(wxT(\"" + ConvertCppString(value)
      //                 + "\"), wxBITMAP_TYPE_XPM)";
      break;
    
    case PT_STRINGLIST:
      // las listas de cadenas ser�n generadas como una secuencia de wxString
      // separados por ','.
      {
        wxArrayString array = TypeConv::StringToArrayString(_WXSTR(value));
        if (array.Count() > 0)
          result = ValueToCode(PT_WXSTRING,_STDSTR(array[0]));
          
        
        for (unsigned int i=1 ; i< array.Count() ; i++)
          result = result + ", " + ValueToCode(PT_WXSTRING,_STDSTR(array[i]));
          
      }
      break;
        
    default:
      
      break;  
  }
  
  return result;
}

///////////////////////////////////////////////////////////////////////////////

string CppCodeGenerator::ConvertCppString(string text)
{
  string result;
  
  for (unsigned int i=0; i<text.length() ; i++)
  {
    char c = text[i];
    
    switch (c)
    {
      case '"':
        result = result + "\\\"";
        break;

      case '\\':
        result = result + "\\\\";
        break;
        
      case '\t':
        result = result + "\\t";
        break;
        
      case '\n':
        result = result + "\\n";
        break;
      
      case '\r':
        result = result + "\\r";
        break;
        
      default:
        result = result + c;
        break;
    }
  }
  return result;
}

string CppCodeGenerator::ConvertXpmName(string text)
{
  string name = text;
  // el nombre consiste en extraer el nombre del fichero (sin el directorio)
  // y sustituir el caracter '.' por '_'.
  
  int last_slash = name.size() - 1;
  while (last_slash >= 0 && name[last_slash] != '\\' && name[last_slash] != '/')
  {
    if (name[last_slash] == '.')
      name[last_slash] = '_';
    last_slash--;
  }
    
  // quitamos el directorio
  if (last_slash >= 0 && last_slash < (int)name.size() - 1)
    name = name.substr(last_slash+1,name.size() - last_slash + 1);
  
  return name;
}

bool CppCodeGenerator::GenerateCode(PObjectBase project)
{
  if (!project)
  {
    wxLogError(wxT("There is no project to generate code"));
    return false;
  }
  
  m_header->Clear();
  m_source->Clear();
  string date(__DATE__);
  string time(__TIME__);
  string code_header (
   "///////////////////////////////////////////////////////////////////////////\n"
   "// C++ code generated with wxFormBuilder (version " __DATE__ ")\n" 
   "// http://wxformbuilder.software-libre.org/\n"
   "//\n"
   "// PLEASE DO \"NOT\" EDIT THIS FILE!\n"
   "///////////////////////////////////////////////////////////////////////////\n");
   
  m_header->WriteLn(code_header);
  m_source->WriteLn(code_header);
  
  PProperty propFile = project->GetProperty("file");
  if (!propFile)
  {
    wxLogError(wxT("Missing \"file\" property on Project Object"));
    return false;
  }
  
  string file = propFile->GetValue();
  if (file == "")
    file = "noname";
  
  m_header->WriteLn("#ifndef __" + file + "__");
  m_header->WriteLn("#define __" + file + "__");

  // en el cpp generamos el include del .h generado y los xpm
  m_source->WriteLn("#include \""+file+".h\"");
  m_source->WriteLn("");
  GenXpmIncludes(project);
  
  // generamos en el h los includes de las dependencias de los componentes.
  GenIncludes(project);
  
  // generamos los defines de las macros
  GenDefines(project);
  
  for (unsigned int i=0; i<project->GetChildCount(); i++)
  {
    GenClassDeclaration(project->GetChild(i));
    GenConstructor(project->GetChild(i));
  }
  
  m_header->WriteLn("#endif //__" + file + "__");
  m_header->WriteLn("");
  
  return true;
}

void CppCodeGenerator::GenAttributeDeclaration(PObjectBase obj, Permission perm)
{
//  if (obj->GetObjectInfo()->IsSubclassOf("C++"))
  if (obj->GetObjectTypeName() == "notebook" ||
      obj->GetObjectTypeName() == "widget" || 
      obj->GetObjectTypeName() == "statusbar" || 
      obj->GetObjectTypeName() == "component" ||
      obj->GetObjectTypeName() == "container" ||
      obj->GetObjectTypeName() == "menubar")
  {
    string perm_str = obj->GetProperty("permission")->GetValue();
    
    if ((perm == P_PUBLIC && perm_str == "public") ||
        (perm == P_PROTECTED && perm_str == "protected") ||
        (perm == P_PRIVATE && perm_str == "private"))
    {
      // generamos la declaraci�n
      string code = GetCode(obj,"declaration");
      m_header->WriteLn(code);
    }
  }
  
  // recursivamente generamos los dem�s atributos
  for (unsigned int i = 0; i < obj->GetChildCount() ; i++)
  {
    PObjectBase child = obj->GetChild(i);
    
    GenAttributeDeclaration(child,perm);
  }
}

string CppCodeGenerator::GetCode(PObjectBase obj, string name)
{
  string _template;
  PCodeInfo code_info = obj->GetObjectInfo()->GetCodeInfo("C++");
  if (!code_info)
  {
    wxString msg(wxString::Format(wxT("Missing \"%s\" template for \"%s\" class. "
      "Review your XML object description"),
      name.c_str(), obj->GetClassName().c_str()));
    wxLogError(msg);
    return "";
  }
  
  _template = code_info->GetTemplate(name);
    
  CppTemplateParser parser(obj,_template);
  string code = parser.ParseTemplate();

  return code;
}

void CppCodeGenerator::GenClassDeclaration(PObjectBase class_obj)
{
  PProperty propName = class_obj->GetProperty("name");
  if (!propName)
  {
    wxLogError(wxT("Missing \"name\" property on \"%s\" class. "
      "Review your XML object description"),class_obj->GetClassName().c_str());
    return;
  }
    
  string class_name = propName->GetValue();
  if (class_name == "")
  {
    wxLogError(wxT("Object name can not be null"));
    return;
  }

  m_header->WriteLn("/**");
  m_header->WriteLn(" * Class " + class_name);
  m_header->WriteLn(" */");

  m_header->WriteLn("class " + class_name + " : " + GetCode(class_obj,"base"));
  m_header->WriteLn("{");
  m_header->Indent();
  
  // private
  m_header->WriteLn("private:");
  m_header->Indent();  
  GenAttributeDeclaration(class_obj,P_PRIVATE);
  m_header->Unindent();
  m_header->WriteLn("");
  
  // protected
  m_header->WriteLn("protected:");
  m_header->Indent();  
  GenAttributeDeclaration(class_obj,P_PROTECTED);
  m_header->Unindent();
  m_header->WriteLn("");  
  
  // public
  m_header->WriteLn("public:");
  m_header->Indent();  
  GenAttributeDeclaration(class_obj,P_PUBLIC);
  m_header->WriteLn("");
    
  // dentro de public tambi�n incluimos el constructor
  m_header->WriteLn(GetCode(class_obj,"cons_decl"));  
  m_header->Unindent();
  m_header->WriteLn("");

  m_header->Unindent();
  m_header->WriteLn("};");
  m_header->WriteLn("");
}


void CppCodeGenerator::GenIncludes(PObjectBase project)
{
  m_header->WriteLn("#include <wx/wx.h>");
  // almacenaremos todos los objetos diferentes que se encuentran en el
  // proyecto para luego generar los includes.
  set<PObjectInfo> info_set;
 
  // buscamos todas las dependencias
  for (unsigned int i=0; i<project->GetChildCount(); i++)
    FindDependencies(project->GetChild(i), info_set);

  // generamos los includes
  set<PObjectInfo>::iterator it;
  for (it = info_set.begin() ; it != info_set.end() ; it++)
  {
    PCodeInfo code_info = (*it)->GetCodeInfo("C++");
    
    if (code_info)
    {
      string include = code_info->GetTemplate("include");
      if (include != "")
        m_header->WriteLn(include);
    }
  }
  
  m_header->WriteLn("");
}

void CppCodeGenerator::FindDependencies(PObjectBase obj, set<PObjectInfo> &info_set)
{
  unsigned int ch_count = obj->GetChildCount();
  if (ch_count > 0)
  {
    unsigned int i;
    for (i = 0; i<ch_count; i++)
    {
      PObjectBase child = obj->GetChild(i);
      info_set.insert(child->GetObjectInfo());
      FindDependencies(child, info_set);
    }
  }
}

void CppCodeGenerator::GenConstructor(PObjectBase class_obj)
{
  m_source->WriteLn(GetCode(class_obj,"cons_def"));
  m_source->WriteLn("{");
  m_source->Indent();
  
  for (unsigned int i=0; i<class_obj->GetChildCount() ; i++)
    GenConstruction(class_obj->GetChild(i),true);
  
  m_source->Unindent();
  m_source->WriteLn("}");
  m_source->WriteLn("");
}

void CppCodeGenerator::GenConstruction(PObjectBase obj, bool is_widget)
{
  string type = obj->GetObjectTypeName();
  
  if (type == "notebook" || type == "container" || type == "widget" ||
      type == "menubar" || type == "statusbar")
  {
      // comprobamos si no se ha declarado como atributo de clase
      // en cuyo caso lo declaramos en el constructor
      
      string perm_str = obj->GetProperty("permission")->GetValue();
      if (perm_str == "none")
        m_source->WriteLn(GetCode(obj,"declaration"));
      
      m_source->WriteLn(GetCode(obj,"construction"));
      GenSettings(obj->GetObjectInfo(), obj);
      
      for (unsigned int i=0; i<obj->GetChildCount() ; i++)
        GenConstruction(obj->GetChild(i),true);
        
      if (type == "menubar")
      {
        m_source->WriteLn(GetCode(obj,"menubar_add")); 
        m_source->WriteLn("");
      }
  }
  else if (type == "sizer")
  {
      m_source->WriteLn(GetCode(obj,"declaration"));
      m_source->WriteLn(GetCode(obj,"construction"));
      GenSettings(obj->GetObjectInfo(), obj);
      
      for (unsigned int i=0; i<obj->GetChildCount() ; i++)
        GenConstruction(obj->GetChild(i),false);
        
      if (is_widget)
      {
        // hay que hacer un SetSizer, pero
        // no hay una plantilla para esta operaci�n :-(
        // No conviene empotrar plantillas en la aplicaci�n, ya que
        // para hacer cambios hay que recompilar el c�digo (sin que
        // sirva de precedente, vamos a hacerlo aqu�)
        string _template = "#wxparent $name->SetSizer($name);\n"
                           "#wxparent $name->SetAutoLayout(true);\n"
                           "#wxparent $name->Layout();";
        CppTemplateParser parser(obj,_template);
        m_source->WriteLn(parser.ParseTemplate());
      } 
      
  }
  else if (type == "menu" || type == "submenu")
  {
      m_source->WriteLn(GetCode(obj,"declaration"));
      m_source->WriteLn(GetCode(obj,"construction"));
      
      for (unsigned int i=0; i<obj->GetChildCount() ; i++)
        GenConstruction(obj->GetChild(i),false);
    
      m_source->WriteLn(GetCode(obj,"menu_add"));
      
  }
  else if (type == "spacer")
  {
      // En lugar de modelar un "spacer" como un objeto que se incluye en
      // un sizer item, los vamos a considerar un como un tipo de
      // de "sizeritem" capaz de existir por s� solo. De esta forma ser�
      // m�s facil la exportaci�n XRC.
      m_source->WriteLn(GetCode(obj,"spacer_add"));
  }
  else if (type == "sizeritem")
  {
      // El hijo, hay que a�adirlo al sizer teniendo en cuenta el tipo
      // del objeto hijo (hay 3 rutinas diferentes)
      GenConstruction(obj->GetChild(0),false);
      
      string child_type = obj->GetChild(0)->GetObjectTypeName();
      string temp_name;
      if (child_type == "notebook" || child_type == "container" ||
          child_type == "widget" || child_type == "statusbar")
      {
        temp_name = "window_add";
      }
      else if (child_type == "sizer")
      {  
        temp_name = "sizer_add";
      }
      else
        assert(false);
          
      m_source->WriteLn(GetCode(obj,temp_name));
  }
  else if (type == "notebookpage")
  {
    GenConstruction(obj->GetChild(0),false);
    m_source->WriteLn(GetCode(obj,"page_add"));
  }
  else if (type == "menuitem")
  {  
    m_source->WriteLn(GetCode(obj,"construction"));
    m_source->WriteLn(GetCode(obj,"menuitem_add"));
    GenSettings(obj->GetObjectInfo(), obj);
  }
  else  
    assert(false);
}

void CppCodeGenerator::FindMacros(PObjectBase obj, set<string> &macro_set)
{
  // recorre cada propiedad de cada objeto identificando aquellas
  // que sean macros, en cuyo caso la a�ade al conjunto.
  unsigned int i;  
 
  for (i=0; i<obj->GetPropertyCount(); i++)
  {
    PProperty prop = obj->GetProperty(i);
    if (prop->GetType() == PT_MACRO)
      macro_set.insert(prop->GetValue());
  }
  
  for (i=0; i<obj->GetChildCount(); i++)
  {
    FindMacros(obj->GetChild(i),macro_set);
  }
}

void CppCodeGenerator::GenDefines(PObjectBase project)
{
  set<string> macro_set;
  FindMacros(project,macro_set);

  m_header->WriteLn("");
  // la macro por defecto tiene valor -1  
  m_header->WriteLn("#define ID_DEFAULT -1 // Default");

  // debemos quitar la macro por defecto del conjunto
  set<string>::iterator it;
  it = macro_set.find("ID_DEFAULT");
  if (it != macro_set.end())
    macro_set.erase(it);
  
  unsigned int id = FIRST_ID;
  for (it = macro_set.begin() ; it != macro_set.end(); it++)
  {
    ostringstream define;
    define << "#define " << *it << " " << id;
    m_header->WriteLn(define.str());
    id++;
  }
  
  m_header->WriteLn("");
}

void CppCodeGenerator::GenSettings(PObjectInfo info, PObjectBase obj)
{
  string _template;
  PCodeInfo code_info = info->GetCodeInfo("C++");

  if (!code_info)
    return;
    
  _template = code_info->GetTemplate("settings");
  
  if (_template != "")
  {
    CppTemplateParser parser(obj,_template);
    string code = parser.ParseTemplate();
    if (code != "")
      m_source->WriteLn(code);
  }
  
  // procedemos recursivamente con las clases base
  for (unsigned int i=0; i< info->GetBaseClassCount(); i++)
  {
    PObjectInfo base_info = info->GetBaseClass(i);
    GenSettings(base_info,obj);
  }
}

///////////////////////////////////////////////////////////////////////


void CppCodeGenerator::GenXpmIncludes(PObjectBase project)
{
  set<string> include_set;

  // lo primero es obtener la lista de includes
  FindXpmProperties(project,include_set);
  
  // y los generamos
  set<string>::iterator it;
  for (it = include_set.begin() ; it != include_set.end() ; it++)
  {
    string include = *it;
    if (include != "")
      m_source->WriteLn(include);
  }
  
  m_source->WriteLn("");
}

void CppCodeGenerator::FindXpmProperties(PObjectBase obj, set<string> &set)
{
  // recorremos cada una de las propiedades del objeto obj, si damos con
  // alguna que sea de tipo PT_XPM_BITMAP a�adimos la cadena del "include"
  // en set. Luego recursivamente hacemos lo mismo con los hijos.
  unsigned int i, count;
  
  count = obj->GetPropertyCount();
  
  for (i = 0; i < count; i++)
  {
    PProperty property = obj->GetProperty(i);
    if (property->GetType() == PT_XPM_BITMAP)
    {
      string inc = "#include \"" + ConvertCppString(property->GetValue()) + "\"";
      set.insert(inc);
    }
  }
  
  count = obj->GetChildCount();
  for (i = 0; i< count; i++)
  {
    PObjectBase child = obj->GetChild(i);
    FindXpmProperties(child, set);
  }
}

bool CppCodeGenerator::SelectRelativePath (string path)
{
  bool result = wxFileName::DirExists(_WXSTR(path));
  m_path = (result ? path : "");

  return result;
}

string ConvertToRelativePath(string path, string referencePath)
{
  // no se usa
  return path;
}