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
#ifndef __TITLE_H__
#define __TITLE_H__

#include <wx/wx.h>

class Title : public wxPanel
{
private:
	void drawTitle( wxDC &dc );
	bool isDark( const wxColour& color );

	void onPaint( wxPaintEvent &event );

	int      m_hgtCaptText;
	bool     m_bUseCustPrefs;
	bool     m_bGradVert;
	wxString m_strCaptText;
	wxColour m_colActvText;
	wxColour m_colActvCapt;
	wxColour m_colActvGrdt;
	wxColour m_colNormText;
	wxColour m_colNormCapt;
	wxColour m_colNormGrdt;

	DECLARE_EVENT_TABLE()

public:
	Title(wxWindow *parent,const wxString &title=wxT("No title"));

	static wxWindow* CreateTitle (wxWindow *inner, const wxString &title);
};

#endif //__TITLE_H__
