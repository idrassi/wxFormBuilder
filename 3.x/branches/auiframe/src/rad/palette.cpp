///////////////////////////////////////////////////////////////////////////////
//
// wxFormBuilder - A Visual Dialog Editor for wxWidgets.
// Copyright (C) 2005 José Antonio Hurtado
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
// Written by
//   José Antonio Hurtado - joseantonio.hurtado@gmail.com
//   Juan Antonio Ortega  - jortegalalmolda@gmail.com
//
///////////////////////////////////////////////////////////////////////////////

#include "palette.h"
#include "model/objectbase.h"
#include "bitmaps.h"
#include "utils/debug.h"
#include "utils/wxfbdefs.h"
#include "utils/typeconv.h"
#include "rad/title.h"
#include "wx/config.h"
#include <rad/appdata.h>
#include "auitbarart.h"

#ifdef __WXMAC__
	#include <wx/tooltip.h>
#endif

#define ID_PALETTE_BUTTON 999

#ifndef WXFB_USE_AUIBOOK
    #ifdef __WXGTK__
        #if wxCHECK_VERSION( 2, 8, 0 )
            #define DRAG_OPTION 0
        #else
            #define DRAG_OPTION wxFNB_NODRAG
        #endif
    #else
        #define DRAG_OPTION 0
    #endif
#endif

wxWindowID wxFbPalette::nextId = wxID_HIGHEST + 1000;

BEGIN_EVENT_TABLE( wxFbPalette, wxPanel )
	#ifdef __WXMAC__
		EVT_BUTTON( -1, wxFbPalette::OnButtonClick )
	#else
		EVT_TOOL(-1, wxFbPalette::OnButtonClick)
	#endif
    #ifndef WXFB_USE_AUITOOLBAR
	    EVT_SPIN_UP( -1, wxFbPalette::OnSpinUp )
	    EVT_SPIN_DOWN( -1, wxFbPalette::OnSpinDown )
    #endif
END_EVENT_TABLE()

wxFbPalette::wxFbPalette( wxWindow *parent, int id ) : wxPanel( parent, id ), m_notebook( NULL )
{
}

#ifdef WXFB_USE_AUITOOLBAR
void wxFbPalette::PopulateToolbar( PObjectPackage pkg, wxAuiToolBar *toolbar )
#else
void wxFbPalette::PopulateToolbar( PObjectPackage pkg, wxToolBar *toolbar )
#endif
{
#ifdef WXFB_USE_AUITOOLBAR
	wxAuiToolBarItemArray auitb_items;
	wxAuiToolBarItemArray auitb_pItms;
#endif

	unsigned int j = 0;
	while ( j < pkg->GetObjectCount() )
	{
		PObjectInfo info = pkg->GetObjectInfo( j );
		if ( info->IsStartOfGroup() )
		{
			toolbar->AddSeparator();

#ifdef WXFB_USE_AUITOOLBAR
			wxAuiToolBarItem sep;
			sep.SetKind( wxITEM_SEPARATOR );
			auitb_items.Add( sep );
#endif
		}
		if ( NULL == info->GetComponent() )
		{
#if wxVERSION_NUMBER < 2900
			Debug::Print( wxT( "Missing Component for Class \"%s\" of Package \"%s\"." ), info->GetClassName().c_str(), pkg->GetPackageName().c_str() );
#else
			Debug::Print( "Missing Component for Class \"" + info->GetClassName() + "\" of Package \"" + pkg->GetPackageName() + "\"." );
#endif
		}
		else
		{
			wxString widget( info->GetClassName() );

			wxBitmap icon = info->GetIconFile();

			#ifdef __WXMAC__
				wxBitmapButton* button = new wxBitmapButton( toolbar, nextId++, icon );
				button->SetToolTip( widget );
				toolbar->AddControl( button );
			#else
				#ifdef WXFB_USE_AUITOOLBAR
					wxAuiToolBarItem item;
					item.SetKind( wxITEM_NORMAL );
					item.SetId( nextId );
					item.SetLabel( widget );
					item.SetBitmap( icon );
					auitb_items.Add( item );
				#endif
				toolbar->AddTool(nextId++, widget, icon, widget);
			#endif

			toolbar->Realize();
		}
		j++;
	}
#ifdef WXFB_USE_AUITOOLBAR
	toolbar->SetArtProvider( new wxFBAuiToolBarArt() );
	toolbar->SetCustomOverflowItems( auitb_items, auitb_pItms );
#endif
}

void wxFbPalette::Create()
{
	wxBoxSizer *top_sizer = new wxBoxSizer( wxVERTICAL );

	long nbStyle;
	wxConfigBase* config = wxConfigBase::Get();

#ifdef WXFB_USE_AUIBOOK
	config->Read( wxT("/palette/auinbook_style"), &nbStyle, wxAUI_NB_TAB_MOVE | wxAUI_NB_WINDOWLIST_BUTTON );

	m_notebook = new wxAuiNotebook( this, -1, wxDefaultPosition, wxDefaultSize, nbStyle );
#else
	config->Read( wxT( "/palette/notebook_style" ), &nbStyle, wxFNB_NO_X_BUTTON | wxFNB_NO_NAV_BUTTONS | DRAG_OPTION | wxFNB_DROPDOWN_TABS_LIST  | wxFNB_VC8 | wxFNB_CUSTOM_DLG );

	m_notebook = new wxFlatNotebook( this, -1, wxDefaultPosition, wxDefaultSize, FNB_STYLE_OVERRIDES( nbStyle ) );
	m_notebook->SetCustomizeOptions( wxFNB_CUSTOM_TAB_LOOK | wxFNB_CUSTOM_ORIENTATION | wxFNB_CUSTOM_LOCAL_DRAG );
#endif

	unsigned int pkg_count = AppData()->GetPackageCount();

	Debug::Print( wxT( "[Palette] Pages %d" ), pkg_count );

	// Populate icon vector
	for ( unsigned int j = 0; j < pkg_count;j++ )
	{
		PObjectPackage pkg = AppData()->GetPackage( j );

#ifndef WXFB_USE_AUIBOOK
		m_icons.Add( pkg->GetPackageIcon() );
#endif
	}

#ifndef WXFB_USE_AUIBOOK
	// Add icons to notebook
	m_notebook->SetImageList( &m_icons );
#endif

	for ( unsigned int i = 0; i < pkg_count;i++ )
	{
		PObjectPackage pkg = AppData()->GetPackage( i );
		wxString pkg_name = pkg->GetPackageName();

		wxPanel *panel = new wxPanel( m_notebook, -1 );
		//panel->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DFACE ) );
		wxBoxSizer *sizer = new wxBoxSizer( wxHORIZONTAL );

		wxPanel *tbPanel = new wxPanel( panel, -1 );
		//tbPanel->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DFACE ) );
		wxBoxSizer *tbSizer = new wxBoxSizer( wxHORIZONTAL );

#ifdef WXFB_USE_AUITOOLBAR
		wxAuiToolBar *toolbar = new wxAuiToolBar( tbPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_TB_OVERFLOW );
#else
		wxPanel *sbPanel = new wxPanel( panel, -1 );
		//sbPanel->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DFACE ) );
		wxBoxSizer *sbSizer = new wxBoxSizer( wxHORIZONTAL );

		wxToolBar *toolbar = new wxToolBar( tbPanel, -1, wxDefaultPosition, wxDefaultSize, wxTB_NODIVIDER | wxTB_FLAT );
		//toolbar->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DFACE ) );
#endif
		toolbar->SetToolBitmapSize( wxSize( 22, 22 ) );

		PopulateToolbar( pkg, toolbar );
		m_tv.push_back( toolbar );

		tbSizer->Add( toolbar, 1, wxEXPAND | wxALIGN_CENTER_VERTICAL );
		tbPanel->SetSizer( tbSizer );

#ifndef WXFB_USE_AUITOOLBAR
		wxSpinButton *sb = new wxSpinButton( sbPanel, -1, wxDefaultPosition, wxDefaultSize, wxSP_HORIZONTAL );
		sb->SetRange( 0, ( int )pkg->GetObjectCount() - 1 );
		sb->SetValue( 0 );
		m_posVector.push_back( 0 );
		sbSizer->Add( sb, 0, wxEXPAND );//wxALL | wxALIGN_TOP, 0);
		sbPanel->SetSizer( sbSizer );
#endif
		sizer->Add( tbPanel, 1, wxEXPAND, 0 );

#ifndef WXFB_USE_AUITOOLBAR
		sizer->Add( sbPanel, 0, wxEXPAND, 0 );
#endif
		panel->SetAutoLayout( true );
		panel->SetSizer( sizer );

		sizer->Fit( panel );
		sizer->SetSizeHints( panel );

#ifdef WXFB_USE_AUIBOOK
		m_notebook->AddPage( panel, pkg_name, false, pkg->GetPackageIcon() );
#else
		m_notebook->AddPage( panel, pkg_name, false, i );
#endif
	}
	//Title *title = new Title( this, wxT("Component Palette") );
	//top_sizer->Add(title,0,wxEXPAND,0);
	top_sizer->Add( m_notebook, 1, wxEXPAND, 0 );
	SetAutoLayout( true );
	SetSizer( top_sizer );
	top_sizer->Fit( this );
	top_sizer->SetSizeHints( this );
}
#ifndef WXFB_USE_AUITOOLBAR
void wxFbPalette::OnSpinUp( wxSpinEvent& )
{
	int page = m_notebook->GetSelection();
	PObjectPackage pkg = AppData()->GetPackage( page );

	if (( int )pkg->GetObjectCount() - m_posVector[page] - 1 <= 0 ) return;

	m_posVector[page]++;
	wxToolBar *toolbar = m_tv[page];
	toolbar->DeleteToolByPos( 0 );
	toolbar->Realize();
}

void wxFbPalette::OnSpinDown( wxSpinEvent& )
{
	int page = m_notebook->GetSelection();
	if ( m_posVector[page] <= 0 ) return;

	m_posVector[page]--;
	wxToolBar *toolbar = m_tv[page];
	PObjectPackage pkg = AppData()->GetPackage( page );
	wxString widget( pkg->GetObjectInfo( m_posVector[page] )->GetClassName() );
	wxBitmap icon = pkg->GetObjectInfo( m_posVector[page] )->GetIconFile();

#ifdef __WXMAC__
		wxBitmapButton* button = new wxBitmapButton( toolbar, nextId++, icon );
		button->SetToolTip( widget );
		toolbar->InsertControl( 0, button );
#else
	#if wxVERSION_NUMBER < 2900
		toolbar->InsertTool( 0, nextId++, icon, wxNullBitmap, false, NULL, widget, widget );
	#else
		toolbar->InsertTool( 0, nextId++, widget, icon );
	#endif
#endif //__WXMAC__

	toolbar->Realize();
}
#endif // WXFB_USE_AUITOOLBAR

void wxFbPalette::OnButtonClick( wxCommandEvent &event )
{
#ifdef __WXMAC__
	wxWindow* win = dynamic_cast< wxWindow* >( event.GetEventObject() );
	if ( win != 0 )
	{
		AppData()->CreateObject( win->GetToolTip()->GetTip() );
	}
#else
	for ( unsigned int i = 0; i < m_tv.size(); i++ )
	{
#ifdef WXFB_USE_AUITOOLBAR
		if ( m_tv[i]->FindTool( event.GetId() ) )
#else
		if ( m_tv[i]->FindById( event.GetId() ) )
#endif
		{
			wxString name = m_tv[i]->GetToolShortHelp( event.GetId() );
			AppData()->CreateObject( name );
			return;
		}
	}
#endif //__WXMAC__
}

wxFbPalette::~wxFbPalette()
{
	size_t pageCount = m_notebook->GetPageCount();

	wxString      separator = wxT(",");
	if ( pageCount > 0 )
	{
		wxString pages;

#ifdef WXFB_USE_AUIBOOK
		std::vector<wxWindow*> auibars;
//		arrangeTabOrder( auibars );
		size_t idx;

		for ( size_t i = 0; i < pageCount; ++i )
		{
#ifdef WXFB_USE_AUITOOLBAR
			wxAuiToolBar* tbar = dynamic_cast< wxAuiToolBar* >( auibars.at( i ) );
#else
			wxToolBar* tbar = dynamic_cast< wxAuiToolBar* >( auibars.at( i ) );
#endif
			idx = 0;

			while ( tbar != m_tv[idx] )
				++idx;

			if ( i == pageCount - 1 )
				separator = wxT("");

			pages << m_notebook->GetPageText( idx ) << separator;
		}
#else
		for ( size_t i = 0; i < pageCount; ++i )
		{
			if ( i == pageCount-1 )
				separator = wxT("");

			pages << m_notebook->GetPageText( i ) << separator;
		}
#endif //WXFB_USE_AUIBOOK

		wxConfigBase* config = wxConfigBase::Get();

#ifdef WXFB_USE_AUIBOOK
		config->Write( wxT("/palette/auinbook_style"), GetWindowStyleFlag() );
#else
		config->Write( wxT("/palette/notebook_style"), m_notebook->GetWindowStyleFlag() );
#endif
		config->Write( wxT("/palette/pageOrder"), pages );
	}
}
#if 0
//ifdef WXFB_USE_AUIBOOK

// Workaround for incorrect tab order in wxAuiNotebook
// Got from Eran's codelite notebook_ex.cpp ( GetEditorsInOrder() )
void wxFbPalette::arrangeTabOrder( std::vector<wxWindow*> &pages )
{
	std::vector<wxWindow*> all_pages;
	std::set<wxAuiTabCtrl*> ctrls;
	for (size_t pg = 0; pg < m_notebook->GetPageCount(); ++pg) {
		wxAuiTabCtrl* ctrl;
		int ctrl_idx;
		wxWindow* win = m_notebook->GetPage(pg);
		if (win && m_notebook->FindTab(win, &ctrl, &ctrl_idx)) {
			ctrls.insert(ctrl);
			all_pages.push_back(win);
		}
	}
	std::set<wxAuiTabCtrl*>::const_iterator it;
	for (it = ctrls.begin(); it != ctrls.end(); ++it) {
		wxAuiTabCtrl* ctrl = *it;
		int y = ctrl->GetRect().height / 2;
		int x_offset = ctrl->GetArtProvider()->GetIndentSize() + 2;
		wxWindow* previouspage = NULL;
		do {
			wxWindow* page;
			int x = 0;
			do {
				page = NULL;
				x += 10;
				bool hit = ctrl->TabHitTest(x_offset+x, y, &page);
				if (!hit && x_offset+x >= ctrl->GetRect().width) {
					break;
				}
			}
			while ((!page) || page == previouspage);
			if (!page) {
				previouspage = NULL;
				break;
			}
			pages.push_back(page);
			for (size_t p=0; p < all_pages.size(); ++p) {
				if (page == *(all_pages.begin()+p)) {
					all_pages.erase(all_pages.begin()+p);
					break;
				}
				wxCHECK_RET(p+1 < all_pages.size(), wxT("Trying to erase a page not in the vector"));
			}
			x_offset += x;
			previouspage = page;
		}
		 while (x_offset < ctrl->GetRect().width);
	}
	if ( !all_pages.empty() ) {
		pages.insert( pages.begin(), all_pages.begin(), all_pages.end() );
	}
}
#endif //WXFB_USE_AUIBOOK
