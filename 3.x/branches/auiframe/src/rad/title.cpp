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
#include "rad/prefs/settings.h"

#include <wx/dcbuffer.h>

BEGIN_EVENT_TABLE( Title, wxPanel )
	EVT_PAINT( Title::onPaint )
END_EVENT_TABLE()

Title::Title( wxWindow *parent, const wxString &title ) : wxPanel( parent, wxID_ANY )
{
	m_strCaptText = title;

	wxFBSettings* conf = wxFBSettings::Get();

	m_bUseCustPrefs = conf->UseCustomPrefs;
	m_bGradVert     = conf->UseGradientVertical;
	m_hgtCaptText   = conf->CaptionTextHeight;
	m_colActvCapt   = conf->CaptionActiveColor;
	m_colActvGrdt   = conf->CaptionActiveColorGradient;
	m_colActvText   = conf->CaptionActiveColorText;
	m_colNormCapt   = conf->CaptionNormalColor;
	m_colNormGrdt   = conf->CaptionNormalColorGradient;
	m_colNormText   = conf->CaptionActiveColorText;

	this->SetBackgroundColour( m_colActvCapt );
	this->SetMinSize( wxSize( -1, m_hgtCaptText ) );
	this->Layout();
}

wxWindow * Title::CreateTitle ( wxWindow *inner, const wxString &title )
{
	wxWindow *parent = inner->GetParent();

	wxPanel *container = new wxPanel( parent, wxID_ANY );
	Title *titleWin = new Title( container, title );
	inner->Reparent( container );

	wxBoxSizer *sizer = new wxBoxSizer( wxVERTICAL );
	sizer->Add( titleWin, 0, wxEXPAND );
	sizer->Add( inner, 1, wxEXPAND );
	container->SetSizer( sizer );

	return container;
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

		if ( m_bUseCustPrefs )
		{
			if ( m_bGradVert )
				dc.DrawLine( i, 0, i, height );
			else
				dc.DrawLine( 0, i, width, i );

			colourR += incR;
			colourG += incG;
			colourB += incB;
		}
		else
			dc.DrawLine( 0, i, width, i );
	}

	// Draw title text
	if ( isDark( m_colActvText ) && isDark( m_colActvGrdt ) && !m_bUseCustPrefs )
		dc.SetTextForeground( *wxWHITE );

	else
		dc.SetTextForeground( m_colActvText );

	dc.SetFont( wxFont(8, wxSWISS, wxNORMAL, wxBOLD, 0, wxT("")) );

	// text vertical adjustment
	wxCoord tw, th;
	dc.GetTextExtent( m_strCaptText, &tw, &th );
	int marginH = ( height - th ) / 2; 
	dc.DrawLabel( m_strCaptText, wxRect( marginH + 2, marginH, tw, th ) );
}

bool Title::isDark(const wxColour& color)
{
	int evg = (color.Red() + color.Green() + color.Blue())/3;
	if (evg < 127)
		return true;

	return false;
}

void Title::onPaint ( wxPaintEvent& WXUNUSED(event) )
{
	wxPaintDC dc( this );
	dc.SetFont( GetFont() );
	wxBufferedDC bdc( &dc, GetClientSize() );
	drawTitle( bdc );
}
