/** Good old settings panel from wxWidgets auidemo :P */
#ifndef AUI_SETTINGSPANEL_H_INCLUDED
#define AUI_SETTINGSPANEL_H_INCLUDED

#include "mainframe.h"

#include <wx/aui/aui.h>
#include <wx/artprov.h>
#include <wx/bmpbuttn.h>
#include <wx/colordlg.h>
#include <wx/spinctrl.h>

class AuiSettingsPanel : public wxPanel
{
	enum {
		ID_AUI_PaneBorderSize = wxID_HIGHEST+1,
		ID_AUI_SashSize,
		ID_AUI_CaptionSize,
		ID_AUI_BackgroundColor,
		ID_AUI_SashColor,
		ID_AUI_InactiveCaptionColor,
		ID_AUI_InactiveCaptionGradientColor,
		ID_AUI_InactiveCaptionTextColor,
		ID_AUI_ActiveCaptionColor,
		ID_AUI_ActiveCaptionGradientColor,
		ID_AUI_ActiveCaptionTextColor,
		ID_AUI_BorderColor,
		ID_AUI_GripperColor
	};

public:
	AuiSettingsPanel( wxWindow* parent, MainFrame* frame )
		: wxPanel( parent, wxID_ANY, wxDefaultPosition, wxDefaultSize ),
		m_frame( frame )
	{
		wxBoxSizer* s1 = new wxBoxSizer( wxHORIZONTAL );
		m_border_size = new wxSpinCtrl( this, ID_AUI_PaneBorderSize,
										wxString::Format( "%d", m_frame->GetDockArt()->GetMetric( wxAUI_DOCKART_PANE_BORDER_SIZE) ),
										wxDefaultPosition, wxSize( 50, 20 ), wxSP_ARROW_KEYS, 0, 100,
										m_frame->GetDockArt()->GetMetric( wxAUI_DOCKART_PANE_BORDER_SIZE ) );
		s1->Add( 1, 1, 1, wxEXPAND );
		s1->Add( new wxStaticText( this, wxID_ANY, _("Pane Border Size:") ) );
		s1->Add( m_border_size );
		s1->Add( 1, 1, 1, wxEXPAND );
		s1->SetItemMinSize( ( size_t ) 1, 180, 20 );

		wxBoxSizer* s2 = new wxBoxSizer( wxHORIZONTAL );
		m_sash_size = new wxSpinCtrl( this, ID_AUI_SashSize,
									wxString::Format( "%d", m_frame->GetDockArt()->GetMetric( wxAUI_DOCKART_SASH_SIZE ) ),
									wxDefaultPosition, wxSize( 50, 20 ), wxSP_ARROW_KEYS, 0, 100,
									m_frame->GetDockArt()->GetMetric( wxAUI_DOCKART_SASH_SIZE ) );
		s2->Add( 1, 1, 1, wxEXPAND );
		s2->Add( new wxStaticText( this, wxID_ANY, _("Sash Size:") ) );
		s2->Add( m_sash_size );
		s2->Add( 1, 1, 1, wxEXPAND );
		s2->SetItemMinSize( ( size_t )1, 180, 20 );

		wxBoxSizer* s3 = new wxBoxSizer( wxHORIZONTAL );
		m_caption_size = new wxSpinCtrl( this, ID_AUI_CaptionSize, wxString::Format( "%d", m_frame->GetDockArt()->GetMetric( wxAUI_DOCKART_CAPTION_SIZE ) ),
										wxDefaultPosition, wxSize( 50, 20 ), wxSP_ARROW_KEYS, 0, 100,
										m_frame->GetDockArt()->GetMetric( wxAUI_DOCKART_CAPTION_SIZE ) );
		s3->Add( 1, 1, 1, wxEXPAND );
		s3->Add( new wxStaticText( this, wxID_ANY, _("Caption Size:") ) );
		s3->Add( m_caption_size );
		s3->Add( 1, 1, 1, wxEXPAND );
		s3->SetItemMinSize( ( size_t )1, 180, 20 );

		wxBitmap b = CreateColorBitmap( *wxBLACK );

		wxBoxSizer* s4 = new wxBoxSizer( wxHORIZONTAL );
		m_background_color = new wxBitmapButton( this, ID_AUI_BackgroundColor, b, wxDefaultPosition, wxSize( 50, 25 ) );
		s4->Add( 1, 1, 1, wxEXPAND );
		s4->Add( new wxStaticText( this, wxID_ANY, _("Background Color:") ) );
		s4->Add( m_background_color );
		s4->Add( 1, 1, 1, wxEXPAND );
		s4->SetItemMinSize( ( size_t )1, 180, 20 );

		wxBoxSizer* s5 = new wxBoxSizer( wxHORIZONTAL );
		m_sash_color = new wxBitmapButton( this, ID_AUI_SashColor, b, wxDefaultPosition, wxSize( 50, 25 ) );
		s5->Add( 1, 1, 1, wxEXPAND );
		s5->Add( new wxStaticText( this, wxID_ANY, _("Sash Color:") ) );
		s5->Add( m_sash_color );
		s5->Add( 1, 1, 1, wxEXPAND );
		s5->SetItemMinSize( ( size_t )1, 180, 20 );

		wxBoxSizer* s6 = new wxBoxSizer( wxHORIZONTAL );
		m_inactive_caption_color = new wxBitmapButton( this, ID_AUI_InactiveCaptionColor, b, wxDefaultPosition, wxSize( 50, 25 ) );
		s6->Add( 1, 1, 1, wxEXPAND );
		s6->Add( new wxStaticText( this, wxID_ANY, _("Normal Caption:") ) );
		s6->Add( m_inactive_caption_color );
		s6->Add( 1, 1, 1, wxEXPAND );
		s6->SetItemMinSize( ( size_t )1, 180, 20 );

		wxBoxSizer* s7 = new wxBoxSizer( wxHORIZONTAL );
		m_inactive_caption_gradient_color = new wxBitmapButton( this, ID_AUI_InactiveCaptionGradientColor, b, wxDefaultPosition, wxSize( 50, 25 ) );
		s7->Add( 1, 1, 1, wxEXPAND );
		s7->Add( new wxStaticText( this, wxID_ANY, _("Normal Caption Gradient:") ) );
		s7->Add( m_inactive_caption_gradient_color );
		s7->Add( 1, 1, 1, wxEXPAND );
		s7->SetItemMinSize( ( size_t )1, 180, 20 );

		wxBoxSizer* s8 = new wxBoxSizer( wxHORIZONTAL );
		m_inactive_caption_text_color = new wxBitmapButton( this, ID_AUI_InactiveCaptionTextColor, b, wxDefaultPosition, wxSize( 50, 25 ) );
		s8->Add( 1, 1, 1, wxEXPAND);
		s8->Add( new wxStaticText( this, wxID_ANY, _("Normal Caption Text:") ) );
		s8->Add( m_inactive_caption_text_color );
		s8->Add( 1, 1, 1, wxEXPAND );
		s8->SetItemMinSize( ( size_t )1, 180, 20 );

		wxBoxSizer* s9 = new wxBoxSizer( wxHORIZONTAL );
		m_active_caption_color = new wxBitmapButton( this, ID_AUI_ActiveCaptionColor, b, wxDefaultPosition, wxSize( 50, 25 ) );
		s9->Add( 1, 1, 1, wxEXPAND );
		s9->Add( new wxStaticText( this, wxID_ANY, _("Active Caption:") ) );
		s9->Add( m_active_caption_color );
		s9->Add( 1, 1, 1, wxEXPAND );
		s9->SetItemMinSize( ( size_t )1, 180, 20 );

		wxBoxSizer* s10 = new wxBoxSizer( wxHORIZONTAL );
		m_active_caption_gradient_color = new wxBitmapButton( this, ID_AUI_ActiveCaptionGradientColor, b, wxDefaultPosition, wxSize( 50, 25 ) );
		s10->Add( 1, 1, 1, wxEXPAND );
		s10->Add( new wxStaticText( this, wxID_ANY, _("Active Caption Gradient:") ) );
		s10->Add( m_active_caption_gradient_color );
		s10->Add( 1, 1, 1, wxEXPAND );
		s10->SetItemMinSize( ( size_t )1, 180, 20 );

		wxBoxSizer* s11 = new wxBoxSizer( wxHORIZONTAL );
		m_active_caption_text_color = new wxBitmapButton( this, ID_AUI_ActiveCaptionTextColor, b, wxDefaultPosition, wxSize( 50, 25 ) );
		s11->Add( 1, 1, 1, wxEXPAND );
		s11->Add( new wxStaticText( this, wxID_ANY, _("Active Caption Text:") ) );
		s11->Add( m_active_caption_text_color );
		s11->Add( 1, 1, 1, wxEXPAND );
		s11->SetItemMinSize( ( size_t )1, 180, 20 );

		wxBoxSizer* s12 = new wxBoxSizer( wxHORIZONTAL );
		m_border_color = new wxBitmapButton( this, ID_AUI_BorderColor, b, wxDefaultPosition, wxSize( 50, 25 ) );
		s12->Add( 1, 1, 1, wxEXPAND );
		s12->Add( new wxStaticText( this, wxID_ANY, _("Border Color:") ) );
		s12->Add( m_border_color );
		s12->Add( 1, 1, 1, wxEXPAND );
		s12->SetItemMinSize( ( size_t )1, 180, 20 );

		wxBoxSizer* s13 = new wxBoxSizer( wxHORIZONTAL );
		m_gripper_color = new wxBitmapButton( this, ID_AUI_GripperColor, b, wxDefaultPosition, wxSize( 50, 25 ) );
		s13->Add( 1, 1, 1, wxEXPAND );
		s13->Add( new wxStaticText( this, wxID_ANY, _("Gripper Color:") ) );
		s13->Add( m_gripper_color );
		s13->Add( 1, 1, 1, wxEXPAND );
		s13->SetItemMinSize( ( size_t )1, 180, 20 );

		wxGridSizer* grid_sizer = new wxGridSizer( 2 );
		grid_sizer->SetHGap( 5 );
		grid_sizer->Add( s1 );  grid_sizer->Add( s4 );
		grid_sizer->Add( s2 );  grid_sizer->Add( s5 );
		grid_sizer->Add( s3 );  grid_sizer->Add( s13 );
		grid_sizer->Add( 1, 1 ); grid_sizer->Add( s12 );
		grid_sizer->Add( s6 );  grid_sizer->Add( s9 );
		grid_sizer->Add( s7 );  grid_sizer->Add( s10 );
		grid_sizer->Add( s8 );  grid_sizer->Add( s11 );

		wxBoxSizer* cont_sizer = new wxBoxSizer( wxVERTICAL );
		cont_sizer->Add( grid_sizer, 1, wxEXPAND | wxALL, 5 );
		SetSizer( cont_sizer );
		GetSizer()->SetSizeHints( this );
	#if 0
		m_border_size->SetValue( m_frame->GetDockArt()->GetMetric( wxAUI_DOCKART_PANE_BORDER_SIZE ) );
		m_sash_size->SetValue( m_frame->GetDockArt()->GetMetric( wxAUI_DOCKART_SASH_SIZE ) );
		m_caption_size->SetValue( m_frame->GetDockArt()->GetMetric( wxAUI_DOCKART_CAPTION_SIZE ) );
	#endif
		UpdateColors();
	}

private:
	wxBitmap CreateColorBitmap(const wxColour& c)
	{
		wxImage image;
		image.Create( 25,14 );
		for ( int x = 0; x < 25; ++x )
		for ( int y = 0; y < 14; ++y )
		{
			wxColour pixcol = c;
			if ( x == 0 || x == 24 || y == 0 || y == 13 )
				pixcol = *wxBLACK;
			image.SetRGB( x, y, pixcol.Red(), pixcol.Green(), pixcol.Blue() );
		}
		return wxBitmap(image);
	}

	void UpdateColors()
	{
		wxColour bk = m_frame->GetDockArt()->GetColor( wxAUI_DOCKART_BACKGROUND_COLOUR );
		m_background_color->SetBitmapLabel( CreateColorBitmap( bk ) );

		wxColour cap = m_frame->GetDockArt()->GetColor( wxAUI_DOCKART_INACTIVE_CAPTION_COLOUR );
		m_inactive_caption_color->SetBitmapLabel( CreateColorBitmap( cap ) );

		wxColour capgrad = m_frame->GetDockArt()->GetColor( wxAUI_DOCKART_INACTIVE_CAPTION_GRADIENT_COLOUR );
		m_inactive_caption_gradient_color->SetBitmapLabel( CreateColorBitmap( capgrad ) );

		wxColour captxt = m_frame->GetDockArt()->GetColor( wxAUI_DOCKART_INACTIVE_CAPTION_TEXT_COLOUR );
		m_inactive_caption_text_color->SetBitmapLabel( CreateColorBitmap( captxt ) );

		wxColour acap = m_frame->GetDockArt()->GetColor( wxAUI_DOCKART_ACTIVE_CAPTION_COLOUR );
		m_active_caption_color->SetBitmapLabel( CreateColorBitmap(acap ) );

		wxColour acapgrad = m_frame->GetDockArt()->GetColor( wxAUI_DOCKART_ACTIVE_CAPTION_GRADIENT_COLOUR );
		m_active_caption_gradient_color->SetBitmapLabel( CreateColorBitmap( acapgrad ) );

		wxColour acaptxt = m_frame->GetDockArt()->GetColor( wxAUI_DOCKART_ACTIVE_CAPTION_TEXT_COLOUR );
		m_active_caption_text_color->SetBitmapLabel( CreateColorBitmap( acaptxt ) );

		wxColour sash = m_frame->GetDockArt()->GetColor( wxAUI_DOCKART_SASH_COLOUR );
		m_sash_color->SetBitmapLabel( CreateColorBitmap( sash ) );

		wxColour border = m_frame->GetDockArt()->GetColor( wxAUI_DOCKART_BORDER_COLOUR );
		m_border_color->SetBitmapLabel( CreateColorBitmap( border ) );

		wxColour gripper = m_frame->GetDockArt()->GetColor( wxAUI_DOCKART_GRIPPER_COLOUR );
		m_gripper_color->SetBitmapLabel( CreateColorBitmap( gripper ) );
	}

	void OnPaneBorderSize(wxSpinEvent& event)
	{
		m_frame->GetDockArt()->SetMetric( wxAUI_DOCKART_PANE_BORDER_SIZE, event.GetPosition() );
		m_frame->DoUpdate();
	}

	void OnSashSize(wxSpinEvent& event)
	{
		m_frame->GetDockArt()->SetMetric( wxAUI_DOCKART_SASH_SIZE, event.GetPosition() );
		m_frame->DoUpdate();
	}

	void OnCaptionSize(wxSpinEvent& event)
	{
		m_frame->GetDockArt()->SetMetric( wxAUI_DOCKART_CAPTION_SIZE, event.GetPosition() );
		m_frame->DoUpdate();
	}

	void OnSetColor( wxCommandEvent& event )
	{
		wxColourDialog dlg( m_frame );
		dlg.SetTitle( _("Color Picker") );
		if ( dlg.ShowModal() != wxID_OK )
			return;

		int var = 0;
		switch (event.GetId())
		{
		case ID_AUI_BackgroundColor:              var = wxAUI_DOCKART_BACKGROUND_COLOUR; break;
		case ID_AUI_SashColor:                    var = wxAUI_DOCKART_SASH_COLOUR; break;
		case ID_AUI_InactiveCaptionColor:         var = wxAUI_DOCKART_INACTIVE_CAPTION_COLOUR; break;
		case ID_AUI_InactiveCaptionGradientColor: var = wxAUI_DOCKART_INACTIVE_CAPTION_GRADIENT_COLOUR; break;
		case ID_AUI_InactiveCaptionTextColor:     var = wxAUI_DOCKART_INACTIVE_CAPTION_TEXT_COLOUR; break;
		case ID_AUI_ActiveCaptionColor:           var = wxAUI_DOCKART_ACTIVE_CAPTION_COLOUR; break;
		case ID_AUI_ActiveCaptionGradientColor:   var = wxAUI_DOCKART_ACTIVE_CAPTION_GRADIENT_COLOUR; break;
		case ID_AUI_ActiveCaptionTextColor:       var = wxAUI_DOCKART_ACTIVE_CAPTION_TEXT_COLOUR; break;
		case ID_AUI_BorderColor:                  var = wxAUI_DOCKART_BORDER_COLOUR; break;
		case ID_AUI_GripperColor:                 var = wxAUI_DOCKART_GRIPPER_COLOUR; break;
		default: return;
		}

		m_frame->GetDockArt()->SetColor(var, dlg.GetColourData().GetColour());
		m_frame->DoUpdate();
		UpdateColors();
	}

	MainFrame* 			m_frame;
	wxSpinCtrl* 		m_border_size;
	wxSpinCtrl* 		m_sash_size;
	wxSpinCtrl* 		m_caption_size;
	wxBitmapButton* 	m_inactive_caption_text_color;
	wxBitmapButton* 	m_inactive_caption_gradient_color;
	wxBitmapButton* 	m_inactive_caption_color;
	wxBitmapButton* 	m_active_caption_text_color;
	wxBitmapButton* 	m_active_caption_gradient_color;
	wxBitmapButton* 	m_active_caption_color;
	wxBitmapButton* 	m_sash_color;
	wxBitmapButton* 	m_background_color;
	wxBitmapButton* 	m_border_color;
	wxBitmapButton* 	m_gripper_color;

	DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(AuiSettingsPanel, wxPanel)
	EVT_SPINCTRL( 	ID_AUI_PaneBorderSize, 					AuiSettingsPanel::OnPaneBorderSize)
	EVT_SPINCTRL( 	ID_AUI_SashSize, 						AuiSettingsPanel::OnSashSize)
	EVT_SPINCTRL( 	ID_AUI_CaptionSize, 					AuiSettingsPanel::OnCaptionSize)
	EVT_BUTTON( 	ID_AUI_BackgroundColor, 				AuiSettingsPanel::OnSetColor)
	EVT_BUTTON( 	ID_AUI_SashColor, 						AuiSettingsPanel::OnSetColor)
	EVT_BUTTON( 	ID_AUI_InactiveCaptionColor, 			AuiSettingsPanel::OnSetColor)
	EVT_BUTTON( 	ID_AUI_InactiveCaptionGradientColor, 	AuiSettingsPanel::OnSetColor)
	EVT_BUTTON( 	ID_AUI_InactiveCaptionTextColor, 		AuiSettingsPanel::OnSetColor)
	EVT_BUTTON( 	ID_AUI_ActiveCaptionColor, 				AuiSettingsPanel::OnSetColor)
	EVT_BUTTON( 	ID_AUI_ActiveCaptionGradientColor, 		AuiSettingsPanel::OnSetColor)
	EVT_BUTTON( 	ID_AUI_ActiveCaptionTextColor, 			AuiSettingsPanel::OnSetColor)
	EVT_BUTTON( 	ID_AUI_BorderColor, 					AuiSettingsPanel::OnSetColor)
	EVT_BUTTON( 	ID_AUI_GripperColor, 					AuiSettingsPanel::OnSetColor)
END_EVENT_TABLE()

#endif // AUI_SETTINGSPANEL_H_INCLUDED
