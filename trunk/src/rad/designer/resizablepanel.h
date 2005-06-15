#ifndef RESIZABLEPANEL_H
#define RESIZABLEPANEL_H

#include <wx/wxprec.h>
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/event.h>

BEGIN_DECLARE_EVENT_TYPES()
    DECLARE_EVENT_TYPE(wxEVT_PANEL_RESIZED, 6000)
END_DECLARE_EVENT_TYPES()

#define EVT_PANEL_RESIZED(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY( \
        wxEVT_PANEL_RESIZED, id, wxID_ANY, \
        (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxCommandEventFunction, &fn ), \
        (wxObject *) NULL \
    ),

class ResizablePanel : public wxPanel
{
    enum{
      NONE,
      RIGHTBOTTOM,
      RIGHT,
      BOTTOM
    } m_sizing;
    
    int m_curX, m_curY, m_difX, m_difY;
    int m_resizeBorder;
    wxSize m_minSize;
  public:
    ResizablePanel(wxWindow *parent, const wxPoint& pos = wxDefaultPosition, 
      const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL);
    
    void SetResizeBorder(int border);
    int GetResizeBorder();
    void SetMinSize(const wxSize& size);
    wxSize GetMinSize();
    
    void OnMouseMotion(wxMouseEvent& e);
    void OnLeftDown(wxMouseEvent& e);
    void OnSetCursor(wxSetCursorEvent& e);
    void OnLeftUp(wxMouseEvent& e);
    void OnSize(wxSizeEvent& e);
    
    DECLARE_EVENT_TABLE()
};

#endif
