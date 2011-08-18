///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  6 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __prefsdialog__
#define __prefsdialog__

#include <wx/intl.h>

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/checkbox.h>
#include <wx/spinctrl.h>
#include <wx/choice.h>
#include <wx/statbox.h>
#include <wx/clrpicker.h>
#include <wx/bmpcbox.h>
#include <wx/treebook.h>
#include <wx/imaglist.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

#define ID_PREFS_GUI 10000
#define ID_PREFS_CAPTIONS 10001
#define ID_PREFS_LOCALE 10002

///////////////////////////////////////////////////////////////////////////////
/// Class _PrefsPageGUI
///////////////////////////////////////////////////////////////////////////////
class _PrefsPageGUI : public wxPanel 
{
	private:
	
	protected:
		wxCheckBox* chkUseAUI;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnUpdateUI( wxUpdateUIEvent& event ) = 0;
		
	
	public:
		
		_PrefsPageGUI( wxWindow* parent, wxWindowID id = ID_PREFS_GUI, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxTAB_TRAVERSAL ); 
		~_PrefsPageGUI();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _PrefsPageGUICaps
///////////////////////////////////////////////////////////////////////////////
class _PrefsPageGUICaps : public wxPanel 
{
	private:
	
	protected:
		wxCheckBox* chkCustPrefs;
		wxPanel* pnlCaptMetrics;
		wxStaticText* txtCaptHeight;
		wxSpinCtrl* spnCaptHeight;
		wxStaticText* txtGrdtDir;
		wxChoice* choGrdtDir;
		wxPanel* pnlCaptColors;
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
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnUpdateUI( wxUpdateUIEvent& event ) = 0;
		virtual void OnToggleCustPrefs( wxCommandEvent& event ) = 0;
		
	
	public:
		
		_PrefsPageGUICaps( wxWindow* parent, wxWindowID id = ID_PREFS_CAPTIONS, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxTAB_TRAVERSAL ); 
		~_PrefsPageGUICaps();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _PrefsPageLocale
///////////////////////////////////////////////////////////////////////////////
class _PrefsPageLocale : public wxPanel 
{
	private:
	
	protected:
		wxPanel* pnlBoxLang;
		wxCheckBox* chkLang;
		wxStaticText* lblLang;
		wxBitmapComboBox* bcbLang;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnUpdateUI( wxUpdateUIEvent& event ) = 0;
		virtual void OnToggleLocale( wxCommandEvent& event ) = 0;
		
	
	public:
		
		_PrefsPageLocale( wxWindow* parent, wxWindowID id = ID_PREFS_LOCALE, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxTAB_TRAVERSAL ); 
		~_PrefsPageLocale();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _PrefsDialog
///////////////////////////////////////////////////////////////////////////////
class _PrefsDialog : public wxDialog 
{
	private:
	
	protected:
		wxTreebook* tbkPrefs;
		wxStdDialogButtonSizer* buttonSizer;
		wxButton* buttonSizerOK;
		wxButton* buttonSizerApply;
		wxButton* buttonSizerCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnUpdateUI( wxUpdateUIEvent& event ) = 0;
		
	
	public:
		
		_PrefsDialog( wxWindow* parent, wxWindowID id = wxID_PREFERENCES, const wxString& title = _("Preferences"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxCAPTION|wxCLOSE_BOX|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER|wxSYSTEM_MENU ); 
		~_PrefsDialog();
	
};

#endif //__prefsdialog__
