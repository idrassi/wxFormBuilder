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

#ifndef _XRC_CODE_GEN_
#define _XRC_CODE_GEN_

#include "codegen.h"

using namespace std;

/**
 * Generador de c�digo XRC.
 */
class XrcCodeGenerator : public CodeGenerator
{
 private:
  PCodeWriter m_cw;
  
  TiXmlElement* GetElement(PObjectBase obj);
 
 public:

  /**
   * Configura el escritor de c�digo para el fichero XML.
   */
  void SetWriter(PCodeWriter cw) { m_cw = cw; }

  /**
   * Genera el c�digo XRC del proyecto.
   */  
  bool GenerateCode(PObjectBase project); 
};


#endif //_XRC_CODE_GEN_
