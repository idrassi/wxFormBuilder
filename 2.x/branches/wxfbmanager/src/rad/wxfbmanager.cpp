#include "wxfbmanager.h"
#include "designer\visualeditor.h"
#include "model\objectbase.h"

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

	shared_ptr< ObjectBase > obj = m_visualEdit->GetObjectBase( wxobject );
	if ( !obj )
	{
		return NULL;
	}

	return m_visualEdit->GetWxObject( obj->GetParent() );
}
