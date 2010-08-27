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

#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>
#include <wx/propgrid/manager.h>
#include <wx/propgrid/props.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/stc/stc.h>

#include "logo.xpm"
#include "smiley.xpm"
/**
Event handler for events generated by controls in this plugin
*/
class ComponentEvtHandler : public wxEvtHandler
{
private:
	wxWindow* m_window;
	IManager* m_manager;

public:
	ComponentEvtHandler( wxWindow* win, IManager* manager )
	:
	m_window( win ),
	m_manager( manager ) {}

protected:
	// Enable folding for wxStyledTextCtrl
	void OnMarginClick ( wxStyledTextEvent& event );
	DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE( ComponentEvtHandler, wxEvtHandler )
	EVT_STC_MARGINCLICK( -1, ComponentEvtHandler::OnMarginClick )
END_EVENT_TABLE()

class PropertyGridComponent : public ComponentBase
{
public:
	wxObject* Create(IObject *obj, wxObject *parent)
	{
		wxPropertyGrid* pg = new wxPropertyGrid((wxWindow *)parent,-1,
												obj->GetPropertyAsPoint("pos"),
												obj->GetPropertyAsSize("size"),
												obj->GetPropertyAsInteger("style") |
												obj->GetPropertyAsInteger("window_style") );

		if ( !obj->GetPropertyAsString("extra_style").empty() )
			pg->SetExtraStyle( obj->GetPropertyAsInteger("extra_style") );

		pg->Append( new wxPropertyCategory( "Sample Category", wxPG_LABEL ) );

		// Add string property
		pg->Append( new wxStringProperty( "Label", "Name", "Initial Value" ) );

		// Add int property
		pg->Append( new wxIntProperty ( "IntProperty", wxPG_LABEL, 12345678 ) );

		// Add float property (value type is actually double)
		pg->Append( new wxFloatProperty ( "FloatProperty", wxPG_LABEL, 12345.678 ) );

		// Add bool properties
		pg->Append( new wxBoolProperty ( "BoolProperty", wxPG_LABEL, false ) );
		pg->Append( new wxBoolProperty ( "BoolPropertyAsCheckbox", wxPG_LABEL, true ) );
		pg->SetPropertyAttribute( "BoolPropertyAsCheckbox", wxPG_BOOL_USE_CHECKBOX, (long)1 );

		// A string property that can be edited in a separate editor dialog.
		pg->Append( new wxLongStringProperty ( "LongStringProperty",
			wxPG_LABEL,
			"This is much longer string than the "
			"first one. Edit it by clicking the button." ) );

		// String editor with dir selector button.
		pg->Append( new wxDirProperty( "DirProperty", wxPG_LABEL, ::wxGetUserHome() ) );

		// A file selector property.
		pg->Append( new wxFileProperty( "FileProperty", wxPG_LABEL, wxEmptyString ) );

		pg->Append( new wxPropertyCategory( "Sample Parent Property", wxPG_LABEL ) );

		wxPGProperty* carProp = pg->Append( new wxStringProperty( "Car", wxPG_LABEL, "<composed>" ) );
		pg->AppendIn( carProp, new wxStringProperty( "Model", wxPG_LABEL, "Lamborghini Diablo SV" ) );
		pg->AppendIn( carProp, new wxIntProperty( "Engine Size (cc)", wxPG_LABEL, 5707) );

		wxPGProperty* speedsProp = pg->AppendIn( carProp, new wxStringProperty( "Speeds", wxPG_LABEL, "<composed>" ) );
		pg->AppendIn( speedsProp, new wxIntProperty( "Max. Speed (mph)", wxPG_LABEL, 300 ) );
		pg->AppendIn( speedsProp, new wxFloatProperty( "0-100 mph (sec)", wxPG_LABEL, 3.9 ) );
		pg->AppendIn( speedsProp, new wxFloatProperty( "1/4 mile (sec)", wxPG_LABEL, 8.6) );

		pg->AppendIn( carProp, new wxIntProperty( "Price ($)", wxPG_LABEL, 300000 ) );

		if ( obj->GetPropertyAsInteger("include_advanced") )
		{
			pg->Append( new wxPropertyCategory( "Advanced Properties", wxPG_LABEL ) );
			// wxArrayStringProperty embeds a wxArrayString.
			pg->Append( new wxArrayStringProperty( "Example of ArrayStringProperty", "ArrayStringProp" ) );

			// Image file property. Wildcard is auto-generated from available
			// image handlers, so it is not set this time.
			pg->Append( new wxImageFileProperty( "Example of ImageFileProperty", "ImageFileProp" ) );

			// Font property has sub-properties.
			pg->Append( new wxFontProperty( "Font", wxPG_LABEL ) );

			// Colour property with arbitrary colour.
			pg->Append( new wxColourProperty( "My Colour 1", wxPG_LABEL, wxColour( 242, 109, 0 ) ) );

			// System colour property.
			pg->Append( new wxSystemColourProperty( "My SysColour 1", wxPG_LABEL, wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) ) );

			// System colour property with custom colour.
			pg->Append( new wxSystemColourProperty( "My SysColour 2", wxPG_LABEL, wxColour( 0, 200, 160 ) ) );

			// Cursor property
			pg->Append( new wxCursorProperty( "My Cursor", wxPG_LABEL, wxCURSOR_ARROW ) );
		}
		return pg;
	}

	void Cleanup( wxObject* )
	{
		// Prevent assert for missing event handler
	}
};

class PropertyGridManagerComponent : public ComponentBase
{
public:
	wxObject* Create(IObject *obj, wxObject *parent)
	{
		wxPropertyGridManager* pgman = new wxPropertyGridManager( (wxWindow *)parent, -1,
																obj->GetPropertyAsPoint("pos"),
																obj->GetPropertyAsSize("size"),
																obj->GetPropertyAsInteger("style") |
																obj->GetPropertyAsInteger("window_style") );

		if ( !obj->GetPropertyAsString("extra_style").empty() )
			pgman->SetExtraStyle( obj->GetPropertyAsInteger("extra_style") );

		pgman->ShowHeader( obj->GetPropertyAsInteger("show_header") );

		wxPropertyGridPage* pg = pgman->AddPage("First Page");

		pg->Append( new wxPropertyCategory( "Sample Category", wxPG_LABEL ) );

		// Add string property
		pg->Append( new wxStringProperty( "Label", "Name", "Initial Value" ) );

		// Add int property
		pg->Append( new wxIntProperty ( "IntProperty", wxPG_LABEL, 12345678 ) );

		// Add float property (value type is actually double)
		pg->Append( new wxFloatProperty ( "FloatProperty", wxPG_LABEL, 12345.678 ) );

		// Add bool properties
		pg->Append( new wxBoolProperty ( "BoolProperty", wxPG_LABEL, false ) );
		pg->Append( new wxBoolProperty ( "BoolPropertyAsCheckbox", wxPG_LABEL, true ) );
		pg->SetPropertyAttribute( "BoolPropertyAsCheckbox", wxPG_BOOL_USE_CHECKBOX, (long)1 );

		// Add an enum property
        wxArrayString strings;
        strings.Add( _("Herbivore") );
        strings.Add( _("Carnivore") );
        strings.Add( _("Omnivore") );

		wxArrayInt indexes;
		indexes.Add( 0 );
		indexes.Add( 1 );
		indexes.Add( 2 );

		pg->Append( new wxEnumProperty( "EnumProperty", wxPG_LABEL, strings, indexes, 0 ) );

		pg->Append( new wxPropertyCategory( "Low Priority Properties", wxPG_LABEL ) );
		// A string property that can be edited in a separate editor dialog.
		pg->Append( new wxLongStringProperty ( "LongStringProperty",
			wxPG_LABEL,
			"This is much longer string than the "
			"first one. Edit it by clicking the button." ) );

		// String editor with dir selector button.
		pg->Append( new wxDirProperty( "DirProperty", wxPG_LABEL, ::wxGetUserHome() ) );

		// A file selector property.
		pg->Append( new wxFileProperty( "FileProperty", wxPG_LABEL, wxEmptyString ) );

		wxPropertyGridPage* pg2 = pgman->AddPage("Second Page");

		pg2->Append( new wxPropertyCategory( "Sample Parent Property", wxPG_LABEL ) );

		wxPGProperty* carProp2 = pg2->Append( new wxStringProperty( "Car", wxPG_LABEL, "<composed>" ) );
		pg2->AppendIn( carProp2, new wxStringProperty( "Model", wxPG_LABEL, "Lamborghini Diablo SV" ) );
		pg2->AppendIn( carProp2, new wxIntProperty( "Engine Size (cc)", wxPG_LABEL, 5707) );

		wxPGProperty* speedsProp2 = pg2->AppendIn( carProp2, new wxStringProperty( "Speeds", wxPG_LABEL, "<composed>" ) );
		pg2->AppendIn( speedsProp2, new wxIntProperty( "Max. Speed (mph)", wxPG_LABEL, 300 ) );
		pg2->AppendIn( speedsProp2, new wxFloatProperty( "0-100 mph (sec)", wxPG_LABEL, 3.9 ) );
		pg2->AppendIn( speedsProp2, new wxFloatProperty( "1/4 mile (sec)", wxPG_LABEL, 8.6) );

		pg2->AppendIn( carProp2, new wxIntProperty( "Price ($)", wxPG_LABEL, 300000 ) );

		if ( obj->GetPropertyAsInteger("include_advanced") )
		{
			pg2->Append( new wxPropertyCategory( "Advanced Properties", wxPG_LABEL ) );
			// wxArrayStringProperty embeds a wxArrayString.
			pg2->Append( new wxArrayStringProperty( "Example of ArrayStringProperty", "ArrayStringProp" ) );

			// Image file property. Wildcard is auto-generated from available
			// image handlers, so it is not set this time.
			pg2->Append( new wxImageFileProperty( "Example of ImageFileProperty", "ImageFileProp" ) );

			// Font property has sub-properties.
			pg2->Append( new wxFontProperty( "Font", wxPG_LABEL ) );

			// Colour property with arbitrary colour.
			pg2->Append( new wxColourProperty( "My Colour 1", wxPG_LABEL, wxColour( 242, 109, 0 ) ) );

			// System colour property.
			pg2->Append( new wxSystemColourProperty( "My SysColour 1", wxPG_LABEL, wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) ) );

			// System colour property with custom colour.
			pg2->Append( new wxSystemColourProperty( "My SysColour 2", wxPG_LABEL, wxColour( 0, 200, 160 ) ) );

			// Cursor property
			pg2->Append( new wxCursorProperty( "My Cursor", wxPG_LABEL, wxCURSOR_ARROW ) );
		}
		pgman->SelectPage( 0 );
		return pgman;
	}
};

class RichTextCtrlComponent : public ComponentBase
{
public:
	wxObject* Create( IObject* obj, wxObject* parent )
	{
		wxRichTextCtrl* richText = new wxRichTextCtrl( 	(wxWindow*)parent,
														wxID_ANY,
														wxEmptyString,
														obj->GetPropertyAsPoint("pos"),
														obj->GetPropertyAsSize("size"),
														obj->GetPropertyAsInteger("style") |
														obj->GetPropertyAsInteger("window_style") );

		wxFont textFont = 	wxFont( 12, wxROMAN, wxNORMAL, wxNORMAL );
		wxFont boldFont = 	wxFont( 12, wxROMAN, wxNORMAL, wxBOLD );
		wxFont italicFont = wxFont( 12, wxROMAN, wxITALIC, wxNORMAL );
		wxFont font( 12, wxROMAN, wxNORMAL, wxNORMAL );

		wxRichTextCtrl& r = *richText;
		r.SetFont( font );
		r.BeginSuppressUndo();

		r.BeginParagraphSpacing( 0, 20 );

		r.BeginAlignment( wxTEXT_ALIGNMENT_CENTRE );
		r.BeginBold();

		r.BeginFontSize(14);
		r.WriteText( _("Welcome to wxRichTextCtrl, a wxWidgets control for editing and presenting styled text and images") );
		r.EndFontSize();
		r.Newline();

		r.BeginItalic();
		r.WriteText( _("by Julian Smart") );
		r.EndItalic();

		r.EndBold();

		r.Newline();
		r.WriteImage(wxBitmap(logo_xpm));

		r.EndAlignment();

		r.Newline();

		r.WriteText( _("What can you do with this thing? ") );
		r.WriteImage(wxBitmap(smiley_xpm));
		r.WriteText( _(" Well, you can change text ") );

		r.BeginTextColour(wxColour(255, 0, 0));
		r.WriteText( _("colour, like this red bit.") );
		r.EndTextColour();

		r.BeginTextColour(wxColour(0, 0, 255));
		r.WriteText( _(" And this blue bit.") );
		r.EndTextColour();

		r.WriteText( _(" Naturally you can make things ") );
		r.BeginBold();
		r.WriteText( _("bold ") );
		r.EndBold();
		r.BeginItalic();
		r.WriteText( _("or italic ") );
		r.EndItalic();
		r.BeginUnderline();
		r.WriteText( _("or underlined.") );
		r.EndUnderline();

		r.BeginFontSize(14);
		r.WriteText( _(" Different font sizes on the same line is allowed, too.") );
		r.EndFontSize();

		r.WriteText( _(" Next we'll show an indented paragraph.") );

		r.BeginLeftIndent(60);
		r.Newline();

		r.WriteText( _("Indented paragraph.") );
		r.EndLeftIndent();

		r.Newline();

		r.WriteText( _("Next, we'll show a first-line indent, achieved using BeginLeftIndent(100, -40).") );

		r.BeginLeftIndent(100, -40);
		r.Newline();

		r.WriteText( _("It was in January, the most down-trodden month of an Edinburgh winter.") );
		r.EndLeftIndent();

		r.Newline();

		r.WriteText( _("Numbered bullets are possible, again using subindents:") );

		r.BeginNumberedBullet(1, 100, 60);
		r.Newline();

		r.WriteText( _("This is my first item. Note that wxRichTextCtrl doesn't automatically do numbering, but this will be added later.") );
		r.EndNumberedBullet();

		r.BeginNumberedBullet(2, 100, 60);
		r.Newline();

		r.WriteText( _("This is my second item.") );
		r.EndNumberedBullet();

		r.Newline();

		r.WriteText( _("The following paragraph is right-indented:") );

		r.BeginRightIndent(200);
		r.Newline();

		r.WriteText( _("It was in January, the most down-trodden month of an Edinburgh winter. An attractive woman came into the cafe, which is nothing remarkable.") );
		r.EndRightIndent();

		r.Newline();

		wxArrayInt tabs;
		tabs.Add(400);
		tabs.Add(600);
		tabs.Add(800);
		tabs.Add(1000);
		wxTextAttrEx attr;
		attr.SetFlags(wxTEXT_ATTR_TABS);
		attr.SetTabs(tabs);
		r.SetDefaultStyle(attr);

		r.WriteText( _("This line contains tabs:\tFirst tab\tSecond tab\tThird tab") );

		r.Newline();
		r.WriteText( _("Other notable features of wxRichTextCtrl include:") );

		r.BeginSymbolBullet(_('*'), 100, 60);
		r.Newline();
		r.WriteText( _("Compatibility with wxTextCtrl API") );
		r.EndSymbolBullet();

		r.WriteText( _("\nNote: this content was generated programmatically and copied from the sample. The images were loaded from inline XPMs. Enjoy wxRichTextCtrl!") );

		r.EndSuppressUndo();

		return richText;
	}

	virtual void Cleanup( wxObject* obj )
    {
    }

/*
	ticpp::Element* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc( obj, "wxRichTextCtrl", obj->GetPropertyAsString("name") );
		xrc.AddWindowProperties();
		return xrc.GetXrcObject();
	}

	ticpp::Element* ImportFromXrc( ticpp::Element* xrcObj )
	{
		XrcToXfbFilter filter( xrcObj, "wxRichTextCtrl" );
		filter.AddWindowProperties();
		return filter.GetXfbObject();
	}
*/
};

class StyledTextCtrlComponent : public ComponentBase
{
public:
	wxObject* Create( IObject* obj, wxObject* parent )
	{
		wxStyledTextCtrl* m_code = new wxStyledTextCtrl((wxWindow *)parent, -1,
														obj->GetPropertyAsPoint("pos"),
														obj->GetPropertyAsSize("size"),
														obj->GetPropertyAsInteger("window_style"),
														obj->GetPropertyAsString("name") );

		// Line Numbers
		if ( 0 != obj->GetPropertyAsInteger("line_numbers") )
		{
			m_code->SetMarginType( 0, wxSTC_MARGIN_NUMBER );
			m_code->SetMarginWidth( 0, m_code->TextWidth( wxSTC_STYLE_LINENUMBER, "_99999" ) );
		}
		else
			m_code->SetMarginWidth( 0, 0 );

		// Markers
		m_code->MarkerDefine 		( wxSTC_MARKNUM_FOLDER, 		wxSTC_MARK_BOXPLUS );
		m_code->MarkerSetBackground ( wxSTC_MARKNUM_FOLDER, 		wxColour("BLACK") );
		m_code->MarkerSetForeground ( wxSTC_MARKNUM_FOLDER, 		wxColour("WHITE") );
		m_code->MarkerDefine 		( wxSTC_MARKNUM_FOLDEROPEN, 	wxSTC_MARK_BOXMINUS );
		m_code->MarkerSetBackground ( wxSTC_MARKNUM_FOLDEROPEN, 	wxColour("BLACK") );
		m_code->MarkerSetForeground ( wxSTC_MARKNUM_FOLDEROPEN, 	wxColour("WHITE") );
		m_code->MarkerDefine 		( wxSTC_MARKNUM_FOLDERSUB, 		wxSTC_MARK_EMPTY );
		m_code->MarkerDefine 		( wxSTC_MARKNUM_FOLDEREND, 		wxSTC_MARK_BOXPLUS );
		m_code->MarkerSetBackground ( wxSTC_MARKNUM_FOLDEREND, 		wxColour("BLACK") );
		m_code->MarkerSetForeground ( wxSTC_MARKNUM_FOLDEREND, 		wxColour("WHITE") );
		m_code->MarkerDefine 		( wxSTC_MARKNUM_FOLDEROPENMID, 	wxSTC_MARK_BOXMINUS );
		m_code->MarkerSetBackground ( wxSTC_MARKNUM_FOLDEROPENMID, 	wxColour("BLACK") );
		m_code->MarkerSetForeground ( wxSTC_MARKNUM_FOLDEROPENMID, 	wxColour("WHITE") );
		m_code->MarkerDefine ( 		  wxSTC_MARKNUM_FOLDERMIDTAIL, 	wxSTC_MARK_EMPTY );
		m_code->MarkerDefine ( 		  wxSTC_MARKNUM_FOLDERTAIL, 	wxSTC_MARK_EMPTY );

		// Folding
		if ( 0 != obj->GetPropertyAsInteger("folding") )
		{
			m_code->SetMarginType ( 1, wxSTC_MARGIN_SYMBOL );
			m_code->SetMarginMask ( 1, wxSTC_MASK_FOLDERS );
			m_code->SetMarginWidth ( 1, 16 );
			m_code->SetMarginSensitive ( 1, true );

			m_code->SetProperty( "fold", "1" );
			m_code->SetFoldFlags( wxSTC_FOLDFLAG_LINEBEFORE_CONTRACTED | wxSTC_FOLDFLAG_LINEAFTER_CONTRACTED );
		}
		else
			m_code->SetMarginWidth( 1, 0 );

		m_code->SetIndentationGuides( ( 0 != obj->GetPropertyAsInteger("indentation_guides") ) );

		m_code->SetMarginWidth( 2, 0 );

		m_code->SetLexer( wxSTC_LEX_CPP);
		m_code->SetKeyWords( 0, "asm auto bool break case catch char class const const_cast \
								continue default delete do double dynamic_cast else enum explicit \
								export extern false float for friend goto if inline int long \
								mutable namespace new operator private protected public register \
								reinterpret_cast return short signed sizeof static static_cast \
								struct switch template this throw true try typedef typeid \
								typename union unsigned using virtual void volatile wchar_t while" );

		wxFont font( 10, wxMODERN, wxNORMAL, wxNORMAL );
		if ( !obj->GetPropertyAsString("font").empty() )
			font = obj->GetPropertyAsFont("font");

		m_code->StyleSetFont( wxSTC_STYLE_DEFAULT, font );

		m_code->StyleClearAll();
		m_code->StyleSetBold( 		wxSTC_C_WORD, 			true );
		m_code->StyleSetForeground( wxSTC_C_WORD, 			*wxBLUE );
		m_code->StyleSetForeground( wxSTC_C_STRING, 		*wxRED );
		m_code->StyleSetForeground( wxSTC_C_STRINGEOL, 		*wxRED );
		m_code->StyleSetForeground( wxSTC_C_PREPROCESSOR, 	wxColour( 49, 106, 197 ) );
		m_code->StyleSetForeground( wxSTC_C_COMMENT, 		wxColour( 0, 128, 0 ) );
		m_code->StyleSetForeground( wxSTC_C_COMMENTLINE, 	wxColour( 0, 128, 0 ) );
		m_code->StyleSetForeground( wxSTC_C_COMMENTDOC, 	wxColour( 0, 128, 0 ) );
		m_code->StyleSetForeground( wxSTC_C_COMMENTLINEDOC, wxColour( 0, 128, 0 ) );
		m_code->StyleSetForeground( wxSTC_C_NUMBER, 		*wxBLUE );

		m_code->SetUseTabs( ( 0 != obj->GetPropertyAsInteger("use_tabs") ) );
		m_code->SetTabWidth( obj->GetPropertyAsInteger("tab_width") );
		m_code->SetTabIndents( ( 0 != obj->GetPropertyAsInteger("tab_indents") ) );
		m_code->SetBackSpaceUnIndents( ( 0 != obj->GetPropertyAsInteger("backspace_unindents") ) );
		m_code->SetIndent( obj->GetPropertyAsInteger("tab_width") );
		m_code->SetSelBackground( true, wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHT ) );
		m_code->SetSelForeground( true, wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHTTEXT ) );
		m_code->SetViewEOL( ( 0 != obj->GetPropertyAsInteger("view_eol") ) );
		m_code->SetViewWhiteSpace( ( 0 != obj->GetPropertyAsInteger("view_whitespace") ) );

		m_code->SetCaretWidth( 2 );

		m_code->SetText( 	"/** Sample Class to Display wxStyledTextCtrl */\n"
							"class ScintillaSampleCode\n"
							"{\n"
							"private:\n"
							"\tint m_privateMember;\n\n"
							"public:\n\n"
							"\t// Sample Member Function\n"
							"\tint SampleFunction( int sample = 0 )\n"
							"\t{\n"
							"\t\treturn sample;\n"
							"\t}\n"
							"};\n" );

		m_code->PushEventHandler( new ComponentEvtHandler( m_code, GetManager() ) );

		return m_code;
	}
};

void ComponentEvtHandler::OnMarginClick( wxStyledTextEvent& event )
{
	wxStyledTextCtrl* stc = wxDynamicCast( m_window, wxStyledTextCtrl );
	if ( stc != NULL )
	{
		if ( event.GetMargin() == 1 )
		{
			int lineClick 	= stc->LineFromPosition( event.GetPosition() );
			int levelClick 	= stc->GetFoldLevel( lineClick );

			if ( ( levelClick & wxSTC_FOLDLEVELHEADERFLAG ) > 0 )
				stc->ToggleFold( lineClick );
		}
	}
	event.Skip();
}

BEGIN_LIBRARY()

	WINDOW_COMPONENT( "wxPropertyGrid", PropertyGridComponent )
	MACRO(wxPG_AUTO_SORT)
	MACRO(wxPG_HIDE_CATEGORIES)
	MACRO(wxPG_ALPHABETIC_MODE)
	MACRO(wxPG_BOLD_MODIFIED)
	MACRO(wxPG_SPLITTER_AUTO_CENTER)
	MACRO(wxPG_TOOLTIPS)
	MACRO(wxPG_HIDE_MARGIN)
	MACRO(wxPG_STATIC_SPLITTER)
	MACRO(wxPG_STATIC_LAYOUT)
	MACRO(wxPG_LIMITED_EDITING)
	MACRO(wxPG_EX_INIT_NOCAT)
	MACRO(wxPG_DEFAULT_STYLE)
	MACRO(wxTAB_TRAVERSAL)

	WINDOW_COMPONENT( "wxPropertyGridManager", PropertyGridManagerComponent )
	MACRO(wxPG_EX_NO_FLAT_TOOLBAR)
	MACRO(wxPG_EX_MODE_BUTTONS)
	MACRO(wxPGMAN_DEFAULT_STYLE)
	MACRO(wxPG_DESCRIPTION)
	MACRO(wxPG_TOOLBAR)

	WINDOW_COMPONENT( "wxRichTextCtrl", RichTextCtrlComponent )
	MACRO(wxTE_PROCESS_ENTER);
	MACRO(wxTE_PROCESS_TAB);
	MACRO(wxTE_READONLY);
	MACRO(wxTE_AUTO_URL);

	WINDOW_COMPONENT( "wxStyledTextCtrl", StyledTextCtrlComponent )

END_LIBRARY()
