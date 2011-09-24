///////////////////////////////////////////////////////////////////////////////
// Name:        src/xrc/xh_aui.h
// Purpose:     Implementation of wxStyledTextCtrl XRC handler.
// Author:      Andrea Zanellato
// Created:     2011-09-18
// RCS-ID:      $Id: $
// Copyright:   (c) 2011 Andrea Zanellato
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#if wxUSE_XRC && wxUSE_AUI

//#include "wx/xrc/xh_aui.h"
#include "handlers/xh_aui.h"
#include "wx/frame.h"
wxIMPLEMENT_DYNAMIC_CLASS( wxAuiXmlHandler, wxXmlResourceHandler )

wxAuiXmlHandler::wxAuiXmlHandler() : wxXmlResourceHandler()
{
}

wxAuiXmlHandler::~wxAuiXmlHandler()
{
    if ( m_mgr )
        m_mgr->UnInit();
}

wxObject *wxAuiXmlHandler::DoCreateResource()
{
    if ( m_class == "wxAuiManager" )
    {
        wxAuiManager *mgr = new wxAuiManager();

        wxAuiManager *old_mgr = m_mgr;
        wxWindow     *old_wnd = m_wnd;
        bool          old_ins = m_isInside;

        m_mgr      = mgr;
        m_isInside = true;

        CreateChildren( mgr );

        m_isInside = old_ins;
        m_wnd      = old_wnd;
        m_mgr      = old_mgr;

        return mgr;
    }
    else if ( m_class == "wxAuiPaneInfo" )
    {
        if ( !m_wnd )
        {
            wxXmlNode *wndNode = m_node->GetParent();
            while ( wndNode )
            {
                if ( ( wndNode->GetName() == "object" || wndNode->GetName() == "object_ref") )
                {
                    wxString classname = "class";
                    wxString name      = "name";

                    if ( wndNode->HasAttribute( classname ) &&
                         wndNode->HasAttribute( name ) )
                    {
                        classname = wndNode->GetAttribute( classname );
                        name      = wndNode->GetAttribute( name );

                        if ( classname != "wxAuiPaneInfo" &&
                             classname != "wxStatusBar"   &&
                             classname != "wxMenuBar" )
                        {
                            
                            m_wnd = wxWindow::FindWindowById( XRCID( name ) );

                            if ( m_wnd )
                                m_mgr->SetManagedWindow( m_wnd );
                            else
                                return NULL;
                        }
                    }
                }
                wndNode = wndNode->GetNext();
            }
        }

        wxXmlNode *node = GetParamNode("object");
        wxWindow *wnd = NULL;

        if ( !node )
            node = GetParamNode("object_ref");

        if ( node )
        {
            bool old_ins = m_isInside;
            m_isInside = false;

            wxObject *obj = CreateResFromNode( node, m_wnd, NULL );

            m_isInside = old_ins;
            wnd = wxDynamicCast( obj, wxWindow );

            if ( wnd == NULL && obj != NULL )
            {
                ReportError( node, _("wxAuiPaneInfo child must be a window.") );
            }
        }

        if ( wnd )
        {
            wxAuiPaneInfo paneInfo = wxAuiPaneInfo();

            wxString name = GetName();
            paneInfo.Name( name );

            if ( HasParam("caption") )
            {
                wxString caption = GetText("caption");
                paneInfo.Caption( caption );
            }

            if ( HasParam("caption_visible") )
                paneInfo.CaptionVisible( GetBool("caption_visible") );
// Buttons
            if ( HasParam("close_button") )
                paneInfo.CloseButton( GetBool("close_button") );

            if ( HasParam("minimize_button") )
                paneInfo.MinimizeButton( GetBool("minimize_button") );

            if ( HasParam("maximize_button") )
                paneInfo.MaximizeButton( GetBool("maximize_button") );

            if ( HasParam("pin_button") )
                paneInfo.PinButton( GetBool("pin_button") );

            if ( HasParam("gripper") )
                paneInfo.Gripper( GetBool("gripper") );

            if ( HasParam("pane_border") )
                paneInfo.PaneBorder( GetBool("pane_border") );

// Dockable Directions

            if ( HasParam("top_dockable") )
                paneInfo.TopDockable( GetBool("top_dockable") );

            if ( HasParam("bottom_dockable") )
                paneInfo.BottomDockable( GetBool("bottom_dockable") );

            if ( HasParam("left_dockable") )
                paneInfo.LeftDockable( GetBool("left_dockable") );

            if ( HasParam("right_dockable") )
                paneInfo.RightDockable( GetBool("right_dockable") );

            if ( HasParam("dock") && GetBool("dock") )
            {
                paneInfo.Dock();
            }
            else if ( HasParam("float") && GetBool("float") )
            {
                paneInfo.Float();
            }

            if ( HasParam("dock_fixed") )
                paneInfo.DockFixed( GetBool("dock_fixed") );

            if ( HasParam("resizable") )
                paneInfo.Resizable( GetBool("resizable") );

            if ( HasParam("movable") )
                paneInfo.Movable( GetBool("movable") );

            if ( HasParam("floatable") )
                paneInfo.Floatable( GetBool("floatable") );
// Sizes
            if ( HasParam("floating_size") )
                paneInfo.FloatingSize( GetSize("floating_size") );

            if ( HasParam("min_size") )
                paneInfo.MinSize( GetSize("min_size") );

            if ( HasParam("max_size") )
                paneInfo.MaxSize( GetSize("max_size") );

            if ( HasParam("best_size") )
                paneInfo.BestSize( GetSize("best_size") );
// Positions
            if ( HasParam("row") )
                paneInfo.Row( GetLong("row") );

            if ( HasParam("layer") )
                paneInfo.Floatable( GetLong("layer") );

            if ( HasParam("default_pane") )
                paneInfo.DefaultPane();

            if ( HasParam("center_pane") || HasParam("centre_pane") )
                paneInfo.CenterPane();

            else if ( HasParam("toolbar_pane") )
                paneInfo.ToolbarPane();

            if ( HasParam("direction") )
            {
                switch ( GetLong("direction") )
                {
                    case wxTOP:    paneInfo.Top(); break;
                    case wxBOTTOM: paneInfo.Bottom(); break;
                    case wxLEFT:   paneInfo.Left(); break;
                    case wxRIGHT:  paneInfo.Right(); break;
                    case wxCENTER: paneInfo.CenterPane(); break;
                }
            }

            m_mgr->AddPane( wnd, paneInfo );
            m_mgr->Update();
        }
        else
        {
            ReportError(_("No wxWindow derived class object specified inside wxAuiPaneInfo.") );
        }
        return wnd;
    }
    return NULL;
}

bool wxAuiXmlHandler::CanHandle( wxXmlNode *node )
{
    return IsOfClass( node, "wxAuiManager" ) || IsOfClass( node, "wxAuiPaneInfo" );
}

#endif //wxUSE_XRC && wxUSE_AUI
