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

#ifndef __VISUAL_EDITOR__
#define __VISUAL_EDITOR__


#include "wx/wx.h"
#include "rad/appobserver.h"
#include "model/objectbase.h"
#include "rad/designer/visualobj.h"

#include <wx/sashwin.h>

/**
 * Redefine el manjedor OnPaint para dibujar una rejilla.
 */

class GridPanel : public wxSashWindow //wxPanel
{
 private:
   int m_x;
   int m_y;
   wxSizer *m_selSizer;
   wxObject *m_selItem;
   WPObjectBase m_selObj;
   wxWindow *m_actPanel;
   
   void DrawRectangle(wxDC& dc, const wxPoint& point, const wxSize& size, PObjectBase object);
   
   DECLARE_CLASS(GridPanel)
   
 protected:
   DECLARE_EVENT_TABLE()
   
 public:
   GridPanel(wxWindow *parent, int id, const wxPoint& pos, const wxSize &size,
     long style, const wxString &name = wxT("gridpanel"));

   void SetGrid(int x, int y);
   void SetSelectedSizer(wxSizer *sizer) { m_selSizer = sizer; }
   void SetSelectedItem(wxObject *item) { m_selItem = item; }
   void SetSelectedObject(PObjectBase object) { m_selObj = object; }
   void SetSelectedPanel(wxWindow *actPanel) { m_actPanel = actPanel; }
   wxSizer *GetSelectedSizer() { return m_selSizer; }
   wxObject* GetSelectedItem() { return m_selItem; }
   PObjectBase GetSelectedObject() { return m_selObj.lock(); }
   wxWindow* GetActivePanel() { return m_actPanel; }
   void SetMenubar(PObjectBase menubar);
   void HighlightSelection(wxDC& dc);
   void OnPaint(wxPaintEvent &event);
//   void OnMouseMove(wxMouseEvent &event);
}; 

class VisualEditor : public DataObserver, public wxPanel
{
 private:
  typedef map<PObjectBase,PVisualObject> VisualObjectMap;
  VisualObjectMap m_map;
  
  GridPanel *m_back; 

  PObjectBase m_form;  // puntero al �ltimo form creado

  DECLARE_EVENT_TABLE()  
  
 protected:
  //PVisualObject Generate(PObjectBase obj, wxWindow *parent, wxSizer *sizer,
  //                       ObjectType parentType);
  PVisualObject Generate(PObjectBase obj, wxWindow *parent, wxSizer *sizer,
                         PVisualObject vobj_parent);
  void Create();
  
 public:
  VisualEditor(wxWindow *parent);
  void OnResizeBackPanel (wxSashEvent &event);
  void OnPaintPanel (wxPaintEvent &event);
  void DeleteVisualObject(PVisualObject obj);
  
  void Setup();

  ///////////////
  void ProjectLoaded();
  void ProjectSaved();
  void ObjectSelected(PObjectBase obj);
  void ObjectCreated(PObjectBase obj);
  void ObjectRemoved(PObjectBase obj);
  void PropertyModified(PProperty prop);
  void ProjectRefresh();

};  


#endif //__VISUAL_EDITOR__

