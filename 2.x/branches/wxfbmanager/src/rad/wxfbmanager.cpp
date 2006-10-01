#include "wxfbmanager.h"
#include "designer/visualeditor.h"
#include "model/objectbase.h"
#include "rad/appdata.h"

#define CHECK_NULL( THING, THING_NAME, RETURN ) 									\
	if ( !THING )																	\
	{																				\
		wxLogError( _("%s is NULL! <%s,%i>"), THING_NAME, __TFILE__, __LINE__ );	\
		return RETURN;																\
	}

#define CHECK_VISUAL_EDITOR( RETURN ) \
	CHECK_NULL( m_visualEdit, "Visual Editor", RETURN )

#define CHECK_WX_OBJECT( RETURN ) \
	CHECK_NULL( wxobject, "wxObject", RETURN )

#define CHECK_OBJECT_BASE( RETURN ) \
	CHECK_NULL( obj, "ObjectBase", RETURN )

wxFBManager::wxFBManager()
:
m_visualEdit( NULL )
{
}

void wxFBManager::SetVisualEditor( VisualEditor* visualEdit )
{
	m_visualEdit = visualEdit;
}

IObject* wxFBManager::GetIObject( wxObject* wxobject )
{
	CHECK_VISUAL_EDITOR( NULL )

	CHECK_WX_OBJECT( NULL )

	shared_ptr< ObjectBase > obj = m_visualEdit->GetObjectBase( wxobject );

	CHECK_OBJECT_BASE( NULL )

	return obj.get();
}

size_t wxFBManager::GetChildCount( wxObject* wxobject )
{
	CHECK_VISUAL_EDITOR( 0 )

	CHECK_WX_OBJECT( 0 )

	shared_ptr< ObjectBase > obj = m_visualEdit->GetObjectBase( wxobject );

	CHECK_OBJECT_BASE( 0 )

	return obj->GetChildCount();
}

wxObject* wxFBManager::GetChild( wxObject* wxobject, size_t childIndex )
{
	CHECK_VISUAL_EDITOR( NULL )

	CHECK_WX_OBJECT( NULL )

	shared_ptr< ObjectBase > obj = m_visualEdit->GetObjectBase( wxobject );

	CHECK_OBJECT_BASE( NULL )

	if ( childIndex >= obj->GetChildCount() )
	{
		return NULL;
	}

	return m_visualEdit->GetWxObject( obj->GetChild( childIndex ) );
}

wxObject* wxFBManager::GetParent( wxObject* wxobject )
{
	CHECK_VISUAL_EDITOR( NULL )

	CHECK_WX_OBJECT( NULL )

	shared_ptr< ObjectBase > obj = m_visualEdit->GetObjectBase( wxobject );

	CHECK_OBJECT_BASE( NULL )

	return m_visualEdit->GetWxObject( obj->GetParent() );
}

wxObject* wxFBManager::GetWxObject( shared_ptr< ObjectBase > obj )
{
	CHECK_OBJECT_BASE( NULL )

	return m_visualEdit->GetWxObject( obj );
}

void wxFBManager::ModifyProperty( wxObject* wxobject, wxString property, wxString value, bool allowUndo )
{
	CHECK_VISUAL_EDITOR()

	CHECK_WX_OBJECT()

	shared_ptr< ObjectBase > obj = m_visualEdit->GetObjectBase( wxobject );

	CHECK_OBJECT_BASE()

	shared_ptr< Property > prop = obj->GetProperty( property );

	if ( !prop )
	{
		wxLogError( _("%s has no property named %s"), obj->GetClassName().c_str(), property.c_str() );
		return;
	}

	if ( allowUndo )
	{
		wxLogDebug( wxT("allowUndo %s"), value.c_str() );
		AppData()->ModifyProperty( prop, value );
	}
	else
	{
		wxLogDebug( wxT("not allowUndo %s"), value.c_str() );
		prop->SetValue( value );
	}
}

void AddEventHandler( wxEvtHandler* handler )
{
	AppData()->AddHandler( handler );
}

void RemoveEventHandler( wxEvtHandler* handler )
{
	AppData()->RemoveHandler( handler );
}
