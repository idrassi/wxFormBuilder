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
 * @file codewriter.h
 * @author 
 * @date 
 * @brief 
 */
#ifndef __CODEWRITER_H__
#define __CODEWRITER_H__

#include <wx/string.h>
#include <wx/stc/stc.h>

/**
 * @class CodeWriter
 * Abstracts the code generation from the target.
 * Because, in some cases the target is a file, sometimes a TextCtrl, and sometimes both.
 */
class CodeWriter
{
private:
	int m_indent; 	/**< Current indentation level in the file. */
	int m_cols; 	/**< @todo Description needed. */

protected:
	/** Write a wxString. */
	virtual void DoWrite( wxString code ) = 0;

	/** Returns the size of the indentation - was useful when using spaces, now it is 1 because using tabs. */
	virtual int GetIndentSize();

	/** Verifies that the wxString does not contain carraige return characters. */
	bool StringOk( wxString s );

	/**
	 * Divides a badly formed string (including carriage returns)
	 * in simple columns, inserting them one after another and taking indent into account.
	 */
	void FixWrite( wxString s, bool keepIndents = false );

public:
	/** Constructor. */
	CodeWriter();

	/** Destructor. */
	virtual ~CodeWriter();

	/** Increment the indent. */
	void Indent();

	/** Decrement the indent. */
	void Unindent();

	/** Write a line of code. */
	void WriteLn( wxString code = wxEmptyString, bool keepIndents = false );

	/** Writes a text string into the code. */
	void Write( wxString code );

	/** Deletes all the code previously written. */
	virtual void Clear() = 0;
};

/**
 * @class TCCodeWriter
 * @todo Description needed.
 */
class TCCodeWriter : public CodeWriter
{
private:
	wxStyledTextCtrl *m_tc; /**< Control associated to display code. */

protected:
	/**
	 * @todo Description needed.
	 * @param code 
	 */
	void DoWrite( wxString code );

public:
	/** Constructor. */
	TCCodeWriter();

	/**
	 * Constructor.
	 * @param tc Pointer to associated text control to display code.
	 */
	TCCodeWriter( wxStyledTextCtrl *tc );

	/** Sets text control to assign to display code. */
	void SetTextCtrl( wxStyledTextCtrl* tc );

	/** Clear code inside text control. */
	void Clear();
};

/**
 * @class StringCodeWriter
 * @todo Description needed.
 */
class StringCodeWriter : public CodeWriter
{
protected:
	wxString m_buffer; 				/**< @todo Description needed. */
	void DoWrite( wxString code ); 	/**< @todo Description needed. */

public:
	/** Constructor. */
	StringCodeWriter();

	/** Clear code inside text control. */
	void Clear();

	/** @todo Description needed. */
	wxString GetString();
};

/**
 * @class FileCodeWriter
 * @todo Description needed.
 */
class FileCodeWriter : public StringCodeWriter
{
private:
	wxString m_filename; 	/**< @todo Description needed. */
	bool m_useMicrosoftBOM; /**< @todo Description needed. */
	bool m_useUtf8; 		/**< @todo Description needed. */

protected:
	void WriteBuffer(); 	/**< @todo Description needed. */

public:
	/**
	 * Constructor.
	 * @todo Description needed.
	 * @param file 				
	 * @param useMicrosoftBOM 	
	 * @param useUtf8 			
	 */
	FileCodeWriter( const wxString &file, bool useMicrosoftBOM = false, bool useUtf8 = true );

	/** Destructor. */
	~FileCodeWriter();

	/** Clear code inside text control. */
	void Clear();
};

#endif //__CODEWRITER_H__
