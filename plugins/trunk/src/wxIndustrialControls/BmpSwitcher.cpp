/////////////////////////////////////////////////////////////////////////////
// Name:        BmpSwitcher.cpp
// Purpose:     wxIndustrialControls Library
// Author:      Marco Cavallini <m.cavallini AT koansoftware.com>
// Modified by:
// Copyright:   (C)2004-2006 Copyright by Koan s.a.s. - www.koansoftware.com
// Licence:     KWIC License http://www.koansoftware.com/kwic/kwic-license.htm
/////////////////////////////////////////////////////////////////////////////

//	La classe kwxBmpSwitcher riceve una o pi� bitmap tramite il metodo
//	AddBitmap, e permette lo scambio di esse tramite il metodo IncState o SetState.
//
//	IncState():			Passa alla bitmap successiva, se si trova all'ultima
//						bitmap riparte dalla prima inserita.
//
//	SetState(stato):	Carica direttamente la bitmap indicata dallo stato
//						passato come parametro.
//
//	Nel caso in cui sia stata inserita una sola bitmap il metodo IncState
//	non ha effetto sul controllo.
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

#include <wx/image.h>

#include "wx/wxIndustrialControls/BmpSwitcher.h"
#include <wx/event.h>

#include <wx/listimpl.cpp>

WX_DEFINE_LIST(CBmpList);

//IMPLEMENT_DYNAMIC_CLASS(kwxBmpSwitcher, wxWindow)

BEGIN_EVENT_TABLE(kwxBmpSwitcher,wxWindow)
	EVT_PAINT(kwxBmpSwitcher::OnPaint)
	EVT_ERASE_BACKGROUND(kwxBmpSwitcher::OnEraseBackGround)
END_EVENT_TABLE()

kwxBmpSwitcher::kwxBmpSwitcher(wxWindow* parent,
		                   const wxWindowID id,
		                   const wxString& label,
                           const wxPoint& pos,
                           const wxSize& size,
		                   const long int style)
	: wxWindow(parent, id, pos, size, 0)
{
	if (parent)
		SetBackgroundColour(parent->GetBackgroundColour());
	else
		SetBackgroundColour(*wxLIGHT_GREY);

	SetSize(size.GetWidth(), size.GetHeight());

	SetAutoLayout(TRUE);
	Refresh();

	m_nState = 0 ;
	membitmap = new wxBitmap(size.GetWidth(), size.GetHeight()) ;

}


kwxBmpSwitcher::~kwxBmpSwitcher()
{
	delete membitmap;

	CBmpList::Node *node= m_bmplist.GetFirst() ;

	while(node)
	{
        wxBitmap *current = node->GetData();
		delete current ;
		node = node->GetNext() ;
	}

}


void kwxBmpSwitcher::OnPaint(wxPaintEvent &event)
{
	wxPaintDC old_dc(this);

	int w,h;
	wxBitmap *pCurrent ;

	m_nCount = m_bmplist.GetCount() ;

	GetClientSize(&w,&h);

	/////////////////

	// Create a memory DC
	wxMemoryDC dc;
	dc.SelectObject(*membitmap);
	dc.SetBackground(*wxTheBrushList->FindOrCreateBrush(GetBackgroundColour(),wxSOLID));
	dc.Clear();

	if (m_nCount == 1)
	{
		CBmpList::Node *node = m_bmplist.GetFirst();

		pCurrent = node->GetData() ;

		dc.DrawBitmap(*pCurrent, 0, 0, TRUE);
	}
	else
	{
		if (m_nState >= m_nCount )
			m_nState = 0 ;

		CBmpList::Node *node = m_bmplist.Item(m_nState);
		pCurrent = node->GetData() ;

		dc.DrawBitmap(*pCurrent, 0, 0, TRUE);

	}

	old_dc.Blit(0, 0, w, h, &dc, 0, 0);
}



void kwxBmpSwitcher::IncState()
{
	if (m_nCount > 1 )
	{
		m_nState++ ;
		Refresh() ;
	}
}


void kwxBmpSwitcher::SetState(int state)
{
	if (m_nCount > 1 )
	{
		m_nState = state ;
		Refresh() ;
	}
}

void kwxBmpSwitcher::AddBitmap(wxBitmap *bitmap)
{
	m_bmplist.Append(bitmap);
}
