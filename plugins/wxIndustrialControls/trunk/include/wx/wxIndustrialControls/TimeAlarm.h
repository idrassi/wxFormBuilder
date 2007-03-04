/////////////////////////////////////////////////////////////////////////////
// Name:        TimeAlarm.h
// Purpose:
// Author:      Marco Cavallini <m.cavallini AT koansoftware.com>
// Modified by:
// Copyright:   (C)2004-2006 Copyright by Koan s.a.s. - www.koansoftware.com
// Licence:     KWIC License http://www.koansoftware.com/kwic/kwic-license.htm
/////////////////////////////////////////////////////////////////////////////
#ifndef __KWX_CTIMEALARM__
#define __KWX_CTIMEALARM__

#include "wx/wxIndustrialControls/indctrlsdef.h"

class WXDLLIMPEXP_INDCTRLS CTimeAlarm
{
public:
	CTimeAlarm() ;

	void Enable () { m_bEnable = true ; } ;
	void Disable () { m_bEnable = false ; } ;

	void SetAlarmTime(wxDateTime alarmtime) ;
	void SetAlarmTime(double alarmtime) ;

	wxString GetAlarmString () ;

private:
	double m_dJAlarmTime ;
	bool m_bEnable ;

} ;

#endif //__KWX_CTIMEALARM__
