/////////////////////////////////////////////////////////////////////////////
// Name:        wx/xrc/xh_aui.h
// Purpose:     XRC resource handler for wxAUI
// Author:      Andrea Zanellato
// Created:     2011-09-23
// RCS-ID:      $Id: $
// Copyright:   (c) 2011 Andrea Zanellato
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_XH_AUI_H_
#define _WX_XH_AUI_H_

#if wxUSE_XRC && wxUSE_AUI

#include "wx/xrc/xmlres.h"
#include "wx/aui/framemanager.h"

class WXDLLIMPEXP_XRC wxAuiXmlHandler : public wxXmlResourceHandler
{
public:
    wxAuiXmlHandler();
    virtual ~wxAuiXmlHandler();
    virtual wxObject *DoCreateResource();
    virtual bool CanHandle( wxXmlNode *node );

private:
    wxAuiManager *m_mgr;
    wxWindow     *m_wnd;
    bool          m_isInside;

    wxDECLARE_DYNAMIC_CLASS( wxAuiXmlHandler );
};

#endif //wxUSE_XRC && wxUSE_AUI

#endif //_WX_XH_AUI_H_
