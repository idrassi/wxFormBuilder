#include "prefs.h"

PrefsDialog::PrefsDialog( wxWindow* parent )
:
_PrefsDialog( parent )
{
	PrefsDialogSetup();
}

#include <wx/config.h>
#include "icons/flags/default.xpm"
#include "icons/flags/de.xpm"
#include "icons/flags/en_GB.xpm"
#include "icons/flags/en_US.xpm"
#include "icons/flags/it.xpm"

#include "rad/bitmaps.h"
#include "utils/typeconv.h"

void PrefsDialog::PrefsDialogSetup()
{
	imgList = new wxImageList();
//	imgList->Add( AppBitmaps::GetBitmap( wxT("properties") ) );
	imgList->Add( AppBitmaps::GetBitmap( wxT("language") ) );
	imgList->Add( AppBitmaps::GetBitmap( wxT("designer") ) );

	tbkPrefs->SetImageList( imgList );

	for ( size_t i = 0; i < tbkPrefs->GetPageCount(); ++i )
	{
		tbkPrefs->SetPageImage( i, i );
	}

	bcbLang->Append( _("System Default"), wxBitmap( default_xpm ) );
	bcbLang->Append( _("English"),        wxBitmap( en_GB_xpm ) );
	bcbLang->Append( _("English (U.S.)"), wxBitmap( en_US_xpm ) );
	bcbLang->Append( _("German"),         wxBitmap( de_xpm ) );
	bcbLang->Append( _("Italian"),        wxBitmap( it_xpm ) );

	bool bEnabled; int selection;
	wxConfigBase* config = wxConfigBase::Get();

	config->Read( wxT("/preferences/locale/enabled"), &bEnabled, 0 );
	config->Read( wxT("/preferences/locale/language"), &selection, 0 );

	bcbLang->SetSelection( selection );
	chkLang->SetValue    ( bEnabled );
	bcbLang->Enable      ( bEnabled );

	bool     bGradVert;
	int      hgtCaptText;
	wxString sColActvCapt;
	wxString sColActvGrdt;
	wxString sColCaptText;

	config->Read( wxT("/preferences/gui/CaptionActiveColour"),         &sColActvCapt, TypeConv::SystemColourToString( wxSYS_COLOUR_ACTIVECAPTION ) );
	config->Read( wxT("/preferences/gui/CaptionActiveGradientColour"), &sColActvGrdt, TypeConv::SystemColourToString( wxSYS_COLOUR_GRADIENTACTIVECAPTION ) );
	config->Read( wxT("/preferences/gui/CaptionTextColour"),           &sColCaptText, TypeConv::SystemColourToString( wxSYS_COLOUR_CAPTIONTEXT ) );
	config->Read( wxT("/preferences/gui/CaptionGradientVertical"),     &bGradVert,   0 );
	config->Read( wxT("/preferences/gui/CaptionHeight"),               &hgtCaptText, 18 );

	if ( hgtCaptText > 100 ) hgtCaptText = 100;

	choGrdtDir->SetSelection  ( bGradVert );
	spnCaptHeight->SetValue   ( hgtCaptText );
	cpkActvCapt->SetColour    ( TypeConv::StringToColour( sColActvCapt ) );
	cpkActvGrdt->SetColour    ( TypeConv::StringToColour( sColActvGrdt ) );
	cpkActvCaptText->SetColour( TypeConv::StringToColour( sColCaptText ) );
}

void PrefsDialog::OnToggleLocale( wxCommandEvent& event )
{
	bcbLang->Enable( event.IsChecked() );
	event.Skip();
}

void PrefsDialog::OnClose( wxCommandEvent& event )
{
	bool     bEnabled    = chkLang->IsChecked();
	int      selection   = bcbLang->GetSelection();
	wxColour colActvCapt = cpkActvCapt->GetColour();
	wxColour colActvGrdt = cpkActvGrdt->GetColour();
	wxColour colCaptText = cpkActvCaptText->GetColour();
	bool     bGradVert   = choGrdtDir->GetSelection();
	int      hgtCaptText = spnCaptHeight->GetValue();
	wxConfigBase* config = wxConfigBase::Get();

	config->Write( wxT("/preferences/locale/enabled"),  bEnabled );
	config->Write( wxT("/preferences/locale/language"), selection );

	config->Write( wxT("/preferences/gui/CaptionActiveColour"),         TypeConv::ColourToString( colActvCapt ) );
	config->Write( wxT("/preferences/gui/CaptionActiveGradientColour"), TypeConv::ColourToString( colActvGrdt ) );
	config->Write( wxT("/preferences/gui/CaptionTextColour"),           TypeConv::ColourToString( colCaptText ) );
	config->Write( wxT("/preferences/gui/CaptionGradientVertical"),     bGradVert );
	config->Write( wxT("/preferences/gui/CaptionHeight"),               hgtCaptText );
	event.Skip();
}
