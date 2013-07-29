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
 * @file codeparser.h
 * @author
 * @date
 * @brief
 */
#ifndef CODEPARSER_H_INCLUDED
#define CODEPARSER_H_INCLUDED

#include <wx/hashmap.h>
#include <wx/msgdlg.h>
#include <wx/string.h>
#include <wx/textfile.h>

/**
 * @class Function
 * Stores all of the information for all of the parsed funtions.
 */
class Function
{
public:
	/** Constructor. */
	Function() {}

	/** Destructor. */
	~Function() {}

	/** Stores the code contained in the body of the function */
	void SetContents( wxString contents );

	/** Stores the whole first line of the function as a single string
	 * ex: "void fubar::DoSomething(int number)"
	 */
	void SetHeading( wxString heading );

	/** Stores any code/documentation located between the previous function and the current function. */
	void SetDocumentation( wxString documentation )
	{
		m_documentation = documentation;
	}

	/** Retrieves the body of the function. */
	wxString GetContents()
	{
		return m_functionContents;
	}

	/** Retrieves the documentation. Basically anything between the function declaration and the previous function*/
	wxString GetDocumentation()
	{
		return m_documentation;
	}
	/** Retrieves everything including documentation. */
	wxString GetFunction();

protected:
	wxString m_functionContents; 	/**< @todo Description needed. */
	wxString m_functionHeading; 	/**< @todo Description needed. */
	wxString m_documentation; 		/**< @todo Description needed. */
};

/** Map class mapping Function* to function name. */
WX_DECLARE_STRING_HASH_MAP( Function*, FunctionMap );
#define funcIterator FunctionMap::iterator

class CppTemplateParser;

/**
 * @class CodeParser
 * Parses the source and header files for all code added to the files after generation.
 */
class CodeParser
{
public:
	/** Constructor. */
	CodeParser() {}

	/** Destructor. */
	~CodeParser() {}

	/** Returns all user header include code before the class declaration. */
	wxString GetUserIncludes()
	{
		return m_userInclude;
	}

	/** Returns user class members. */
	wxString GetUserMembers()
	{
		return m_userMemebers;
	}

	/** Returns the Documentation of a function by name. */
	wxString GetFunctionDocumentation( wxString function );

	/** Returns the contents of a function by name and then removes it from the list of remaining functions. */
	wxString GetFunctionContents( wxString function );

	/**
	 * Returns all ramaining functions including documentation as one string.
	 * this may rearrange functions, but should keep them intact. */
	wxString GetRemainingFunctions();

	/** @todo Description needed. */
	wxString GetTrailingCode()
	{
		return m_trailingCode;
	}

protected:
	wxString m_userInclude; 		/**< @todo Description needed. */
	wxString m_className; 			/**< @todo Description needed. */
	wxString m_userMemebers; 		/**< @todo Description needed. */
	wxString m_trailingCode; 		/**< @todo Description needed. */

	FunctionMap m_functions; 		/**< @todo Description needed. */
	funcIterator m_functionIter; 	/**< @todo Description needed. */
};

/**
 * @class CCodeParser
 * Parses C++ source and header files for all code added to the generated.
 */
class CCodeParser : public CodeParser
{
private:
	wxString m_hFile; /**< @todo Description needed. */
	wxString m_cFile; /**< @todo Description needed. */

public:
	/** Constructor. */
	CCodeParser() {}

	/**
	 * Constructor
	 * @param headerFileName Header file name.
	 * @param sourceFileName Source file name.
	 */
	CCodeParser( wxString headerFileName, wxString sourceFileName )
	{
		m_hFile = headerFileName;
		m_cFile = sourceFileName;
	}

	/** Destructor. */
	~CCodeParser() {}

/* c++ Parser */

	/**
	 * Opens the header and source.
	 * @param className The Inherited class.
	 */
	void ParseCFiles( wxString className );

	/**
	 * Extracts the contents of the files.
	 * Take the the entire contents of both files in string form.
	 */
	void ParseCCode( wxString header, wxString source );

	/** Extracts all user header include code before the class declaration. */
	void ParseCInclude( wxString code );

	/** Extracts the contents of the generated class declaration. */
	void ParseCClass( wxString code );

	/** parses cpp file for functions and stores their contents in a hashmap with the function names as keys. */
	void ParseSourceFunctions( wxString code );

	/** searches code for code blocks starting at function start, returns contents of block. */
	wxString ParseBrackets( wxString code, int& functionStart );

	/** retrieves class members declared after the generated memebers */
	void ParseCUserMembers( wxString code );

/***************/
};

//class PCodeParser : public CodeParser

#endif // CODEPARSER_H_INCLUDED
