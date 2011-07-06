#include "prefs.h"

#include "settings.h"
#include "icons/flags/default.xpm"
#include "icons/flags/de.xpm"
#include "icons/flags/en_GB.xpm"
#include "icons/flags/en_US.xpm"
#include "icons/flags/it.xpm"

#include "rad/bitmaps.h"

PrefsPageGUI::PrefsPageGUI( wxWindow* parent ) : _PrefsPageGUI( parent )
{
}

PrefsPageGUICaps::PrefsPageGUICaps( wxWindow* parent )
:
_PrefsPageGUICaps( parent )
{
	wxFBSettings* conf = wxFBSettings::Get();

	chkCustPrefs->SetValue      ( conf->UseCustomPrefs );
	pnlCaptMetrics->Enable      ( conf->UseCustomPrefs );
	pnlCaptColors->Enable       ( conf->UseCustomPrefs );
	choGrdtDir->SetSelection    ( conf->UseGradientVertical );
	spnCaptHeight->SetValue     ( conf->CaptionTextHeight );
	cpkActvCapt->SetColour      ( conf->CaptionActiveColor );
	cpkActvGrdt->SetColour      ( conf->CaptionActiveColorGradient );
	cpkActvCaptText->SetColour  ( conf->CaptionActiveColorText );
	cpkNormCapt->SetColour      ( conf->CaptionNormalColor );
	cpkNormGrdt->SetColour      ( conf->CaptionNormalColorGradient );
	cpkNormCaptText->SetColour  ( conf->CaptionNormalColorText );
}

void PrefsPageGUICaps::SetValues()
{
	wxFBSettings* conf = wxFBSettings::Get();

	conf->CaptionActiveColor         = cpkActvCapt->GetColour();
	conf->CaptionActiveColorGradient = cpkActvGrdt->GetColour();
	conf->CaptionActiveColorText     = cpkActvCaptText->GetColour();
	conf->CaptionNormalColor         = cpkNormCapt->GetColour();
	conf->CaptionNormalColorGradient = cpkNormGrdt->GetColour();
	conf->CaptionNormalColorText     = cpkNormCaptText->GetColour();
	conf->UseGradientVertical        = choGrdtDir->GetSelection();
	conf->UseCustomPrefs             = chkCustPrefs->IsChecked();
	conf->CaptionTextHeight          = spnCaptHeight->GetValue();
}

void PrefsPageGUICaps::OnUpdateUI( wxUpdateUIEvent& event )
{
	wxFBSettings* conf  = wxFBSettings::Get();

	conf->IsDirty = conf->UseCustomPrefs             != chkCustPrefs->IsChecked()   ||
	                conf->UseGradientVertical        != choGrdtDir->GetSelection()  ||
	                conf->CaptionTextHeight          != spnCaptHeight->GetValue()   ||
	                conf->CaptionActiveColor         != cpkActvCapt->GetColour()    ||
	                conf->CaptionActiveColorGradient != cpkActvGrdt->GetColour()    ||
	                conf->CaptionActiveColorText     != cpkActvCaptText->GetColour()||
	                conf->CaptionNormalColor         != cpkNormCapt->GetColour()    ||
	                conf->CaptionNormalColorGradient != cpkNormGrdt->GetColour()    ||
	                conf->CaptionNormalColorText     != cpkNormCaptText->GetColour();

	event.SetInt( conf->IsDirty );
	event.Skip();
}

void PrefsPageGUICaps::OnToggleCustPrefs( wxCommandEvent& event )
{
	pnlCaptMetrics->Enable( event.IsChecked() );
	pnlCaptColors->Enable ( event.IsChecked() );
	event.Skip();
}

PrefsPageLocale::PrefsPageLocale( wxWindow* parent )
:
_PrefsPageLocale( parent )
{
	wxFBSettings* conf = wxFBSettings::Get();

	bcbLang->Append( _("System Default"), wxBitmap( default_xpm ) );
	bcbLang->Append( _("English"),        wxBitmap( en_GB_xpm )   );
	bcbLang->Append( _("English (U.S.)"), wxBitmap( en_US_xpm )   );
	bcbLang->Append( _("German"),         wxBitmap( de_xpm )      );
	bcbLang->Append( _("Italian"),        wxBitmap( it_xpm )      );

	bcbLang->SetSelection( conf->LocaleSelected );
	chkLang->SetValue    ( conf->IsLocaleEnabled );
	bcbLang->Enable      ( conf->IsLocaleEnabled );
}

void PrefsPageLocale::SetValues()
{
	wxFBSettings* conf = wxFBSettings::Get();

	conf->IsLocaleEnabled = chkLang->GetValue();
	conf->LocaleSelected  = bcbLang->GetSelection();
}

void PrefsPageLocale::OnUpdateUI( wxUpdateUIEvent& event )
{
	wxFBSettings* conf  = wxFBSettings::Get();

	conf->IsDirty = conf->IsLocaleEnabled != chkLang->IsChecked()   ||
                    conf->LocaleSelected  != bcbLang->GetSelection();

	event.SetInt( conf->IsDirty );
	event.Skip();
}

void PrefsPageLocale::OnToggleLocale( wxCommandEvent& event )
{
	bcbLang->Enable( event.IsChecked() );
	event.Skip();
}

PrefsDialog::PrefsDialog( wxWindow* parent )
:
_PrefsDialog( parent )
{
	PrefsPageGUI* pnlGUI = new PrefsPageGUI     ( tbkPrefs );
	pnlGuiCaps           = new PrefsPageGUICaps ( tbkPrefs );
	pnlLang              = new PrefsPageLocale  ( tbkPrefs );

	tbkPrefs->AddPage   ( pnlGUI,     _("GUI"),      false, 1 );
	tbkPrefs->AddSubPage( pnlGuiCaps, _("Captions"), false, 0 );
	tbkPrefs->AddPage   ( pnlLang,    _("Language"), false, 2 );

	tbkPrefs->ExpandNode( 0, true );

	buttonSizerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PrefsDialog::OnOK ), NULL, this );
	buttonSizerApply->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PrefsDialog::OnApply ), NULL, this );
}

void PrefsDialog::SetValues()
{
	pnlGuiCaps->SetValues();
	pnlLang->SetValues();
}

void PrefsDialog::SaveConfig()
{
	SetValues();
	wxFBSettings::Get()->Save();
}

void PrefsDialog::OnUpdateUI( wxUpdateUIEvent& event )
{
	if ( (event.GetId() == ID_PREFS_CAPTIONS) || (event.GetId() == ID_PREFS_LOCALE) )
	{
		buttonSizerApply->Enable( event.GetInt() );
		buttonSizerOK->Enable( event.GetInt() );
	}
	event.Skip();
}

void PrefsDialog::OnOK( wxCommandEvent&  event )
{
	SetValues();
	Hide();
}

void PrefsDialog::OnApply( wxCommandEvent&  event )
{
	SaveConfig();
	Hide();
}
