#ifndef __WXFB_SETTINGS_H__
#define __WXFB_SETTINGS_H__

#include "utils/singleton.h"
#include <wx/colour.h>

class wxFBSettings : public Singleton< wxFBSettings >
{
	friend class Singleton< wxFBSettings >;

public:
	void     Load();
	void     Save();

	bool     IsDirty;

	bool     UseCustomPrefs;
	bool     UseGradientVertical;
	int      CaptionTextHeight;
	wxColour CaptionActiveColor;
	wxColour CaptionActiveColorGradient;
	wxColour CaptionActiveColorText;
	wxColour CaptionNormalColor;
	wxColour CaptionNormalColorGradient;
	wxColour CaptionNormalColorText;

	bool     IsLocaleEnabled;
	int      LocaleSelected;

protected:
	wxFBSettings();
	virtual ~wxFBSettings();
};

#endif //__WXFB_SETTINGS_H__
