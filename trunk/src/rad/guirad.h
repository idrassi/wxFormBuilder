///////////////////////////////////////////////////////////////////////////////
//
// wxFormBuilder - A Visual Dialog Editor for wxWidgets.
// Copyright (C) 2005 Jos� Antonio Hurtado
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
// Written by Jos� Antonio Hurtado - joseantonio.hurtado@hispalinux.es
//
///////////////////////////////////////////////////////////////////////////////

// -*- C++ -*- generated by wxGlade 0.3.5.1 on Tue Dec 28 20:50:56 2004

#include <wx/wx.h>
#include <wx/image.h>
// begin wxGlade: ::dependencies
#include <wx/notebook.h>
#include <wx/treectrl.h>
// end wxGlade


#ifndef GUIRAD_H
#define GUIRAD_H

#define ID_CPP 2020





class CodeEditorGUI: public wxFrame {
public:
    // begin wxGlade: CodeEditorGUI::ids
    // end wxGlade

    CodeEditorGUI(wxWindow* parent, int id, const wxString& title, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxDEFAULT_FRAME_STYLE);

private:
    // begin wxGlade: CodeEditorGUI::methods
    void set_properties();
    void do_layout();
    // end wxGlade

protected:
    // begin wxGlade: CodeEditorGUI::attributes
    wxStatusBar* frame_1_statusbar;
    wxMenuBar* frame_1_menubar;
    wxTextCtrl* m_txtHeader;
    wxPanel* notebook_2_pane_1;
    wxTextCtrl* m_txtSource;
    wxPanel* notebook_2_pane_2;
    wxNotebook* notebook_2;
    // end wxGlade
};


class ObjectInspectorGUI: public wxPanel {
public:
    // begin wxGlade: ObjectInspectorGUI::ids
    // end wxGlade

    ObjectInspectorGUI(wxWindow* parent, int id, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=0);

private:
    // begin wxGlade: ObjectInspectorGUI::methods
    void set_properties();
    void do_layout();
    // end wxGlade

protected:
    // begin wxGlade: ObjectInspectorGUI::attributes
    wxStaticText* label_2_copy;
    wxTextCtrl* text_ctrl_1_copy;
    wxStaticText* label_3_copy;
    wxComboBox* combo_box_1_copy;
    wxStaticText* label_4_copy;
    wxListBox* list_box_1_copy;
    wxStaticText* label_5;
    wxTextCtrl* text_ctrl_2;
    wxScrolledWindow* notebook_1_pane_1;
    wxPanel* notebook_1_pane_2;
    wxNotebook* notebook_1;
    // end wxGlade
};

class MyPanel: public wxPanel {
public:
// content of this block (ids) not found: did you rename this class?

    MyPanel(wxWindow* parent, int id, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=0);

private:
    void set_properties();
    void do_layout();

protected:
// content of this block (attributes) not found: did you rename this class?
};

class ObjectTreeGUI: public wxPanel {
public:
    // begin wxGlade: ObjectTreeGUI::ids
    // end wxGlade

    ObjectTreeGUI(wxWindow* parent, int id, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=0);

private:
    // begin wxGlade: ObjectTreeGUI::methods
    void set_properties();
    void do_layout();
    // end wxGlade

protected:
    // begin wxGlade: ObjectTreeGUI::attributes
    wxTextCtrl* m_txtSelected;
    wxTreeCtrl* m_tcObjects;
    // end wxGlade
};


#endif // GUIRAD_H
