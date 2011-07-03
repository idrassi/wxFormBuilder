///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  7 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "prefsdialog.h"

///////////////////////////////////////////////////////////////////////////

_PrefsDialog::_PrefsDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 450,300 ), wxDefaultSize );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	mainSizer->SetMinSize( wxSize( 450,300 ) ); 
	tbkPrefs = new wxTreebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBK_DEFAULT );
	pnlLang = new wxPanel( tbkPrefs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* langSizer;
	langSizer = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbsLang;
	sbsLang = new wxStaticBoxSizer( new wxStaticBox( pnlLang, wxID_ANY, _("Locale") ), wxVERTICAL );
	
	pnlBoxLang = new wxPanel( pnlLang, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
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
	
	langSizer->Add( sbsLang, 0, wxEXPAND, 5 );
	
	pnlLang->SetSizer( langSizer );
	pnlLang->Layout();
	langSizer->Fit( pnlLang );
	tbkPrefs->AddPage( pnlLang, _("Language"), false );
	pnlGUI = new wxPanel( tbkPrefs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bszGUI;
	bszGUI = new wxBoxSizer( wxVERTICAL );
	
	chkCustPrefs = new wxCheckBox( pnlGUI, wxID_ANY, _("Use custom settings"), wxDefaultPosition, wxDefaultSize, 0 );
	bszGUI->Add( chkCustPrefs, 0, 0, 5 );
	
	wxFlexGridSizer* fgsSize;
	fgsSize = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgsSize->AddGrowableCol( 0 );
	fgsSize->SetFlexibleDirection( wxBOTH );
	fgsSize->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	txtCaptHeight = new wxStaticText( pnlGUI, wxID_ANY, _("Caption Height:"), wxDefaultPosition, wxDefaultSize, 0 );
	txtCaptHeight->Wrap( -1 );
	fgsSize->Add( txtCaptHeight, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	spnCaptHeight = new wxSpinCtrl( pnlGUI, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 120,-1 ), wxSP_ARROW_KEYS, 0, 100, 0 );
	fgsSize->Add( spnCaptHeight, 0, 0, 5 );
	
	
	fgsSize->Add( 0, 5, 1, wxEXPAND, 5 );
	
	
	fgsSize->Add( 0, 5, 1, wxEXPAND, 5 );
	
	txtGrdtDir = new wxStaticText( pnlGUI, wxID_ANY, _("Caption Gradient Orientation:"), wxDefaultPosition, wxDefaultSize, 0 );
	txtGrdtDir->Wrap( -1 );
	fgsSize->Add( txtGrdtDir, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString choGrdtDirChoices[] = { _("Horizontal"), _("Vertical") };
	int choGrdtDirNChoices = sizeof( choGrdtDirChoices ) / sizeof( wxString );
	choGrdtDir = new wxChoice( pnlGUI, wxID_ANY, wxDefaultPosition, wxSize( 120,-1 ), choGrdtDirNChoices, choGrdtDirChoices, 0 );
	choGrdtDir->SetSelection( 0 );
	fgsSize->Add( choGrdtDir, 0, 0, 5 );
	
	
	fgsSize->Add( 0, 5, 1, wxEXPAND, 5 );
	
	
	fgsSize->Add( 0, 5, 1, wxEXPAND, 5 );
	
	bszGUI->Add( fgsSize, 0, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgsColors;
	fgsColors = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgsColors->AddGrowableCol( 0 );
	fgsColors->SetFlexibleDirection( wxBOTH );
	fgsColors->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	txtNormCapt = new wxStaticText( pnlGUI, wxID_ANY, _("Normal Caption:"), wxDefaultPosition, wxDefaultSize, 0 );
	txtNormCapt->Wrap( -1 );
	fgsColors->Add( txtNormCapt, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	cpkNormCapt = new wxColourPickerCtrl( pnlGUI, wxID_ANY, *wxBLACK, wxDefaultPosition, wxSize( -1,-1 ), wxCLRP_DEFAULT_STYLE );
	cpkNormCapt->SetMinSize( wxSize( 42,24 ) );
	
	fgsColors->Add( cpkNormCapt, 0, 0, 5 );
	
	txtActvCapt = new wxStaticText( pnlGUI, wxID_ANY, _("Active Caption:"), wxDefaultPosition, wxDefaultSize, 0 );
	txtActvCapt->Wrap( -1 );
	fgsColors->Add( txtActvCapt, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	cpkActvCapt = new wxColourPickerCtrl( pnlGUI, wxID_ANY, *wxBLACK, wxDefaultPosition, wxSize( -1,-1 ), wxCLRP_DEFAULT_STYLE );
	cpkActvCapt->SetMinSize( wxSize( 42,24 ) );
	
	fgsColors->Add( cpkActvCapt, 0, 0, 5 );
	
	
	fgsColors->Add( 0, 5, 1, wxEXPAND, 5 );
	
	
	fgsColors->Add( 0, 5, 1, wxEXPAND, 5 );
	
	txtNormGrdt = new wxStaticText( pnlGUI, wxID_ANY, _("Normal Caption Gradient:"), wxDefaultPosition, wxDefaultSize, 0 );
	txtNormGrdt->Wrap( -1 );
	fgsColors->Add( txtNormGrdt, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	cpkNormGrdt = new wxColourPickerCtrl( pnlGUI, wxID_ANY, *wxBLACK, wxDefaultPosition, wxSize( -1,-1 ), wxCLRP_DEFAULT_STYLE );
	cpkNormGrdt->SetMinSize( wxSize( 42,24 ) );
	
	fgsColors->Add( cpkNormGrdt, 0, 0, 5 );
	
	txtActvGrdt = new wxStaticText( pnlGUI, wxID_ANY, _("Active Caption Gradient:"), wxDefaultPosition, wxDefaultSize, 0 );
	txtActvGrdt->Wrap( -1 );
	fgsColors->Add( txtActvGrdt, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	cpkActvGrdt = new wxColourPickerCtrl( pnlGUI, wxID_ANY, *wxBLACK, wxDefaultPosition, wxSize( -1,-1 ), wxCLRP_DEFAULT_STYLE );
	cpkActvGrdt->SetMinSize( wxSize( 42,24 ) );
	
	fgsColors->Add( cpkActvGrdt, 0, 0, 5 );
	
	
	fgsColors->Add( 0, 5, 1, wxEXPAND, 5 );
	
	
	fgsColors->Add( 0, 5, 1, wxEXPAND, 5 );
	
	txtNormCaptText = new wxStaticText( pnlGUI, wxID_ANY, _("Normal Caption Text:"), wxDefaultPosition, wxDefaultSize, 0 );
	txtNormCaptText->Wrap( -1 );
	fgsColors->Add( txtNormCaptText, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	cpkNormCaptText = new wxColourPickerCtrl( pnlGUI, wxID_ANY, *wxBLACK, wxDefaultPosition, wxSize( -1,-1 ), wxCLRP_DEFAULT_STYLE );
	cpkNormCaptText->SetMinSize( wxSize( 42,24 ) );
	
	fgsColors->Add( cpkNormCaptText, 0, 0, 5 );
	
	txtActvCaptText = new wxStaticText( pnlGUI, wxID_ANY, _("Active Caption Text:"), wxDefaultPosition, wxDefaultSize, 0 );
	txtActvCaptText->Wrap( -1 );
	fgsColors->Add( txtActvCaptText, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	cpkActvCaptText = new wxColourPickerCtrl( pnlGUI, wxID_ANY, *wxBLACK, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	cpkActvCaptText->SetMinSize( wxSize( 42,24 ) );
	
	fgsColors->Add( cpkActvCaptText, 0, wxEXPAND, 5 );
	
	bszGUI->Add( fgsColors, 1, wxEXPAND, 5 );
	
	pnlGUI->SetSizer( bszGUI );
	pnlGUI->Layout();
	bszGUI->Fit( pnlGUI );
	tbkPrefs->AddPage( pnlGUI, _("GUI"), false );
	mainSizer->Add( tbkPrefs, 1, wxEXPAND | wxALL, 5 );
	
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
	chkLang->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _PrefsDialog::OnToggleLocale ), NULL, this );
	buttonSizerApply->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _PrefsDialog::OnClose ), NULL, this );
	buttonSizerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _PrefsDialog::OnClose ), NULL, this );
}

_PrefsDialog::~_PrefsDialog()
{
	// Disconnect Events
	chkLang->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _PrefsDialog::OnToggleLocale ), NULL, this );
	buttonSizerApply->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _PrefsDialog::OnClose ), NULL, this );
	buttonSizerOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _PrefsDialog::OnClose ), NULL, this );
	
}
