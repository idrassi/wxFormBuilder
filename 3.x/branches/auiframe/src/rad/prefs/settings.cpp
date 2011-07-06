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
	wxString sColActvText;
	wxString sColNormCapt;
	wxString sColNormGrdt;
	wxString sColNormText;

	config->Read( wxT("/preferences/gui/UseCustomPrefs"),             &UseCustomPrefs,      0 );
	config->Read( wxT("/preferences/gui/UseGradientVertical"),        &UseGradientVertical, 0 );
	config->Read( wxT("/preferences/gui/CaptionTextHeight"),          &CaptionTextHeight,  18 );
	config->Read( wxT("/preferences/gui/CaptionActiveColor"),         &sColActvCapt, TypeConv::SystemColourToString( wxSYS_COLOUR_ACTIVECAPTION ) );
	config->Read( wxT("/preferences/gui/CaptionActiveColorGradient"), &sColActvGrdt, TypeConv::SystemColourToString( wxSYS_COLOUR_GRADIENTACTIVECAPTION ) );
	config->Read( wxT("/preferences/gui/CaptionActiveColorText"),     &sColActvText, TypeConv::SystemColourToString( wxSYS_COLOUR_CAPTIONTEXT ) );
	config->Read( wxT("/preferences/gui/CaptionNormalColor"),         &sColNormCapt, TypeConv::SystemColourToString( wxSYS_COLOUR_INACTIVECAPTION ) );
	config->Read( wxT("/preferences/gui/CaptionNormalColorGradient"), &sColNormGrdt, TypeConv::SystemColourToString( wxSYS_COLOUR_GRADIENTINACTIVECAPTION ) );
	config->Read( wxT("/preferences/gui/CaptionNormalColorText"),     &sColNormText, TypeConv::SystemColourToString( wxSYS_COLOUR_INACTIVECAPTIONTEXT ) );

	CaptionActiveColor         = TypeConv::StringToColour( sColActvCapt );
	CaptionActiveColorGradient = TypeConv::StringToColour( sColActvGrdt );
	CaptionActiveColorText     = TypeConv::StringToColour( sColActvText );
	CaptionNormalColor         = TypeConv::StringToColour( sColNormCapt );
	CaptionNormalColorGradient = TypeConv::StringToColour( sColNormGrdt );
	CaptionNormalColorText     = TypeConv::StringToColour( sColNormText );

	if ( CaptionTextHeight < 0 )   CaptionTextHeight = 0;
	if ( CaptionTextHeight > 100 ) CaptionTextHeight = 100;

	config->Read( wxT("/preferences/locale/enabled"),  &IsLocaleEnabled, 0  );
	config->Read( wxT("/preferences/locale/language"), &LocaleSelected, 0 );
}

void wxFBSettings::Save()
{
	wxConfigBase* config = wxConfigBase::Get();

	if ( config == NULL ) return;

	config->Write( wxT("/preferences/gui/UseCustomPrefs"),             UseCustomPrefs );
	config->Write( wxT("/preferences/gui/CaptionActiveColor"),         TypeConv::ColourToString( CaptionActiveColor ) );
	config->Write( wxT("/preferences/gui/CaptionActiveColorGradient"), TypeConv::ColourToString( CaptionActiveColorGradient ) );
	config->Write( wxT("/preferences/gui/CaptionActiveColorText"),     TypeConv::ColourToString( CaptionActiveColorText ) );
	config->Write( wxT("/preferences/gui/CaptionNormalColor"),         TypeConv::ColourToString( CaptionNormalColor ) );
	config->Write( wxT("/preferences/gui/CaptionNormalColorGradient"), TypeConv::ColourToString( CaptionNormalColorGradient ) );
	config->Write( wxT("/preferences/gui/CaptionNormalColorText"),     TypeConv::ColourToString( CaptionNormalColorText ) );
	config->Write( wxT("/preferences/gui/UseGradientVertical"),        UseGradientVertical );
	config->Write( wxT("/preferences/gui/CaptionTextHeight"),          CaptionTextHeight );

	config->Write( wxT("/preferences/locale/enabled"),  IsLocaleEnabled );
	config->Write( wxT("/preferences/locale/language"), LocaleSelected );

	config->Flush();
}
