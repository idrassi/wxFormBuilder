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

#include "codeeditor.h"

#include <wx/fdrepdlg.h>
#include <wx/msgdlg.h>

BEGIN_EVENT_TABLE ( CodeEditor,  wxPanel )
	EVT_STC_MARGINCLICK( wxID_ANY, CodeEditor::OnMarginClick )
	EVT_FIND( wxID_ANY, CodeEditor::OnFind )
	EVT_FIND_NEXT( wxID_ANY, CodeEditor::OnFind )
END_EVENT_TABLE()

CodeEditor::CodeEditor( wxWindow *parent, int id )
:
wxPanel( parent, id )
{
	wxBoxSizer *sizer = new wxBoxSizer( wxVERTICAL );
	m_code = new wxStyledTextCtrl( this, -1 );

	// Line Numbers
	m_code->SetMarginType( 0, wxSTC_MARGIN_NUMBER );
	m_code->SetMarginWidth( 0, m_code->TextWidth ( wxSTC_STYLE_LINENUMBER, "_99999") );

	// markers
	m_code->MarkerDefine 		( wxSTC_MARKNUM_FOLDER, 		wxSTC_MARK_BOXPLUS );
	m_code->MarkerSetBackground ( wxSTC_MARKNUM_FOLDER, 		wxColour("BLACK") );
	m_code->MarkerSetForeground ( wxSTC_MARKNUM_FOLDER, 		wxColour("WHITE") );
	m_code->MarkerDefine 		( wxSTC_MARKNUM_FOLDEROPEN, 	wxSTC_MARK_BOXMINUS );
	m_code->MarkerSetBackground ( wxSTC_MARKNUM_FOLDEROPEN, 	wxColour("BLACK") );
	m_code->MarkerSetForeground ( wxSTC_MARKNUM_FOLDEROPEN, 	wxColour("WHITE") );
	m_code->MarkerDefine 		( wxSTC_MARKNUM_FOLDERSUB, 		wxSTC_MARK_EMPTY );
	m_code->MarkerDefine 		( wxSTC_MARKNUM_FOLDEREND, 		wxSTC_MARK_BOXPLUS );
	m_code->MarkerSetBackground ( wxSTC_MARKNUM_FOLDEREND, 		wxColour("BLACK") );
	m_code->MarkerSetForeground ( wxSTC_MARKNUM_FOLDEREND, 		wxColour("WHITE") );
	m_code->MarkerDefine 		( wxSTC_MARKNUM_FOLDEROPENMID, 	wxSTC_MARK_BOXMINUS );
	m_code->MarkerSetBackground ( wxSTC_MARKNUM_FOLDEROPENMID, 	wxColour("BLACK") );
	m_code->MarkerSetForeground ( wxSTC_MARKNUM_FOLDEROPENMID, 	wxColour("WHITE") );
	m_code->MarkerDefine 		( wxSTC_MARKNUM_FOLDERMIDTAIL, 	wxSTC_MARK_EMPTY );
	m_code->MarkerDefine 		( wxSTC_MARKNUM_FOLDERTAIL, 	wxSTC_MARK_EMPTY );

	// folding
	m_code->SetMarginType ( 1, wxSTC_MARGIN_SYMBOL );
	m_code->SetMarginMask ( 1, wxSTC_MASK_FOLDERS );
	m_code->SetMarginWidth ( 1, 16 );
	m_code->SetMarginSensitive ( 1, true );

	m_code->SetProperty( "fold", "1" );
	m_code->SetProperty( "fold.comment", "1" );
	m_code->SetProperty( "fold.compact", "1" );
	m_code->SetProperty( "fold.preprocessor", "1" );
	m_code->SetProperty( "fold.html", "1" );
	m_code->SetProperty( "fold.html.preprocessor", "1" );
	m_code->SetFoldFlags( wxSTC_FOLDFLAG_LINEBEFORE_CONTRACTED | wxSTC_FOLDFLAG_LINEAFTER_CONTRACTED );

	m_code->SetIndentationGuides( true );

	m_code->SetMarginWidth( 2, 0 );
	sizer->Add( m_code, 1, wxEXPAND | wxALL );
	SetSizer( sizer );
}

void CodeEditor::OnMarginClick ( wxStyledTextEvent &event )
{
	if ( event.GetMargin() == 1 )
	{
		int lineClick = m_code->LineFromPosition ( event.GetPosition() );
		int levelClick = m_code->GetFoldLevel ( lineClick );

		if ( ( levelClick & wxSTC_FOLDLEVELHEADERFLAG ) > 0 )
		{
			m_code->ToggleFold ( lineClick );
		}
	}
}

wxStyledTextCtrl* CodeEditor::GetTextCtrl()
{
	return m_code;
}

void CodeEditor::OnFind( wxFindDialogEvent& event )
{
	int wxflags = event.GetFlags();
	int sciflags = 0;
	if ( (wxflags & wxFR_WHOLEWORD) != 0 )
	{
		sciflags |= wxSTC_FIND_WHOLEWORD;
	}
	if ( (wxflags & wxFR_MATCHCASE) != 0 )
	{
		sciflags |= wxSTC_FIND_MATCHCASE;
	}
	int result;
	if ( (wxflags & wxFR_DOWN) != 0 )
	{
		m_code->SetSelectionStart( m_code->GetSelectionEnd() );
		m_code->SearchAnchor();
		result = m_code->SearchNext( sciflags, event.GetFindString() );
	}
	else
	{
		m_code->SetSelectionEnd( m_code->GetSelectionStart() );
		m_code->SearchAnchor();
		result = m_code->SearchPrev( sciflags, event.GetFindString() );
	}
	if ( wxSTC_INVALID_POSITION == result )
	{
		wxMessageBox( wxString::Format( _("\"%s\" not found!"), event.GetFindString().c_str() ),
										_("Not Found!"), wxICON_ERROR, (wxWindow*)event.GetClientData() );
	}
	else
	{
		m_code->EnsureCaretVisible();
	}
}
