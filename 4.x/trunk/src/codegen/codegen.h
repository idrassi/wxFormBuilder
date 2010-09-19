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
// Written by
//   José Antonio Hurtado - joseantonio.hurtado@gmail.com
//   Juan Antonio Ortega  - jortegalalmolda@gmail.com
//
///////////////////////////////////////////////////////////////////////////////

/**
 * @file codegen.h
 * @author José Antonio Hurtado - joseantonio.hurtado@gmail.com
 * @author Juan Antonio Ortega  - jortegalalmolda@gmail.com
 * @date 
 * @brief 
 */

#ifndef __CODEGEN_H__
#define __CODEGEN_H__

#include "model/types.h"
#include "utils/wxfbdefs.h"

#include <map>

#include <wx/sstream.h>

/**
 * @class TemplateParser
 * Template notes
 *
 * The preprocessor macros begin with the character '#'.
 *   Example: @code #wxparent $name @endcode
 *
 * The object properties begin with the character '$'.
 *   Example: @code $name @endcode
 *
 * The creation of a local variable begins with the character '%'
 *   Example: @code int %var = $style; @endcode
 *
 * The '@' character is used to escape the special characters to treat them as text
 *   Example: @code @# @$ @@ @% @endcode
 *
 * Preprocessor directives:
 *
 * - #wxparent $property
 *   Used to get the property of the parent of the current object.
 *	 This directive is necessary to generate the parameter "wxWindow* parent" in the constructors of each widget.
 *   Example: @code $name = new wxButton( #wxparent $name, .... @endcode
 *
 * - @code #wxchild $property @endcode
 *   Used to get a property of the first child of the current object.
 *   Used by "sizeritem" in order to add a sizer object.
 *
 * - @code #ifnotnull $property @{ .... @} @endcode
 *   Used to generate code as long as the property is not null
 *
 * - @code #foreach $property @{ ..... @} @endcode
 *   Used to repeat code for each subproperty of $property, where $property is a comma delimited list.
 *   The code is contained between '@{' and '@}'. The code will be generated as many times as there are subexpressions
 *   in the value of the property. Within the brace, access to the subexpression is obtained with the #pred directive, and
 *	access to index of the subexpression is obtained with #npred.
 *   Example:
 * @code
 *    #foreach $growable_cols
 *    @{
 *		$name->AddGrowableCol(#pred);
 *    @}
 * @endcode
 * - #pred (see #foreach)
 * - #npred (see #foreach)
 */

class TemplateParser
{
private:
	PObjectBase 		m_obj; 		/**< @todo Description needed. */
	wxStringInputStream m_in; 		/**< @todo Description needed. */
	wxString 			m_out; 		/**< @todo Description needed. */
	wxString 			m_pred; 	/**< @todo Description needed. */
	wxString 			m_npred; 	/**< @todo Description needed. */
	void ignore_whitespaces(); 		/**< @todo Description needed. */
	int m_indent;					/**< Current indentation level in the file */

protected:
	/** @todo Description needed. */
	typedef enum {
		TOK_ERROR,
		TOK_MACRO,
		TOK_TEXT,
		TOK_PROPERTY
	} Token;

	/** @todo Description needed. */
	typedef enum {
		ID_ERROR,
		ID_WXPARENT,
		ID_PARENT,
		ID_FORM,
		ID_CHILD,
		ID_IFNOTNULL,
		ID_IFNULL,
		ID_FOREACH,
		ID_PREDEFINED, 			// predefined symbol '#pred'
		ID_PREDEFINED_INDEX, 	// #npred
		ID_NEWLINE,
		ID_IFEQUAL,
		ID_IFNOTEQUAL,
		ID_IFPARENTTYPEEQUAL,
		ID_IFPARENTCLASSEQUAL,
		ID_APPEND,
		ID_CLASS,
		ID_INDENT,
		ID_UNINDENT,
		ID_IFTYPEEQUAL
	} Ident;

	/**
	 * @todo Description needed.
	 * @param value 
	 * @param set 	
	 */
	bool IsEqual( const wxString& value, const wxString& set );

	/**
	 * @todo Description needed.
	 * @param ident 
	 */
	Ident SearchIdent( wxString ident );

	/** @todo Description needed. */
	Ident ParseIdent();

	/**
	 * @todo Description needed.
	 * @param child 
	 */
	wxString ParsePropertyName( wxString* child = NULL );

	/**
	 * This routine extracts the source code from a template enclosed between
	 * the \#begin and \#end macros, having in mind that they can be nested.
	 * 
	 * Obtaining the template enclosed between "@{" and "@}"
	 * @note Whitespaces at the very start will be ignored.
	 */
	wxString ExtractInnerTemplate();

	/**
	 * A literal value is an string enclosed between '"' (e.g. "xxx"),
	 * The " character is represented with "".
	 */
	wxString ExtractLiteral();

	/**
	 * Look up for the following symbol from input and returns the token.
	 * @return TOK_MACRO when it's followed by a command.
	 *         TOK_PROPERTY when it's followed by a property.
	 *         TOK_TEXT when it's followed by normal text.
	 */
	Token GetNextToken();

	bool ParseInnerTemplate(); 		/**< @todo Description needed. */
	bool ParseWxParent(); 			/**< @todo Description needed. */
	bool ParseParent(); 			/**< @todo Description needed. */
	bool ParseForm(); 				/**< @todo Description needed. */
	bool ParseChild(); 				/**< @todo Description needed. */
	bool ParseForEach(); 			/**< @todo Description needed. */
	bool ParseIfNotNull(); 			/**< @todo Description needed. */
	bool ParseIfNull(); 			/**< @todo Description needed. */
	bool ParseNewLine(); 			/**< @todo Description needed. */
	bool ParseIfEqual(); 			/**< @todo Description needed. */
	bool ParseIfNotEqual(); 		/**< @todo Description needed. */
	bool ParseIfParentTypeEqual(); 	/**< @todo Description needed. */
	bool ParseIfParentClassEqual(); /**< @todo Description needed. */
	void ParseAppend(); 			/**< @todo Description needed. */
	void ParseClass(); 				/**< @todo Description needed. */
	void ParseIndent(); 			/**< @todo Description needed. */
	void ParseUnindent(); 			/**< @todo Description needed. */
	bool ParseIfTypeEqual(); 		/**< @todo Description needed. */

	/**
	 * @todo Description needed.
	 * @param childName 
	 */
	PProperty GetProperty( wxString* childName = NULL );

	/** @todo Description needed. */
	PObjectBase GetWxParent();

	/**
	 * @todo Description needed.
	 * @param relative 
	 */
	PProperty GetRelatedProperty( PObjectBase relative );

	bool ParseMacro(); 				/**< Parse a macro. */
	bool ParseProperty(); 			/**< Parse a property. */
	bool ParseText(); 				/**< Parse text. */
	bool ParsePred(); 				/**< Parse #pred macro. */
	bool ParseNPred(); 				/**< Parse #npred macro. */

public:
	/**
	 * Constructor.
	 * @param obj 		Object.
	 * @param _template Code template.
	 */
	TemplateParser( PObjectBase obj, wxString _template );

	/**
	 * Constructor.
	 * @param that 		Parser.
	 * @param _template Code template.
	 */
	TemplateParser( const TemplateParser& that, wxString _template );

	/**
	 * Returns the code for a property value in the language format.
	 * @note use ValueToCode
	 */
	wxString PropertyToCode( PProperty property );

	/**
	 * This method creates a new parser with the same type that the object
	 * calling such method.
	 */
	virtual PTemplateParser CreateParser( const TemplateParser* oldparser, wxString _template ) = 0;

	/** Virtual destructor */
	virtual ~TemplateParser() {};

	/**
	 * Returns the code for a "wxWindow *parent" root attribute' name.
	 * In C++ it will be the "this" pointer, but in other languages it
	 * could be named differently.
	 */
	virtual wxString RootWxParentToCode() = 0;

	/** Generates the code from a property value. */
	virtual wxString ValueToCode( PropertyType type, wxString value ) = 0;

	/** The "star" function for this class. Analyzes a template, returning the code. */
	wxString ParseTemplate();

	/** Set the string for the #pred and #npred macros */
	void SetPredefined( wxString pred, wxString npred ) { m_pred = pred; m_npred = npred; };
};

/**
 * @class CodeGenerator
 * Code Generator
 *
 * This class defines an interface to execute the code generation.
 * The algorithms to generate the code are similar from one language to another.
 * Examples:
 *
 * - In C++, we generate the class declarations and then its implementation,
 *   besides the related #define and #include.
 * - In java, it has a similar syntax, but declaration and implementation are
 *   together in the same file, and it's required one file per class.
 * - In XRC format (XML), it's a different way, it's more likely to the
 *   data model from the application itself.
 *
 * Given that doesn't exist an "universal" algorithm for generating code, there
 * is no choice but to make a different implementation for each language. It's
 * possible to reuse the whole code templates system, although, simplifying a lot
 * the implementation task for a new language.
 */
class CodeGenerator
{
protected:

public:
	/** Virtual destructor. */
	virtual ~CodeGenerator() {};

	/** Generate the code of the project */
	virtual bool GenerateCode( PObjectBase project ) = 0;
};

#endif //__CODEGEN_H__
