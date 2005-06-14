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

#include "codegen.h"
#include "utils/debug.h"
#include "wx/wx.h"
#include <wx/tokenzr.h>

void CodeWriter::WriteLn(string code)
{
  // no se permitirán saltos de linea dentro de "code"
  // si los hubiera, FixWrite toma la cadena y la trocea en líneas
  // e inserta una a una mediante WriteLn
  if (!StringOk(code))
    FixWrite(code);
  else
  {
    Write(code);
    Write("\n");
    m_cols = 0;
  }
}  

bool CodeWriter::StringOk(string s)
{
  if (s.find("\n",0) == string::npos)
    return true;
  else
    return false;
}

void CodeWriter::FixWrite(string s)
{
  wxString str(s.c_str(),wxConvUTF8);
  
  wxStringTokenizer tkz(str,wxT("\n"));
  bool prev_is_null = false;
  
  while (tkz.HasMoreTokens())
  {
    wxString line = tkz.GetNextToken();
    line.Trim(false);
    line.Trim(true);
    
    if (line != wxT("") || !prev_is_null)
      WriteLn(string(line.mb_str()));
      
    prev_is_null = (line == wxT(""));
  }
}


void CodeWriter::Write(string code)
{
  if (m_cols == 0)
  {
    // insertamos el indentado
    for (int i=0 ; i< m_indent ; i++)
      DoWrite(" ");
      
    m_cols = m_indent;
  }

  
 // aquí debemos comprobar si hemos sobrepasado el maximo de columnas
//  if (m_cols + code.length() > GetColumns())
//    BreakLine(code)
  
  
  DoWrite(code);
}  

TemplateParser::TemplateParser(PObjectBase obj, string _template)
  : m_obj(obj), m_in(_template)
{
}

TemplateParser::Token TemplateParser::GetNextToken()
{
  // Hay 3 caracteres espaciales
  // #xxxx -> comando
  // $xxxx -> propiedad
  // @x -> caracter especial. @# es el caracter #.
  
  Token result = TOK_ERROR;
  
  if (!m_in.eof())
  {
    char c = m_in.peek();
    if (c == '#')
      result = TOK_MACRO;
    else if (c == '$')
      result = TOK_PROPERTY;
    else
      result = TOK_TEXT;
  }

  return result;
}


bool TemplateParser::ParseMacro()
{
  Ident ident;
  
  ident = ParseIdent();
  switch (ident)
  {
    case ID_WXPARENT:
      return ParseWxParent();
      break;
    case ID_PARENT:
      return ParseParent();
      break;
    case ID_IFNOTNULL:
      return ParseIfNotNull();
      break;
    case ID_FOREACH:
      return ParseForEach();
      break;
    case ID_PREDEFINED:
      return ParsePred();
      break;
    case ID_CHILD:
      return ParseChild();
      break;
    case ID_NEWLINE:
      return ParseNewLine();
      break;
    default:
      assert(false);
      return false;
      break;
  }

  return true;
}


TemplateParser::Ident TemplateParser::ParseIdent()
{
  Ident ident;
  
  if (!m_in.eof())
  {
    ostringstream macro;
    m_in.get();
      
    while (m_in.peek() != EOF && m_in.peek() != '#' && m_in.peek() != '$'
           && ( (m_in.peek() >= 'a' && m_in.peek() <= 'z') ||
                (m_in.peek() >= 'A' && m_in.peek() <= 'Z') ||
                (m_in.peek() >= '0' && m_in.peek() <= '9')))
    {
      char c = m_in.get();
      macro << c;
    }
        
    // buscar el identificador
    ident = SearchIdent(macro.str());
  }
  return ident;
}

string TemplateParser::ParsePropertyName()
{
 string propname;
  
  if (!m_in.eof())
  {
    ostringstream propstream;
    m_in.get();
      
    while (m_in.peek() != EOF && m_in.peek() != '#' && m_in.peek() != '$'
           && ( (m_in.peek() >= 'a' && m_in.peek() <= 'z') ||
                (m_in.peek() >= 'A' && m_in.peek() <= 'Z') ||
                (m_in.peek() >= '0' && m_in.peek() <= '9') ||
                m_in.peek() == '_'))
    {
      char c = m_in.get(); 
      propstream << c << flush;
    }
        
      // buscar el comando
    propname = propstream.str();
  }
  return propname;
}

bool TemplateParser::ParseProperty()
{
  string propname = ParsePropertyName();
 
  PProperty property = m_obj->GetProperty(propname);
  m_out << PropertyToCode(property);

//  Debug::Print("parsing property %s",propname.c_str());
  
  return true;
}

bool TemplateParser::ParseText()
{
  bool result = true;
  
  ostringstream aux;
  
  while (m_in.peek() != EOF && m_in.peek() != '#' && m_in.peek() != '$')
  {
    char c = m_in.get();
    if (c == '@')
      c = m_in.get();

    m_out << c;
    aux << c;
  }
  
//  Debug::Print("Parsed Text: %s",aux.str().c_str());
  return result;
}


bool TemplateParser::ParseInnerTemplate()
{
  return true;
}

/*
bool TemplateParser::ParseToken(int token)
{
  return true;
}*/

bool TemplateParser::ParseWxParent()
{
  ignore_whitespaces();
  
  string propname = ParsePropertyName();
  
  // llegamos a uno de los inconvenientes del diseño elegido
  // y es que el padre puede ser T_CONTAINER o T_NOTEBOOK
  //PObjectBase wxparent(m_obj->FindNearAncestor(T_CONTAINER));

  PObjectBase wxparent;
  
  PObjectBase cont_parent (m_obj->FindNearAncestor("container"));
  PObjectBase nbook_parent (m_obj->FindNearAncestor("notebook"));
  
  if (cont_parent && nbook_parent)

    wxparent = (cont_parent->Deep() > nbook_parent->Deep() ?
                cont_parent : nbook_parent);

  else
    wxparent = (cont_parent ? cont_parent : nbook_parent);
  
  if (wxparent)
  {
    PProperty property = wxparent->GetProperty(propname);
    m_out << PropertyToCode(property);
  }
  else
    m_out << RootWxParentToCode();
    
  return true;
}

bool TemplateParser::ParseParent()
{
  ignore_whitespaces();
  
  string propname = ParsePropertyName();
  
  PObjectBase parent(m_obj->GetParent());
  if (parent)
  {
    PProperty property = parent->GetProperty(propname);
    m_out << PropertyToCode(property);
  }
  else
    m_out << "ERROR";
    
  return true;
}

bool TemplateParser::ParseChild()
{
  ignore_whitespaces();
  
  string propname = ParsePropertyName();
  
  // obtiene el primer hijo.
  PObjectBase child(m_obj->GetChild(0));
  
  if (child)
  {
    PProperty property = child->GetProperty(propname);
    m_out << PropertyToCode(property);
  }
  else
    m_out << RootWxParentToCode();
    
  return true;
}


bool TemplateParser::ParseForEach()
{
  // ignoramos los espacios que pudiera haber al principio
  ignore_whitespaces();

  // parseamos la propiedad
  if (GetNextToken() == TOK_PROPERTY)
  {
    string propname = ParsePropertyName();
    string inner_template = ExtractInnerTemplate();
    
    PProperty property = m_obj->GetProperty(propname);
    string propvalue = property->GetValue();
    
    // el valor de la propiedad debe ser una cadena de caracteres
    // separada por ','. Se va a generar la plantilla anidada tantas
    // veces como tokens se encuentren el el valor de la propiedad.
    
    if (property->GetType() == PT_INTLIST)
    {
      // Para ello se utiliza la clase wxStringTokenizer de wxWidgets
      wxStringTokenizer tkz(wxString(propvalue.c_str(),wxConvUTF8), wxT(","));
      while (tkz.HasMoreTokens())
      {
        wxString token;
        token = tkz.GetNextToken();
        token.Trim(true);
        token.Trim(false);
      
        // parseamos la plantilla interna
        {
          string code;
          PTemplateParser parser = CreateParser(m_obj,inner_template);
          parser->SetPredefined(string(token.mb_str()));
          code = parser->ParseTemplate();
          m_out << endl << code;        
        }
      }
    }
    else if (property->GetType() == PT_STRINGLIST)
    {
      wxArrayString array = property->GetValueAsArrayString();
      for (unsigned int i=0 ; i<array.Count() ; i++)
      {
        string code;
        PTemplateParser parser = CreateParser(m_obj,inner_template);
        parser->SetPredefined(ValueToCode(PT_WXSTRING,string(array[i].mb_str())));
        code = parser->ParseTemplate();
        m_out << endl << code;        
      }
    }
    else
      wxLogError(wxT("Property type not compatible with \"foreach\" macro"));
  }

  return true;
}

void TemplateParser::ignore_whitespaces()
{
  while (m_in.peek() != EOF && m_in.peek() == ' ')
    m_in.get();
}


bool TemplateParser::ParseIfNotNull()
{
  // ignoramos los espacios que pudiera haber al principio
  ignore_whitespaces();
      
  // parseamos la propiedad
  if (GetNextToken() == TOK_PROPERTY)
  {
    string propname = ParsePropertyName();
    string inner_template = ExtractInnerTemplate();
    
    PProperty property = m_obj->GetProperty(propname);
    if (property->GetValue() != "")
    {
      // hay que generar el codigo de la plantilla
      string code;
      PTemplateParser parser = CreateParser(m_obj,inner_template);
      code = parser->ParseTemplate();
      //m_out << endl << code;
      m_out << code;
    }
    
  }
  // else error

  return true;
}

TemplateParser::Ident TemplateParser::SearchIdent(string ident)
{
//  Debug::Print("Parsing command %s",ident.c_str());
  
  if (ident == "wxparent")
    return ID_WXPARENT;
  else if (ident == "ifnotnull")
    return ID_IFNOTNULL;
  else if (ident == "foreach")
    return ID_FOREACH;
  else if (ident == "pred")
    return ID_PREDEFINED;
  else if (ident == "child")
    return ID_CHILD;
  else if (ident == "parent")
    return ID_PARENT;
  else if (ident == "nl")
    return ID_NEWLINE;
  else
    return ID_ERROR;  
}

string TemplateParser::ParseTemplate()
{
  string result;
  
  while (!m_in.eof())
  {
    Token token = GetNextToken();
    switch (token)
    {
      case TOK_MACRO:
        ParseMacro();
        break;
      case TOK_PROPERTY:
        ParseProperty();
        break;
      case TOK_TEXT:
        ParseText();
        break;
      default:
        return "";
    }
  }
  
  result = m_out.str();
  
  // vamos a trim'ear la cadena
  wxString wx_result(result.c_str(),wxConvUTF8);
  
  // FIXME: estos trim's eliminan también los \n del principio y del final...
  //wx_result.Trim(true);
  //wx_result.Trim(false);
  
  return string(wx_result.mb_str());
}

/**
 * Extrae la plantilla encerrada entre '@{' y '@}'.
 * Nota: Los espacios al comienzo serán ignorados.
 */
string TemplateParser::ExtractInnerTemplate()
{
//  bool error = false;
  ostringstream os;
  
  char c1, c2;

  // ignoramos los espacios que pudiera haber al principio
  ignore_whitespaces();
 
  // los dos caracteres siguientes deberán ser '@{'
  c1 = m_in.get();
  c2 = m_in.get();
  
  if (c1 == '@' && c2 == '{')
  {
    int level = 1;
    bool end = false;
    // comenzamos la extracción de la plantilla  
    while (!end && m_in.peek() != EOF)
    {
      c1 = m_in.get();
      
      // comprobamos si estamos ante un posible cierre o apertura de llaves.
      if (c1 == '@')
      {
        c2 = m_in.get();
        
        if (c2 == '}')
        {
          level--;
          if (level == 0)
            end = true;
          else
          {
            // no es el cierre final, por tanto metemos los caracteres
            // y seguimos
            os << c1;
            os << c2;
          }
        }
        else
        {
          os << c1;
          os << c2;
          
          if (c2 == '{')
            level++;
        }
      }
      else
        os << c1;
    }
  }  
      
  return os.str();
}


bool TemplateParser::ParsePred()
{
  if (m_pred != "")
    m_out << m_pred;
  
  return true;
}

bool TemplateParser::ParseNewLine()
{
  m_out << '\n';
  return true;
}

string TemplateParser::PropertyToCode(PProperty property)
{
  return ValueToCode(property->GetType(), property->GetValue());
}

//////////////////////////////////////////////////////////////////////////////
CodeWriter::CodeWriter()
{
  m_indent = 0;
  m_cols = 0;
}  
