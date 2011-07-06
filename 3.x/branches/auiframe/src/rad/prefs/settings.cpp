#include "settings.h"
#include "utils/typeconv.h"
#include <wx/config.h>
#include <wx/settings.h>

wxFBSettings::wxFBSettings()
{
	Load();
}

wxFBSettings::~wxFBSettings()
{
}

void wxFBSettings::Load()
{
	wxConfigBase* config = wxConfigBase::Get();

	wxString sColActvCapt;
	wxString sColActvGrdt;
	wxString sColCaptText;

	config->Read( wxT("/preferences/gui/UseCustomPrefs"),              &UseCustomPrefs, 0 );
	config->Read( wxT("/preferences/gui/CaptionActiveColour"),         &sColActvCapt, TypeConv::SystemColourToString( wxSYS_COLOUR_ACTIVECAPTION ) );
	config->Read( wxT("/preferences/gui/CaptionActiveGradientColour"), &sColActvGrdt, TypeConv::SystemColourToString( wxSYS_COLOUR_GRADIENTACTIVECAPTION ) );
	config->Read( wxT("/preferences/gui/CaptionTextColour"),           &sColCaptText, TypeConv::SystemColourToString( wxSYS_COLOUR_CAPTIONTEXT ) );
	config->Read( wxT("/preferences/gui/CaptionGradientVertical"),     &UseGradientVertical, 0  );
	config->Read( wxT("/preferences/gui/CaptionHeight"),               &CaptionTextHeight, 18 );

	CaptionActiveColor         = TypeConv::StringToColour( sColActvCapt );
	CaptionActiveColorGradient = TypeConv::StringToColour( sColActvGrdt );
	CaptionActiveColorText     = TypeConv::StringToColour( sColCaptText );

	if ( CaptionTextHeight < 0 )   CaptionTextHeight = 0;
	if ( CaptionTextHeight > 100 ) CaptionTextHeight = 100;

	config->Read( wxT("/preferences/locale/enabled"),  &IsLocaleEnabled, 0  );
	config->Read( wxT("/preferences/locale/language"), &LocaleSelected, 0 );
}

void wxFBSettings::Save()
{
	wxConfigBase* config = wxConfigBase::Get();

	config->Write( wxT("/preferences/locale/enabled"),  IsLocaleEnabled );
	config->Write( wxT("/preferences/locale/language"), LocaleSelected );

	config->Write( wxT("/preferences/gui/CaptionActiveColour"),         TypeConv::ColourToString( CaptionActiveColor ) );
	config->Write( wxT("/preferences/gui/CaptionActiveGradientColour"), TypeConv::ColourToString( CaptionActiveColorGradient ) );
	config->Write( wxT("/preferences/gui/CaptionTextColour"),           TypeConv::ColourToString( CaptionActiveColorText ) );
	config->Write( wxT("/preferences/gui/CaptionGradientVertical"),     UseGradientVertical );
	config->Write( wxT("/preferences/gui/CaptionHeight"),               CaptionTextHeight );

	delete wxConfigBase::Set((wxConfigBase *) NULL);
}
