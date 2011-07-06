#ifndef __WXFB_AUITBARART_H__
#define __WXFB_AUITBARART_H__

#include <wx/dc.h>
#include <wx/gdicmn.h>
#include <wx/sizer.h>
#include <wx/aui/auibar.h>

class wxFBAuiToolBarArt : public wxAuiDefaultToolBarArt
{
public:
	wxFBAuiToolBarArt();
	virtual ~wxFBAuiToolBarArt();

    virtual void DrawOverflowButton( wxDC& dc, wxWindow* wnd,
                                     const wxRect& rect, int state );
};

#endif //__WXFB_AUITBARART_H__
