///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 28 2007)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __gui__
#define __gui__

#include <wx/wx.h>

#include <wx/wxIndustrialControls/LCDWindow.h>
#include <wx/wxIndustrialControls/LCDClock.h>
#include <wx/wxIndustrialControls/AngularRegulator.h>
#include <wx/wxIndustrialControls/AngularMeter.h>
#include <wx/wxIndustrialControls/LinearMeter.h>
#include <wx/wxIndustrialControls/LinearRegulator.h>
#include <wx/panel.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class G_MainFrame
///////////////////////////////////////////////////////////////////////////////
class G_MainFrame : public wxFrame 
{
	private:
	
	protected:
		wxPanel* m_panel1;
		kwxLCDDisplay* m_lcdDisplay1;
		kwxLCDClock* m_lcdClock1;
		kwxAngularRegulator* m_angRegulator1;
		kwxAngularMeter* m_angMeter1;
		kwxLinearMeter* m_linMeter1;
		kwxLinearRegulator* m_linRegulator1;
	
	public:
		G_MainFrame( wxWindow* parent, int id = wxID_ANY, wxString title = wxT("wxIndustrialControls Test"), wxPoint pos = wxDefaultPosition, wxSize size = wxSize( -1,-1 ), int style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
	
};

#endif //__gui__
