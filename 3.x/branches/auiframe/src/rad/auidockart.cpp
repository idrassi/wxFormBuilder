#include "auidockart.h"

wxFBAuiDockArt::wxFBAuiDockArt()
{
}

wxFBAuiDockArt::~wxFBAuiDockArt()
{
}

void wxFBAuiDockArt::DrawCaption( wxDC& dc, wxWindow *window,
                                  const wxString& text, const wxRect& rect,
                                  wxAuiPaneInfo& pane)
{
	wxString caption;

	if ( pane.name == wxT("palette") )
	{
		caption = _("Component Palette");
	}
	else if ( pane.name == wxT("editor") )
	{
		caption = _("Editor");
	}
	else if ( pane.name == wxT("objtree") )
	{
		caption = _("Object Tree");
	}
	if ( pane.name == wxT("inspector") )
	{
		caption = _("Object Properties");
	}

	wxAuiDefaultDockArt::DrawCaption( dc, window, caption, rect, pane );
}
