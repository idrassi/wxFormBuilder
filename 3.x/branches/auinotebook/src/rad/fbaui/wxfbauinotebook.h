#ifndef WXFBAUINOTEBOOK_H
#define WXFBAUINOTEBOOK_H

#include <wx/aui/auibook.h>


class wxFBAuiNotebook : public wxAuiNotebook
{
public:
	wxFBAuiNotebook(wxWindow* parent,
			  wxWindowID id = wxID_ANY,
			  const wxPoint& pos = wxDefaultPosition,
			  const wxSize& size = wxDefaultSize,
			  long style = wxAUI_NB_DEFAULT_STYLE);
	virtual ~wxFBAuiNotebook();

	wxString GetPageOrder();
};

#endif // WXFBAUINOTEBOOK_H
