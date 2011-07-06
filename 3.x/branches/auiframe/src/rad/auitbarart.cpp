#include "auitbarart.h"

#include <wx/aui/framemanager.h>
#include <wx/wxFlatNotebook/fnb_resources.h>

wxFBAuiToolBarArt::wxFBAuiToolBarArt()
{
}

wxFBAuiToolBarArt::~wxFBAuiToolBarArt()
{
}

void wxFBAuiToolBarArt::DrawOverflowButton( wxDC& dc, wxWindow* wnd,
                                            const wxRect& rect, int state)
{
	switch( state )
	{
	case wxAUI_BUTTON_STATE_HOVER:
		m_overflow_bmp = wxBitmap(down_arrow_hilite_xpm);
		break;
	case wxAUI_BUTTON_STATE_PRESSED:
		m_overflow_bmp = wxBitmap(down_arrow_pressed_xpm);
		break;
	case wxAUI_BUTTON_STATE_NORMAL:
	default:
		m_overflow_bmp = wxBitmap(down_arrow_xpm);
		break;
	}

	wxRect _rect = rect;
	_rect.x = _rect.x - 4;
	_rect.y = _rect.y + 10;
	_rect.height = 10;
	_rect.width  = 10;

	m_overflow_bmp.SetMask( new wxMask( m_overflow_bmp, wxColour( 0, 128, 128 ) ) );

	wxAuiDefaultToolBarArt::DrawOverflowButton( dc, wnd, _rect, state );
}