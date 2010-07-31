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
#include "about.h"
#include "rad/appdata.h"

#include <wx/mimetype.h>
#include <wx/sizer.h>

class HtmlWindow : public wxHtmlWindow
{
  public:
    HtmlWindow( wxWindow *parent ) : wxHtmlWindow( parent, -1, wxDefaultPosition, wxDefaultSize,
													wxHW_SCROLLBAR_NEVER | wxHW_NO_SELECTION | wxRAISED_BORDER )
    {
    }

    void LaunchBrowser(const wxString& url)
    {
      wxFileType *ft = wxTheMimeTypesManager->GetFileTypeFromExtension("html");
      if (!ft) {
        wxLogError( _("Impossible to determine the file type for extension html.\nPlease edit your MIME types.") );
        return;
      }

      wxString cmd;
      bool ok = ft->GetOpenCommand( &cmd, wxFileType::MessageParameters(url, "") );
      delete ft;

      if ( ok )
          wxExecute( cmd, wxEXEC_ASYNC );
    }

    void OnLinkClicked(const wxHtmlLinkInfo& link)
    {
		::wxLaunchDefaultBrowser( link.GetHref() );
    }
};

AboutDialog::AboutDialog( wxWindow* parent, wxWindowID id, const wxString& title,
						const wxPoint& pos, const wxSize& size, long style )
				: wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* sizer;
	sizer = new wxBoxSizer( wxVERTICAL );
	
	html = new HtmlWindow( this );
	html->LoadFile( wxFileName( AppData()->GetApplicationPath() + wxFILE_SEP_PATH + "resources/about.html" ) );

	sizer->Add( html, 1, wxALL|wxEXPAND, 5 );
	
	button = new wxButton( this, wxID_OK, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sizer->Add( button, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM, 5 );
	
	this->SetSizer( sizer );
	this->Layout();
	
	this->Centre( wxBOTH );

	button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboutDialog::OnButtonEvent ), NULL, this );
}

AboutDialog::~AboutDialog()
{
	button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboutDialog::OnButtonEvent ), NULL, this );
}

void AboutDialog::OnButtonEvent (wxCommandEvent &)
{
	Close();
}
