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

#ifndef __CODEGEN__
#define __CODEGEN__

#include <string>
#include <sstream>
#include "model/objectbase.h"
#include <boost/smart_ptr.hpp>

using namespace boost;
using namespace std;

class TemplateParser;

typedef shared_ptr<TemplateParser> PTemplateParser;

/**
 * Aspectos Lexicos.
 *
 * Las macros del preprocesador viene precedidas del car�cter '#'.
 *   Ejemplo: #wxparent $name
 *
 * Las propiedades del objeto vienen precedidas del car�cter '$'.
 *   Ejemplo: $name
 *
 * La creacion de una variable local vienen precedidas con el caracter '%'
 *   Ejemplo: int %var = $style;
 *
 * Para considerar como texto los caracteres especiales se usa el car�cter
 * especial '@'.
 *   Ejemplo: @# @$ @@ @%
 *
 */
 
/**
 * Directivas del procesador de plantillas:
 * 
 * - #wxparent $property
 *   Se utiliza para obtener una propiedad del objeto de tipo T_WIDGET padre
 *   del objeto actual. Esta directiva es necesaria para generar el par�metro
 *   "wxWindow *parent" en los constructores de cada widget.
 *   Ejemplo:
 *     $name = new wxButton(#wxparent $name, ....
 *
 * - #wxchild $property
 *   Se utiliza para obtener una propiedad del primer hijo del objeto actual.
 *   Es utilizada por el objeto "sizeritem" para a�adir un objeto al sizer.
 *
 * - #ifnotnull $property @{ .... @}
 *   Se utiliza para generar el c�digo siempre y cuando se cumpla la condici�n
 *   de que la propiedad no tiene un valor nulo.
 *
 * - #foreach $property @{ ..... @}
 *   Se utiliza para aquellos casos donde hay que repetir un trozo de c�digo
 *   repetidas veces. $property es una expresi�n separada por ','. El c�digo
 *   encerrado entre llaves ( '@{' y '@}' ) ser� incluido tantas veces como
 *   subexpresiones se encuentren en el valor de la propiedad. Dentro del
 *   c�digo de la plantilla, se podr� hacer referencia a la subexpresi�n
 *   con la directiva #pred.
 *   Ejemplo:
 *    #foreach $growable_cols
 *    @{
 *     $name->AddGrowableCol(#pred);
 *    @}
 *
 * - #pred (ver #foreach)
 *
 */

/**
 * Analizador de plantillas de c�digo.
 */
class TemplateParser
{
 private:
   PObjectBase m_obj;   
   istringstream m_in;
   ostringstream m_out;
   string m_pred;
   
   void ignore_whitespaces();

 protected:
  typedef enum {
    TOK_ERROR,
    TOK_MACRO,
    TOK_TEXT,
    TOK_PROPERTY
  } Token;
  
  typedef enum {
    ID_ERROR,
    ID_WXPARENT,
    ID_PARENT,
    ID_CHILD,
    ID_IFNOTNULL, 
    ID_FOREACH,
    ID_PREDEFINED,  // simbolo predefinido '#pred'
    ID_NEWLINE
  } Ident;
  

  Ident SearchIdent(string ident);
  Ident ParseIdent();

  string ParsePropertyName();
  /**
   * Esta rutina extrae el codigo de una plantilla encerrada entre
   * las macros #begin y #end, teniendo en cuenta que puede estar anidados
   */
  string ExtractInnerTemplate();

  /**
   * Consulta el siguiente s�mbolo de la entrada y devuelve el token.
   * @return TOK_MACRO si a continuaci�n viene un comando.
   *         TOK_PROPERTY si a continuaci�n viene una propiedad.
   *         TOK_TEXT si a continuaci�n viene texto normal.
   */
  Token GetNextToken();


  bool ParseInnerTemplate();
  bool ParseWxParent();
  bool ParseParent();
  bool ParseChild();
  bool ParseForEach();
  bool ParseIfNotNull();
  bool ParseNewLine();
  
  /**
   * Parsea una macro.
   */
  bool ParseMacro();
  
  /**
   * Parsea una propiedad.
   */
  bool ParseProperty();
  
  
  /**
   * Parsea texto.
   */
  bool ParseText();
  
  bool ParsePred();
    
 public:
   TemplateParser(PObjectBase obj, string _template); 
   
   /**
    * Devuelve el c�digo del valor de una propiedad en el formato del lenguaje.
    * @note usa ValueToCode
    */
   string PropertyToCode(PProperty property);
   
   /**
    * Este m�todo crea un nuevo parser del mismo tipo que el objeto que llama
    * a dicho m�todo.
    */
   virtual PTemplateParser CreateParser(PObjectBase obj, string _template) = 0; 
   
   virtual ~TemplateParser() {};
    
  /** Devuelve el c�digo del nombre del atributo "wxWindow *parent" ra�z.
   * En C++ ser� el puntero "this" pero en otros lenguajes no tiene porqu�
   * llamarse as�.
   */
  virtual string RootWxParentToCode() = 0;
  
  /**
   * A partir del valor de una propiedad genera el c�digo.
   */
  virtual string ValueToCode(PropertyType type, string value) = 0;
  
  /**
   * La funci�n "estrella" de la clase. Analiza una plantilla devolviendo el
   * c�digo.
   */
  string ParseTemplate();
  
  /**
   * establece el texto predefinido, el cual ser� devuelto con la directiva
   * #pred.
   */
  void SetPredefined(string pred) { m_pred = pred; };
};

/**
 * Escritor de c�digo.
 * 
 * Con esta clase se pretende abstraer al generador de c�digo de la forma 
 * en la que se escribe el c�digo, ya que es posible que en algunos casos
 * queramos que se escriba en un fichero, en un control gr�fico o incluso en
 * ambos.
 */
class CodeWriter
{
 private:
  int m_indent;
  int m_cols;
    
 protected:
  /**
   * Escribe una cadena de caracteres.
   */
  virtual void DoWrite(string code) {};

  /**
   * Devuelve el tama�o del indentado.
   */  
  virtual int GetIndentSize() { return 2; }
  
  /**
   * Devuelve el tama�o de la columna del fichero.
   * @note esto es por si queremos ajustar el c�digo.
   */
  virtual int GetColumns() { return 80; }
  
  /**
   * Comprueba si la cadena pasada no contiene caracteres de retorno de carro.
   */
  bool StringOk(string s);  

  /**
   * Divide una cadena de texto mal formada (con retornos de carro), en
   * columnas simples insert�ndolas una a una respetando el indentado.
   */
  void FixWrite(string s);
  
  public:
   /**
    * Constructor.
    */
   CodeWriter();
   
   /**
    * Destructor.
    */
   virtual ~CodeWriter() {};
  
   /**
    * Incrementa el indentado.
    */
   void Indent()    { m_indent += GetIndentSize(); } 
   
   /**
    * Decrementa el indentado.
    */
   void Unindent()
   {
      m_indent -= GetIndentSize();
      if (m_indent < 0)
        m_indent = 0; 
   } 
  
  /**
   * Escribe una l�nea de c�digo.
   */   
  void WriteLn(string code);
  
  /**
   * Escribe una cadena de texto en el c�digo.
   */
  void Write(string code);

  /** 
   * borra todo el c�digo previamente escrito.
   */
  virtual void Clear() = 0;
};

typedef shared_ptr<CodeWriter> PCodeWriter;

/**
 * Generador de c�digo.
 *
 * Esta clase define una interfaz para ejecutar la generaci�n de c�digo.
 * Los algoritmos para generar el c�digo guardan excasas similitudes de un
 * lenguaje a otro, veamos algunos ejemplos:
 *
 * - En C++ tenemos que generar las declaraciones de una clase y luego su
 *   implementaci�n, a parte de los #defines e #includes pertinentes.
 * - En java, aunque tiene una sintaxis "parecida", implementaci�n y declaraci�n
 *   van ligadas en el mismo fichero, adem�s requiere de un fichero por clase.
 * - En el formato XRC (XML), no tiene nada que ver con ninguno de los
 *   anteriores, pareciendose mucho al modelo de datos de la propia aplicaci�n.
 *
 * Dado que no existe un algoritmo "universal" para generar c�digo no queda m�s
 * remedio que realizar una implementaci�n diferente por cada lenguaje. A pesar
 * de esto, es posible reutilizar todo el sistema de plantillas de c�digo
 * simplificando bastante la tarea de implementar el generador de un nuevo
 * lenguaje.
 */
class CodeGenerator
{
 protected:
  
 public:
  /**
   * Destructor virtual.
   */   
  virtual ~CodeGenerator() {};
  /**
   * Genera el c�digo del proyecto.
   */  
  virtual bool GenerateCode(PObjectBase project) = 0;   
};


#endif //__CODEGEN__
