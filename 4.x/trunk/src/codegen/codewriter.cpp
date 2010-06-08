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

#include "codewriter.h"
#include "md5/md5.hh"
#include "utils/wxfbexception.h"
#include "utils/typeconv.h"

#include <wx/file.h>
#include <wx/regex.h>
#include <wx/tokenzr.h>

#include <cstring>
#include <fstream>

CodeWriter::CodeWriter()
:
m_indent( 0 ),
m_cols( 0 )
{
}

CodeWriter::~CodeWriter()
{
}

int CodeWriter::GetIndentSize()
{
	return 1;
}

void CodeWriter::Indent()
{
	m_indent += GetIndentSize();
}

void CodeWriter::Unindent()
{
	m_indent -= GetIndentSize();

	if ( m_indent < 0 )
	{
		m_indent = 0;
	}
}

void CodeWriter::WriteLn( wxString code )
{
	// It will not be allowed newlines (carry return) inside "code"
	// If there was anyone, then FixWrite gets the string and breaks it
	// in different lines, inserting them one after another using WriteLn
	if ( !StringOk( code ) )
	{
		FixWrite( code );
	}
	else
	{
		Write( code );
		#if defined( __WXMSW__ )
			Write( "\r\n" );
		#elif defined( __WXMAC__ )
			Write( "\r" );
		#else
			Write( "\n" );
		#endif
		m_cols = 0;
	}
}

bool CodeWriter::StringOk( wxString s )
{
	return ( s.find( "\n", 0 ) == wxString::npos );
}

void CodeWriter::FixWrite( wxString s )
{
	wxRegEx reIndent( "%TAB%\\s*", wxRE_ADVANCED );
	wxStringTokenizer tkz( s, "\n", wxTOKEN_RET_EMPTY_ALL );

	while ( tkz.HasMoreTokens() )
	{
		wxString line = tkz.GetNextToken();

		line.Trim( false );
		line.Trim( true );

		// replace indentations defined in code templates by #indent and #unindent macros...
		reIndent.Replace( &line, "\t" );
		WriteLn( line );
	}
}


void CodeWriter::Write( wxString code )
{
	if ( m_cols == 0 )
	{
		// Inserting indents
		for ( int i = 0; i < m_indent; i++ )
		{
			DoWrite( "\t" );
		}
		m_cols = m_indent;
	}
	DoWrite( code );
}

TCCodeWriter::TCCodeWriter()
:
m_tc( 0 )
{
}

TCCodeWriter::TCCodeWriter( wxStyledTextCtrl* tc )
{
	SetTextCtrl( tc );
}

void TCCodeWriter::SetTextCtrl( wxStyledTextCtrl* tc )
{
	m_tc = tc;
}

void TCCodeWriter::DoWrite( wxString code )
{
	if ( m_tc )
		m_tc->AddText( code );
}

void TCCodeWriter::Clear()
{
	if ( m_tc )
		m_tc->ClearAll(); //*!*
}

StringCodeWriter::StringCodeWriter()
{
}

void StringCodeWriter::DoWrite( wxString code )
{
	m_buffer += code;
}

void StringCodeWriter::Clear()
{
	m_buffer.clear();
}

wxString StringCodeWriter::GetString()
{
	return m_buffer;
}

FileCodeWriter::FileCodeWriter( const wxString &file, bool useMicrosoftBOM, bool useUtf8 )
:
m_filename( file ),
m_useMicrosoftBOM( useMicrosoftBOM ),
m_useUtf8( useUtf8 )
{
	Clear();
}

FileCodeWriter::~FileCodeWriter()
{
	WriteBuffer();
}

void FileCodeWriter::WriteBuffer()
{
	#ifdef __WXMSW__
		unsigned char microsoftBOM[3] = { 0xEF, 0xBB, 0xBF };
	#endif

	// Compare buffer with existing file (if any) to determine if
	// writing the file is necessary
	bool shouldWrite = true;

	std::ifstream file( m_filename.mb_str( wxConvFile ), std::ios::binary | std::ios::in );

	std::string buf;

	if ( file )
	{
		MD5 diskHash( file );
		unsigned char* diskDigest = diskHash.raw_digest();

		MD5 bufferHash;
		#ifdef __WXMSW__
			if ( m_useMicrosoftBOM )
			{
				bufferHash.update( microsoftBOM, 3 );
			}
		#endif
		const std::string& data = m_useUtf8 ? _STDSTR( m_buffer ) : _ANSISTR( m_buffer );

		if (!m_useUtf8) buf = data;

		bufferHash.update( reinterpret_cast< const unsigned char* >( data.c_str() ), data.size() );

		bufferHash.finalize();

		unsigned char* bufferDigest = bufferHash.raw_digest();

		shouldWrite = ( 0 != std::memcmp( diskDigest, bufferDigest, 16 ) );

		delete [] diskDigest;

		delete [] bufferDigest;
	}

	if ( shouldWrite )
	{
		wxFile file;
		if ( !file.Create( m_filename, true ) )
		{
			wxLogError( _("Unable to create file: %s"), m_filename.c_str() );
			return;
		}

		#ifdef __WXMSW__
		if ( m_useMicrosoftBOM )
		{
			file.Write( microsoftBOM, 3 );
		}
		#endif

		if (!m_useUtf8)
            file.Write( buf.c_str(), buf.length() );
        else
            file.Write( m_buffer );
	}
}

void FileCodeWriter::Clear()
{
	StringCodeWriter::Clear();

	if ( ::wxFileExists( m_filename ) )
	{
		// check for write access to the target file
		if ( !wxFile::Access( m_filename, wxFile::write ) )
		{
			THROW_WXFBEX( _("Unable to write file: ") << m_filename );
		}
	}
	else
	{
		wxFile file;
		if ( !file.Create( m_filename, true ) )
		{
			THROW_WXFBEX( _("Unable to create file: ") << m_filename );
		}
	}
}