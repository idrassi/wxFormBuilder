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

#ifndef __VISUAL_EDITOR__
#define __VISUAL_EDITOR__


#include "wx/wx.h"
#include "model/objectbase.h"
#include "rad/designer/visualobj.h"
#include "rad/designer/resizablepanel.h"
#include <wx/sashwin.h>

/**
 * Redefine el manjedor OnPaint para dibujar una rejilla.
 */

class GridPanel : public ResizablePanel //wxSashWindow //wxPanel
{
 private:
   int m_x;
   int m_y;
   wxSizer *m_selSizer;
   wxObject *m_selItem;
   weak_ptr<ObjectBase> m_selObj;
   wxWindow *m_actPanel;

   void DrawRectangle(wxDC& dc, const wxPoint& point, const wxSize& size, shared_ptr<ObjectBase> object);

   DECLARE_CLASS(GridPanel)

 protected:
   DECLARE_EVENT_TABLE()

 public:
   GridPanel(wxWindow *parent, int id, const wxPoint& pos, const wxSize &size,
     long style, const wxString &name = wxT("gridpanel"));

   void SetGrid(int x, int y);
   void SetSelectedSizer(wxSizer *sizer) { m_selSizer = sizer; }
   void SetSelectedItem(wxObject *item) { m_selItem = item; }
   void SetSelectedObject(shared_ptr<ObjectBase> object) { m_selObj = object; }
   void SetSelectedPanel(wxWindow *actPanel) { m_actPanel = actPanel; }
   wxSizer *GetSelectedSizer() { return m_selSizer; }
   wxObject* GetSelectedItem() { return m_selItem; }
   shared_ptr<ObjectBase> GetSelectedObject() { return m_selObj.lock(); }
   wxWindow* GetActivePanel() { return m_actPanel; }
   wxMenu* GetMenuFromObject(shared_ptr<ObjectBase> menu);
   void SetFrameWidgets(shared_ptr<ObjectBase> menubar, wxWindow *toolbar, wxWindow* statusbar);
   void HighlightSelection(wxDC& dc);
   void OnPaint(wxPaintEvent &event);
//   void OnMouseMove(wxMouseEvent &event);
};

class wxFBEvent;
class wxFBPropertyEvent;
class wxFBObjectEvent;

class VisualEditor : public wxScrolledWindow
{
 private:
  typedef map<shared_ptr<ObjectBase>,PVisualObject> VisualObjectMap;
  VisualObjectMap m_map;

  GridPanel *m_back;

  shared_ptr<ObjectBase> m_form;  // puntero al último form creado

  DECLARE_EVENT_TABLE()

 protected:
  //PVisualObject Generate(shared_ptr<ObjectBase> obj, wxWindow *parent, wxSizer *sizer,
  //                       ObjectType parentType);
  PVisualObject Generate(shared_ptr<ObjectBase> obj, wxWindow *parent, wxSizer *sizer,
                         PVisualObject vobj_parent);
  void Create();

 public:
  VisualEditor(wxWindow *parent);
  ~VisualEditor();
  void OnResizeBackPanel (wxCommandEvent &event); //(wxSashEvent &event)
  void OnPaintPanel (wxPaintEvent &event);
  void DeleteVisualObject(PVisualObject obj);

  void Setup();
  void UpdateVirtualSize();

  // Events
  void OnProjectLoaded ( wxFBEvent &event );
  void OnProjectSaved  ( wxFBEvent &event );
  void OnObjectSelected( wxFBObjectEvent &event );
  void OnObjectCreated ( wxFBObjectEvent &event );
  void OnObjectRemoved ( wxFBObjectEvent &event );
  void OnPropertyModified ( wxFBPropertyEvent &event );
  void OnProjectRefresh ( wxFBEvent &event);
};


#endif //__VISUAL_EDITOR__

