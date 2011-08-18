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

#include <component.h>
#include <plugin.h>
#include <xrcconv.h>
#include <ticpp.h>
#include <wx/tokenzr.h>
#include <wx/gbsizer.h>
#include <map>

#ifdef __WX24__
	#define wxFIXED_MINSIZE wxADJUST_MINSIZE
#endif

class SpacerComponent : public ComponentBase
{
public:
	// ImportFromXRC is handled in sizeritem components

	ticpp::Element* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, wxT("spacer"));
		xrc.AddPropertyPair( wxT("width"), wxT("height"), wxT("size") );
		return xrc.GetXrcObject();
	}
};

class GBSizerItemComponent : public ComponentBase
{
public:

	ticpp::Element* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, wxT("sizeritem"));
		xrc.AddPropertyPair( wxT("row"), wxT("column"), wxT("cellpos") );
		xrc.AddPropertyPair( wxT("rowspan"), wxT("colspan"), wxT("cellspan") );
		xrc.AddProperty(wxT("flag"),   wxT("flag"),   XRC_TYPE_BITLIST);
		xrc.AddProperty(wxT("border"), wxT("border"), XRC_TYPE_INTEGER);
		return xrc.GetXrcObject();
	}

	ticpp::Element* ImportFromXrc( ticpp::Element* xrcObj )
	{
		// XrcLoader::GetObject imports spacers as sizeritems
		XrcToXfbFilter filter(xrcObj, wxT("gbsizeritem"));
		filter.AddPropertyPair( "cellpos", wxT("row"), wxT("column") );
		filter.AddPropertyPair( "cellspan", wxT("rowspan"), wxT("colspan") );
		filter.AddProperty(wxT("flag"),   wxT("flag"),   XRC_TYPE_BITLIST);
		filter.AddProperty(wxT("border"), wxT("border"), XRC_TYPE_INTEGER);
		ticpp::Element* sizeritem = filter.GetXfbObject();

		// XrcLoader::GetObject imports spacers as sizeritems, so check for a spacer
		if ( xrcObj->FirstChildElement( "size", false ) && !xrcObj->FirstChildElement( "object", false ) )
		{
			// it is a spacer
			XrcToXfbFilter spacer( xrcObj, wxT("spacer") );
			spacer.AddPropertyPair( "size", wxT("width"), wxT("height") );
			sizeritem->LinkEndChild( spacer.GetXfbObject() );
		}

		return sizeritem;
	}
};

class SizerItemComponent : public ComponentBase
{
public:
	void OnCreated( wxObject* wxobject, wxWindow* /*wxparent*/ )
	{
		// Get parent sizer
		wxObject* parent = GetManager()->GetParent( wxobject );
		wxSizer* sizer = wxDynamicCast( parent, wxSizer );

		if ( NULL == sizer )
		{
			wxLogError( _("The parent of a SizerItem is either missing or not a wxSizer - this should not be possible!") );
			return;
		}

		// Get child window
		wxObject* child = GetManager()->GetChild( wxobject, 0 );
		if ( NULL == child )
		{
			wxLogError( _("The SizerItem component has no child - this should not be possible!") );
			return;
		}

		// Get IObject for property access
		IObject* obj = GetManager()->GetIObject( wxobject );
		IObject* childObj = GetManager()->GetIObject( child );

		// Add the spacer
		if ( wxT("spacer") == childObj->GetClassName() )
		{
			sizer->Add(	childObj->GetPropertyAsInteger( wxT("width") ),
						childObj->GetPropertyAsInteger( wxT("height") ),
						obj->GetPropertyAsInteger(wxT("proportion")),
						obj->GetPropertyAsInteger(wxT("flag")),
						obj->GetPropertyAsInteger(wxT("border"))
						);
			return;
		}

		// Add the child ( window or sizer ) to the sizer
		wxWindow* windowChild = wxDynamicCast( child, wxWindow );
		wxSizer* sizerChild = wxDynamicCast( child, wxSizer );

		if ( windowChild != NULL )
		{
			sizer->Add( windowChild,
				obj->GetPropertyAsInteger(wxT("proportion")),
				obj->GetPropertyAsInteger(wxT("flag")),
				obj->GetPropertyAsInteger(wxT("border")));
		}
		else if ( sizerChild != NULL )
		{
			sizer->Add( sizerChild,
				obj->GetPropertyAsInteger(wxT("proportion")),
				obj->GetPropertyAsInteger(wxT("flag")),
				obj->GetPropertyAsInteger(wxT("border")));
		}
		else
		{
			wxLogError( _("The SizerItem component's child is not a wxWindow or a wxSizer or a spacer - this should not be possible!") );
		}
	}

	ticpp::Element* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, wxT("sizeritem"));
		xrc.AddProperty(wxT("proportion"), wxT("option"), XRC_TYPE_INTEGER);
		xrc.AddProperty(wxT("flag"),   wxT("flag"),   XRC_TYPE_BITLIST);
		xrc.AddProperty(wxT("border"), wxT("border"), XRC_TYPE_INTEGER);
		return xrc.GetXrcObject();
	}

	ticpp::Element* ImportFromXrc( ticpp::Element* xrcObj )
	{
		XrcToXfbFilter filter(xrcObj, wxT("sizeritem"));
		filter.AddProperty(wxT("option"), wxT("proportion"), XRC_TYPE_INTEGER);
		filter.AddProperty(wxT("flag"),   wxT("flag"),   XRC_TYPE_BITLIST);
		filter.AddProperty(wxT("border"), wxT("border"), XRC_TYPE_INTEGER);
		ticpp::Element* sizeritem = filter.GetXfbObject();

		// XrcLoader::GetObject imports spacers as sizeritems, so check for a spacer
		if ( xrcObj->FirstChildElement("size", false ) && !xrcObj->FirstChildElement("object", false ) )
		{
			// it is a spacer
			XrcToXfbFilter spacer( xrcObj, wxT("spacer") );
			spacer.AddPropertyPair( "size", wxT("width"), wxT("height") );
			sizeritem->LinkEndChild( spacer.GetXfbObject() );
		}
		return sizeritem;
	}
};

class BoxSizerComponent : public ComponentBase
{
public:
	wxObject* Create(IObject *obj, wxObject * /*parent*/)
	{
		wxBoxSizer *sizer = new wxBoxSizer(obj->GetPropertyAsInteger(wxT("orient")));
		sizer->SetMinSize( obj->GetPropertyAsSize(wxT("minimum_size")) );
		return sizer;
	}

	ticpp::Element* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, wxT("wxBoxSizer"));
		if( obj->GetPropertyAsSize(wxT("minimum_size")) != wxDefaultSize ) xrc.AddProperty(wxT("minimum_size"), wxT("minsize"), XRC_TYPE_SIZE);
		xrc.AddProperty(wxT("orient"), wxT("orient"), XRC_TYPE_TEXT);
		return xrc.GetXrcObject();
	}

	ticpp::Element* ImportFromXrc( ticpp::Element* xrcObj )
	{
		XrcToXfbFilter filter(xrcObj, wxT("wxBoxSizer"));
		filter.AddProperty(wxT("minsize"), wxT("minsize"), XRC_TYPE_SIZE);
		filter.AddProperty(wxT("orient"),wxT("orient"),XRC_TYPE_TEXT);
		return filter.GetXfbObject();
	}
};

class StaticBoxSizerComponent : public ComponentBase
{
public:
	int m_count;
	StaticBoxSizerComponent()
	{
		m_count = 0;
	}
	wxObject* Create(IObject *obj, wxObject *parent)
	{
		m_count++;
		wxStaticBox* box = new wxStaticBox((wxWindow *)parent, -1,
			obj->GetPropertyAsString(wxT("label")));

		wxStaticBoxSizer* sizer = new wxStaticBoxSizer(box,
			obj->GetPropertyAsInteger(wxT("orient")));

		sizer->SetMinSize( obj->GetPropertyAsSize(wxT("minimum_size")) );
		
		return sizer;
	}

	ticpp::Element* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, wxT("wxStaticBoxSizer"));
		if( obj->GetPropertyAsSize(wxT("minimum_size")) != wxDefaultSize ) xrc.AddProperty(wxT("minimum_size"), wxT("minsize"), XRC_TYPE_SIZE);
		xrc.AddProperty(wxT("orient"), wxT("orient"), XRC_TYPE_TEXT);
		xrc.AddProperty(wxT("label"), wxT("label"), XRC_TYPE_TEXT);
		return xrc.GetXrcObject();
	}

	ticpp::Element* ImportFromXrc( ticpp::Element* xrcObj )
	{
		XrcToXfbFilter filter(xrcObj, wxT("wxStaticBoxSizer"));
		filter.AddProperty(wxT("minsize"), wxT("minsize"), XRC_TYPE_SIZE);
		filter.AddProperty(wxT("orient"),wxT("orient"),XRC_TYPE_TEXT);
		filter.AddProperty(wxT("label"),wxT("label"),XRC_TYPE_TEXT);
		return filter.GetXfbObject();
	}
};

class GridSizerComponent : public ComponentBase
{
public:
	wxObject* Create(IObject *obj, wxObject * /*parent*/)
	{
		wxGridSizer *sizer = new wxGridSizer(
			obj->GetPropertyAsInteger(wxT("rows")),
			obj->GetPropertyAsInteger(wxT("cols")),
			obj->GetPropertyAsInteger(wxT("vgap")),
			obj->GetPropertyAsInteger(wxT("hgap")));
		
		sizer->SetMinSize( obj->GetPropertyAsSize(wxT("minimum_size")) );
		
		return sizer;
	}

	ticpp::Element* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, wxT("wxGridSizer"));
		if( obj->GetPropertyAsSize(wxT("minimum_size")) != wxDefaultSize ) xrc.AddProperty(wxT("minimum_size"), wxT("minsize"), XRC_TYPE_SIZE);
		xrc.AddProperty(wxT("rows"), wxT("rows"), XRC_TYPE_INTEGER);
		xrc.AddProperty(wxT("cols"), wxT("cols"), XRC_TYPE_INTEGER);
		xrc.AddProperty(wxT("vgap"), wxT("vgap"), XRC_TYPE_INTEGER);
		xrc.AddProperty(wxT("hgap"), wxT("hgap"), XRC_TYPE_INTEGER);
		return xrc.GetXrcObject();
	}

	ticpp::Element* ImportFromXrc( ticpp::Element* xrcObj )
	{
		XrcToXfbFilter filter(xrcObj, wxT("wxGridSizer"));
		filter.AddProperty(wxT("minsize"), wxT("minsize"), XRC_TYPE_SIZE);
		filter.AddProperty(wxT("rows"), wxT("rows"), XRC_TYPE_INTEGER);
		filter.AddProperty(wxT("cols"), wxT("cols"), XRC_TYPE_INTEGER);
		filter.AddProperty(wxT("vgap"), wxT("vgap"), XRC_TYPE_INTEGER);
		filter.AddProperty(wxT("hgap"), wxT("hgap"), XRC_TYPE_INTEGER);
		return filter.GetXfbObject();
	}
};

class FlexGridSizerBase : public ComponentBase
{
public:
	void AddProperties( IObject* obj, wxFlexGridSizer* sizer )
	{
		wxArrayInt gcols, grows;
		gcols = obj->GetPropertyAsArrayInt(wxT("growablecols"));
		grows = obj->GetPropertyAsArrayInt(wxT("growablerows"));

		unsigned int i;
		for (i=0; i < gcols.GetCount() ; i++)
			sizer->AddGrowableCol(gcols[i]);

		for (i=0; i < grows.GetCount() ; i++)
			sizer->AddGrowableRow(grows[i]);
			
		sizer->SetMinSize( obj->GetPropertyAsSize(wxT("minimum_size")) );
		sizer->SetFlexibleDirection( obj->GetPropertyAsInteger(wxT("flexible_direction")) );
		sizer->SetNonFlexibleGrowMode( (wxFlexSizerGrowMode )obj->GetPropertyAsInteger(wxT("non_flexible_grow_mode")) );
	}

	void ExportXRCProperties( ObjectToXrcFilter* xrc, IObject* obj )
	{
		if( obj->GetPropertyAsSize(wxT("minimum_size")) != wxDefaultSize ) xrc->AddProperty(wxT("minimum_size"), wxT("minsize"), XRC_TYPE_SIZE);
		xrc->AddProperty(wxT("vgap"), wxT("vgap"), XRC_TYPE_INTEGER);
		xrc->AddProperty(wxT("hgap"), wxT("hgap"), XRC_TYPE_INTEGER);
		xrc->AddPropertyValue(wxT("growablecols"), obj->GetPropertyAsString(wxT("growablecols")));
		xrc->AddPropertyValue(wxT("growablerows"), obj->GetPropertyAsString(wxT("growablerows")));
	}

	void ImportXRCProperties( XrcToXfbFilter* filter )
	{
		filter->AddProperty(wxT("minsize"), wxT("minsize"), XRC_TYPE_SIZE);
		filter->AddProperty(wxT("vgap"), wxT("vgap"), XRC_TYPE_INTEGER);
		filter->AddProperty(wxT("hgap"), wxT("hgap"), XRC_TYPE_INTEGER);
		filter->AddProperty(wxT("growablecols"),wxT("growablecols"),XRC_TYPE_TEXT);
		filter->AddProperty(wxT("growablerows"),wxT("growablerows"),XRC_TYPE_TEXT);
	}
};

class FlexGridSizerComponent : public FlexGridSizerBase
{
public:
	wxObject* Create(IObject *obj, wxObject * /*parent*/)
	{
		wxFlexGridSizer *sizer = new wxFlexGridSizer(
			obj->GetPropertyAsInteger(wxT("rows")),
			obj->GetPropertyAsInteger(wxT("cols")),
			obj->GetPropertyAsInteger(wxT("vgap")),
			obj->GetPropertyAsInteger(wxT("hgap")));

		AddProperties( obj, sizer );

		return sizer;
	}

	ticpp::Element* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, wxT("wxFlexGridSizer"));
		xrc.AddProperty(wxT("rows"), wxT("rows"), XRC_TYPE_INTEGER);
		xrc.AddProperty(wxT("cols"), wxT("cols"), XRC_TYPE_INTEGER);
		ExportXRCProperties( &xrc, obj );
		return xrc.GetXrcObject();
	}

	ticpp::Element* ImportFromXrc( ticpp::Element* xrcObj )
	{
		XrcToXfbFilter filter(xrcObj, wxT("wxFlexGridSizer"));
		filter.AddProperty(wxT("rows"), wxT("rows"), XRC_TYPE_INTEGER);
		filter.AddProperty(wxT("cols"), wxT("cols"), XRC_TYPE_INTEGER);
		ImportXRCProperties( &filter );
		return filter.GetXfbObject();
	}
};

class GridBagSizerComponent : public FlexGridSizerBase
{
private:
	wxGBSizerItem* GetGBSizerItem( IObject* sizeritem, const wxGBPosition& position, const wxGBSpan& span, wxObject* child )
	{
		IObject* childObj = GetManager()->GetIObject( child );

		if ( wxT("spacer") == childObj->GetClassName() )
		{
			return new wxGBSizerItem(	childObj->GetPropertyAsInteger( wxT("width") ),
										childObj->GetPropertyAsInteger( wxT("height") ),
										position,
										span,
										sizeritem->GetPropertyAsInteger(wxT("flag")),
										sizeritem->GetPropertyAsInteger(wxT("border")),
										NULL
										);
		}

		// Add the child ( window or sizer ) to the sizer
		wxWindow* windowChild = wxDynamicCast( child, wxWindow );
		wxSizer* sizerChild = wxDynamicCast( child, wxSizer );

		if ( windowChild != NULL )
		{
			return new wxGBSizerItem( 	windowChild,
										position,
										span,
										sizeritem->GetPropertyAsInteger(wxT("flag")),
										sizeritem->GetPropertyAsInteger(wxT("border")),
										NULL
										);
		}
		else if ( sizerChild != NULL )
		{
			return new wxGBSizerItem( 	sizerChild,
										position,
										span,
										sizeritem->GetPropertyAsInteger(wxT("flag")),
										sizeritem->GetPropertyAsInteger(wxT("border")),
										NULL
										);
		}
		else
		{
			wxLogError( _("The GBSizerItem component's child is not a wxWindow or a wxSizer or a Spacer - this should not be possible!") );
			return NULL;
		}
	}

public:
	wxObject* Create(IObject *obj, wxObject * /*parent*/)
	{
		wxGridBagSizer* sizer = new wxGridBagSizer(
			obj->GetPropertyAsInteger(wxT("vgap")),
			obj->GetPropertyAsInteger(wxT("hgap")));

		AddProperties( obj, sizer );

		if ( !obj->IsNull( wxT("empty_cell_size") ) )
		{
			sizer->SetEmptyCellSize( obj->GetPropertyAsSize( wxT("empty_cell_size") ) );
		}

		return sizer;
	}

	void OnCreated( wxObject* wxobject, wxWindow* /*wxparent*/ )
	{
		// For storing objects whose postion needs to be determined
		std::vector< std::pair< wxObject*, wxGBSizerItem* > > newObjects;
		wxGBPosition lastPosition( 0, 0 );

		// Get sizer
		wxGridBagSizer* sizer = wxDynamicCast( wxobject, wxGridBagSizer );
		if ( NULL == sizer )
		{
			wxLogError( wxT("This should be a wxGridBagSizer!") );
			return;
		}

		// Add the children
		IManager* manager = GetManager();
		size_t count = manager->GetChildCount( wxobject );
		if ( 0 == count )
		{
			// wxGridBagSizer gets upset sometimes without children
			sizer->Add( 0, 0, wxGBPosition( 0, 0 ) );
			return;
		}
		for ( size_t i = 0; i < count; ++i )
		{
			// Should be a GBSizerItem
			wxObject* wxsizerItem = manager->GetChild( wxobject, i );
			IObject* isizerItem = manager->GetIObject( wxsizerItem );

			// Get the location of the item
			wxGBSpan span( isizerItem->GetPropertyAsInteger( wxT("rowspan") ), isizerItem->GetPropertyAsInteger( wxT("colspan") ) );

			int column = isizerItem->GetPropertyAsInteger( wxT("column") );
			if ( column < 0 )
			{
				// Needs to be auto positioned after the other children are added
				wxGBSizerItem* item = GetGBSizerItem( isizerItem, lastPosition, span, manager->GetChild( wxsizerItem, 0 ) );
				if ( item != NULL )
				{
					newObjects.push_back( std::pair< wxObject*, wxGBSizerItem* >( wxsizerItem, item ) );
				}
				continue;
			}

			wxGBPosition position( isizerItem->GetPropertyAsInteger( wxT("row") ), column );

			// Check for intersection
			if ( sizer->CheckForIntersection( position, span ) )
			{
				continue;
			}

			lastPosition = position;

			// Add the child to the sizer
			wxGBSizerItem* item = GetGBSizerItem( isizerItem, position, span, manager->GetChild( wxsizerItem, 0 ) );
			if ( item != NULL )
			{
				sizer->Add( item );
			}
		}

		std::vector< std::pair< wxObject*, wxGBSizerItem* > >::iterator it;
		for ( it = newObjects.begin(); it != newObjects.end(); ++it )
		{
			wxGBPosition position = it->second->GetPos();
			wxGBSpan span = it->second->GetSpan();
			int column = position.GetCol();
			while ( sizer->CheckForIntersection( position, span ) )
			{
				column++;
				position.SetCol( column );
			}
			it->second->SetPos( position );
			sizer->Add( it->second );
			GetManager()->ModifyProperty( it->first, wxT("row"), wxString::Format( wxT("%i"), position.GetRow() ), false );
			GetManager()->ModifyProperty( it->first, wxT("column"), wxString::Format( wxT("%i"), column ), false );
		}
	}

	ticpp::Element* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, wxT("wxGridBagSizer"));
		ExportXRCProperties( &xrc, obj );
		return xrc.GetXrcObject();
	}

	ticpp::Element* ImportFromXrc( ticpp::Element* xrcObj )
	{
		XrcToXfbFilter filter(xrcObj, wxT("wxGridBagSizer"));
		ImportXRCProperties( &filter );
		return filter.GetXfbObject();
	}
};

class StdDialogButtonSizerComponent : public ComponentBase
{
private:
	void AddXRCButton( ticpp::Element* sizer, const std::string& id, const std::string& label )
	{
		try
		{
			ticpp::Element button( "object" );
			button.SetAttribute( "class", "button" );

			ticpp::Element flag( "flag" );
			flag.SetText( "wxALIGN_CENTER_HORIZONTAL|wxALL" );
			button.LinkEndChild( &flag );

			ticpp::Element border( "border" );
			border.SetText( "5" );
			button.LinkEndChild( &border );

			ticpp::Element wxbutton( "object" );
			wxbutton.SetAttribute( "class", "wxButton" );
			wxbutton.SetAttribute( "name", id );

			ticpp::Element labelEl( "label" );
			labelEl.SetText( label );
			wxbutton.LinkEndChild( &labelEl );

			button.LinkEndChild( &wxbutton );

			sizer->LinkEndChild( &button );
		}
		catch( ticpp::Exception& ex )
		{
			wxLogError( wxString( ex.m_details.c_str(), wxConvUTF8 ) );
		}
	}

public:
	wxObject* Create(IObject *obj, wxObject *parent)
	{
		wxStdDialogButtonSizer* sizer =  new wxStdDialogButtonSizer();
		
		sizer->SetMinSize( obj->GetPropertyAsSize(wxT("minimum_size")) );
		
		if ( obj->GetPropertyAsInteger( wxT("OK") ) )
		{
			sizer->AddButton( new wxButton( (wxWindow*)parent, wxID_OK ) );
		}
		if ( obj->GetPropertyAsInteger( wxT("Yes") ) )
		{
			sizer->AddButton( new wxButton( (wxWindow*)parent, wxID_YES ) );
		}
		if ( obj->GetPropertyAsInteger( wxT("Save") ) )
		{
			sizer->AddButton( new wxButton( (wxWindow*)parent, wxID_SAVE ) );
		}
		if ( obj->GetPropertyAsInteger( wxT("Apply") ) )
		{
			sizer->AddButton( new wxButton( (wxWindow*)parent, wxID_APPLY ) );
		}
		if ( obj->GetPropertyAsInteger( wxT("No") ) )
		{
			sizer->AddButton( new wxButton( (wxWindow*)parent, wxID_NO ) );
		}
		if ( obj->GetPropertyAsInteger( wxT("Cancel") ) )
		{
			sizer->AddButton( new wxButton( (wxWindow*)parent, wxID_CANCEL ) );
		}
		if ( obj->GetPropertyAsInteger( wxT("Help") ) )
		{
			sizer->AddButton( new wxButton( (wxWindow*)parent, wxID_HELP ) );
		}
		if ( obj->GetPropertyAsInteger( wxT("ContextHelp") ) )
		{
			sizer->AddButton( new wxButton( (wxWindow*)parent, wxID_CONTEXT_HELP ) );
		}
		
		sizer->Realize();
		return sizer;
	}

	ticpp::Element* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, wxT("wxStdDialogButtonSizer"));
		ticpp::Element* sizer = xrc.GetXrcObject();
		
		if( obj->GetPropertyAsSize(wxT("minimum_size")) != wxDefaultSize )
		{
			xrc.AddProperty(wxT("minimum_size"), wxT("minsize"), XRC_TYPE_SIZE);
		}
		if ( obj->GetPropertyAsInteger( wxT("OK") ) )
		{
			AddXRCButton( sizer, "wxID_OK", "&OK" );
		}
		if ( obj->GetPropertyAsInteger( wxT("Yes") ) )
		{
			AddXRCButton( sizer, "wxID_YES", "&Yes" );
		}
		if ( obj->GetPropertyAsInteger( wxT("Save") ) )
		{
			AddXRCButton( sizer, "wxID_SAVE", "&Save" );
		}
		if ( obj->GetPropertyAsInteger( wxT("Apply") ) )
		{
			AddXRCButton( sizer, "wxID_APPLY", "&Apply" );
		}
		if ( obj->GetPropertyAsInteger( wxT("No") ) )
		{
			AddXRCButton( sizer, "wxID_NO", "&No" );
		}
		if ( obj->GetPropertyAsInteger( wxT("Cancel") ) )
		{
			AddXRCButton( sizer, "wxID_CANCEL", "&Cancel" );
		}
		if ( obj->GetPropertyAsInteger( wxT("Help") ) )
		{
			AddXRCButton( sizer, "wxID_HELP", "&Help" );
		}
		if ( obj->GetPropertyAsInteger( wxT("ContextHelp") ) )
		{
			AddXRCButton( sizer, "wxID_CONTEXT_HELP", "" );
		}

		return sizer;
	}

	ticpp::Element* ImportFromXrc( ticpp::Element* xrcObj )
	{
		std::map< wxString, wxString > buttons;
		buttons[ wxT("OK") ] 			= wxT("0");
		buttons[ wxT("Yes") ] 		= wxT("0");
		buttons[ wxT("Save") ] 		= wxT("0");
		buttons[ wxT("Apply") ] 		= wxT("0");
		buttons[ wxT("No") ] 			= wxT("0");
		buttons[ wxT("Cancel") ] 		= wxT("0");
		buttons[ wxT("Help") ] 		= wxT("0");
		buttons[ wxT("ContextHelp") ] = wxT("0");

		XrcToXfbFilter filter(xrcObj, wxT("wxStdDialogButtonSizer"));
		filter.AddProperty(wxT("minsize"), wxT("minsize"), XRC_TYPE_SIZE);

		ticpp::Element* button = xrcObj->FirstChildElement( "object", false );
		for (  ; button != 0; button = button->NextSiblingElement( "object", false ) )
		{
			try
			{
				std::string button_class;
				button->GetAttribute( "class", &button_class );
				if ( std::string("button") != button_class )
				{
					continue;
				}

				ticpp::Element* wxbutton = button->FirstChildElement( "object" );
				std::string wxbutton_class;
				wxbutton->GetAttribute( "class", &wxbutton_class );
				if ( std::string("wxButton") != wxbutton_class )
				{
					continue;
				}

				std::string name;
				wxbutton->GetAttribute( "name", &name );

				if ( name == "wxID_OK" )
				{
					buttons[ wxT("OK") ] = wxT("1");
				}
				else if ( name == "wxID_YES" )
				{
					buttons[ wxT("Yes") ] = wxT("1");
				}
				else if ( name == "wxID_SAVE" )
				{
					buttons[ wxT("Save") ] = wxT("1");
				}
				else if ( name == "wxID_APPLY" )
				{
					buttons[ wxT("Apply") ] = wxT("1");
				}
				else if ( name == "wxID_NO" )
				{
					buttons[ wxT("No") ] = wxT("1");
				}
				else if ( name == "wxID_CANCEL" )
				{
					buttons[ wxT("Cancel") ] = wxT("1");
				}
				else if ( name == "wxID_HELP" )
				{
					buttons[ wxT("Help") ] = wxT("1");
				}
				else if ( name == "wxID_CONTEXT_HELP" )
				{
					buttons[ wxT("ContextHelp") ] = wxT("1");
				}
			}
			catch( ticpp::Exception& )
			{
				continue;
			}
		}

		std::map< wxString, wxString >::iterator prop;
		for ( prop = buttons.begin(); prop != buttons.end(); ++prop )
		{
			filter.AddPropertyValue( prop->first, prop->second );
		}

		xrcObj->Clear();

		return filter.GetXfbObject();
	}
};

///////////////////////////////////////////////////////////////////////////////

BEGIN_LIBRARY()
ABSTRACT_COMPONENT("spacer",SpacerComponent)
ABSTRACT_COMPONENT("sizeritem",SizerItemComponent)
ABSTRACT_COMPONENT("gbsizeritem",GBSizerItemComponent)

SIZER_COMPONENT("wxBoxSizer",BoxSizerComponent)
SIZER_COMPONENT("wxStaticBoxSizer",StaticBoxSizerComponent)
SIZER_COMPONENT("wxGridSizer",GridSizerComponent)
SIZER_COMPONENT("wxFlexGridSizer",FlexGridSizerComponent)
SIZER_COMPONENT("wxGridBagSizer",GridBagSizerComponent)
SIZER_COMPONENT("wxStdDialogButtonSizer",StdDialogButtonSizerComponent)

// wxBoxSizer
MACRO(wxHORIZONTAL)
MACRO(wxVERTICAL)

// wxFlexGridSizer
MACRO(wxBOTH)
MACRO(wxFLEX_GROWMODE_NONE)
MACRO(wxFLEX_GROWMODE_SPECIFIED)
MACRO(wxFLEX_GROWMODE_ALL)

// Add
MACRO(wxALL)
MACRO(wxLEFT)
MACRO(wxRIGHT)
MACRO(wxTOP)
MACRO(wxBOTTOM)
MACRO(wxEXPAND)
MACRO(wxALIGN_BOTTOM)
MACRO(wxALIGN_CENTER)
MACRO(wxALIGN_CENTER_HORIZONTAL)
MACRO(wxALIGN_CENTER_VERTICAL)
MACRO(wxSHAPED)
MACRO(wxFIXED_MINSIZE)

SYNONYMOUS(wxGROW, wxEXPAND)

END_LIBRARY()

