/////////////////////////////////////////////////////////////////////////////
// Name:        TimeAlarm.cpp
// Purpose:     wxIndustrialControls Library
// Author:      Marco Cavallini <m.cavallini AT koansoftware.com>
// Modified by:
// Copyright:   (C)2004-2006 Copyright by Koan s.a.s. - www.koansoftware.com
// Licence:     KWIC License http://www.koansoftware.com/kwic/kwic-license.htm
/////////////////////////////////////////////////////////////////////////////

// ----------------------------------------------------------------------------
// Precompiled headers
// ----------------------------------------------------------------------------
#ifdef WX_PRECOMP

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#else
#include <wx/wx.h>
#endif //WX_PRECOMP

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

#include <wx/datetime.h>
#include "wx/wxIndustrialControls/TimeAlarm.h"

CTimeAlarm::CTimeAlarm()
{
	m_dJAlarmTime = 0 ;
	m_bEnable = false ;
}

void CTimeAlarm::SetAlarmTime(wxDateTime alarmtime)
{
	m_dJAlarmTime = alarmtime.GetJDN();
}

void CTimeAlarm::SetAlarmTime(double alarmtime)
{
	m_dJAlarmTime = alarmtime ;
}


//return DD-MM-YY HH:MM::SS dell'allarme corrente
wxString CTimeAlarm::GetAlarmString()
{
	wxString sDate ;
	wxDateTime jdate ;

	jdate.Set(m_dJAlarmTime) ;
	sDate = jdate.Format(wxT("%d-%m-%Y %H:%M:%S")) ;

	return sDate ;
}
