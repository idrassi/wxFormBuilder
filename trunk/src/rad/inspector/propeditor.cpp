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
// Written by José Antonio Hurtado - joseantonio.hurtado@hispalinux.es
//
///////////////////////////////////////////////////////////////////////////////

#include "propeditor.h"
#include "utils/typeconv.h"
#include <wx/tokenzr.h>
#include "utils/debug.h"
#include <wx/fontdlg.h>
#include <wx/colordlg.h>

using namespace TypeConv;

wxWindow * PropertyEditor::CreatePropertyEditor(DataObservable *data,
  PProperty prop,wxWindow *parent)
{
  wxWindow *result = NULL;
  PPropertyInfo pinfo = prop->GetPropertyInfo();
  PropertyType type = pinfo->GetType();
/*
  wxString value(prop->GetValue().c_str(),wxConvUTF8);
  if (value == wxT(""))
    value = wxString(prop_desc->GetDefaultValue().c_str(),wxConvUTF8);
  */
  
  if (type == PT_TEXT || type == PT_MACRO || type == PT_WXSTRING)
    result = new TextEditor(data,prop,parent,-1);

  else if (type == PT_BOOL)
    result = new BoolEditor(data,prop,parent,-1);
    
  else if (type == PT_BITLIST)
    result = new BitlistEditor(data,prop,parent,-1);

  else if (type == PT_INTLIST)
    result = new IntlistEditor(data,prop,parent,-1);

  else if (type == PT_OPTION)
    result = new OptionEditor(data,prop,parent,-1);

  else if (type == PT_WXPOINT)
    result = new PointEditor(data,prop,parent,-1);

  else if (type == PT_WXSIZE)
    result = new PointEditor(data,prop,parent,-1);
  
  else if (type == PT_WXFONT)
    result = new FontEditor(data,prop,parent,-1);

  else if (type == PT_WXCOLOUR)
    result = new ColourEditor(data,prop,parent,-1);

  else if (type == PT_PATH)
    result = new PathEditor(data,prop,parent,-1);
  
  else if (type == PT_BITMAP)
    result = new BitmapEditor(data,prop,parent,-1);
    
  return result;
}


PointEditor::PointEditor(DataObservable *data, PProperty prop, wxWindow *parent, int id)
  : PropertyEditor(data,prop), wxTextCtrl(parent,id)
{
  RetrieveValue();
  PushEventHandler(new UpdateEventHandler(this));
}
  
PointEditor::~PointEditor()
{
//  UpdateValue();
}  
   
void PointEditor::RetrieveValue()
{
  SetValue(wxString(GetProperty()->GetValue().c_str(),wxConvUTF8));
}
  
void PointEditor::UpdateValue()
{
  wxString val = GetValue();
  wxPoint point;
  // chequeamos si es un valor bueno
  
  if (!StringToPoint(val,&point))
    val = wxT("");
    
  GetData()->ModifyProperty(GetProperty(),val);
}  


OptionEditor::OptionEditor(DataObservable *data, PProperty prop, wxWindow *parent, int id)
  : PropertyEditor(data,prop), wxComboBox(parent,id, wxT(""), wxDefaultPosition,
      wxDefaultSize, 0, NULL, wxCB_READONLY)
{
  PPropertyInfo prop_desc = prop->GetPropertyInfo();
  POptionList opt_list = prop_desc->GetOptionList();
  for (unsigned int i=0; i<opt_list->GetOptionCount() ;i++)
    Append(wxString(opt_list->GetOption(i).c_str(),wxConvUTF8));
    
  RetrieveValue();
  PushEventHandler(new UpdateEventHandler(this));
}  

void OptionEditor::RetrieveValue()
{
  ParseValue(wxString(GetProperty()->GetValue().c_str(),wxConvUTF8));
}  
  
void OptionEditor::UpdateValue()
{
 //GetProperty()->SetValue(GetString(GetSelection()).c_str());
  wxString val = GetString(GetSelection());
  GetData()->ModifyProperty(GetProperty(),val);
}  

OptionEditor::~OptionEditor()
{
//  UpdateValue();
}  

void OptionEditor::ParseValue(const wxString &val)
{
  if (val != wxT(""))
  {
    int i=0;
    while (i < GetCount() && val != GetString(i))
      i++;
      
    if (i < GetCount())
      SetValue(GetString(i));
    else
      SetValue(GetString(0));
  }
}

BEGIN_EVENT_TABLE(BitlistEditor,wxListBox)
  EVT_LISTBOX(-1,BitlistEditor::OnSelectItem)
END_EVENT_TABLE()

BitlistEditor::BitlistEditor(DataObservable *data, PProperty prop, wxWindow *parent, int id)
  : PropertyEditor(data,prop), wxListBox(parent,id, wxDefaultPosition,
      wxDefaultSize, 0, NULL, wxLB_MULTIPLE)
{
  PPropertyInfo prop_desc = prop->GetPropertyInfo();
  POptionList opt_list = prop_desc->GetOptionList();
  
  assert(opt_list && opt_list->GetOptionCount() > 0);
  
  for (unsigned int i=0; i<opt_list->GetOptionCount() ;i++)
    Append(wxString(opt_list->GetOption(i).c_str(),wxConvUTF8));
    
  RetrieveValue();
  PushEventHandler(new UpdateEventHandler(this));
}  

BitlistEditor::~BitlistEditor()
{
//  UpdateValue();
}  

void BitlistEditor::RetrieveValue()
{
  ParseValue(wxString(GetProperty()->GetValue().c_str(),wxConvUTF8));
}  

void BitlistEditor::ParseValue(const wxString &val)
{
  if (val != wxT(""))
  {
    wxStringTokenizer tkz(val, wxT("|"));
    while (tkz.HasMoreTokens())
    {
      wxString token;
      token = tkz.GetNextToken();
      token.Trim(true);
      token.Trim(false);
      
      int i=0;
      while (i < GetCount() && token != GetString(i))
        i++;
        
      if (i < GetCount())
        SetSelection(i);
    }  
  }  
}  
  
void BitlistEditor::UpdateValue()
{
  wxString val;
  
  for (int i=0; i < GetCount() ; i++)
  {
    if (Selected(i))
    {
      if (val != wxT(""))
        val = val + wxT("|");
        
      val = val + GetString(i);
    }  
  }  
  
  //GetProperty()->SetValue(val.c_str());
  GetData()->ModifyProperty(GetProperty(),val);
}

void BitlistEditor::OnSelectItem(wxCommandEvent &event)
{
  UpdateValue();  
}

TextEditor::TextEditor(DataObservable *data, PProperty prop, wxWindow *parent, int id)
  : PropertyEditor(data,prop), wxTextCtrl(parent,id)
{
  RetrieveValue();
  PushEventHandler(new UpdateEventHandler(this));
}
  
TextEditor::~TextEditor()
{
//  UpdateValue();
}  
   
void TextEditor::RetrieveValue()
{
  SetValue(wxString(GetProperty()->GetValue().c_str(),wxConvUTF8));
}
  
void TextEditor::UpdateValue()
{
  
  wxString val = GetValue();
  if (val != wxT(""))
    //GetProperty()->SetValue(val.c_str());
    GetData()->ModifyProperty(GetProperty(),val);
    
//  GetProperty()->GetObject()->Notify();
}  



IntlistEditor::IntlistEditor(DataObservable *data, PProperty prop, wxWindow *parent, int id)
  : PropertyEditor(data,prop), wxTextCtrl(parent,id)
{
  RetrieveValue();
  PushEventHandler(new UpdateEventHandler(this));
}

IntlistEditor::~IntlistEditor()
{
}

void IntlistEditor::RetrieveValue()
{
  m_list.SetList(GetProperty()->GetValue());
  SetValue(wxString(m_list.ToString().c_str(),wxConvUTF8));
}
  
void IntlistEditor::UpdateValue()
{
  m_list.SetList(string(GetValue().mb_str()));
  wxString val = wxString (m_list.ToString().c_str(),wxConvUTF8);
  if (val != wxT(""))
    //GetProperty()->SetValue(val.c_str());
    GetData()->ModifyProperty(GetProperty(),val);
}  


BoolEditor::BoolEditor(DataObservable *data, PProperty prop, wxWindow *parent, int id)
  : PropertyEditor(data,prop), wxCheckBox(parent,id,wxT(""))
{
  RetrieveValue();
  PushEventHandler(new UpdateEventHandler(this));
}

BoolEditor::~BoolEditor()
{
//  UpdateValue();
}  

  
void BoolEditor::RetrieveValue()
{
  wxString val(GetProperty()->GetValue().c_str(),wxConvUTF8);
  
  if (val == wxT("1"))
    SetValue(true);
  else
    SetValue(false);
}  

void BoolEditor::UpdateValue()
{
  wxString val;
  if (GetValue())
    val = wxT("1");
  else
    val = wxT("0");
    
  //GetProperty()->SetValue(val.c_str());
  GetData()->ModifyProperty(GetProperty(),val);
}

#define BUTTON_CHOOSE_FONT 1000
BEGIN_EVENT_TABLE(FontEditor,wxPanel)
  EVT_BUTTON(BUTTON_CHOOSE_FONT,FontEditor::OnChooseFont)
END_EVENT_TABLE()

FontEditor::FontEditor(DataObservable *data, PProperty prop, wxWindow *parent, int id)
  : PropertyEditor(data,prop), wxPanel(parent,id)
{
    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);

    m_text = new wxTextCtrl(this,-1,wxT(""));
//    m_text->Disable();
    m_button = new wxButton(this,BUTTON_CHOOSE_FONT,wxT("Choose..."));
    
    sizer->Add(m_text,1,wxADJUST_MINSIZE,0);
    sizer->Add(m_button,0,wxADJUST_MINSIZE,0);
    SetSizer(sizer);
    RetrieveValue();
}

void FontEditor::OnChooseFont(wxCommandEvent &event)
{
  wxFontData data;
      
  wxFontDialog dialog(this, &data);
  if (dialog.ShowModal() == wxID_OK)
  {
    wxString value;
    
    wxFontData ret_data = dialog.GetFontData();
    // tipo de letra
    wxFont font = ret_data.GetChosenFont();
    
//    value = wxString::Format(wxT("'%s','%d'"),font.GetFaceName().c_str(),font.GetPointSize());
//    value = wxString::Format(wxT("'%d','%d'"),font.GetFamily(),font.GetPointSize());
    value = FontToString(font);
    
    m_text->SetValue(value);
    UpdateValue();
  }
}

FontEditor::~FontEditor()
{
}

void FontEditor::RetrieveValue()
{
  wxString val(GetProperty()->GetValue().c_str(),wxConvUTF8);
  m_text->SetValue(val);
}

void FontEditor::UpdateValue()
{
  wxString val = m_text->GetValue();
  GetData()->ModifyProperty(GetProperty(),val);  
}

////////
#define BUTTON_CHOOSE_COLOUR 1001
BEGIN_EVENT_TABLE(ColourEditor,wxPanel)
  EVT_BUTTON(BUTTON_CHOOSE_COLOUR,ColourEditor::OnChooseColour)
END_EVENT_TABLE()

ColourEditor::ColourEditor(DataObservable *data, PProperty prop, wxWindow *parent, int id)
  : PropertyEditor(data,prop), wxPanel(parent,id)
{
    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);

    m_text = new wxTextCtrl(this,-1,wxT(""));
//    m_text->Disable();
    
    m_button = new wxButton(this,BUTTON_CHOOSE_COLOUR,wxT("Choose..."));
    
    sizer->Add(m_text,1,wxADJUST_MINSIZE,0);
    sizer->Add(m_button,0,wxADJUST_MINSIZE,0);
    SetSizer(sizer);
    RetrieveValue();
}

void ColourEditor::OnChooseColour(wxCommandEvent &event)
{
  wxColourData data;
    
  wxColourDialog dialog(this, &data);
  if (dialog.ShowModal() == wxID_OK)
  {
    wxColourData ret_data = dialog.GetColourData();
    wxColour colour = ret_data.GetColour();
    wxString val = ColourToString(colour);
    m_text->SetValue(val);
    UpdateValue();
  }
}

ColourEditor::~ColourEditor()
{
}

void ColourEditor::RetrieveValue()
{
  wxString val(GetProperty()->GetValue().c_str(),wxConvUTF8);
  m_text->SetValue(val);

}

void ColourEditor::UpdateValue()
{
  wxString val = m_text->GetValue();
  GetData()->ModifyProperty(GetProperty(),val);  
}



#define BUTTON_SELECT_PATH 1002
BEGIN_EVENT_TABLE(PathEditor,wxPanel)
  EVT_BUTTON(BUTTON_SELECT_PATH,PathEditor::OnSelectPath)
END_EVENT_TABLE()

PathEditor::PathEditor(DataObservable *data, PProperty prop, wxWindow *parent, int id)
  : PropertyEditor(data,prop), wxPanel(parent,id)
{
    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);

    m_text = new wxTextCtrl(this,-1,wxT(""));
//    m_text->Disable();
    
    m_button = new wxButton(this,BUTTON_SELECT_PATH,wxT("..."),
      wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
    
    sizer->Add(m_text,1,wxADJUST_MINSIZE,0);
    sizer->Add(m_button,0,wxADJUST_MINSIZE,0);
    SetSizer(sizer);
    RetrieveValue();
}

void PathEditor::OnSelectPath(wxCommandEvent &event)
{
  wxDirDialog *dialog = new wxDirDialog(this);
  if (dialog->ShowModal() == wxID_OK)
  {
    wxString path = dialog->GetPath();
    m_text->SetValue(path);
    UpdateValue();
  }
  dialog->Destroy();
}

PathEditor::~PathEditor()
{
}

void PathEditor::RetrieveValue()
{
  wxString val(GetProperty()->GetValue().c_str(),wxConvUTF8);
  m_text->SetValue(val);

}

void PathEditor::UpdateValue()
{
  wxString val = m_text->GetValue();
  GetData()->ModifyProperty(GetProperty(),val);  
}


#define BUTTON_SELECT_BITMAP 1003
BEGIN_EVENT_TABLE(BitmapEditor,wxPanel)
  EVT_BUTTON(BUTTON_SELECT_BITMAP,BitmapEditor::OnSelectBitmap)
END_EVENT_TABLE()

BitmapEditor::BitmapEditor(DataObservable *data, PProperty prop, wxWindow *parent, int id)
  : PropertyEditor(data,prop), wxPanel(parent,id)
{
    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);

    m_text = new wxTextCtrl(this,-1,wxT(""));
//    m_text->Disable();
    
    m_button = new wxButton(this,BUTTON_SELECT_BITMAP,wxT("..."),
      wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
    
    sizer->Add(m_text,1,wxADJUST_MINSIZE,0);
    sizer->Add(m_button,0,wxADJUST_MINSIZE,0);
    SetSizer(sizer);
    RetrieveValue();
}

void BitmapEditor::OnSelectBitmap(wxCommandEvent &event)
{
  wxFileDialog *dialog = new wxFileDialog(this,wxT("Open Image"),wxT(""),
    wxT(""),wxT("*.xpm"),wxOPEN);

  if (dialog->ShowModal() == wxID_OK)
  {
    wxString path = dialog->GetPath();
    m_text->SetValue(path);
    UpdateValue();
  };
  
  dialog->Destroy();
}

BitmapEditor::~BitmapEditor()
{
}

void BitmapEditor::RetrieveValue()
{
  wxString val(GetProperty()->GetValue().c_str(),wxConvUTF8);
  m_text->SetValue(val);

}

void BitmapEditor::UpdateValue()
{
  wxString val = m_text->GetValue();
  GetData()->ModifyProperty(GetProperty(),val);  
}

BEGIN_EVENT_TABLE(UpdateEventHandler, wxEvtHandler)
  EVT_KILL_FOCUS(UpdateEventHandler::OnKillFocus)
END_EVENT_TABLE()  

void UpdateEventHandler::OnKillFocus(wxFocusEvent &event)
{
  Debug::Print("[Focus Event]");
  m_propEditor->UpdateValue();
  event.Skip();
}

