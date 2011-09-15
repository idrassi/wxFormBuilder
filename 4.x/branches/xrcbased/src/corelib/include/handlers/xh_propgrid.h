/////////////////////////////////////////////////////////////////////////////
// Name:        xh_propgrid.h
// Purpose:     XML resource handler for wxPropertyGrid
// Author:      Jaakko Salli
// Modified by:
// Created:     May-16-2007
// RCS-ID:      $Id:
// Copyright:   (c) Jaakko Salli
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_XH_PROPGRID_H_
#define _WX_XH_PROPGRID_H_

/*

  NOTE: relevant source file, xh_propgrid.cpp is *not* included in the
    wxPropertyGrid library (to prevent xrc-lib dependency). To use this
    code, you will need to separately add src/xh_propgrid.cpp to your
    application.

*/
#include "defs.h"

#if wxUSE_XRC && wxCHECK_VERSION(2,8,0)

#include "wx/xrc/xmlres.h"

#include "wx/propgrid/propgrid.h"

#if wxCHECK_VERSION(2,9,0)
    #include "wx/propgrid/propgridpagestate.h"
    #define wxPropertyGridState wxPropertyGridPageState
#endif

#if defined(wxPG_INCLUDE_MANAGER) || wxCHECK_VERSION(2,9,0)
    #include "wx/propgrid/manager.h"
#endif

class WXDLLIMPEXP_WXFBCORE wxPropertyGridXmlHandler : public wxXmlResourceHandler
{
    friend class wxPropertyGridXrcPopulator;
    DECLARE_DYNAMIC_CLASS(wxPropertyGridXmlHandler)

public:
    wxPropertyGridXmlHandler();
    virtual wxObject *DoCreateResource();
    virtual bool CanHandle(wxXmlNode *node);

    void InitPopulator();
    void PopulatePage( wxPropertyGridState* state );
    void DonePopulator();

    void HandlePropertyGridParams();

private:
    wxPropertyGrid*             m_pg;
    wxPropertyGridPopulator*    m_populator;

#if defined(wxPG_INCLUDE_MANAGER) || wxCHECK_VERSION(2,9,0)
    wxPropertyGridManager*      m_manager;
#endif
};

#endif // wxUSE_XRC && wxCHECK_VERSION(2,8,0)

#endif // _WX_XH_PROPGRID_H_
