/**
    @file    xrcconfig.h
    @author  Andrea Zanellato (zanellato.andrea@gmail.com)
    @date    2011/09/22
    @version 0.0.1
 */
#include "xrcconfig.h"

#include <wx/stdpaths.h>

void XRCConfig::Initialize()
{
    wxXmlNode      *xrcRoot = new wxXmlNode( wxXML_ELEMENT_NODE, "resource" );
    wxXmlAttribute *xrcNS   = new wxXmlAttribute("xmlns", "http://www.wxwidgets.org/wxxrc");
    wxXmlAttribute *xrcVer  = new wxXmlAttribute("version", "2.5.3.0");

    xrcRoot->AddAttribute( xrcNS );
    xrcRoot->AddAttribute( xrcVer );

    m_xrcDoc.SetRoot( xrcRoot );
}

bool XRCConfig::AddObjectRef( const wxString &ref, const wxString &name )
{
    wxXmlNode *root = m_xrcDoc.GetRoot();
    if ( !root ) return false;

    wxXmlNode      *objNode = new wxXmlNode( wxXML_ELEMENT_NODE, "object_ref" );
    wxXmlAttribute *objRef  = new wxXmlAttribute( "ref", ref );
    wxXmlAttribute *objName = new wxXmlAttribute( "name", name );

    objNode->AddAttribute( objName );
    objNode->AddAttribute( objRef );

    root->AddChild( objNode );
    return true;
}

bool XRCConfig::AddProperty( const wxString &objName, const wxString &propName, const wxString &propValue )
{
    wxXmlNode *root = m_xrcDoc.GetRoot();
    if ( !root ) return false;

    wxXmlNode *objNode = root->GetChildren();
    while ( objNode )
    {
        if ( objNode->GetName() == "object_ref" )
        {
            wxString attrName = objNode->GetAttribute("name");
            if ( attrName == objName )
            {
                wxXmlNode *propNode = objNode->GetChildren();
                while ( propNode )
                {
                    if ( propNode->GetName() == propName )
                    {
                        wxXmlNode *propVal = propNode->GetChildren();
                        propVal->SetContent( propValue );
                        return true;
                    }
                    propNode = propNode->GetNext();
                }

                propNode = new wxXmlNode( objNode, wxXML_ELEMENT_NODE, propName );
                new wxXmlNode( propNode, wxXML_TEXT_NODE, wxEmptyString, propValue );

                return true;
            }
        }
        objNode = objNode->GetNext();
    }
    return false;
}

bool XRCConfig::Load( const wxString &fileName )
{
    return m_xrcDoc.Load( wxStandardPaths::Get().GetUserConfigDir() + wxFILE_SEP_PATH + fileName );
}

bool XRCConfig::Save( const wxString &fileName )
{
    return m_xrcDoc.Save( wxStandardPaths::Get().GetUserConfigDir() + wxFILE_SEP_PATH + fileName, 4 );
}
