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

#include "appdata.h"
#include "bitmaps.h"
#include "palette.h"
#include "model/objectbase.h"
#include "utils/debug.h"
#include "utils/wxfbdefs.h"
#include "utils/typeconv.h"

#include <wx/config.h>

BEGIN_EVENT_TABLE( Palette, wxPanel )
	EVT_TOOL( wxID_ANY, Palette::OnButtonClick )
END_EVENT_TABLE()

Palette::Palette( wxWindow *parent, int id )
		: wxPanel( parent, id ), m_notebook( NULL )
{
}

void Palette::PopulateToolbar( PObjectPackage pkg, wxAuiToolBar *toolbar )
{
	unsigned int j = 0;
	while ( j < pkg->GetObjectCount() )
	{
		PObjectInfo info = pkg->GetObjectInfo( j );
		if ( info->IsStartOfGroup() )
			toolbar->AddSeparator();

		if ( NULL == info->GetComponent() )
		{
			wxString msg = _("Missing Component for Class \"") + info->GetClassName() + _("\" of Package \"") + pkg->GetPackageName() + "\"";
			Debug::Print( msg );
		}
		else
		{
			wxString widget( info->GetClassName() );
			int tid = wxNewId();
			wxBitmap icon = info->GetIconFile();

			toolbar->AddTool( tid, widget, icon, widget );
			toolbar->Realize();
		}
		j++;
	}
}

void Palette::Create()
{
	wxBoxSizer *top_sizer = new wxBoxSizer( wxVERTICAL );

	long nbStyle = wxAUI_NB_SCROLL_BUTTONS | wxAUI_NB_TAB_MOVE | wxAUI_NB_WINDOWLIST_BUTTON;
	wxConfigBase* config = wxConfigBase::Get();
	config->Read( "/palette/notebook_style", &nbStyle );

	m_notebook = new wxAuiNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, nbStyle );

	unsigned int pkg_count = AppData()->GetPackageCount();

	Debug::Print( _("[Palette] Pages %d"), pkg_count );

	// Populate icon vector
	for ( unsigned int j = 0; j < pkg_count; j++ )
		PObjectPackage pkg = AppData()->GetPackage( j );

	for ( unsigned int i = 0; i < pkg_count; i++ )
	{
		PObjectPackage 	pkg 		= AppData()->GetPackage( i );
		wxString 		pkg_name 	= pkg->GetPackageName();
		wxAuiToolBar* 	toolbar 	= new wxAuiToolBar( m_notebook, wxID_ANY, wxDefaultPosition,
														wxDefaultSize, wxAUI_TB_OVERFLOW );
		PopulateToolbar( pkg, toolbar );
		m_tv.push_back( toolbar );

		m_notebook->AddPage( toolbar, pkg_name, false, pkg->GetPackageIcon() );
	}
	top_sizer->Add( m_notebook, 1, wxEXPAND, 0 );
	SetSizer( top_sizer );
	top_sizer->Fit( this );
}

void Palette::OnButtonClick( wxCommandEvent &event )
{
	for ( unsigned int i = 0; i < m_tv.size(); i++ )
	{
		if ( m_tv[i]->GetToolIndex( event.GetId() ) != wxNOT_FOUND )
		{
			wxString name = m_tv[i]->GetToolShortHelp( event.GetId() );
			AppData()->CreateObject( name );
			return;
		}
	}
}

Palette::~Palette()
{
	wxConfigBase* 	config 		= wxConfigBase::Get();
	size_t 			pageCount 	= m_notebook->GetPageCount();
	wxString 		separator 	= ",";
	if ( pageCount > 0 )
	{
		wxString pages;
		for ( size_t i = 0; i < pageCount; i++ )
		{
			if ( i == pageCount-1 )
				separator = "";
			pages << m_notebook->GetPageText( i ) << separator;
		}
		config->Write( "/palette/pageOrder", pages );
	}
	config->Write( "/palette/notebook_style", m_notebook->GetWindowStyleFlag() );
}
