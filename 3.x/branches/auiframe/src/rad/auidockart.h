#ifndef __WXFB_AUIDOCKART_H__
#define __WXFB_AUIDOCKART_H__

#include <wx/aui/framemanager.h>
#include <wx/aui/dockart.h>

class wxFBAuiDockArt : public wxAuiDefaultDockArt
{
public:
	wxFBAuiDockArt();
	virtual ~wxFBAuiDockArt();

	void DrawCaption( wxDC& dc, wxWindow *window,
                      const wxString& text, const wxRect& rect,
                      wxAuiPaneInfo& pane);
};

#endif //__WXFB_AUIDOCKART_H__
