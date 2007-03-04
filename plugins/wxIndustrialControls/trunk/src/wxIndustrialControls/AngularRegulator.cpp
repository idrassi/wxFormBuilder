/////////////////////////////////////////////////////////////////////////////
// Name:        AngularRegulator.cpp
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

#include <math.h>

#include "wx/wxIndustrialControls/AngularRegulator.h"

IMPLEMENT_DYNAMIC_CLASS(kwxAngularRegulator, wxControl)

BEGIN_EVENT_TABLE(kwxAngularRegulator,wxControl)
	EVT_MOUSE_EVENTS(kwxAngularRegulator::OnMouse)
	EVT_PAINT(kwxAngularRegulator::OnPaint)
	EVT_ERASE_BACKGROUND(kwxAngularRegulator::OnEraseBackGround)
END_EVENT_TABLE()


kwxAngularRegulator::kwxAngularRegulator(wxWindow* parent,
		                   const wxWindowID id,
		                   const wxString& label,
                           const wxPoint& pos,
                           const wxSize& size,
		                   const long int style)
	: wxControl(parent, id, pos, size, style)
{
	if (parent)
		SetBackgroundColour(parent->GetBackgroundColour());
	else
		SetBackgroundColour(*wxLIGHT_GREY);

    //SetSize(size);
    SetAutoLayout(TRUE);
	Refresh();

//	m_nClientWidth = size.GetWidth() ;
//	m_nClientHeight = size.GetHeight() ;

	m_nStato = 0 ;
	m_nRealVal = 0 ;
	m_nScaledVal = 0 ;
	m_nTags = 0 ;

	m_cExtCircle = wxColour(82,150,243); //*wxLIGHT_GREY ;
	m_cIntCircle = *wxBLUE; //*wxLIGHT_GREY ;

	m_cLimitsColour = *wxBLACK ;

	m_cKnobBorderColour = *wxLIGHT_GREY; //*wxBLACK ;
	m_cKnobColour = wxColour(181,209,246); //*wxLIGHT_GREY ;

	m_cTagsColour = *wxWHITE;// *wxBLACK ;

	//membitmap = new wxBitmap(size.GetWidth(), size.GetHeight()) ;

}

kwxAngularRegulator::~kwxAngularRegulator()
{
	//delete membitmap;
}

wxSize kwxAngularRegulator::DoGetBestSize() const
{
    return wxSize(200,200);
}

void kwxAngularRegulator::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);

    int w,h;
	GetClientSize(&w,&h);

	if (w != m_nClientWidth || h != m_nClientHeight)
	{
      m_nClientWidth = w;
      m_nClientHeight = h;

      int deltaRange = m_nMax - m_nMin;
	  int deltaAngle = m_nAngleEnd - m_nAngleStart;

	  double coeff = (double)deltaAngle / (double)deltaRange;

	  double ang = 360 + ((m_val * coeff) + m_nAngleStart);

	  ang = (ang * PGRECO) / 180;
	  m_dxi = cos(ang) * ((m_nClientHeight / 2) - 22) ; //coordinate centro knob
	  m_dyi = sin(ang) * ((m_nClientHeight / 2) - 22) ;
	}

	wxBitmap membitmap_(m_nClientWidth,m_nClientHeight);

	// Create a memory DC
	wxMemoryDC temp_dc;

	temp_dc.SelectObject(membitmap_);

	temp_dc.SetBackground(*wxTheBrushList->FindOrCreateBrush(GetBackgroundColour(),wxSOLID));
	temp_dc.Clear();

    //////////////////////////////////////////////////////
	temp_dc.SetPen(*wxThePenList->FindOrCreatePen(*wxBLACK, 1, wxSOLID));
	temp_dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(m_cExtCircle,wxSOLID));
	temp_dc.DrawCircle(m_nClientWidth / 2, m_nClientHeight / 2, m_nClientHeight / 2) ;
    //////////////////////////////////////////////////////
    temp_dc.SetPen(*wxThePenList->FindOrCreatePen(*wxBLACK, 1, wxSOLID));
	temp_dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(m_cIntCircle,wxSOLID));
	temp_dc.DrawCircle(m_nClientWidth / 2, m_nClientHeight / 2, m_nClientHeight / 2 - 10) ;

	DrawLimit(temp_dc) ;	//limiti

	if (m_nTags >0 )
		DrawTags(temp_dc);	//tags

	DrawKnob(temp_dc) ;		//knob


	// We can now draw into the memory DC...
	// Copy from this DC to another DC.
	dc.Blit(0, 0, m_nClientWidth, m_nClientHeight, &temp_dc, 0, 0);

}

void kwxAngularRegulator::SetValue(int val)
{
    GetClientSize(&m_nClientWidth,&m_nClientHeight);
	int deltaRange = m_nMax - m_nMin;
	int deltaAngle = m_nAngleEnd - m_nAngleStart;

	double coeff = (double)deltaAngle / (double)deltaRange;

	double ang = 360 + ((val * coeff) + m_nAngleStart);

	ang = (ang * PGRECO) / 180;
	m_dxi = cos(ang) * ((m_nClientHeight / 2) - 22) ; //coordinate centro knob
	m_dyi = sin(ang) * ((m_nClientHeight / 2) - 22) ;

	m_val = val;

	Refresh();


}



void kwxAngularRegulator::OnMouse(wxMouseEvent& event)
{
	if (m_nStato == 0 && event.Entering())	//dentro nel controllo
		m_nStato = 1 ;
	else if (m_nStato >= 1 && event.Leaving())	//fuori dal controllo
		m_nStato = 0 ;
	else if (m_nStato == 1 && event.LeftDown())	//click o inizio trascinamento
	{
		m_nStato = 2 ;
		m_mousePosition = event.GetPosition();
		SetPosition() ;
	}
	else if (m_nStato == 2 && event.LeftIsDown())	//trascinamento
	{
		m_mousePosition = event.GetPosition();
		SetPosition() ;
	}
	else if (m_nStato == 2 && event.LeftUp())	//fine trascinamento o rilascio click
		m_nStato = 1 ;
}


void kwxAngularRegulator::DrawKnob(wxDC &temp_dc)
{
	double x, y ;

	x = (m_nClientWidth / 2) - m_dxi ;
	y = (m_nClientHeight / 2) - m_dyi ;

	temp_dc.SetPen(*wxThePenList->FindOrCreatePen(m_cKnobBorderColour, 1, wxSOLID));
	temp_dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(m_cKnobColour,wxSOLID));

	temp_dc.DrawCircle(x, y, 5) ;
}

void kwxAngularRegulator::DrawLimit(wxDC &temp_dc)
{
	double ang ;

	int anglestart = m_nAngleStart ;
	//Start
	if (anglestart < 0 )
		anglestart = 360 + anglestart ;

	ang = (anglestart * PGRECO) / 180 ; //radianti parametro angolo

	double sx = cos(ang) * ((m_nClientHeight / 2) ) ; //coordinate limite start
	double sy = sin(ang) * ((m_nClientHeight / 2) ) ;

	double dx = cos(ang) * ((m_nClientHeight / 2) - 7) ; //coordinate limite start
	double dy = sin(ang) * ((m_nClientHeight / 2) - 7) ;


	temp_dc.SetPen(*wxThePenList->FindOrCreatePen(m_cLimitsColour, 2, wxSOLID));

	temp_dc.DrawLine((m_nClientWidth / 2) - sx,(m_nClientHeight / 2) - sy, (m_nClientWidth / 2) - dx , (m_nClientHeight / 2) - dy ) ;

	ang = (m_nAngleEnd * PGRECO) / 180 ; //radianti parametro angolo

	sx = cos(ang) * ((m_nClientHeight / 2) ) ; //coordinate limite start
	sy = sin(ang) * ((m_nClientHeight / 2) ) ;

	dx = cos(ang) * ((m_nClientHeight / 2) - 7) ; //coordinate limite start
	dy = sin(ang) * ((m_nClientHeight / 2) - 7) ;

	temp_dc.DrawLine((m_nClientWidth / 2) - sx,(m_nClientHeight / 2) - sy, (m_nClientWidth / 2) - dx , (m_nClientHeight / 2) - dy ) ;

}

void kwxAngularRegulator::DrawTags(wxDC &temp_dc)
{
	int tagCount ;

	int deltaRange = m_nMax - m_nMin;
	int deltaAngle = m_nAngleEnd - m_nAngleStart;

	int sxi, syi ;
	int dxi, dyi ;

	double coeff = (double)deltaAngle / (double)deltaRange;

	double angle ;

	temp_dc.SetPen(*wxThePenList->FindOrCreatePen(m_cTagsColour, 1, wxSOLID));

	for (tagCount = 0 ; tagCount < m_nTags ; tagCount++)
	{
		angle = 360 + ((m_nTagsValue[tagCount] * coeff) + m_nAngleStart);
		angle = (angle * PGRECO) / 180;

		sxi = cos(angle) * (m_nClientHeight / 2) ;
		syi = sin(angle) * (m_nClientHeight / 2) ;

		dxi = cos(angle) * ((m_nClientHeight / 2) - 7) ;
		dyi = sin(angle) * ((m_nClientHeight / 2) - 7);

		temp_dc.DrawLine((m_nClientWidth / 2) - sxi,(m_nClientHeight / 2) - syi, (m_nClientWidth / 2) - dxi , (m_nClientHeight / 2) - dyi ) ;
	}


}


void kwxAngularRegulator::SetPosition()
{
	int x, y ;
	double ang ;
	int deltaRange, deltaAngle ;
	double val ;

	x = m_mousePosition.x ;
	y = m_mousePosition.y ;

	ang = GetAngleFromCord(x, y) ; //IN RADIANTI

	val = (ang * 180) / PGRECO; //radianti parametro angolo

	deltaRange = m_nMax - m_nMin;
	deltaAngle = m_nAngleEnd - m_nAngleStart;

	double coeff = (double)deltaAngle / (double)deltaRange;

	//OK
	if( m_nAngleStart < 0 && val >= (360 + m_nAngleStart) )
		m_nScaledVal = (double)(val  - (360 + m_nAngleStart)) / coeff;
	else
		m_nScaledVal = (double)(val  - m_nAngleStart) / coeff;


	//vale sempre fuori dall'intervallo ma non si sa da dove si arriva
	//salviamo ultima posizione e ricarichiamo
	if(m_nScaledVal > m_nMax || m_nScaledVal < m_nMin)
		ang = old_ang ;
	else
	{
		m_nRealVal = (int)(ceil(m_nScaledVal)) ;
		wxCommandEvent event(kwxEVT_ANGREG_CHANGE, GetId());	//evento
		event.SetEventObject(this);
		ProcessCommand(event) ;
	}

	m_dxi = cos(ang) * ((m_nClientHeight / 2) - 22) ; //coordinate centro knob
	m_dyi = sin(ang) * ((m_nClientHeight / 2) - 22) ;

//	wxLogTrace("angolo: %f scalato: %f",val, m_nScaledVal);

	old_ang = ang ;

	Refresh() ;

}

//Ritorna l'angolo in radianti della posizione del mouse
double kwxAngularRegulator::GetAngleFromCord(int cx, int cy)
{

	double x, y, ang = 0 ;

	y = ((m_nClientHeight / 2) - (double)cy)  / (m_nClientHeight / 2);
	x = ((double)cx - (m_nClientWidth / 2)) / (m_nClientHeight / 2);

	ang -= (atan2(-y, -x)) ; // IN RADIANTI

	if (ang < 0 )
		ang += 2 * PGRECO ;

	return  ang ;
}

void kwxAngularRegulator::AddTag(int value)
{
	m_nTagsValue[m_nTags++] = value ;

}

