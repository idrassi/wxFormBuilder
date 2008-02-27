#include "wxfbauinotebook.h"
#include <wx/config.h>

wxFBAuiNotebook::wxFBAuiNotebook( wxWindow *parent,
                                  wxWindowID id,
                                  const wxPoint& pos,
                                  const wxSize& size,
                                  long style ) : wxAuiNotebook( parent, id, pos, size, style )
{
}

wxString wxFBAuiNotebook::GetPageOrder()
{
	wxString pageOrder;
	wxAuiNotebookPageArray& pages = GetActiveTabCtrl()->GetPages();
	for ( size_t i = 0; i < pages.GetCount(); ++i )
	{
		pageOrder << pages[i].caption << wxT(",");
	}
	return pageOrder;
}

wxFBAuiNotebook::~wxFBAuiNotebook()
{
}
