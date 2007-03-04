/////////////////////////////////////////////////////////////////////////////
// Name:        AngularRegulator.h
// Purpose:     wxIndustrialControls Library
// Author:      Marco Cavallini <m.cavallini AT koansoftware.com>
// Modified by:
// Copyright:   (C)2004-2006 Copyright by Koan s.a.s. - www.koansoftware.com
// Licence:     KWIC License http://www.koansoftware.com/kwic/kwic-license.htm
/////////////////////////////////////////////////////////////////////////////
#ifndef __KWX_ANGULAR_REGULATOR__
#define __KWX_ANGULAR_REGULATOR__

#include "wx/wxIndustrialControls/indctrlsdef.h"

const int kwxEVT_ANGREG_FIRST = wxEVT_FIRST + 5402;

const wxEventType kwxEVT_ANGREG_CHANGE	= kwxEVT_ANGREG_FIRST + 1;

#define EVT_ANGULARREG_CHANGE(id, fn)	\
		DECLARE_EVENT_TABLE_ENTRY(kwxEVT_ANGREG_CHANGE, id, -1, \
		(wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, \
		(wxObject*)NULL ),


#define PGRECO (4.0 * atan(1.0))

class WXDLLIMPEXP_INDCTRLS kwxAngularRegulator : public wxControl
{
public:
	kwxAngularRegulator(void) { m_id = -1 ; };

	kwxAngularRegulator(wxWindow* parent,
				        const wxWindowID id         = -1,
			            const wxString&  label      = wxEmptyString,
				        const wxPoint&   pos        = wxDefaultPosition,
				        const wxSize&    size       = wxDefaultSize,
				        const long int   style      = 0);

	virtual ~kwxAngularRegulator();

	void	SetRange(int min, int max) { m_nMin = min ; m_nMax = max ; } ;
	void	SetAngle(int min, int max) { m_nAngleStart = min ; m_nAngleEnd = max ; } ;
	int		GetValue() { return m_nRealVal ; } ;
	void	SetValue(int val) ;

	void	SetExtCircleColour(const wxColour &colour) { m_cExtCircle = colour ; } ;
	void	SetIntCircleColour(const wxColour &colour) { m_cIntCircle = colour ; } ;

	void	SetKnobBorderColour(const wxColour &colour) { m_cKnobBorderColour = colour ; } ;
	void	SetKnobColour(const wxColour &colour) { m_cKnobColour = colour ; } ;

	void	SetLimitsColour(const wxColour &colour) { m_cLimitsColour = colour ; } ;

	void	SetTagsColour(const wxColour &colour) { m_cTagsColour = colour ; } ;

	void	AddTag(int value) ;

	wxSize DoGetBestSize() const;

private:

	DECLARE_DYNAMIC_CLASS(kwxAngularRegulator)
	DECLARE_EVENT_TABLE()

	void	DrawKnob(wxDC &temp_dc) ;
	void	DrawLimit(wxDC &temp_dc) ;
	void	DrawTags(wxDC &temp_dc) ;

	void	SetPosition() ;
	double	GetAngleFromCord(int cx, int cy) ;

	void    OnPaint(wxPaintEvent& event);
	void	OnEraseBackGround(wxEraseEvent& event) {};
	void	OnMouse(wxMouseEvent& event) ;

	wxWindowID	 GetID() { return m_id; } ;

	wxWindowID m_id ;

	int m_nStato ;
	int m_nMin ;
	int m_nMax ;
	int m_nAngleStart ;
	int m_nAngleEnd ;

	double m_nScaledVal ;
	double old_ang ;
	int m_nRealVal ;

	wxPoint m_mousePosition ;

	wxColour m_cExtCircle ;
	wxColour m_cIntCircle ;
	wxColour m_cKnobBorderColour ;
	wxColour m_cKnobColour ;
	wxColour m_cTagsColour ;
	wxColour m_cLimitsColour ;

    // cached values, they are recalculated when the size change
	int m_nClientWidth ;
	int m_nClientHeight ;
    double m_dxi ;
	double m_dyi ;

	int m_nTagsValue[20] ;
	int m_nTags ;



	int m_val; // value

	//wxBitmap *membitmap ;

} ;

#endif //__KWX_ANGULAR_REGULATOR__
