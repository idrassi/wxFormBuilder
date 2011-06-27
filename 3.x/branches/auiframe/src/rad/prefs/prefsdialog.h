///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  7 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __prefsdialog__
#define __prefsdialog__

#include <wx/intl.h>

#include <wx/string.h>
#include <wx/checkbox.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/stattext.h>
#include <wx/bmpcbox.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/statbox.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/spinctrl.h>
#include <wx/choice.h>
#include <wx/clrpicker.h>
#include <wx/treebook.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class _PrefsDialog
///////////////////////////////////////////////////////////////////////////////
class _PrefsDialog : public wxDialog 
{
	private:
	
	protected:
		wxTreebook* tbkPrefs;
		wxPanel* pnlLang;
		wxPanel* pnlBoxLang;
		wxCheckBox* chkLang;
		wxStaticText* lblLang;
		wxBitmapComboBox* bcbLang;
		wxPanel* pnlGUI;
		wxCheckBox* chkCustPrefs;
		wxStaticText* txtCaptHeight;
		wxSpinCtrl* spnCaptHeight;
		
		
		wxStaticText* txtGrdtDir;
		wxChoice* choGrdtDir;
		
		
		wxStaticText* txtNormCapt;
		wxColourPickerCtrl* cpkNormCapt;
		wxStaticText* txtActvCapt;
		wxColourPickerCtrl* cpkActvCapt;
		
		
		wxStaticText* txtNormGrdt;
		wxColourPickerCtrl* cpkNormGrdt;
		wxStaticText* txtActvGrdt;
		wxColourPickerCtrl* cpkActvGrdt;
		
		
		wxStaticText* txtNormCaptText;
		wxColourPickerCtrl* cpkNormCaptText;
		wxStaticText* txtActvCaptText;
		wxColourPickerCtrl* cpkActvCaptText;
		wxStdDialogButtonSizer* buttonSizer;
		wxButton* buttonSizerOK;
		wxButton* buttonSizerApply;
		wxButton* buttonSizerCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnToggleLocale( wxCommandEvent& event ) = 0;
		virtual void OnClose( wxCommandEvent& event ) = 0;
		
	
	public:
		
		_PrefsDialog( wxWindow* parent, wxWindowID id = wxID_PREFERENCES, const wxString& title = _("Preferences"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( wxDefaultSize ), long style = wxCAPTION|wxCLOSE_BOX|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER|wxSYSTEM_MENU ); 
		~_PrefsDialog();
	
};

#endif //__prefsdialog__
