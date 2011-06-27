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
#include "title.h"
#include "utils/typeconv.h"

#include <wx/config.h>
#include <wx/dcbuffer.h>

BEGIN_EVENT_TABLE( Title, wxPanel )
	EVT_PAINT( Title::onPaint )
	EVT_SIZE( Title::onSize )
	EVT_CLOSE( Title::onClose )
END_EVENT_TABLE()

Title::Title(wxWindow *parent,const wxString &title) : wxPanel(parent,-1)
{
/*
	wxBoxSizer* sizer = new wxBoxSizer( wxVERTICAL );
	m_lblCaptText = new wxStaticText(this,-1,title);//,wxDefaultPosition,wxDefaultSize,wxSIMPLE_BORDER);
*/
	m_strCaptText = title;

	wxConfigBase* config = wxConfigBase::Get();
	config->Read( wxT("/preferences/gui/CaptionGradientVertical"), &m_bGradVert, false );
	config->Read( wxT("/preferences/gui/CaptionHeight"), &m_hgtCaptText, 18 );

	m_colCaptText = getColourFromConfig( wxT("/preferences/gui/CaptionTextColour"),           wxSYS_COLOUR_CAPTIONTEXT );
	m_colActvCapt = getColourFromConfig( wxT("/preferences/gui/CaptionActiveColour"),         wxSYS_COLOUR_ACTIVECAPTION );
	m_colActvGrdt = getColourFromConfig( wxT("/preferences/gui/CaptionActiveGradientColour"), wxSYS_COLOUR_GRADIENTACTIVECAPTION );

	SetBackgroundColour( m_colActvCapt );
/*
	m_lblCaptText->SetBackgroundColour( m_colActvCapt );
	m_lblCaptText->SetForegroundColour( m_colCaptText );
	m_lblCaptText->SetFont( wxFont( 8, wxSWISS, wxNORMAL, wxBOLD, 0, wxT("") ) );
*/
	SetSize( -1, m_hgtCaptText );
/*
	sizer->Add( m_lblCaptText, 0, wxALL | wxEXPAND, 2 );
	SetSizer(sizer);
	Fit();*/
}

wxWindow * Title::CreateTitle (wxWindow *inner, const wxString &title)
{
	wxWindow *parent = inner->GetParent();

	wxPanel *container = new wxPanel(parent, -1);
	Title *titleWin = new Title(container,title);
	inner->Reparent(container);

	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(titleWin,0,wxEXPAND);
	sizer->Add(inner,1,wxEXPAND);
	container->SetSizer(sizer);

	return container;
}

wxColour Title::getColourFromConfig( const wxString& confpath, wxSystemColour sys_colour )
{
	wxConfigBase* config = wxConfigBase::Get();
	wxString sColour;
	if ( config->Read( confpath, &sColour ) )
	{
		wxString sR, sG, sB; wxChar comma = wxT(',');
		int iR = -1; int iG = -1; int iB = -1;

		sR = sColour.BeforeFirst( comma );
		sG = sColour.AfterFirst( comma ).BeforeLast( comma );;
		sB = sColour.AfterLast( comma );

		if ( !sR.IsEmpty() && !sG.IsEmpty() && !sB.IsEmpty() )
		{
			iR = wxAtoi( sR ); iG = wxAtoi( sG ); iB = wxAtoi( sB );
		}

		if ( (iR >= 0 || iR <= 255) && (iG >= 0 || iG <= 255) && (iB >= 0 || iB <= 255) )
		{
			return wxColour( iR, iG, iB );
		}
	}
	return wxSystemSettings::GetColour( sys_colour );
}

void Title::drawTitle( wxDC &dc )
{
	int width, height, length1, length2;
	GetSize( &width, &height );

	length1 = ( m_bGradVert == true ? width : height );
	length2 = ( m_bGradVert == true ? height : width );

	float incR = ( float )( m_colActvGrdt.Red()   - m_colActvCapt.Red() )   / length1;
	float incG = ( float )( m_colActvGrdt.Green() - m_colActvCapt.Green() ) / length1;
	float incB = ( float )( m_colActvGrdt.Blue()  - m_colActvCapt.Blue() )  / length1;

	float colourR = m_colActvCapt.Red();
	float colourG = m_colActvCapt.Green();
	float colourB = m_colActvCapt.Blue();

	wxColour colour;
	wxPen    pen;

	for ( int i = 0; i < length2; i++ )
	{
		colour.Set( ( unsigned char )colourR, ( unsigned char )colourG, ( unsigned char )colourB );
		pen.SetColour( colour );
		dc.SetPen( pen );

		if ( m_bGradVert )
			dc.DrawLine( i, 0, i, height );
		else
			dc.DrawLine( 0, i, width, i );

		colourR += incR;
		colourG += incG;
		colourB += incB;
	}

	// Draw title text
	wxFont font = dc.GetFont();
	font.SetPointSize( 9 );
	font.SetWeight( wxBOLD );

	dc.SetTextForeground( m_colCaptText );
	dc.SetFont( font );

	// text vertical adjustment
	wxCoord tw, th;
	dc.GetTextExtent( m_strCaptText, &tw, &th );
	int marginH = ( height - th ) / 2; 
	dc.DrawLabel( m_strCaptText, wxRect( marginH + 2, marginH, tw, th ) );
}

void Title::onSize ( wxSizeEvent& )
{
	wxClientDC dc( this );
	wxBufferedDC bdc( &dc, GetClientSize() );
	drawTitle( bdc );
}

void Title::onPaint ( wxPaintEvent& )
{
	wxPaintDC dc( this );
	wxBufferedDC bdc( &dc, GetClientSize() );
	drawTitle( bdc );
}

void Title::onClose ( wxCloseEvent& )
{
	wxConfigBase* config = wxConfigBase::Get();
	config->Write( wxT("/preferences/gui/CaptionActiveColour"),         TypeConv::ColourToString( m_colActvCapt ) );
	config->Write( wxT("/preferences/gui/CaptionActiveGradientColour"), TypeConv::ColourToString( m_colActvGrdt ) );
	config->Write( wxT("/preferences/gui/CaptionTextColour"),           TypeConv::ColourToString( m_colCaptText ) );
	config->Write( wxT("/preferences/gui/CaptionGradientVertical"),     m_bGradVert );
	config->Write( wxT("/preferences/gui/CaptionHeight"),               m_hgtCaptText );
}
