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

#include "customkeys.h"
#include "appdata.h"
#include "codegen/cppcg.h"
#include "model/objectbase.h"
#include "utils/debug.h"

BEGIN_EVENT_TABLE(CustomKeysEvtHandler,wxEvtHandler)
	EVT_CHAR( CustomKeysEvtHandler::OnKeyPress )
END_EVENT_TABLE()

void CustomKeysEvtHandler::OnKeyPress( wxKeyEvent &event )
{
	Debug::Print( wxString::Format( "%d", event.GetKeyCode() ) );

	if ( event.GetKeyCode() == WXK_DELETE )
	{
		AppData()->RemoveObject( AppData()->GetSelectedObject() );
	}
	else if ( event.GetKeyCode() == 'P' )
	{
		Debug::Print( _("#### Parser test ####") );

		PObjectBase obj = AppData()->GetSelectedObject();
		PCodeInfo code_info = obj->GetObjectInfo()->GetCodeInfo("C++");

		Debug::Print( _("#### Templates ####") );
		Debug::Print( ( wxChar * )( code_info->GetTemplate("construction").wchar_str() ) );
		Debug::Print( ( wxChar * )( code_info->GetTemplate("declaration").wchar_str() ) );

		Debug::Print( _("#### Code ####") );
		{
			CppTemplateParser parser(obj,code_info->GetTemplate("construction"), false, false, wxEmptyString );
			Debug::Print((wxChar *)parser.ParseTemplate().wchar_str());
		}
		{
			CppTemplateParser parser(obj,code_info->GetTemplate("declaration"), false, false, wxEmptyString );
			Debug::Print((wxChar *)parser.ParseTemplate().wchar_str());
		}
	}
	else if ( event.GetKeyCode() == 'C' )
	{
		AppData()->GenerateCode();
	}
	else
	{
		event.Skip();
	}
}
