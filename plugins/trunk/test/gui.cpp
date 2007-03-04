///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 28 2007)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifdef WX_PRECOMP

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#else
#include <wx/wx.h>
#endif //WX_PRECOMP

#include "gui.h"

///////////////////////////////////////////////////////////////////////////

G_MainFrame::G_MainFrame( wxWindow* parent, int id, wxString title, wxPoint pos, wxSize size, int style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_lcdDisplay1 = new kwxLCDDisplay(m_panel1, wxDefaultPosition, wxDefaultSize );
	m_lcdDisplay1->SetNumberDigits( 2 );
	m_lcdDisplay1->SetValue( wxT("0") );
	
	fgSizer1->Add( m_lcdDisplay1, 1, wxEXPAND | wxALL, 5 );
	
	m_lcdClock1 = new kwxLCDClock(m_panel1, wxDefaultPosition, wxDefaultSize );
	m_lcdClock1->SetNumberDigits( 8 );
	m_lcdClock1->SetValue( wxT("0") );
	m_lcdClock1->StartClock();
	fgSizer1->Add( m_lcdClock1, 1, wxEXPAND | wxALL, 5 );
	
	m_angRegulator1 = new kwxAngularRegulator(m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize );
	m_angRegulator1->SetRange( 0 , 360 );
	m_angRegulator1->SetAngle( 0 , 360 );
	m_angRegulator1->SetValue( 0 );
	
	fgSizer1->Add( m_angRegulator1, 1, wxEXPAND | wxALL, 5 );
	
	m_angMeter1 = new kwxAngularMeter(m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize );
	m_angMeter1->SetNumSectors( 1 );
	m_angMeter1->SetNumTick( 9 );
	m_angMeter1->SetRange( 0 , 100 );
	m_angMeter1->SetAngle( -20 , 200 );
	m_angMeter1->SetValue( 10 );
	m_angMeter1->DrawCurrent( true );
	m_angMeter1->SetNeedleColour( wxColour( 255, 0, 0 ) );
	
	fgSizer1->Add( m_angMeter1, 0, wxALL, 5 );
	
	m_linMeter1 = new kwxLinearMeter(m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize );
	m_linMeter1->SetRangeVal( 0 , 100 );
	m_linMeter1->SetValue( 0 );
	m_linMeter1->SetOrizDirection( false );
	m_linMeter1->ShowCurrent( true );
	m_linMeter1->ShowLimits( true );
	
	fgSizer1->Add( m_linMeter1, 0, wxALL, 5 );
	
	m_linRegulator1 = new kwxLinearRegulator(m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize );
	m_linRegulator1->SetRangeVal( 0 , 100 );
	m_linRegulator1->SetValue( 0 );
	m_linRegulator1->SetOrizDirection( false );
	m_linRegulator1->ShowCurrent( true );
	m_linRegulator1->ShowLimits( true );
	
	fgSizer1->Add( m_linRegulator1, 0, wxALL, 5 );
	
	m_panel1->SetSizer( fgSizer1 );
	m_panel1->Layout();
	fgSizer1->Fit( m_panel1 );
	bSizer1->Add( m_panel1, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
}
