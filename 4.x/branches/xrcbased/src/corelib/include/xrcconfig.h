/**
 * @file    xrcconfig.h
 * @author  Andrea Zanellato (zanellato.andrea@gmail.com)
 * @date    2011/09/22
 * @version 0.0.1
 */
#ifndef __WXFB_XRCCONFIG_H__
#define __WXFB_XRCCONFIG_H__

#include "defs.h"
#include "utils/singleton.h"

#include <wx/xml/xml.h>

class WXDLLIMPEXP_WXFBCORE XRCConfig : public Singleton< XRCConfig >
{
public:
    bool AddObjectRef( const wxString &ref, const wxString &name );
    bool AddProperty( const wxString &objName, const wxString &propName, const wxString &propValue );
    void Initialize();
    bool Load( const wxString &fileName );
    bool Save( const wxString &fileName );

protected:
    wxXmlDocument m_xrcDoc;

    friend class Singleton< XRCConfig >;
};

#endif //__WXFB_XRCCONFIG_H__
