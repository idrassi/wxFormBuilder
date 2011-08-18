///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  6 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "icons/caption.png.h"
#include "icons/designer.png.h"
#include "icons/language.png.h"

#include "prefsdialog.h"

///////////////////////////////////////////////////////////////////////////

_PrefsPageGUI::_PrefsPageGUI( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* sizerGUI;
	sizerGUI = new wxBoxSizer( wxVERTICAL );
	
	
	sizerGUI->Add( 0, 0, 1, 0, 5 );
	
	wxStaticText* lblGUI;
	lblGUI = new wxStaticText( this, wxID_ANY, _("This is where you can configure wxFormBuilder appearance. The first sub-page deals with caption's metrics and colours."), wxDefaultPosition, wxDefaultSize, 0 );
	lblGUI->Wrap( -1 );
	sizerGUI->Add( lblGUI, 0, wxALL|wxEXPAND, 5 );
	
	
	sizerGUI->Add( 0, 0, 1, 0, 5 );
	
	this->SetSizer( sizerGUI );
	this->Layout();
}

_PrefsPageGUI::~_PrefsPageGUI()
{
}

_PrefsPageGUICaps::_PrefsPageGUICaps( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bszGUI;
	bszGUI = new wxBoxSizer( wxVERTICAL );
	
	chkCustPrefs = new wxCheckBox( this, wxID_ANY, _("Use custom settings"), wxDefaultPosition, wxDefaultSize, 0 );
	bszGUI->Add( chkCustPrefs, 0, 0, 5 );
	
	wxStaticBoxSizer* sbsCaptMetrics;
	sbsCaptMetrics = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Metrics") ), wxVERTICAL );
	
	pnlCaptMetrics = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgsSize;
	fgsSize = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgsSize->AddGrowableCol( 0 );
	fgsSize->SetFlexibleDirection( wxBOTH );
	fgsSize->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	txtCaptHeight = new wxStaticText( pnlCaptMetrics, wxID_ANY, _("Height:"), wxDefaultPosition, wxDefaultSize, 0 );
	txtCaptHeight->Wrap( -1 );
	fgsSize->Add( txtCaptHeight, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	spnCaptHeight = new wxSpinCtrl( pnlCaptMetrics, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 120,-1 ), wxSP_ARROW_KEYS, 0, 100, 0 );
	fgsSize->Add( spnCaptHeight, 0, 0, 5 );
	
	txtGrdtDir = new wxStaticText( pnlCaptMetrics, wxID_ANY, _("Gradient Orientation:"), wxDefaultPosition, wxDefaultSize, 0 );
	txtGrdtDir->Wrap( -1 );
	fgsSize->Add( txtGrdtDir, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString choGrdtDirChoices[] = { _("Horizontal"), _("Vertical") };
	int choGrdtDirNChoices = sizeof( choGrdtDirChoices ) / sizeof( wxString );
	choGrdtDir = new wxChoice( pnlCaptMetrics, wxID_ANY, wxDefaultPosition, wxSize( 120,-1 ), choGrdtDirNChoices, choGrdtDirChoices, 0 );
	choGrdtDir->SetSelection( 0 );
	fgsSize->Add( choGrdtDir, 0, 0, 5 );
	
	pnlCaptMetrics->SetSizer( fgsSize );
	pnlCaptMetrics->Layout();
	fgsSize->Fit( pnlCaptMetrics );
	sbsCaptMetrics->Add( pnlCaptMetrics, 1, wxEXPAND | wxALL, 0 );
	
	bszGUI->Add( sbsCaptMetrics, 0, wxEXPAND|wxLEFT|wxRIGHT, 5 );
	
	wxStaticBoxSizer* sbsCaptColors;
	sbsCaptColors = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Colors") ), wxVERTICAL );
	
	pnlCaptColors = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgsCaptColors;
	fgsCaptColors = new wxFlexGridSizer( 0, 4, 0, 0 );
	fgsCaptColors->AddGrowableCol( 0 );
	fgsCaptColors->SetFlexibleDirection( wxBOTH );
	fgsCaptColors->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	txtNormCapt = new wxStaticText( pnlCaptColors, wxID_ANY, _("Normal:"), wxDefaultPosition, wxDefaultSize, 0 );
	txtNormCapt->Wrap( -1 );
	fgsCaptColors->Add( txtNormCapt, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	cpkNormCapt = new wxColourPickerCtrl( pnlCaptColors, wxID_ANY, *wxBLACK, wxDefaultPosition, wxSize( -1,-1 ), wxCLRP_DEFAULT_STYLE );
	cpkNormCapt->SetMinSize( wxSize( 42,24 ) );
	
	fgsCaptColors->Add( cpkNormCapt, 0, 0, 5 );
	
	txtActvCapt = new wxStaticText( pnlCaptColors, wxID_ANY, _("Active:"), wxDefaultPosition, wxDefaultSize, 0 );
	txtActvCapt->Wrap( -1 );
	fgsCaptColors->Add( txtActvCapt, 0, wxALIGN_CENTER_VERTICAL|wxLEFT, 5 );
	
	cpkActvCapt = new wxColourPickerCtrl( pnlCaptColors, wxID_ANY, *wxBLACK, wxDefaultPosition, wxSize( -1,-1 ), wxCLRP_DEFAULT_STYLE );
	cpkActvCapt->SetMinSize( wxSize( 42,24 ) );
	
	fgsCaptColors->Add( cpkActvCapt, 0, 0, 5 );
	
	txtNormGrdt = new wxStaticText( pnlCaptColors, wxID_ANY, _("Normal Gradient:"), wxDefaultPosition, wxDefaultSize, 0 );
	txtNormGrdt->Wrap( -1 );
	fgsCaptColors->Add( txtNormGrdt, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT, 5 );
	
	cpkNormGrdt = new wxColourPickerCtrl( pnlCaptColors, wxID_ANY, *wxBLACK, wxDefaultPosition, wxSize( -1,-1 ), wxCLRP_DEFAULT_STYLE );
	cpkNormGrdt->SetMinSize( wxSize( 42,24 ) );
	
	fgsCaptColors->Add( cpkNormGrdt, 0, 0, 5 );
	
	txtActvGrdt = new wxStaticText( pnlCaptColors, wxID_ANY, _("Active Gradient:"), wxDefaultPosition, wxDefaultSize, 0 );
	txtActvGrdt->Wrap( -1 );
	fgsCaptColors->Add( txtActvGrdt, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5 );
	
	cpkActvGrdt = new wxColourPickerCtrl( pnlCaptColors, wxID_ANY, *wxBLACK, wxDefaultPosition, wxSize( -1,-1 ), wxCLRP_DEFAULT_STYLE );
	cpkActvGrdt->SetMinSize( wxSize( 42,24 ) );
	
	fgsCaptColors->Add( cpkActvGrdt, 0, 0, 5 );
	
	txtNormCaptText = new wxStaticText( pnlCaptColors, wxID_ANY, _("Normal Text:"), wxDefaultPosition, wxDefaultSize, 0 );
	txtNormCaptText->Wrap( -1 );
	fgsCaptColors->Add( txtNormCaptText, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	cpkNormCaptText = new wxColourPickerCtrl( pnlCaptColors, wxID_ANY, *wxBLACK, wxDefaultPosition, wxSize( -1,-1 ), wxCLRP_DEFAULT_STYLE );
	cpkNormCaptText->SetMinSize( wxSize( 42,24 ) );
	
	fgsCaptColors->Add( cpkNormCaptText, 0, 0, 5 );
	
	txtActvCaptText = new wxStaticText( pnlCaptColors, wxID_ANY, _("Active Text:"), wxDefaultPosition, wxDefaultSize, 0 );
	txtActvCaptText->Wrap( -1 );
	fgsCaptColors->Add( txtActvCaptText, 0, wxALIGN_CENTER_VERTICAL|wxLEFT, 5 );
	
	cpkActvCaptText = new wxColourPickerCtrl( pnlCaptColors, wxID_ANY, *wxBLACK, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	cpkActvCaptText->SetMinSize( wxSize( 42,24 ) );
	
	fgsCaptColors->Add( cpkActvCaptText, 0, wxEXPAND, 5 );
	
	pnlCaptColors->SetSizer( fgsCaptColors );
	pnlCaptColors->Layout();
	fgsCaptColors->Fit( pnlCaptColors );
	sbsCaptColors->Add( pnlCaptColors, 1, wxEXPAND | wxALL, 0 );
	
	bszGUI->Add( sbsCaptColors, 0, wxEXPAND|wxLEFT|wxRIGHT, 5 );
	
	this->SetSizer( bszGUI );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _PrefsPageGUICaps::OnUpdateUI ) );
	chkCustPrefs->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _PrefsPageGUICaps::OnToggleCustPrefs ), NULL, this );
}

_PrefsPageGUICaps::~_PrefsPageGUICaps()
{
	// Disconnect Events
	this->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _PrefsPageGUICaps::OnUpdateUI ) );
	chkCustPrefs->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _PrefsPageGUICaps::OnToggleCustPrefs ), NULL, this );
	
}

_PrefsPageLocale::_PrefsPageLocale( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* langSizer;
	langSizer = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbsLang;
	sbsLang = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Locale") ), wxVERTICAL );
	
	pnlBoxLang = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bszBoxLang;
	bszBoxLang = new wxBoxSizer( wxVERTICAL );
	
	chkLang = new wxCheckBox( pnlBoxLang, wxID_ANY, _("Enable Localization"), wxDefaultPosition, wxDefaultSize, 0 );
	chkLang->SetToolTip( _("Enable / Disable wxFormBuilder localization") );
	
	bszBoxLang->Add( chkLang, 0, wxEXPAND|wxLEFT|wxTOP, 5 );
	
	wxFlexGridSizer* fgsLang;
	fgsLang = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgsLang->AddGrowableCol( 1 );
	fgsLang->SetFlexibleDirection( wxBOTH );
	fgsLang->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	lblLang = new wxStaticText( pnlBoxLang, wxID_ANY, _("Locale to use:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblLang->Wrap( -1 );
	fgsLang->Add( lblLang, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	bcbLang = new wxBitmapComboBox( pnlBoxLang, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY ); 
	bcbLang->SetToolTip( _("Select language to use") );
	
	fgsLang->Add( bcbLang, 1, wxALIGN_RIGHT|wxALL|wxEXPAND, 5 );
	
	bszBoxLang->Add( fgsLang, 0, wxEXPAND, 5 );
	
	pnlBoxLang->SetSizer( bszBoxLang );
	pnlBoxLang->Layout();
	bszBoxLang->Fit( pnlBoxLang );
	sbsLang->Add( pnlBoxLang, 1, wxEXPAND, 5 );
	
	langSizer->Add( sbsLang, 0, wxEXPAND|wxLEFT|wxRIGHT, 5 );
	
	this->SetSizer( langSizer );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _PrefsPageLocale::OnUpdateUI ) );
	chkLang->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _PrefsPageLocale::OnToggleLocale ), NULL, this );
}

_PrefsPageLocale::~_PrefsPageLocale()
{
	// Disconnect Events
	this->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _PrefsPageLocale::OnUpdateUI ) );
	chkLang->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _PrefsPageLocale::OnToggleLocale ), NULL, this );
	
}

_PrefsDialog::_PrefsDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 510,360 ), wxDefaultSize );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	mainSizer->SetMinSize( wxSize( 510,360 ) ); 
	tbkPrefs = new wxTreebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBK_DEFAULT );
	
	wxImageList* imgList = new wxImageList( 16, 16 );
	imgList->Add( caption_png_to_wx_bitmap() );
	imgList->Add( designer_png_to_wx_bitmap() );
	imgList->Add( language_png_to_wx_bitmap() );
	
	tbkPrefs->SetImageList( imgList );
	mainSizer->Add( tbkPrefs, 1, wxALL|wxEXPAND, 5 );
	
	buttonSizer = new wxStdDialogButtonSizer();
	buttonSizerOK = new wxButton( this, wxID_OK );
	buttonSizer->AddButton( buttonSizerOK );
	buttonSizerApply = new wxButton( this, wxID_APPLY );
	buttonSizer->AddButton( buttonSizerApply );
	buttonSizerCancel = new wxButton( this, wxID_CANCEL );
	buttonSizer->AddButton( buttonSizerCancel );
	buttonSizer->Realize();
	mainSizer->Add( buttonSizer, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM, 5 );
	
	this->SetSizer( mainSizer );
	this->Layout();
	mainSizer->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _PrefsDialog::OnUpdateUI ) );
}

_PrefsDialog::~_PrefsDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _PrefsDialog::OnUpdateUI ) );
	
}
