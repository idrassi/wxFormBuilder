#ifndef __PREFS_H__
#define __PREFS_H__

#include "prefsdialog.h"

class PrefsPageGUI : public _PrefsPageGUI
{
public:
	PrefsPageGUI( wxWindow* parent );
};

class PrefsPageGUICaps : public _PrefsPageGUICaps
{
public:
	PrefsPageGUICaps( wxWindow* parent );

	void SetValues();

private:
	void OnUpdateUI        ( wxUpdateUIEvent& event );
	void OnToggleCustPrefs ( wxCommandEvent&  event );
};

class PrefsPageLocale : public _PrefsPageLocale
{
public:
	PrefsPageLocale( wxWindow* parent );

	void SetValues();

private:
	void OnUpdateUI     ( wxUpdateUIEvent& event );
	void OnToggleLocale ( wxCommandEvent&  event );
};

class PrefsDialog : public _PrefsDialog
{
public:
	PrefsDialog( wxWindow* parent );

	void SaveConfig();
	void SetValues();

private:
	void OnUpdateUI( wxUpdateUIEvent& event );
	void OnOK      ( wxCommandEvent&  event );
	void OnApply   ( wxCommandEvent&  event );

	PrefsPageGUICaps* pnlGuiCaps;
	PrefsPageLocale*  pnlLang;
};

#endif // __PREFS_H__
