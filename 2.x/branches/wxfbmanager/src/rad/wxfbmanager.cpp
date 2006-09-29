#include "wxfbmanager.h"
#include "designer/visualeditor.h"
#include "model/objectbase.h"
#include "rad/appdata.h"

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
	if ( NULL == m_visualEdit )
	{
		return NULL;
	}

	if ( NULL == wxobject )
	{
		return NULL;
	}

	shared_ptr< ObjectBase > obj = m_visualEdit->GetObjectBase( wxobject );
	if ( !obj )
	{
		return NULL;
	}
	else
	{
		return obj.get();
	}
}

size_t wxFBManager::GetChildCount( wxObject* wxobject )
{
	if ( NULL == m_visualEdit )
	{
		return 0;
	}

	if ( NULL == wxobject )
	{
		return 0;
	}

	shared_ptr< ObjectBase > obj = m_visualEdit->GetObjectBase( wxobject );
	if ( !obj )
	{
		return 0;
	}

	return obj->GetChildCount();
}

wxObject* wxFBManager::GetChild( wxObject* wxobject, size_t childIndex )
{
	if ( NULL == m_visualEdit )
	{
		return NULL;
	}

	if ( NULL == wxobject )
	{
		return NULL;
	}

	shared_ptr< ObjectBase > obj = m_visualEdit->GetObjectBase( wxobject );
	if ( !obj )
	{
		return NULL;
	}

	if ( childIndex >= obj->GetChildCount() )
	{
		return NULL;
	}

	return m_visualEdit->GetWxObject( obj->GetChild( childIndex ) );
}

wxObject* wxFBManager::GetParent( wxObject* wxobject )
{
	if ( NULL == m_visualEdit )
	{
		return NULL;
	}

	if ( NULL == wxobject )
	{
		return NULL;
	}

	shared_ptr< ObjectBase > obj = m_visualEdit->GetObjectBase( wxobject );
	if ( !obj )
	{
		return NULL;
	}

	return m_visualEdit->GetWxObject( obj->GetParent() );
}

wxObject* wxFBManager::GetWxObject( shared_ptr< ObjectBase > obj )
{
	if ( !obj )
	{
		return NULL;
	}

	return m_visualEdit->GetWxObject( obj );
}

void wxFBManager::ModifyProperty( wxObject* wxobject, wxString property, wxString value, bool allowUndo )
{
	if ( NULL == m_visualEdit )
	{
		return;
	}

	if ( NULL == wxobject )
	{
		return;
	}

	shared_ptr< ObjectBase > obj = m_visualEdit->GetObjectBase( wxobject );
	if ( !obj )
	{
		return;
	}

	shared_ptr< Property > prop = obj->GetProperty( property );

	if ( prop )
	{
		if ( allowUndo )
		{
			AppData()->ModifyProperty( prop, value );
		}
		else
		{
			prop->SetValue( value );
		}
	}
}
