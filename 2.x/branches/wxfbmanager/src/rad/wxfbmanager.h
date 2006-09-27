#ifndef WXFBMANAGER
#define WXFBMANAGER

#include <component.h>

class VisualEditor;

class wxFBManager : public IManager
{
private:
	VisualEditor* m_visualEdit;

public:
	wxFBManager();
	void SetVisualEditor( VisualEditor* visualEdit );
	size_t GetChildCount( wxObject* wxobject );
	wxObject* GetChild( wxObject* wxobject, size_t childIndex );
	wxObject* wxFBManager::GetParent( wxObject* wxobject );
	IObject* GetIObject( wxObject* wxobject );

};

#endif //WXFBMANAGER
