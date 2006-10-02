#ifndef BOOKUTILS
#define BOOKUTILS

#include <component.h>
#include "icons/unknown.xpm"
#include <wx/image.h>
#include <wx/notebook.h>
#include <wx/listbook.h>
#include <wx/choicebk.h>

namespace BookUtils
{
	template < class T >
		void AddImageList( IObject* obj, T* book )
	{
		if ( !obj->GetPropertyAsString( _("bitmapsize") ).empty() )
		{
			wxSize imageSize = obj->GetPropertyAsSize(_("bitmapsize"));
			wxImageList* images = new wxImageList( imageSize.GetWidth(), imageSize.GetHeight() );
			wxImage image = wxBitmap( unknown_xpm ).ConvertToImage();
			images->Add( image.Scale( imageSize.GetWidth(), imageSize.GetHeight() ) );
			book->AssignImageList( images );
		}
	}

	template < class T >
		void OnCreated( wxObject* wxobject, wxWindow* wxparent, IManager* manager, wxString name )
	{
		// Easy read-only property access
		IObject* obj = manager->GetIObject( wxobject );

		T* book = wxDynamicCast( wxparent, T );
		wxWindow* page = wxDynamicCast( manager->GetChild( wxobject, 0 ), wxWindow );

		// Error checking
		if ( !( obj && book && page ) )
		{
			wxLogError( _("%s is missing its wxFormBuilder object(%i), its parent(%i), or its child(%i)"), name.c_str(), obj, book, page );
			return;
		}

		// Prevent events during construction
		wxEvtHandler* bookEvtHandler = book->PopEventHandler();

		// Save selection
		int selection = book->GetSelection();
		book->AddPage( page, obj->GetPropertyAsString( _("label") ) );

		// Apply image to page
		IObject* parentObj = manager->GetIObject( wxparent );
		if ( !parentObj )
		{
			wxLogError( _("%s's parent is missing its wxFormBuilder object"), name.c_str() );
			return;
		}

		if ( !parentObj->GetPropertyAsString( _("bitmapsize") ).empty() )
		{
			if ( !obj->GetPropertyAsString( _("bitmap") ).empty() )
			{
				wxSize imageSize = parentObj->GetPropertyAsSize( _("bitmapsize") );
				int width = imageSize.GetWidth();
				int height = imageSize.GetHeight();
				if ( width > 0 && height > 0 )
				{
					wxImageList* imageList = book->GetImageList();
					if ( imageList != NULL )
					{
						wxImage image = obj->GetPropertyAsBitmap( _("bitmap") ).ConvertToImage();
						imageList->Add( image.Scale( width, height ) );
						book->SetPageImage( book->GetPageCount() - 1, imageList->GetImageCount() - 1 );
					}
				}
			}
		}

		if ( obj->GetPropertyAsString( _("select") ) == wxT("0") && selection >= 0 )
		{
			book->SetSelection(selection);
		}
		else
		{
			book->SetSelection( book->GetPageCount() - 1 );
		}

		// Restore event handling
		book->PushEventHandler( bookEvtHandler );
	}

	template < class T >
		void OnSelected( wxObject* wxobject, IManager* manager )
	{
		// Get actual page - first child
		wxObject* page = manager->GetChild( wxobject, 0 );
		if ( NULL == page )
		{
			return;
		}

		T* book = wxDynamicCast( manager->GetParent( wxobject ), T );
		if ( book )
		{
			for ( size_t i = 0; i < book->GetPageCount(); ++i )
			{
				if ( book->GetPage( i ) == page )
				{
					book->SetSelection( i );
				}
			}
		}
	}
}

#endif //BOOKUTILS
